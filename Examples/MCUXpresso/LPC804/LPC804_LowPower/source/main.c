/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC804.h"
#include "application.h"

int main(void) {
  /* Init board hardware. */
#if 1 /* empty */
  BOARD_InitBootPins();
#endif
  BOARD_InitBootClocks();
#if 1 /* empty */
  BOARD_InitBootPeripherals();
#endif
//  for(;;) {
//    __asm volatile("nop");
//  }
  APP_Run();
  return 0 ;
}
