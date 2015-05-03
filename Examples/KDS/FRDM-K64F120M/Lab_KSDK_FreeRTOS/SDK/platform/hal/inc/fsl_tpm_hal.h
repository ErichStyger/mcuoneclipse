/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_TPM_HAL_H__)
#define __FSL_TPM_HAL_H__

#include "fsl_device_registers.h"
#include <stdbool.h>
#include <assert.h>

#if FSL_FEATURE_SOC_TPM_COUNT

/*!
 * @addtogroup tpm_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of number of channels for each TPM instance */
extern const uint32_t g_tpmChannelCount[TPM_INSTANCE_COUNT];

/*! @brief TPM clock source selection for TPM_SC[CMOD].*/
typedef enum _tpm_clock_mode
{
     kTpmClockSourceNoneClk = 0,    /*TPM clock mode, None CLK*/
     kTpmClockSourceModuleClk,      /*TPM clock mode, Module CLK*/
     kTpmClockSourceExternalClk,    /*TPM clock mode, External input clock*/
     kTpmClockSourceReservedClk     /*TPM clock mode, Reserved*/
}tpm_clock_mode_t;

/*! @brief TPM counting mode, up or down*/
typedef enum _tpm_counting_mode
{
     kTpmCountingUp = 0,           /*TPM counter mode, Up counting only*/
     kTpmCountingUpDown            /*TPM counter mode, Up/Down counting mode*/
}tpm_counting_mode_t;

/*! @brief TPM prescaler factor selection for clock source*/
typedef enum _tpm_clock_ps
{
     kTpmDividedBy1 = 0,          /*TPM module clock prescaler, by 1*/
     kTpmDividedBy2 ,             /*TPM module clock prescaler, by 2*/
     kTpmDividedBy4 ,             /*TPM module clock prescaler, by 4*/
     kTpmDividedBy8,              /*TPM module clock prescaler, by 8*/
     kTpmDividedBy16,             /*TPM module clock prescaler, by 16*/
     kTpmDividedBy32,             /*TPM module clock prescaler, by 32*/
     kTpmDividedBy64,             /*TPM module clock prescaler, by 64*/
     kTpmDividedBy128             /*TPM module clock prescaler, by 128*/
}tpm_clock_ps_t;

/*! @brief TPM trigger sources, please refer to the chip reference manual for available options */
typedef enum _tpm_trigger_source_t
{
    kTpmTrigSel0 = 0,       /*!< TPM trigger source 0 */
    kTpmTrigSel1,           /*!< TPM trigger source 1 */
    kTpmTrigSel2,           /*!< TPM trigger source 2 */
    kTpmTrigSel3,           /*!< TPM trigger source 3 */
    kTpmTrigSel4,           /*!< TPM trigger source 4 */
    kTpmTrigSel5,           /*!< TPM trigger source 5 */
    kTpmTrigSel6,           /*!< TPM trigger source 6 */
    kTpmTrigSel7,           /*!< TPM trigger source 7 */
    kTpmTrigSel8,           /*!< TPM trigger source 8 */
    kTpmTrigSel9,           /*!< TPM trigger source 8 */
    kTpmTrigSel10,          /*!< TPM trigger source 10 */
    kTpmTrigSel11,          /*!< TPM trigger source 11 */
    kTpmTrigSel12,          /*!< TPM trigger source 12 */
    kTpmTrigSel13,          /*!< TPM trigger source 13 */
    kTpmTrigSel14,          /*!< TPM trigger source 14 */
    kTpmTrigSel15           /*!< TPM trigger source 15 */
}tpm_trigger_source_t;

/*! @brief TPM operation mode */
typedef enum _tpm_pwm_mode_t
{
    kTpmEdgeAlignedPWM = 0, /*!< Edge aligned mode @internal gui name="Edge aligned" */
    kTpmCenterAlignedPWM /*!< Center aligned mode @internal gui name="Center aligned" */
}tpm_pwm_mode_t;

/*! @brief TPM PWM output pulse mode, high-true or low-true on match up */
typedef enum _tpm_pwm_edge_mode_t
{
    kTpmHighTrue = 0, /*!< Clear output on match, set output on reload @internal gui name="High true" */
    kTpmLowTrue /*!< Set output on match, clear output on reload @internal gui name="Low true" */
}tpm_pwm_edge_mode_t;

/*! @brief TPM input capture modes */
typedef enum _tpm_input_capture_mode_t
{
    kTpmRisingEdge = 1,
    kTpmFallingEdge,
    kTpmRiseOrFallEdge
}tpm_input_capture_mode_t;

/*! @brief TPM output compare modes */
typedef enum _tpm_output_compare_mode_t
{
    kTpmOutputNone = 0,
    kTpmToggleOutput,
    kTpmClearOutput,
    kTpmSetOutput,
    kTpmHighPulseOutput,
    kTpmLowPulseOutput
}tpm_output_compare_mode_t;

/*! @brief Error codes for TPM driver. */
typedef enum _tpm_status
{
    kStatusTpmSuccess = 0x00U,        /*!< TPM success status.*/
    kStatusTpmFail    = 0x01U         /*!< TPM error status.*/
} tpm_status_t;

/*!
 * @brief TPM driver PWM parameter
 * @internal gui name="PWM channels configuration" id="tpmPwmCfg"
 */
typedef struct TpmPwmParam
{
    tpm_pwm_mode_t mode;          /*!< TPM PWM operation mode  @internal gui name="Mode" id="PWMmode" */
    tpm_pwm_edge_mode_t edgeMode;    /*!< PWM output mode  @internal gui name="Edge mode" id="ChannelEdgeMode" */
    uint32_t uFrequencyHZ;           /*!< PWM period in Hz  @internal gui name="Frequency" id="Frequency" */
    uint32_t uDutyCyclePercent;      /*!< PWM pulse width, value should be between 0 to 100
                                          0=inactive signal(0% duty cycle)...
                                          100=active signal (100% duty cycle).  @internal gui name="Duty cycle" id="ChannelDuty" */
}tpm_pwm_param_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief reset tpm registers
 *
 * @param tpmBase TPM module base address pointer
 * @param instance The TPM peripheral instance number.
 */
void TPM_HAL_Reset(TPM_Type *tpmBase, uint32_t instance);

/*!
 * @brief Enables the TPM PWM output mode.
 *
 * @param tpmBase TPM module base address pointer
 * @param config PWM configuration parameter
 * @param channel The TPM channel number.
 */
void TPM_HAL_EnablePwmMode(TPM_Type *tpmBase, tpm_pwm_param_t *config, uint8_t channel);

/*!
 * @brief Disables the TPM channel.
 *
 * @param tpmBase TPM module base address pointer
 * @param channel The TPM channel number.
 */
void TPM_HAL_DisableChn(TPM_Type *tpmBase, uint8_t channel);

/*!
 * @brief Set TPM clock mode.
 *
 * When disabling the TPM counter, the function will wait till it receives an acknowledge from the
 * TPM clock domain
 *
 * @param tpmBase TPM module base address pointer
 * @param mode The TPM counter clock mode (source).
 */
void TPM_HAL_SetClockMode(TPM_Type *tpmBase, tpm_clock_mode_t mode);

/*!
 * @brief get TPM clock mode.
 * @param tpmBase TPM module base address pointer
 * @return The TPM counter clock mode (source).
 */
static inline tpm_clock_mode_t TPM_HAL_GetClockMode(TPM_Type *tpmBase)
{
    return (tpm_clock_mode_t) TPM_BRD_SC_CMOD(tpmBase);
}

/*!
 * @brief set TPM clock divider.
 * @param tpmBase TPM module base address pointer
 * @param ps  The TPM peripheral clock prescale divider
 */
static inline void TPM_HAL_SetClockDiv(TPM_Type *tpmBase, tpm_clock_ps_t ps)
{
    TPM_BWR_SC_PS(tpmBase, ps);
}

/*!
 * @brief get TPM clock divider.
 * @param tpmBase TPM module base address pointer
 * @return The TPM peripheral clock prescale divider.
 */
static inline tpm_clock_ps_t TPM_HAL_GetClockDiv(TPM_Type *tpmBase)
{
    return (tpm_clock_ps_t)TPM_BRD_SC_PS(tpmBase);
}

/*!
 * @brief Enable the TPM peripheral timer overflow interrupt.
 *
 * @param tpmBase TPM module base address pointer
 */
static inline void TPM_HAL_EnableTimerOverflowInt(TPM_Type *tpmBase)
{
    TPM_BWR_SC_TOIE(tpmBase, 1);
}

/*!
 * @brief Disable the TPM peripheral timer overflow interrupt.
 *
 * @param tpmBase TPM module base address pointer
 */
static inline void TPM_HAL_DisableTimerOverflowInt(TPM_Type *tpmBase)
{
    TPM_BWR_SC_TOIE(tpmBase, 0);
}

/*!
 * @brief Read the bit that controls TPM timer overflow interrupt enablement.
 *
 * @param tpmBase TPM module base address pointer
 * @return true if overflow interrupt is enabled, false if not
 */
static inline bool TPM_HAL_IsOverflowIntEnabled(TPM_Type *tpmBase)
{
    return (bool)(TPM_BRD_SC_TOIE(tpmBase));
}

/*!
 * @brief return TPM peripheral timer overflow interrupt flag.
 * @param tpmBase TPM module base address pointer
 * @return true if overflow, false if not
 */
static inline bool TPM_HAL_GetTimerOverflowStatus(TPM_Type *tpmBase)
{
    return (bool)(TPM_BRD_SC_TOF(tpmBase));
}

/*!
 * @brief Clear the TPM timer overflow interrupt flag.
 * @param tpmBase TPM module base address pointer
 */
static inline void TPM_HAL_ClearTimerOverflowFlag(TPM_Type *tpmBase)
{
    TPM_BWR_SC_TOF(tpmBase, 1);
}

/*!
 * @brief set TPM center-aligned PWM select.
 * @param tpmBase TPM module base address pointer
 * @param mode 1:upcounting mode 0:up_down counting mode.
 */
static inline void TPM_HAL_SetCpwms(TPM_Type *tpmBase, uint8_t mode)
{
    assert(mode < 2);
    TPM_BWR_SC_CPWMS(tpmBase, mode);
}

/*!
 * @brief get TPM center-aligned PWM selection value.
 * @param tpmBase TPM module base address pointer
 * @return Whether the TPM center-aligned PWM is selected or not.
 */
static inline bool TPM_HAL_GetCpwms(TPM_Type *tpmBase)
{
    return (bool)TPM_BRD_SC_CPWMS(tpmBase);
}

/*!
 * @brief clear TPM peripheral current counter value.
 * @param tpmBase TPM module base address pointer
 */
static inline void  TPM_HAL_ClearCounter(TPM_Type *tpmBase)
{
    TPM_BWR_CNT_COUNT(tpmBase, 0);
}

/*!
 * @brief return TPM peripheral current counter value.
 * @param tpmBase TPM module base address pointer
 * @return current TPM timer counter value
 */
static inline uint16_t  TPM_HAL_GetCounterVal(TPM_Type *tpmBase)
{
    return TPM_BRD_CNT_COUNT(tpmBase);
}

/*!
 * @brief set TPM peripheral timer modulo value.
 * @param tpmBase TPM module base address pointer
 * @param val The value to be set to the timer modulo
 */
static inline void TPM_HAL_SetMod(TPM_Type *tpmBase, uint16_t val)
{
    /*As RM mentioned, first clear TPM_CNT then write value to TPM_MOD*/
    TPM_BWR_CNT_COUNT(tpmBase, 0);
    TPM_BWR_MOD_MOD(tpmBase, val);
}

/*!
 * @brief return TPM peripheral counter modulo value.
 * @param tpmBase TPM module base address pointer
 * @return TPM timer modula value
 */
static inline uint16_t  TPM_HAL_GetMod(TPM_Type *tpmBase)
{
    return TPM_BRD_MOD_MOD(tpmBase);
}

/*TPM channel operate mode(Mode, edge and level selection) for capture, output, pwm*/

/*!
 * @brief Set TPM peripheral timer channel mode and edge level,
 *
 * TPM channel operate mode, MSnBA and ELSnBA shoud be set at the same time.
 *
 * @param tpmBase The TPM base address
 * @param channel  The TPM peripheral channel number
 * @param value    The value to set for MSnBA and ELSnBA
 */
static inline void TPM_HAL_SetChnMsnbaElsnbaVal(TPM_Type *tpmBase, uint8_t channel, uint8_t value)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);

    /* Keep CHIE bit value not changed by this function, so read it first and or with value*/
    value |= TPM_RD_CnSC(tpmBase, channel) & TPM_CnSC_CHIE_MASK;

    TPM_WR_CnSC(tpmBase, channel, value);
}

/*!
 * @brief get TPM peripheral timer channel mode.
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 * @return The MSnB:MSnA mode value, will be 00,01, 10, 11
 */
static inline uint8_t TPM_HAL_GetChnMsnbaVal(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (TPM_RD_CnSC(tpmBase, channel) & (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK)) >> TPM_CnSC_MSA_SHIFT;
}

/*!
 * @brief get TPM peripheral timer channel edge level.
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 * @return The ELSnB:ELSnA mode value, will be 00,01, 10, 11
 */
static inline uint8_t TPM_HAL_GetChnElsnbaVal(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (TPM_RD_CnSC(tpmBase, channel) & (TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)) >> TPM_CnSC_ELSA_SHIFT;
}

/*!
 * @brief enable TPM peripheral timer channel(n) interrupt.
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 */
static inline void TPM_HAL_EnableChnInt(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnSC_CHIE(tpmBase, channel, 1);
}

/*!
 * @brief disable TPM peripheral timer channel(n) interrupt.
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 */
static inline void TPM_HAL_DisableChnInt(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnSC_CHIE(tpmBase, channel, 0);
}

/*!
 * @brief get TPM peripheral timer channel(n) interrupt enabled or not.
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number
 * @return Whether the TPM peripheral timer channel(n) interrupt is enabled or not.
 */
static inline bool TPM_HAL_IsChnIntEnabled(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (bool)(TPM_BRD_CnSC_CHIE(tpmBase, channel));
}

/*!
 * @brief return if any event for TPM peripheral timer channel has occourred ,
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 * @return true if event occourred, false otherwise
 */
static inline bool TPM_HAL_GetChnStatus(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return (bool)(TPM_BRD_CnSC_CHF(tpmBase, channel));
}

/*!
 * @brief return if any event for TPM peripheral timer channel has occourred ,
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 */
static inline void TPM_HAL_ClearChnInt(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnSC_CHF(tpmBase, channel, 0x1);
}

/*TPM Channel control*/
/*!
 * @brief set TPM peripheral timer channel counter value,
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 * @param val counter value to be set
 */
static inline void TPM_HAL_SetChnCountVal(TPM_Type *tpmBase, uint8_t channel, uint16_t val)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    TPM_BWR_CnV_VAL(tpmBase, channel, val);
}

/*!
 * @brief get TPM peripheral timer channel counter value.
 * @param tpmBase TPM module base address pointer
 * @param channel  The TPM peripheral channel number.
 * @return The TPM timer channel counter value.
 */
static inline uint16_t TPM_HAL_GetChnCountVal(TPM_Type *tpmBase, uint8_t channel)
{
    assert(channel < FSL_FEATURE_TPM_CHANNEL_COUNT);
    return TPM_BRD_CnV_VAL(tpmBase, channel);
}

/*!
 * @brief get TPM peripheral timer channel event status.
 * @param tpmBase TPM module base address pointer
 * @return The TPM timer channel event status.
 */
static inline uint32_t TPM_HAL_GetStatusRegVal(TPM_Type *tpmBase)
{
    return TPM_RD_STATUS(tpmBase);
}

/*!
 * @brief clear TPM peripheral timer clear status register value,
 * @param tpmBase TPM module base address pointer
 * @param tpm_status tpm channel or overflow flag to clear
 */
static inline void TPM_HAL_ClearStatusReg(TPM_Type *tpmBase, uint16_t tpm_status)
{
    TPM_WR_STATUS(tpmBase, tpm_status);
}

/*!
 * @brief set TPM peripheral timer trigger.
 * @param tpmBase TPM module base address pointer
 * @param trigger_num  0-15
 */
static inline void TPM_HAL_SetTriggerSrc(TPM_Type *tpmBase, tpm_trigger_source_t trigger_num)
{
    TPM_BWR_CONF_TRGSEL(tpmBase, trigger_num);
}

/*!
 * @brief set TPM peripheral timer running on trigger or not .
 * @param tpmBase TPM module base address pointer
 * @param enable true to enable, 1 to enable
 */
static inline void TPM_HAL_SetTriggerMode(TPM_Type *tpmBase, bool enable)
{
    TPM_BWR_CONF_CSOT (tpmBase, enable);
}

/*!
 * @brief enable TPM timer counter reload on selected trigger or not.
 * @param tpmBase TPM module base address pointer
 * @param enable  true to enable, false to disable.
 */
static inline void TPM_HAL_SetReloadOnTriggerMode(TPM_Type *tpmBase, bool enable)
{
    TPM_BWR_CONF_CROT(tpmBase, enable);
}

/*!
 * @brief enable TPM timer counter sotp on selected trigger or not.
 * @param tpmBase TPM module base address pointer
 * @param enable  true to enable, false to disable.
 */
static inline void TPM_HAL_SetStopOnOverflowMode(TPM_Type *tpmBase, bool enable)
{
    TPM_BWR_CONF_CSOO(tpmBase, enable);
}

/*!
 * @brief enable TPM timer global time base.
 * @param tpmBase TPM module base address pointer
 * @param enable  true to enable, false to disable.
 */
static inline void TPM_HAL_EnableGlobalTimeBase(TPM_Type *tpmBase, bool enable)
{
    TPM_BWR_CONF_GTBEEN(tpmBase, enable);
}

/*!
 * @brief set BDM mode.
 * @param tpmBase TPM module base address pointer
 * @param enable  false pause, true continue work
 */
static inline void TPM_HAL_SetDbgMode(TPM_Type *tpmBase, bool enable)
{
    TPM_BWR_CONF_DBGMODE(tpmBase, enable ? 3 : 0);
}

/*!
 * @brief set WAIT mode behavior.
 * @param tpmBase TPM module base address pointer
 * @param enable  0 continue running, 1 stop running
 */
static inline void TPM_HAL_SetWaitMode(TPM_Type *tpmBase, bool enable)
{
    TPM_BWR_CONF_DOZEEN(tpmBase, enable ? 0 : 1);
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_TPM_COUNT */

#endif /* __FSL_TPM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

