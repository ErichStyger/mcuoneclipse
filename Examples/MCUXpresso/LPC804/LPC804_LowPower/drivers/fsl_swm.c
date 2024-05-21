/*
 * Copyright  2017-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_swm.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.swm"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (defined(FSL_FEATURE_SWM_HAS_FLEXTIMER_PINASSIGN_REGISTER) && \
     (FSL_FEATURE_SWM_HAS_FLEXTIMER_PINASSIGN_REGISTER == 1))
/*! @brief Flextimer pin assignments. */
static const uint32_t s_swmFlextimerFuncMatrix[18][4] = {
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM0_EXTCLK: P0_24, P0_30, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_CH0: P0_17, P1_1, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_CH1: P0_18, P1_2, P0_16, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_CH2: P0_19, P1_3, P1_2, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_CH3: P0_20, P1_4, P0_27, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_CH4: P0_21, P1_5, P0_25, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_CH5: P0_22, P1_6, P0_24, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_FAULT0: P0_10, P1_7, P0_28, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, (uint32_t)kSWM_FTM_Selection2,
     0xff}, /* FTM0_FAULT1: P0_11, P1_12, P1_3, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM0_FAULT2: P0_13, P1_13, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM0_FAULT3: P0_23, P1_14, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM1_EXTCLK: P0_25, P0_29, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM1_CH0: P0_15, P1_8, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM1_CH1: P0_16, P1_9, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM1_CH2: P0_26, P0_31, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM1_CH3: P0_27, P1_0, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff}, /* FTM1_QD_PHA: P0_24, P0_29, none, Not connected */
    {(uint32_t)kSWM_FTM_Selection0, (uint32_t)kSWM_FTM_Selection1, 0xff,
     0xff} /* FTM1_QD_PHB: P0_25, P0_30, none, Not connected */
};
#endif /* FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER */
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
    uint32_t shifter   = 0;

    pinassign = (uint32_t)func / 4U;
    shifter   = ((uint32_t)func % 4U) * 8U;

    temp = base->PINASSIGN_DATA[pinassign];
    temp &= ~(0xFFUL << (shifter));
    temp |= ((uint32_t)swm_port_pin << shifter);
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

    shifter = (uint32_t)func * 2U;

    temp = base->PINASSIGNFIXED0;
    temp &= ~(0x03UL << (shifter));
    temp |= ((uint32_t)swm_port_pin << shifter);
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

    if (enable)
    {
        if (((uint32_t)func & 0x80000000U) == 0x00U)
        {
            base->PINENABLE0 &= ~((uint32_t)func);
        }
#if (defined(FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER) && (FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER == 1))
        else
        {
            base->PINENABLE1 &= ~((uint32_t)func);
        }
#endif /* FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER */
    }
    else
    {
        if (((uint32_t)func & 0x80000000U) == 0x00U)
        {
            base->PINENABLE0 |= ((uint32_t)func);
        }
#if (defined(FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER) && (FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER == 1))
        else
        {
            base->PINENABLE1 |= ((uint32_t)func);
        }
#endif /* FSL_FEATURE_SWM_HAS_PINENABLE1_REGISTER */
    }
}

#if (defined(FSL_FEATURE_SWM_HAS_FLEXTIMER_PINASSIGN_REGISTER) && \
     (FSL_FEATURE_SWM_HAS_FLEXTIMER_PINASSIGN_REGISTER == 1))
/*!
 * brief Enable the flextimer function.
 *
 * This function will enables a flextimer function in FTM_PINASSIGN0 or FTM_PINASSIGN1.
 *
 * param base SWM peripheral base address.
 * param func any function name that is flextimer.
 * param selection flextimer pin selection.
 */
void SWM_SetFlextimerPinSelect(SWM_Type *base, swm_flextimer_pin_func_t func, swm_flextimer_pin_sel_t selection)
{
    /* Check arguments */
    assert(NULL != base);
    assert(func < kSWM_FTM_NUM_FUNCS);

    uint32_t temp = 0x00U;

    if (((uint32_t)func & 0x10U) == 0x00U)
    {
        temp = base->FTM_PINASSIGN0;
        temp &= ~(0x03UL << ((uint32_t)func * 2U));
        temp |= ((uint32_t)s_swmFlextimerFuncMatrix[func][selection] << ((uint32_t)func * 2U));
        base->FTM_PINASSIGN0 = temp;
    }
    else
    {
        temp = base->FTM_PINASSIGN1;
        temp &= ~(0x03UL << (((uint32_t)func & 0x0FU) * 2U));
        temp |= ((uint32_t)s_swmFlextimerFuncMatrix[func][selection] << (((uint32_t)func & 0x0FU) * 2U));
        base->FTM_PINASSIGN1 = temp;
    }
}
#endif /* FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER */
