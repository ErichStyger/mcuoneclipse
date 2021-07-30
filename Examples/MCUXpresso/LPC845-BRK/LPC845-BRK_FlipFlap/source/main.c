/*
 * Copyright (c) 2021, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"

#include "application.h"

#include "McuXFormat.h"

uint8_t buff[256];
void debugPrint(uint8_t color, uint8_t *buffer, const uint8_t *format, ...){
  va_list args;
  va_start(args, format);
  McuXFormat_xsprintf((char*)buffer,(const char*)format,args);
  va_end(args);
//  scrollPrintColor(buffer,color);
}

// And here is the call to it
//debugPrint(RED,buff,"This is a test of the debugPrint %d %d %d %s %d",1,2,3,"four",5);
// and what it actually prints:
//This is a test of the debugPrint 536872884 1 0 0
// It actually printed an extra space between the final two zeros

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    debugPrint(123,buff,(uint8_t*)"This is a test of the debugPrint %d %d %d %s %d",1,2,3,"four",5);
    APP_Run();
    for(;;) {
      __asm("nop");
    }
    return 0 ;
}
