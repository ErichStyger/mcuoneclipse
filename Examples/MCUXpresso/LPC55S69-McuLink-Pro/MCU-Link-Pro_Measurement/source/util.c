/*
 * util.c
 *
 *  Created on: 28 Mar 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include "util.h"
#include "board.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;
uint8_t sysTickInitiated = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/
#if !McuLib_CONFIG_SDK_USE_FREERTOS
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}
#endif

void SysTick_DelayTicks(uint32_t n)
{
    if (sysTickInitiated == 0)
    {
        SysTick_Config(SystemCoreClock / 1000U);
        sysTickInitiated = 1;
    }
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}
