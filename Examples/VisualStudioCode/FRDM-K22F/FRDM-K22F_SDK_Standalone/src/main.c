/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "MK22F51212.h"
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  #include "LPC55S69_cm33_core0.h"
  #include "fsl_power.h"
#endif
#include "platform.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "McuArmTools.h"

int main(void) {
  BOARD_InitBootPins();
  BOARD_InitBootClocks();

 #if McuLib_CONFIG_CPU_IS_LPC55xx
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE);
 #endif
  PL_Init();
  vTaskStartScheduler();
  return 0;
}
