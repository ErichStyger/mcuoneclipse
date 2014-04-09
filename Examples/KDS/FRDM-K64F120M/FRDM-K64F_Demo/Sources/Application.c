/**
 * \file
 * \brief Main Application Module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is the main application module. 
 * From here the application runs and performs all tasks.
 */
#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "timers.h"
#include "TMOUT1.h"
#if PL_HAS_RADIO
  #include "RNet_App.h"
#endif
#if PL_HAS_KEYS
  #include "KEY1.h"
#endif
#if PL_HAS_ACCELEROMETER
  #include "FX1.h"
#endif
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif

static xTimerHandle timerHndl;
#define TIMER_PERIOD_MS TMOUT1_TICK_PERIOD_MS

#if PL_HAS_KEYS
void APP_OnKeyPressed(uint8_t keys) {
  if (keys&1) {
    CLS1_SendStr((uint8_t*)"SW3 pressed!\r\n", CLS1_GetStdio()->stdOut);
  } else if (keys&2) {
    CLS1_SendStr((uint8_t*)"SW2 pressed!\r\n", CLS1_GetStdio()->stdOut);
  }
}

void APP_OnKeyReleased(uint8_t keys) {
  if (keys&1) {
    CLS1_SendStr((uint8_t*)"SW3 released!\r\n", CLS1_GetStdio()->stdOut);
  } else if (keys&2) {
    CLS1_SendStr((uint8_t*)"SW2 released!\r\n", CLS1_GetStdio()->stdOut);
  }
}

void APP_OnKeyReleasedLong(uint8_t keys) {
  if (keys&1) {
    CLS1_SendStr((uint8_t*)"SW3 long released!\r\n", CLS1_GetStdio()->stdOut);
  } else if (keys&2) {
    CLS1_SendStr((uint8_t*)"SW2 long released!\r\n", CLS1_GetStdio()->stdOut);
  }
}
#endif /* PL_HAS_KEYS */

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  TMOUT1_AddTick();
  TRG1_AddTick();
}

#if PL_HAS_DEBUG_PRINT
void APP_DebugPrint(unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}
#endif

static portTASK_FUNCTION(MainTask, pvParameters) {
#if PL_HAS_ACCELEROMETER
  int16_t xmg, ymg;
#endif

  (void)pvParameters; /* parameter not used */
  for(;;) {
#if PL_HAS_ACCELEROMETER
    xmg = FX1_GetXmg();
    ymg = FX1_GetYmg();
    LED1_Put(xmg>100||xmg<-100||ymg>100||ymg<-100);
    LED2_Put(xmg>500||xmg<-500||ymg>500||ymg<-500);
#endif
    LED3_Neg();
#if PL_HAS_KEYS
    KEY1_ScanKeys();
#endif
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Start(void) {
#if PL_HAS_RTOS_TRACE
  if(RTOSTRC1_uiTraceStart()!=1) {
    for(;;){} /* failure? */
  }
#endif
#if PL_HAS_RADIO
  RNETA_Init();
#endif
  SHELL_Init();
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
  timerHndl = xTimerCreate("timer0", TIMER_PERIOD_MS/portTICK_RATE_MS, pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  FRTOS1_vTaskStartScheduler();
}
