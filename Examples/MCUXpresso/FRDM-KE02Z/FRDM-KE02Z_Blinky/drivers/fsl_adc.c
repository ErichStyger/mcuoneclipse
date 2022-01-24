/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_adc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.adc"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get instance number for ADC module.
 *
 * @param base ADC peripheral base address
 */
static uint32_t ADC_GetInstance(ADC_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to ADC bases for each instance. */
static ADC_Type *const s_adcBases[] = ADC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to ADC clocks for each instance. */
static const clock_ip_name_t s_adcClocks[] = ADC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t ADC_GetInstance(ADC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_adcBases); instance++)
    {
        if (s_adcBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_adcBases));

    return instance;
}

/*!
 * brief Initializes the ADC module.
 *
 * param base   ADC peripheral base address.
 * param config Pointer to configuration structure. See "adc_config_t".
 */
void ADC_Init(ADC_Type *base, const adc_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_adcClocks[ADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Configure SC2 register. */
    tmp32 = (base->SC2) & (~ADC_SC2_REFSEL_MASK);
    tmp32 |= ADC_SC2_REFSEL(config->referenceVoltageSource);
    base->SC2 = tmp32;

    /* Configure SC3 register. */
    tmp32 =
        ADC_SC3_ADICLK(config->clockSource) | ADC_SC3_MODE(config->ResolutionMode) | ADC_SC3_ADIV(config->clockDivider);
    if (config->enableLowPower)
    {
        tmp32 |= ADC_SC3_ADLPC_MASK;
    }
    if (config->enableLongSampleTime)
    {
        tmp32 |= ADC_SC3_ADLSMP_MASK;
    }
    base->SC3 = tmp32;
}

/*!
 * brief De-initialize the ADC module.
 *
 * param base ADC peripheral base address.
 */
void ADC_Deinit(ADC_Type *base)
{
    /* Disable ADC module. */
    base->SC1 |= ADC_SC1_ADCH_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_adcClocks[ADC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets an available pre-defined settings for the converter's configuration.
 *
 * This function initializes the converter configuration structure with available settings. The default values are as
 * follows.
 * code
 *   config->referenceVoltageSource = kADC_ReferenceVoltageSourceAlt0;
 *   config->enableLowPower = false;
 *   config->enableLongSampleTime = false;
 *   config->clockDivider = kADC_ClockDivider1;
 *   config->ResolutionMode = kADC_Resolution8BitMode;
 *   config->clockSource = kADC_ClockSourceAlt0;
 * endcode
 * param config Pointer to the configuration structure.
 */
void ADC_GetDefaultConfig(adc_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->referenceVoltageSource = kADC_ReferenceVoltageSourceAlt0;
    config->enableLowPower         = false;
    config->enableLongSampleTime   = false;
    config->clockDivider           = kADC_ClockDivider1;
    config->ResolutionMode         = kADC_Resolution8BitMode;
    config->clockSource            = kADC_ClockSourceAlt0;
}

/*!
 * brief Configure the hardware compare mode.
 *
 * The compare function can be configured to check for an upper or lower limit. After the
 * input is sampled and converted, the result is added to the complement of the compare
 * value (ADC_CV).
 *
 * param base ADC peripheral base address.
 * param config Pointer to "adc_hardware_compare_config_t" structure.
 */
void ADC_SetHardwareCompare(ADC_Type *base, const adc_hardware_compare_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    /* Configure SC2 register. */
    tmp32 = (base->SC2) & ~(ADC_SC2_ACFGT_MASK | ADC_SC2_ACFE_MASK);
    tmp32 |= ((uint32_t)(config->compareMode) << ADC_SC2_ACFGT_SHIFT);
    base->SC2 = tmp32;

    /* Configure CV register. */
    base->CV = ADC_CV_CV(config->compareValue);
}

/*!
 * brief Configure the Fifo mode.
 *
 * The ADC module supports FIFO operation to minimize the interrupts to CPU in order to
 * reduce CPU loading in ADC interrupt service routines. This module contains two FIFOs
 * to buffer analog input channels and analog results respectively.
 *
 * param base ADC peripheral base address.
 * param config Pointer to "adc_fifo_config_t" structure.
 */
void ADC_SetFifoConfig(ADC_Type *base, const adc_fifo_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    /* Configure SC4 register. */
    tmp32 = ADC_SC4_AFDEP(config->FifoDepth);
    if (config->enableFifoScanMode)
    {
        tmp32 |= ADC_SC4_ASCANE_MASK;
    }
    if (config->enableCompareAndMode)
    {
        tmp32 |= ADC_SC4_ACFSEL_MASK;
    }
#if defined(FSL_FEATURE_ADC_HAS_SC4_HTRGME) && FSL_FEATURE_ADC_HAS_SC4_HTRGME
    if (config->enableHWTriggerMultConv)
    {
        tmp32 |= ADC_SC4_HTRGME_MASK;
    }
#endif /* FSL_FEATURE_ADC_HAS_SC4_HTRGME */
    base->SC4 = tmp32;
}

/*!
 * brief Gets an available pre-defined settings for the FIFO's configuration.
 *
 * param config Pointer to the FIFO configuration structure, please refer to adc_fifo_config_t for details.
 */
void ADC_GetDefaultFIFOConfig(adc_fifo_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->enableFifoScanMode   = false;
    config->enableCompareAndMode = false;
    config->FifoDepth            = 0UL;
#if defined(FSL_FEATURE_ADC_HAS_SC4_HTRGME) && FSL_FEATURE_ADC_HAS_SC4_HTRGME
    config->enableHWTriggerMultConv = false;
#endif
}

/*!
 * brief Configures the conversion channel.
 *
 * This operation triggers the conversion when in software trigger mode. When in hardware trigger mode, this API
 * configures the channel while the external trigger source helps to trigger the conversion.
 *
 * param base ADC peripheral base address.
 * param config Pointer to "adc_channel_config_t" structure.
 */
void ADC_SetChannelConfig(ADC_Type *base, const adc_channel_config_t *config)
{
    assert(NULL != config);

    uint32_t tmp32;

    /* Configure SC1 register. */
    tmp32 = ADC_SC1_ADCH(config->channelNumber);
    if (config->enableContinuousConversion)
    {
        tmp32 |= ADC_SC1_ADCO_MASK;
    }
    if (config->enableInterruptOnConversionCompleted)
    {
        tmp32 |= ADC_SC1_AIEN_MASK;
    }
    base->SC1 = tmp32;
}

/*!
 * brief Get the status flags of channel.
 *
 * param  base ADC peripheral base address.
 * return "True" means conversion has completed and "false" means conversion has not completed.
 */
bool ADC_GetChannelStatusFlags(ADC_Type *base)
{
    bool ret = false;

    if (ADC_SC1_COCO_MASK == (ADC_SC1_COCO_MASK & (base->SC1)))
    {
        ret = true;
    }

    return ret;
}

/*!
 * brief Get the ADC status flags.
 *
 * param base ADC peripheral base address.
 * return Flags' mask if indicated flags are asserted. See "_adc_status_flags".
 */
uint32_t ADC_GetStatusFlags(ADC_Type *base)
{
    uint32_t tmp32;

    tmp32 = (base->SC2) & (ADC_SC2_ADACT_MASK | ADC_SC2_FEMPTY_MASK | ADC_SC2_FFULL_MASK);

    return tmp32;
}
