/**
 * \file
 * \brief Reflectance sensor driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the bot front sensor.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_REFLECTANCE
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
#include "UTIL1.h"
#include "FRTOS1.h"
#include "Application.h"
#include "Event.h"
#include "Shell.h"
#if PL_CONFIG_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_CONFIG_NVM
  #include "NVM_Config.h"
#endif

#define REF_NOF_SENSORS       6 /* number of sensors */
#define REF_SENSOR1_IS_LEFT   1 /* sensor number one is on the left side */
#define REF_MIN_NOISE_VAL     0x40   /* values below this are not added to the weighted sum */
#define REF_USE_WHITE_LINE    0  /* if set to 1, then the robot is using a white (on black) line, otherwise a black (on white) line */

#define REF_START_STOP_CALIB      1 /* start/stop calibration commands */
#if REF_START_STOP_CALIB
  static xSemaphoreHandle REF_StartStopSem = NULL;
#endif

typedef enum {
  REF_STATE_INIT,
  REF_STATE_NOT_CALIBRATED,
  REF_STATE_START_CALIBRATION,
  REF_STATE_CALIBRATING,
  REF_STATE_STOP_CALIBRATION,
  REF_STATE_READY
} RefStateType;
static volatile RefStateType refState = REF_STATE_INIT; /* state machine state */

static LDD_TDeviceData *timerHandle;

typedef struct SensorFctType_ {
  void (*SetOutput)(void);
  void (*SetInput)(void);
  void (*SetVal)(void);
  bool (*GetVal)(void);
} SensorFctType;

typedef uint16_t SensorTimeType;
#define MAX_SENSOR_VALUE  ((SensorTimeType)-1)

/* calibration min/max values */
typedef struct SensorCalibT_ {
  SensorTimeType minVal[REF_NOF_SENSORS];
  SensorTimeType maxVal[REF_NOF_SENSORS];
} SensorCalibT;

static int16_t refCenterLineVal=0; /* 0 means no line, >0 means line is below sensor 0, 1000 below sensor 1 and so on */
static SensorCalibT SensorCalibMinMax; /* min/max calibration data in SRAM */
static SensorTimeType SensorRaw[REF_NOF_SENSORS]; /* raw sensor values */
static SensorTimeType SensorCalibrated[REF_NOF_SENSORS]; /* 0 means white/min value, 1000 means black/max value */

/* Functions as wrapper around macro. */
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

static const SensorFctType SensorFctArray[REF_NOF_SENSORS] = {
  {S1_SetOutput, S1_SetInput, S1_SetVal, S1_GetVal},
  {S2_SetOutput, S2_SetInput, S2_SetVal, S2_GetVal},
  {S3_SetOutput, S3_SetInput, S3_SetVal, S3_GetVal},
  {S4_SetOutput, S4_SetInput, S4_SetVal, S4_GetVal},
  {S5_SetOutput, S5_SetInput, S5_SetVal, S5_GetVal},
  {S6_SetOutput, S6_SetInput, S6_SetVal, S6_GetVal},
};

#if 1 || PL_CONFIG_HAS_LINE_MAZE
void REF_GetSensorValues(uint16_t *values, int nofValues) {
  int i;

  for(i=0;i<nofValues && i<REF_NOF_SENSORS;i++) {
    values[i] = SensorCalibrated[i];
  }
}
#endif

#if REF_START_STOP_CALIB
void REF_CalibrateStartStop(void) {
  if (refState==REF_STATE_NOT_CALIBRATED || refState==REF_STATE_CALIBRATING || refState==REF_STATE_READY) {
    (void)xSemaphoreGive(REF_StartStopSem);
  }
}
#endif

/*!
 * \brief Measures the time until the sensor discharges
 * \param raw Array to store the raw values.
 * \return ERR_OVERFLOW if there is a timeout, ERR_OK otherwise
 */
static void REF_MeasureRaw(SensorTimeType raw[REF_NOF_SENSORS]) {
  uint8_t cnt; /* number of sensor */
  uint8_t i;
  RefCnt_TValueType timerVal;
  /*! \todo Consider reentrancy and mutual exclusion! */
#if 1 /*! \todo added timout */
  #define REF_SENSOR_TIMEOUT_US  1500
  const RefCnt_TValueType timeoutCntVal = ((RefCnt_CNT_INP_FREQ_U_0/1000)*REF_SENSOR_TIMEOUT_US)/1000 /* REF_SENSOR_TIMEOUT_US translated into timeout ticks */;
  bool isTimeout = FALSE;
#endif

  LED_IR_On(); /* IR LED's on */
  WAIT1_Waitus(200);
  taskENTER_CRITICAL();
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetOutput(); /* turn I/O line as output */
    SensorFctArray[i].SetVal(); /* put high */
    raw[i] = MAX_SENSOR_VALUE;
  }
  WAIT1_Waitus(50); /* give at least 10 us to charge the capacitor */
  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorFctArray[i].SetInput(); /* turn I/O line as input */
  }
  (void)RefCnt_ResetCounter(timerHandle); /* reset timer counter */
  do {
    timerVal = RefCnt_GetCounterValue(timerHandle);
#if 1 /*! \todo add timeout */
    if (timerVal>timeoutCntVal) {
      isTimeout = TRUE;
      break; /* get out of while loop */
    }
#endif
    cnt = 0;
    for(i=0;i<REF_NOF_SENSORS;i++) {
      if (raw[i]==MAX_SENSOR_VALUE) { /* not measured yet? */
        if (SensorFctArray[i].GetVal()==0) {
          raw[i] = (uint16_t)timerVal;
        }
      } else { /* have value */
        cnt++;
      }
    }
  } while(cnt!=REF_NOF_SENSORS);
  taskEXIT_CRITICAL();
  LED_IR_Off(); /* IR LED's off */
#if 1 /*! \todo added timeout */
  if (isTimeout) {
    for(i=0;i<REF_NOF_SENSORS;i++) {
      if (raw[i]==MAX_SENSOR_VALUE) { /* not measured yet? */
        raw[i] = SensorCalibMinMax.maxVal[i]; /* use calibrated max value */
      }
    } /* for */
  }
#endif
}

static void REF_CalibrateMinMax(SensorTimeType min[REF_NOF_SENSORS], SensorTimeType max[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS]) {
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
  for(i=0;i<REF_NOF_SENSORS;i++) {
    x = 0;
    denominator = SensorCalibMinMax.maxVal[i]-SensorCalibMinMax.minVal[i];
    if (denominator!=0) {
      x = (((int32_t)raw[i]-SensorCalibMinMax.minVal[i])*1000)/denominator;
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
static int ReadLine(SensorTimeType calib[REF_NOF_SENSORS], SensorTimeType raw[REF_NOF_SENSORS], bool white_line) {
  int i;
  unsigned long avg; /* this is for the weighted total, which is long */
  /* before division */
  unsigned int sum; /* this is for the denominator which is <= 64000 */
  unsigned int mul; /* multiplication factor, 0, 1000, 2000, 3000 ... */
  int value;

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
  return avg/sum;
}

uint16_t REF_GetLineValue(void) {
  return refCenterLineVal;
}

#if 1 || PL_CONFIG_HAS_LINE_FOLLOW
static REF_LineKind ReadLineKind(SensorTimeType val[REF_NOF_SENSORS]) {
  uint32_t sum, sumLeft, sumRight, outerLeft, outerRight;
  int i;
  #define REF_MIN_LINE_VAL      0x60   /* minimum value indicating a line */

  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (val[i]<REF_MIN_LINE_VAL) { /* smaller value? White seen! */
      break;
    }
  }
  if (i==REF_NOF_SENSORS) { /* all sensors see 'black' */
    return REF_LINE_FULL;
  }
  /* check the line type */
  sum = 0; sumLeft = 0; sumRight = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (val[i]>REF_MIN_LINE_VAL) { /* count only line values */
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

  #define MIN_LEFT_RIGHT_SUM   ((REF_NOF_SENSORS*1000)/4) /* 1/4 of full sensor values */

  if (outerLeft>=REF_MIN_LINE_VAL && outerRight<REF_MIN_LINE_VAL && sumLeft>MIN_LEFT_RIGHT_SUM && sumRight<MIN_LEFT_RIGHT_SUM) {
#if 1 || PL_APP_LINE_MAZE
    return REF_LINE_LEFT; /* line going to the left side */
#else
    return REF_LINE_STRAIGHT;
#endif
  } else if (outerLeft<REF_MIN_LINE_VAL && outerRight>=REF_MIN_LINE_VAL && sumRight>MIN_LEFT_RIGHT_SUM && sumLeft<MIN_LEFT_RIGHT_SUM) {
#if 1 || PL_APP_LINE_MAZE
    return REF_LINE_RIGHT; /* line going to the right side */
#else
    return REF_LINE_STRAIGHT;
#endif
  } else if (outerLeft>=REF_MIN_LINE_VAL && outerRight>=REF_MIN_LINE_VAL && sumRight>MIN_LEFT_RIGHT_SUM && sumLeft>MIN_LEFT_RIGHT_SUM) {
    return REF_LINE_FULL; /* full line */
  } else if (sumRight==0 && sumLeft==0 && sum == 0) {
    return REF_LINE_NONE; /* no line */
  } else {
    return REF_LINE_STRAIGHT; /* straight line forward */
  }
}
#endif

#if 1 || PL_CONFIG_HAS_LINE_FOLLOW
static REF_LineKind refLineKind = REF_LINE_NONE;

REF_LineKind REF_GetLineKind(void) {
  return refLineKind;
}
#endif

static void REF_Measure(void) {
  ReadCalibrated(SensorCalibrated, SensorRaw);
  refCenterLineVal = ReadLine(SensorCalibrated, SensorRaw, REF_USE_WHITE_LINE);
#if 1 || PL_CONFIG_HAS_LINE_FOLLOW
  refLineKind = ReadLineKind(SensorCalibrated);
#endif
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"ref", (unsigned char*)"Group of Reflectance commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
#if REF_START_STOP_CALIB
  CLS1_SendHelpStr((unsigned char*)"  calib (start|stop)", (unsigned char*)"Start/Stop calibrating while moving sensor over line\r\n", io->stdOut);
#endif
  return ERR_OK;
}

static unsigned char*REF_GetStateString(void) {
  switch (refState) {
    case REF_STATE_INIT:                return (unsigned char*)"INIT";
    case REF_STATE_NOT_CALIBRATED:      return (unsigned char*)"NOT CALIBRATED";
    case REF_STATE_START_CALIBRATION:   return (unsigned char*)"START CALIBRATION";
    case REF_STATE_CALIBRATING:         return (unsigned char*)"CALIBRATING";
    case REF_STATE_STOP_CALIBRATION:    return (unsigned char*)"STOP CALIBRATION";
    case REF_STATE_READY:               return (unsigned char*)"READY";
    default:
      break;
  } /* switch */
  return (unsigned char*)"UNKNOWN";
}

#if 1 || PL_CONFIG_HAS_LINE_FOLLOW
static unsigned char *REF_LineKindStr(REF_LineKind line) {
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
  default:
    return (unsigned char *)"unknown";
  } /* switch */
}
#endif

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  unsigned char buf[24];
  int i;

  CLS1_SendStatusStr((unsigned char*)"reflectance", (unsigned char*)"\r\n", io->stdOut);
  
  CLS1_SendStatusStr((unsigned char*)"  state", REF_GetStateString(), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), REF_MIN_NOISE_VAL);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  min noise", buf, io->stdOut);

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
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibMinMax.minVal[i]);
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
    buf[0] = '\0'; UTIL1_strcatNum16Hex(buf, sizeof(buf), SensorCalibMinMax.maxVal[i]);
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

#if 1 || PL_CONFIG_HAS_LINE_FOLLOW
  CLS1_SendStatusStr((unsigned char*)"  line kind", REF_LineKindStr(refLineKind), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
#endif
return ERR_OK;
}

byte REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ref help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "ref status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
#if REF_START_STOP_CALIB
  } else if (UTIL1_strcmp((char*)cmd, "ref calib start")==0) {
    if (refState==REF_STATE_NOT_CALIBRATED || refState==REF_STATE_READY) {
      REF_CalibrateStartStop();
    } else {
      CLS1_SendStr((unsigned char*)"ERROR: cannot start calibration, must not be calibrating or be ready.\r\n", io->stdErr);
      return ERR_FAILED;
    }
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ref calib stop")==0) {
    if (refState==REF_STATE_CALIBRATING) {
      REF_CalibrateStartStop();
    } else {
      CLS1_SendStr((unsigned char*)"ERROR: can only stop if calibrating.\r\n", io->stdErr);
      return ERR_FAILED;
    }
    *handled = TRUE;
    return ERR_OK;
#endif
  }
  return ERR_OK;
}

static void REF_StateMachine(void) {
  int i;

  switch (refState) {
    case REF_STATE_INIT:
    #if PL_CONFIG_HAS_CONFIG_NVM
    {
      SensorCalibT *ptr;

      ptr = (SensorCalibT*)NVMC_GetReflectanceData();
      if (ptr!=NULL) { /* valid data */
        SensorCalibMinMax = *ptr; /* struct copy */
        refState = REF_STATE_READY;
      } else {
        refState = REF_STATE_NOT_CALIBRATED;
      }
    }
    #else
      SHELL_SendString((unsigned char*)"INFO: No calibration data present.\r\n");
      refState = REF_STATE_NOT_CALIBRATED;
    #endif
      break;
      
    case REF_STATE_NOT_CALIBRATED:
      REF_MeasureRaw(SensorRaw);
      /*! \todo You might add a new event to your event module...*/
#if REF_START_STOP_CALIB
      if (FRTOS1_xSemaphoreTake(REF_StartStopSem, 0)==pdTRUE) {
        refState = REF_STATE_START_CALIBRATION;
      }
#endif
      break;
    
    case REF_STATE_START_CALIBRATION:
      SHELL_SendString((unsigned char*)"start calibration...\r\n");
      for(i=0;i<REF_NOF_SENSORS;i++) {
        SensorCalibMinMax.minVal[i] = MAX_SENSOR_VALUE;
        SensorCalibMinMax.maxVal[i] = 0;
        SensorCalibrated[i] = 0;
      }
      refState = REF_STATE_CALIBRATING;
      break;
    
    case REF_STATE_CALIBRATING:
      REF_CalibrateMinMax(SensorCalibMinMax.minVal, SensorCalibMinMax.maxVal, SensorRaw);
#if PL_CONFIG_HAS_BUZZER
      (void)BUZ_Beep(300, 20);
#endif
#if REF_START_STOP_CALIB
      if (FRTOS1_xSemaphoreTake(REF_StartStopSem, 0)==pdTRUE) {
        refState = REF_STATE_STOP_CALIBRATION;
      }
#endif
      break;
    
    case REF_STATE_STOP_CALIBRATION:
      SHELL_SendString((unsigned char*)"...stopping calibration.\r\n");
#if PL_CONFIG_HAS_CONFIG_NVM
      if (NVMC_SaveReflectanceData(&SensorCalibMinMax, sizeof(SensorCalibMinMax))!=ERR_OK) {
        SHELL_SendString((unsigned char*)"Flashing calibration data FAILED!\r\n");
      } else {
        SHELL_SendString((unsigned char*)"Stored calibration data.\r\n");
      }
#endif
      refState = REF_STATE_READY;
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

bool REF_IsReady(void) {
  return refState==REF_STATE_READY;
}

static void ReflTask (void *pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    REF_StateMachine();
    FRTOS1_vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void REF_Deinit(void) {
}

void REF_Init(void) {
#if REF_START_STOP_CALIB
  vSemaphoreCreateBinary(REF_StartStopSem);
  if (REF_StartStopSem==NULL) { /* semaphore creation failed */
    for(;;){} /* error */
  }
  (void)xSemaphoreTake(REF_StartStopSem, 0); /* empty token */
  vQueueAddToRegistry(REF_StartStopSem, "RefStartStopSem");
#endif

  refState = REF_STATE_INIT;
  timerHandle = RefCnt_Init(NULL);
  /*! \todo You might need to adjust priority or other task settings */
  if (xTaskCreate(ReflTask, "Refl", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_HAS_REFLECTANCE */
