/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "fsl_power.h"
#include "application.h"

int main(void) {
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();

   /* set BOD VBAT level to 1.65V, otherwise higher clock speeds might cause a brown-out! */
  POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);

  APP_Run();
  while(1) {
    __asm volatile ("nop");
  }
  return 0 ;
}
