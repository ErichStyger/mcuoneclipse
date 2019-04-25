/*
 * Copyright 2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "veneer_table.h"
#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define PRINTF_NSE DbgConsole_Printf_NSE
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void SystemInit (void)
{
}
/*!
 * @brief Main function
 */
int main(void)
{
    int result;


    
    PRINTF_NSE("Welcome in normal world!\r\n");
    PRINTF_NSE("This is a text printed from normal world!\r\n");

    result = StringCompare_NSE(&strcmp, "Test1\r\n", "Test2\r\n");
    if (result == 0)
    {
        PRINTF_NSE("Both strings are equal!\r\n");
    }
    else
    {
        PRINTF_NSE("Both strings are not equal!\r\n");
    }
    while (1)
    {
    }
}
