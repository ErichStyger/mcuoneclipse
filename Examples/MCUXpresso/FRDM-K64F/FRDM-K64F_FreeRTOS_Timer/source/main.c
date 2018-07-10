#if 0
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

#define USE_SEGGER_SYSVIEW  (1)

#if USE_SEGGER_SYSVIEW

#include "SEGGER_SYSVIEW.h"
#include "SEGGER_RTT.h"

#define SYSVIEW_DEVICE_NAME "FRDMK64F Cortex-M4"
#define SYSVIEW_RAM_BASE (0x1FFF0000)

extern SEGGER_RTT_CB _SEGGER_RTT;
extern const SEGGER_SYSVIEW_OS_API SYSVIEW_X_OS_TraceAPI;

/* The application name to be displayed in SystemViewer */
#ifndef SYSVIEW_APP_NAME
	#define SYSVIEW_APP_NAME "FreeRTOS Software Timer Example"
#endif

/* The target device name */
#ifndef SYSVIEW_DEVICE_NAME
	#define SYSVIEW_DEVICE_NAME "Generic Cortex device"
#endif

/* Frequency of the timestamp. Must match SEGGER_SYSVIEW_GET_TIMESTAMP in SEGGER_SYSVIEW_Conf.h */
#define SYSVIEW_TIMESTAMP_FREQ (configCPU_CLOCK_HZ)

/* System Frequency. SystemcoreClock is used in most CMSIS compatible projects. */
#define SYSVIEW_CPU_FREQ configCPU_CLOCK_HZ

/* The lowest RAM address used for IDs (pointers) */
#ifndef SYSVIEW_RAM_BASE
	#define SYSVIEW_RAM_BASE 0x20000000
#endif

static void _cbSendSystemDesc(void) {
    SEGGER_SYSVIEW_SendSysDesc("N=" SYSVIEW_APP_NAME ",D=" SYSVIEW_DEVICE_NAME ",O=FreeRTOS");
    SEGGER_SYSVIEW_SendSysDesc("I#15=SysTick");
}

void SEGGER_SYSVIEW_Conf(void) {
    SEGGER_SYSVIEW_Init(SYSVIEW_TIMESTAMP_FREQ, SYSVIEW_CPU_FREQ, &SYSVIEW_X_OS_TraceAPI, _cbSendSystemDesc);
    SEGGER_SYSVIEW_SetRAMBase(SYSVIEW_RAM_BASE);
}
#endif

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

/* global variables to show the timer status in the debugger */
static int debugTimer1Sec, debugTimer5Sec;

static void vTimerCallback1SecExpired(xTimerHandle pxTimer) {
#if USE_SEGGER_SYSVIEW
	SEGGER_SYSVIEW_PrintfTarget("1 Sec Timer (ID %d) expired", (int)pvTimerGetTimerID(pxTimer));
#endif
    GPIO_PortToggle(BOARD_INITPINS_LED_RED_GPIO, 1<<BOARD_INITPINS_LED_RED_PIN); /* toggle red LED */
    debugTimer1Sec = !debugTimer1Sec;
}

static void vTimerCallback5SecExpired(xTimerHandle pxTimer) {
	/* this timer callback turns off the green LED */
#if USE_SEGGER_SYSVIEW
	SEGGER_SYSVIEW_PrintfTarget("5 Sec Timer (ID %d) expired", (int)pvTimerGetTimerID(pxTimer));
#endif
    GPIO_PortSet(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* turn off green LED */
    debugTimer5Sec = 0;
}

static void AppTask(void *param) {
	xTimerHandle timerHndl1Sec, timerHndl5SecTimeout;

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
#if USE_SEGGER_SYSVIEW
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
#if USE_SEGGER_SYSVIEW
    SEGGER_SYSVIEW_PrintfTarget("Start of 5 Second Timer");
#endif
    if (xTimerStart(timerHndl1Sec, 0)!=pdPASS) {
      for(;;); /* failure! */
    }
    debugTimer1Sec = 1;
	for(;;) {
		if (!GPIO_PinRead(BOARD_INITPINS_SW3_GPIO, BOARD_INITPINS_SW3_PIN)) { /* pin LOW ==> SW03 push button pressed */
			GPIO_PortClear(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* Turn green LED on */
			debugTimer5Sec = 1;
#if USE_SEGGER_SYSVIEW
		    SEGGER_SYSVIEW_PrintfTarget("Reset of 5 Second Timer");
#endif
		    if (xTimerReset(timerHndl5SecTimeout, 0)!=pdPASS) { /* start timer to turn off LED after 5 seconds */
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

#if USE_SEGGER_SYSVIEW
    SEGGER_SYSVIEW_Conf();
#endif

    GPIO_PortClear(BOARD_INITPINS_LED_BLUE_GPIO, 1<<BOARD_INITPINS_LED_BLUE_PIN); /* turn on LED */
    GPIO_PortSet(BOARD_INITPINS_LED_BLUE_GPIO, 1<<BOARD_INITPINS_LED_BLUE_PIN); /* turn off LED */
    PRINTF("Hello World\n");
    /*lint -FALLTHROUGH*/
    if (xTaskCreate(
    	AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
		300/sizeof(StackType_t), /* task stack size */
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
#else

/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "peripherals.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
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

#define B0 (1 << 0)
#define B1 (1 << 1)

#define sw1_Detection               PORTA_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void write_task_1(void *pvParameters);
static void write_task_2(void *pvParameters);
static void read_task(void *pvParameters);
/*******************************************************************************
 * Globals
 ******************************************************************************/
static EventGroupHandle_t event_group = NULL;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
	BOARD_InitPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	//BOARD_Init_Switches();
	BOARD_InitDebugConsole();
	event_group = xEventGroupCreate();
	if (xTaskCreate(write_task_1, "WRITE_TASK_1", configMINIMAL_STACK_SIZE + 38, NULL, tskIDLE_PRIORITY + 1, NULL) !=
			pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	if (xTaskCreate(write_task_2, "WRITE_TASK_2", configMINIMAL_STACK_SIZE + 38, NULL, tskIDLE_PRIORITY + 1, NULL) !=
			pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	if (xTaskCreate(read_task, "READ_TASK", configMINIMAL_STACK_SIZE + 38, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	/* Start scheduling. */
	vTaskStartScheduler();
	for (;;)
		;
}

/*!
 * @brief write_task_1 function
 */
static void write_task_1(void *pvParameters)
{
	while (1)
	{
		printf("write_task_1\n");
		vTaskDelay(500);
	}
}

/*!
 * @brief write_task_2 function
 */
static void write_task_2(void *pvParameters)
{
	while (1)
	{
		//        xEventGroupSetBits(event_group, B1);
		printf("write_task_2\n");
		vTaskDelay(500);
	}
}

/*!
 * @brief read_task function
 */
static void read_task(void *pvParameters)
{
	EventBits_t event_bits;
	while (1)
	{
		event_bits = xEventGroupWaitBits(event_group,    /* The event group handle. */
				B0 | B1,        /* The bit pattern the event group is waiting for. */
				pdTRUE,         /* BIT_0 and BIT_4 will be cleared automatically. */
				pdFALSE,        /* Don't wait for both bits, either bit unblock task. */
				portMAX_DELAY); /* Block indefinitely to wait for the condition to be met. */

		if ((event_bits & (B0 | B1)) == (B0 | B1))
		{
			PRINTF("Both bits are set.");
		}
		else if ((event_bits & B0) == B0)
		{
			PRINTF("Bit B0 is set.\r\n");
		}
		else if ((event_bits & B1) == B1)
		{
			PRINTF("Bit B1 is set.\r\n");
		}
	}
}

void sw2_Detection(void)
{
	GPIO_ClearPinsInterruptFlags(BOARD_INITPINS_SW2_GPIO, 1U << BOARD_INITPINS_SW2_PIN);
	BaseType_t xHigherPriorityTaskWoken, xResult;

	// xHigherPriorityTaskWoken must be initialised to pdFALSE.
	xHigherPriorityTaskWoken = pdFALSE;

	// Set bit 0 and bit 4 in xEventGroup.
	xResult = xEventGroupSetBitsFromISR(
			event_group,    // The event group being updated.
			B0,   // The bits being set.
			&xHigherPriorityTaskWoken );

	// Was the message posted successfully?
	if( xResult == pdPASS )
	{
		// If xHigherPriorityTaskWoken is now set to pdTRUE then a context
		// switch should be requested.  The macro used is port specific and
		// will be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() -
		// refer to the documentation page for the port being used.
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}

}

#endif
