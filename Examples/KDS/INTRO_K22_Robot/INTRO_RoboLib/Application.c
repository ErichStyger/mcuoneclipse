#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#if PL_HAS_LED_RED
  #include "LEDR.h"
#endif
#if PL_HAS_LED_GREEN
  #include "LEDG.h"
#endif
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
#if PL_HAS_USER_LED
  #include "LED1.h"
#endif
#if PL_HAS_USER_LED2
  #include "LED2.h"
#endif
#include "Maze.h"
#if PL_HAS_RADIO
  #include "RStack.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif
#if PL_HAS_SHELL_QUEUE
  #include "ShellQueue.h"
#endif
#if PL_HAS_DISTANCE_SENSOR
  #include "Distance.h"
#endif
#if PL_HAS_ACCEL_SENSOR
  #include "Accel.h"
  #include "MMA1.h"
#endif
#if PL_APP_SUMO
  #include "Sumo.h"
#endif
#if PL_HAS_PID
  #include "PID.h"
#endif
#if PL_HAS_EVENTS
 #include "Event.h"
#endif
#if PL_HAS_TEST
  #include "Test.h"
#endif
#if configUSE_TRACE_HOOKS
  #include "PTRC1.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
  #include "RNet_App.h"
#endif
#if PL_HAS_SHELL_TRACE
  #include "ShellTrace.h"
#endif
#if PL_HAS_FREEMASTER
  #include "FMSTR1.h"
#endif
#if PL_HAS_DRIVE
  #include "Drive.h"
#endif
#if PL_HAS_I2C_SPY
  #include "I2CSPY1.h"
#endif
#if PL_HAS_MCP4728
  #include "MCP4728.h"
#endif
#if PL_CONFIG_HAS_BATTERY_ADC
  #include "Battery.h"
#endif
#if PL_HAS_ROBO_SHIELD
  #include "RoboShield.h"
#endif
#if PL_HAS_MUSIC_SHIELD
  #include "Music.h"
#endif
#if PL_HAS_SPI
  #include "SPI.h"
#endif
#if PL_HAS_LASER
  #include "Laser.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_CONFIG_HAS_IDENTIFY
  #include "Identify.h"
#endif
#if PL_HAS_MINT
  #include "MintRobot.h"
#endif
#if PL_HAS_MINT_REMOTE
  #include "MintRemote.h"
#endif
#if PL_HAS_MINT_LED
  #include "MintLed.h"
#endif
#if PL_HAS_TOF_SENSOR
  #include "VL6180X.h"
#endif
#if PL_CONFIG_HAS_NVM_CONFIG
  #include "NVM_Config.h"
#endif
#if PL_CONFIG_HAS_LCD
  #include "LCD.h"
  #include "GDisp1.h"
#endif
#include "Event.h"
#include "Keys.h"
#include "KeyDebounce.h"
#include "KIN1.h"
#if PL_HAS_MIDI
  #include "MidiMusic.h"
#endif

typedef enum {
  APP_STATE_STARTUP,
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
#if PL_DO_MIDI
  APP_STATE_PLAY_MIDI,
#endif
#if PL_APP_SUMO
  APP_STATE_RUN_SUMO, /* Sumo fight */
#endif
  APP_STATE_IDLE
} AppStateType;

static AppStateType appState = APP_STATE_STARTUP;
#if PL_APP_FOLLOW_OBSTACLE
static bool followObstacle = FALSE;
#endif
#if PL_APP_AVOID_OBSTACLE
static bool avoidObstacle = FALSE;
#endif

void APP_DebugPrint(unsigned char *str) {
#if PL_CONFIG_HAS_SHELL
  SHELL_SendString(str);
#endif
}

#if PL_CONFIG_HAS_SHELL
static unsigned char *AppStateString(AppStateType state) {
  switch(state) {
    case APP_STATE_STARTUP: return (unsigned char*)"STARTUP";
    case APP_STATE_INIT: return (unsigned char*)"INIT";
  #if PL_HAS_LINE_SENSOR
    case APP_STATE_CALIBRATE: return (unsigned char*)"CALIBRATE";
  #endif
  #if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
    case APP_STATE_FOLLOW_LINE: return (unsigned char*)"FOLLOW_LINE";
  #endif
  #if PL_APP_FOLLOW_OBSTACLE
    case APP_STATE_FOLLOW_OBSTACLE: return (unsigned char*)"FOLLOW_OBSTACLE";
  #endif
  #if PL_DO_MIDI
    case APP_STATE_PLAY_MIDI: return (unsigned char*)"PLAY_MIDI";
  #endif
  #if PL_APP_SUMO
    case APP_STATE_RUN_SUMO: return (unsigned char*)"RUN_SUMO";
  #endif
    case APP_STATE_IDLE: return (unsigned char*)"IDLE";
    default:
      break;
  }
  return (unsigned char*)"unknown?";
}
#endif

static void StateMachine(bool buttonPress) {
#if PL_HAS_LINE_SENSOR
  static uint8_t cnt;
#endif
  
  switch (appState) {
    case APP_STATE_STARTUP:
#if PL_HAS_BUZZER && PL_DO_MINT
      BUZ_PlayTune(BUZ_TUNE_BUTTON); /* only short beep */
#elif PL_HAS_BUZZER
      BUZ_Beep(300, 800);
      //BUZ_PlayTune(BUZ_TUNE_WELCOME);
#endif
#if PL_HAS_MUSIC_POWERUP
      WAIT1_WaitOSms(300);
      MUSIC_PlayTheme(MUSIC_THEME_IMPERIAL);
#endif
      appState = APP_STATE_INIT;
      break;

    case APP_STATE_INIT:
#if PL_HAS_LED_GREEN
      LEDG_Off();
#endif
#if PL_HAS_LED_RED
      LEDR_On();
#endif
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE || PL_APP_SUMO
      if (REF_CanUseSensor()) {
        appState = APP_STATE_IDLE;
      }
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
#if PL_HAS_LED_RED
        LEDR_Neg();
#endif
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
#if PL_HAS_LED_RED
        LEDR_Neg();
#endif
      }
      if (buttonPress) {
        APP_StateStopCalibrate(); 
      }
      break;
#endif

    case APP_STATE_IDLE:
#if PL_HAS_LED_RED
      LEDR_Off();
#endif
#if PL_HAS_LED_GREEN
      LEDG_On();
#endif
      if (buttonPress) {
#if (PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE) && !PL_APP_MINT /* Mint application handles buttons itself */
        if (LF_IsFollowing()) {
          LF_StopFollowing();
          appState = APP_STATE_IDLE;
        } else {
          LF_StartFollowing();
          appState = APP_STATE_FOLLOW_LINE;
        }
#elif PL_APP_FOLLOW_OBSTACLE
        followObstacle = TRUE;
        appState = APP_STATE_FOLLOW_OBSTACLE;
#elif 0 && PL_DO_MIDI
        MM_PlayMusic(-1); /* play current song */
        appState = APP_STATE_PLAY_MIDI;
#elif PL_APP_SUMO
        SUMO_StartCountdown();
        appState = APP_STATE_RUN_SUMO;
#endif
#if PL_HAS_MUSIC_START_SUMO
        MUSIC_PlayTheme(MUSIC_THEME_DARK_SIDE);
#endif
      }
      break;
      
#if 0 && PL_DO_MIDI
    case APP_STATE_PLAY_MIDI:
      if (buttonPress || !MM_IsPlaying()) {
        MM_StopPlaying();
        appState = APP_STATE_IDLE;
      }
      break;
#endif

#if PL_APP_SUMO
    case APP_STATE_RUN_SUMO:
#if PL_IS_INTRO_ZUMO_K22 || PL_IS_INTRO_ZUMO_K22_V2
      /* no LED signaling */
#else
  #if PL_HAS_LED_RED
      LEDR_Off();
  #endif
  #if PL_HAS_LED_GREEN
      LEDG_Off();
  #endif
#endif
      if (!SUMO_IsDoingSumo()) {
        appState = APP_STATE_IDLE;
      } else {
#if PL_HAS_MUSIC_RUN_SUMO
        if (!MUSIC_IsPlaying()) {
          MUSIC_PlayTheme(MUSIC_THEME_BREATHING);
        }
#endif
      }
      if (buttonPress) {
        SUMO_StopSumo();
        appState = APP_STATE_IDLE;
      }
      break;
#endif
      
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
    case APP_STATE_FOLLOW_LINE:
#if PL_HAS_LED_RED
      LEDR_Off();
#endif
#if PL_HAS_LED_GREEN
      LEDG_Off();
#endif
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
#if PL_HAS_LINE_SENSOR
  REF_CalibrateStartStop();
  appState = APP_STATE_CALIBRATE;
#endif
}

bool APP_StateIsCalibrating(void) {
#if PL_HAS_LINE_SENSOR
  return appState == APP_STATE_CALIBRATE;
#else
  return FALSE;
#endif
}

void APP_StateStopCalibrate(void) {
  appState = APP_STATE_IDLE;
#if PL_HAS_LINE_SENSOR
  REF_CalibrateStartStop();
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
  //uint16_t cm, us;
  
  cnt++; /* get called with 100 Hz, reduce to 10 Hz */
  if (cnt==10) {
    //us = US_Measure_us();
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

#if PL_HAS_LINE_SENSOR && PL_HAS_TURN 
static uint8_t AutoCalibrateReflectance(void) {
#if PL_CONFIG_HAS_SHELL
  SHELL_SendString((unsigned char*)"start auto-calibration...\r\n");
#endif
  /* perform automatic calibration */
  APP_StateStartCalibrate();
  TURN_Turn(TURN_LEFT90, NULL);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_RIGHT90, NULL);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_RIGHT90, NULL);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_LEFT90, NULL);
  WAIT1_WaitOSms(500); /* wait some time */
  TURN_Turn(TURN_STOP, NULL);
  APP_StateStopCalibrate();
#if PL_CONFIG_HAS_SHELL
  SHELL_SendString((unsigned char*)"auto-calibration finished.\r\n");
#endif
  return ERR_OK;
}
#endif

#if 0 /* do not use this any more, use proper debouncing! */
static void CheckButton(void) {
#if PL_HAS_USER_BUTTON
  uint32_t timeTicks; /* time in ticks */
  #define BUTTON_CNT_MS  100  /* iteration count for button */
#if PL_HAS_LINE_SENSOR && PL_HAS_TURN 
  bool autoCalibrate = FALSE;
#endif
  
  if (SW1_GetVal()==0) { /* button pressed */
    /* short press (1 beep): start or stop line following if calibrated 
     * 1 s press   (2 beep): calibrate manually
     * 2 s press   (3 beep): calibrate with auto-move
     * 3 s press   (4 beep or more): clear path
     * */
    FRTOS1_vTaskDelay(50/portTICK_PERIOD_MS); /* simple debounce */
    if (SW1_GetVal()==0) { /* still pressed */
#if PL_HAS_LED_GREEN
      LEDG_On();
#endif
      timeTicks = 0;
      while(SW1_GetVal()==0 && timeTicks<=6000/BUTTON_CNT_MS) { 
        FRTOS1_vTaskDelay(BUTTON_CNT_MS/portTICK_PERIOD_MS);
        if ((timeTicks%(1000/BUTTON_CNT_MS))==0) {
#if PL_HAS_BUZZER
          (void)BUZ_Beep(300, 500);
#elif PL_HAS_LED_GREEN
          LEDG_Neg();
#endif
        }
        timeTicks++;
      } /* wait until released */
#if PL_HAS_LINE_SENSOR && PL_HAS_TURN 
      autoCalibrate = FALSE;
#endif
      if (timeTicks<1000/BUTTON_CNT_MS) { /* less than 1 second */
#if PL_CONFIG_HAS_SHELL
        SHELL_SendString((unsigned char*)"button press.\r\n");
#endif
        StateMachine(TRUE); /* <1 s, short button press, according to state machine */
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE || PL_APP_SUMO
      } else if (timeTicks>=(1000/BUTTON_CNT_MS) && timeTicks<(2000/BUTTON_CNT_MS)) {
#if PL_CONFIG_HAS_SHELL
        SHELL_SendString((unsigned char*)"calibrate.\r\n");
#endif
        APP_StateStartCalibrate(); /* 1-2 s: start calibration by hand */
      } else if (timeTicks>=(2000/BUTTON_CNT_MS) && timeTicks<(3000/BUTTON_CNT_MS)) {
#if PL_CONFIG_HAS_SHELL
        SHELL_SendString((unsigned char*)"auto calibrate.\r\n");
#endif
        autoCalibrate = TRUE; /* 2-3 s: start auto calibration */
#endif
#if PL_APP_LINE_MAZE
      } else if (timeTicks>=(3000/BUTTON_CNT_MS)) {
        MAZE_ClearSolution();
        SHELL_SendString((unsigned char*)"Deleted solution.\r\n");
#if PL_HAS_BUZZER
        WAIT1_WaitOSms(500);
        (void)BUZ_Beep(300, 100);
        WAIT1_WaitOSms(100);
#endif
        #endif
      }
      while (SW1_GetVal()==0) { /* wait until button is released */
        FRTOS1_vTaskDelay(BUTTON_CNT_MS/portTICK_PERIOD_MS);
      }
#if PL_HAS_LINE_SENSOR && PL_HAS_TURN 
      if (autoCalibrate) {
        /* perform automatic calibration */
        WAIT1_WaitOSms(1500); /* wait some time so the user can remove the finger from the button */
        (void)AutoCalibrateReflectance();
      }
#endif
    }
  } /* if */
#endif
}
#endif

#if PL_HAS_ACCEL_STOP
static void CheckAccelerometer(void) {
  int16_t x, y, z;
  bool isEnabled;
  uint8_t res;
  static uint8_t cnt = 0;

#if PL_HAS_ACCEL_STOP_INVERTED /* board with sensor mounted head-over */
  #define ACCEL_OK_CONDITION(x,y,z) ((z)<0)
#else
  #define ACCEL_OK_CONDITION(x,y,z) (-900<=(z) && (z)<5000)
#endif

  if ((cnt%10)==0) { /* check not too often */
    res = ACCEL_isEnabled(&isEnabled);
  } else {
    res = ERR_OK;
    isEnabled = TRUE;
  }
  cnt++;
  if (res==ERR_OK && isEnabled) {
    ACCEL_GetValues(&x, &y, &z);
    if (!ACCEL_OK_CONDITION(x,y,z)) { /* measure again */
      FRTOS1_vTaskDelay(100/portTICK_PERIOD_MS);
      ACCEL_GetValues(&x, &y, &z);
      if (!ACCEL_OK_CONDITION(x,y,z)) {
    #if PL_HAS_DRIVE
        DRV_Stop(1000);
    #else
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
        MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
    #endif
    #if PL_DO_LINE_MAZE || PL_DO_LINE_FOLLOWING
        LF_StopFollowing();
    #endif
    #if PL_DO_LINE_MAZE
        MAZE_ClearSolution();
    #endif
    #if PL_DO_SUMO
        SUMO_Stop();
    #endif
    #if PL_HAS_MUSIC_ACCEL_STOP
        MUSIC_PlayTheme(MUSIC_THEME_DAVE);
    #endif
        SHELL_SendString((unsigned char*)"Accel: Engines stopped!\r\n");
#if 1
        {
          uint8_t buf[32];

          UTIL1_strcpy(buf, sizeof(buf), "x: ");
          UTIL1_strcatNum16s(buf, sizeof(buf), x);
          UTIL1_strcat(buf, sizeof(buf), " y: ");
          UTIL1_strcatNum16s(buf, sizeof(buf), y);
          UTIL1_strcat(buf, sizeof(buf), " z: ");
          UTIL1_strcatNum16s(buf, sizeof(buf), z);
          UTIL1_strcat(buf, sizeof(buf), "\r\n");
          SHELL_SendString(buf);
        }
#endif
  #if PL_HAS_BUZZER
        (void)BUZ_Beep(300, 500);
  #endif
  #if PL_HAS_MUSIC_ACCEL_STOP
        MUSIC_PlayTheme(MUSIC_THEME_DAVE);
  #endif
      }
    }
  } else {
    SHELL_SendString((unsigned char*)"Accelerometer disabled?\r\n");
    (void)ACCEL_Enable();
  }
}
#endif /* PL_HAS_ACCEL_STOP */

static void MapButtonsForDisplay(EVNT_Handle event) {
#if PL_CONFIG_HAS_LCD
  if (GDisp1_GetDisplayOrientation()==GDisp1_ORIENTATION_LANDSCAPE) {
    switch(event) {
      case EVNT_SW1_PRESSED: LCD_SetEvent(LCD_BTN_RIGHT); break;
      case EVNT_SW2_PRESSED: LCD_SetEvent(LCD_BTN_LEFT); break;
      case EVNT_SW3_PRESSED: LCD_SetEvent(LCD_BTN_DOWN); break;
      case EVNT_SW4_PRESSED: LCD_SetEvent(LCD_BTN_CENTER); break;
      case EVNT_SW5_PRESSED: LCD_SetEvent(LCD_BTN_UP); break;
      case EVNT_SW6_PRESSED: LCD_SetEvent(LCD_SIDE_BTN_DOWN); break;
      case EVNT_SW7_PRESSED: LCD_SetEvent(LCD_SIDE_BTN_UP); break;
      default: break;
    } /* case */
  } else {
    switch(event) {
      case EVNT_SW1_PRESSED: LCD_SetEvent(LCD_BTN_LEFT); break;
      case EVNT_SW2_PRESSED: LCD_SetEvent(LCD_BTN_RIGHT); break;
      case EVNT_SW3_PRESSED: LCD_SetEvent(LCD_BTN_UP); break;
      case EVNT_SW4_PRESSED: LCD_SetEvent(LCD_BTN_CENTER); break;
      case EVNT_SW5_PRESSED: LCD_SetEvent(LCD_BTN_DOWN); break;
      case EVNT_SW6_PRESSED: LCD_SetEvent(LCD_SIDE_BTN_UP); break;
      case EVNT_SW7_PRESSED: LCD_SetEvent(LCD_SIDE_BTN_DOWN); break;
      default: break;
    } /* case */
  }
#else
  (void)event; /* not used */
#endif
}

static void APP_EventHandler(EVNT_Handle event) {
  MapButtonsForDisplay(event);
  switch(event) {
  case EVNT_STARTUP:
#if PL_HAS_USER_LED
    LED1_On(); /* just do something */
#endif
#if PL_CONFIG_HAS_BUZZER
    //BUZ_PlayTune(BUZ_TUNE_WELCOME);
#endif
    break;

  case EVNT_LED_HEARTBEAT:
#if PL_HAS_USER_LED
    LED1_Neg();
#endif
    break;

#if PL_CONFIG_HAS_KEYS
  #if PL_CONFIG_NOF_KEYS>=1
  case EVNT_SW1_PRESSED:
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
    LF_StartStopFollowing();
#endif
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW1 pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('a'); /* A */
    #endif
  #if PL_DO_MIDI
    if (MM_IsPlaying()) {
      MM_StopPlaying();
    } else {
      MM_Play(1);
    }
  #elif PL_APP_SUMO
    #if PL_CONFIG_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_BUTTON);
    #endif
    if (!SUMO_IsDoingSumo()) {
      SUMO_StartCountdown();
    } else {
      SUMO_StopSumo();
    }
  #endif
    break;

  case EVNT_SW1_RELEASED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW1 released\r\n", SHELL_GetStdio()->stdOut);
    break;

  case EVNT_SW1_LPRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW1 long pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_HAS_BUZZER
    BUZ_PlayTune(BUZ_TUNE_BUTTON_LONG);
    #endif
    break;
  #endif

  #if PL_CONFIG_NOF_KEYS>=2
  case EVNT_SW2_PRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW2 pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('b'); /* B */
    #endif
    break;
  case EVNT_SW2_LPRESSED:
  case EVNT_SW2_RELEASED:
    break;
    #endif


    #if PL_CONFIG_NOF_KEYS>=3
  case EVNT_SW3_PRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW3 pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('c'); /* C */
    #endif
    break;
  case EVNT_SW3_LPRESSED:
  case EVNT_SW3_RELEASED:
    break;
  #endif

    #if PL_CONFIG_NOF_KEYS>=4
  case EVNT_SW4_PRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW4 pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('d'); /* D */
    #endif
    break;
  case EVNT_SW4_LPRESSED:
  case EVNT_SW4_RELEASED:
    break;
  #endif

    #if PL_CONFIG_NOF_KEYS>=5
  case EVNT_SW5_PRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW5 pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('e');
    #endif
    break;

  case EVNT_SW5_LPRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW5L pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('E');
    #endif
    break;
  case EVNT_SW5_RELEASED:
    break;
  #endif

    #if PL_CONFIG_NOF_KEYS>=6
  case EVNT_SW6_PRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW6 pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('f');
    #endif
    break;

  case EVNT_SW6_LPRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW6L pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('F');
    #endif
    break;
  case EVNT_SW6_RELEASED:
    break;
  #endif

    #if PL_CONFIG_NOF_KEYS>=7
  case EVNT_SW7_PRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW7 pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('g');
    #endif
   break;

  case EVNT_SW7_LPRESSED:
#if PL_HAS_USER_LED2
    LED2_Neg();
#endif
    CLS1_SendStr((uint8_t*)"SW7L pressed\r\n", SHELL_GetStdio()->stdOut);
    #if PL_CONFIG_CONTROL_SENDER
    (void)REMOTE_SendButton('G'); /* G */
    #endif
   break;
  case EVNT_SW7_RELEASED:
    break;
  #endif
#endif
  default:
    break;
  } /* switch */
}

static void MainTask(void *pvParameters) {
#if PL_HAS_ACCEL_STOP || (PL_APP_SUMO && PL_HAS_USER_LED)
  uint32_t cnt = 0;
#endif
  
  (void)pvParameters; /* not used */
  vTaskDelay(100/portTICK_PERIOD_MS); /* provide some time to get hardware (SW1) pull-up effective */
#if PL_HAS_ACCEL_SENSOR
  if (ACCEL_LowLevelInit()!=ERR_OK) { /* always enable accelerometer */
#if PL_CONFIG_HAS_SHELL
    SHELL_SendString((unsigned char*)"ERR: Accel sensor init failed!\r\n");
#endif
  }
#endif
#if PL_APP_SUMO && PL_HAS_USER_LED
  LED1_On();
#endif
#if PL_HAS_TSS
  Configure(); /* initialize TSS library */
#endif
#if PL_HAS_MINT_LED
  MINTLED_SetMode(MINTLED_MODE_WAIT_BALL_REMOVAL); /* initial demo mode */
#endif
  for(;;) {
    KEYDBNC_Process(); /* scan and debounce polled keys */
    EVNT_HandleEvent(APP_EventHandler, TRUE);
#if PL_HAS_TSS
    TSS_Task(); /* call TSS library to process touches */
#elif 0 && !PL_DO_TEST
    CheckButton();
#endif
#if PL_APP_AVOID_OBSTACLE
    AvoidObstacle();
#endif
#if PL_APP_FOLLOW_OBSTACLE
    FollowObstacle();
#endif
#if PL_HAS_LED_BLUE
    LEDB_Neg();
#endif
    StateMachine(FALSE);
#if 0 && PL_APP_SUMO && PL_HAS_USER_LED
    if ((cnt%48)==0) {
      LED1_Neg();
    }
#endif
#if PL_HAS_FREEMASTER
    FMSTR1_Poll();
    FMSTR1_Recorder();
#endif
#if PL_HAS_ACCEL_STOP
    if ((cnt%10)==0) { /* every 100 ms */
      CheckAccelerometer();
    }
#endif /* PL_HAS_ACCEL_STOP */
#if PL_HAS_LASER
    {
      bool isLeft, isRight;

      LASER_LeftRightStatus(&isLeft, &isRight);
      USER_LED2_Put(isLeft);
      USER_LED_Put(isRight);
    }
#endif
#if PL_HAS_ACCEL_STOP || (PL_APP_SUMO && PL_HAS_USER_LED)
    cnt++;
#endif
    vTaskDelay(10/portTICK_PERIOD_MS);
  } /* for */
}

#if PL_CONFIG_HAS_SHELL
static uint8_t APP_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of app commands\r\n", io->stdOut);
#if PL_DO_MINT
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"Short press (1 beep): enter automatic mode, simulate ball received/removed.\r\n", io->stdOut);
#elif PL_IS_ROBOT
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"Short press (1 beep): start or stop line following if calibrated\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"1 s press   (2 beep): calibrate manually\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"2 s press   (3 beep): calibrate with auto-move\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"3 s press   (4 beep or more): clear path\r\n", io->stdOut);
#endif
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows app help or status\r\n", io->stdOut);
#if PL_APP_FOLLOW_OBSTACLE
  CLS1_SendHelpStr((unsigned char*)"  follow (on|off)", (unsigned char*)"Obstacle following on or off\r\n", io->stdOut);
#endif
#if PL_APP_AVOID_OBSTACLE
  CLS1_SendHelpStr((unsigned char*)"  avoid (on|off)", (unsigned char*)"Obstacle avoidance on or off\r\n", io->stdOut);
#endif
#if PL_HAS_LINE_SENSOR && PL_HAS_TURN 
  CLS1_SendHelpStr((unsigned char*)"  autocalib", (unsigned char*)"Automatically calibrate line sensor\r\n", io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t APP_PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
#if PL_APP_SUMO
  CLS1_SendStatusStr((unsigned char*)"  mode", (unsigned char*)"SUMO\r\n", io->stdOut);
#endif
#if PL_APP_REMOTE_CONTROL
  CLS1_SendStatusStr((unsigned char*)"  mode", (unsigned char*)"REMOTE CONTROL\r\n", io->stdOut);
#endif
#if  PL_APP_LINE_FOLLOWING
  CLS1_SendStatusStr((unsigned char*)"  mode", (unsigned char*)"LINE FOLLOWING\r\n", io->stdOut);
#endif
#if PL_APP_LINE_MAZE
  CLS1_SendStatusStr((unsigned char*)"  mode", (unsigned char*)"LINE MAZE\r\n", io->stdOut);
#endif
#if PL_APP_FOLLOW_OBSTACLE
  CLS1_SendStatusStr((unsigned char*)"  follow", followObstacle?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
#endif
#if PL_HAS_USER_BUTTON
  CLS1_SendStatusStr((unsigned char*)"  button", SW1_GetVal()==0?(unsigned char*)"pressed\r\n":(unsigned char*)"released\r\n", io->stdOut);
#endif
  CLS1_SendStatusStr((unsigned char*)"  App State", AppStateString(appState), io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
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
#if PL_HAS_LINE_SENSOR && PL_HAS_TURN 
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app autocalib")==0) {
    *handled = TRUE;
    return AutoCalibrateReflectance();
#endif
#if PL_APP_AVOID_OBSTACLE
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app avoid on")==0) {
    avoidObstacle = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)"app avoid off")==0) {
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
#endif /* PL_CONFIG_HAS_SHELL */

#if PL_CONFIG_HAS_NVM_CONFIG
static void InitNVMCValues(void) {
  const NVMC_RobotData *ptr;
  NVMC_RobotData data;
  uint8_t res;
  #define NVMC_VERSION  0x01

  ptr = NVMC_GetRobotData();
  if (ptr==NULL || ptr->version != NVMC_VERSION) {
    data.version = NVMC_VERSION;
    data.MazeLeftHandOnTheWall = TRUE;
    res = NVMC_SaveRobotData(&data);
    if (res!=ERR_OK) {
      for(;;); /* error */
    }
  }
}
#endif

static void APP_AdoptToHardware(void) {
#if PL_CONFIG_HAS_IDENTIFY
#if PL_CONFIG_HAS_MOTOR
  ID_Devices robot;

  robot = ID_WhichDevice();
  if (robot==ID_DEVICE_ROBO_V1_L1 || robot==ID_DEVICE_ROBO_V1_L3) { /* L3, V1 */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert right motor */
    (void)Q4CLeft_SwapPins(TRUE);
    (void)Q4CRight_SwapPins(TRUE);
  } else if (robot==ID_DEVICE_ROBO_V1_L2) {
    (void)Q4CLeft_SwapPins(TRUE);
    (void)Q4CRight_SwapPins(TRUE);
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert left motor */
  } else if (robot==ID_DEVICE_ROBO_V1_L4) {
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert left motor */
    (void)Q4CLeft_SwapPins(TRUE);
    (void)Q4CRight_SwapPins(TRUE);
  } else if (robot==ID_DEVICE_ROBO_V2_L5) {
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* revert right motor */
    (void)Q4CRight_SwapPins(TRUE);
  } else if (robot==ID_DEVICE_ROBO_V1_L8) {
    (void)Q4CLeft_SwapPins(TRUE);
    (void)Q4CRight_SwapPins(TRUE);
  } else if (robot==ID_DEVICE_ROBO_V2_L20 || robot==ID_DEVICE_ROBO_V2_L21 || robot==ID_DEVICE_ROBO_V2_L23) {
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_LEFT), TRUE); /* invert left motor */
    MOT_Invert(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), TRUE); /* invert right motor */
    (void)Q4CRight_SwapPins(TRUE);
  } else if (robot==ID_DEVICE_ROBO_V2_L22) {
    (void)Q4CRight_SwapPins(TRUE);
  }
#endif
#endif
#if PL_CONFIG_BOARD_IS_ROBO_V2_2016
  /* SW1: enable and turn on pull-up resistor for PTA14 (push button) */
  PORT_PDD_SetPinPullSelect(PORTA_BASE_PTR, 14, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTA_BASE_PTR, 14, PORT_PDD_PULL_ENABLE);

  /* pull-ups for Quadrature Encoder Pins */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 10, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 10, PORT_PDD_PULL_ENABLE);
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 11, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 11, PORT_PDD_PULL_ENABLE);
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 16, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 16, PORT_PDD_PULL_ENABLE);
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 17, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 17, PORT_PDD_PULL_ENABLE);
#endif
}

void APP_Run(void) {
#if PL_CONFIG_HAS_NVM_CONFIG
  InitNVMCValues();
#endif
  appState = APP_STATE_STARTUP;
#if PL_HAS_MOTOR
  MOT_Init();
#endif
#if PL_CONFIG_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_LINE_SENSOR
  REF_Init();
#endif
#if PL_HAS_TURN
  TURN_Init();
#endif
#if PL_HAS_PID
  PID_Init();
#endif
#if PL_APP_LINE_FOLLOWING || PL_APP_LINE_MAZE
  LF_Init();
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
  RSTACK_Init();
  RNETA_Init();
#endif
#if PL_HAS_REMOTE
  REMOTE_Init();
#endif
#if PL_HAS_SHELL_QUEUE
  SQUEUE_Init();
#endif
#if PL_HAS_DISTANCE_SENSOR
  DIST_Init();
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_Init();
#endif
#if PL_HAS_SHELL_TRACE
  TRACE_Init();
#endif
#if PL_APP_SUMO
  SUMO_Init();
#endif
#if PL_DO_TEST
  TEST_Init();
#endif
#if PL_HAS_DRIVE
  DRV_Init();
#endif
#if PL_HAS_ACCEL
  /*lint -save  -e522 Highest operation, function 'ACCE_Init', lacks side-effect. */
  ACCEL_Init();
  /*lint -restore Highest operation, function 'ACCE_Init', lacks side-effect. */
#endif
#if PL_HAS_MCP4728
  MCP4728_Init();
#endif
#if PL_HAS_ROBO_SHIELD
  RS_Init();
#endif
#if PL_HAS_MUSIC_SHIELD
  MUSIC_Init();
#endif
#if PL_HAS_SPI
  SPI_Init();
#endif
#if PL_HAS_LASER
  LASER_Init();
#endif
#if PL_APP_LINE_MAZE
  MAZE_Init();
#endif
#if PL_HAS_MINT
  MINT_Init();
#endif
#if PL_HAS_MINT_REMOTE
  MINTREMOTE_Init();
#endif
#if PL_HAS_MINT_LED
  MINTLED_Init();
#endif
#if PL_HAS_TOF_SENSOR
  (void)VL6180X_Init();
#endif
#if PL_CONFIG_HAS_LCD
  LCD_Init();
#endif
#if PL_CONFIG_HAS_BATTERY_ADC
  BATT_Init();
#endif
#if PL_HAS_MIDI
  MM_Init();
#endif
  APP_AdoptToHardware();
  if (xTaskCreate(MainTask, "Main", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  FRTOS1_vTaskStartScheduler();
}
