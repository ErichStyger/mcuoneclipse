/*
 * Copyright (c) 2013-2016, Freescale Semiconductor, Inc.
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
 * @file microseconds.c
 * @brief Microseconds timer driver source file
 *
 * Notes: The driver configure PIT as lifetime timer
 */
#include "microseconds/microseconds.h"
#include <stdarg.h>
#include "bootloader_common.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

// Below MACROs are defined in order to keep this driver compabtile among all targets.
#if defined(PIT0)
#define PIT PIT0
#endif
#if defined(SIM_SCGC6_PIT0_MASK)
#define SIM_SCGC6_PIT_MASK SIM_SCGC6_PIT0_MASK
#endif

enum
{
    kFrequency_1MHz = 1000000UL
};

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
uint32_t s_tickPerMicrosecondMul8; //!< This value equal to 8 times ticks per microseconds

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Initialize timer facilities.
//!
//! It is initialize the timer to lifetime timer by chained channel 0
//! and channel 1 together, and set b0th channels to maximum counting period
void microseconds_init(void)
{
    uint32_t busClock;

    // PIT clock gate control ON
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // Turn on PIT: MDIS = 0, FRZ = 0
    PIT->MCR = 0x00;

    // Set up timer 1 to max value
    PIT->CHANNEL[1].LDVAL = 0xFFFFFFFF;          // setup timer 1 for maximum counting period
    PIT->CHANNEL[1].TCTRL = 0;                   // Disable timer 1 interrupts
    PIT->CHANNEL[1].TFLG = 1;                    // clear the timer 1 flag
    PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_CHN_MASK; // chain timer 1 to timer 0
    PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK; // start timer 1

    // Set up timer 0 to max value
    PIT->CHANNEL[0].LDVAL = 0xFFFFFFFF;         // setup timer 0 for maximum counting period
    PIT->CHANNEL[0].TFLG = 1;                   // clear the timer 0 flag
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK; // start timer 0

    /* Calculate this value early
     * The reason why use this solution is that lowest clock frequency supported by L0PB and L4KS
     * is 0.25MHz, this solution will make sure ticks per microscond is greater than 0.
     */

    busClock = get_bus_clock();
    s_tickPerMicrosecondMul8 = (busClock * 8) / kFrequency_1MHz;

    // Make sure this value is greater than 0
    if (!s_tickPerMicrosecondMul8)
    {
        s_tickPerMicrosecondMul8 = 1;
    }
}

//! @brief Shutdown the microsecond timer
void microseconds_shutdown(void)
{
    // Turn off PIT: MDIS = 1, FRZ = 0
    PIT->MCR |= PIT_MCR_MDIS_MASK;
}

//! @brief Read back running tick count
uint64_t microseconds_get_ticks(void)
{
    uint64_t valueH;
    uint32_t valueL;

#if defined(FSL_FEATURE_PIT_HAS_LIFETIME_TIMER) && (FSL_FEATURE_PIT_HAS_LIFETIME_TIMER == 1)
    valueH = PIT->LTMR64H;
    valueL = PIT->LTMR64L;
#else
    // Make sure that there are no rollover of valueL.
    // Because the valueL always decreases, so, if the formal valueL is greater than
    // current value, that means the valueH is updated during read valueL.
    // In this case, we need to re-update valueH and valueL.
    do
    {
        valueH = PIT->CHANNEL[1].CVAL;
        valueL = PIT->CHANNEL[0].CVAL;
    } while (valueL < PIT->CHANNEL[0].CVAL);
#endif // FSL_FEATURE_PIT_HAS_LIFETIME_TIMER

    // Invert to turn into an up counter
    return ~((valueH << 32) | valueL);
}

//! @brief Returns the conversion of ticks to actual microseconds
//!        This is used to seperate any calculations from getting a timer
//         value for speed critical scenarios
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
    return get_bus_clock();
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
