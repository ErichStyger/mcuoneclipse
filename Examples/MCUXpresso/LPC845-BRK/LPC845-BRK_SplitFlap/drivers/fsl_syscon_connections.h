/*
 * Copyright  2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SYSCON_CONNECTIONS_
#define _FSL_SYSCON_CONNECTIONS_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.syscon_connections"
#endif

/*!
 * @addtogroup syscon
 * @{
 */

/*!
 * @name Syscon multiplexing connections
 * @{
 */

/*! @brief Periphinmux IDs */
#define PINTSEL_ID 0x178U
#define SYSCON_SHIFT 20U

/*! @brief SYSCON connections type */
typedef enum _syscon_connection_t
{
    /*!< Pin Interrupt. */
    kSYSCON_GpioPort0Pin0ToPintsel = 0U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin1ToPintsel = 1U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin2ToPintsel = 2U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin3ToPintsel = 3U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin4ToPintsel = 4U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin5ToPintsel = 5U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin6ToPintsel = 6U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin7ToPintsel = 7U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin8ToPintsel = 8U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin9ToPintsel = 9U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin10ToPintsel = 10U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin11ToPintsel = 11U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin12ToPintsel = 12U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin13ToPintsel = 13U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin14ToPintsel = 14U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin15ToPintsel = 15U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin16ToPintsel = 16U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin17ToPintsel = 17U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin18ToPintsel = 18U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin19ToPintsel = 19U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin20ToPintsel = 20U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin21ToPintsel = 21U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin22ToPintsel = 22U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin23ToPintsel = 23U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin24ToPintsel = 24U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin25ToPintsel = 25U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin26ToPintsel = 26U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin27ToPintsel = 27U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin28ToPintsel = 28U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin29ToPintsel = 29U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin30ToPintsel = 30U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort0Pin31ToPintsel = 31U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin0ToPintsel = 32U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin1ToPintsel = 33U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin2ToPintsel = 34U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin3ToPintsel = 35U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin4ToPintsel = 36U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin5ToPintsel = 37U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin6ToPintsel = 38U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin7ToPintsel = 39U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin8ToPintsel = 40U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin9ToPintsel = 41U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin10ToPintsel = 42U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin11ToPintsel = 43U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin12ToPintsel = 44U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin13ToPintsel = 45U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin14ToPintsel = 46U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin15ToPintsel = 47U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin16ToPintsel = 48U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin17ToPintsel = 49U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin18ToPintsel = 50U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin19ToPintsel = 51U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin20ToPintsel = 52U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin21ToPintsel = 53U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin22ToPintsel = 54U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin23ToPintsel = 55U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin24ToPintsel = 56U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin25ToPintsel = 57U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin26ToPintsel = 58U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin27ToPintsel = 59U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin28ToPintsel = 60U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin29ToPintsel = 61U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin30ToPintsel = 62U + (PINTSEL_ID << SYSCON_SHIFT),
    kSYSCON_GpioPort1Pin31ToPintsel = 63U + (PINTSEL_ID << SYSCON_SHIFT),
} syscon_connection_t;

/*@}*/

/*@}*/

#endif /* _FSL_SYSCON_CONNECTIONS_ */
