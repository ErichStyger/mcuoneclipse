#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"

static int test1(void) {
  __asm("bkpt #1"); /* will hit breakpoint and move PC to next line */
  return 1;
}

static int test2(void) {
  __asm("bkpt #2"); /* will hit breakpoint and continue */
  return 1;
}

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
#endif
  test1();
  test2();
  while(1) {
    __asm volatile ("nop");
    test1();
    test2();
  }
  return 0 ;
}
