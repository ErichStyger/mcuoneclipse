/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_power.h"
#include "platform.h"
#include "McuRTOS.h"

int main(void) {
  int i;
  BOARD_InitBootPins();
  BOARD_InitBootClocks();

  if (i>0) {
    return -1; 
  }
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE);

  PL_Init();
  vTaskStartScheduler();
  return 0;
}
