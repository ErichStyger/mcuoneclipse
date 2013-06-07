

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

typedef enum {
  APP_STATE_INIT,
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  APP_STATE_CALIBRATE,
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

static void StateMachine(bool buttonPress) {
#if PL_APP_FOLLOW_OBSTACLE || PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  static uint8_t cnt;
#endif
  
  switch (appState) {
    case APP_STATE_INIT:
      LEDG_Off();
      LEDR_On();
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
      if (buttonPress) {
        APP_StateStartCalibrate(); 
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
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
    case APP_STATE_CALIBRATE:
      cnt++;
      if (cnt>50) {
        cnt = 0;
        LEDR_Neg();
      }
      if (buttonPress) {
        APP_StateStopCalibrate(); 
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

void APP_StateStartCalibrate(void) {
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  REF_Calibrate(TRUE);
  appState = APP_STATE_CALIBRATE;
#endif
}

void APP_StateStopCalibrate(void) {
  appState = APP_STATE_IDLE;
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  REF_Calibrate(FALSE);
#endif
}


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
        TURN_Turn(TURN_RIGHT45); /* try to avoid obstacle */
      } else if (cm>20 && cm<=40) { /* forward slowly */
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), DUTY_MEDIUM);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), DUTY_MEDIUM);
      } else if (cm>40 && cm<100) { /* forward fast */
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
          BUZ_Beep(300, 200);
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
        APP_StateStartCalibrate(); /* 1-2 s: start calibration by hand */
      } else if (timeTicks>=(2000/BUTTON_CNT_MS) && timeTicks<(3000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"auto calibrate.\r\n", CLS1_GetStdio()->stdOut);
        APP_StateStartCalibrate(); /* 2-3 s: start auto calibration */
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
        CLS1_SendStr((unsigned char*)"start auto-calibration...\r\n", CLS1_GetStdio()->stdOut);
        /* perform automatic calibration */
        WAIT1_WaitOSms(1500); /* wait some time */
        TURN_Turn(TURN_LEFT90);
        TURN_Turn(TURN_RIGHT90);
        TURN_Turn(TURN_RIGHT90);
        TURN_Turn(TURN_LEFT90);
        TURN_Turn(TURN_STOP);
        APP_StateStopCalibrate();
        CLS1_SendStr((unsigned char*)"auto-calibration finished.\r\n", CLS1_GetStdio()->stdOut);
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
#if PL_APP_FOLLOW_OBSTACLE
    FollowObstacle();
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

static void APP_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of app commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
#if PL_APP_FOLLOW_OBSTACLE
  CLS1_SendHelpStr((unsigned char*)"  follow (on|off)", (unsigned char*)"Obstacle following on or off\r\n", io->stdOut);
#endif
}

static void APP_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
#if PL_APP_FOLLOW_OBSTACLE
  CLS1_SendStatusStr((unsigned char*)"  follow", followObstacle?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#endif
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"app help")==0) {
    APP_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"app status")==0) {
    APP_PrintStatus(io);
    *handled = TRUE;
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
  if (FRTOS1_xTaskCreate(MainTask, (signed portCHAR *)"Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}
