/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_acomp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_acomp"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the ACOMP instance from the peripheral base address.
 *
 * @param base ACOMP peripheral base address.
 * @return ACOMP instance.
 */
static uint32_t ACOMP_GetInstance(ACOMP_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of ACOMP peripheral base address. */
static ACOMP_Type *const s_acompBases[] = ACOMP_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name of ACOMP. */
static const clock_ip_name_t s_acompClock[] = ACMP_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_ACMP_HAS_NO_RESET) && FSL_FEATURE_ACMP_HAS_NO_RESET)
/* Reset the ACMP module */
static const reset_ip_name_t s_acompResets[] = ACMP_RSTS_N;
#endif

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t ACOMP_GetInstance(ACOMP_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_acompBases); instance++)
    {
        if (s_acompBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_acompBases));

    return instance;
}

/*!
 * brief Initialize the ACOMP module.
 *
 * param base ACOMP peripheral base address.
 * param config Pointer to "acomp_config_t" structure.
 */
void ACOMP_Init(ACOMP_Type *base, const acomp_config_t *config)
{
    assert(NULL != config);
    assert(NULL != base);

    uint32_t tmp32;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_acompClock[ACOMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_ACMP_HAS_NO_RESET) && FSL_FEATURE_ACMP_HAS_NO_RESET)
    RESET_PeripheralReset(s_acompResets[ACOMP_GetInstance(base)]);
#endif

    /* Write CTRL register. */
    tmp32 = base->CTRL & ~(ACOMP_CTRL_COMPSA_MASK | ACOMP_CTRL_HYS_MASK);
    tmp32 |= ACOMP_CTRL_HYS(config->hysteresisSelection);
    if (config->enableSyncToBusClk)
    {
        tmp32 |= ACOMP_CTRL_COMPSA_MASK;
    }
    base->CTRL = tmp32;
}

/*!
 * brief De-initialize the ACOMP module.
 *
 * param base ACOMP peripheral base address.
 */
void ACOMP_Deinit(ACOMP_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_acompClock[ACOMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets an available pre-defined settings for the ACOMP's configuration.
 *
 * This function initializes the converter configuration structure with available settings. The default values are:
 * code
 *   config->enableSyncToBusClk = false;
 *   config->hysteresisSelection = kACOMP_hysteresisNoneSelection;
 * endcode
 * In default configuration, the ACOMP's output would be used directly and switch as the voltages cross.
 *
 * param base   ACOMP peripheral base address.
 * param config Pointer to the configuration structure.
 */
void ACOMP_GetDefaultConfig(acomp_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableSyncToBusClk  = false;
    config->hysteresisSelection = kACOMP_HysteresisNoneSelection;
}

/*!
 * brief Enable ACOMP interrupts.
 *
 * param base ACOMP peripheral base address.
 * param enable Enable/Disable interrupt feature.
 */
void ACOMP_EnableInterrupts(ACOMP_Type *base, acomp_interrupt_enable_t enable)
{
#if defined(FSL_FEATURE_ACOMP_HAS_CTRL_INTENA) && FSL_FEATURE_ACOMP_HAS_CTRL_INTENA
    if (enable == kACOMP_InterruptsDisable)
    {
        base->CTRL &= ~ACOMP_CTRL_INTENA_MASK;
    }
    else
#endif /*FSL_FEATURE_ACOMP_HAS_CTRL_INTENA*/
    {
        base->CTRL = (base->CTRL & ~ACOMP_CTRL_EDGESEL_MASK) | ACOMP_CTRL_EDGESEL(enable)
#if defined(FSL_FEATURE_ACOMP_HAS_CTRL_INTENA) && FSL_FEATURE_ACOMP_HAS_CTRL_INTENA
                     | ACOMP_CTRL_INTENA_MASK
#endif /*FSL_FEATURE_ACOMP_HAS_CTRL_INTENA*/
            ;
    }
}

/*!
 * brief Set the voltage ladder configuration.
 *
 * param base ACOMP peripheral base address.
 * param config The structure for voltage ladder. If the config is NULL, voltage ladder would be diasbled,
 *               otherwise the voltage ladder would be configured and enabled.
 */
void ACOMP_SetLadderConfig(ACOMP_Type *base, const acomp_ladder_config_t *config)
{
    if (NULL == config)
    {
        base->LAD = 0U;
    }
    else
    {
        base->LAD =
            ACOMP_LAD_LADEN_MASK | ACOMP_LAD_LADSEL(config->ladderValue) | ACOMP_LAD_LADREF(config->referenceVoltage);
    }
}
