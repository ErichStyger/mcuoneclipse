/**
 * \file
 * \brief Main Application Module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is the main application module. 
 * From here the application runs and performs all tasks.
 */
#include "Platform.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "timers.h"
#include "TMOUT1.h"
#include "CLS1.h"
#if PL_HAS_KEYS
  #include "KEY1.h"
  #include "TRG1.h"
#endif
#if PL_HAS_ACCELEROMETER
  #include "MMA1.h"
#endif

static TimerHandle_t timerHndl;
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

static void vTimerCallback(TimerHandle_t pxTimer) {
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
#if PL_HAS_ACCELEROMETER
  (void)MMA1_Enable(); /* enable accelerometer */
#endif
  for(;;) {
#if PL_HAS_KEYS
    KEY1_ScanKeys();
#endif
#if PL_HAS_ACCELEROMETER
    xmg = MMA1_GetXmg();
    ymg = MMA1_GetYmg();
    LED1_Put(xmg>100||xmg<-100||ymg>100||ymg<-100);
    LED2_Put(xmg>500||xmg<-500||ymg>500||ymg<-500);
    LED3_Put(xmg>800||xmg<-800||ymg>800||ymg<-800);
#endif
    LED4_Neg();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void APP_Start(void) {
#if PL_HAS_SHELL
  SHELL_Init();
#endif
  if (FRTOS1_xTaskCreate(
      MainTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
  /*lint -e527 */
  for(;;){} /* error! probably out of memory */
    /*lint +e527 */
  }
  timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  FRTOS1_vTaskStartScheduler();
}
