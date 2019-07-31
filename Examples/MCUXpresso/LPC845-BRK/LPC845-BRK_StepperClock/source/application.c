/*
 * application.c
 *
 *  Created on: 30.07.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "buttons.h"
#include "leds.h"

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100
static SemaphoreHandle_t mutex;

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}

static void AppTask(void *pv) {
  for(;;) {
    McuLED_Toggle(LEDS_Green);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void APP_Run(void) {
	PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      300/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  mutex = xSemaphoreCreateMutex();
  if (mutex!=NULL) {
    vQueueAddToRegistry(mutex, "Mutex");
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }

	for(;;) {
    if (BTN_K1ButtonIsPressed()) { /* check push button */
      McuLED_On(LEDS_Green);
      while(BTN_K1ButtonIsPressed()) {}
    }
    if (BTN_K3ButtonIsPressed()) { /* check push button */
      McuLED_On(LEDS_Red);
      while(BTN_K3ButtonIsPressed()) {}
    }
    McuLED_On(LEDS_Green);
    McuWait_Waitms(100);
    McuLED_Off(LEDS_Green);

    McuLED_On(LEDS_Blue);
    McuWait_Waitms(100);
    McuLED_Off(LEDS_Blue);

    McuLED_On(LEDS_Red);
    McuWait_Waitms(100);
    McuLED_Off(LEDS_Red);
	}
}
