/*
 * Application.c
 *
 *  Created on: 27.08.2018
 *      Author: Erich Styger
 */


#include "Application.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"


static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}


static void AppTask(void *param) {
	(void)param;
	for(;;) {
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void APP_Run(void) {
  if (xTaskCreate(
	  AppTask,  /* pointer to the task */
	  "App", /* task name for kernel awareness debugging */
	  configMINIMAL_STACK_SIZE+500, /* task stack size */
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
  vTaskStartScheduler();
  for(;;) {}
}
