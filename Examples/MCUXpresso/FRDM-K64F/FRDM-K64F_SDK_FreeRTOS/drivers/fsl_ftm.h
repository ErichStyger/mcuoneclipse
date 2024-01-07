/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_FTM_H_
#define _FSL_FTM_H_

#include "fsl_common.h"

/*!
 * @addtogroup ftm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief FTM driver version 2.5.0. */
#define FSL_FTM_DRIVER_VERSION (MAKE_VERSION(2, 5, 0))
/*@}*/

/*!
 * @brief List of FTM channels
 * @note Actual number of available channels is SoC dependent
 */
typedef enum _ftm_chnl
{
    kFTM_Chnl_0 = 0U, /*!< FTM channel number 0*/
    kFTM_Chnl_1,      /*!< FTM channel number 1 */
    kFTM_Chnl_2,      /*!< FTM channel number 2 */
    kFTM_Chnl_3,      /*!< FTM channel number 3 */
    kFTM_Chnl_4,      /*!< FTM channel number 4 */
    kFTM_Chnl_5,      /*!< FTM channel number 5 */
    kFTM_Chnl_6,      /*!< FTM channel number 6 */
    kFTM_Chnl_7       /*!< FTM channel number 7 */
} ftm_chnl_t;

/*! @brief List of FTM faults */
typedef enum _ftm_fault_input
{
    kFTM_Fault_0 = 0U, /*!< FTM fault 0 input pin */
    kFTM_Fault_1,      /*!< FTM fault 1 input pin */
    kFTM_Fault_2,      /*!< FTM fault 2 input pin */
    kFTM_Fault_3       /*!< FTM fault 3 input pin */
} ftm_fault_input_t;

/*! @brief FTM PWM operation modes */
typedef enum _ftm_pwm_mode
{
    kFTM_EdgeAlignedPwm = 0U,      /*!< Edge-aligned PWM */
    kFTM_CenterAlignedPwm,         /*!< Center-aligned PWM */
    kFTM_EdgeAlignedCombinedPwm,   /*!< Edge-aligned combined PWM */
    kFTM_CenterAlignedCombinedPwm, /*!< Center-aligned combined PWM */
    kFTM_AsymmetricalCombinedPwm   /*!< Asymmetrical combined PWM */
} ftm_pwm_mode_t;

/*! @brief FTM PWM output pulse mode: high-true, low-true or no output */
typedef enum _ftm_pwm_level_select
{
    kFTM_NoPwmSignal = 0U, /*!< No PWM output on pin */
    kFTM_LowTrue,          /*!< Low true pulses */
    kFTM_HighTrue          /*!< High true pulses */
} ftm_pwm_level_select_t;

/*! @brief Options to configure a FTM channel's PWM signal */
typedef struct _ftm_chnl_pwm_signal_param
{
    ftm_chnl_t chnlNumber;         /*!< The channel/channel pair number.
                                        In combined mode, this represents the channel pair number. */
    ftm_pwm_level_select_t level;  /*!< PWM output active level select. */
    uint8_t dutyCyclePercent;      /*!< PWM pulse width, value should be between 0 to 100
                                        0 = inactive signal(0% duty cycle)...
                                        100 = always active signal (100% duty cycle).*/
    uint8_t firstEdgeDelayPercent; /*!< Used only in kFTM_AsymmetricalCombinedPwm mode to generate an asymmetrical PWM.
                                        Specifies the delay to the first edge in a PWM period.
                                        If unsure leave as 0; Should be specified as a
                                        percentage of the PWM period */
    bool enableComplementary;      /*!< Used only in combined PWM mode.
                                        true: The combined channels output complementary signals;
                                        false: The combined channels output same signals; */
    bool enableDeadtime;           /*!< Used only in combined PWM mode with enable complementary.
                                        true: The deadtime insertion in this pair of channels is enabled;
                                        false: The deadtime insertion in this pair of channels is disabled. */
} ftm_chnl_pwm_signal_param_t;

/*! @brief Options to configure a FTM channel using precise setting.*/
typedef struct _ftm_chnl_pwm_config_param
{
    ftm_chnl_t chnlNumber;        /*!< The channel/channel pair number.
                                       In combined mode, this represents the channel pair number. */
    ftm_pwm_level_select_t level; /*!< PWM output active level select. */
    uint16_t dutyValue;           /*!< PWM pulse width, the uint of this value is timer ticks. */
    uint16_t firstEdgeValue;      /*!< Used only in kFTM_AsymmetricalCombinedPwm mode to generate an asymmetrical PWM.
                                       Specifies the delay to the first edge in a PWM period.
                                       If unsure leave as 0, uint of this value is timer ticks. */
    bool enableComplementary;     /*!< Used only in combined PWM mode.
                                       true: The combined channels output complementary signals;
                                       false: The combined channels output same signals; */
    bool enableDeadtime;          /*!< Used only in combined PWM mode with enable complementary.
                                       true: The deadtime insertion in this pair of channels is enabled;
                                       false: The deadtime insertion in this pair of channels is disabled. */
} ftm_chnl_pwm_config_param_t;

/*! @brief FlexTimer output compare mode */
typedef enum _ftm_output_compare_mode
{
    kFTM_NoOutputSignal = (1U << FTM_CnSC_MSA_SHIFT), /*!< No channel output when counter reaches CnV  */
    kFTM_ToggleOnMatch  = ((1U << FTM_CnSC_MSA_SHIFT) | (1U << FTM_CnSC_ELSA_SHIFT)), /*!< Toggle output */
    kFTM_ClearOnMatch   = ((1U << FTM_CnSC_MSA_SHIFT) | (2U << FTM_CnSC_ELSA_SHIFT)), /*!< Clear output */
    kFTM_SetOnMatch     = ((1U << FTM_CnSC_MSA_SHIFT) | (3U << FTM_CnSC_ELSA_SHIFT))  /*!< Set output */
} ftm_output_compare_mode_t;

/*! @brief FlexTimer input capture edge */
typedef enum _ftm_input_capture_edge
{
    kFTM_RisingEdge      = (1U << FTM_CnSC_ELSA_SHIFT), /*!< Capture on rising edge only*/
    kFTM_FallingEdge     = (2U << FTM_CnSC_ELSA_SHIFT), /*!< Capture on falling edge only*/
    kFTM_RiseAndFallEdge = (3U << FTM_CnSC_ELSA_SHIFT)  /*!< Capture on rising or falling edge */
} ftm_input_capture_edge_t;

/*! @brief FlexTimer dual edge capture modes */
typedef enum _ftm_dual_edge_capture_mode
{
    kFTM_OneShot    = 0U,                        /*!< One-shot capture mode */
    kFTM_Continuous = (1U << FTM_CnSC_MSA_SHIFT) /*!< Continuous capture mode */
} ftm_dual_edge_capture_mode_t;

/*! @brief FlexTimer dual edge capture parameters */
typedef struct _ftm_dual_edge_capture_param
{
    ftm_dual_edge_capture_mode_t mode;         /*!< Dual Edge Capture mode */
    ftm_input_capture_edge_t currChanEdgeMode; /*!< Input capture edge select for channel n */
    ftm_input_capture_edge_t nextChanEdgeMode; /*!< Input capture edge select for channel n+1 */
} ftm_dual_edge_capture_param_t;

/*! @brief FlexTimer quadrature decode modes */
typedef enum _ftm_quad_decode_mode
{
    kFTM_QuadPhaseEncode = 0U, /*!< Phase A and Phase B encoding mode */
    kFTM_QuadCountAndDir       /*!< Count and direction encoding mode */
} ftm_quad_decode_mode_t;

/*! @brief FlexTimer quadrature phase polarities */
typedef enum _ftm_phase_polarity
{
    kFTM_QuadPhaseNormal = 0U, /*!< Phase input signal is not inverted */
    kFTM_QuadPhaseInvert       /*!< Phase input signal is inverted */
} ftm_phase_polarity_t;

/*! @brief FlexTimer quadrature decode phase parameters */
typedef struct _ftm_phase_param
{
    bool enablePhaseFilter;             /*!< True: enable phase filter; false: disable filter */
    uint32_t phaseFilterVal;            /*!< Filter value, used only if phase filter is enabled */
    ftm_phase_polarity_t phasePolarity; /*!< Phase polarity */
} ftm_phase_params_t;

/*! @brief Structure is used to hold the parameters to configure a FTM fault */
typedef struct _ftm_fault_param
{
    bool enableFaultInput; /*!< True: Fault input is enabled; false: Fault input is disabled */
    bool faultLevel;       /*!< True: Fault polarity is active low; in other words, '0' indicates a fault;
                                False: Fault polarity is active high */
    bool useFaultFilter;   /*!< True: Use the filtered fault signal;
                                False: Use the direct path from fault input */
} ftm_fault_param_t;

/*! @brief FlexTimer pre-scaler factor for the dead time insertion*/
typedef enum _ftm_deadtime_prescale
{
    kFTM_Deadtime_Prescale_1 = 1U, /*!< Divide by 1 */
    kFTM_Deadtime_Prescale_4,      /*!< Divide by 4 */
    kFTM_Deadtime_Prescale_16      /*!< Divide by 16 */
} ftm_deadtime_prescale_t;

/*! @brief FlexTimer clock source selection*/
typedef enum _ftm_clock_source
{
    kFTM_SystemClock = 1U, /*!< System clock selected */
    kFTM_FixedClock,       /*!< Fixed frequency clock */
    kFTM_ExternalClock     /*!< External clock */
} ftm_clock_source_t;

/*! @brief FlexTimer pre-scaler factor selection for the clock source*/
typedef enum _ftm_clock_prescale
{
    kFTM_Prescale_Divide_1 = 0U, /*!< Divide by 1 */
    kFTM_Prescale_Divide_2,      /*!< Divide by 2 */
    kFTM_Prescale_Divide_4,      /*!< Divide by 4 */
    kFTM_Prescale_Divide_8,      /*!< Divide by 8 */
    kFTM_Prescale_Divide_16,     /*!< Divide by 16 */
    kFTM_Prescale_Divide_32,     /*!< Divide by 32 */
    kFTM_Prescale_Divide_64,     /*!< Divide by 64 */
    kFTM_Prescale_Divide_128     /*!< Divide by 128 */
} ftm_clock_prescale_t;

/*! @brief Options for the FlexTimer behaviour in BDM Mode */
typedef enum _ftm_bdm_mode
{
    kFTM_BdmMode_0 = 0U,
    /*!< FTM counter stopped, CH(n)F bit can be set, FTM channels in functional mode, writes to MOD,CNTIN and C(n)V
       registers bypass the register buffers */
    kFTM_BdmMode_1,
    /*!< FTM counter stopped, CH(n)F bit is not set, FTM channels outputs are forced to their safe value , writes to
       MOD,CNTIN and C(n)V registers bypass the register buffers */
    kFTM_BdmMode_2,
    /*!< FTM counter stopped, CH(n)F bit is not set, FTM channels outputs are frozen when chip enters in BDM mode,
       writes to MOD,CNTIN and C(n)V registers bypass the register buffers */
    kFTM_BdmMode_3
    /*!< FTM counter in functional mode, CH(n)F bit can be set, FTM channels in functional mode, writes to MOD,CNTIN and
       C(n)V registers is in fully functional mode */
} ftm_bdm_mode_t;

/*! @brief Options for the FTM fault control mode */
typedef enum _ftm_fault_mode
{
    kFTM_Fault_Disable = 0U, /*!< Fault control is disabled for all channels */
    kFTM_Fault_EvenChnls,    /*!< Enabled for even channels only(0,2,4,6) with manual fault clearing */
    kFTM_Fault_AllChnlsMan,  /*!< Enabled for all channels with manual fault clearing */
    kFTM_Fault_AllChnlsAuto  /*!< Enabled for all channels with automatic fault clearing */
} ftm_fault_mode_t;

/*!
 * @brief FTM external trigger options
 * @note Actual available external trigger sources are SoC-specific
 */
typedef enum _ftm_external_trigger
{
    kFTM_Chnl0Trigger = (1U << 4), /*!< Generate trigger when counter equals chnl 0 CnV reg */
    kFTM_Chnl1Trigger = (1U << 5), /*!< Generate trigger when counter equals chnl 1 CnV reg */
    kFTM_Chnl2Trigger = (1U << 0), /*!< Generate trigger when counter equals chnl 2 CnV reg */
    kFTM_Chnl3Trigger = (1U << 1), /*!< Generate trigger when counter equals chnl 3 CnV reg */
    kFTM_Chnl4Trigger = (1U << 2), /*!< Generate trigger when counter equals chnl 4 CnV reg */
    kFTM_Chnl5Trigger = (1U << 3), /*!< Generate trigger when counter equals chnl 5 CnV reg */
#if defined(FSL_FEATURE_FTM_HAS_CHANNEL6_TRIGGER) && (FSL_FEATURE_FTM_HAS_CHANNEL6_TRIGGER)
    kFTM_Chnl6Trigger =
        (1U << 8), /*!< Available on certain SoC's, generate trigger when counter equals chnl 6 CnV reg */
#endif
#if defined(FSL_FEATURE_FTM_HAS_CHANNEL7_TRIGGER) && (FSL_FEATURE_FTM_HAS_CHANNEL7_TRIGGER)
    kFTM_Chnl7Trigger =
        (1U << 9), /*!< Available on certain SoC's, generate trigger when counter equals chnl 7 CnV reg */
#endif
    kFTM_InitTrigger = (1U << 6), /*!< Generate Trigger when counter is updated with CNTIN */
#if defined(FSL_FEATURE_FTM_HAS_RELOAD_INITIALIZATION_TRIGGER) && (FSL_FEATURE_FTM_HAS_RELOAD_INITIALIZATION_TRIGGER)
    kFTM_ReloadInitTrigger = (1U << 7) /*!< Available on certain SoC's, trigger on reload point */
#endif
} ftm_external_trigger_t;

/*! @brief FlexTimer PWM sync options to update registers with buffer */
typedef enum _ftm_pwm_sync_method
{
    kFTM_SoftwareTrigger   = FTM_SYNC_SWSYNC_MASK, /*!< Software triggers PWM sync */
    kFTM_HardwareTrigger_0 = FTM_SYNC_TRIG0_MASK,  /*!< Hardware trigger 0 causes PWM sync */
    kFTM_HardwareTrigger_1 = FTM_SYNC_TRIG1_MASK,  /*!< Hardware trigger 1 causes PWM sync */
    kFTM_HardwareTrigger_2 = FTM_SYNC_TRIG2_MASK   /*!< Hardware trigger 2 causes PWM sync */
} ftm_pwm_sync_method_t;

/*!
 * @brief FTM options available as loading point for register reload
 * @note Actual available reload points are SoC-specific
 */
typedef enum _ftm_reload_point
{
    kFTM_Chnl0Match   = (1U << 0), /*!< Channel 0 match included as a reload point */
    kFTM_Chnl1Match   = (1U << 1), /*!< Channel 1 match included as a reload point */
    kFTM_Chnl2Match   = (1U << 2), /*!< Channel 2 match included as a reload point */
    kFTM_Chnl3Match   = (1U << 3), /*!< Channel 3 match included as a reload point */
    kFTM_Chnl4Match   = (1U << 4), /*!< Channel 4 match included as a reload point */
    kFTM_Chnl5Match   = (1U << 5), /*!< Channel 5 match included as a reload point */
    kFTM_Chnl6Match   = (1U << 6), /*!< Channel 6 match included as a reload point */
    kFTM_Chnl7Match   = (1U << 7), /*!< Channel 7 match included as a reload point */
    kFTM_CntMax       = (1U << 8), /*!< Use in up-down count mode only, reload when counter reaches the maximum value */
    kFTM_CntMin       = (1U << 9), /*!< Use in up-down count mode only, reload when counter reaches the minimum value */
    kFTM_HalfCycMatch = (1U << 10) /*!< Available on certain SoC's, half cycle match reload point */
} ftm_reload_point_t;

/*!
 * @brief List of FTM interrupts
 * @note Actual available interrupts are SoC-specific
 */
typedef enum _ftm_interrupt_enable
{
    kFTM_Chnl0InterruptEnable        = (1U << 0), /*!< Channel 0 interrupt */
    kFTM_Chnl1InterruptEnable        = (1U << 1), /*!< Channel 1 interrupt */
    kFTM_Chnl2InterruptEnable        = (1U << 2), /*!< Channel 2 interrupt */
    kFTM_Chnl3InterruptEnable        = (1U << 3), /*!< Channel 3 interrupt */
    kFTM_Chnl4InterruptEnable        = (1U << 4), /*!< Channel 4 interrupt */
    kFTM_Chnl5InterruptEnable        = (1U << 5), /*!< Channel 5 interrupt */
    kFTM_Chnl6InterruptEnable        = (1U << 6), /*!< Channel 6 interrupt */
    kFTM_Chnl7InterruptEnable        = (1U << 7), /*!< Channel 7 interrupt */
    kFTM_FaultInterruptEnable        = (1U << 8), /*!< Fault interrupt */
    kFTM_TimeOverflowInterruptEnable = (1U << 9), /*!< Time overflow interrupt */
    kFTM_ReloadInterruptEnable       = (1U << 10) /*!< Reload interrupt; Available only on certain SoC's */
} ftm_interrupt_enable_t;

/*!
 * @brief List of FTM flags
 * @note Actual available flags are SoC-specific
 */
typedef enum _ftm_status_flags
{
    kFTM_Chnl0Flag        = (1U << 0),  /*!< Channel 0 Flag */
    kFTM_Chnl1Flag        = (1U << 1),  /*!< Channel 1 Flag */
    kFTM_Chnl2Flag        = (1U << 2),  /*!< Channel 2 Flag */
    kFTM_Chnl3Flag        = (1U << 3),  /*!< Channel 3 Flag */
    kFTM_Chnl4Flag        = (1U << 4),  /*!< Channel 4 Flag */
    kFTM_Chnl5Flag        = (1U << 5),  /*!< Channel 5 Flag */
    kFTM_Chnl6Flag        = (1U << 6),  /*!< Channel 6 Flag */
    kFTM_Chnl7Flag        = (1U << 7),  /*!< Channel 7 Flag */
    kFTM_FaultFlag        = (1U << 8),  /*!< Fault Flag */
    kFTM_TimeOverflowFlag = (1U << 9),  /*!< Time overflow Flag */
    kFTM_ChnlTriggerFlag  = (1U << 10), /*!< Channel trigger Flag */
    kFTM_ReloadFlag       = (1U << 11)  /*!< Reload Flag; Available only on certain SoC's */
} ftm_status_flags_t;

#if !(defined(FSL_FEATURE_FTM_HAS_NO_QDCTRL) && FSL_FEATURE_FTM_HAS_NO_QDCTRL)
/*!
 * @brief List of FTM Quad Decoder flags.
 */
enum
{
    kFTM_QuadDecoderCountingIncreaseFlag = FTM_QDCTRL_QUADIR_MASK, /*!< Counting direction is increasing (FTM counter
                                                                        increment), or the direction is decreasing. */
    kFTM_QuadDecoderCountingOverflowOnTopFlag = FTM_QDCTRL_TOFDIR_MASK, /*!< Indicates if the TOF bit was set on the top
                                                                             or the bottom of counting. */
};
#endif

/*!
 * @brief FTM configuration structure
 *
 * This structure holds the configuration settings for the FTM peripheral. To initialize this
 * structure to reasonable defaults, call the FTM_GetDefaultConfig() function and pass a
 * pointer to the configuration structure instance.
 *
 * The configuration structure can be made constant so as to reside in flash.
 */
typedef struct _ftm_config
{
    ftm_clock_prescale_t prescale;            /*!< FTM clock prescale value */
    ftm_bdm_mode_t bdmMode;                   /*!< FTM behavior in BDM mode */
    uint32_t pwmSyncMode;                     /*!< Synchronization methods to use to update buffered registers; Multiple
                                                   update modes can be used by providing an OR'ed list of options
                                                   available in enumeration ::ftm_pwm_sync_method_t. */
    uint32_t reloadPoints;                    /*!< FTM reload points; When using this, the PWM
                                                   synchronization is not required. Multiple reload points can be used by providing
                                                   an OR'ed list of options available in
                                                   enumeration ::ftm_reload_point_t. */
    ftm_fault_mode_t faultMode;               /*!< FTM fault control mode */
    uint8_t faultFilterValue;                 /*!< Fault input filter value */
    ftm_deadtime_prescale_t deadTimePrescale; /*!< The dead time prescalar value */
    uint32_t deadTimeValue;                   /*!< The dead time value
                                                   deadTimeValue's available range is 0-1023 when register has DTVALEX,
                                                   otherwise its available range is 0-63. */
    uint32_t extTriggers;                     /*!< External triggers to enable. Multiple trigger sources can be
                                                   enabled by providing an OR'ed list of options available in
                                                   enumeration ::ftm_external_trigger_t. */
    uint8_t chnlInitState;  /*!< Defines the initialization value of the channels in OUTINT register */
    uint8_t chnlPolarity;   /*!< Defines the output polarity of the channels in POL register */
    bool useGlobalTimeBase; /*!< True: Use of an external global time base is enabled;
                                 False: disabled */
} ftm_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the FTM clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application which is using the FTM driver.
 *       If the FTM instance has only TPM features, please use the TPM driver.
 *
 * @param base   FTM peripheral base address
 * @param config Pointer to the user configuration structure.
 *
 * @return kStatus_Success indicates success; Else indicates failure.
 */
status_t FTM_Init(FTM_Type *base, const ftm_config_t *config);

/*!
 * @brief Gates the FTM clock.
 *
 * @param base FTM peripheral base address
 */
void FTM_Deinit(FTM_Type *base);

/*!
 * @brief  Fills in the FTM configuration structure with the default settings.
 *
 * The default values are:
 * @code
 *   config->prescale = kFTM_Prescale_Divide_1;
 *   config->bdmMode = kFTM_BdmMode_0;
 *   config->pwmSyncMode = kFTM_SoftwareTrigger;
 *   config->reloadPoints = 0;
 *   config->faultMode = kFTM_Fault_Disable;
 *   config->faultFilterValue = 0;
 *   config->deadTimePrescale = kFTM_Deadtime_Prescale_1;
 *   config->deadTimeValue =  0;
 *   config->extTriggers = 0;
 *   config->chnlInitState = 0;
 *   config->chnlPolarity = 0;
 *   config->useGlobalTimeBase = false;
 * @endcode
 * @param config Pointer to the user configuration structure.
 */
void FTM_GetDefaultConfig(ftm_config_t *config);

/*!
 * brief Calculates the counter clock prescaler.
 *
 * This function calculates the values for SC[PS] bit.
 *
 * param base                FTM peripheral base address
 * param counterPeriod_Hz    The desired frequency in Hz which corresponding to the time when the counter reaches the
 *                           mod value
 * param srcClock_Hz         FTM counter clock in Hz
 *
 * return Calculated clock prescaler value, see @ref ftm_clock_prescale_t.
 */
static inline ftm_clock_prescale_t FTM_CalculateCounterClkDiv(FTM_Type *base,
                                                              uint32_t counterPeriod_Hz,
                                                              uint32_t srcClock_Hz)
{
    uint8_t i;
    assert((srcClock_Hz / 2U) > counterPeriod_Hz);
    assert((srcClock_Hz / 128U / 0xFFFFU) <= counterPeriod_Hz);
    for (i = 0U; i < (uint32_t)kFTM_Prescale_Divide_128; i++)
    {
        if ((srcClock_Hz / (1UL << i) / 0xFFFFU) < counterPeriod_Hz)
        {
            break;
        }
    }
    return (ftm_clock_prescale_t)i;
}

/*! @}*/

/*!
 * @name Channel mode operations
 * @{
 */

/*!
 * @brief Configures the PWM signal parameters.
 *
 * Call this function to configure the PWM signal period, mode, duty cycle, and edge. Use this
 * function to configure all FTM channels that are used to output a PWM signal.
 *
 * @param base        FTM peripheral base address
 * @param chnlParams  Array of PWM channel parameters to configure the channel(s)
 * @param numOfChnls  Number of channels to configure; This should be the size of the array passed in
 * @param mode        PWM operation mode, options available in enumeration ::ftm_pwm_mode_t
 * @param pwmFreq_Hz  PWM signal frequency in Hz
 * @param srcClock_Hz FTM counter clock in Hz
 *
 * @return kStatus_Success if the PWM setup was successful
 *         kStatus_Error on failure
 */
status_t FTM_SetupPwm(FTM_Type *base,
                      const ftm_chnl_pwm_signal_param_t *chnlParams,
                      uint8_t numOfChnls,
                      ftm_pwm_mode_t mode,
                      uint32_t pwmFreq_Hz,
                      uint32_t srcClock_Hz);

/*!
 * @brief Updates the duty cycle of an active PWM signal.
 *
 * @param base              FTM peripheral base address
 * @param chnlNumber        The channel/channel pair number. In combined mode, this represents
 *                          the channel pair number
 * @param currentPwmMode    The current PWM mode set during PWM setup
 * @param dutyCyclePercent  New PWM pulse width; The value should be between 0 to 100
 *                          0=inactive signal(0% duty cycle)...
 *                          100=active signal (100% duty cycle)
 * @return kStatus_Success if the PWM update was successful
 *         kStatus_Error on failure
 */
status_t FTM_UpdatePwmDutycycle(FTM_Type *base,
                                ftm_chnl_t chnlNumber,
                                ftm_pwm_mode_t currentPwmMode,
                                uint8_t dutyCyclePercent);

/*!
 * @brief Updates the edge level selection for a channel.
 *
 * @param base       FTM peripheral base address
 * @param chnlNumber The channel number
 * @param level      The level to be set to the ELSnB:ELSnA field; Valid values are 00, 01, 10, 11.
 *                   See the Kinetis SoC reference manual for details about this field.
 */
void FTM_UpdateChnlEdgeLevelSelect(FTM_Type *base, ftm_chnl_t chnlNumber, uint8_t level);

/*!
 * @brief Configures the PWM mode parameters.
 *
 * Call this function to configure the PWM signal mode, duty cycle in ticks, and edge. Use this
 * function to configure all FTM channels that are used to output a PWM signal.
 * Please note that: This API is similar with FTM_SetupPwm() API, but will not set the timer period,
 *                   and this API will set channel match value in timer ticks, not period percent.
 *
 * @param base        FTM peripheral base address
 * @param chnlParams  Array of PWM channel parameters to configure the channel(s)
 * @param numOfChnls  Number of channels to configure; This should be the size of the array passed in
 * @param mode        PWM operation mode, options available in enumeration ::ftm_pwm_mode_t
 *
 * @return kStatus_Success if the PWM setup was successful
 *         kStatus_Error on failure
 */
status_t FTM_SetupPwmMode(FTM_Type *base,
                          const ftm_chnl_pwm_config_param_t *chnlParams,
                          uint8_t numOfChnls,
                          ftm_pwm_mode_t mode);

/*!
 * @brief Enables capturing an input signal on the channel using the function parameters.
 *
 * When the edge specified in the captureMode argument occurs on the channel, the FTM counter is
 * captured into the CnV register. The user has to read the CnV register separately to get this
 * value. The filter function is disabled if the filterVal argument passed in is 0. The filter
 * function is available only for channels 0, 1, 2, 3.
 *
 * @param base        FTM peripheral base address
 * @param chnlNumber  The channel number
 * @param captureMode Specifies which edge to capture
 * @param filterValue Filter value, specify 0 to disable filter. Available only for channels 0-3.
 */
void FTM_SetupInputCapture(FTM_Type *base,
                           ftm_chnl_t chnlNumber,
                           ftm_input_capture_edge_t captureMode,
                           uint32_t filterValue);

/*!
 * @brief Configures the FTM to generate timed pulses.
 *
 * When the FTM counter matches the value of compareVal argument (this is written into CnV reg),
 * the channel output is changed based on what is specified in the compareMode argument.
 *
 * @param base         FTM peripheral base address
 * @param chnlNumber   The channel number
 * @param compareMode  Action to take on the channel output when the compare condition is met
 * @param compareValue Value to be programmed in the CnV register.
 */
void FTM_SetupOutputCompare(FTM_Type *base,
                            ftm_chnl_t chnlNumber,
                            ftm_output_compare_mode_t compareMode,
                            uint32_t compareValue);

/*!
 * @brief Configures the dual edge capture mode of the FTM.
 *
 * This function sets up the dual edge capture mode on a channel pair. The capture edge for the
 * channel pair and the capture mode (one-shot or continuous) is specified in the parameter
 * argument. The filter function is disabled if the filterVal argument passed is zero. The filter
 * function is available only on channels 0 and 2. The user has to read the channel CnV registers
 * separately to get the capture values.
 *
 * @param base           FTM peripheral base address
 * @param chnlPairNumber The FTM channel pair number; options are 0, 1, 2, 3
 * @param edgeParam      Sets up the dual edge capture function
 * @param filterValue    Filter value, specify 0 to disable filter. Available only for channel pair 0 and 1.
 */
void FTM_SetupDualEdgeCapture(FTM_Type *base,
                              ftm_chnl_t chnlPairNumber,
                              const ftm_dual_edge_capture_param_t *edgeParam,
                              uint32_t filterValue);

/*! @}*/

/*!
 * @brief Sets up the working of the FTM fault inputs protection.
 *
 * FTM can have up to 4 fault inputs. This function sets up fault parameters, fault level, and input filter.
 *
 * @param base        FTM peripheral base address
 * @param faultNumber FTM fault to configure.
 * @param faultParams Parameters passed in to set up the fault
 */
void FTM_SetupFaultInput(FTM_Type *base, ftm_fault_input_t faultNumber, const ftm_fault_param_t *faultParams);

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected FTM interrupts.
 *
 * @param base FTM peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::ftm_interrupt_enable_t
 */
void FTM_EnableInterrupts(FTM_Type *base, uint32_t mask);

/*!
 * @brief Disables the selected FTM interrupts.
 *
 * @param base FTM peripheral base address
 * @param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::ftm_interrupt_enable_t
 */
void FTM_DisableInterrupts(FTM_Type *base, uint32_t mask);

/*!
 * @brief Gets the enabled FTM interrupts.
 *
 * @param base FTM peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::ftm_interrupt_enable_t
 */
uint32_t FTM_GetEnabledInterrupts(FTM_Type *base);

/*! @}*/

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets the FTM status flags.
 *
 * @param base FTM peripheral base address
 *
 * @return The status flags. This is the logical OR of members of the
 *         enumeration ::ftm_status_flags_t
 */
uint32_t FTM_GetStatusFlags(FTM_Type *base);

/*!
 * @brief Clears the FTM status flags.
 *
 * @param base FTM peripheral base address
 * @param mask The status flags to clear. This is a logical OR of members of the
 *             enumeration ::ftm_status_flags_t
 */
void FTM_ClearStatusFlags(FTM_Type *base, uint32_t mask);

/*! @}*/

/*!
 * @name Read and write the timer period
 * @{
 */

/*!
 * @brief Sets the timer period in units of ticks.
 *
 * Timers counts from 0 until it equals the count value set here. The count value is written to
 * the MOD register.
 *
 * @note
 * 1. This API allows the user to use the FTM module as a timer. Do not mix usage
 *    of this API with FTM's PWM setup API's.
 * 2. Call the utility macros provided in the fsl_common.h to convert usec or msec to ticks.
 *
 * @param base FTM peripheral base address
 * @param ticks A timer period in units of ticks, which should be equal or greater than 1.
 */
static inline void FTM_SetTimerPeriod(FTM_Type *base, uint32_t ticks)
{
    base->CNTIN = 0x0U;
    base->MOD   = ticks;
}

/*!
 * @brief Reads the current timer counting value.
 *
 * This function returns the real-time timer counting value in a range from 0 to a
 * timer period.
 *
 * @note Call the utility macros provided in the fsl_common.h to convert ticks to usec or msec.
 *
 * @param base FTM peripheral base address
 *
 * @return The current counter value in ticks
 */
static inline uint32_t FTM_GetCurrentTimerCount(FTM_Type *base)
{
    return (uint32_t)((base->CNT & FTM_CNT_COUNT_MASK) >> FTM_CNT_COUNT_SHIFT);
}

/*!
 * @brief Reads the captured value.
 *
 * This function returns the captured value of a FTM channel configured in input capture or dual edge capture mode.
 *
 * @note Call the utility macros provided in the fsl_common.h to convert ticks to usec or msec.
 *
 * @param base FTM peripheral base address
 * @param chnlNumber Channel to be read
 *
 * @return The captured FTM counter value of the input modes.
 */
static inline uint32_t FTM_GetInputCaptureValue(FTM_Type *base, ftm_chnl_t chnlNumber)
{
    return (base->CONTROLS[chnlNumber].CnV & FTM_CnV_VAL_MASK);
}

/*! @}*/
/*!
 * @name Timer Start and Stop
 * @{
 */

/*!
 * @brief Starts the FTM counter.
 *
 * @param base        FTM peripheral base address
 * @param clockSource FTM clock source; After the clock source is set, the counter starts running.
 */
static inline void FTM_StartTimer(FTM_Type *base, ftm_clock_source_t clockSource)
{
    uint32_t reg = base->SC;

    reg &= ~(FTM_SC_CLKS_MASK);
    reg |= FTM_SC_CLKS(clockSource);
    base->SC = reg;
}

/*!
 * @brief Stops the FTM counter.
 *
 * @param base FTM peripheral base address
 */
static inline void FTM_StopTimer(FTM_Type *base)
{
    /* Set clock source to none to disable counter */
    base->SC &= ~(FTM_SC_CLKS_MASK);
}

/*! @}*/

/*!
 * @name Software output control
 * @{
 */

/*!
 * @brief Enables or disables the channel software output control.
 *
 * @param base       FTM peripheral base address
 * @param chnlNumber Channel to be enabled or disabled
 * @param value      true: channel output is affected by software output control
                     false: channel output is unaffected by software output control
 */
static inline void FTM_SetSoftwareCtrlEnable(FTM_Type *base, ftm_chnl_t chnlNumber, bool value)
{
    if (value)
    {
        base->SWOCTRL |= (1UL << (uint32_t)chnlNumber);
    }
    else
    {
        base->SWOCTRL &= ~(1UL << (uint32_t)chnlNumber);
    }
}

/*!
 * @brief Sets the channel software output control value.
 *
 * @param base       FTM peripheral base address.
 * @param chnlNumber Channel to be configured
 * @param value      true to set 1, false to set 0
 */
static inline void FTM_SetSoftwareCtrlVal(FTM_Type *base, ftm_chnl_t chnlNumber, bool value)
{
    if (value)
    {
        base->SWOCTRL |= (1UL << ((uint32_t)chnlNumber + FTM_SWOCTRL_CH0OCV_SHIFT));
    }
    else
    {
        base->SWOCTRL &= ~(1UL << ((uint32_t)chnlNumber + FTM_SWOCTRL_CH0OCV_SHIFT));
    }
}

/*! @}*/

/*!
 * @brief Enables or disables the FTM global time base signal generation to other FTMs.
 *
 * @param base   FTM peripheral base address
 * @param enable true to enable, false to disable
 */
static inline void FTM_SetGlobalTimeBaseOutputEnable(FTM_Type *base, bool enable)
{
    if (enable)
    {
        base->CONF |= FTM_CONF_GTBEOUT_MASK;
    }
    else
    {
        base->CONF &= ~FTM_CONF_GTBEOUT_MASK;
    }
}

/*!
 * @brief Sets the FTM peripheral timer channel output mask.
 *
 * @param base       FTM peripheral base address
 * @param chnlNumber Channel to be configured
 * @param mask       true: masked, channel is forced to its inactive state; false: unmasked
 */
static inline void FTM_SetOutputMask(FTM_Type *base, ftm_chnl_t chnlNumber, bool mask)
{
    if (mask)
    {
        base->OUTMASK |= (1UL << (uint32_t)chnlNumber);
    }
    else
    {
        base->OUTMASK &= ~(1UL << (uint32_t)chnlNumber);
    }
}

#if defined(FSL_FEATURE_FTM_HAS_ENABLE_PWM_OUTPUT) && (FSL_FEATURE_FTM_HAS_ENABLE_PWM_OUTPUT)
/*!
 * @brief Allows users to enable an output on an FTM channel.
 *
 * To enable the PWM channel output call this function with val=true. For input mode,
 * call this function with val=false.
 *
 * @param base       FTM peripheral base address
 * @param chnlNumber Channel to be configured
 * @param value      true: enable output; false: output is disabled, used in input mode
 */
static inline void FTM_SetPwmOutputEnable(FTM_Type *base, ftm_chnl_t chnlNumber, bool value)
{
    if (value)
    {
        base->SC |= (1UL << ((uint32_t)chnlNumber + FTM_SC_PWMEN0_SHIFT));
    }
    else
    {
        base->SC &= ~(1UL << ((uint32_t)chnlNumber + FTM_SC_PWMEN0_SHIFT));
    }
}
#endif

/*!
 * @name Channel pair operations
 * @{
 */

/*!
 * @brief This function enables/disables the fault control in a channel pair.
 *
 * @param base           FTM peripheral base address
 * @param chnlPairNumber The FTM channel pair number; options are 0, 1, 2, 3
 * @param value          true: Enable fault control for this channel pair; false: No fault control
 */
static inline void FTM_SetFaultControlEnable(FTM_Type *base, ftm_chnl_t chnlPairNumber, bool value)
{
    /* Fault input is not supported if the instance has only basic feature.*/
#if (defined(FSL_FEATURE_FTM_HAS_BASIC_FEATURE_ONLY_INSTANCE) && FSL_FEATURE_FTM_HAS_BASIC_FEATURE_ONLY_INSTANCE)
    assert(0 == FSL_FEATURE_FTM_IS_BASIC_FEATURE_ONLY_INSTANCEn(base));
#endif
    if (value)
    {
        base->COMBINE |=
            (1UL << (FTM_COMBINE_FAULTEN0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * (uint32_t)chnlPairNumber)));
    }
    else
    {
        base->COMBINE &=
            ~(1UL << (FTM_COMBINE_FAULTEN0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * (uint32_t)chnlPairNumber)));
    }
}

/*!
 * @brief This function enables/disables the dead time insertion in a channel pair.
 *
 * @param base           FTM peripheral base address
 * @param chnlPairNumber The FTM channel pair number; options are 0, 1, 2, 3
 * @param value          true: Insert dead time in this channel pair; false: No dead time inserted
 */
static inline void FTM_SetDeadTimeEnable(FTM_Type *base, ftm_chnl_t chnlPairNumber, bool value)
{
    if (value)
    {
        base->COMBINE |= (1UL << (FTM_COMBINE_DTEN0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * (uint32_t)chnlPairNumber)));
    }
    else
    {
        base->COMBINE &= ~(1UL << (FTM_COMBINE_DTEN0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * (uint32_t)chnlPairNumber)));
    }
}

/*!
 * @brief This function enables/disables complementary mode in a channel pair.
 *
 * @param base           FTM peripheral base address
 * @param chnlPairNumber The FTM channel pair number; options are 0, 1, 2, 3
 * @param value          true: enable complementary mode; false: disable complementary mode
 */
static inline void FTM_SetComplementaryEnable(FTM_Type *base, ftm_chnl_t chnlPairNumber, bool value)
{
    if (value)
    {
        base->COMBINE |= (1UL << (FTM_COMBINE_COMP0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * (uint32_t)chnlPairNumber)));
    }
    else
    {
        base->COMBINE &= ~(1UL << (FTM_COMBINE_COMP0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * (uint32_t)chnlPairNumber)));
    }
}

/*!
 * @brief This function enables/disables inverting control in a channel pair.
 *
 * @param base            FTM peripheral base address
 * @param chnlPairNumber  The FTM channel pair number; options are 0, 1, 2, 3
 * @param value           true: enable inverting; false: disable inverting
 */
static inline void FTM_SetInvertEnable(FTM_Type *base, ftm_chnl_t chnlPairNumber, bool value)
{
    if (value)
    {
        base->INVCTRL |= (1UL << (uint32_t)chnlPairNumber);
    }
    else
    {
        base->INVCTRL &= ~(1UL << (uint32_t)chnlPairNumber);
    }
}

/*! @}*/

/*!
 * @name Quad Decoder
 * @{
 */

/*!
 * @brief Configures the parameters and activates the quadrature decoder mode.
 *
 * @param base         FTM peripheral base address
 * @param phaseAParams Phase A configuration parameters
 * @param phaseBParams Phase B configuration parameters
 * @param quadMode     Selects encoding mode used in quadrature decoder mode
 */
void FTM_SetupQuadDecode(FTM_Type *base,
                         const ftm_phase_params_t *phaseAParams,
                         const ftm_phase_params_t *phaseBParams,
                         ftm_quad_decode_mode_t quadMode);

#if !(defined(FSL_FEATURE_FTM_HAS_NO_QDCTRL) && FSL_FEATURE_FTM_HAS_NO_QDCTRL)
/*!
 * @brief Gets the FTM Quad Decoder flags.
 *
 * @param base FTM peripheral base address.
 * @return Flag mask of FTM Quad Decoder, see _ftm_quad_decoder_flags.
 */
static inline uint32_t FTM_GetQuadDecoderFlags(FTM_Type *base)
{
    return base->QDCTRL & (FTM_QDCTRL_QUADIR_MASK | FTM_QDCTRL_TOFDIR_MASK);
}
#endif

/*!
 * @brief Sets the modulo values for Quad Decoder.
 *
 * The modulo values configure the minimum and maximum values that the Quad decoder counter can reach. After the
 * counter goes over, the counter value goes to the other side and decrease/increase again.
 *
 * @param base FTM peripheral base address.
 * @param startValue The low limit value for Quad Decoder counter.
 * @param overValue The high limit value for Quad Decoder counter.
 */
static inline void FTM_SetQuadDecoderModuloValue(FTM_Type *base, uint32_t startValue, uint32_t overValue)
{
    base->CNTIN = startValue;
    base->MOD   = overValue;
}

/*!
 * @brief Gets the current Quad Decoder counter value.
 *
 * @param base FTM peripheral base address.
 * @return Current quad Decoder counter value.
 */
static inline uint32_t FTM_GetQuadDecoderCounterValue(FTM_Type *base)
{
    return base->CNT;
}

/*!
 * @brief Clears the current Quad Decoder counter value.
 *
 * The counter is set as the initial value.
 *
 * @param base FTM peripheral base address.
 */
static inline void FTM_ClearQuadDecoderCounterValue(FTM_Type *base)
{
    base->CNT = base->CNTIN;
}

/*! @}*/

/*!
 * @brief Enables or disables the FTM software trigger for PWM synchronization.
 *
 * @param base   FTM peripheral base address
 * @param enable true: software trigger is selected, false: software trigger is not selected
 */
static inline void FTM_SetSoftwareTrigger(FTM_Type *base, bool enable)
{
    if (enable)
    {
        base->SYNC |= FTM_SYNC_SWSYNC_MASK;
    }
    else
    {
        base->SYNC &= ~FTM_SYNC_SWSYNC_MASK;
    }
}

/*!
 * @brief Enables or disables the FTM write protection.
 *
 * @param base   FTM peripheral base address
 * @param enable true: Write-protection is enabled, false: Write-protection is disabled
 */
static inline void FTM_SetWriteProtection(FTM_Type *base, bool enable)
{
    /* Configure write protection */
    if (enable)
    {
        base->FMS |= FTM_FMS_WPEN_MASK;
    }
    else
    {
        base->MODE |= FTM_MODE_WPDIS_MASK;
    }
}

#if defined(FSL_FEATURE_FTM_HAS_DMA_SUPPORT) && FSL_FEATURE_FTM_HAS_DMA_SUPPORT
/*!
 * @brief Enable DMA transfer or not.
 *
 * Note: CHnIE bit needs to be set when calling this API. The channel DMA transfer request
 * is generated and the channel interrupt is not generated if (CHnF = 1) when DMA and CHnIE
 * bits are set.
 *
 * @param base   FTM peripheral base address.
 * @param chnlNumber Channel to be configured
 * @param enable true to enable, false to disable
 */
static inline void FTM_EnableDmaTransfer(FTM_Type *base, ftm_chnl_t chnlNumber, bool enable)
{
    if (enable)
    {
        /* Enable DMA transfer */
        base->CONTROLS[chnlNumber].CnSC |= FTM_CnSC_DMA_MASK;
    }
    else
    {
        /* Disable DMA transfer */
        base->CONTROLS[chnlNumber].CnSC &= ~FTM_CnSC_DMA_MASK;
    }
}
#endif /* FSL_FEATURE_FTM_HAS_DMA_SUPPORT */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_FTM_H_*/
