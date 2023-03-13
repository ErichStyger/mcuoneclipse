/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"

#include "McuSemihost.h"
#include "McuWait.h"
#include "benchmark.h"
#include <stdio.h>

int main(void) {
  BOARD_InitBootPins();
  BOARD_InitBootClocks();

  McuWait_Init();
#if !BENCHMARK_USE_STDLIB
  McuSemiHost_Init();
#endif
  //printf("hello world!\n");

  //Benchmark_Run();
  McuSemiHost_Test();
#if !BENCHMARK_USE_STDLIB
  McuSemiHost_Deinit();
#endif
#if 0
  for(;;) {
    McuSemihost_WriteString((const unsigned char*)"hello with semihosting!\n");
    McuWait_Waitms(500);
  }
#endif
  for(;;) {}
  return 0;
}
