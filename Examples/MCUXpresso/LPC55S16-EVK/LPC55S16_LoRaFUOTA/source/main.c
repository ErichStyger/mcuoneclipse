/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S16.h"
#include "fsl_debug_console.h"
#include "application.h"
#include "W25Q128.h"
#include "fsl_power.h"

int main(void) {

    /* attach 12 MHz clock to SPI3 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);
    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC3_RST_SHIFT_RSTn);
  //POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  //SystemCoreClockUpdate();
  BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
//  BOARD_InitDebugConsole();
#endif
  APP_Run();
  return 0 ;
}
