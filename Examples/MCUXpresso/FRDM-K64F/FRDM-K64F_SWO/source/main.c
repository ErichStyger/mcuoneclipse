/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"

#include "platform.h"
#include "McuSWO.h"
#include "McuWait.h"

int main(void) {
  int i = 0;
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();

  PL_Init(); /* initializes modules including SWO */
  //McuSWO_TestStdio(); /* set a breakpoint here and configure SWO (SWO Trace Config) and enable SWO ITM Console */
  while(1) {
    __asm volatile ("nop");
    McuSWO_printf("hello from SWO: %d\n", i);
    i++;
    McuWait_Waitms(1000);
  }
  return 0 ;
}
