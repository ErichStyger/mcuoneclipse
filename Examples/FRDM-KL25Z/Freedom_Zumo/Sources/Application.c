

#include "Platform.h"
#include "Application.h"
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#include "FRTOS1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "WAIT1.h"
#include "Shell.h"
#include "Motor.h"
#include "Reflectance.h"
#include "LineFollow.h"
#if PL_USE_TSS
  #include "TSS1.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#include "Turn.h"
#include "SW1.h"
#include "Maze.h"

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
      if (buttonPress) {
        LF_StartFollowing();
        appState = APP_STATE_FOLLOW;
      }
      break;
    case APP_STATE_FOLLOW:
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
  } /* switch */
}


void APP_StateStartCalibrate(void) {
  REF_Calibrate(TRUE);
  appState = APP_STATE_CALIBRATE;
}

void APP_StateStopCalibrate(void) {
  appState = APP_STATE_IDLE;
  REF_Calibrate(FALSE);
}


#if 0
static uint8_t MeasureCm(void) {
  uint16_t us, cm;
  uint8_t buf[8];

  us = US_Measure_us();
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), us, ' ', 5);
  //LCD1_GotoXY(1,5);
  //LCD1_WriteString((char*)buf);

  cm = US_usToCentimeters(us, 22);
  UTIL1_Num16uToStrFormatted(buf, sizeof(buf), cm, ' ', 5);
  //LCD1_GotoXY(2,5);
  //LCD1_WriteString((char*)buf);
  
  LEDR_Put(cm>0 && cm<10); /* red LED if object closer than 10 cm */
//  LEDB_Put(cm>=10&&cm<=100); /* blue LED if object is in 10..100 cm range */
  LEDG_Put(cm>=10); /* blue LED if object is in 10..100 cm range */
  return cm;
}

static bool runIt = TRUE;

static portTASK_FUNCTION(RoboTask, pvParameters) {
  uint16_t cm;
  
  (void)pvParameters; /* not used */
  for(;;) {
    cm = MeasureCm();
    LEDR_Neg();
    if (runIt && cm != 0) {
      if (cm<10) { /* back up! */
        MOT_SetSpeedPercent(MOT_GetMotorA(), -40);
        MOT_SetSpeedPercent(MOT_GetMotorB(), -40);
      } else if (cm>=10 && cm<=15) {
        /* stand still */
        MOT_SetSpeedPercent(MOT_GetMotorA(), 0);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 0);
      } else if (cm>15 && cm<=40) {
        MOT_SetSpeedPercent(MOT_GetMotorA(), 50);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 50);
      } else if (cm>40 && cm<80) {
        MOT_SetSpeedPercent(MOT_GetMotorA(), 80);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 80);
      } else { /* nothing in range */
        MOT_SetSpeedPercent(MOT_GetMotorA(), 0);
        MOT_SetSpeedPercent(MOT_GetMotorB(), 0);
      }
    }
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}
#endif

static void CheckButton(void) {
  uint32_t timeTicks; /* time in ticks */
  #define BUTTON_CNT_MS  100  /* iteration count for button */
  bool autoCalibrate = FALSE;

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
          BUZ_Beep(300, 200);
        }
        timeTicks++;
      } /* wait until released */
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
      } else if (timeTicks>=(3000/BUTTON_CNT_MS)) {
        CLS1_SendStr((unsigned char*)"delete solution.\r\n", CLS1_GetStdio()->stdOut);
        MAZE_ClearSolution();
      } 
      while (SW1_GetVal()==0) { /* wait until button is released */
        FRTOS1_vTaskDelay(BUTTON_CNT_MS/portTICK_RATE_MS);
      }
      if (autoCalibrate) {
        CLS1_SendStr((unsigned char*)"start auto-calibration...\r\n", CLS1_GetStdio()->stdOut);
        /* perform automatic calibration */
        WAIT1_WaitOSms(1500); /* wait some time */
        TURN_Turn(TURN_LEFT90, FALSE);
        WAIT1_WaitOSms(500); /* wait some time */
        TURN_Turn(TURN_RIGHT90, FALSE);
        WAIT1_WaitOSms(100); /* wait some time */
        TURN_Turn(TURN_RIGHT90, FALSE);
        WAIT1_WaitOSms(500); /* wait some time */
        TURN_Turn(TURN_LEFT90, FALSE);
        APP_StateStopCalibrate();
        CLS1_SendStr((unsigned char*)"auto-calibration finished.\r\n", CLS1_GetStdio()->stdOut);
      }
    }
  } /* if */
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
    LEDB_Neg();
    StateMachine(FALSE);
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  appState = APP_STATE_INIT;
  REF_Init();
  MOT_Init();
  SHELL_Init();
  LF_Init();
  TURN_Init();
#if 0
  US_Init();
#endif
#if PL_HAS_BUZZER
  BUZ_Init();
#endif
  if (FRTOS1_xTaskCreate(MainTask, (signed portCHAR *)"Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}
