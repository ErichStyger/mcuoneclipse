/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*
 * @file microseconds_sysclk.c
 * @brief Microseconds sysclk timer driver source file
 *
 * Notes: The driver configure sysclk as lifetime timer
 */
#include "bootloader_common.h"
#include "microseconds.h"
#include "fsl_device_registers.h"
#include <stdarg.h>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

enum
{
    kFrequency_1MHz = 1000000UL
};

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
//! @brief Tracks number of timer rollovers for extended time keeping
//!        with 32 bits here + the 24 bits of the counter for lower resolution
//!        it will be years worth of time
volatile uint32_t s_highCounter;
uint32_t s_tickPerMicrosecondMul8; //!< This value equal to 8 times ticks per microseconds
uint64_t s_timeoutTicks;           //!< Tick value of timeout.
////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Initialize and start the timer facilities using the SysTick.
void microseconds_init(void)
{
    s_highCounter = 0;
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk; // Set reload register to max value
    SysTick->VAL = 0;                        // As per ARM reference initialization, set initial value to 0
                                             //  interrupts are only triggered when going from 1 to 0

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | // Set timer to core clock frequency
                    SysTick_CTRL_TICKINT_Msk |   // Enable interrupts on timeout
                    SysTick_CTRL_ENABLE_Msk;     // Enable SysTick IRQ and SysTick Timer

    /* Calculate this value early
     * The reason why use this solution is that lowest clock frequency supported by L0PB and L4KS
     * is 0.25MHz, this solution will make sure ticks per microscond is greater than 0.
     */
    s_tickPerMicrosecondMul8 = (SystemCoreClock * 8) / kFrequency_1MHz;

    // Make sure this value is greater than 0
    if (!s_tickPerMicrosecondMul8)
    {
        s_tickPerMicrosecondMul8 = 1;
    }
}

//! @brief Shutdown the microsecond timer
void microseconds_shutdown(void)
{
    // Disable the timer and interrupts from it
    SysTick->CTRL = SysTick->CTRL & ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

    // Clear the current value register
    SysTick->VAL = 0;
}

//! @brief Read back the running tick count
uint64_t microseconds_get_ticks(void)
{
    uint64_t retVal;

    //! The rollover counter keeps track of increments higher than the 24 bit SysTick counter
    //! to combine them shift rollover up 24 bits and add the current ticks
    uint32_t high;
    uint32_t low;

    // Check for an overflow condition between the two reads above
    do
    {
        high = s_highCounter;
        low = ~SysTick->VAL & SysTick_LOAD_RELOAD_Msk;
    } while (high != s_highCounter);

    retVal = ((uint64_t)high << 24) + low;

    return retVal;
}

//! @brief Returns the conversion of ticks to actual microseconds
//!        This is used to seperate any calculations from getting a timer
//         value for timing sensitive scenarios
uint32_t microseconds_convert_to_microseconds(uint32_t ticks)
{
    // return the total ticks divided by the number of Mhz the system clock is at to give microseconds
    return (8 * ticks / s_tickPerMicrosecondMul8); //!< Assumes system clock will never be < 0.125 Mhz
}

//! @brief Returns the conversion of microseconds to ticks
uint64_t microseconds_convert_to_ticks(uint32_t microseconds)
{
    return ((uint64_t)microseconds * s_tickPerMicrosecondMul8 / 8);
}

//! @brief Delay specified time
//!
//! @param us Delay time in microseconds unit
void microseconds_delay(uint32_t us)
{
    uint64_t currentTicks = microseconds_get_ticks();

    //! The clock value in Mhz = ticks/microsecond
    uint64_t ticksNeeded = ((uint64_t)us * s_tickPerMicrosecondMul8 / 8) + currentTicks;
    while (microseconds_get_ticks() < ticksNeeded)
    {
        ;
    }
}

//! @brief Set delay time
//!
//! @param us Delay time in microseconds unit
void microseconds_set_delay(uint32_t us)
{
    uint64_t ticks;
    ticks = microseconds_convert_to_ticks(us);
    s_timeoutTicks = microseconds_get_ticks() + ticks;
}

//! @brief Get timeout flag
//!
//! @retval true Timeout is reached.
//! @retval false Timeout isn't reached.
bool microseconds_timeout(void)
{
    uint64_t currentTicks = microseconds_get_ticks();

    return (currentTicks < s_timeoutTicks) ? false : true;
}

//! @brief Gets the clock value used for microseconds driver
__WEAK uint32_t microseconds_get_clock(void)
{
    return SystemCoreClock;
}

//! @brief Interrupt handler for the SysTick timer, this will just increment
//         the rollover counter for extended time keeping
void SysTick_Handler(void)
{
    s_highCounter++;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
