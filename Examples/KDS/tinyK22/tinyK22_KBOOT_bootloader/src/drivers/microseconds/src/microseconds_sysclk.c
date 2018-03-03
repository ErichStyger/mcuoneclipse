/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * @file microseconds_sysclk.c
 * @brief Microseconds sysclk timer driver source file
 *
 * Notes: The driver configure sysclk as lifetime timer
 */
#include "bootloader_common.h"
#include "microseconds/microseconds.h"
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

//! @brief Gets the clock value used for microseconds driver
uint32_t microseconds_get_clock(void)
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
