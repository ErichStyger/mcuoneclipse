
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "leds.h"
#include "McuWait.h"
#include "McuSemihost.h"

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
#endif

  McuWait_Init();
  McuSemiHost_Init();
  LEDS_Init();
  McuSemihost_WriteString0((unsigned char*)"*STOP*"); /* terminate LinkServer runner */
  for(;;) {
    LEDS_Neg(LEDS_BLUE);
    McuWait_Waitms(100);
  }

  while(1) {
  }
  return 0;
}
