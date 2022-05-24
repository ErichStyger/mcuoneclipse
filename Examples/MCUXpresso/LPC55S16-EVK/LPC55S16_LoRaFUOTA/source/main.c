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
#include "fsl_power.h"

int main(void) {

	// IF LORA add these lines to INCLUDE!!!!!!!!!!!!!!
/*
 * "${LoRaSrc}"
"${LoRaSrc}/boards"
"${LoRaSrc}/boards/LPC55S16-EVK"
"${LoRaSrc}/system"
"${LoRaSrc}/radio"
"${LoRaSrc}/mac"
"${LoRaSrc}/mac/region"
"${LoRaSrc}/apps/LoRaMac/common"
"${LoRaSrc}/apps/LoRaMac/common/LmHandler"
"${LoRaSrc}/apps/LoRaMac/common/LmHandler/packages"
"${LoRaSrc}/peripherals"
"${LoRaSrc}/peripherals/soft-se"
 */
  /* Init board hardware. */
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach main clock divide to FLEXCOMM0 (debug console) */
   CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  BOARD_InitDebugConsole();
  APP_Run();
  return 0 ;
}
