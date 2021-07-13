/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC804.h"
#include "fsl_debug_console.h"
#include "application.h"

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins(); /* muxes SPI pins */
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals(); /* initializes PLU */
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  //BOARD_InitDebugConsole();
#endif
  APP_Run();
  return 0 ;
}
