/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "leds.h"
#include "fsl_pit.h"

uint32_t McuRTOS_RunTimeCounter; /* runtime counter, used for configGENERATE_RUNTIME_STATS */

#if 0 /* using Cortex cycle counter */
static uint32_t prevCycleCounter, cycleCntCounter = 0;

void AppConfigureTimerForRuntimeStats(void) {
  cycleCntCounter = 0;
  McuArmTools_InitCycleCounter();
  prevCycleCounter = McuArmTools_GetCycleCounter();
}

uint32_t AppGetRuntimeCounterValueFromISR(void) {
  uint32_t newCntr, diff;

  newCntr = McuArmTools_GetCycleCounter();
  diff = newCntr-prevCycleCounter;
  prevCycleCounter = newCntr;
  cycleCntCounter += diff>>12; /* scale down the counter */
  return cycleCntCounter;
}
#else /* using PIT timer */

#define PIT_BASEADDR       PIT
#define PIT_SOURCE_CLOCK   CLOCK_GetFreq(kCLOCK_BusClk)
#define PIT_CHANNEL        kPIT_Chnl_0
#define PIT_HANDLER        PIT0_IRQHandler
#define PIT_IRQ_ID         PIT0_IRQn

void PIT_HANDLER(void) {
  PIT_ClearStatusFlags(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerFlag);
  McuRTOS_RunTimeCounter++;
  __DSB();
}

void AppConfigureTimerForRuntimeStats(void) {
  pit_config_t config;

  PIT_GetDefaultConfig(&config);
  config.enableRunInDebug = false;
  PIT_Init(PIT_BASEADDR, &config);
  PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL, USEC_TO_COUNT(100U, PIT_SOURCE_CLOCK));
  PIT_EnableInterrupts(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);
  NVIC_SetPriority(PIT_IRQ_ID, 0);
  EnableIRQ(PIT_IRQ_ID);
  PIT_StartTimer(PIT_BASEADDR, PIT_CHANNEL);
}

uint32_t AppGetRuntimeCounterValueFromISR(void) {
  return McuRTOS_AppGetRuntimeCounterValueFromISR();
}
#endif

static void AppTask(void *pv) {
  for(;;) {
    McuLED_Toggle(tinyLED);
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for */
}

#if configSUPPORT_STATIC_ALLOCATION
/* static memory allocation for the IDLE task */
#define IDLE_TASK_SIZE   100
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[IDLE_TASK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = IDLE_TASK_SIZE;
}
#endif

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

static TaskHandle_t staticTaskHandle;
#define STATIC_TASK_STACK_SIZE   (100)
static StaticTask_t xTaskBuffer;
static StackType_t xStack[STATIC_TASK_STACK_SIZE];

static void staticTask(void *pv) {
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  PL_Init();
  /* just some LED test code */
  McuLED_On(tinyLED);
  McuWait_Waitms(100);
  McuLED_Off(tinyLED);
  /* creating task */
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

  staticTaskHandle = xTaskCreateStatic(staticTask, "staticTask", STATIC_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, xStack, &xTaskBuffer);
  if (staticTaskHandle==NULL) {
    for(;;){};
  }
  vTaskStartScheduler();
}
