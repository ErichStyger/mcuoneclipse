

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
#if PL_USE_TSS
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
  APP_STATE_CALIBRATE,
  APP_STATE_IDLE,
  APP_STATE_FOLLOW
} AppStateType;

static AppStateType appState = APP_STATE_INIT;

static void StateMachine(bool buttonPress) {
  static uint8_t cnt;
  
  switch (appState) {
    case APP_STATE_INIT:
      LEDG_Off();
      LEDR_On();
      if (buttonPress) {
        APP_StateStartCalibrate(); 
      }
      break;
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
    case APP_STATE_IDLE:
      LEDR_Off();
      LEDG_On();
#if PL_HAS_LINE_SENSOR
      if (buttonPress) {
        LF_StartFollowing();
        appState = APP_STATE_FOLLOW;
      }
#endif
      break;
    case APP_STATE_FOLLOW:
      LEDR_Off();
      LEDG_Off();
#if PL_HAS_LINE_SENSOR
      if (!LF_IsFollowing()) {
        appState = APP_STATE_IDLE;
      }
#endif
      if (buttonPress) {
#if PL_HAS_LINE_SENSOR
        LF_StopFollowing(); 
#endif
        appState = APP_STATE_IDLE;
      }
      break;
  } /* switch */
}

void APP_StateStartCalibrate(void) {
#if PL_HAS_LINE_SENSOR
  REF_Calibrate(TRUE);
  appState = APP_STATE_CALIBRATE;
#endif
}

void APP_StateStopCalibrate(void) {
  appState = APP_STATE_IDLE;
#if PL_HAS_LINE_SENSOR
  REF_Calibrate(FALSE);
#endif
}


#if PL_APP_FOLLOW_OBSTACLE
static bool runIt = TRUE;

static void FollowObstacle(void) {
  uint16_t cm, us;
  
  LEDR_Neg();
  us = US_Measure_us();
  cm = US_usToCentimeters(us, 22);
  if (runIt && cm != 0) {
    if (cm<10) { /* back up! */
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -20);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), -20);
    } else if (cm>=10 && cm<=15) { /* stand still */
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
    } else if (cm>15 && cm<=40) { /* forward slowly */
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 30);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 30);
    } else if (cm>40 && cm<80) { /* forward fast */
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 50);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 50);
    } else { /* nothing in range */
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
      MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
    }
  }
}
#endif

static void CheckButton(void) {
#if PL_HAS_USER_BUTTON
  uint32_t timeTicks; /* time in ticks */
  #define BUTTON_CNT_MS  100  /* iteration count for button */
#if PL_HAS_LINE_SENSOR
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
#if PL_HAS_LINE_SENSOR
      autoCalibrate = FALSE;
      if (timeTicks<1000/BUTTON_CNT_MS) { /* less than 1 second */
        CLS1_SendStr((unsigned char*)"button press.\r\n", CLS1_GetStdio()->stdOut);
        StateMachine(TRUE); /* <1 s, short button press, according to state machine */
      } else if (timeTicks>=(1000/BUTTON_CNT_MS) && timeTicks<(2000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"calibrate.\r\n", CLS1_GetStdio()->stdOut);
        APP_StateStartCalibrate(); /* 1-2 s: start calibration by hand */
      } else if (timeTicks>=(2000/BUTTON_CNT_MS) && timeTicks<(3000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"auto calibrate.\r\n", CLS1_GetStdio()->stdOut);
        APP_StateStartCalibrate(); /* 2-3 s: start auto calibration */
        autoCalibrate = TRUE;
#if PL_APP_MAZE_LINE_SOLVING
      } else if (timeTicks>=(3000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"delete solution.\r\n", CLS1_GetStdio()->stdOut);
        MAZE_ClearSolution();
#endif
      } 
#endif
      while (SW1_GetVal()==0) { /* wait until button is released */
        FRTOS1_vTaskDelay(BUTTON_CNT_MS/portTICK_RATE_MS);
      }
#if PL_HAS_LINE_SENSOR
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
#if PL_USE_TSS
  Configure(); /* initialize TSS library */
#endif
  for(;;) {
#if PL_USE_TSS
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
#if PL_HAS_LINE_SENSOR
    StateMachine(FALSE);
#endif
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
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
