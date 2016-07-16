/**
 * \file
 * \brief Main Application Module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is the main application module. 
 * From here the application runs and performs all tasks.
 */

#include "Platform.h"
#include "LED.h"
#include "WAIT1.h"
#include "Event.h"
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_SHELL
  #include "Shell.h"
#endif
#if PL_HAS_RTOS
  #include "FRTOS1.h"
  #include "RTOS.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
  //#include "RadioSMAC.h"
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_FREEMASTER
  #include "FMSTR1.h"
#endif
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
  #include "RStdIO.h"
#endif

static void APP_HandleEvent(EVNT_Handle event) {
  switch(event) {
  case EVNT_INIT:
    LED1_On(); WAIT1_Waitms(500); LED1_Off();
    break;
#if PL_NOF_KEYS>=1
  case EVNT_SW1_PRESSED:
    LED1_Neg();
  #if PL_HAS_BUZZER
    (void)BUZ_Beep(300, 500);
  #endif
  #if PL_HAS_REMOTE
    if (REMOTE_GetOnOff()) {
      REMOTE_SetOnOff(FALSE);
    } else {
      REMOTE_SetOnOff(TRUE);
    }
  #endif
    break;
#endif
#if PL_NOF_KEYS>=2
  case EVNT_SW2_PRESSED:
    LED2_Neg();
#if PL_HAS_REMOTE && PL_APP_ACCEL_CONTROL_SENDER
    //(void)RSTDIO_SendToTxStdio(RSTDIO_QUEUE_TX_IN, "buzzer buz 800 400\r\n", sizeof("buzzer buz 800 400\r\n")-1);
#endif
    break;
#endif
#if PL_NOF_KEYS>=3
  case EVNT_SW3_PRESSED:
    LED3_Neg();
    break;
#endif
#if PL_NOF_KEYS>=4
  case EVNT_SW4_PRESSED:
    LED4_Neg();
    break;
#endif
#if PL_HAS_LED_HEARTBEAT
  case EVNT_LED_HEARTBEAT:
    LED4_Neg();
    break;
#endif
  default:
#if PL_HAS_RADIO
    //RADIO_AppHandleEvent(event);
#endif
    break;
  }
}

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
#if PL_HAS_ACCEL
  (void)ACCEL_LowLevelInit();
#endif
  for(;;) {
#if PL_HAS_KEYS && !PL_HAS_KBI
    /* poll keys */
    KEY_Scan(); /* poll keys */
#endif
    EVNT_HandleEvent(APP_HandleEvent);
#if PL_HAS_FREEMASTER
    FMSTR1_Poll();
    FMSTR1_Recorder();
#endif
#if PL_HAS_ULTRASONIC
    //(void)US_Measure_us();
#endif
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  }
}

void APP_Start(void) {
  EVNT_SetEvent(EVNT_INIT);
#if PL_HAS_RTOS
  if (FRTOS1_xTaskCreate(
        MainTask,  /* pointer to the task */
        "Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
#else
  for(;;) { /* application main loop */
#if PL_HAS_SHELL
    SHELL_Process();
#endif
#if PL_HAS_KEYS && !PL_HAS_KBI
    /* poll keys */
    KEY_Scan(); /* poll keys */
#endif
    EVNT_HandleEvent(APP_HandleEvent);
    WAIT1_Waitms(10);
  }
#endif
}
