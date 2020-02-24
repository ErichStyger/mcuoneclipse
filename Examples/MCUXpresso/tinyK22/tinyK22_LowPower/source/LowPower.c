/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "LowPower.h"
#include "fsl_pit.h"
#include "fsl_smc.h"

#if LP_MODE==LP_MODE_WAIT || LP_MODE==LP_MODE_STOP
#define PIT_BASEADDR       PIT
#define PIT_SOURCE_CLOCK   CLOCK_GetFreq(kCLOCK_BusClk)
#define PIT_CHANNEL        kPIT_Chnl_0
#define PIT_HANDLER        PIT0_IRQHandler
#define PIT_IRQ_ID         PIT0_IRQn

void PIT_HANDLER(void) {
  PIT_ClearStatusFlags(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerFlag);
  __DSB();
}

static void ConfigurePIT(void) {
  pit_config_t config;

  PIT_GetDefaultConfig(&config);
  config.enableRunInDebug = false;
  PIT_Init(PIT_BASEADDR, &config);
  PIT_SetTimerPeriod(PIT_BASEADDR, PIT_CHANNEL, MSEC_TO_COUNT(10*1000U, PIT_SOURCE_CLOCK));
  PIT_EnableInterrupts(PIT_BASEADDR, PIT_CHANNEL, kPIT_TimerInterruptEnable);
  NVIC_SetPriority(PIT_IRQ_ID, 0);
  EnableIRQ(PIT_IRQ_ID);
  PIT_StartTimer(PIT_BASEADDR, PIT_CHANNEL);
}
#endif

void LP_EnterLowPower(void) {
#if LP_MODE==LP_MODE_RUN
  /* not entering any low power mode */
#elif LP_MODE==LP_MODE_WAIT
  SMC_SetPowerModeWait(SMC);
   /* next interrupt will wake us up */
#elif LP_MODE==LP_MODE_STOP
  SMC_SetPowerModeStop(SMC, kSMC_PartialStop2); /* Partial Stop with system clock disabled and bus clock enabled */
  /* next interrupt will wake us up */
#endif
}

void LP_Init(void) {
#if LP_MODE==LP_MODE_RUN
  /* not entering any low power mode */
#elif LP_MODE==LP_MODE_WAIT
  ConfigurePIT(); /* configure timer used as wake-up source */
#elif LP_MODE==LP_MODE_STOP
  ConfigurePIT(); /* configure timer used as wake-up source */
#endif
}
