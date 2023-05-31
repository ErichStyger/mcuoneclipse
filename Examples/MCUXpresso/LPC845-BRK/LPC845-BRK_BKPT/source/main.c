#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"

#ifdef DEBUG
  #define BREAK_1 __asm("bkpt #1")
  #define BREAK_2 __asm("bkpt #2")
#else
  #define BREAK_1 /* empty */
  #define BREAK_2 /* empty */
#endif

static int test1(void) {
  BREAK_1; /* hit breakpoint and move PC to next line */
  return 1;
}

static int test2(void) {
  BREAK_2; /* hit breakpoint and continue */
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
