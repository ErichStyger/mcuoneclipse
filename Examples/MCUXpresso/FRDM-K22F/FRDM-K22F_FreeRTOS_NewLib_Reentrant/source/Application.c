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
#include "McuHardFault.h"
#include "McuArmTools.h"
#include "McuSystemView.h"
#include "McuPercepio.h"
#include "McuLED.h"
#include "McuGenericI2C.h"
#include "McuGenericSWI2C.h"
#include "McuSSD1306.h"
#include "McuTimeDate.h"
#include "McuCriticalSection.h"
#include "McuXFormat.h"
#include "McuTrigger.h"

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100

static void vTimerCallback(xTimerHandle pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}

void McuGenericI2C_OnError(void) {
	/* I2C error hook */  /* disable with McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT */
}

#include <stdlib.h>
static void AppTask2(void *param) {
	int i;
	int *p[32];

	(void)param;
	for(;;) {
		McuLED_Neg();
		for(i=0;i<sizeof(p)/sizeof(p[0]); i++) {
			p[i] = (int*)malloc(sizeof(int));
			if (p[i]!=NULL) {
				*(p[i]) = i;
			} else {
				for(;;) {} /* error */
			}
		}
		vTaskDelay(pdMS_TO_TICKS(100));
		for(i=0;i<sizeof(p)/sizeof(p[0]); i++) {
			if (*(p[i])!=i) {
				for(;;) {} /* error */
			}
			free(p[i]);
			p[i] = NULL;
		}
	}
}


static void AppTask(void *param) {
	int *p[32];
	int i;

	(void)param;
	for(;;) {
		McuLED_Neg();
		for(i=0;i<sizeof(p)/sizeof(p[0]); i++) {
			p[i] = (int*)pvPortMalloc(sizeof(int));
			if (p[i]!=NULL) {
				*(p[i]) = i;
			} else {
				for(;;) {} /* error */
			}
		}
		vTaskDelay(pdMS_TO_TICKS(50));
		for(i=0;i<sizeof(p)/sizeof(p[0]); i++) {
			if (*(p[i])!=i) {
				for(;;) {} /* error */
			}
			vPortFree(p[i]);
			p[i] = NULL;
		}
	}
}

void APP_Run(void) {
  /* initialize components */
  McuRTOS_Init();
  McuCriticalSection_Init();
  McuRTT_Init();
#if configUSE_PERCEPIO_TRACE_HOOKS
  //McuPercepio_Init();
#elif configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuXFormat_Init();
  McuTrigger_Init();
  McuWait_Init();
  McuUtility_Init();
  McuHardFault_Init();
  McuArmTools_Init();
  McuLED_Init(); /* initializes as well the LED pin */
  McuGenericI2C_Init();
  McuGenericSWI2C_Init(); /* initializes as well the SCL and SDA pins */
  //McuSSD1306_Init(); /* requires display on the I2C bus! */
  McuTimeDate_Init();

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
  if (xTaskCreate(
	  AppTask2,  /* pointer to the task */
	  "App2", /* task name for kernel awareness debugging */
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
