/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "autobaud/autobaud.h"
#include "microseconds.h"
#include "bootloader_common.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

enum _autobaud_counts
{
    //! the number of falling edge transitions being counted
    //! for 0x5A
    kFirstByteRequiredFallingEdges = 4,
    //! the number of falling edge transitions being counted
    //! for 0xA6
    kSecondByteRequiredFallingEdges = 3,
    //! the number of bits being measured for the baud rate
    //! for 0x5A we have the start bit + 7 bits to the last falling edge = 8 bits
    kNumberOfBitsForFirstByteMeasured = 8,
    //! for 0xA6 we have the start bit + 6 bits to the last falling edge = 7 bits
    kNumberOfBitsForSecondByteMeasured = 7,
    //! Time in microseconds that we will wait in between toggles before restarting detection
    //! Make this value 8 bits at 100 baud worth of time = 80000 microseconds
    kMaximumTimeBetweenFallingEdges = 80000,
    //! Autobaud baud step size that our calculation will be rounded to, this is to ensure
    //! that we can use a valid multiplier in the UART configuration which runs into problems
    //! at higher baud rates with slightly off baud rates (e.g. if we measure 115458 vs 115200)
    //! a calculation of UartClock at 48MHz gives an SBR calculation of 48000000/ (16 * 115458) = 25
    //! giving a baud rate calculation of 48000000/(16 * 25) = 120000 baud
    //! which is out of spec and fails
    kAutobaudStepSize = 1200
};

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////
void instance_transition_callback(uint32_t instance);
// This function is used to filter invalid noises on LPUART RX pins.
static bool is_falling_edge_interval_valid(void);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static uint32_t s_transitionCount;
static uint64_t s_ticksAtFirstFallingEdge;
static uint64_t s_firstByteTotalTicks;
static uint64_t s_secondByteTotalTicks;
static uint64_t s_lastToggleTicks;
static uint64_t s_ticksBetweenFailure;
static uint32_t s_instanceMeasured;
static uint32_t s_ticksFallingEdges[kFirstByteRequiredFallingEdges + kSecondByteRequiredFallingEdges];
static uint32_t s_intervalFallingEdgesFirstByte[kFirstByteRequiredFallingEdges - 1];
static uint32_t s_intervalFallingEdgesSecondByte[kSecondByteRequiredFallingEdges - 1];

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void autobaud_init(uint32_t instance)
{
    s_transitionCount = 0;
    s_firstByteTotalTicks = 0;
    s_secondByteTotalTicks = 0;
    s_lastToggleTicks = 0;
    s_instanceMeasured = 0;
    s_ticksBetweenFailure = microseconds_convert_to_ticks(kMaximumTimeBetweenFallingEdges);
    enable_autobaud_pin_irq(instance, instance_transition_callback);
}

void autobaud_deinit(uint32_t instance)
{
    disable_autobaud_pin_irq(instance);
}

/*
 *   This function filters the invalid noises on LPUART rx pins by following characters:
 *   For 0x5A, the interval between falling edges meets 3:3:2
 *   For 0xA5, the interval between falling edges meets: 4:3
 *      |              0x5A                 |                 0xA6              |
 *
 *   ___       ___     _____     ___     ______       _____       ___     ________
 *      | S 0 | 1 | 0 | 1 1 | 0 | 1 | 0 | STOP | S 0 | 1 1 | 0 0 | 1 | 0 | 1  STOP
 *       -----     ---       ---     ---        -----       -----     ---
 *   ---------------------------------------------------------------------------
 *      |    1st  |   2nd   |  3rd  |          |    1st    |    2nd  |
 *   ---------------------------------------------------------------------------
 *      |     3   :     3   :   2   |          |     4     :     3   |
 *
 *  NOTE:
 *       There are still some noises which cannot be filtered by this function due to algorithm limitation.
 *       1st byte: 0x5B, 0x53, 0x52 can pass this check, and will be treated as 0x5A.
 *       2nd byte: 0xA4,0xA5,0xA7, 0xB4,0xB5,0xB6,0xB7 can pass this check. and will be treated as 0xA6.
 *       This function is able to filter up to 99.95% noises.
 */
bool is_falling_edge_interval_valid(void)
{
    // Calculate intervals between falling edges for 0x5A
    for (uint32_t i = 0; i < kFirstByteRequiredFallingEdges - 1; i++)
    {
        s_intervalFallingEdgesFirstByte[i] = s_ticksFallingEdges[i + 1] - s_ticksFallingEdges[i];
    }

    // Calculate intervals between falling edges for 0xA6
    for (uint32_t i = 0; i < kSecondByteRequiredFallingEdges - 1; i++)
    {
        s_intervalFallingEdgesSecondByte[i] = s_ticksFallingEdges[kFirstByteRequiredFallingEdges + 1 + i] -
                                              s_ticksFallingEdges[kFirstByteRequiredFallingEdges + i];
    }

    // Ensure the intervals for 0x5A meet above characters.
    // 3rd Interval : 1st Interval = 2:3
    uint32_t tmp = s_intervalFallingEdgesFirstByte[2] * 100;
    uint32_t div = tmp / s_intervalFallingEdgesFirstByte[0];
    // For PL2303, there is a large jitter at the first falling edge.
    // So expand the check range. No such issue for the left edges.
    if ((div < 60) || (div > 73))
    {
        return false;
    }

    // 3rd interval : 2nd Interval = 2:3
    div = tmp / s_intervalFallingEdgesFirstByte[1];
    // baud rate tolerance should be -+3%
    // 2 / 3 * 100 * 0.97 = 64.667
    // 2 / 3 * 100 * 1.03 = 68.667
    if ((div < 64) || (div > 69))
    {
        return false;
    }

    // Ensure the intervals for 0xA6 meet above characters.
    // 1st Interval : 2nd Interval = 4:3
    tmp = s_intervalFallingEdgesSecondByte[0] * 100;
    div = tmp / s_intervalFallingEdgesSecondByte[1];
    // baud rate tolerance should be -+3%
    // 4 / 3 * 100 * 0.97 = 129.33
    // 2 / 3 * 100 * 1.03 = 137.33
    if ((div < 129) || (div > 138))
    {
        return false;
    }

    // 1st interval for 0xA6 : 1st interval for 0x5a = 4:3
    // For PL2303, there is a large jitter at the first falling edge.
    // So uses s_intervalFallingEdgesFirstByte[1] instead of
    // s_intervalFallingEdgesFirstByte[0]
    div = tmp / s_intervalFallingEdgesFirstByte[1];
    // baud rate tolerance should be -+3%
    // 4 / 3 * 100 * 0.97 = 129.33
    // 2 / 3 * 100 * 1.03 = 137.33
    if ((div < 129) || (div > 138))
    {
        return false;
    }

    return true;
}

status_t autobaud_get_rate(uint32_t instance, uint32_t *rate)
{
    if ((s_transitionCount == (kFirstByteRequiredFallingEdges + kSecondByteRequiredFallingEdges)) &&
        (instance == s_instanceMeasured))
    {
        // Invalid bytes received.
        if (!is_falling_edge_interval_valid())
        {
            // Restart auto buad detection
            autobaud_init(instance);
            return kStatus_Fail;
        }

        uint32_t calculatedBaud =
            (microseconds_get_clock() * (kNumberOfBitsForFirstByteMeasured + kNumberOfBitsForSecondByteMeasured)) /
            (uint32_t)(s_firstByteTotalTicks + s_secondByteTotalTicks);

        // Round the rate to the nearest step size
        // rounded = stepSize * (value/stepSize + .5)
        // multiplying by 10 since we can't work with floats
        *rate = ((((calculatedBaud * 10) / kAutobaudStepSize) + 5) / 10) * kAutobaudStepSize;

        return kStatus_Success;
    }
    else
    {
        // no baud rate yet/inactive
        return kStatus_Fail;
    }
}

void instance_transition_callback(uint32_t instance)
{
    uint64_t ticks = microseconds_get_ticks();
    s_transitionCount++;

    uint64_t delta = ticks - s_lastToggleTicks;

    // The last toggle was longer than we allow so treat this as the first one
    if (delta > s_ticksBetweenFailure)
    {
        s_transitionCount = 1;
    }

    switch (s_transitionCount)
    {
        case 1:
            // This is our first falling edge, store the initial ticks temporarily in firstByteTicks
            // and save the instance that we are measuring
            s_ticksAtFirstFallingEdge = ticks;
            s_firstByteTotalTicks = ticks;
            s_instanceMeasured = instance;
            break;

        case kFirstByteRequiredFallingEdges:
            // We reached the end of our measurable first byte, subtract the current ticks from the initial
            // first byte ticks
            s_firstByteTotalTicks = ticks - s_firstByteTotalTicks;
            break;

        case (kFirstByteRequiredFallingEdges + 1):
            // We hit our first falling edge of the second byte, store the initial ticks temporarily in secondByteTicks
            s_secondByteTotalTicks = ticks;
            break;

        case (kFirstByteRequiredFallingEdges + kSecondByteRequiredFallingEdges):
            // We reached the end of our measurable second byte, subtract the current ticks from the initial
            // second byte ticks
            s_secondByteTotalTicks = ticks - s_secondByteTotalTicks;
            disable_autobaud_pin_irq(instance);
            break;
    }

    s_ticksFallingEdges[s_transitionCount - 1] = ticks - s_ticksAtFirstFallingEdge;

    s_lastToggleTicks = ticks;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
