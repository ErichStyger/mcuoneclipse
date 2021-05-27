/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S16.h"
#include "fsl_debug_console.h"
#include "pic_module.h"
#include "lib.h"
#include "module.h"

/* Force the counter to be placed into memory. */
volatile int i, j = 0 ;

int main(void) {
    /* Init board hardware. */
//    BOARD_InitBootPins();
//    BOARD_InitBootClocks();
//    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
//    BOARD_InitDebugConsole();
#endif
//    PICModule_Init();
//    LIB_Init();
    MODULE_Init();
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++;
        j++;
  //      PICModule_DoThings();
        __asm volatile ("nop");
    }
    return 0 ;
}
