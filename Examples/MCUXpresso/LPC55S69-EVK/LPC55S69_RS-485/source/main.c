/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "application.h"

int main(void) {
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();

  APP_Run();

  return 0;
}
