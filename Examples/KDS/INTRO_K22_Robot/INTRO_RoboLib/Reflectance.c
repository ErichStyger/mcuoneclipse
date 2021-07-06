/**
 * \file
 * \brief Reflectance sensor driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the bot front sensor.
 */
 
#include "Platform.h"
#if PL_HAS_LINE_SENSOR
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
#if PL_CONFIG_HAS_NVM_CONFIG
  #include "NVM_Config.h"
#endif
#include "Event.h"
#include "Shell.h"

typedef enum {
  REF_STATE_INIT,
  REF_STATE_NOT_CALIBRATED,
  REF_STATE_START_CALIBRATION,
  REF_STATE_CALIBRATING,
  REF_STATE_STOP_CALIBRATION,
  REF_STATE_SAVE_CALIBRATION,
  REF_STATE_READY
} RefStateType;

static volatile RefStateType refState = REF_STATE_INIT;

static LDD_TDeviceData *timerHandle;
static bool REF_IsEnabled = TRUE;

#define REF_USE_WHITE_LINE  0  /* if set to 1, then the robot is using a white (on black) line, otherwise a black (on white) line */

#define REF_START_STOP_CALIB      1 /* start/stop calibration commands */
#if REF_START_STOP_CALIB
  static SemaphoreHandle_t REF_StartStopSem = NULL;
#endif

#define REF_TIMEOUT_TICKS       ((RefCnt_CNT_INP_FREQ_U_0/1000)*REF_SENSOR_TIMEOUT_US)/1000 /* REF_SENSOR_TIMEOUT_US translated into timeout ticks */

typedef struct SensorFctType_ {
  void (*SetOutput)(void);
  void (*SetInput)(void);
  void (*SetVal)(void);
  bool (*GetVal)(void);
} SensorFctType;

typedef uint16_t SensorTimeType;
#define MAX_SENSOR_VALUE  ((SensorTimeType)-1)

/* type of NVM Configuration data (in FLASH) */
typedef struct SensorCalibT_ {
  SensorTimeType minVal[REF_NOF_SENSORS];
  SensorTimeType maxVal[REF_NOF_SENSORS];
} SensorCalibT;

static SensorCalibT *SensorCalibMinMaxPtr; /* pointer to calibrated data in FLASH, NULL if not calibrated */
static SensorCalibT *SensorCalibMinMaxTmpPtr=NULL; /* temporary calibration data */

static SensorTimeType SensorRaw[REF_NOF_SENSORS]; /* raw sensor values */
static SensorTimeType SensorCalibrated[REF_NOF_SENSORS]; /* 0 means white/min value, 1000 means black/max value */
static bool REF_LedOn = TRUE;
static int16_t refCenterLineVal=0; /* 0 means no line, >0 means line is below sensor 0, 1000 below sensor 1 and so on */
static REF_LineKind refLineKind = REF_LINE_NONE;
static uint16_t refLineWidth = 0;

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

void REF_GetSensorValues(uint16_t *values, int nofValues) {
  int i;

  for(i=0;i<nofValues && i<REF_NOF_SENSORS;i++) {
    values[i] = SensorCalibrated[i];
  }
}

static void IR_on(bool on) {
  if (on) {
    LED_IR_On();
  } else {
    LED_IR_Off();
  }
}

/*!
 * \brief Measures the time until the sensor discharges
 * \param raw Array to store the raw values.
 * \return ERR_OVERFLOW if there is a timeout, ERR_OK otherwise
 */
static bool REF_MeasureRaw(SensorTimeType raw[REF_NOF_SENSORS], RefCnt_TValueType timeoutCntVal) {
  uint8_t cnt; /* number of sensor */
  uint8_t i;
  bool isTimeout = FALSE;
  RefCnt_TValueType timerVal;

  if (!REF_IsEnabled) {
    return ERR_DISABLED;
  }
  if (REF_LedOn) {
    IR_on(TRUE); /* IR LED's on */
    WAIT1_Waitus(200);
  }
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetOutput(); /* turn I/O line as output */
    SensorFctArray[i].SetVal(); /* put high */
    raw[i] = MAX_SENSOR_VALUE;
  }
  WAIT1_Waitus(50); /* give at least 10 us to charge the capacitor */
  taskENTER_CRITICAL();
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetInput(); /* turn I/O line as input */
  }
  (void)RefCnt_ResetCounter(timerHandle); /* reset timer counter */
  do {
    cnt = 0;
    timerVal = RefCnt_GetCounterValue(timerHandle);
    if (timerVal>timeoutCntVal) {
      isTimeout = TRUE;
      break; /* get out of while loop */
    }
    for(i=0;i<REF_NOF_SENSORS;i++) {
      if (raw[i]==MAX_SENSOR_VALUE) { /* not measured yet? */
        if (SensorFctArray[i].GetVal()==0) {
          raw[i] = timerVal;
        }
      } else { /* have value */
        cnt++;
      }
    }
  } while(cnt!=REF_NOF_SENSORS);
  taskEXIT_CRITICAL();
  if (REF_LedOn) {
    IR_on(FALSE); /* IR LED's off */
  }
  if (isTimeout) {
    for(i=0;i<REF_NOF_SENSORS;i++) {
      if (raw[i]==MAX_SENSOR_VALUE) { /* not measured yet? */
        if (SensorCalibMinMaxPtr!=NULL) {
          raw[i] = SensorCalibMinMaxPtr->maxVal[i]; /* use calibrated max value */
        } else {
          raw[i] = timeoutCntVal; /* set to timeout value */
        }
      }
    } /* for */
    return ERR_OVERFLOW;
  } else {
    return ERR_OK;
  }
}

static void REF_CalibrateMinMax(SensorTimeType min[REF_NOF_SENSORS], SensorTimeType max[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  int i;

  if (REF_MeasureRaw(raw, REF_TIMEOUT_TICKS)==ERR_OK) { /* if timeout, do not count values */
    for(i=0;i<REF_NOF_SENSORS;i++) {
      if (raw[i] < min[i]) {
        min[i] = raw[i];
      }
      if (raw[i]> max[i]) {
        max[i] = raw[i];
      }
    }
  }
}

static void ReadCalibrated(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
  int i;
  int32_t x, denominator;
  RefCnt_TValueType max;
  
  max = 0; /* determine maximum timeout value */
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (SensorCalibMinMaxPtr->maxVal[i]>max) {
      max = SensorCalibMinMaxPtr->maxVal[i];
    }
  }
  if (max > REF_TIMEOUT_TICKS) { /* limit to timeout value */
    max = REF_TIMEOUT_TICKS;
  }
  (void)REF_MeasureRaw(raw, max);
  if (SensorCalibMinMaxPtr==NULL) { /* no calibration data? */
    return;
  }
  for(i=0;i<REF_NOF_SENSORS;i++) {
    x = 0;
    denominator = SensorCalibMinMaxPtr->maxVal[i]-SensorCalibMinMaxPtr->minVal[i];
    if (denominator!=0) {
      x = (((int32_t)raw[i]-SensorCalibMinMaxPtr->minVal[i])*1000)/denominator;
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
static int ReadLine(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS], bool white_line) {
  int i;
  unsigned long avg; /* this is for the weighted total, which is long */
  /* before division */
  unsigned int sum; /* this is for the denominator which is <= 64000 */
  unsigned int mul; /* multiplication factor, 0, 1000, 2000, 3000 ... */
  int value;
#if RETURN_LAST_VALUE  
  bool on_line = FALSE;
  static int last_value=0; /* assume initially that the line is left. */
#endif
  
  (void)raw; /* unused */
  avg = 0;
  sum = 0;
  mul = 1000;
#if REF_SENSOR1_IS_LEFT
  for(i=0;i<REF_NOF_SENSORS;i++) {
#else
  for(i=REF_NOF_SENSORS-1;i>=0;i--) {
#endif
    value = calib[i];
    if(white_line) {
      value = 1000-value;
    }
    /* only average in values that are above a noise threshold */
    if(value > REF_MIN_NOISE_VAL) {
      avg += ((long)value)*mul;
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
  if (sum>0) {
    return avg/sum;
  } else {
    return avg;
  }
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

REF_LineKind REF_GetLineKind(REF_LineKindMode mode) {
  if (mode==REF_LINE_KIND_MODE_ALL || mode==REF_LINE_KIND_MODE_MAZE || mode==REF_LINE_KIND_MODE_SUMO) {
    return refLineKind;
  } else if (mode==REF_LINE_KIND_MODE_LINE_FOLLOW) {
    switch(refLineKind) {
    case REF_LINE_NONE:
      return REF_LINE_NONE;

    case REF_LINE_LEFT:
    case REF_LINE_RIGHT:
    case REF_LINE_STRAIGHT:
      return REF_LINE_STRAIGHT;

    case REF_LINE_AIR:
    case REF_LINE_FULL:
      return REF_LINE_FULL;

    default:
      return REF_LINE_NONE;
    }
  }
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
  uint32_t sum, sumLeft, sumRight, outerLeft, outerRight, nofLines;
  int i;
  
  /* check if robot is in the air or does see something */
  if (SensorsSaturated()) {
    return REF_LINE_AIR;
  }
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (val[i]<REF_MIN_LINE_VAL) { /* smaller value? White seen! */
      break;
    }
  }
  if (i==REF_NOF_SENSORS) { /* all sensors see 'black' */
    return REF_LINE_FULL;
  }
  /* check the line type */
  sum = 0; sumLeft = 0; sumRight = 0; nofLines = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (val[i]>REF_MIN_LINE_VAL) { /* count only line values */
      nofLines++;
      sum += val[i];
      if (i<REF_NOF_SENSORS/2) {
#if REF_SENSOR1_IS_LEFT
        sumLeft += val[i];
#else
        sumRight += val[i];
#endif
      } else {
#if REF_SENSOR1_IS_LEFT
        sumRight += val[i];
#else
        sumLeft += val[i];
#endif
      }
    }
  }
#if REF_SENSOR1_IS_LEFT
  outerLeft = val[0];
  outerRight = val[REF_NOF_SENSORS-1];
#else
  outerLeft = val[REF_NOF_SENSORS-1];
  outerRight = val[0];
#endif
  
  #define MIN_LEFT_RIGHT_SUM   ((((REF_NOF_SENSORS)*2)/3)*REF_MIN_LINE_VAL) /* 2/3 of half the number of the sensors shall see a line */
  
  if (outerLeft<REF_MIN_LINE_VAL && outerRight<REF_MIN_LINE_VAL && nofLines>0) {
    /* both leftmost and rightmost sensors are seeing white, middle is seeing at least one black line */
    return REF_LINE_STRAIGHT; /* straight line forward */
  }

  if (outerLeft>=REF_MIN_LINE_VAL && outerRight<REF_MIN_LINE_VAL && sumLeft>MIN_LEFT_RIGHT_SUM && sumRight<MIN_LEFT_RIGHT_SUM) {
    return REF_LINE_LEFT; /* line going to the left side */
  } else if (outerLeft<REF_MIN_LINE_VAL && outerRight>=REF_MIN_LINE_VAL && sumRight>MIN_LEFT_RIGHT_SUM && sumLeft<MIN_LEFT_RIGHT_SUM) {
    return REF_LINE_RIGHT; /* line going to the right side */
  } else if (outerLeft>=REF_MIN_LINE_VAL && outerRight>=REF_MIN_LINE_VAL && sumRight>MIN_LEFT_RIGHT_SUM && sumLeft>MIN_LEFT_RIGHT_SUM) {
    return REF_LINE_FULL; /* full line */
  } else if (sumRight==0 && sumLeft==0 && sum == 0) {
    return REF_LINE_NONE; /* no line */
  } else { 
    return REF_LINE_STRAIGHT; /* straight line forward */
  }
}

uint16_t REF_LineWidth(void) {
  return refLineWidth;
}

static uint16_t CalculateRefLineWidth(SensorTimeType calib[REF_NOF_SENSORS]) {
  int32_t val;
  int i;

  val = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (calib[i]>=REF_MIN_NOISE_VAL) { /* sensor not seeing anything? */
      val += calib[i];
    }
  }
  return (uint16_t)val;
}

#if 0
static void Dump(void) {
  uint8_t buf[32];
  int i;

  if (SensorCalibMinMaxPtr!=NULL) { /* have calibration data */
    CLS1_SendStatusStr((unsigned char*)"  calib val", (unsigned char*)"", CLS1_GetStdio()->stdOut);
  #if REF_SENSOR1_IS_LEFT
    for (i=0;i<REF_NOF_SENSORS;i++) {
      if (i==0) {
  #else
    for (i=REF_NOF_SENSORS-1;i>=0;i--) {
      if (i==REF_NOF_SENSORS-1) {
  #endif
        CLS1_SendStr((unsigned char*)"0x", CLS1_GetStdio()->stdOut);
      } else {
        CLS1_SendStr((unsigned char*)" 0x", CLS1_GetStdio()->stdOut);
      }
      buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibrated[i]);
      CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    }
    CLS1_SendStr((unsigned char*)"\r\n", CLS1_GetStdio()->stdOut);
  }
}
#endif

static void REF_Measure(void) {
  ReadCalibrated(SensorCalibrated, SensorRaw);
  refCenterLineVal = ReadLine(SensorCalibrated, SensorRaw, REF_USE_WHITE_LINE);
  refLineWidth = CalculateRefLineWidth(SensorCalibrated);
  if (refState==REF_STATE_READY) {
    refLineKind = ReadLineKind(SensorCalibrated);
#if 0
    if (refLineKind!=REF_LINE_STRAIGHT) {
      Dump(); /* \todo */
    }
#endif
  }
}

#if REF_START_STOP_CALIB
void REF_CalibrateStartStop(void) {
  REF_IsEnabled = TRUE;
  if (refState==REF_STATE_NOT_CALIBRATED || refState==REF_STATE_CALIBRATING || refState==REF_STATE_READY) {
    (void)xSemaphoreGive(REF_StartStopSem);
  }
}
#endif

bool REF_CanUseSensor(void) {
  return refState==REF_STATE_READY;
}

uint16_t REF_GetLineValue(bool *onLine) {
  *onLine = refCenterLineVal>0 && refCenterLineVal<REF_MAX_LINE_VALUE;
  return refCenterLineVal;
}

#if PL_CONFIG_HAS_SHELL
static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"ref", (unsigned char*)"Group of Reflectance commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  (on|off)", (unsigned char*)"Enables or disables the reflectance measurement\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  calib (start|stop)", (unsigned char*)"Start/Stop calibrating while moving sensor over line\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  led (on|off)", (unsigned char*)"Uses LED or not\r\n", io->stdOut);
  return ERR_OK;
}

static unsigned char*REF_GetStateString(void) {
  switch (refState) {
    case REF_STATE_INIT:                return (unsigned char*)"INIT";
    case REF_STATE_NOT_CALIBRATED:      return (unsigned char*)"NOT CALIBRATED";
    case REF_STATE_START_CALIBRATION:   return (unsigned char*)"START CALIBRATION";
    case REF_STATE_CALIBRATING:         return (unsigned char*)"CALIBRATING";
    case REF_STATE_STOP_CALIBRATION:    return (unsigned char*)"STOP CALIBRATION";
    case REF_STATE_SAVE_CALIBRATION:    return (unsigned char*)"SAVE CALIBRATION";
    case REF_STATE_READY:               return (unsigned char*)"READY";
    default:
      break;
  } /* switch */
  return (unsigned char*)"UNKNOWN";
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[32];
  int i;

  CLS1_SendStatusStr((unsigned char*)"reflectance", (unsigned char*)"\r\n", io->stdOut);
  
  CLS1_SendStatusStr((unsigned char*)"  enabled", REF_IsEnabled?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);
#if REF_USE_WHITE_LINE
  CLS1_SendStatusStr((unsigned char*)"  line", (unsigned char*)"white\r\n", io->stdOut);
#else
  CLS1_SendStatusStr((unsigned char*)"  line", (unsigned char*)"black\r\n", io->stdOut);
#endif
  CLS1_SendStatusStr((unsigned char*)"  state", REF_GetStateString(), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  IR led on", REF_LedOn?(unsigned char*)"yes\r\n":(unsigned char*)"no\r\n", io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), REF_MIN_NOISE_VAL);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  min noise", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), REF_MIN_LINE_VAL);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  min line", buf, io->stdOut);
  
  UTIL1_Num16uToStr(buf, sizeof(buf), REF_SENSOR_TIMEOUT_US);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" us, 0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), REF_TIMEOUT_TICKS);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ticks\r\n");
  CLS1_SendStatusStr((unsigned char*)"  timeout", buf, io->stdOut); 

  CLS1_SendStatusStr((unsigned char*)"  raw val", (unsigned char*)"", io->stdOut);
#if REF_SENSOR1_IS_LEFT
  for (i=0;i<REF_NOF_SENSORS;i++) {
    if (i==0) {
#else
  for (i=REF_NOF_SENSORS-1;i>=0;i--) {
    if (i==REF_NOF_SENSORS-1) {
#endif
      CLS1_SendStr((unsigned char*)"0x", io->stdOut);
    } else {
      CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
    }
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorRaw[i]);
    CLS1_SendStr(buf, io->stdOut);
  }
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  
  if (SensorCalibMinMaxPtr!=NULL) { /* have calibration data */
    CLS1_SendStatusStr((unsigned char*)"  min val", (unsigned char*)"", io->stdOut);
  #if REF_SENSOR1_IS_LEFT
    for (i=0;i<REF_NOF_SENSORS;i++) {
      if (i==0) {
  #else
    for (i=REF_NOF_SENSORS-1;i>=0;i--) {
      if (i==REF_NOF_SENSORS-1) {
  #endif
        CLS1_SendStr((unsigned char*)"0x", io->stdOut);
      } else {
        CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
      }
      buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibMinMaxPtr->minVal[i]);
      CLS1_SendStr(buf, io->stdOut);
    }
    CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  }
  if (SensorCalibMinMaxPtr!=NULL) {
    CLS1_SendStatusStr((unsigned char*)"  max val", (unsigned char*)"", io->stdOut);
  #if REF_SENSOR1_IS_LEFT
    for (i=0;i<REF_NOF_SENSORS;i++) {
      if (i==0) {
  #else
    for (i=REF_NOF_SENSORS-1;i>=0;i--) {
      if (i==REF_NOF_SENSORS-1) {
  #endif
        CLS1_SendStr((unsigned char*)"0x", io->stdOut);
      } else {
        CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
      }
      buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibMinMaxPtr->maxVal[i]);
      CLS1_SendStr(buf, io->stdOut);
    }
    CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  }

  if (SensorCalibMinMaxPtr!=NULL) { /* have calibration data */
    CLS1_SendStatusStr((unsigned char*)"  calib val", (unsigned char*)"", io->stdOut);
  #if REF_SENSOR1_IS_LEFT
    for (i=0;i<REF_NOF_SENSORS;i++) {
      if (i==0) {
  #else
    for (i=REF_NOF_SENSORS-1;i>=0;i--) {
      if (i==REF_NOF_SENSORS-1) {
  #endif
        CLS1_SendStr((unsigned char*)"0x", io->stdOut);
      } else {
        CLS1_SendStr((unsigned char*)" 0x", io->stdOut);
      }
      buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibrated[i]);
      CLS1_SendStr(buf, io->stdOut);
    }
    CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  }
  
  CLS1_SendStatusStr((unsigned char*)"  line pos", (unsigned char*)"", io->stdOut);
  buf[0] = '\0'; UTIL1_strcatNum16s(buf, sizeof(buf), refCenterLineVal);
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  line width", (unsigned char*)"", io->stdOut);
  buf[0] = '\0'; UTIL1_strcatNum16s(buf, sizeof(buf), refLineWidth);
  CLS1_SendStr(buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  line kind", REF_LineKindStr(refLineKind), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}

byte REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ref help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "ref status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "ref on")==0) {
    REF_IsEnabled = TRUE;
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ref off")==0) {
    REF_IsEnabled = FALSE;
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ref calib start")==0) {
    if (refState==REF_STATE_NOT_CALIBRATED || refState==REF_STATE_READY) {
      APP_StateStartCalibrate();
    } else {
      CLS1_SendStr((unsigned char*)"ERROR: cannot start calibration, must not be calibrating or be ready.\r\n", io->stdErr);
      return ERR_FAILED;
    }
    *handled = TRUE;
    return ERR_OK;  
  } else if (UTIL1_strcmp((char*)cmd, "ref calib stop")==0) {
    if (refState==REF_STATE_CALIBRATING) {
      APP_StateStopCalibrate();
    } else {
      CLS1_SendStr((unsigned char*)"ERROR: can only stop if calibrating.\r\n", io->stdErr);
      return ERR_FAILED;
    }
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ref led on")==0) {
    REF_LedOn = TRUE;
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ref led off")==0) {
    REF_LedOn = FALSE;
    *handled = TRUE;
    return ERR_OK;
  }
  return ERR_OK;
}
#endif /* PL_CONFIG_HAS_SHELL */

static void REF_StateMachine(void) {
  int i;

  switch (refState) {
    case REF_STATE_INIT:
      SensorCalibMinMaxPtr = NVMC_GetReflectanceData();
      if (SensorCalibMinMaxPtr!=NULL) { /* use calibration data from FLASH */
        refState = REF_STATE_READY;
      } else {
#if PL_CONFIG_HAS_SHELL
        CLS1_SendStr((unsigned char*)"no calibration data present.\r\n", SHELL_GetStdio()->stdOut);
#endif
        refState = REF_STATE_NOT_CALIBRATED;
      }
      break;
      
    case REF_STATE_NOT_CALIBRATED:
      FRTOS1_vTaskDelay(80/portTICK_PERIOD_MS); /* no need to sample that fast: this gives 80+20=100 ms */
      (void)REF_MeasureRaw(SensorRaw, REF_TIMEOUT_TICKS);
#if REF_START_STOP_CALIB
      if (FRTOS1_xSemaphoreTake(REF_StartStopSem, 0)==pdTRUE) {
        refState = REF_STATE_START_CALIBRATION;
      }
#endif
      break;
    
    case REF_STATE_START_CALIBRATION:
#if PL_CONFIG_HAS_SHELL
      SHELL_SendString((unsigned char*)"start calibration...\r\n");
#endif
      if (SensorCalibMinMaxTmpPtr!=NULL) {
        refState = REF_STATE_INIT; /* error case */
        break;
      }
      SensorCalibMinMaxTmpPtr = FRTOS1_pvPortMalloc(sizeof(SensorCalibT));
      if (SensorCalibMinMaxTmpPtr!=NULL) { /* success */
        for(i=0;i<REF_NOF_SENSORS;i++) {
          SensorCalibMinMaxTmpPtr->minVal[i] = MAX_SENSOR_VALUE;
          SensorCalibMinMaxTmpPtr->maxVal[i] = 0;
          SensorCalibrated[i] = 0;
        }
        refState = REF_STATE_CALIBRATING;
      } else {
        refState = REF_STATE_INIT; /* error case */
      }
      break;
    
    case REF_STATE_CALIBRATING:
      FRTOS1_vTaskDelay(80/portTICK_PERIOD_MS); /* no need to sample that fast: this gives 80+20=100 ms */
      if (SensorCalibMinMaxTmpPtr!=NULL) { /* safety check */
        REF_CalibrateMinMax(SensorCalibMinMaxTmpPtr->minVal, SensorCalibMinMaxTmpPtr->maxVal, SensorRaw);
      } else {
        refState = REF_STATE_INIT; /* error case */
        break;
      }
#if PL_HAS_BUZZER
      (void)BUZ_Beep(300, 50);
#endif
#if REF_START_STOP_CALIB
      if (FRTOS1_xSemaphoreTake(REF_StartStopSem, 0)==pdTRUE) {
        refState = REF_STATE_STOP_CALIBRATION;
      }
#endif
      break;
    
    case REF_STATE_STOP_CALIBRATION:
#if PL_CONFIG_HAS_SHELL
      SHELL_SendString((unsigned char*)"...stopping calibration.\r\n");
#endif
      refState = REF_STATE_SAVE_CALIBRATION;
      break;
    
    case REF_STATE_SAVE_CALIBRATION:
      (void)NVMC_SaveReflectanceData((void*)SensorCalibMinMaxTmpPtr, sizeof(SensorCalibT));
      /* free memory */
      FRTOS1_vPortFree(SensorCalibMinMaxTmpPtr);
      SensorCalibMinMaxTmpPtr = NULL;
      SensorCalibMinMaxPtr = NVMC_GetReflectanceData();
      if (SensorCalibMinMaxPtr!=NULL) { /* use calibration data from FLASH */
#if PL_CONFIG_HAS_SHELL
        SHELL_SendString((unsigned char*)"calibration data saved.\r\n");
#endif
        refState = REF_STATE_READY;
        break;
      } else {
        refState = REF_STATE_INIT; /* error case */
      }
      break;
    
    case REF_STATE_READY:
      REF_Measure();
#if REF_START_STOP_CALIB
      if (FRTOS1_xSemaphoreTake(REF_StartStopSem, 0)==pdTRUE) {
        refState = REF_STATE_START_CALIBRATION;
      }
#endif
      break;
  } /* switch */
}

static void ReflTask(void *pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    REF_StateMachine();
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void REF_Init(void) {
#if REF_START_STOP_CALIB
  FRTOS1_vSemaphoreCreateBinary(REF_StartStopSem);
  if (REF_StartStopSem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  (void)FRTOS1_xSemaphoreTake(REF_StartStopSem, 0); /* empty token */
  FRTOS1_vQueueAddToRegistry(REF_StartStopSem, "RefStartStopSem");
#if configUSE_TRACE_HOOKS
  PTRC1_vTraceSetQueueName(REF_StartStopSem, "RefStartStopSem");
#endif
#endif
  refState = REF_STATE_INIT;
#if PL_REMOTE_STOP_LINE
  refLineKind = REF_LINE_FULL; /* need an initial state, assume on black so the robot does not move */
#else
  refLineKind = REF_LINE_NONE;
#endif
  refCenterLineVal = 0;
  IR_on(TRUE); REF_LedOn = TRUE; /* IR LED's on */
#if 0 && PL_APP_REMOTE_CONTROL
  REF_IsEnabled = FALSE;
#else
  REF_IsEnabled = TRUE;
#endif
  timerHandle = RefCnt_Init(NULL);
  if (xTaskCreate(ReflTask, "Refl", 550/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+4, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_LINE_SENSOR */
