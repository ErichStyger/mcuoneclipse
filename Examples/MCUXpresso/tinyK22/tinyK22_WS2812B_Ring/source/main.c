/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "application.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "peripherals.h"


uint8_t array[12][16];

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();

  for(int i=0; i<12; i++) {
    for(int j=0; j<16; j++) {
      array[i][j] = i+j;
    }
  }

  APP_Run();
  return 0 ;
}

