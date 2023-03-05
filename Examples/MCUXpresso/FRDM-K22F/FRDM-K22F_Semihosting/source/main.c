/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_debug_console.h"

#include "McuSemihost.h"
#include "McuWait.h"

int main(void) {
  BOARD_InitBootPins();
  BOARD_InitBootClocks();

  McuWait_Init();
  McuSemiHost_Init();

  McuSemiHost_Test();
  McuSemiHost_Deinit();

  //for(;;) {
    McuSemihost_WriteString((const unsigned char*)"hello with semihosting!\n");
    McuWait_Waitms(500);
  //}
  return 0;
}
