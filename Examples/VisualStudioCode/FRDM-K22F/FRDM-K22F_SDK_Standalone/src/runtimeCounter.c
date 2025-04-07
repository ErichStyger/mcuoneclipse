/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * Application which can disable debugging.
 */

#include "runtimeCounter.h"
#include <stdint.h>
#include "McuRTOS.h"
#include "McuArmTools.h"

uint32_t McuRTOS_RunTimeCounter; /* runtime counter, used for configGENERATE_RUNTIME_STATS */

#if McuLib_CONFIG_CPU_IS_LPC55xx /* using Cortex cycle counter */

  static uint32_t prevCycleCounter, cycleCntCounter = 0;

  void AppConfigureTimerForRuntimeStats(void) {
    cycleCntCounter = 0;
    McuArmTools_InitCycleCounter();
    prevCycleCounter = McuArmTools_GetCycleCounter();
  }

  unsigned int AppGetRuntimeCounterValueFromISR(void) {
    uint32_t newCntr, diff;

    newCntr = McuArmTools_GetCycleCounter();
    diff = newCntr-prevCycleCounter;
    prevCycleCounter = newCntr;
    cycleCntCounter += diff>>12; /* scale down the counter */
    return cycleCntCounter;
  }

#elif McuLib_CONFIG_CPU_IS_KINETIS /* using hardware timer with 100 us period */

  #include "fsl_pit.h"
  
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