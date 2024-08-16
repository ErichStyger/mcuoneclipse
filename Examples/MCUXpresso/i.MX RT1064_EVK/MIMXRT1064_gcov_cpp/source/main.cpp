/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MIMXRT1064_gcov_cpp.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "McuCoverage.h"
#include "rdimon/McuRdimon.h"
#include "McuSemihost.h"

int main(void) {
#if McuSemihost_CONFIG_IS_ENABLED
  McuSemiHost_Init();
#endif
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init();
#endif
#if McuCoverage_CONFIG_IS_ENABLED
  McuCoverage_Init();  /* initialize library */
  McuCoverage_Check();
#endif    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
