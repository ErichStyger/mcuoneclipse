/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ACMP_H_
#define _FSL_ACMP_H_

#include "fsl_common.h"

/*!
 * @addtogroup acmp
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief ACMP driver version 2.0.2. */
#define FSL_ACMP_DRIVER_VERSION (MAKE_VERSION(2U, 0U, 2U))
/*@}*/

/*!
 * @brief Analog Comparator Hysterisis Selection.
 */
typedef enum _acmp_hysterisis_mode
{
    kACMP_HysterisisLevel1 = 0U, /*!< ACMP hysterisis is 20mv. >*/
    kACMP_HysterisisLevel2 = 1U, /*!< ACMP hysterisis is 30mv. >*/
} acmp_hysterisis_mode_t;

/*!
 * @brief DAC Voltage Reference source.
 */
typedef enum _acmp_reference_voltage_source
{
    kACMP_VrefSourceVin1 = 0U, /*!< The DAC selects Bandgap as the reference. */
    kACMP_VrefSourceVin2 = 1U, /*!< The DAC selects VDDA as the reference. */
} acmp_reference_voltage_source_t;

/*!
 * @brief The sensitivity modes of the interrupt trigger.
 */
typedef enum _acmp_interrupt_mode
{
    kACMP_OutputFallingInterruptMode  = 0U, /*!< ACMP interrupt on output falling edge. >*/
    kACMP_OutputRisingInterruptMode   = 1U, /*!< ACMP interrupt on output rising edge. >*/
    kACMP_OutputBothEdgeInterruptMode = 3U, /*!< ACMP interrupt on output falling or rising edge. >*/
} acmp_interrupt_mode_t;

/*!
 * @brief The ACMP input channel selection.
 */
typedef enum _acmp_input_channel_selection
{
    kACMP_ExternalReference0 = 0U, /*!< External reference 0 is selected to as input channel. >*/
    kACMP_ExternalReference1 = 1U, /*!< External reference 1 is selected to as input channel. >*/
    kACMP_ExternalReference2 = 2U, /*!< External reference 2 is selected to as input channel. >*/
    kACMP_InternalDACOutput  = 3U, /*!< Internal DAC putput is selected to as input channel. >*/
} acmp_input_channel_selection_t;

/*!
 * @brief The ACMP status flags.
 */
enum _acmp_status_flags
{
    kACMP_InterruptFlag = ACMP_CS_ACF_MASK, /*!< ACMP interrupt on output valid edge. >*/
    kACMP_OutputFlag    = ACMP_CS_ACO_MASK, /*!< The current value of the analog comparator output. >*/
};

/*!
 * @brief Configuration for ACMP.
 */
typedef struct _acmp_config
{
    bool enablePinOut;                     /*!< The comparator output is available on the associated pin. */
    acmp_hysterisis_mode_t hysteresisMode; /*!< Hysteresis mode. */
} acmp_config_t;

/*!
 * @brief Configuration for Internal DAC.
 */
typedef struct _acmp_dac_config
{
    uint8_t DACValue; /*!< Value for DAC Output Voltage. Available range is 0-63. */
    acmp_reference_voltage_source_t referenceVoltageSource; /*!< Supply voltage reference source. */
} acmp_dac_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initialize the ACMP.
 *
 * The default configuration can be got by calling ACMP_GetDefaultConfig().
 *
 * @param base ACMP peripheral base address.
 * @param config Pointer to ACMP configuration structure.
 */
void ACMP_Init(ACMP_Type *base, const acmp_config_t *config);

/*!
 * @brief De-Initialize the ACMP.
 *
 * @param base ACMP peripheral basic address.
 */
void ACMP_Deinit(ACMP_Type *base);

/*!
 * @brief Gets the default configuration for ACMP.
 *
 * This function initializes the user configuration structure to default value. The default value are:
 * Example:
 *   @code
 *   config->enablePinOut = false;
 *   config->hysteresisMode = kACMP_HysterisisLevel1;
 *   @endcode
 *
 * @param config Pointer to ACMP configuration structure.
 */
void ACMP_GetDefaultConfig(acmp_config_t *config);

/*!
 * @brief Enable/Disable the ACMP module.
 *
 * @param base ACMP peripheral base address.
 * @param enable Switcher to enable/disable ACMP module.
 */
static inline void ACMP_Enable(ACMP_Type *base, bool enable)
{
    if (enable)
    {
        base->CS |= ACMP_CS_ACE_MASK;
    }
    else
    {
        base->CS &= ~(uint8_t)ACMP_CS_ACE_MASK;
    }
}

/*!
 * @brief Enable the ACMP interrupt and determines the sensitivity modes of the interrupt trigger.
 *
 *
 * @param base ACMP peripheral base address.
 * @param mode Select one interrupt mode to generate interrupt.
 */
void ACMP_EnableInterrupt(ACMP_Type *base, acmp_interrupt_mode_t mode);

/*!
 * @brief Disable the ACMP interrupt.
 *
 * @param base ACMP peripheral base address.
 */
static inline void ACMP_DisableInterrupt(ACMP_Type *base)
{
    base->CS &= ~(uint8_t)ACMP_CS_ACIE_MASK;
}

/*!
 * @brief Configure the ACMP positive and negative input channel.
 *
 * @param base ACMP peripheral base address.
 * @param PositiveInput ACMP Positive Input Select. Refer to "acmp_input_channel_selection_t".
 * @param negativeInout ACMP Negative Input Select. Refer to "acmp_input_channel_selection_t".
 */
void ACMP_SetChannelConfig(ACMP_Type *base,
                           acmp_input_channel_selection_t PositiveInput,
                           acmp_input_channel_selection_t negativeInout);

/*
 * @brief Configure the internal DAC.
 *
 * @param base ACMP peripheral base address.
 * @param config Pointer to DAC configuration structure. "NULL" is for disabling the feature.
 */
void ACMP_SetDACConfig(ACMP_Type *base, const acmp_dac_config_t *config);

/*!
 * @brief Enable/Disable ACMP input pin.
 *        The API controls if the corresponding ACMP external pin can be driven by an analog input
 *
 * @param base ACMP peripheral base address.
 * @param mask The mask of the pin associated with channel ADx. Valid range is AD0:0x1U ~ AD3:0x4U.
 *             For example: If enable AD0, AD1 and AD2 pins, mask should be set to 0x7U(0x1 | 0x2 | 0x4).
 * @param enable Switcher to enable/disable ACMP module.
 */
void ACMP_EnableInputPin(ACMP_Type *base, uint32_t mask, bool enable);

/*!
 * @brief Get ACMP status flags.
 *
 * @param base ACMP peripheral base address.
 * @return Flags' mask if indicated flags are asserted. See "_acmp_status_flags".
 */
static inline uint8_t ACMP_GetStatusFlags(ACMP_Type *base)
{
    return (base->CS) & (ACMP_CS_ACF_MASK | ACMP_CS_ACO_MASK);
}

/*!
 * @brief Clear interrupts status flag.
 *
 * @param base ACMP peripheral base address.
 */
static inline void ACMP_ClearInterruptFlags(ACMP_Type *base)
{
    base->CS &= ~(uint8_t)ACMP_CS_ACF_MASK;
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*@}*/

#endif /* _FSL_ACMP_H_ */
