/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#include "application.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  APP_Run();
  return 0;
}
