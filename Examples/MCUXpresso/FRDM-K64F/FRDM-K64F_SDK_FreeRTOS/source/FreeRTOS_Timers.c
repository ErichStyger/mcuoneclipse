/*
 * FreeRTOS_Timers.c
 *
 *  Created on: 03.07.2018
 *      Author: Erich Styger
 */

#include "App_Config.h"
#if APP_CONFIG_USE_FREERTOS
#include "FreeRTOS_Timers.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"

/* configuration items for timers in FreeRTOSConfig.h
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            (configMINIMAL_STACK_SIZE * 2)
*/

/* global variables to show the timer status in the debugger */
static int debugTimer1Sec, debugTimer5Sec;

static void vTimerCallback1SecExpired(TimerHandle_t pxTimer) {
#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
	SEGGER_SYSVIEW_PrintfTarget("1 Sec Timer (ID %d) expired", (int)pvTimerGetTimerID(pxTimer));
#endif
  GPIO_PortToggle(BOARD_INITPINS_LED_RED_GPIO, 1<<BOARD_INITPINS_LED_RED_PIN); /* toggle red LED */
  debugTimer1Sec = !debugTimer1Sec;
}

static void vTimerCallback5SecExpired(TimerHandle_t pxTimer) {
	/* this timer callback turns off the green LED */
#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
	SEGGER_SYSVIEW_PrintfTarget("5 Sec Timer (ID %d) expired", (int)pvTimerGetTimerID(pxTimer));
#endif
    GPIO_PortSet(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* turn off green LED */
    debugTimer5Sec = 0;
}

static void TimersTask(void *param) {
	TimerHandle_t timerHndl1Sec, timerHndl5SecTimeout;

	(void)param; /* not used */
    timerHndl1Sec = xTimerCreate(
    		"timer1Sec", /* name */
			pdMS_TO_TICKS(1000), /* period/time */
			pdTRUE, /* auto reload */
			(void*)0, /* timer ID */
			vTimerCallback1SecExpired); /* callback */
    if (timerHndl1Sec==NULL) {
      for(;;); /* failure! */
    }
#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
    SEGGER_SYSVIEW_PrintfTarget("Start of 1 Second Timer");
#endif
    if (xTimerStart(timerHndl1Sec, 0)!=pdPASS) {
      for(;;); /* failure!?! */
    }
    debugTimer1Sec = 1;

    timerHndl5SecTimeout = xTimerCreate(
    		"timerGreen", /* name */
			pdMS_TO_TICKS(5000), /* period/time */
			pdFALSE, /* auto reload */
			(void*)1, /* timer ID */
			vTimerCallback5SecExpired); /* callback */
    if (timerHndl5SecTimeout==NULL) {
      for(;;); /* failure! */
    }
#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
    SEGGER_SYSVIEW_PrintfTarget("Start of 5 Second Timer");
#endif
    if (xTimerStart(timerHndl1Sec, 0)!=pdPASS) {
      for(;;); /* failure! */
    }
    debugTimer1Sec = 1;
	for(;;) {
		if (!GPIO_PinRead(BOARD_INITPINS_SW3_GPIO, BOARD_INITPINS_SW3_PIN)) { /* pin LOW ==> SW03 push button pressed */
		  while(!GPIO_PinRead(BOARD_INITPINS_SW3_GPIO, BOARD_INITPINS_SW3_PIN)) {
		    /* wait until push button is released */
		  }
			GPIO_PortClear(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* Turn green LED on */
			debugTimer5Sec = 1;
#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
		    SEGGER_SYSVIEW_PrintfTarget("Reset of 5 Second Timer");
#endif
		    if (xTimerReset(timerHndl5SecTimeout, 0)!=pdPASS) { /* start timer to turn off LED after 5 seconds */
		      for(;;); /* failure! */
		    }
		}
	  GPIO_PortToggle(BOARD_INITPINS_LED_BLUE_GPIO, 1<<BOARD_INITPINS_LED_BLUE_PIN); /* toggle blue LED */
		vTaskDelay(pdMS_TO_TICKS(50));
	}
}

void FreeRTOS_Timers_Init(void) {
    if (xTaskCreate(
    		TimersTask,  /* pointer to the task */
        "Timers", /* task name for kernel awareness debugging */
		500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
      /*lint -e527 */
       for(;;){} /* error! probably out of memory */
      /*lint +e527 */
    }
}
#endif
