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
#include "disk.h"

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
#if PL_CONFIG_USE_SD_CARD
  bool sdDiskPresent = false;
  bool present;
#endif
  for(;;) {
#if PL_CONFIG_USE_SD_CARD
    present = DISK_IsInserted((unsigned char*)DISK_DRIVE_SD_CARD);
    if (!sdDiskPresent && present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_INSERTED);
      sdDiskPresent = true;
    } else if (sdDiskPresent && !present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_REMOVED);
      sdDiskPresent = false;
    }
#endif
    McuLED_Toggle(tinyLED);
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for */
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
  vTaskStartScheduler();
}
