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

#if APP_CONFIG_USE_FREERTOS
/*!
 * @brief First task, higher priority.
 */
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

void BOARD_InitBootPeripherals(void);
extern const uint8_t FreeRTOSDebugConfig[];
/*!
 * @brief Main function
 */
int main(void) {
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	//BOARD_InitDebugConsole();
	BOARD_InitBootPeripherals();

  #if APP_CONFIG_USE_FREERTOS
	if (FreeRTOSDebugConfig[0]==0) { /* dummy usage */
	  for(;;);
	}
  #endif
	#if APP_CONFIG_USE_SEGGER_SYSTEMVIEW
	SysView_Init();
	#endif
  #if APP_CONFIG_USE_FREERTOS
	FreeRTOS_Timers_Init();
	IPC_Init();

	if (xTaskCreate(first_task, "first_task", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+4, NULL) != pdPASS)  {
		PRINTF("Task creation failed!.\r\n");
		for(;;){}
	}
	vTaskStartScheduler();
  #endif
	for(;;){}
}

