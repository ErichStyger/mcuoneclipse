/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __FSL_CAPT_H__
#define __FSL_CAPT_H__

#include "fsl_common.h"

/*! @addtogroup capt */
/*! @{*/

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CAPT driver version. */
#define FSL_CAPT_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

#define CAPT_GET_XMAX_NUMBER(mask) (((CAPT_STATUS_XMAX_MASK & (mask)) >> CAPT_STATUS_XMAX_SHIFT) + 1)

/*!
 * @brief The enumeration for X pins.
 */
enum _capt_xpins
{
    kCAPT_X0Pin  = 1U << 0U,  /*!< CAPT_X0 pin. */
    kCAPT_X1Pin  = 1U << 1U,  /*!< CAPT_X1 pin. */
    kCAPT_X2Pin  = 1U << 2U,  /*!< CAPT_X2 pin. */
    kCAPT_X3Pin  = 1U << 3U,  /*!< CAPT_X3 pin. */
    kCAPT_X4Pin  = 1U << 4U,  /*!< CAPT_X4 pin. */
    kCAPT_X5Pin  = 1U << 5U,  /*!< CAPT_X5 pin. */
    kCAPT_X6Pin  = 1U << 6U,  /*!< CAPT_X6 pin. */
    kCAPT_X7Pin  = 1U << 7U,  /*!< CAPT_X7 pin. */
    kCAPT_X8Pin  = 1U << 8U,  /*!< CAPT_X8 pin. */
    kCAPT_X9Pin  = 1U << 9U,  /*!< CAPT_X9 pin. */
    kCAPT_X10Pin = 1U << 10U, /*!< CAPT_X10 pin. */
    kCAPT_X11Pin = 1U << 11U, /*!< CAPT_X11 pin. */
    kCAPT_X12Pin = 1U << 12U, /*!< CAPT_X12 pin. */
    kCAPT_X13Pin = 1U << 13U, /*!< CAPT_X13 pin. */
    kCAPT_X14Pin = 1U << 14U, /*!< CAPT_X14 pin. */
    kCAPT_X15Pin = 1U << 15U, /*!< CAPT_X15 pin. */
};

/*!
 * @brief The enumeration for enabling/disabling interrupts.
 */
enum _capt_interrupt_enable
{
    kCAPT_InterruptOfYesTouchEnable =
        CAPT_INTENSET_YESTOUCH_MASK, /*!< Generate interrupt when a touch has been detected. */
    kCAPT_InterruptOfNoTouchEnable =
        CAPT_INTENSET_NOTOUCH_MASK, /*!< Generate interrupt when a no-touch has been detected. */
    kCAPT_InterruptOfPollDoneEnable = CAPT_INTENSET_POLLDONE_MASK, /*!< Genarate interrupt at the end of a polling
                                                                      round, or when a POLLNOW completes. */
    kCAPT_InterruptOfTimeOutEnable = CAPT_INTENSET_TIMEOUT_MASK,   /*!< Generate interrupt when the count reaches the
                                                                      time-out   count value before a trigger occurs. */
    kCAPT_InterruptOfOverRunEnable = CAPT_INTENSET_OVERUN_MASK, /*!< Generate interrupt when the Touch Data register has
                                                                   been up-dated before software has read the previous
                                                                   data, and the touch has been detected. */
};

/*!
 * @brief The enumeration for interrupt status flags.
 */
enum _capt_interrupt_status_flags
{
    kCAPT_InterruptOfYesTouchStatusFlag = CAPT_INTSTAT_YESTOUCH_MASK, /*!< YESTOUCH interrupt status flag. */
    kCAPT_InterruptOfNoTouchStatusFlag  = CAPT_INTSTAT_NOTOUCH_MASK,  /*!< NOTOUCH interrupt status flag. */
    kCAPT_InterruptOfPollDoneStatusFlag = CAPT_INTSTAT_POLLDONE_MASK, /*!< POLLDONE interrupt status flag. */
    kCAPT_InterruptOfTimeOutStatusFlag  = CAPT_INTSTAT_TIMEOUT_MASK,  /*!< TIMEOUT interrupt status flag. */
    kCAPT_InterruptOfOverRunStatusFlag  = CAPT_INTSTAT_OVERUN_MASK,   /*!< OVERRUN interrupt status flag. */
};

/*!
 * @brief The enumeration for CAPT status flags.
 */
enum _capt_status_flags
{
    kCAPT_BusyStatusFlag = CAPT_STATUS_BUSY_MASK, /*!< Set while a poll is currently in progress, otherwise cleared. */
    kCAPT_XMAXStatusFlag = CAPT_STATUS_XMAX_MASK, /*!< The maximum number of X pins available for a given device is
                                                       equal to XMAX+1. */
};

/*!
 * @brief The enumeration for CAPT trigger mode.
 */
typedef enum _capt_trigger_mode
{
    kCAPT_YHPortTriggerMode     = 0U, /*!< YH port pin trigger mode. */
    kCAPT_ComparatorTriggerMode = 1U, /*!< Analog comparator trigger mode. */
} capt_trigger_mode_t;

/*!
 * @brief The enumeration for the inactive X pins mode.
 */
typedef enum _capt_inactive_xpins_mode
{
    kCAPT_InactiveXpinsHighZMode =
        0U, /*!<  Xpins enabled in the XPINSEL field are controlled to HIGH-Z mode when not active. */
    kCAPT_InactiveXpinsDrivenLowMode =
        1U, /*!<  Xpins enabled in the XPINSEL field are controlled to be driven low mode when not active. */
} capt_inactive_xpins_mode_t;

/*!
 * @brief The enumeration for the delay of measuring voltage state.
 */
typedef enum _capt_measurement_delay
{
    kCAPT_MeasureDelayNoWait     = 0U, /*!< Don’t wait. */
    kCAPT_MeasureDelayWait3FCLKs = 1U, /*!< Wait 3 divided FCLKs. */
    kCAPT_MeasureDelayWait5FCLKs = 2U, /*!< Wait 5 divided FCLKs. */
    kCAPT_MeasureDelayWait9FCLKs = 3U, /*!< Wait 9 divided FCLKs. */
} capt_measurement_delay_t;

/*!
 * @brief The enumeration for the delay of reseting or draining Cap.
 */
typedef enum _capt_reset_delay
{
    kCAPT_ResetDelayNoWait     = 0U, /*!< Don’t wait. */
    kCAPT_ResetDelayWait3FCLKs = 1U, /*!< Wait 3 divided FCLKs. */
    kCAPT_ResetDelayWait5FCLKs = 2U, /*!< Wait 5 divided FCLKs. */
    kCAPT_ResetDelayWait9FCLKs = 3U, /*!< Wait 9 divided FCLKs. */
} capt_reset_delay_t;

/*!
 * @brief The enumeration of CAPT polling mode.
 */
typedef enum _capt_polling_mode
{
    kCAPT_PollInactiveMode =
        0U, /*!< No measurements are taken, no polls are performed. The module remains in the Reset/ Draining Cap. */
    kCAPT_PollNowMode = 1U, /*!< Immediately launches (ignoring Poll Delay) a one-time-only, simultaneous poll of all X
                               pins that are enabled in the XPINSEL field of the Control register, then stops, returning
                               to Reset/Draining Cap. */
    kCAPT_PollContinuousMode =
        2U, /*!< Polling rounds are continuously performed, by walking through the enabled X pins. */
} capt_polling_mode_t;

/*!
 * @brief The enumeration of CAPT DMA trigger mode.
 */
typedef enum _capt_dma_mode
{
    kCAPT_DMATriggerOnTouchMode = 1U, /*!< Trigger on touch. */
    kCAPT_DMATriggerOnBothMode  = 2U, /*!< Trigger on both touch and no-touch. */
    kCAPT_DMATriggerOnAllMode   = 3U, /*!< Trigger on all touch, no-touch and time-out.  */
} capt_dma_mode_t;

/*!
 * @brief The structure for CAPT basic configuration.
 */
typedef struct _capt_config
{
    bool enableWaitMode; /*!< If enable the wait mode, when the touch event occurs, the module will wait until the TOUCH
                            register is read
                              before starting the next measurement. Other-wise, measurements continue. */
    bool enableTouchLower; /*!< enableTouchLower = true: Trigger at count < TCNT is a touch. Trigger at count > TCNT is
                              a no-touch.
                                enableTouchLower = false: Trigger at count > TCNT is a touch. Trigger at count < TCNT is
                              a no-touch.
                                Notice: TCNT will be set by "CAPT_DoCalibration" API. */
    uint8_t clockDivider;  /*!< Function clock divider. The function clock is divided by clockDivider+1 to produce the
                              divided FCLK for the module.
                                The available range is 0-15. */
    uint8_t timeOutCount; /*!< Sets the count value at which a time-out event occurs if a measurement has not triggered.
                               The time-out count value is calculated as 2^timeOutCount. The available range is 0-12. */
    uint8_t pollCount; /*!< Sets the time delay between polling rounds (successive sets of X measurements). After each
                          polling round completes,
                            the module will wait 4096 x PollCount divided FCLKs before starting the next polling round.
                          The available range is 0-255. */
    uint16_t enableXpins; /*!< Selects which of the available X pins are enabled. Please refer to '_capt_xpins'.
                               For example, if want to enable X0, X2 and X3 pins, you can set "enableXpins = kCAPT_X0Pin
                             | kCAPT_X2Pin
                               | kCAPT_X3Pin". */
    capt_trigger_mode_t
        triggerMode; /*!< Select the menthods of measuring the voltage across the measurement capacitor. */
    capt_inactive_xpins_mode_t
        XpinsMode; /*!< Determines how X pins enabled in the XPINSEL field are controlled when not active. */
    capt_measurement_delay_t mDelay; /*!< Set the time delay after entering step 3 (measure voltage state), before
                               sampling the YH port pin or analog comarator output. */
    capt_reset_delay_t rDelay; /*!< Set the number of divided FCLKs the module will remain in Reset or Draining Cap. */
} capt_config_t;

/*!
 * @brief The structure for storing touch data.
 */
typedef struct _capt_touch_data
{
    bool yesTimeOut;    /*!< 'true': if the measurement resulted in a time-out event, 'false': otherwise. */
    bool yesTouch;      /*!< 'true': if the trigger is due to a touch even, 'false': if the trigger is due to a no-touch
                           event. */
    uint8_t XpinsIndex; /*!< Contains the index of the X pin for the current measurement, or lowest X for a
                             multiple-pin poll now measurement. */
    uint8_t sequenceNumber; /*!< Contains the 4-bit(0-7) sequence number, which increments at the end of each polling
                               round. */
    uint16_t count;         /*!< Contains the count value reached at trigger or time-out. */
} capt_touch_data_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initialize the CAPT module.
 *
 * @param base CAPT peripheral base address.
 * @param config Pointer to "capt_config_t" structure.
 */
void CAPT_Init(CAPT_Type *base, const capt_config_t *config);

/*!
 * @brief De-initialize the CAPT module.
 *
 * @param base CAPT peripheral base address.
 */
void CAPT_Deinit(CAPT_Type *base);

/*!
 * @brief Gets an available pre-defined settings for the CAPT's configuration.
 *
 * This function initializes the converter configuration structure with available settings. The default values are:
 * @code
 *   config->enableWaitMode = false;
 *   config->enableTouchLower = true;
 *   config->clockDivider = 15U;
 *   config->timeOutCount = 12U;
 *   config->pollCount = 0U;
 *   config->enableXpins = 0U;
 *   config->triggerMode = kCAPT_YHPortTriggerMode;
 *   config->XpinsMode = kCAPT_InactiveXpinsDrivenLowMode;
 *   config->mDelay = kCAPT_MeasureDelayNoWait;
 *   config->rDelay = kCAPT_ResetDelayWait9FCLKs;
 * @endcode
 * @param config Pointer to the configuration structure.
 */
void CAPT_GetDefaultConfig(capt_config_t *config);

/*!
 * @brief Set Sets the count threshold in divided FCLKs between touch and no-touch.
 *
 * @param base CAPT peripheral base address.
 * @param count The count threshold.
 */
static inline void CAPT_SetThreshold(CAPT_Type *base, uint32_t count)
{
    base->POLL_TCNT = ((base->POLL_TCNT & ~CAPT_POLL_TCNT_TCNT_MASK) | CAPT_POLL_TCNT_TCNT(count));
}

/*!
 * @brief Set the CAPT polling mode.
 *
 * @param base CAPT peripheral base address.
 * @param mode The selection of polling mode.
 */
void CAPT_SetPollMode(CAPT_Type *base, capt_polling_mode_t mode);

#if defined(FSL_FEATURE_CAPT_HAS_CTRL_DMA) && FSL_FEATURE_CAPT_HAS_CTRL_DMA
/*!
 * @brief Enable DMA feature.
 *
 * @param base CAPT peripheral base address.
 * @param mode Select how DMA triggers are generated.
 */
void CAPT_EnableDMA(CAPT_Type *base, capt_dma_mode_t mode);

/*!
 * @brief Disable DMA feature.
 *
 * @param base CAPT peripheral base address.
 */
void CAPT_DisableDMA(CAPT_Type *base);
#endif /*FSL_FEATURE_CAPT_HAS_CTRL_DMA*/

/*!
 * @brief Enable interrupt features.
 *
 * @param base CAPT peripheral base address.
 * @param mask The mask of enabling interrupt features. Please refer to "_capt_interrupt_enable".
 */
static inline void CAPT_EnableInterrupts(CAPT_Type *base, uint32_t mask)
{
    base->INTENSET = mask;
}

/*!
 * @brief Disable interrupt features.
 *
 * @param base CAPT peripheral base address.
 * @param mask The mask of disabling interrupt features. Please refer to "_capt_interrupt_enable".
 */
static inline void CAPT_DisableInterrupts(CAPT_Type *base, uint32_t mask)
{
    base->INTENCLR = mask;
}

/*!
 * @brief Get CAPT interrupts' status flags.
 *
 * @param base CAPT peripheral base address.
 * @return The mask of interrupts' status flags. please refer to "_capt_interrupt_status_flags".
 */
static inline uint32_t CAPT_GetInterruptStatusFlags(CAPT_Type *base)
{
    return base->INTSTAT;
}

/*!
 * @brief Clear the interrupts' status flags.
 *
 * @param base CAPT peripheral base address.
 * @param mask The mask of clearing the interrupts' status flags, please refer to "_capt_interrupt_status_flags".
 */
static inline void CAPT_ClearInterruptStatusFlags(CAPT_Type *base, uint32_t mask)
{
    base->STATUS = mask;
}

/*!
 * @brief Get CAPT status flags.
 *
 * @param base CAPT peripheral base address.
 * @return The mask of CAPT status flags. Please refer to "_capt_status_flags"
 *         Or use CAPT_GET_XMAX_NUMBER(mask) to get XMAX number.
 */
static inline uint32_t CAPT_GetStatusFlags(CAPT_Type *base)
{
    return base->STATUS;
}

/*!
 * @brief Get CAPT touch data.
 *
 * @param base CAPT peripheral base address.
 * @param data The structure to store touch data.
 *
 * @return If return 'true', which means get valid data.
 *         if return 'false', which means get invalid data.
 */
bool CAPT_GetTouchData(CAPT_Type *base, capt_touch_data_t *data);

/*!
 * @brief Start touch data polling using poll-now method.
 *
 * This function starts new data polling using polling-now method, CAPT stops when
 * the polling is finished, application could check the status or monitor interrupt
 * to know when the progress is finished.
 *
 * Note that this is simultaneous poll of all X pins, all enabled X pins are
 * activated concurrently, rather than walked one-at-a-time
 *
 * @param base CAPT peripheral base address.
 * @param enableXpins The X pins enabled in this polling.
 */
void CAPT_PollNow(CAPT_Type *base, uint16_t enableXpins);

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*@}*/

#endif /* _FSL_CAPT_H_ */
