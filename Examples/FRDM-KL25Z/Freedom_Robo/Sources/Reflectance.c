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
#include "IR7.h"
#include "IR8.h"
#include "UTIL1.h"
#include "TMOUT1.h"
#include "FRTOS1.h"
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif

static LDD_TDeviceData *timerHandle;
static xQueueHandle mutexHandle;
static bool doMinMaxCalibration = FALSE;
#if PL_IS_ZUMO_ROBOT
  #define REF_MIN_LINE_VAL   0x50  /* minimum value indicating a line */
  #define REF_MIN_NOISE_VAL    50   /* values below this are not added to the weighted sum */
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
#define MAX_SENSOR_VALUE ((SensorTimeType)-1)

static SensorTimeType SensorRaw[REF_NOF_SENSORS]; 
static SensorTimeType SensorMin[REF_NOF_SENSORS]; 
static SensorTimeType SensorMax[REF_NOF_SENSORS]; 
static SensorTimeType SensorCalibrated[REF_NOF_SENSORS]; /* 0 means white/min value, 1000 means black/max value */
static bool isCalibrated = FALSE;
static bool ledON = TRUE;
static int16_t refLineVal=0; /* 0 means no line, >0 means line is below sensor 0, 1000 below sensor 1 and so on */
static REF_LineKind refLineKind = REF_LINE_NONE;

/* functions as wrapper around macro. Number 0 is on the right side */
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

static void S7_SetOutput(void) { IR7_SetOutput(); }
static void S7_SetInput(void) { IR7_SetInput(); }
static void S7_SetVal(void) { IR7_SetVal(); }
static bool S7_GetVal(void) { return IR7_GetVal(); }

static void S8_SetOutput(void) { IR8_SetOutput(); }
static void S8_SetInput(void) { IR8_SetInput(); }
static void S8_SetVal(void) { IR8_SetVal(); }
static bool S8_GetVal(void) { return IR8_GetVal(); }

static const SensorFctType SensorFctArray[REF_NOF_SENSORS] = {
  {S1_SetOutput, S1_SetInput, S1_SetVal, S1_GetVal},
  {S2_SetOutput, S2_SetInput, S2_SetVal, S2_GetVal},
  {S3_SetOutput, S3_SetInput, S3_SetVal, S3_GetVal},
  {S4_SetOutput, S4_SetInput, S4_SetVal, S4_GetVal},
  {S5_SetOutput, S5_SetInput, S5_SetVal, S5_GetVal},
  {S6_SetOutput, S6_SetInput, S6_SetVal, S6_GetVal},
  {S7_SetOutput, S7_SetInput, S7_SetVal, S7_GetVal},
  {S8_SetOutput, S8_SetInput, S8_SetVal, S8_GetVal},
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
  timeout = TMOUT1_GetCounter(20/TMOUT1_TICK_PERIOD_MS); /* set up timeout counter */
  FRTOS1_vTaskSuspendAll();
  
  (void)RefCnt_ResetCounter(timerHandle); /* reset timer counter */
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetInput(); /* turn I/O line as input */
  }
  do {
    cnt = 0;
    if (TMOUT1_CounterExpired(timeout)) {
      break; /* get out of wile loop */
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
  FRTOS1_xTaskResumeAll();
  if (ledON) {
    IR_on(FALSE); /* IR LED's off */
    WAIT1_Waitus(200);
  }
  FRTOS1_xSemaphoreGive(mutexHandle);
}

void REF_CalibrateAverage(SensorTimeType values[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  uint32_t sum[REF_NOF_SENSORS];
  #define CALIB_NOF_MEASUREMENT 8
  int i, j;
  
  for(i=0;i<REF_NOF_SENSORS;i++) {
    sum[i] = 0; /* init */
  }
  for(j=0;j<CALIB_NOF_MEASUREMENT;j++) {
    REF_MeasureRaw(raw);
    for(i=0;i<REF_NOF_SENSORS;i++) {
      sum[i]+=raw[i];
    }
  }
  /* build average */
  for(i=0;i<REF_NOF_SENSORS;i++) {
    values[i] = sum[i]/CALIB_NOF_MEASUREMENT;
  }
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
 * multiplied by 1000, so that a return value of 0 indicates that
 * the line is directly below sensor 0, a return value of 1000
 * indicates that the line is directly below sensor 1, 2000
 * indicates that it's below sensor 2000, etc. Intermediate
 * values indicate that the line is between two sensors. The
 * formula is:
 *
 * 0*value0 + 1000*value1 + 2000*value2 + ...
 * --------------------------------------------
 * value0 + value1 + value2 + ...
 *
 * By default, this function assumes a dark line (high values)
 * surrounded by white (low values). If your line is light on
 * black, set the optional second argument white_line to true. In
 * this case, each sensor value will be replaced by (1000-value)
 * before the averaging.
 */
static int ReadLine(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS], bool white_line) {
  unsigned char i;
  bool on_line = FALSE;
  unsigned long avg; /* this is for the weighted total, which is long */
  /* before division */
  unsigned int sum; /* this is for the denominator which is <= 64000 */
  static int last_value=0; /* assume initially that the line is left. */
  
  ReadCalibrated(calib, raw);
  avg = 0;
  sum = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    int value = calib[i];
    if(white_line) {
      value = 1000-value;
    }
    /* keep track of whether we see the line at all */
    if(value > REF_MIN_LINE_VAL) {
      on_line = TRUE;
    }
    /* only average in values that are above a noise threshold */
    if(value > REF_MIN_NOISE_VAL) {
      avg += (long)(value) * (i * 1000);
      sum += value;
    }
  }
  if(!on_line) { /* If it last read to the left of center, return 0. */
    if(last_value < (REF_NOF_SENSORS-1)*1000/2) {
      return 0;
    } else { /* If it last read to the right of center, return the max. */
      return (REF_NOF_SENSORS-1)*1000;
    }
  }
  last_value = avg/sum;
  return last_value;
}

unsigned char *LF_LineKindStr(REF_LineKind line) {
  switch(line) {
  case REF_LINE_NONE:
    return (unsigned char *)"NONE";
  case REF_LINE_FORWARD:
    return (unsigned char *)"FORWARD";
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

static void ReadLineKind(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  uint32_t sum, sumLeft, sumRight;
  int i, cnt;
  
  /* check if robot is in the air or does see something */
  cnt = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (raw[i]==MAX_SENSOR_VALUE) { /* count only values above noise */
      cnt++;
    }
  }
  if (cnt==REF_NOF_SENSORS) { /* all sensors see raw max value: not on the ground? */
    refLineKind = REF_LINE_AIR;
    return;
  }
  /* check the line type */
  sum = 0; sumLeft = 0; sumRight = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (calib[i]>REF_MIN_LINE_VAL) { /* count only values above noise */
      sum += 1000;
      if (i<REF_NOF_SENSORS/2) {
        sumRight += 1000;
      } else {
        sumLeft += 1000;
      }
    }
  }
  
  #define MIN_LEFT_RIGHT_SUM   ((REF_NOF_SENSORS*1000)/2) /* half of the sensors */
  
  if (sumLeft>=MIN_LEFT_RIGHT_SUM && sumRight<MIN_LEFT_RIGHT_SUM) {
    refLineKind = REF_LINE_LEFT;
  } else if (sumRight>=MIN_LEFT_RIGHT_SUM && sumLeft<MIN_LEFT_RIGHT_SUM) {
    refLineKind = REF_LINE_RIGHT;
  } else if (sumRight>=MIN_LEFT_RIGHT_SUM && sumLeft>=MIN_LEFT_RIGHT_SUM) {
    refLineKind = REF_LINE_FULL;
  } else if (sum>=1000) {
    refLineKind = REF_LINE_FORWARD;
  } else { /* default */
    refLineKind = REF_LINE_NONE;
  }
}

void REF_Measure(void) {
  refLineVal = ReadLine(SensorCalibrated, SensorRaw, FALSE);
  if (isCalibrated) {
    ReadLineKind(SensorCalibrated, SensorRaw);
  }
}

void InitSensorValues(void) {
  int i;
  
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
    InitSensorValues();
    doMinMaxCalibration = TRUE;
  } else {
    doMinMaxCalibration = FALSE;
    isCalibrated = TRUE;
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
  CLS1_SendHelpStr((unsigned char*)"  calibrate (white|black)", (unsigned char*)"Calibrate for all white or black values\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  calibrate line (on|off)", (unsigned char*)"Calibrate while moving sensor over line\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  led (on|off)", (unsigned char*)"Uses LED or not\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[15];
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
  buf[0] = '\0'; UTIL1_strcatNum16s(buf, sizeof(buf), refLineVal);
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  line kind", LF_LineKindStr(refLineKind), io->stdOut);
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
  } else if (UTIL1_strcmp((char*)cmd, "reflectance calibrate line on")==0) {
    REF_Calibrate(TRUE);
    *handled = TRUE;
    return ERR_OK;  
  } else if (UTIL1_strcmp((char*)cmd, "reflectance calibrate line off")==0) {
    REF_Calibrate(FALSE);
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
  *onLine = refLineVal>0 && refLineVal<REF_MAX_LINE_VALUE;
  return refLineVal;
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
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  }
}

void REF_Init(void) {
  refLineKind = REF_LINE_NONE;
  refLineVal = 0;
  mutexHandle = FRTOS1_xSemaphoreCreateMutex();
  if (mutexHandle==NULL) {
    for(;;);
  }
  timerHandle = RefCnt_Init(NULL);
  InitSensorValues();
  if (FRTOS1_xTaskCreate(ReflTask, (signed portCHAR *)"Refl", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
