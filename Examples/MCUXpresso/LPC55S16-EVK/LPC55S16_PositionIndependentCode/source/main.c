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
#include "lib.h"
#include "module.h"
#include "myLib.h"

/* Force the counter to be placed into memory. */
volatile int i, j = 0 ;
void foobar(void) {}

typedef void(*fp_t)(void);
extern unsigned int _sgot, _sgot_plt; /* symbols provided by the linker */
void BindLibrary(fp_t fp) {
  ((uint32_t*)&_sgot_plt)[5] = (uint32_t)foobar; /* 0x2000'0014 */
}

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
   // i = LIB_Utility();
#if 1
    BindLibrary((fp_t)MyLib_Calc);
    i = MyLib_Calc(3);
    //void foo(void);
    //void bar(void);
    //foo();
    //bar();
    //foobar();
    //MODULE_Init();
    /* Enter an infinite loop, just incrementing a counter. */
#endif
    while(1) {
        i++;
        j++;
  //      PICModule_DoThings();
        __asm volatile ("nop");
    }
    return 0 ;
}

