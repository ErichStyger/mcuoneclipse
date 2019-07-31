/*
 * Copyright (c) 2017, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_swm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.swm"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Assignment of digital peripheral functions to pins.
 *
 * This function will selects a pin (designated by its GPIO port and
 * bit numbers) to a function.
 *
 * param base SWM peripheral base address.
 * param func any function name that is movable.
 * param swm_port_pin any pin which has a GPIO port number and bit number.
 */
void SWM_SetMovablePinSelect(SWM_Type *base, swm_select_movable_t func, swm_port_pin_type_t swm_port_pin)
{
    /* Check arguments */
    assert(NULL != base);
    assert(func < kSWM_MOVABLE_NUM_FUNCS);

    uint32_t temp;
    uint32_t pinassign = 0;
    uint32_t shifter = 0;

    pinassign = func / 4;
    shifter = (func % 4) * 8;

    temp = base->PINASSIGN_DATA[pinassign];
    temp &= ~(0xFF << (shifter));
    temp |= (swm_port_pin << shifter);
    base->PINASSIGN_DATA[pinassign] = temp;
}

#if (defined(FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER) && (FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER == 1))
/*!
 * brief Assignment of digital peripheral functions to pins.
 *
 * This function will selects a pin (designated by its GPIO port and
 * bit numbers) to a function.
 *
 * param base SWM peripheral base address.
 * param func any function name that is movable.
 * param swm_port_pin any pin which has a GPIO port number and bit number.
 */
void SWM_SetFixedMovablePinSelect(SWM_Type *base,
                                  swm_select_fixed_movable_t func,
                                  swm_fixed_port_pin_type_t swm_port_pin)
{
    /* Check arguments */
    assert(NULL != base);
    assert(func < kSWM_PINASSINGNFIXED_MOVABLE_NUM_FUNCS);

    uint32_t temp;
    uint32_t shifter = 0;

    shifter = func * 2;

    temp = base->PINASSIGNFIXED0;
    temp &= ~(0x03 << (shifter));
    temp |= (swm_port_pin << shifter);
    base->PINASSIGNFIXED0 = temp;
}
#endif /* FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER */

/*!
 * brief Enable the fixed-pin function.
 *
 * This function will enables a fixed-pin function in PINENABLE0 or PINENABLE1.
 *
 * param base SWM peripheral base address.
 * param func any function name that is fixed pin.
 * param enable enable or disable.
 */
void SWM_SetFixedPinSelect(SWM_Type *base, swm_select_fixed_pin_t func, bool enable)
{
    /* Check arguments */
    assert(NULL != base);
    assert((func > 0) || func < kSWM_FIXEDPIN_NUM_FUNCS);

    if (enable)
    {
        if (!(func & 0x80000000U))
        {
            base->PINENABLE0 &= ~(func);
        }
#if (defined(FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER) && (FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER == 1))
        else
        {
            base->PINENABLE1 &= ~(func);
        }
#endif /* FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER */
    }
    else
    {
        if (!(func & 0x80000000U))
        {
            base->PINENABLE0 |= (func);
        }
#if (defined(FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER) && (FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER == 1))
        else
        {
            base->PINENABLE1 |= (func);
        }
#endif /* FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER */
    }
}
