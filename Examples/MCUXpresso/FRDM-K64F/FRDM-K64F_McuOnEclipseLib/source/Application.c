/*
 * Application.c
 *
 *  Created on: 27.08.2018
 *      Author: Erich Styger
 */


#include "Application.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "McuRTT.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuSystemView.h"
#include "McuPercepio.h"
#include "McuLED.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}

void McuGenericI2C_OnError(void) {
	/* I2C error hook */  /* disable with McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT */
}

static void AppTask(void *param) {
	(void)param;
	for(;;) {
		McuLED_Neg();
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void APP_Run(void) {
  /* initialize components */
  McuRTT_Init();
#if configUSE_PERCEPIO_TRACE_HOOKS
  //McuPercepio_Init();
#elif configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuRTOS_Init();
  McuWait_Init();
  McuUtility_Init();
  McuLED_Init();
  McuGenericI2C_Init();
  McuGenericSWI2C_Init();

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
