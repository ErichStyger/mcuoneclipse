/*
 * The Clear BSD License
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#include "SEGGER_SYSVIEW.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "FreeRTOS_Timers.h"
#include "SysView.h"
#include "fsl_ftm.h"
#include "App_Config.h"
#include "InterProcessComm.h"

#if APP_CONFIG_USE_FREERTOS
/*!
 * @brief Second task, lower priority.
 */
#if configSUPPORT_STATIC_ALLOCATION
#else
static void second_task(void *pvParameters) {
  for(;;) {
    if (GPIO_PinRead(BOARD_INITPINS_SW3_GPIO, BOARD_INITPINS_SW3_PIN)) { /* pin HIGH ==> SW03 push button not pressed */
      vTaskDelay(pdMS_TO_TICKS(50));
    } else {
      for(int i=0; i<20; i++) {
        GPIO_PortToggle(BOARD_INITPINS_LED_GREEN_GPIO, 1<<BOARD_INITPINS_LED_GREEN_PIN); /* toggle green LED on */
        vTaskDelay(pdMS_TO_TICKS(5));
      }
    }
  }
}
#endif
#endif

#if APP_CONFIG_USE_FREERTOS
/*!
 * @brief First task, higher priority.
 */
#if configSUPPORT_STATIC_ALLOCATION
#define FIRST_TASK_SIZE   configMINIMAL_STACK_SIZE+100
#if configSUPPORT_STATIC_ALLOCATION
  static StaticTask_t xFirstTaskTCBBuffer;
  static StackType_t xFirstStack[FIRST_TASK_SIZE];
#endif

#else
#if 0
static void first_task(void *pvParameters) {
  if (xTaskCreate(second_task, "second_task", 500/sizeof(StackType_t), NULL, 3, NULL) != pdPASS) {
      PRINTF("Task creation failed!.\r\n");
      vTaskSuspend(NULL);
  }
  /* dummy code, print counter and delay */
  for (int counter = 0;; counter++) {
#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
      SEGGER_SYSVIEW_PrintfTarget("first task counter: %d ", counter++);
#endif
      vTaskDelay(pdMS_TO_TICKS(100));
  }
}
#endif
#endif
#endif

static void first_task(void *pvParameters) {
  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

#if 0
uint32_t RTOS_RunTimeCounter; /* runtime counter, used for configGENERATE_RUNTIME_STATS */
void FTM0_IRQHandler(void) {
  /* Clear interrupt flag.*/
  FTM_ClearStatusFlags(FTM0, kFTM_TimeOverflowFlag);
  RTOS_RunTimeCounter++; /* increment runtime counter */
}

void RTOS_AppConfigureTimerForRuntimeStats(void) {
  RTOS_RunTimeCounter = 0;
  EnableIRQ(FTM0_IRQn);
}

uint32_t RTOS_AppGetRuntimeCounterValueFromISR(void) {
#if configGENERATE_RUN_TIME_STATS
  #if configGENERATE_RUN_TIME_STATS_USE_TICKS
  return xTaskGetTickCountFromISR(); /* using RTOS tick counter */
  #else /* using timer counter */
  return RTOS_RunTimeCounter;
  #endif
#else
  return 0; /* dummy value */
#endif
}
#endif

void __assertion_failed(char *_Expr)  {
  for(;;) {
    __asm("nop");
  }
}

void __assert_func(const char *file, int line, const char *func, const char *expr) {
  for(;;) {
    __asm("nop");
  }
}

#if configSUPPORT_STATIC_ALLOCATION && configUSE_TIMERS
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

/* If static allocation is supported then the application must provide the
   following callback function - which enables the application to optionally
   provide the memory that will be used by the timer task as the task's stack
   and TCB. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#endif

#if configSUPPORT_STATIC_ALLOCATION
/* static memory allocation for the IDLE task */
#define IDLE_TASK_SIZE   (100)
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[IDLE_TASK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = IDLE_TASK_SIZE;
}
#endif

void BOARD_InitBootPeripherals(void);
extern const uint8_t FreeRTOSDebugConfig[];
/*!
 * @brief Main function
 */
int main(void) {
	/* Init board hardware. */
	//BOARD_InitPins();
	//BOARD_BootClockRUN();
	//BOARD_InitDebugConsole();
	//BOARD_InitBootPeripherals();

  #if APP_CONFIG_USE_FREERTOS
	//if (FreeRTOSDebugConfig[0]==0) { /* dummy usage */
	//  for(;;);
	//}
  #endif
	#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
	SysView_Init();
	#endif
  #if APP_CONFIG_USE_FREERTOS
	//FreeRTOS_Timers_Init();
	//IPC_Init();

#if configSUPPORT_STATIC_ALLOCATION
  if (xTaskCreateStatic(first_task, "first_task", FIRST_TASK_SIZE, NULL, tskIDLE_PRIORITY+1, &xFirstStack[0], &xFirstTaskTCBBuffer)==NULL) {
    for(;;){} /* task creation failed */
  }
#else
	if (xTaskCreate(first_task, "first_task", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS)  {
		for(;;){}
	}
#endif
	vTaskStartScheduler();
  #endif
	for(;;){}
}

