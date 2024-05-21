/*
 * Copyright  2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_syscon.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.syscon"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Attaches a signal
 *
 * This function gates the SYSCON clock.
 *
 * param base Base address of the SYSCON peripheral.
 * param index Destination peripheral to attach the signal to.
 * param connection Selects connection.
 *
 * retval None.
 */
void SYSCON_AttachSignal(SYSCON_Type *base, uint32_t index, syscon_connection_t connection)
{
    uint32_t syscon_id;
    uint32_t output_id;

    /* extract syscon to be used */
    syscon_id = ((uint32_t)(connection)) >> SYSCON_SHIFT;
    /*  extract function number */
    output_id = ((uint32_t)(connection)) & 0xffffU;
    /* programm signal */
    *(volatile uint32_t *)(((uint32_t)base) + syscon_id + (index * 4u)) = output_id;
}
