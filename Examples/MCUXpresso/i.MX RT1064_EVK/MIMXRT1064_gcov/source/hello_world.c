/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "../gcov/gcov_support.h"
#include "test.h"
/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    gcov_init(); /* initialize coverage stubs and support */

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    PRINTF("hello world.\r\n");

    TEST_Test();
    //gcov_check();
    gcov_write_files(); /* write coverage files, might take a while depending how many files are covered */

    while (1)
    {
        ch = GETCHAR();
        PUTCHAR(ch);
    }
}
