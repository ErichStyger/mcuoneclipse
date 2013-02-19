/*
 * Reflectance.c
 *
 *  Created on: Feb 5, 2013
 *      Author: Erich Styger
 */
#include "Reflectance.h"
#include "LED_IR.h"
#include "WAIT1.h"
#include "RefCnt.h" /* timer counter to measure reflectance */
#include "IR_A0.h"
#include "IR_A2.h"
#include "IR_A3.h"
#include "IR_D4.h"
#include "IR_D5.h"
#include "IR_A11.h"
#include "UTIL1.h"
#include "TMOUT1.h"
#include "FRTOS1.h"
#include "Buzzer.h"

#define NOF_SENSORS 6
static LDD_TDeviceData *timerHandle;
static xQueueHandle mutexHandle;
static bool doMinMaxCalibration = FALSE;

typedef struct {
  void (*SetOutput)(void);
  void (*SetInput)(void);
  void (*SetVal)(void);
  bool (*GetVal)(void);
} SensorFctType;

typedef uint16_t SensorTimeType;
#define MAX_SENSOR_VALUE ((SensorTimeType)-1)

static SensorTimeType SensorRaw[NOF_SENSORS]; 
static SensorTimeType SensorWhite[NOF_SENSORS]; 
static SensorTimeType SensorBlack[NOF_SENSORS]; 
static SensorTimeType SensorCalibrated[NOF_SENSORS]; /* 0 means white value, 1000 means black value */
static bool isCalibrated = FALSE;
static bool ledON = TRUE;
static int16_t refLine=0; /* 0 means no line, >0 means line is below sensor 0, 1000 below sensor 1 and so on */

/* functions as wrapper around macro. Number 0 is on the right side */
static void S0_SetOutput(void) { IR_D5_SetOutput(); }
static void S0_SetInput(void) { IR_D5_SetInput(); }
static void S0_SetVal(void) { IR_D5_SetVal(); }
static bool S0_GetVal(void) { return IR_D5_GetVal(); }

static void S1_SetOutput(void) { IR_A2_SetOutput(); }
static void S1_SetInput(void) { IR_A2_SetInput(); }
static void S1_SetVal(void) { IR_A2_SetVal(); }
static bool S1_GetVal(void) { return IR_A2_GetVal(); }

static void S2_SetOutput(void) { IR_A0_SetOutput(); }
static void S2_SetInput(void) { IR_A0_SetInput(); }
static void S2_SetVal(void) { IR_A0_SetVal(); }
static bool S2_GetVal(void) { return IR_A0_GetVal(); }

static void S3_SetOutput(void) { IR_A11_SetOutput(); }
static void S3_SetInput(void) { IR_A11_SetInput(); }
static void S3_SetVal(void) { IR_A11_SetVal(); }
static bool S3_GetVal(void) { return IR_A11_GetVal(); }

static void S4_SetOutput(void) { IR_A3_SetOutput(); }
static void S4_SetInput(void) { IR_A3_SetInput(); }
static void S4_SetVal(void) { IR_A3_SetVal(); }
static bool S4_GetVal(void) { return IR_A3_GetVal(); }

static void S5_SetOutput(void) { IR_D4_SetOutput(); }
static void S5_SetInput(void) { IR_D4_SetInput(); }
static void S5_SetVal(void) { IR_D4_SetVal(); }
static bool S5_GetVal(void) { return IR_D4_GetVal(); }

static const SensorFctType SensorFctArray[NOF_SENSORS] = {
  {S0_SetOutput, S0_SetInput, S0_SetVal, S0_GetVal},
  {S1_SetOutput, S1_SetInput, S1_SetVal, S1_GetVal},
  {S2_SetOutput, S2_SetInput, S2_SetVal, S2_GetVal},
  {S3_SetOutput, S3_SetInput, S3_SetVal, S3_GetVal},
  {S4_SetOutput, S4_SetInput, S4_SetVal, S4_GetVal},
  {S5_SetOutput, S5_SetInput, S5_SetVal, S5_GetVal},
};

static void REF_MeasureRaw(SensorTimeType raw[NOF_SENSORS]) {
  uint8_t cnt; /* number of sensor */
  uint8_t i;
  TMOUT1_CounterHandle timeout;

  FRTOS1_xSemaphoreTake(mutexHandle, portMAX_DELAY);
  if (ledON) {
    LED_IR_On(); /* IR LED's on */
    WAIT1_Waitus(200);
  }
  for(i=0;i<NOF_SENSORS;i++) {
    SensorFctArray[i].SetOutput(); /* turn I/O line as output */
    SensorFctArray[i].SetVal(); /* put high */
    raw[i] = MAX_SENSOR_VALUE;
  }
  WAIT1_Waitus(20); /* give at least 10 us to charge the capacitor */
  timeout = TMOUT1_GetCounter(20/TMOUT1_TICK_PERIOD_MS); /* set up timeout counter */
  FRTOS1_vTaskSuspendAll();
  
  (void)RefCnt_ResetCounter(timerHandle); /* reset timer counter */
  for(i=0;i<NOF_SENSORS;i++) {
    SensorFctArray[i].SetInput(); /* turn I/O line as input */
  }
  do {
    cnt = 0;
    if (TMOUT1_CounterExpired(timeout)) {
      break; /* get out of wile loop */
    }
    for(i=0;i<NOF_SENSORS;i++) {
      if (raw[i]==MAX_SENSOR_VALUE) { /* not measured yet? */
        if (SensorFctArray[i].GetVal()==0) {
          raw[i] = RefCnt_GetCounterValue(timerHandle);
        }
      } else { /* have value */
        cnt++;
      }
    }
  } while(cnt!=NOF_SENSORS);
  TMOUT1_LeaveCounter(timeout);
  FRTOS1_xTaskResumeAll();
  if (ledON) {
    LED_IR_Off(); /* IR LED's off */
    WAIT1_Waitus(200);
  }
  FRTOS1_xSemaphoreGive(mutexHandle);
}

void REF_CalibrateAverage(SensorTimeType values[NOF_SENSORS], SensorTimeType raw[NOF_SENSORS]) {
  uint32_t sum[NOF_SENSORS];
  #define CALIB_NOF_MEASUREMENT 8
  int i, j;
  
  for(i=0;i<NOF_SENSORS;i++) {
    sum[i] = 0; /* init */
  }
  for(j=0;j<CALIB_NOF_MEASUREMENT;j++) {
    REF_MeasureRaw(raw);
    for(i=0;i<NOF_SENSORS;i++) {
      sum[i]+=raw[i];
    }
  }
  /* build average */
  for(i=0;i<NOF_SENSORS;i++) {
    values[i] = sum[i]/CALIB_NOF_MEASUREMENT;
  }
}

void REF_CalibrateMinMax(SensorTimeType min[NOF_SENSORS], SensorTimeType max[NOF_SENSORS], SensorTimeType raw[NOF_SENSORS]) {
  int i;
  
  REF_MeasureRaw(raw);
  for(i=0;i<NOF_SENSORS;i++) {
    if (raw[i] < min[i]) {
      min[i] = raw[i];
    }
    if (raw[i]> max[i]) {
      max[i] = raw[i];
    }
  }
}

static void ReadCalibrated(SensorTimeType calib[NOF_SENSORS], SensorTimeType raw[NOF_SENSORS]) {
  int i;
  int32_t x, denominator;
  
  REF_MeasureRaw(raw);
  if (!isCalibrated) {
    return;
  }
  for(i=0;i<NOF_SENSORS;i++) {
    denominator = SensorBlack[i]-SensorWhite[i];
    if (denominator!=0) {
      x = (((int32_t)SensorRaw[i]-SensorWhite[i])*1000)/denominator;
    }
    if (x<0) {
      x = 0;
    } else if (x>1000) {
      x = 1000;
    }
    calib[i] = x;
  }
}

// Operates the same as read calibrated, but also returns an
// estimated position of the robot with respect to a line. The
// estimate is made using a weighted average of the sensor indices
// multiplied by 1000, so that a return value of 0 indicates that
// the line is directly below sensor 0, a return value of 1000
// indicates that the line is directly below sensor 1, 2000
// indicates that it's below sensor 2000, etc. Intermediate
// values indicate that the line is between two sensors. The
// formula is:
//
// 0*value0 + 1000*value1 + 2000*value2 + ...
// --------------------------------------------
// value0 + value1 + value2 + ...
//
// By default, this function assumes a dark line (high values)
// surrounded by white (low values). If your line is light on
// black, set the optional second argument white_line to true. In
// this case, each sensor value will be replaced by (1000-value)
// before the averaging.
static int ReadLine(SensorTimeType calib[NOF_SENSORS], SensorTimeType raw[NOF_SENSORS], bool white_line) {
  unsigned char i;
  bool on_line = FALSE;
  unsigned long avg; // this is for the weighted total, which is long
  // before division
  unsigned int sum; // this is for the denominator which is <= 64000
  static int last_value=0; // assume initially that the line is left.
#define LINE_MIN_VAL 0x50  /* 200 */ /* minimum value indicating a line */
#define MIN_NOISE    16  /* 50 */
  
  ReadCalibrated(calib, raw);
  avg = 0;
  sum = 0;
  for(i=0;i<NOF_SENSORS;i++) {
    int value = calib[i];
    if(white_line) {
      value = 1000-value;
    }
    /* keep track of whether we see the line at all */
    if(value > LINE_MIN_VAL) {
      on_line = TRUE;
    }
    /* only average in values that are above a noise threshold */
    if(value > 50) {
      avg += (long)(value) * (i * 1000);
      sum += value;
    }
  }
  if(!on_line) { /* If it last read to the left of center, return 0. */
    if(last_value < (NOF_SENSORS-1)*1000/2) {
      return 0;
    } else { /* If it last read to the right of center, return the max. */
      return (NOF_SENSORS-1)*1000;
    }
  }
  last_value = avg/sum;
  return last_value;
}

void REF_Measure(void) {
  refLine = ReadLine(SensorCalibrated, SensorRaw, FALSE);
}

void InitSensorValues(void) {
  int i;
  
  for(i=0;i<NOF_SENSORS;i++) {
    SensorRaw[i] = 0;
    SensorWhite[i] = MAX_SENSOR_VALUE;
    SensorBlack[i] = 0;
    SensorCalibrated[i] = 0;
  }
  isCalibrated = FALSE;
}

void REF_Calibrate(bool on) {
  if (on) {
    InitSensorValues();
    doMinMaxCalibration = TRUE;
  } else {
    doMinMaxCalibration = FALSE;
    isCalibrated = TRUE;
  }
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
  CLS1_SendStatusStr((unsigned char*)"  led", ledON?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  calibrated", isCalibrated?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  raw", (unsigned char*)"", io->stdOut);
  for (i=0;i<NOF_SENSORS;i++) {
    CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorRaw[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  white", (unsigned char*)"", io->stdOut);
  for (i=0;i<NOF_SENSORS;i++) {
    CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorWhite[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  black", (unsigned char*)"", io->stdOut);
  for (i=0;i<NOF_SENSORS;i++) {
    CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorBlack[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  calibrated", (unsigned char*)"", io->stdOut);
  for (i=0;i<NOF_SENSORS;i++) {
    CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibrated[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  line", (unsigned char*)"", io->stdOut);
  buf[0] = '\0'; UTIL1_strcatNum16s(buf, sizeof(buf), refLine);
  CLS1_SendStr(buf, io->stdOut);
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

uint16_t REF_GetLine(bool *onLine) {
  *onLine = refLine>0 && refLine<5000;
  return refLine;
}

static portTASK_FUNCTION(ReflTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    if (doMinMaxCalibration) {
      REF_CalibrateMinMax(SensorWhite, SensorBlack, SensorRaw);
      BUZ_Beep(300, 50);
    } else {
      REF_Measure();
    }
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  }
}

void REF_Init(void) {
  mutexHandle = FRTOS1_xSemaphoreCreateMutex();
  if (mutexHandle==NULL) {
    for(;;);
  }
  timerHandle = RefCnt_Init(NULL);
  InitSensorValues();
  if (FRTOS1_xTaskCreate(ReflTask, (signed portCHAR *)"Refl", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
