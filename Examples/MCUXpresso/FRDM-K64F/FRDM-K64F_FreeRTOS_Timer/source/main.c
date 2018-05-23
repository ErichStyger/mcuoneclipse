/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    FRDM-K64F_FreeRTOS_Timer.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* TODO: insert other definitions and declarations here. */

static uint32_t cycleCntCounter = 0;

void FTM0_IRQHandler(void) {
	cycleCntCounter++;
}

void AppConfigureTimerForRuntimeStats(void) {
  cycleCntCounter = 0;
}

uint32_t AppGetRuntimeCounterValueFromISR(void) {
  return cycleCntCounter;
}

/* configuration items for timers in FreeRTOSConfig.h
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            (configMINIMAL_STACK_SIZE * 2)
 */

static void vTimerCallbackRedToggle(xTimerHandle pxTimer) {
    GPIO_PortToggle(BOARD_INITPINS_LED_RED_GPIO, 1<<BOARD_INITPINS_LED_RED_PIN); /* toggle red LED */
}

static void vTimerCallbackGreenOff(xTimerHandle pxTimer) {
	/* this timer callback turns off the green LED */
    GPIO_PortSet(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* turn green LED */
}

static void AppTask(void *param) {
	xTimerHandle timerHndlRed, timerHndlGreen;

	(void)param; /* not used */
    timerHndlRed = xTimerCreate(
    		"timerRed", /* name */
			pdMS_TO_TICKS(1000), /* period/time */
			pdTRUE, /* auto reload */
			(void*)0, /* timer ID */
			vTimerCallbackRedToggle); /* callback */
    if (timerHndlRed==NULL) {
      for(;;); /* failure! */
    }
    if (xTimerStart(timerHndlRed, 0)!=pdPASS) {
      for(;;); /* failure! */
    }

    timerHndlGreen = xTimerCreate(
    		"timerGreen", /* name */
			pdMS_TO_TICKS(5000), /* period/time */
			pdFALSE, /* auto reload */
			(void*)1, /* timer ID */
			vTimerCallbackGreenOff); /* callback */
    if (timerHndlGreen==NULL) {
      for(;;); /* failure! */
    }
	for(;;) {
		if (!GPIO_PinRead(BOARD_INITPINS_SW3_GPIO, BOARD_INITPINS_SW3_PIN)) { /* pin LOW ==> SW03 push button pressed */
			GPIO_PortClear(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* Turn green LED on */
#if 0
		    if (xTimerStart(timerHndlGreen, 0)!=pdPASS) { /* start timer to turn off LED after 5 seconds */
		      for(;;); /* failure! */
		    }
#endif
		    if (xTimerReset(timerHndlGreen, 0)!=pdPASS) { /* start timer to turn off LED after 5 seconds */
		      for(;;); /* failure! */
		    }
		}
	    //GPIO_PortToggle(BOARD_INITPINS_LED_BLUE_GPIO, 1<<BOARD_INITPINS_LED_BLUE_PIN); /* toggle blue LED */
		vTaskDelay(pdMS_TO_TICKS(50));
	}
}


/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    GPIO_PortClear(BOARD_INITPINS_LED_BLUE_GPIO, 1<<BOARD_INITPINS_LED_BLUE_PIN); /* turn on LED */
    GPIO_PortSet(BOARD_INITPINS_LED_BLUE_GPIO, 1<<BOARD_INITPINS_LED_BLUE_PIN); /* turn off LED */
    PRINTF("Hello World\n");
    /*lint -FALLTHROUGH*/
    if (xTaskCreate(
    	AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE+20, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
      /*lint -e527 */
       for(;;){} /* error! probably out of memory */
      /*lint +e527 */
    }

    vTaskStartScheduler(); /* run RTOS */

    return 0 ;
}
