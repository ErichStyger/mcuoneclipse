/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "fsl_power.h"
#include "application.h"


int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  /* BOARD_InitBootPeripherals(); */
  /* Init FSL debug console. */
  /* BOARD_InitDebugConsole(); */

  /* set BOD VBAT level to 1.65V */
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
  CLOCK_AttachClk(kTRACE_DIV_to_TRACE);

  PRINTF("Hello World\n");
  APP_Run();
  return 0 ;
}
