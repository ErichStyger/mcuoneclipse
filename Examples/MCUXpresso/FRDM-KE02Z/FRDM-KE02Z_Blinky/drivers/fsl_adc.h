/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ADC_H_
#define _FSL_ADC_H_

#include "fsl_common.h"

/*!
 *  @addtogroup adc_12b1msps_sar
 *  @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief ADC driver version */
#define FSL_ADC_DRIVER_VERSION (MAKE_VERSION(2, 1, 0)) /*!< Version 2.1.0. */

/*!
 * @brief Reference voltage source.
 */
typedef enum _adc_reference_voltage_source
{
    kADC_ReferenceVoltageSourceAlt0 = 0U, /*!< Default voltage reference pin pair (VREFH/VREFL). >*/
    kADC_ReferenceVoltageSourceAlt1 = 1U, /*!< Analog supply pin pair (VDDA/VSSA). >*/
} adc_reference_voltage_source_t;

/*!
 * @brief Clock divider for the converter.
 */
typedef enum _adc_clock_divider
{
    kADC_ClockDivider1 = 0U, /*!< Divide ration = 1, and clock rate = Input clock. >*/
    kADC_ClockDivider2 = 1U, /*!< Divide ration = 2, and clock rate = Input clock / 2. >*/
    kADC_ClockDivider4 = 2U, /*!< Divide ration = 3, and clock rate = Input clock / 4. >*/
    kADC_ClockDivider8 = 3U, /*!< Divide ration = 4, and clock rate = Input clock / 8. >*/
} adc_clock_divider_t;

/*!
 * @brief ADC converter resolution mode.
 */
typedef enum _adc_resolution_mode
{
    kADC_Resolution8BitMode  = 0U, /*!< 8-bit conversion (N = 8). >*/
    kADC_Resolution10BitMode = 1U, /*!< 10-bit conversion (N = 10) >*/
    kADC_Resolution12BitMode = 2U, /*!< 12-bit conversion (N = 12) >*/
} adc_resolution_mode_t;

/*!
 * @brief ADC input Clock source.
 */
typedef enum _adc_clock_source
{
    kADC_ClockSourceAlt0 = 0U, /*!< Bus clock. >*/
    kADC_ClockSourceAlt1 = 1U, /*!< Bus clock divided by 2. >*/
    kADC_ClockSourceAlt2 = 2U, /*!< Alternate clock (ALTCLK). >*/
    kADC_ClockSourceAlt3 = 3U, /*!< Asynchronous clock (ADACK). >*/
} adc_clock_source_t;

/*!
 * @brief Compare function mode.
 */
typedef enum _adc_compare_mode
{
    kADC_CompareDisableMode        = 0U, /*!< Compare function disabled. >*/
    kADC_CompareLessMode           = 2U, /*!< Compare triggers when input is less than compare level. >*/
    kADC_CompareGreaterOrEqualMode = 3U, /*!< Compare triggers when input is greater than or equal to compare level. >*/
} adc_compare_mode_t;

/*!
 * @brief ADC status flags mask.
 */
enum _adc_status_flags
{
    kADC_ActiveFlag    = ADC_SC2_ADACT_MASK,  /*!< Indicates that a conversion is in progress. >*/
    kADC_FifoEmptyFlag = ADC_SC2_FEMPTY_MASK, /*!< Indicates that ADC result FIFO have no valid new data. >*/
    kADC_FifoFullFlag  = ADC_SC2_FFULL_MASK,  /*!< Indicates that ADC result FIFO is full. >*/
};

#if defined(FSL_FEATURE_ADC_HAS_SC5_REG) && FSL_FEATURE_ADC_HAS_SC5_REG
/*!
 * @brief Hardware tigger mask mode.
 */
typedef enum _adc_hardware_trigger_mask_mode
{
    kADC_HWTriggerMaskDisableMode =
        0U, /*!< Hardware trigger mask disable and hardware trigger can trigger ADC conversion. >*/
    kADC_HWTriggerMaskAutoMode = 1U, /*!< Hardware trigger mask automatically when data fifo is not empty. >*/
    kADC_HWTriggerMaskEnableMode =
        2U, /*!< Hardware trigger mask enable and hardware trigger cannot trigger ADC conversion. >*/
} adc_hardware_trigger_mask_mode_t;
#endif /* FSL_FEATURE_ADC_HAS_SC5_REG */

/*!
 * @brief ADC converter configuration.
 */
typedef struct _adc_config
{
    adc_reference_voltage_source_t
        referenceVoltageSource; /*!< Selects the voltage reference source used for conversions. >*/
    bool enableLowPower; /*!< Enable low power mode. The power is reduced at the expense of maximum clock speed. >*/
    bool enableLongSampleTime;            /*!< Enable long sample time mode. >*/
    adc_clock_divider_t clockDivider;     /*!< Select the divider of input clock source. >*/
    adc_resolution_mode_t ResolutionMode; /*!< Select the sample resolution mode. >*/
    adc_clock_source_t clockSource;       /*!< Select the input Clock source. >*/
} adc_config_t;

/*!
 * @brief ADC hardware comparison configuration.
 */
typedef struct _adc_hardware_compare_config
{
    uint32_t compareValue;          /*!< Setting the compare value. The value are compared to the conversion result. >*/
    adc_compare_mode_t compareMode; /*!< Setting the compare mode. Refer to "adc_compare_mode_t". >*/
} adc_hardware_compare_config_t;

/*!
 * @brief ADC FIFO configuration.
 */
typedef struct _adc_fifo_config
{
#if defined(FSL_FEATURE_ADC_HAS_SC4_HTRGME) && FSL_FEATURE_ADC_HAS_SC4_HTRGME
    bool enableHWTriggerMultConv; /*!< The field is valid when FIFO is enabled.Enable hardware trigger
                                       multiple conversion. One hardware trigger pulse triggers multiple
                                       conversions in fifo mode. >*/
#endif                            /* FSL_FEATURE_ADC_HAS_SC4_HTRGME */
    bool enableFifoScanMode;      /*!< The field is valid when FIFO is enabled. Enable the FIFO scan mode.
                                     If enable, ADC will repeat using the first FIFO channel as the conversion
                                     channel until the result FIFO is fulfilled. >*/
    bool enableCompareAndMode;    /*!< The field is valid when FIFO is enabled. If enable, ADC will AND all of compare
                                       triggers and set COCO after all of compare triggers occur. If disable, ADC will
                                       OR all of compare triggers and set COCO after at least one of compare trigger
                                     occurs. >*/
    uint32_t FifoDepth;           /*!< Setting the depth of FIFO. Depth of fifo is FifoDepth + 1. When FifoDepth = 0U,
                                       the FIFO is DISABLED. When FifoDepth is set to nonzero, the FIFO function is ENABLED
                                       and the depth is indicated by the FifoDepth field. >*/
} adc_fifo_config_t;

/*!
 * @brief ADC channel conversion configuration
 */
typedef struct _adc_channel_config
{
    uint32_t channelNumber;                    /*!< Setting the conversion channel number. The available range is 0-31.
                                                    See channel connection information for each chip in Reference
                                                    Manual document. */
    bool enableContinuousConversion;           /*!< enables continuous conversions. >*/
    bool enableInterruptOnConversionCompleted; /*!< Generate an interrupt request once the conversion is completed. */
} adc_channel_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initializes the ADC module.
 *
 * @param base   ADC peripheral base address.
 * @param config Pointer to configuration structure. See "adc_config_t".
 */
void ADC_Init(ADC_Type *base, const adc_config_t *config);

/*!
 * @brief De-initialize the ADC module.
 *
 * @param base ADC peripheral base address.
 */
void ADC_Deinit(ADC_Type *base);

/*!
 * @brief Gets an available pre-defined settings for the converter's configuration.
 *
 * This function initializes the converter configuration structure with available settings. The default values are as
 * follows.
 * @code
 *   config->referenceVoltageSource = kADC_ReferenceVoltageSourceAlt0;
 *   config->enableLowPower = false;
 *   config->enableLongSampleTime = false;
 *   config->clockDivider = kADC_ClockDivider1;
 *   config->ResolutionMode = kADC_Resolution8BitMode;
 *   config->clockSource = kADC_ClockSourceAlt0;
 * @endcode
 * @param config Pointer to the configuration structure.
 */
void ADC_GetDefaultConfig(adc_config_t *config);

/*!
 * @brief Enable the hardware trigger mode.
 *
 * @param base ADC peripheral base address.
 * @param enable Switcher of the hardware trigger feature. "true" means enabled, "false" means not enabled.
 */
static inline void ADC_EnableHardwareTrigger(ADC_Type *base, bool enable)
{
    if (enable)
    {
        base->SC2 |= ADC_SC2_ADTRG_MASK;
    }
    else
    {
        base->SC2 &= ~ADC_SC2_ADTRG_MASK;
    }
}

/*!
 * @brief Configure the hardware compare mode.
 *
 * The compare function can be configured to check for an upper or lower limit. After the
 * input is sampled and converted, the result is added to the complement of the compare
 * value (ADC_CV).
 *
 * @param base ADC peripheral base address.
 * @param config Pointer to "adc_hardware_compare_config_t" structure.
 */
void ADC_SetHardwareCompare(ADC_Type *base, const adc_hardware_compare_config_t *config);

/*!
 * @brief Configure the Fifo mode.
 *
 * The ADC module supports FIFO operation to minimize the interrupts to CPU in order to
 * reduce CPU loading in ADC interrupt service routines. This module contains two FIFOs
 * to buffer analog input channels and analog results respectively.
 *
 * @param base ADC peripheral base address.
 * @param config Pointer to "adc_fifo_config_t" structure.
 */
void ADC_SetFifoConfig(ADC_Type *base, const adc_fifo_config_t *config);

/*!
 * @brief Gets an available pre-defined settings for the FIFO's configuration.
 *
 * @param config Pointer to the FIFO configuration structure, please refer to @ref adc_fifo_config_t for details.
 */
void ADC_GetDefaultFIFOConfig(adc_fifo_config_t *config);

/*!
 * @brief Configures the conversion channel.
 *
 * This operation triggers the conversion when in software trigger mode. When in hardware trigger mode, this API
 * configures the channel while the external trigger source helps to trigger the conversion.
 *
 * @param base ADC peripheral base address.
 * @param config Pointer to "adc_channel_config_t" structure.
 */
void ADC_SetChannelConfig(ADC_Type *base, const adc_channel_config_t *config);

/*!
 * @brief Get the status flags of channel.
 *
 * @param  base ADC peripheral base address.
 * @return "True" means conversion has completed and "false" means conversion has not completed.
 */
bool ADC_GetChannelStatusFlags(ADC_Type *base);

/*!
 * @brief Get the ADC status flags.
 *
 * @param base ADC peripheral base address.
 * @return Flags' mask if indicated flags are asserted. See "_adc_status_flags".
 */
uint32_t ADC_GetStatusFlags(ADC_Type *base);

/*!
 * @brief Disables the I/O port control of the pins used as analog inputs.
 *
 * When a pin control register bit is set, the following conditions are forced for the associated MCU pin:
 *  -The output buffer is forced to its high impedance state.
 *  -The input buffer is disabled. A read of the I/O port returns a zero for any pin with its input buffer disabled.
 *  -The pullup is disabled.
 *
 * @param base ADC peripheral base address.
 * @param mask The mask of the pin associated with channel ADx. Valid range is AD0:0x1U ~ AD15:0x8000U.
 *             For example: If enable AD0, AD1 and AD2 pins, mask should be set to 0x7U.
 * @param enable The "true" means enabled, "false" means not enabled.
 */
static inline void ADC_EnableAnalogInput(ADC_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->APCTL1 |= ADC_APCTL1_ADPC(mask);
    }
    else
    {
        base->APCTL1 &= ~ADC_APCTL1_ADPC(mask);
    }
}

/*!
 * @brief  Gets the conversion value.
 *
 * @param base ADC peripheral base address.
 * @return Conversion value.
 */
static inline uint32_t ADC_GetChannelConversionValue(ADC_Type *base)
{
    return (((base->R) & ADC_R_ADR_MASK) >> ADC_R_ADR_SHIFT);
}

#if defined(FSL_FEATURE_ADC_HAS_SC5_REG) && FSL_FEATURE_ADC_HAS_SC5_REG
static inline void ADC_SetHardwareTriggerMaskMode(ADC_Type *base, adc_hardware_trigger_mask_mode_t mode)
{
    base->SC5 = (uint32_t)mode << ADC_SC5_HTRGMASKSEL_SHIFT;
}
#endif /* FSL_FEATURE_ADC_HAS_SC5_REG */

/*@}*/

#if defined(__cplusplus)
}
#endif

/*@}*/

#endif /* _FSL_ADC_H_ */
