

#include "Platform.h"
#include "Application.h"
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#include "FRTOS1.h"
#include "LEDR.h"
#include "LEDG.h"
#if PL_HAS_LED_BLUE
  #include "LEDB.h"
#endif
#include "WAIT1.h"
#include "Shell.h"
#include "Motor.h"
#include "Reflectance.h"
#include "LineFollow.h"
#include "Motor.h"
#if PL_HAS_TSS
  #include "TSS1.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#include "Turn.h"
#if PL_HAS_USER_BUTTON
#include "SW1.h"
#endif
#include "Maze.h"
#if PL_HAS_RADIO
  #include "Radio.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif
#if PL_HAS_QUEUE
  #include "MyQueue.h"
#endif
#if PL_HAS_DISTANCE_SENSOR
  #include "Distance.h"
#endif

typedef enum {
  APP_STATE_INIT,
#if PL_HAS_LINE_SENSOR
  APP_STATE_CALIBRATE,
#endif
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  APP_STATE_FOLLOW_LINE,
#endif
#if PL_APP_FOLLOW_OBSTACLE
  APP_STATE_FOLLOW_OBSTACLE, /* follow obstacle */
#endif
  APP_STATE_IDLE
} AppStateType;

static AppStateType appState = APP_STATE_INIT;
#if PL_APP_FOLLOW_OBSTACLE
static bool followObstacle = FALSE;
#endif
#if PL_APP_AVOID_OBSTACLE
static bool avoidObstacle = FALSE;
#endif

static void StateMachine(bool buttonPress) {
#if PL_HAS_LINE_SENSOR
  static uint8_t cnt;
#endif
  
  switch (appState) {
    case APP_STATE_INIT:
      LEDG_Off();
      LEDR_On();
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
      if (buttonPress) {
        APP_StateStartCalibrate(CLS1_GetStdio()); 
      }
#elif PL_APP_FOLLOW_OBSTACLE
      appState = APP_STATE_IDLE;
#endif
      break;
#if PL_APP_FOLLOW_OBSTACLE
    case APP_STATE_FOLLOW_OBSTACLE:
      cnt++;
      if (cnt>50) {
        cnt = 0;
        LEDR_Neg();
      }
      if (buttonPress) {
        followObstacle = FALSE;
        appState = APP_STATE_IDLE;
      }
      break;
#endif
#if PL_HAS_LINE_SENSOR
    case APP_STATE_CALIBRATE:
      cnt++;
      if (cnt>50) {
        cnt = 0;
        LEDR_Neg();
      }
      if (buttonPress) {
        APP_StateStopCalibrate(CLS1_GetStdio()); 
      }
      break;
#endif
    case APP_STATE_IDLE:
      LEDR_Off();
      LEDG_On();
      if (buttonPress) {
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
        LF_StartFollowing();
        appState = APP_STATE_FOLLOW_LINE;
#elif PL_APP_FOLLOW_OBSTACLE
        followObstacle = TRUE;
        appState = APP_STATE_FOLLOW_OBSTACLE;
#endif
      }
      break;
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
    case APP_STATE_FOLLOW_LINE:
      LEDR_Off();
      LEDG_Off();
      if (!LF_IsFollowing()) {
        appState = APP_STATE_IDLE;
      }
      if (buttonPress) {
        LF_StopFollowing(); 
        appState = APP_STATE_IDLE;
      }
      break;
#endif
  } /* switch */
}

void APP_StateStartCalibrate(const CLS1_StdIOType *io) {
#if PL_HAS_LINE_SENSOR
  REF_Calibrate(TRUE, io);
  appState = APP_STATE_CALIBRATE;
#endif
}

void APP_StateStopCalibrate(const CLS1_StdIOType *io) {
  appState = APP_STATE_IDLE;
#if PL_HAS_LINE_SENSOR
  REF_Calibrate(FALSE, io);
#endif
}

#if PL_APP_AVOID_OBSTACLE
static void AvoidObstacle(void) {
  if (DIST_10cmLeftOn() && DIST_5cmLeftOn() && !DIST_10cmRightOn() && !DIST_5cmRightOn()) {
    /* turn right */
    TURN_TurnAngle(10);
  } else if (!DIST_10cmLeftOn() && !DIST_5cmLeftOn() && DIST_10cmRightOn() && DIST_5cmRightOn()) {
    /* turn left */
    TURN_TurnAngle(-10);
  }
}
#endif

#if PL_APP_FOLLOW_OBSTACLE
static void FollowObstacle(void) {
  #define DUTY_SLOW   16
  #define DUTY_MEDIUM 20
  #define DUTY_FAST   23
  static uint8_t cnt;
  uint16_t cm, us;
  
  cnt++; /* get called with 100 Hz, reduce to 10 Hz */
  if (cnt==10) {
    us = US_Measure_us();
    cnt = 0;
    if (followObstacle) {
      cm = US_usToCentimeters(us, 22);
      if (cm<10) { /* back up! */
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -DUTY_SLOW);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -DUTY_SLOW);
      } else if (cm>=10 && cm<=20) { /* stand still */
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
        //TURN_Turn(TURN_RIGHT45); /* try to avoid obstacle */
      } else if (cm>20 && cm<=40) { /* forward slowly */
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), DUTY_MEDIUM);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), DUTY_MEDIUM);
      } else if (cm>40 && cm<60) { /* forward fast */
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), DUTY_FAST);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), DUTY_FAST);
      } else { /* nothing in range */
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
      }
    }
  }
}
#endif

#if PL_HAS_LINE_SENSOR
static uint8_t AutoCalibrateReflectance(const CLS1_StdIOType *io) {
  CLS1_SendStr((unsigned char*)"start auto-calibration...\r\n", io->stdOut);
  /* perform automatic calibration */
  APP_StateStartCalibrate(io);
  TURN_Turn(TURN_LEFT90);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_RIGHT90);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_RIGHT90);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_LEFT90);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_STOP);
  APP_StateStopCalibrate(io);
  CLS1_SendStr((unsigned char*)"auto-calibration finished.\r\n", io->stdOut);
  return ERR_OK;
}
#endif

static void CheckButton(void) {
#if PL_HAS_USER_BUTTON
  uint32_t timeTicks; /* time in ticks */
  #define BUTTON_CNT_MS  100  /* iteration count for button */
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  bool autoCalibrate = FALSE;
#endif
  
  if (SW1_GetVal()==0) { /* button pressed */
    /* short press (1 beep): start or stop line following if calibrated 
     * 1 s press   (2 beep): calibrate manually
     * 2 s press   (3 beep): calibrate with auto-move
     * 3 s press   (4 beep or more): clear path
     * */
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS); /* simple debounce */
    if (SW1_GetVal()==0) { /* still pressed */
      LEDG_On();
      timeTicks = 0;
      while(SW1_GetVal()==0 && timeTicks<=6000/BUTTON_CNT_MS) { 
        FRTOS1_vTaskDelay(BUTTON_CNT_MS/portTICK_RATE_MS);
        if ((timeTicks%(1000/BUTTON_CNT_MS))==0) {
#if PL_HAS_BUZZER
          (void)BUZ_Beep(300, 200);
#endif
        }
        timeTicks++;
      } /* wait until released */
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
      autoCalibrate = FALSE;
#endif
      if (timeTicks<1000/BUTTON_CNT_MS) { /* less than 1 second */
        CLS1_SendStr((unsigned char*)"button press.\r\n", CLS1_GetStdio()->stdOut);
        StateMachine(TRUE); /* <1 s, short button press, according to state machine */
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
      } else if (timeTicks>=(1000/BUTTON_CNT_MS) && timeTicks<(2000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"calibrate.\r\n", CLS1_GetStdio()->stdOut);
        APP_StateStartCalibrate(CLS1_GetStdio()); /* 1-2 s: start calibration by hand */
      } else if (timeTicks>=(2000/BUTTON_CNT_MS) && timeTicks<(3000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"auto calibrate.\r\n", CLS1_GetStdio()->stdOut);
        APP_StateStartCalibrate(CLS1_GetStdio()); /* 2-3 s: start auto calibration */
        autoCalibrate = TRUE;
#endif
#if PL_APP_LINE_MAZE
      } else if (timeTicks>=(3000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"delete solution.\r\n", CLS1_GetStdio()->stdOut);
        MAZE_ClearSolution();
#endif
      }
      while (SW1_GetVal()==0) { /* wait until button is released */
        FRTOS1_vTaskDelay(BUTTON_CNT_MS/portTICK_RATE_MS);
      }
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
      if (autoCalibrate) {
        /* perform automatic calibration */
        WAIT1_WaitOSms(1500); /* wait some time so the user can remove the hand from the button */
        AutoCalibrateReflectance(CLS1_GetStdio());
      }
#endif
    }
  } /* if */
#endif
}

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* not used */
#if PL_HAS_TSS
  Configure(); /* initialize TSS library */
#endif
  for(;;) {
#if PL_HAS_TSS
    TSS_Task(); /* call TSS library to process touches */
#else
    CheckButton();
#endif
#if PL_APP_AVOID_OBSTACLE
    AvoidObstacle();
#endif
#if PL_APP_FOLLOW_OBSTACLE
    FollowObstacle();
#elif PL_HAS_ULTRASONIC
    (void)US_Measure_us(); /* only measure, so we have it for the status */
#endif
#if PL_HAS_LED_BLUE
    LEDB_Neg();
#endif
#if PL_HAS_RADIO
    (void)RADIO_Handle();
#endif
#if PL_HAS_EVENTS
    EVNT_HandleEvent(RADIO_AppHandleEvent);
#endif
    StateMachine(FALSE);
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

static uint8_t APP_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of app commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
#if PL_APP_FOLLOW_OBSTACLE
  CLS1_SendHelpStr((unsigned char*)"  follow (on|off)", (unsigned char*)"Obstacle following on or off\r\n", io->stdOut);
#endif
#if PL_APP_AVOID_OBSTACLE
  CLS1_SendHelpStr((unsigned char*)"  avoid (on|off)", (unsigned char*)"Obstacle avoidance on or off\r\n", io->stdOut);
#endif
#if PL_HAS_LINE_SENSOR
  CLS1_SendHelpStr((unsigned char*)"  autocalib", (unsigned char*)"Automatically calibrate line sensor\r\n", io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t APP_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
#if PL_APP_ACCEL_CONTROL
  CLS1_SendStatusStr((unsigned char*)"  mode", (unsigned char*)"ACCEL_CONTROL\r\n", io->stdOut);
#endif
#if  PL_APP_LINE_FOLLOWING
  CLS1_SendStatusStr((unsigned char*)"  mode", (unsigned char*)"LINE_FOLLOWING\r\n", io->stdOut);
#endif
#if PL_APP_LINE_MAZE
  CLS1_SendStatusStr((unsigned char*)"  mode", (unsigned char*)"LINE_MAZE\r\n", io->stdOut);
#endif
#if PL_APP_FOLLOW_OBSTACLE
  CLS1_SendStatusStr((unsigned char*)"  follow", followObstacle?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#endif
#if PL_HAS_USER_BUTTON
  CLS1_SendStatusStr((unsigned char*)"  button", SW1_GetVal()!=0?(unsigned char*)"pressed\r\n":(unsigned char*)"released\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"app help")==0) {
    *handled = TRUE;
    return APP_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"app status")==0) {
    *handled = TRUE;
    return APP_PrintStatus(io);
#if PL_HAS_LINE_SENSOR
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app autocalib")==0) {
    *handled = TRUE;
    return AutoCalibrateReflectance(io);
#endif
#if PL_APP_AVOID_OBSTACLE
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app avoid on")==0) {
    avoidObstacle = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app avoi off")==0) {
    avoidObstacle = FALSE;
    *handled = TRUE;
#endif
#if PL_APP_FOLLOW_OBSTACLE
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app follow on")==0) {
    followObstacle = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app follow off")==0) {
    followObstacle = FALSE;
    *handled = TRUE;
#endif
  }
  return res;
}

void APP_Run(void) {
  appState = APP_STATE_INIT;
  MOT_Init();
  SHELL_Init();
#if PL_HAS_LINE_SENSOR
  REF_Init();
  LF_Init();
  TURN_Init();
#endif
#if PL_HAS_ULTRASONIC
  US_Init();
#endif
#if PL_HAS_BUZZER
  BUZ_Init();
#endif
#if PL_HAS_EVENTS
  EVNT_Init();
#endif
#if PL_HAS_RADIO
  RADIO_Init();
#endif
#if PL_HAS_REMOTE
  REMOTE_Init();
#endif
#if PL_HAS_QUEUE
  QUEUE_Init();
#endif
#if PL_HAS_DISTANCE_SENSOR
  DIST_Init();
#endif
  if (FRTOS1_xTaskCreate(MainTask, (signed portCHAR *)"Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}
