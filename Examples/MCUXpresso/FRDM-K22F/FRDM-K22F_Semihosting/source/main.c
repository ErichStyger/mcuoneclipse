#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_debug_console.h"

#include "McuSemihost.h"
#include "McuWait.h"

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();

  //printf("hello world with semihosting!\n");

  McuWait_Init();
  McuSemiHost_Init();

  McuSemiHost_Test();
  McuSemiHost_Deinit();

  for(;;) {}
  return 0;
}
