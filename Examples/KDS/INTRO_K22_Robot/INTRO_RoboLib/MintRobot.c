/*
 * MintRobot.c
 *
 *  Created on: 22.08.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#if PL_HAS_MINT_ROBOT
#include "MintRobot.h"
#include "CLS1.h"
#include "MintLED.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "RNet_App.h"
#include "Reflectance.h"
#include "LineFollow.h"
#include "LineHistory.h"
#include "PID.h"
#include "Turn.h"
#include "Drive.h"
#include "Motor.h"
#include "Shell.h"
#include "UTIL1.h"
#if PL_HAS_MINT_IR
  #include "IRTX38.h"
  #include "IRRX.h"
#else
  #include "SW1.h"
#endif
#if PL_HAS_TOF_SENSOR
  #include "VL6180X.h"
#endif
#if PL_HAS_DISTANCE_SENSOR
  #include "Distance.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_CONFIG_HAS_BATTERY_ADC
  #include "Battery.h"
#endif

#define MINT_CHECK_TOF_WHILE_LINE_FOLLOWING   0  /* if we check the ToF distance sensors while following the line */
#define MINT_USE_REED_POSITION_CONTACT        0  /* if we use the reed contact information to determine the robot position */

typedef enum {
  MINT_STATE_ERROR,
  MINT_STATE_START_MANUAL,
  MINT_STATE_MANUAL,
  MINT_STATE_MANUAL_GOTO_START,        /* user driving to the start area */
  MINT_STATE_MANUAL_START_REACHED,     /* user has placed robot on start area */
  MINT_STATE_MANUAL_GOTO_FINISH,       /* user driving to the finish area */
  MINT_STATE_MANUAL_FINISH_REACHED,    /* user has placed robot on finish area */
  MINT_STATE_START_AUTOMATIC,
  MINT_STATE_AUTOMATIC,
  MINT_STATE_FIND_CENTER,
  MINT_STATE_FIND_LINE,
  MINT_STATE_POSITION_ON_LINE,
  MINT_STATE_CENTER_ON_LINE,
  MINT_STATE_GOTO_START,
  MINT_STATE_CHECK_START,
  MINT_STATE_START_REACHED,
  MINT_STATE_WAIT_FOR_BALL,
  MINT_STATE_GOTO_FINISH,
  MINT_STATE_CHECK_FINISH,
  MINT_STATE_FINISH_REACHED,
  MINT_STATE_WAIT_FOR_BALL_REMOVAL,
} MINT_StateType;

typedef enum {
  MINT_MODE_MANUAL=0,
  MINT_MODE_AUTOMATIC=1
} MINT_ModeType;

#define MINT_DRIVE_FIND_LINE_SPEED 400

static MINT_ModeType MINT_Mode = MINT_MODE_MANUAL;
static MINT_StateType MINT_State = MINT_STATE_MANUAL;
#if MINT_USE_REED_POSITION_CONTACT
  static volatile uint8_t MINT_ReedContactPosition = 0; /* 0: no position, 1: start position, 2: finish position */
#endif
static xTaskHandle MintTaskHandle;
static portTickType MINT_ManualModeTimoutTicks = 0; /* number of ticks in manual mode for timeout */
#define MINT_MANUAL_MODE_TIMEOUT_SECONDS       0 /* 60 */ /* timeout value for manual mode without activity, 0 disables the timeout function */

/* task notification bits */
#define MINT_GOTO_LINE          (1<<0)  /* go to line */
#define MINT_GOTO_START         (1<<1)  /* go to start position */
#define MINT_GOTO_FINISH        (1<<2)  /* go to finish position */
#define MINT_SET_MANUAL_MODE    (1<<3)  /* set manual mode */
#define MINT_SET_AUTOMATIC_MODE (1<<4)  /* set automatic mode */

bool MINT_AllowedToDrive(void) {
  MINT_ManualModeTimoutTicks = xTaskGetTickCount(); /* rest timeout tick counter */
  return MINT_Mode==MINT_MODE_MANUAL;
}

static const unsigned char *MINT_StateToStr(MINT_StateType state) {
  switch(state) {
    case MINT_STATE_ERROR:                 return "ERROR";
    /* manual states */
    case MINT_STATE_START_MANUAL:          return "START_MANUAL";
    case MINT_STATE_MANUAL:                return "MANUAL";
    case MINT_STATE_MANUAL_GOTO_START:     return "MANUAL_GOTO_START";
    case MINT_STATE_MANUAL_START_REACHED:  return "MANUAL_START_REACHED";
    case MINT_STATE_MANUAL_GOTO_FINISH:    return "MANUAL_GOTO_FINISH";
    case MINT_STATE_MANUAL_FINISH_REACHED: return "MANUAL_FINISH_REACHED";
    /* automatic states */
    case MINT_STATE_START_AUTOMATIC:       return "START_AUTOMATIC";
    case MINT_STATE_AUTOMATIC:             return "AUTOMATIC";
    case MINT_STATE_FIND_CENTER:           return "FIND_CENTER";
    case MINT_STATE_FIND_LINE:             return "FIND_LINE";
    case MINT_STATE_POSITION_ON_LINE:      return "POSITION_ON_LINE";
    case MINT_STATE_CENTER_ON_LINE:        return "CENTR_ON_LINE";
    case MINT_STATE_GOTO_START:            return "GOTO_START";
    case MINT_STATE_CHECK_START:           return "CHECK_START";
    case MINT_STATE_START_REACHED:         return "START_REACHED";
    case MINT_STATE_WAIT_FOR_BALL:         return "WAIT_FOR_BALL";
    case MINT_STATE_GOTO_FINISH:           return "GOTO_FINISH";
    case MINT_STATE_CHECK_FINISH:          return "CHECK_FINISH";
    case MINT_STATE_FINISH_REACHED:        return "FINISH_REACHED";
    case MINT_STATE_WAIT_FOR_BALL_REMOVAL: return "WAIT_FOR_BALL_REMOVAL";
    default:
      break;
  }
  return "????";
}

static const unsigned char *MINT_ModeToStr(MINT_ModeType state) {
  switch(state) {
    case MINT_MODE_MANUAL:          return "MANUAL";
    case MINT_MODE_AUTOMATIC:       return "AUTOMATIC";
    default:
      break;
  }
  return "????";
}

static void MINT_SetManualMode(void) {
  (void)xTaskNotify(MintTaskHandle, MINT_SET_MANUAL_MODE, eSetBits);
}

static void MINT_SetAutomaticMode(void) {
  (void)xTaskNotify(MintTaskHandle, MINT_SET_AUTOMATIC_MODE, eSetBits);
}

static void MINT_GotoLine(void) {
  (void)xTaskNotify(MintTaskHandle, MINT_GOTO_LINE, eSetBits);
}

static void MINT_GotoStart(void) {
  (void)xTaskNotify(MintTaskHandle, MINT_GOTO_START, eSetBits);
}

static void MINT_GotoFinish(void) {
  (void)xTaskNotify(MintTaskHandle, MINT_GOTO_FINISH, eSetBits);
}

static uint32_t GetTaskNotificationBits(uint32_t bits, bool clearBits) {
  uint32_t notifcationValue;
  BaseType_t res;

  notifcationValue = 0; /* init */
  res = xTaskNotifyWait(0UL, bits, &notifcationValue, 0); /* get flags */
  if (res==pdTRUE) {
    /* A notification was already pending or a notification was
    received while the task was waiting. */
    if (!clearBits) { /* bits were cleared on exit: set the bits again */
      (void)xTaskNotify(MintTaskHandle, notifcationValue, eSetBits);
    }
  }
  if (clearBits && (notifcationValue&bits)) {
    (void)xTaskNotifyWait(bits, 0, NULL, 0); /* clear bits */
  }
  return notifcationValue;
}

static void EnableBallDetect(bool on) {
#if PL_HAS_MINT_IR
  if (on) {
    IRTX38_Enable();
  } else {
    IRTX38_Disable();
  }
#endif
}

static bool BallIsIn(void) {
  bool ballDetected;

  EnableBallDetect(TRUE); /* turn on IR */
  vTaskDelay(pdMS_TO_TICKS(100)); /* wait some time */
#if PL_HAS_MINT_IR
  ballDetected = IRRX_GetVal()!=0; /* If no IR (blocked, ball detected, pin is HIGH. if IR signal is detected (no ball), the pin will be pulled LOW */
#else
  ballDetected = FALSE;
#endif
  EnableBallDetect(FALSE); /* turn off IR */
  return ballDetected;
}

/* temporary data for line finding */
static struct {
  bool turnLeft;
  uint16_t startRef[REF_NOF_SENSORS];
  int32_t leftSpeed, rightSpeed;
} tmp;

static void StartMoveToLine(void) {
  REF_GetSensorValues(&tmp.startRef[0], REF_NOF_SENSORS);
  tmp.turnLeft = tmp.startRef[0]<REF_MIN_LINE_VAL;
  tmp.leftSpeed = tmp.rightSpeed = 200;
  DRV_SetSpeed(tmp.leftSpeed, tmp.rightSpeed);
  (void)DRV_SetMode(DRV_MODE_SPEED);
}

static bool MoveToLine(void) {
  uint16_t currRef[REF_NOF_SENSORS];
  #define LINE_THRESHOLD  (REF_MIN_LINE_VAL*2)

  REF_GetSensorValues(&currRef[0], REF_NOF_SENSORS);
  if (currRef[REF_NOF_SENSORS/2]<LINE_THRESHOLD || currRef[(REF_NOF_SENSORS/2)-1]<LINE_THRESHOLD) {
    return TRUE; /* still not reached line in the middle, continue driving */
  } else {
    if (   currRef[0]<LINE_THRESHOLD
        && currRef[REF_NOF_SENSORS/2]>=LINE_THRESHOLD
        && currRef[(REF_NOF_SENSORS/2)-1]>=LINE_THRESHOLD
        && currRef[REF_NOF_SENSORS-1]<LINE_THRESHOLD
        )
    { /* staying on the line */
      return FALSE; /* left and right on white, middle on black ==> continue with line following */
    } else if (tmp.turnLeft && currRef[0]<LINE_THRESHOLD && currRef[REF_NOF_SENSORS-1]>=LINE_THRESHOLD) { /* turning left: left on white, right on black */
      DRV_SetSpeed(-tmp.leftSpeed-200, tmp.rightSpeed+400); /* turn left */
      return TRUE; /* continue driving */
    } else if (tmp.turnLeft && currRef[0]>=LINE_THRESHOLD && currRef[REF_NOF_SENSORS-1]<LINE_THRESHOLD) { /* turning left: past line?: left on black, right on white */
      DRV_SetSpeed(-tmp.leftSpeed-200, tmp.rightSpeed+400); /* turn left */
      return TRUE; /* continue driving */
    } else if (!tmp.turnLeft && currRef[0]>=LINE_THRESHOLD && currRef[REF_NOF_SENSORS-1]<LINE_THRESHOLD) { /* turning right: left on black, right on white */
      DRV_SetSpeed(tmp.leftSpeed+400, -tmp.rightSpeed-200); /* turn right */
      return TRUE; /* continue driving */
    } else if (!tmp.turnLeft && currRef[0]<LINE_THRESHOLD && currRef[REF_NOF_SENSORS-1]>=LINE_THRESHOLD) { /* turning right, past line?: left on white, right on black */
      DRV_SetSpeed(tmp.leftSpeed+400, -tmp.rightSpeed-200); /* turn right */
      return TRUE; /* continue driving */
    } else if (currRef[0]>=LINE_THRESHOLD && currRef[REF_NOF_SENSORS-1]>=LINE_THRESHOLD) { /* on full black line? left on black, right on black */
      if (tmp.turnLeft) {
        DRV_SetSpeed(tmp.leftSpeed, tmp.rightSpeed+400); /* turn right */
      } else {
        DRV_SetSpeed(tmp.leftSpeed+400, tmp.rightSpeed); /* turn left */
      }
      return TRUE; /* continue driving */
    }
    return FALSE; /* middle on black, right on white ==> continue with line following */
  }
  return TRUE;
}

uint8_t MINT_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
  uint8_t val;
  uint16_t id;
  bool beep = FALSE;

  (void)size;
  (void)packet;
  switch(type) {
    case RAPP_MSG_TYPE_REQUEST_SET_VALUE:
      id = UTIL1_GetValue16LE(data); /* extract 16bit ID (little endian) */
      if (id==RAPP_MSG_TYPE_DATA_ID_MINT_MODE) {
        uint32_t mode;

        mode = UTIL1_GetValue32LE(&data[2]);
        if (mode==MINT_MODE_AUTOMATIC) {
          MINT_SetAutomaticMode();
        } else if (mode==MINT_MODE_MANUAL) {
          MINT_SetManualMode();
        }
        *handled = TRUE;
        beep =  TRUE;
      } else if (id==RAPP_MSG_TYPE_DATA_ID_MINT_GOTO) {
        uint32_t where;

        where = UTIL1_GetValue32LE(&data[2]);
        if (where==0) {
          MINT_GotoLine();
        } else if (where==1) {
          MINT_GotoStart();
        } else if (where==2) {
          MINT_GotoFinish();
        }
        *handled = TRUE;
        beep =  TRUE;
      } else if (id==RAPP_MSG_TYPE_DATA_ID_PID_FW_SPEED) {
        uint8_t speed;
        PID_Config *lineFwPid;
        uint8_t res;

        speed = UTIL1_GetValue32LE(&data[2]);
        res = PID_GetPIDConfig(PID_CONFIG_LINE_FW, &lineFwPid);
        if (res==ERR_OK && lineFwPid!=NULL) {
          lineFwPid->maxSpeedPercent = speed;
        }
        *handled = TRUE;
        beep =  TRUE;
      }
      break;

    case RAPP_MSG_TYPE_QUERY_VALUE:
      id = UTIL1_GetValue16LE(data); /* extract 16bit ID (little endian) */
      if (id==RAPP_MSG_TYPE_DATA_ID_MINT_BALL) { /* send back data */
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, BallIsIn()?1:0, srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
        beep =  TRUE;
      } else if (id==RAPP_MSG_TYPE_DATA_ID_MINT_MODE) {
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, MINT_Mode, srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
        beep =  TRUE;
      } else if (id==RAPP_MSG_TYPE_DATA_ID_TOF_VALUES) {
        union {
          uint8_t mm[4];
          uint32_t val;
        } dist;

        dist.mm[0] = DIST_GetDistance(DIST_SENSOR_FRONT);
        dist.mm[1] = DIST_GetDistance(DIST_SENSOR_LEFT);
        dist.mm[2] = DIST_GetDistance(DIST_SENSOR_REAR);
        dist.mm[3] = DIST_GetDistance(DIST_SENSOR_RIGHT);
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, dist.val, srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
        beep =  TRUE;
    #if MINT_USE_REED_POSITION_CONTACT
      } else if (id==RAPP_MSG_TYPE_DATA_ID_REED_CONTACT) {
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, MINT_ReedContactPosition, srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
        beep =  TRUE;
    #endif
      } else if (id==RAPP_MSG_TYPE_DATA_ID_BATTERY_V) {
        uint16_t centiV;

     #if PL_CONFIG_HAS_BATTERY_ADC
        if (BATT_MeasureBatteryVoltage(&centiV)!=ERR_OK) {
          centiV = 0; /* error case */
        }
      #else
        centiV = 0; /* error case */
      #endif
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, centiV, srcAddr, RPHY_PACKET_FLAGS_NONE);
        *handled = TRUE;
        beep =  TRUE;
      } else if (id==RAPP_MSG_TYPE_DATA_ID_PID_FW_SPEED) {
        uint8_t speed = 0;
        PID_Config *lineFwPid;
        uint8_t res;

        res = PID_GetPIDConfig(PID_CONFIG_LINE_FW, &lineFwPid);
        if (res==ERR_OK && lineFwPid!=NULL) {
          speed = lineFwPid->maxSpeedPercent;
          RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE, id, speed, srcAddr, RPHY_PACKET_FLAGS_NONE);
        }
        *handled = TRUE;
        beep =  TRUE;
      }
      break;

    case RAPP_MSG_TYPE_NOTIFY_VALUE:
      id = UTIL1_GetValue16LE(data); /* extract 16bit ID (little endian) */
#if MINT_USE_REED_POSITION_CONTACT
      if (id==RAPP_MSG_TYPE_DATA_ID_REED_CONTACT) { /* send back data */
        MINT_ReedContactPosition = (uint8_t)UTIL1_GetValue32LE(&data[2]); /* 0: no position, 1: start, 2: finish */
        *handled = TRUE;
        beep =  TRUE;
      }
#endif
      break;

    default:
      break;
  } /* switch */
  if (beep) {
  #if PL_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_BUTTON);
  #endif
  }
  return ERR_OK;
}

static uint8_t CheckManualDrivingConditions(void) {
#if PL_HAS_DISTANCE_SENSOR
  if (DIST_MotorDrivingIntoObstacle()!=0) { /* forward/backward check */
    DRV_SetSpeed(0, 0);
  } else if (DRV_GetMode()!=DRV_MODE_SPEED) {
    DRV_SetMode(DRV_MODE_SPEED); /* go into driving mode again */
  }
#endif
#if MINT_MANUAL_MODE_TIMEOUT_SECONDS > 0
  if (((xTaskGetTickCount()-MINT_ManualModeTimoutTicks)/configTICK_RATE_HZ)>MINT_MANUAL_MODE_TIMEOUT_SECONDS) {
    MINT_ManualModeTimoutTicks = 0;
    DRV_SetSpeed(0, 0);
    CLS1_SendStr("Manual mode timeout.\r\n", SHELL_GetStdio()->stdOut);
    (void)GetTaskNotificationBits(MINT_GOTO_LINE|MINT_GOTO_START|MINT_GOTO_FINISH, TRUE); /* clear any pending bits */
    MINT_State = MINT_STATE_START_AUTOMATIC;
    return ERR_OVERRUN;
  }
#endif
  return ERR_OK;
}

#if PL_HAS_DISTANCE_SENSOR
static bool IsInFinishBox(void) {
#if MINT_USE_REED_POSITION_CONTACT
  if (MINT_ReedContactPosition!=2) {
    return FALSE;
  }
#endif
  /*  example range      : front:140 left:115 rear:255 right:96  */
  return
         DIST_NearFrontObstacle(160)
      && DIST_NearLeftObstacle(140)
      && DIST_NearRightObstacle(120)
      && !DIST_NearRearObstacle(200);
}

static bool IsInStartBox(void) {
#if MINT_USE_REED_POSITION_CONTACT
  if (MINT_ReedContactPosition!=1) {
    return FALSE;
  }
#endif
  /* example   range      : front:58 left:89 rear:255 right:118   */
  return DIST_NearFrontObstacle(80)
      && DIST_NearLeftObstacle(110)
      && DIST_NearRightObstacle(150)
      && !DIST_NearRearObstacle(200);
}
#endif

static bool IsOnStartPosition(void) {
  REF_LineKind currLineKind;

  currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
  if (currLineKind == REF_LINE_FULL) {
#if PL_HAS_TOF_SENSOR
    return IsInStartBox();
#else
    return TRUE;
#endif
  }
  return FALSE;
}

static bool IsOnFinishPosition(void) {
  REF_LineKind currLineKind;

  currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
  if (currLineKind == REF_LINE_NONE) {
#if PL_HAS_TOF_SENSOR
    return IsInFinishBox();
#else
    return TRUE;
#endif
  }
  return FALSE;
}

static void Process(void) {
  REF_LineKind currLineKind;
  bool onLine;
  uint16_t lineWidth;
  int i;
  uint32_t notifcationValue;

  for(;;) { /* will break */
    switch(MINT_State) {
      case MINT_STATE_ERROR:
        CLS1_SendStr("ERROR!\r\n", SHELL_GetStdio()->stdErr);
        DRV_SetSpeed(0, 0);
        DRV_SetMode(DRV_MODE_STOP);
      #if PL_HAS_MINT_LED
         MINTLED_SetMode(MINTLED_MODE_ERROR);
      #endif
         for (i=0;i<10;i++) {
        #if PL_HAS_BUZZER
          BUZ_PlayTune(BUZ_TUNE_BUTTON);
        #endif
          vTaskDelay(pdMS_TO_TICKS(200));
         }
        MINT_State = MINT_STATE_START_MANUAL;
        break;

      case MINT_STATE_START_MANUAL:
        CLS1_SendStr("Manual mode: going to manual state.\r\n", SHELL_GetStdio()->stdOut);
        MINT_ManualModeTimoutTicks = xTaskGetTickCount(); /* get tick counter for timeout value */
        (void)GetTaskNotificationBits(MINT_GOTO_LINE|MINT_GOTO_START|MINT_GOTO_FINISH, TRUE); /* clear bits which do not apply to manual mode */
        DRV_SetSpeed(0, 0);
        DRV_SetMode(DRV_MODE_SPEED);
        MINT_Mode = MINT_MODE_MANUAL;
        MINT_State = MINT_STATE_MANUAL;
        continue;

      case MINT_STATE_MANUAL:
        CheckManualDrivingConditions(); /* just checking if we are OK */
        if (BallIsIn()) { /* have ball */
          CLS1_SendStr("Have ball, need to go to finish.\r\n", SHELL_GetStdio()->stdOut);
          MINT_State = MINT_STATE_MANUAL_GOTO_FINISH;
        } else {
          CLS1_SendStr("Have no ball, need to go to start.\r\n", SHELL_GetStdio()->stdOut);
          MINT_State = MINT_STATE_MANUAL_GOTO_START;
        }
      #if PL_HAS_MINT_LED
        MINTLED_SetMode(MINTLED_MODE_JOYSTICK);
      #endif
        break;

      case MINT_STATE_MANUAL_GOTO_START:
        notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, FALSE); /* check flags */
        if (notifcationValue!=0) { /* any of the bits set? */
          MINT_State = MINT_STATE_START_AUTOMATIC; /* go into automatic mode, it will handle the bits there */
        } else {
          CheckManualDrivingConditions(); /* just checking if we are OK */
          if (IsOnStartPosition()) {
          #if PL_HAS_MINT_LED
            MINTLED_SetMode(MINTLED_MODE_MANUAL_ON_START);
          #endif
            CLS1_SendStr("Start reached! Insert ball...\r\n", SHELL_GetStdio()->stdOut);
            RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_POSITION, 1, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
          #if PL_HAS_BUZZER
            BUZ_PlayTune(BUZ_TUNE_BUTTON);
          #endif
            DRV_SetSpeed(0, 0); /* stop the engines */
            DRV_SetMode(DRV_MODE_STOP);
            MINT_State = MINT_STATE_MANUAL_START_REACHED;
          }
        }
        break;

      case MINT_STATE_MANUAL_START_REACHED:
        notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, TRUE); /* check flags */
        if (notifcationValue&MINT_GOTO_FINISH) { /* any of the bits set? */
          TURN_Turn(TURN_RIGHT180, NULL); /* turn around */
          MINT_GotoFinish();
          MINT_State = MINT_STATE_START_AUTOMATIC; /* go into automatic mode, it will handle the bits there */
        } else if (!IsOnStartPosition()) { /* not on start any more? */
          /* go back to driving mode */
          CLS1_SendStr("Not on start position any more? Going back to manual mode.\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_START_MANUAL;
        } else if (BallIsIn()) { /* wait for ball */
          vTaskDelay(pdMS_TO_TICKS(1000)); /* wait some time */
          if (BallIsIn()) { /* check for ball again */
          #if PL_HAS_BUZZER
            BUZ_PlayTune(BUZ_TUNE_BUTTON);
          #endif
            CLS1_SendStr("Ball received!\r\n", SHELL_GetStdio()->stdOut);
            RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_MINT_BALL, 1, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
            MINT_State = MINT_STATE_START_MANUAL;
          }
        }
        break;

      case MINT_STATE_MANUAL_GOTO_FINISH:
        notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, FALSE); /* check flags */
        if (notifcationValue!=0) { /* any of the bits set? */
          MINT_State = MINT_STATE_START_AUTOMATIC; /* go into automatic mode, it will handle the bits there */
        } else {
          CheckManualDrivingConditions(); /* just checking if we are OK */
          if (IsOnFinishPosition()) {
          #if PL_HAS_MINT_LED
            MINTLED_SetMode(MINTLED_MODE_MANUAL_ON_FINISH);
          #endif
            CLS1_SendStr("Finish reached! Remove ball...\r\n", SHELL_GetStdio()->stdOut);
            RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_POSITION, 2, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
          #if PL_HAS_BUZZER
            BUZ_PlayTune(BUZ_TUNE_BUTTON);
          #endif
            DRV_SetSpeed(0, 0); /* stop the engines */
            DRV_SetMode(DRV_MODE_STOP);
            MINT_State = MINT_STATE_MANUAL_FINISH_REACHED;
          }
        }
        break;

      case MINT_STATE_MANUAL_FINISH_REACHED:
        notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, FALSE); /* check flags */
        if (notifcationValue!=0) { /* any of the bits set? */
          MINT_State = MINT_STATE_START_AUTOMATIC; /* go into automatic mode, it will handle the bits there */
        } else if (!IsOnFinishPosition()) { /* not on finish any more? */
          /* go back to driving mode */
          CLS1_SendStr("Not on finish position any more? Going back to manual mode.\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_START_MANUAL;
        } else if (!BallIsIn()) { /* wait for ball removal */
          vTaskDelay(pdMS_TO_TICKS(1000)); /* wait some time */
          if (!BallIsIn()) { /* check for ball removal again */
          #if PL_HAS_BUZZER
            BUZ_PlayTune(BUZ_TUNE_BUTTON);
          #endif
            CLS1_SendStr("Ball removed!\r\n", SHELL_GetStdio()->stdOut);
            RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_MINT_BALL, 0, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
            MINT_State = MINT_STATE_START_MANUAL;
          }
        }
        break;

      case MINT_STATE_START_AUTOMATIC:
        CLS1_SendStr("Automatic mode: going to automatic state.\r\n", SHELL_GetStdio()->stdOut);
      #if PL_HAS_MINT_LED
         MINTLED_SetMode(MINTLED_MODE_AUTOMATIC);
      #endif
        MINT_Mode = MINT_MODE_AUTOMATIC;
        MINT_State = MINT_STATE_AUTOMATIC;
        break;

      case MINT_STATE_AUTOMATIC:
        if (!REF_CanUseSensor()) { /* sensor not available? */
          CLS1_SendStr("ERROR: cannot use sensors.\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR; /* error */
        } else {
          currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
#if 0 /* button emulation only */
          if (SW1_GetVal()==0) { /* key pressed */
            CLS1_SendStr("Key pressed.\r\n", SHELL_GetStdio()->stdOut);
            if (currLineKind==REF_LINE_STRAIGHT) {
              (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following */
             #if PL_HAS_MINT_LED
               MINTLED_SetMode(MINTLED_MODE_GOTO_START);
             #endif
               CLS1_SendStr("Going to start.\r\n", SHELL_GetStdio()->stdOut);
               MINT_State = MINT_STATE_GOTO_START;
            } else {
              CLS1_SendStr("Going to line.\r\n", SHELL_GetStdio()->stdOut);
              DRV_SetSpeed(MINT_DRIVE_FIND_LINE_SPEED, MINT_DRIVE_FIND_LINE_SPEED);
              (void)DRV_SetMode(DRV_MODE_SPEED);
              MINT_State = MINT_STATE_FIND_LINE;
            }
          }
#endif
          notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, FALSE); /* check flags */
          if (notifcationValue&MINT_GOTO_LINE) {
            (void)GetTaskNotificationBits(MINT_GOTO_LINE, TRUE); /* clear flag, but keep MINT_GOTO_START and MINT_GOTO_FINISH */
            CLS1_SendStr("Going to line.\r\n", SHELL_GetStdio()->stdOut);
            currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
            if(currLineKind==REF_LINE_STRAIGHT) {
              CLS1_SendStr("Already on line.\r\n", SHELL_GetStdio()->stdOut);
              MINT_State = MINT_STATE_START_MANUAL; /* go back to manual mode */
            } else {
              DRV_SetSpeed(MINT_DRIVE_FIND_LINE_SPEED, MINT_DRIVE_FIND_LINE_SPEED);
              (void)DRV_SetMode(DRV_MODE_SPEED);
              MINT_State = MINT_STATE_FIND_LINE;
            }
          } else if (notifcationValue&MINT_GOTO_START) {
            (void)GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, FALSE); /* clear flags */
            if (currLineKind==REF_LINE_STRAIGHT || IsOnStartPosition()) {
             (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following */
            #if PL_HAS_MINT_LED
              MINTLED_SetMode(MINTLED_MODE_GOTO_START);
            #endif
              CLS1_SendStr("Going to start.\r\n", SHELL_GetStdio()->stdOut);
              MINT_State = MINT_STATE_GOTO_START;
            } else {
              MINT_GotoLine(); /* set goto line flag */
              MINT_GotoStart(); /* set goto start flag */
              CLS1_SendStr("Request sent to goto line (then goto start).\r\n", SHELL_GetStdio()->stdOut);
              //CLS1_SendStr("ERROR: not on line, cannot go to start.\r\n", SHELL_GetStdio()->stdErr);
              //MINT_State = MINT_STATE_ERROR;
            }
          } else if (notifcationValue&MINT_GOTO_FINISH) {
            (void)GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, FALSE); /* clear flags */
            if (currLineKind==REF_LINE_STRAIGHT) {
             (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following */
            #if PL_HAS_MINT_LED
              MINTLED_SetMode(MINTLED_MODE_GOTO_FINISH);
            #endif
              CLS1_SendStr("Going to finish.\r\n", SHELL_GetStdio()->stdOut);
              MINT_State = MINT_STATE_GOTO_FINISH;
            } else {
              MINT_GotoLine(); /* set goto line flag */
              MINT_GotoFinish(); /* set goto finish flag */
              CLS1_SendStr("Request sent to goto line (then goto finish).\r\n", SHELL_GetStdio()->stdOut);
              //CLS1_SendStr("ERROR: not on line, cannot go to finish.\r\n", SHELL_GetStdio()->stdErr);
              //MINT_State = MINT_STATE_ERROR;
            }
          }
        }
        break;

      case MINT_STATE_FIND_CENTER: /* find center of area with distance sensors */
#if PL_HAS_DISTANCE_SENSOR
        if (!DIST_DriveToCenter()) {
          /* continue driving to center */
        }
#endif
        break;

      case MINT_STATE_FIND_LINE:
#if PL_HAS_DISTANCE_SENSOR
        if (DIST_MotorDrivingIntoObstacle()!=0) { /* forward/backward check */
          /* obstacle in front of the robot */
          TURN_Turn(TURN_STOP, NULL); /* stop the engines */
          TURN_Turn(TURN_LEFT90, NULL); /* turn around */
          (void)DRV_SetMode(DRV_MODE_SPEED);
        }
#endif
        currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
        if (currLineKind==REF_LINE_NONE) {
          /* continue driving */
        } else { /* found a line? */
          TURN_Turn(TURN_STOP, NULL); /* stop the engines */
          (void)DRV_SetMode(DRV_MODE_NONE);
          CLS1_SendStr("Found line? Position on it...\r\n", SHELL_GetStdio()->stdOut);
          StartMoveToLine();
          MINT_State = MINT_STATE_POSITION_ON_LINE;
        }
        break;

      case MINT_STATE_POSITION_ON_LINE: /* moves robot over the line */
#if PL_HAS_DISTANCE_SENSOR
        if (DIST_MotorDrivingIntoObstacle()!=0) { /* forward/backward check */
          CLS1_SendStr("ERROR: Obstacle while positioning on line?\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
        } else
#endif
        if (REF_GetLineValue(&onLine)==0) { /* no line at all???? */
          CLS1_SendStr("ERROR: Lost line positioning on line?\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
        } else if (!MoveToLine()) {
          /* have moved to line situation, means we have left and right some white areas */
          (void)DRV_SetMode(DRV_MODE_NONE); /* disable drive mode for line following */
          CLS1_SendStr("Going to turn onto line.\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_CENTER_ON_LINE;
        }
        break;

      case MINT_STATE_CENTER_ON_LINE: /* slowly turn on line to get the line into the middle */
#if PL_HAS_DISTANCE_SENSOR
        if (DIST_MotorDrivingIntoObstacle()!=0) { /* forward/backward check */
          CLS1_SendStr("ERROR: Obstacle while center on line?\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
        }
#endif
        lineWidth = REF_LineWidth();
        if (lineWidth<=2000) { /* having line in the middle */
          CLS1_SendStr("Placed robot on line!\r\n", SHELL_GetStdio()->stdOut);
          (void)DRV_SetMode(DRV_MODE_NONE);
        #if PL_HAS_BUZZER
          BUZ_PlayTune(BUZ_TUNE_BUTTON);
        #endif
          notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, TRUE); /* check flags */
          if (notifcationValue&MINT_GOTO_START) {
          #if PL_HAS_MINT_LED
            MINTLED_SetMode(MINTLED_MODE_GOTO_START);
          #endif
            MINT_State = MINT_STATE_GOTO_START;
          } else if (notifcationValue&MINT_GOTO_FINISH) {
          #if PL_HAS_MINT_LED
            MINTLED_SetMode(MINTLED_MODE_GOTO_FINISH);
          #endif
            MINT_State = MINT_STATE_GOTO_FINISH;
          } else {
            MINT_State = MINT_STATE_START_MANUAL; /* go back to manual mode */
          }
        } else if (!LF_MoveOnSegment(tmp.turnLeft)) { /* move/turn robot on line to center it */
          /* not on line any more? */
          TURN_Turn(TURN_STOP, NULL); /* stop the engines */
          CLS1_SendStr("ERROR: Lost line while turning onto line?\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
          continue;
        }
        break;

      case MINT_STATE_GOTO_FINISH:
#if PL_HAS_DISTANCE_SENSOR && MINT_CHECK_TOF_WHILE_LINE_FOLLOWING
        if (DIST_MotorDrivingIntoObstacle()!=0) { /* forward/backward check */
          CLS1_SendStr("ERROR: Obstacle while following line?\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
        }
#endif
        if (!LF_FollowSegment(REF_LINE_KIND_MODE_LINE_FOLLOW, TRUE)) { /* not straight line any more? */
          DRV_SetSpeed(0, 0);
          TURN_Turn(TURN_STOP, NULL); /* stop the engines */
          CLS1_SendStr("Missed the line while going to finish?\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_CHECK_FINISH;
          continue;
        }
        break;

      case MINT_STATE_CHECK_FINISH: /* finish is a simple line end */
        CLS1_SendStr("Checking finish condition.\r\n", SHELL_GetStdio()->stdOut);
        if (IsOnFinishPosition()) { /* no line ==> finish */
          CLS1_SendStr("Finish detected.\r\n", SHELL_GetStdio()->stdOut);
          TURN_Turn(TURN_RIGHT180, NULL); /* turn around */
          currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
          if (currLineKind!=REF_LINE_STRAIGHT) {
            CLS1_SendStr("No Line after turn on finish? Going to manual mode.\r\n", SHELL_GetStdio()->stdErr);
            MINT_State = MINT_STATE_ERROR;
          } else {
            MINT_State = MINT_STATE_FINISH_REACHED;
          }
        } else if (IsOnStartPosition()) { /* wrong end, start area reached which is a full block */
          CLS1_SendStr("Start detected.\r\n", SHELL_GetStdio()->stdOut);
          TURN_Turn(TURN_RIGHT180, NULL); /* turn around */
          currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW); /* must be on line now */
          if (currLineKind==REF_LINE_STRAIGHT) {
            (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following*/
            MINT_State = MINT_STATE_GOTO_FINISH;
          } else {
            CLS1_SendStr("ERROR: After turning on finish not on a line?\r\n", SHELL_GetStdio()->stdErr);
            MINT_State = MINT_STATE_ERROR;
          }
        } else {
          CLS1_SendStr("ERROR: Unknown finish? Going to manual state.\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
        }
        break;

      case MINT_STATE_FINISH_REACHED:
      #if PL_HAS_BUZZER
        BUZ_PlayTune(BUZ_TUNE_BUTTON);
      #endif
        CLS1_SendStr("Finish reached, waiting for ball removal.\r\n", SHELL_GetStdio()->stdOut);
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_POSITION, 2, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
      #if PL_HAS_BUZZER
        BUZ_PlayTune(BUZ_TUNE_BUTTON);
      #endif
      #if PL_HAS_MINT_LED
        MINTLED_SetMode(MINTLED_MODE_WAIT_BALL_REMOVAL);
      #endif
        MINT_State = MINT_STATE_WAIT_FOR_BALL_REMOVAL;
        (void)GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, TRUE); /* clear flags */
        break;

      case MINT_STATE_WAIT_FOR_BALL_REMOVAL:
        notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, FALSE); /* check flags */
        if (notifcationValue!=0) { /* any of the bits set? */
          MINT_State = MINT_STATE_START_AUTOMATIC; /* go into automatic mode, it will handle the bits there */
        } else
#if PL_HAS_MINT_IR
        if (!BallIsIn()) { /* check for ball removal */
#else /* only for button emulation */
        if (SW1_GetVal()==0) { /* key pressed */
#endif
          vTaskDelay(pdMS_TO_TICKS(1000)); /* wait some time */
          if (!BallIsIn()) { /* check for ball removal again */
            CLS1_SendStr("Ball removed!\r\n", SHELL_GetStdio()->stdOut);
            RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_MINT_BALL, 0, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
            currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
            if (currLineKind==REF_LINE_STRAIGHT) {
              CLS1_SendStr("Going to start.\r\n", SHELL_GetStdio()->stdOut);
              (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following*/
            #if PL_HAS_MINT_LED
              MINTLED_SetMode(MINTLED_MODE_GOTO_START);
            #endif
              MINT_State = MINT_STATE_GOTO_START;
            } else {
              CLS1_SendStr("ERROR: No straight line on finish? Going to manual mode.\r\n", SHELL_GetStdio()->stdErr);
              MINT_State = MINT_STATE_ERROR;
            }
          }
        }
        break;

      case MINT_STATE_GOTO_START:
        if (!LF_FollowSegment(REF_LINE_KIND_MODE_LINE_FOLLOW, TRUE)) {
          /* not on straight line any more? */
          TURN_Turn(TURN_STOP, NULL); /* stop the engines */
          CLS1_SendStr("No straight line any more while going to start?\r\n", SHELL_GetStdio()->stdOut);
          MINT_State = MINT_STATE_CHECK_START;
          continue;
        }
        break;

      case MINT_STATE_CHECK_START:
        CLS1_SendStr("Checking start condition.\r\n", SHELL_GetStdio()->stdOut);
        if (IsOnFinishPosition()) { /* wrong end, no line any more ==> this is the finish area */
          CLS1_SendStr("Finish detected.\r\n", SHELL_GetStdio()->stdOut);
          TURN_Turn(TURN_LEFT180, NULL); /* turn around */
          (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following*/
        #if PL_HAS_MINT_LED
          MINTLED_SetMode(MINTLED_MODE_GOTO_START);
        #endif
          MINT_State = MINT_STATE_GOTO_START;
        } else if (IsOnStartPosition()) { /* full line, start reached */
          CLS1_SendStr("Start detected.\r\n", SHELL_GetStdio()->stdOut);
          MINT_State = MINT_STATE_START_REACHED;
        } else {
          CLS1_SendStr("ERROR: Unknown start? Going to manual mode.\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
        }
        break;

      case MINT_STATE_START_REACHED: /* start is a full black area */
      #if PL_HAS_BUZZER
        BUZ_PlayTune(BUZ_TUNE_BUTTON);
      #endif
        CLS1_SendStr("Start reached, waiting for ball.\r\n", SHELL_GetStdio()->stdOut);
        RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_POSITION, 1, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
      #if PL_HAS_BUZZER
        BUZ_PlayTune(BUZ_TUNE_BUTTON);
      #endif
      #if PL_HAS_MINT_LED
        MINTLED_SetMode(MINTLED_MODE_BALL_REQUESTD);
      #endif
        (void)DRV_SetMode(DRV_MODE_STOP);
        MINT_State = MINT_STATE_WAIT_FOR_BALL;
        (void)GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, TRUE); /* clear flags */
        break;

      case MINT_STATE_WAIT_FOR_BALL:
        notifcationValue = GetTaskNotificationBits(MINT_GOTO_START|MINT_GOTO_FINISH|MINT_GOTO_LINE, TRUE); /* check flags */
        if (notifcationValue&MINT_GOTO_FINISH) { /* any of the bits set? */
          currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
          if (currLineKind==REF_LINE_FULL || currLineKind==REF_LINE_RIGHT || currLineKind==REF_LINE_LEFT || currLineKind==REF_LINE_STRAIGHT) { /* full line, finish reached */
            TURN_Turn(TURN_RIGHT180, NULL); /* turn around */
          }
          MINT_GotoFinish(); /* set flags */
          MINT_State = MINT_STATE_START_AUTOMATIC; /* go into automatic mode, it will handle the bits there */
        } else if (!IsOnStartPosition()) { /* not on start any more? */
          CLS1_SendStr("ERROR: not on start area any more?\r\n", SHELL_GetStdio()->stdErr);
          MINT_State = MINT_STATE_ERROR;
        }
        if (BallIsIn()) { /* check for ball */
          vTaskDelay(pdMS_TO_TICKS(1000)); /* wait some time */
          if (BallIsIn()) { /* check for ball again */
            CLS1_SendStr("Ball detected!\r\n", SHELL_GetStdio()->stdOut);
            RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_MINT_BALL, 1, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
         #if PL_HAS_MINT_LED
            MINTLED_SetMode(MINTLED_MODE_BALL_LOADED);
         #endif
            currLineKind = REF_GetLineKind(REF_LINE_KIND_MODE_LINE_FOLLOW);
            if (currLineKind==REF_LINE_FULL || currLineKind==REF_LINE_RIGHT || currLineKind==REF_LINE_LEFT || currLineKind==REF_LINE_STRAIGHT) { /* full line, finish reached */
              TURN_Turn(TURN_RIGHT180, NULL); /* turn around */
              CLS1_SendStr("Going to Finish.\r\n", SHELL_GetStdio()->stdOut);
            #if PL_HAS_MINT_LED
              MINTLED_SetMode(MINTLED_MODE_GOTO_FINISH);
            #endif
              (void)DRV_SetMode(DRV_MODE_NONE); /* disable any drive mode for line following*/
              MINT_State = MINT_STATE_GOTO_FINISH;
            } else {
              CLS1_SendStr("ERROR: not on start area!\r\n", SHELL_GetStdio()->stdErr);
              MINT_State = MINT_STATE_ERROR;
            }
          }
        }
        break;

      default:
        break;
    } /* switch */
    break; /* break for */
  } /* for */
}

static uint8_t MINT_SetPid(void) {
  PID_Config *lineFwPid;
  uint8_t res;

  res = PID_GetPIDConfig(PID_CONFIG_LINE_FW, &lineFwPid);
  if (res!=ERR_OK || lineFwPid==NULL) {
    return ERR_FAILED;
  }
  lineFwPid->maxSpeedPercent = 20;
  lineFwPid->pFactor100 = 3000;
  lineFwPid->iFactor100 = 40;
  lineFwPid->iAntiWindup = 0xffff;
  TURN_SetStepsLine(230, 160);
  return ERR_OK;
}

static void MintTask(void *param) {
  uint32_t notifcationValue;
  int cntr;

  (void)param;
  MINT_SetPid();
  cntr = 0;
  for(;;) {
    Process();
    notifcationValue = GetTaskNotificationBits(MINT_SET_AUTOMATIC_MODE|MINT_SET_MANUAL_MODE, TRUE);
    if (notifcationValue!=0) { /* some bit are set */
      if (notifcationValue&MINT_SET_AUTOMATIC_MODE) {
        MINT_State = MINT_STATE_START_AUTOMATIC;
      }
      if (notifcationValue&MINT_SET_MANUAL_MODE) {
        MINT_State = MINT_STATE_START_MANUAL;
      }
    }
    if (cntr==0) {
      LED1_Off();
      LED2_Off();
    } else if (cntr==20) {
      cntr = 0;
      if (MINT_Mode==MINT_MODE_MANUAL) {
        LED1_Neg();
        LED2_Off();
      } else if (MINT_Mode==MINT_MODE_AUTOMATIC) {
        LED1_Neg(); /* left LED */
        LED2_Neg(); /* right LED */
      }
    }
    cntr++;
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

static void MINT_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"mint", (unsigned char*)"Group of mint commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows mint  help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  mode (auto|manual)", (unsigned char*)"Sets automatic or manual mode\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  goto (line|start|finish)", (unsigned char*)"In automatic mode, go to line, start or finish\r\n", io->stdOut);
}

static void MINT_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr((unsigned char*)"mint", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  mode", MINT_ModeToStr(MINT_Mode), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);

  CLS1_SendStatusStr((unsigned char*)"  state", MINT_StateToStr(MINT_State), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
#if PL_HAS_MINT_IR
  if (BallIsIn()) {
    CLS1_SendStatusStr((unsigned char*)"  ball", (unsigned char*)"present\r\n", io->stdOut);
  } else {
    CLS1_SendStatusStr((unsigned char*)"  ball", (unsigned char*)"not present\r\n", io->stdOut);
  }
#else
  CLS1_SendStatusStr((unsigned char*)"  IR", (unsigned char*)"NOT IMPLEMENTED, push button emulation\r\n", io->stdOut);
#endif
  UTIL1_Num32uToStr(buf, sizeof(buf), MINT_MANUAL_MODE_TIMEOUT_SECONDS);
  UTIL1_strcat(buf, sizeof(buf), " sec timout value.\r\n");
  CLS1_SendStatusStr((unsigned char*)"  timeout", buf, io->stdOut);
  if (MINT_ManualModeTimoutTicks>0) {
    UTIL1_Num32sToStr(buf, sizeof(buf), (xTaskGetTickCount()-MINT_ManualModeTimoutTicks)/configTICK_RATE_HZ);
    UTIL1_strcat(buf, sizeof(buf), " seconds since last timeout reset\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "not running.\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  timeout val", buf, io->stdOut);
#if MINT_USE_REED_POSITION_CONTACT
  UTIL1_Num8uToStr(buf, sizeof(buf), MINT_ReedContactPosition);
  UTIL1_strcat(buf, sizeof(buf), " (0: none, 1: start, 2: finish)\r\n");
  CLS1_SendStatusStr((unsigned char*)"  reed pos", buf, io->stdOut);
#endif
}

uint8_t MINT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"mint help")==0) {
    MINT_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"mint status")==0) {
    MINT_PrintStatus(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"mint mode auto")==0) {
    MINT_SetAutomaticMode();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"mint mode manual")==0) {
    MINT_SetManualMode();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"mint goto line")==0) {
    MINT_GotoLine();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"mint goto start")==0) {
     MINT_GotoStart();
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"mint goto finish")==0) {
     MINT_GotoFinish();
    *handled = TRUE;
  }
  return res;
}

void MINT_Init(void) {
  MINT_Mode = MINT_MODE_MANUAL;
  MINT_State = MINT_STATE_START_MANUAL;
#if PL_HAS_MINT_IR
  IRTX38_SetRatio16(0xffff/2); /* 50% duty ratio */
#endif
  if (xTaskCreate(MintTask, "Mint", configMINIMAL_STACK_SIZE+80, NULL, tskIDLE_PRIORITY+1, &MintTaskHandle) != pdPASS) {
    for(;;){} /* error */
  }
}

#endif /* PL_HAS_MINT */
