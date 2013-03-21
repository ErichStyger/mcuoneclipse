/*
 * Reflectance.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Reflectance.h"
#include "LED_IR.h"
#include "WAIT1.h"
#include "RefCnt.h" /* timer counter to measure reflectance */
#include "IR1.h"
#include "IR2.h"
#include "IR3.h"
#include "IR4.h"
#include "IR5.h"
#include "IR6.h"
#if REF_NOF_SENSORS>=7
  #include "IR7.h"
#endif
#if REF_NOF_SENSORS>=8
  #include "IR8.h"
#endif
#include "UTIL1.h"
#include "TMOUT1.h"
#include "FRTOS1.h"
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#include "Application.h"

static LDD_TDeviceData *timerHandle;
static xQueueHandle mutexHandle;
static bool doMinMaxCalibration = FALSE;
#define REF_SENSOR_TIMEOUT_MS  3  /* after this time, consider no reflection (black) */
#if PL_IS_ZUMO_ROBOT
  #define REF_MIN_LINE_VAL   0x100  /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL  0x45  /* values below this are not added to the weighted sum */
#else
  #define REF_MIN_LINE_VAL   0x60  /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL  0x32   /* values below this are not added to the weighted sum */
#endif

typedef struct {
  void (*SetOutput)(void);
  void (*SetInput)(void);
  void (*SetVal)(void);
  bool (*GetVal)(void);
} SensorFctType;

typedef uint16_t SensorTimeType;
#define MAX_SENSOR_VALUE  ((SensorTimeType)-1)
#define REF_NOF_HISTORY   1

static SensorTimeType SensorRaw[REF_NOF_SENSORS]; 
static SensorTimeType SensorMin[REF_NOF_SENSORS]; 
static SensorTimeType SensorMax[REF_NOF_SENSORS]; 
static SensorTimeType SensorCalibrated[REF_NOF_SENSORS]; /* 0 means white/min value, 1000 means black/max value */
static SensorTimeType SensorHistory[REF_NOF_SENSORS];
static bool isCalibrated = FALSE;
static bool ledON = TRUE;
static int16_t refCenterLineVal=0; /* 0 means no line, >0 means line is below sensor 0, 1000 below sensor 1 and so on */
static REF_LineKind refLineKind = REF_LINE_NONE;

/* Functions as wrapper around macro. Number S1 is on the right side */
static void S1_SetOutput(void) { IR1_SetOutput(); }
static void S1_SetInput(void) { IR1_SetInput(); }
static void S1_SetVal(void) { IR1_SetVal(); }
static bool S1_GetVal(void) { return IR1_GetVal(); }

static void S2_SetOutput(void) { IR2_SetOutput(); }
static void S2_SetInput(void) { IR2_SetInput(); }
static void S2_SetVal(void) { IR2_SetVal(); }
static bool S2_GetVal(void) { return IR2_GetVal(); }

static void S3_SetOutput(void) { IR3_SetOutput(); }
static void S3_SetInput(void) { IR3_SetInput(); }
static void S3_SetVal(void) { IR3_SetVal(); }
static bool S3_GetVal(void) { return IR3_GetVal(); }

static void S4_SetOutput(void) { IR4_SetOutput(); }
static void S4_SetInput(void) { IR4_SetInput(); }
static void S4_SetVal(void) { IR4_SetVal(); }
static bool S4_GetVal(void) { return IR4_GetVal(); }

static void S5_SetOutput(void) { IR5_SetOutput(); }
static void S5_SetInput(void) { IR5_SetInput(); }
static void S5_SetVal(void) { IR5_SetVal(); }
static bool S5_GetVal(void) { return IR5_GetVal(); }

static void S6_SetOutput(void) { IR6_SetOutput(); }
static void S6_SetInput(void) { IR6_SetInput(); }
static void S6_SetVal(void) { IR6_SetVal(); }
static bool S6_GetVal(void) { return IR6_GetVal(); }

#if REF_NOF_SENSORS>=7
static void S7_SetOutput(void) { IR7_SetOutput(); }
static void S7_SetInput(void) { IR7_SetInput(); }
static void S7_SetVal(void) { IR7_SetVal(); }
static bool S7_GetVal(void) { return IR7_GetVal(); }
#endif
#if REF_NOF_SENSORS>=8
static void S8_SetOutput(void) { IR8_SetOutput(); }
static void S8_SetInput(void) { IR8_SetInput(); }
static void S8_SetVal(void) { IR8_SetVal(); }
static bool S8_GetVal(void) { return IR8_GetVal(); }
#endif

static const SensorFctType SensorFctArray[REF_NOF_SENSORS] = {
  {S1_SetOutput, S1_SetInput, S1_SetVal, S1_GetVal},
  {S2_SetOutput, S2_SetInput, S2_SetVal, S2_GetVal},
  {S3_SetOutput, S3_SetInput, S3_SetVal, S3_GetVal},
  {S4_SetOutput, S4_SetInput, S4_SetVal, S4_GetVal},
  {S5_SetOutput, S5_SetInput, S5_SetVal, S5_GetVal},
  {S6_SetOutput, S6_SetInput, S6_SetVal, S6_GetVal},
#if REF_NOF_SENSORS>=7
  {S7_SetOutput, S7_SetInput, S7_SetVal, S7_GetVal},
#endif
#if REF_NOF_SENSORS>=8
  {S8_SetOutput, S8_SetInput, S8_SetVal, S8_GetVal},
#endif
};

static void IR_on(bool on) {
  if (on) {
    LED_IR_On();
  } else {
    LED_IR_Off();
  }
}

static void REF_MeasureRaw(SensorTimeType raw[REF_NOF_SENSORS]) {
  uint8_t cnt; /* number of sensor */
  uint8_t i;
  TMOUT1_CounterHandle timeout;

  FRTOS1_xSemaphoreTake(mutexHandle, portMAX_DELAY);
  if (ledON) {
    IR_on(TRUE); /* IR LED's on */
    WAIT1_Waitus(200);
  }
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetOutput(); /* turn I/O line as output */
    SensorFctArray[i].SetVal(); /* put high */
    raw[i] = MAX_SENSOR_VALUE;
  }
  WAIT1_Waitus(50); /* give at least 10 us to charge the capacitor */
  timeout = TMOUT1_GetCounter(REF_SENSOR_TIMEOUT_MS/TMOUT1_TICK_PERIOD_MS); /* set up timeout counter */
#if 0
  FRTOS1_vTaskSuspendAll();
#else
  //FRTOS1_vTaskPrioritySet(NULL, FRTOS1_uxTaskPriorityGet(NULL)+2); /* prio above other tasks */
#endif
  (void)RefCnt_ResetCounter(timerHandle); /* reset timer counter */
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetInput(); /* turn I/O line as input */
  }
  do {
    cnt = 0;
    if (TMOUT1_CounterExpired(timeout)) {
      break; /* get out of while loop */
    }
    for(i=0;i<REF_NOF_SENSORS;i++) {
      if (raw[i]==MAX_SENSOR_VALUE) { /* not measured yet? */
        if (SensorFctArray[i].GetVal()==0) {
          raw[i] = RefCnt_GetCounterValue(timerHandle);
        }
      } else { /* have value */
        cnt++;
      }
    }
  } while(cnt!=REF_NOF_SENSORS);
  TMOUT1_LeaveCounter(timeout);
#if 0
  FRTOS1_xTaskResumeAll();
#else
  //FRTOS1_vTaskPrioritySet(NULL, FRTOS1_uxTaskPriorityGet(NULL)-2); /* back to normal */
#endif
  if (ledON) {
    IR_on(FALSE); /* IR LED's off */
    //WAIT1_Waitus(200);
  }
  FRTOS1_xSemaphoreGive(mutexHandle);
}

void REF_CalibrateMinMax(SensorTimeType min[REF_NOF_SENSORS], SensorTimeType max[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  int i;
  
  REF_MeasureRaw(raw);
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (raw[i] < min[i]) {
      min[i] = raw[i];
    }
    if (raw[i]> max[i]) {
      max[i] = raw[i];
    }
  }
}

static void ReadCalibrated(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  int i;
  int32_t x, denominator;
  
  REF_MeasureRaw(raw);
  if (!isCalibrated) {
    return;
  }
  for(i=0;i<REF_NOF_SENSORS;i++) {
    x = 0;
    denominator = SensorMax[i]-SensorMin[i];
    if (denominator!=0) {
      x = (((int32_t)SensorRaw[i]-SensorMin[i])*1000)/denominator;
    }
    if (x<0) {
      x = 0;
    } else if (x>1000) {
      x = 1000;
    }
    calib[i] = x;
  }
}

/*
 * Operates the same as read calibrated, but also returns an
 * estimated position of the robot with respect to a line. The
 * estimate is made using a weighted average of the sensor indices
 * multiplied by 1000, so that a return value of 1000 indicates that
 * the line is directly below sensor 0, a return value of 2000
 * indicates that the line is directly below sensor 1, 2000
 * indicates that it's below sensor 2000, etc. Intermediate
 * values indicate that the line is between two sensors. The
 * formula is:
 *
 * 1000*value0 + 2000*value1 + 3000*value2 + ...
 * --------------------------------------------
 * value0 + value1 + value2 + ...
 *
 * By default, this function assumes a dark line (high values)
 * surrounded by white (low values). If your line is light on
 * black, set the optional second argument white_line to true. In
 * this case, each sensor value will be replaced by (1000-value)
 * before the averaging.
 */
#define RETURN_LAST_VALUE  0
static int ReadLine(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS], bool white_line, int startIdx, int endIdx) {
  unsigned char i;
  unsigned long avg; /* this is for the weighted total, which is long */
  /* before division */
  unsigned int sum; /* this is for the denominator which is <= 64000 */
  unsigned int mul; /* multiplication factor, 0, 1000, 2000, 3000 ... */
  int value;
#if RETURN_LAST_VALUE  
  bool on_line = FALSE;
  static int last_value=0; /* assume initially that the line is left. */
#endif
  
  avg = 0;
  sum = 0;
  mul = (startIdx+1)*1000;
  for(i=startIdx;i<=endIdx;i++) {
    value = calib[i];
    if(white_line) {
      value = 1000-value;
    }
    /* only average in values that are above a noise threshold */
    if(value > REF_MIN_NOISE_VAL) {
      avg += ((long)value) * mul;
      sum += value;
    }
    mul += 1000;
  }
#if RETURN_LAST_VALUE
  /* keep track of whether we see the line at all */
  if(value > REF_MIN_LINE_VAL) {
    on_line = TRUE;
  }
  if(!on_line) { /* If it last read to the left of center, return 0. */
    if(last_value < endIdx*1000/2) {
      return 0;
    } else { /* If it last read to the right of center, return the max. */
      return endIdx*1000;
    }
  }
  last_value = avg/sum;
  return last_value;
#else
  return avg/sum;
#endif
}

unsigned char *REF_LineKindStr(REF_LineKind line) {
  switch(line) {
  case REF_LINE_NONE:
    return (unsigned char *)"NONE";
  case REF_LINE_STRAIGHT:
    return (unsigned char *)"STRAIGHT";
  case REF_LINE_LEFT:
    return (unsigned char *)"LEFT";
  case REF_LINE_RIGHT:
    return (unsigned char *)"RIGHT";
  case REF_LINE_FULL:
    return (unsigned char *)"FULL";
  case REF_LINE_AIR:
    return (unsigned char *)"AIR";
  default:
    return (unsigned char *)"unknown";
  } /* switch */
}

REF_LineKind REF_GetLineKind(void) {
  return refLineKind;
}

static bool SensorsSaturated(void) {
#if 0
  int i, cnt;
  
  /* check if robot is in the air or does see something */
  cnt = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (SensorRaw[i]==MAX_SENSOR_VALUE) { /* sensor not seeing anything? */
      cnt++;
    }
  }
  return (cnt==REF_NOF_SENSORS); /* all sensors see raw max value: not on the ground? */
#else
  return FALSE;
#endif
}

static REF_LineKind ReadLineKind(SensorTimeType val[REF_NOF_SENSORS]) {
  uint32_t sum, sumLeft, sumRight;
  int i;
  
  /* check if robot is in the air or does see something */
  if (SensorsSaturated()) {
    return REF_LINE_AIR;
  }
  /* check the line type */
  sum = 0; sumLeft = 0; sumRight = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (val[i]>REF_MIN_LINE_VAL) { /* count only line values */
      sum += val[i];
      if (i<REF_NOF_SENSORS/2) {
        sumRight += val[i];
      } else {
        sumLeft += val[i];
      }
    }
  }
  
  #define MIN_LEFT_RIGHT_SUM   ((REF_NOF_SENSORS*1000)/3) /* third of the sensors */
  
  if (sumLeft>=MIN_LEFT_RIGHT_SUM && sumRight<MIN_LEFT_RIGHT_SUM) {
    return REF_LINE_LEFT;
  } else if (sumRight>=MIN_LEFT_RIGHT_SUM && sumLeft<MIN_LEFT_RIGHT_SUM) {
    return REF_LINE_RIGHT;
  } else if (sumRight>=MIN_LEFT_RIGHT_SUM && sumLeft>=MIN_LEFT_RIGHT_SUM) {
    return REF_LINE_FULL;
  } else if (sumRight==0 && sumLeft==0 && sum == 0) {
    return REF_LINE_NONE;
  } else { 
    return REF_LINE_STRAIGHT;
  }
}

static uint16_t REF_nofHistory = 0;

static void StoreHistory(SensorTimeType val[REF_NOF_SENSORS]) {
  uint8_t i;
  
  for(i=0; i<REF_NOF_SENSORS; i++) {
    if (val[i]>=REF_MIN_LINE_VAL) { /* only count line values */
      SensorHistory[i] += val[i];
      if (SensorHistory[i] > 1000) { /* cap it */
        SensorHistory[i] = 1000;
      }
    }
  }
  REF_nofHistory++;
}

void REF_DumpHistory(void) {
  int i;
  unsigned char buf[16];
  
  CLS1_SendStr((unsigned char*)"history: #", CLS1_GetStdio()->stdOut);
  CLS1_SendNum16u(REF_nofHistory, CLS1_GetStdio()->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    CLS1_SendStr((unsigned char*)" 0x", CLS1_GetStdio()->stdOut);
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorHistory[i]);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
}

void REF_SampleHistory(void) {
  StoreHistory(SensorCalibrated);
}

void REF_Measure(void) {
  ReadCalibrated(SensorCalibrated, SensorRaw);
  REF_SampleHistory();
  refCenterLineVal = ReadLine(SensorCalibrated, SensorRaw, FALSE, 0, REF_NOF_SENSORS-1);
  if (isCalibrated) {
    refLineKind = ReadLineKind(SensorCalibrated);
  }
}

REF_LineKind REF_HistoryLineKind(void) {
  int i, cnt, cntLeft, cntRight;
  
  cnt = cntLeft = cntRight = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (SensorHistory[i]>REF_MIN_LINE_VAL) { /* count only line values */
      cnt++;
      if (i<REF_NOF_SENSORS/2) {
        cntRight++;
      } else {
        cntLeft++;
      }
    }
  }
  if (cnt==0) {
    return REF_LINE_NONE;
  } else if (cnt==REF_NOF_SENSORS) {
    return REF_LINE_FULL;
  } else if (cntLeft>cntRight) {
    return REF_LINE_LEFT;
  } else { /* must be cntRight>cntLeft */
    return REF_LINE_RIGHT;
  }
}

void REF_ClearHistory(void) {
  int i;
  
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorHistory[i] = 0;
  }
  REF_nofHistory = 0;
}

void REF_InitSensorValues(void) {
  int i;
  
  REF_ClearHistory();
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorRaw[i] = 0;
    SensorMin[i] = MAX_SENSOR_VALUE;
    SensorMax[i] = 0;
    SensorCalibrated[i] = 0;
  }
  isCalibrated = FALSE;
}

void REF_Calibrate(bool start) {
  if (start) {
    isCalibrated = FALSE;
    REF_InitSensorValues();
    doMinMaxCalibration = TRUE;
    CLS1_SendStr((unsigned char*)"start calibration...\r\n", CLS1_GetStdio()->stdOut);
  } else {
    doMinMaxCalibration = FALSE;
    isCalibrated = TRUE;
    CLS1_SendStr((unsigned char*)"calibration stopped.\r\n", CLS1_GetStdio()->stdOut);
  }
}

bool REF_IsCalibrating(void) {
  return doMinMaxCalibration;
}

bool REF_CanUseSensor(void) {
  return !doMinMaxCalibration && isCalibrated;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"reflectance", (unsigned char*)"Group of Reflectance commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  calibrate (on|off)", (unsigned char*)"Calibrate while moving sensor over line\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  led (on|off)", (unsigned char*)"Uses LED or not\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[24];
  int i;

  CLS1_SendStatusStr((unsigned char*)"reflectance", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  IR led on", ledON?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  calibrating", doMinMaxCalibration?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  calibrated", isCalibrated?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), REF_MIN_NOISE_VAL);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  min noise", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), REF_MIN_LINE_VAL);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  min line", buf, io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  raw val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorRaw[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  min val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorMin[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  max val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorMax[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  calib val", (unsigned char*)"", io->stdOut);
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibrated[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  line val", (unsigned char*)"", io->stdOut);
  buf[0] = '\0'; UTIL1_strcatNum16s(buf, sizeof(buf), refCenterLineVal);
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
      CLS1_SendStatusStr((unsigned char*)"  history", (unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorHistory[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  line kind", REF_LineKindStr(refLineKind), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

byte REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "reflectance help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "reflectance status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "reflectance calibrate on")==0) {
    APP_StateStartCalibrate();
    *handled = TRUE;
    return ERR_OK;  
  } else if (UTIL1_strcmp((char*)cmd, "reflectance calibrate off")==0) {
    APP_StateStopCalibrate();
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "reflectance led on")==0) {
    ledON = TRUE;
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "reflectance led off")==0) {
    ledON = FALSE;
    *handled = TRUE;
    return ERR_OK;
  }
  return ERR_OK;
}

uint16_t REF_GetLineValue(bool *onLine) {
  *onLine = refCenterLineVal>0 && refCenterLineVal<REF_MAX_LINE_VALUE;
  return refCenterLineVal;
}

static portTASK_FUNCTION(ReflTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    if (doMinMaxCalibration) {
      REF_CalibrateMinMax(SensorMin, SensorMax, SensorRaw);
#if PL_HAS_BUZZER
      BUZ_Beep(300, 50);
#endif
    } else {
      REF_Measure();
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void REF_Init(void) {
  refLineKind = REF_LINE_NONE;
  refCenterLineVal = 0;
  mutexHandle = FRTOS1_xSemaphoreCreateMutex();
  if (mutexHandle==NULL) {
    for(;;);
  }
  timerHandle = RefCnt_Init(NULL);
  REF_InitSensorValues();
  if (FRTOS1_xTaskCreate(ReflTask, (signed portCHAR *)"Refl", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
