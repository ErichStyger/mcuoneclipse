/** ###################################################################
**     Filename  : RTOS.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 21.01.2010, 08:24
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE RTOS */

#include "Platform.h"

#include "RTOS.h"
#if PL_HAS_WATCHDOG
  #include "WatchDog.h"
#endif
#if PL_HAS_CUBE_DEMO
  #include "Cube.h"
#endif
#if PL_HAS_TETRIS_DEMO
  #include "Tetris.h"
#endif
#if PL_USE_RTOS
  #include "FRTOS1.h"
#endif
#if !PL_IS_BOOTLOADER /* bootloader does not need events */
  #include "EVNT1.h"
#endif
#if PL_HAS_HW_TOUCHSCREEN
  #include "TCHS1.h"
#endif
#if PL_HAS_HW_SOUNDER
  #include "Buzzer.h"
#endif
#include "App.h"
#if PL_HAS_ACCEL_DEMO
  #include "Accelerometer.h"
#endif
#if PL_HAS_HW_LED
  #include "LED3.h"
  #include "LED4.h"
#endif
#if PL_HAS_HW_TOUCHSCREEN
  #include "Touchscreen.h"
#endif
#if PL_POLL_KEYS2    
  #include "KEY2.h"
#endif
#if PL_HAS_BOOTLOADER
  #include "Bootloader.h"
#endif
#if PL_HAS_SHELL
  #include "Serial.h"
#endif
#include "AnalogDigital.h"
#include "I2C.h"
#include "WAIT1.h"

#if PL_USE_RTOS
void RTOS_HandleEvent(byte event) {
  switch(event) {
  #if PL_HAS_HW_NAV_SWITCH
    case EVNT1_BUTTON1_RELEASED:
    #if PL_HAS_HW_LCD /* rotate switch meaning depending on orientation */
      switch(GDisp1_GetDisplayOrientation()) {
        case GDisp1_ORIENTATION_LANDSCAPE180: EVNT1_SetEvent(EVNT1_BUTTON_UI_LEFT);  break;
        case GDisp1_ORIENTATION_PORTRAIT:     EVNT1_SetEvent(EVNT1_BUTTON_UI_DOWN);  break;
        case GDisp1_ORIENTATION_LANDSCAPE:    EVNT1_SetEvent(EVNT1_BUTTON_UI_RIGHT); break;
        case GDisp1_ORIENTATION_PORTRAIT180:  EVNT1_SetEvent(EVNT1_BUTTON_UI_UP);    break;
      } /* switch */
    #else
      EVNT1_SetEvent(EVNT1_BUTTON_UI_RIGHT);
    #endif
      break;
    case EVNT1_BUTTON2_RELEASED:
    #if PL_HAS_HW_LCD /* rotate switch meaning depending on orientation */
      switch(GDisp1_GetDisplayOrientation()) {
        case GDisp1_ORIENTATION_LANDSCAPE180: EVNT1_SetEvent(EVNT1_BUTTON_UI_UP);    break;
        case GDisp1_ORIENTATION_PORTRAIT:     EVNT1_SetEvent(EVNT1_BUTTON_UI_LEFT);  break;
        case GDisp1_ORIENTATION_LANDSCAPE:    EVNT1_SetEvent(EVNT1_BUTTON_UI_DOWN);  break;
        case GDisp1_ORIENTATION_PORTRAIT180:  EVNT1_SetEvent(EVNT1_BUTTON_UI_RIGHT); break;
      } /* switch */
    #else
      EVNT1_SetEvent(EVNT1_BUTTON_UI_DOWN);
    #endif
      break;
    case EVNT1_BUTTON5_RELEASED:
    #if PL_HAS_HW_LCD /* rotate switch meaning depending on orientation */
      switch(GDisp1_GetDisplayOrientation()) {
        case GDisp1_ORIENTATION_LANDSCAPE180: EVNT1_SetEvent(EVNT1_BUTTON_UI_RIGHT); break;
        case GDisp1_ORIENTATION_PORTRAIT:     EVNT1_SetEvent(EVNT1_BUTTON_UI_UP);    break;
        case GDisp1_ORIENTATION_LANDSCAPE:    EVNT1_SetEvent(EVNT1_BUTTON_UI_LEFT);  break;
        case GDisp1_ORIENTATION_PORTRAIT180:  EVNT1_SetEvent(EVNT1_BUTTON_UI_DOWN);  break;
      } /* switch */
    #else
      EVNT1_SetEvent(EVNT1_BUTTON_UI_LEFT);
    #endif
      break;
    case EVNT1_BUTTON3_PRESSED:
      EVNT1_SetEvent(EVNT1_BUTTON_UI_MIDDLE_DOWN);
      break;
    case EVNT1_BUTTON3_RELEASED:
      EVNT1_SetEvent(EVNT1_BUTTON_UI_MIDDLE);
      break;
    case EVNT1_BUTTON4_RELEASED:
    #if PL_HAS_HW_LCD /* rotate switch meaning depending on orientation */
      switch(GDisp1_GetDisplayOrientation()) {
        case GDisp1_ORIENTATION_LANDSCAPE180: EVNT1_SetEvent(EVNT1_BUTTON_UI_DOWN);  break;
        case GDisp1_ORIENTATION_PORTRAIT:     EVNT1_SetEvent(EVNT1_BUTTON_UI_RIGHT); break;
        case GDisp1_ORIENTATION_LANDSCAPE:    EVNT1_SetEvent(EVNT1_BUTTON_UI_UP);    break;
        case GDisp1_ORIENTATION_PORTRAIT180:  EVNT1_SetEvent(EVNT1_BUTTON_UI_LEFT);  break;
      } /* switch */
    #else
      EVNT1_SetEvent(EVNT1_BUTTON_UI_UP);
    #endif
      break;
  #elif (PL_BOARD_TWR_CN128 || PL_BOARD_TWR_52259) /* use the TWR SW2 and SW3, translate to navigation messages */
    case EVNT1_BUTTON1_RELEASED:      EVNT1_SetEvent(EVNT1_BUTTON_UI_LEFT);  break;
    case EVNT1_BUTTON2_RELEASED:      EVNT1_SetEvent(EVNT1_BUTTON_UI_RIGHT);  break;
    case EVNT1_BUTTON1_RELEASED_LONG: EVNT1_SetEvent(EVNT1_BUTTON_UI_MIDDLE);  break;
    case EVNT1_BUTTON2_RELEASED_LONG: EVNT1_SetEvent(EVNT1_BUTTON_UI_MIDDLE);  break;
  #endif
    case EVNT1_BUZZER_BEEP:
  #if PL_HAS_HW_SOUNDER
      BUZ_Beep();
  #endif
      break;
    default:
      break;
  } /* switch */
  /* call other event handler... */
#if PL_HAS_UI
  APP_HandleEvent(event);
#endif
#if PL_APP_MODE_I2C_LCD
  I2C_HandleEvent(event);
#endif
}
#endif /* PL_USE_RTOS */

#if PL_HAS_AUTO_DEMO
static size_t heapSize;
#endif

#if PL_USE_RTOS
static portTASK_FUNCTION(TaskMain, pvParameters ) {
  byte i;
#if PL_HAS_HW_LED
  byte cntr;
#endif
  
	/* The parameters are not used. */
	(void)pvParameters;
#if PL_HAS_WATCHDOG
	WDOG_Clear();
#endif
#if PL_HAS_HW_TOUCHSCREEN
  TouchScreen_CheckTouchScreenCalibrationData();
#endif
  BUZ_Init();
#if PL_HAS_UI
  APP_Init();
#endif
#if PL_HAS_HW_LED
  cntr = 0;
  LED3_On(); LED4_Off();
#endif
	for(;;) {
  #if PL_HAS_HW_TOUCHSCREEN
    TCHS1_Scan();
  #endif
  #if PL_POLL_KEYS2    
    KEY2_ScanKeys(); /* poll keys */
  #endif
    i = 10; /* to avoid stalling */
    while (EVNT1_EventsPending() && i>0) {
      EVNT1_HandleEvent();
      i--;
    }
  #if PL_HAS_HW_LED
    cntr++;
    if (cntr == 10) {  /* change LED's */
      LED3_Neg();
      LED4_Neg();
      cntr = 0;
    }
  #endif
#if PL_HAS_AUTO_DEMO
  #if PL_HAS_FONT_DEMO
    FRTOS1_vTaskDelay((2*1000)/portTICK_RATE_MS);
    APP_SetApplicationMode(APP_MODE_FONT_DEMO);
    FRTOS1_vTaskDelay((10*1000)/portTICK_RATE_MS);
  #endif
  #if PL_HAS_ACCEL_DEMO
    APP_SetApplicationMode(APP_MODE_ACCEL_DEMO);
    FRTOS1_vTaskDelay((15*1000)/portTICK_RATE_MS);
    ACCEL_StopAccelDemo();
    FRTOS1_vTaskDelay((2*1000)/portTICK_RATE_MS);
  #endif
  #if 0 && PL_HAS_TETRIS_DEMO
    APP_SetApplicationMode(APP_MODE_TETRIS);
    FRTOS1_vTaskDelay((5*1000)/portTICK_RATE_MS);
    TETRIS_KillTask();
    FRTOS1_vTaskDelay((2*1000)/portTICK_RATE_MS);
  #endif
  #if PL_HAS_CUBE_DEMO
    APP_SetApplicationMode(APP_MODE_3D_CUBE);
    FRTOS1_vTaskDelay((8*1000)/portTICK_RATE_MS);
    CUBE_CloseShipWindow();
    FRTOS1_vTaskDelay((2*1000)/portTICK_RATE_MS);
    CUBE_CloseCubeWindow();
    FRTOS1_vTaskDelay((2*1000)/portTICK_RATE_MS);
  #endif
    //APP_SetApplicationMode(APP_MODE_MAIN_MENU);
    //FRTOS1_vTaskDelay((5*1000)/portTICK_RATE_MS);
    heapSize = FRTOS1_xPortGetFreeHeapSize();
#endif
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	} /* for */
}
#endif

void RTOS_Start(void) {
#if PL_HAS_HW_SOUNDER
  BUZ_Disable();
#endif
#if PL_HAS_HW_TOUCHSCREEN
  TCHS1_Init();
#endif
#if PL_HAS_HW_LCD
  LCD1_Init();
#endif
#if PL_APP_MODE_I2C_LCD || PL_APP_MODE_I2C_TWR
  I2C_Init();
#endif
  AD_Init();
#if PL_HAS_ACCEL_DEMO
  ACCEL_StartOrientationTask();
#endif
#if PL_HAS_SHELL
  SERIAL_Start();
#endif
#if PL_USE_RTOS
  if (FRTOS1_xTaskCreate(TaskMain, "Main", configMINIMAL_STACK_SIZE+350, NULL, tskIDLE_PRIORITY+2, (xTaskHandle *) NULL)==pdPASS) {
    FRTOS1_vTaskStartScheduler(); /* Start the scheduler */
  }
#endif
}


/* END RTOS */
