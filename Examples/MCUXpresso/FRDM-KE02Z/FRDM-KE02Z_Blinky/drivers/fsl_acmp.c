/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_acmp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.acmp_1"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the ACMP instance from the peripheral base address.
 *
 * @param base ACMP peripheral base address.
 * @return ACMP instance.
 */
static uint32_t ACMP_GetInstance(ACMP_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of ACMP peripheral base address. */
static ACMP_Type *const s_acmpBases[] = ACMP_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name of ACMP. */
static const clock_ip_name_t s_acmpClock[] = ACMP_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t ACMP_GetInstance(ACMP_Type *base)
{
    uint32_t instance = 0U;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_acmpBases); instance++)
    {
        if (s_acmpBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_acmpBases));

    return instance;
}

/*!
 * brief Initialize the ACMP.
 *
 * The default configuration can be got by calling ACMP_GetDefaultConfig().
 *
 * param base ACMP peripheral base address.
 * param config Pointer to ACMP configuration structure.
 */
void ACMP_Init(ACMP_Type *base, const acmp_config_t *config)
{
    assert(NULL != config);

    uint8_t tmp8;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate. */
    CLOCK_EnableClock(s_acmpClock[ACMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable the module before configuring it. */
    ACMP_Enable(base, false);

    /* ACMP_CS register. */
    tmp8 = base->CS & (uint8_t)(~(ACMP_CS_HYST_MASK | ACMP_CS_ACOPE_MASK));

    tmp8 |= ACMP_CS_HYST(config->hysteresisMode);
    if (config->enablePinOut)
    {
        tmp8 |= ACMP_CS_ACOPE_MASK;
    }
    base->CS = tmp8;
}

/*!
 * brief De-Initialize the ACMP.
 *
 * param base ACMP peripheral basic address.
 */
void ACMP_Deinit(ACMP_Type *base)
{
    /* Disable the ACMP module. */
    ACMP_Enable(base, false);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Close clock gate. */
    CLOCK_DisableClock(s_acmpClock[ACMP_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the default configuration for ACMP.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 * Example:
 *   code
 *   config->enablePinOut = false;
 *   config->hysteresisMode = kACMP_HysterisisLevel1;
 *   endcode
 *
 * param config Pointer to ACMP configuration structure.
 */
void ACMP_GetDefaultConfig(acmp_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enablePinOut   = false;
    config->hysteresisMode = kACMP_HysterisisLevel1;
}

/*!
 * brief Enable the ACMP interrupt and determines the sensitivity modes of the interrupt trigger.
 *
 *
 * param base ACMP peripheral base address.
 * param mode Select one interrupt mode to generate interrupt.
 */
void ACMP_EnableInterrupt(ACMP_Type *base, acmp_interrupt_mode_t mode)
{
    uint8_t tmp8;

    /* ACMP_CS register. */
    tmp8 = base->CS & (uint8_t)(~ACMP_CS_ACMOD_MASK);

    tmp8 |= ACMP_CS_ACIE_MASK | ACMP_CS_ACMOD(mode);
    base->CS = tmp8;
}

/*!
 * brief Configure the ACMP positive and negative input channel.
 *
 * param base ACMP peripheral base address.
 * param PositiveInput ACMP Positive Input Select. Refer to "acmp_input_channel_selection_t".
 * param negativeInout ACMP Negative Input Select. Refer to "acmp_input_channel_selection_t".
 */
void ACMP_SetChannelConfig(ACMP_Type *base,
                           acmp_input_channel_selection_t PositiveInput,
                           acmp_input_channel_selection_t negativeInout)
{
    uint8_t tmp8;

    /* ACMP_C0 register. */
    tmp8     = ACMP_C0_ACPSEL(PositiveInput) | ACMP_C0_ACNSEL(negativeInout);
    base->C0 = tmp8;
}

/*
 * brief Configure the internal DAC.
 *
 * param base ACMP peripheral base address.
 * param config Pointer to DAC configuration structure. "NULL" is for disabling the feature.
 */
void ACMP_SetDACConfig(ACMP_Type *base, const acmp_dac_config_t *config)
{
    uint8_t tmp8;

    /* "NULL" is for disabling the feature. */
    if (NULL == config)
    {
        tmp8 = 0U;
    }
    else
    {
        /* ACMP_C1 register. */
        tmp8 = ACMP_C1_DACEN_MASK | ACMP_C1_DACREF(config->referenceVoltageSource) | ACMP_C1_DACVAL(config->DACValue);
    }
    base->C1 = tmp8;
}

/*!
 * brief Enable/Disable ACMP input pin.
 *        The API controls if the corresponding ACMP external pin can be driven by an analog input
 *
 * param base ACMP peripheral base address.
 * param mask The mask of the pin associated with channel ADx. Valid range is AD0:0x1U ~ AD3:0x4U.
 *             For example: If enable AD0, AD1 and AD2 pins, mask should be set to 0x7U(0x1 | 0x2 | 0x4).
 */
void ACMP_EnableInputPin(ACMP_Type *base, uint32_t mask, bool enable)
{
    assert(mask <= ACMP_C2_ACIPE_MASK);

    if (enable)
    {
        base->C2 |= ACMP_C2_ACIPE(mask);
    }
    else
    {
        base->C2 &= ~ACMP_C2_ACIPE(mask);
    }
}
