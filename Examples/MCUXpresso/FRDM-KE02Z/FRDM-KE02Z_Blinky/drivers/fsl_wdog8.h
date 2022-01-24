/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_WDOG8_H_
#define _FSL_WDOG8_H_

#include "fsl_common.h"

/*!
 * @addtogroup wdog8
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*@}*/
/*! @name Driver version */
/*@{*/
/*! @brief WDOG8 driver version 2.0.1. */
#define FSL_WDOG8_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/*! @brief Describes WDOG8 clock source. */
typedef enum _wdog8_clock_source
{
    kWDOG8_ClockSource0 = 0U, /*!< Clock source 0 */
    kWDOG8_ClockSource1 = 1U, /*!< Clock source 1 */
    kWDOG8_ClockSource2 = 2U, /*!< Clock source 2 */
    kWDOG8_ClockSource3 = 3U, /*!< Clock source 3 */
} wdog8_clock_source_t;

/*! @brief Describes the selection of the clock prescaler. */
typedef enum _wdog8_clock_prescaler
{
    kWDOG8_ClockPrescalerDivide1   = 0x0U, /*!< Divided by 1 */
    kWDOG8_ClockPrescalerDivide256 = 0x1U, /*!< Divided by 256 */
} wdog8_clock_prescaler_t;

/*! @brief Defines WDOG8 work mode. */
typedef struct _wdog8_work_mode
{
    bool enableWait;  /*!< Enables or disables WDOG8 in wait mode */
    bool enableStop;  /*!< Enables or disables WDOG8 in stop mode */
    bool enableDebug; /*!< Enables or disables WDOG8 in debug mode */
} wdog8_work_mode_t;

/*! @brief Describes WDOG8 test mode. */
typedef enum _wdog8_test_mode
{
    kWDOG8_TestModeDisabled = 0U, /*!< Test Mode disabled */
    kWDOG8_UserModeEnabled  = 1U, /*!< User Mode enabled */
    kWDOG8_LowByteTest      = 2U, /*!< Test Mode enabled, only low byte is used */
    kWDOG8_HighByteTest     = 3U, /*!< Test Mode enabled, only high byte is used */
} wdog8_test_mode_t;

/*! @brief Describes WDOG8 configuration structure. */
typedef struct _wdog8_config
{
    bool enableWdog8;                  /*!< Enables or disables WDOG8 */
    wdog8_clock_source_t clockSource;  /*!< Clock source select */
    wdog8_clock_prescaler_t prescaler; /*!< Clock prescaler value */
    wdog8_work_mode_t workMode;        /*!< Configures WDOG8 work mode in debug stop and wait mode */
    wdog8_test_mode_t testMode;        /*!< Configures WDOG8 test mode */
    bool enableUpdate;                 /*!< Update write-once register enable */
    bool enableInterrupt;              /*!< Enables or disables WDOG8 interrupt */
    bool enableWindowMode;             /*!< Enables or disables WDOG8 window mode */
    uint16_t windowValue;              /*!< Window value */
    uint16_t timeoutValue;             /*!< Timeout value */
} wdog8_config_t;

/*!
 * @brief WDOG8 interrupt configuration structure.
 *
 * This structure contains the settings for all of the WDOG8 interrupt configurations.
 */
enum _wdog8_interrupt_enable_t
{
    kWDOG8_InterruptEnable = WDOG_CS1_INT_MASK, /*!< Interrupt is generated before forcing a reset */
};

/*!
 * @brief WDOG8 status flags.
 *
 * This structure contains the WDOG8 status flags for use in the WDOG8 functions.
 */
enum _wdog8_status_flags_t
{
    kWDOG8_RunningFlag   = WDOG_CS1_EN_MASK,  /*!< Running flag, set when WDOG8 is enabled */
    kWDOG8_InterruptFlag = WDOG_CS2_FLG_MASK, /*!< Interrupt flag, set when interrupt occurs */
};

/*! @} */

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @addtogroup wdog8
 * @{
 */

/*!
 * @name WDOG8 Initialization and De-initialization
 * @{
 */

/*!
 * @brief Initializes the WDOG8 configuration structure.
 *
 * This function initializes the WDOG8 configuration structure to default values. The default
 * values are:
 * @code
 *   wdog8Config->enableWdog8 = true;
 *   wdog8Config->clockSource = kWDOG8_ClockSource1;
 *   wdog8Config->prescaler = kWDOG8_ClockPrescalerDivide1;
 *   wdog8Config->workMode.enableWait = true;
 *   wdog8Config->workMode.enableStop = false;
 *   wdog8Config->workMode.enableDebug = false;
 *   wdog8Config->testMode = kWDOG8_TestModeDisabled;
 *   wdog8Config->enableUpdate = true;
 *   wdog8Config->enableInterrupt = false;
 *   wdog8Config->enableWindowMode = false;
 *   wdog8Config->windowValue = 0U;
 *   wdog8Config->timeoutValue = 0xFFFFU;
 * @endcode
 *
 * @param config Pointer to the WDOG8 configuration structure.
 * @see wdog8_config_t
 */
void WDOG8_GetDefaultConfig(wdog8_config_t *config);

/*!
 * @brief Initializes the WDOG8 module.
 *
 * This function initializes the WDOG8.
 * To reconfigure the WDOG8 without forcing a reset first, enableUpdate must be set to true
 * in the configuration.
 *
 * Example:
 * @code
 *   wdog8_config_t config;
 *   WDOG8_GetDefaultConfig(&config);
 *   config.timeoutValue = 0x7ffU;
 *   config.enableUpdate = true;
 *   WDOG8_Init(wdog_base,&config);
 * @endcode
 *
 * @param base   WDOG8 peripheral base address.
 * @param config The configuration of the WDOG8.
 */
void WDOG8_Init(WDOG_Type *base, const wdog8_config_t *config);

/*!
 * @brief De-initializes the WDOG8 module.
 *
 * This function shuts down the WDOG8.
 * Ensure that the WDOG_CS1.UPDATE is 1, which means that the register update is enabled.
 *
 * @param base   WDOG8 peripheral base address.
 */
void WDOG8_Deinit(WDOG_Type *base);

/* @} */

/*!
 * @name WDOG8 functional Operation
 * @{
 */

/*!
 * @brief Enables the WDOG8 module.
 *
 * This function writes a value into the WDOG_CS1 register to enable the WDOG8.
 * The WDOG_CS1 register is a write-once register. Ensure that the WCT window is still open and
 * this register has not been written in this WCT while the function is called.
 *
 * @param base WDOG8 peripheral base address.
 */
static inline void WDOG8_Enable(WDOG_Type *base)
{
    base->CS1 |= WDOG_CS1_EN_MASK;
}

/*!
 * @brief Disables the WDOG8 module.
 *
 * This function writes a value into the WDOG_CS1 register to disable the WDOG8.
 * The WDOG_CS1 register is a write-once register. Ensure that the WCT window is still open and
 * this register has not been written in this WCT while the function is called.
 *
 * @param base WDOG8 peripheral base address
 */
static inline void WDOG8_Disable(WDOG_Type *base)
{
    base->CS1 &= (uint8_t)~WDOG_CS1_EN_MASK;
}

/*!
 * @brief Enables the WDOG8 interrupt.
 *
 * This function writes a value into the WDOG_CS1 register to enable the WDOG8 interrupt.
 * The WDOG_CS1 register is a write-once register. Ensure that the WCT window is still open and
 * this register has not been written in this WCT while the function is called.
 *
 * @param base WDOG8 peripheral base address.
 * @param mask The interrupts to enable.
 *        The parameter can be a combination of the following source if defined:
 *        @arg kWDOG8_InterruptEnable
 */
static inline void WDOG8_EnableInterrupts(WDOG_Type *base, uint8_t mask)
{
    base->CS1 |= mask;
}

/*!
 * @brief Disables the WDOG8 interrupt.
 *
 * This function writes a value into the WDOG_CS register to disable the WDOG8 interrupt.
 * The WDOG_CS register is a write-once register. Ensure that the WCT window is still open and
 * this register has not been written in this WCT while the function is called.
 *
 * @param base WDOG8 peripheral base address.
 * @param mask The interrupts to disabled.
 *        The parameter can be a combination of the following source if defined:
 *        @arg kWDOG8_InterruptEnable
 */
static inline void WDOG8_DisableInterrupts(WDOG_Type *base, uint8_t mask)
{
    base->CS1 &= (uint8_t)~mask;
}

/*!
 * @brief Gets the WDOG8 all status flags.
 *
 * This function gets all status flags.
 *
 * Example to get the running flag:
 * @code
 *   uint32_t status;
 *   status = WDOG8_GetStatusFlags(wdog_base) & kWDOG8_RunningFlag;
 * @endcode
 * @param base        WDOG8 peripheral base address
 * @return            State of the status flag: asserted (true) or not-asserted (false). @see _wdog8_status_flags_t
 *                    - true: related status flag has been set.
 *                    - false: related status flag is not set.
 */
static inline uint8_t WDOG8_GetStatusFlags(WDOG_Type *base)
{
    return (base->CS1 & WDOG_CS1_EN_MASK) | (base->CS2 & WDOG_CS2_FLG_MASK);
}

/*!
 * @brief Clears the WDOG8 flag.
 *
 * This function clears the WDOG8 status flag.
 *
 * Example to clear an interrupt flag:
 * @code
 *   WDOG8_ClearStatusFlags(wdog_base,kWDOG8_InterruptFlag);
 * @endcode
 * @param base        WDOG8 peripheral base address.
 * @param mask        The status flags to clear.
 *                    The parameter can be any combination of the following values:
 *                    @arg kWDOG8_InterruptFlag
 */
void WDOG8_ClearStatusFlags(WDOG_Type *base, uint8_t mask);

/*!
 * @brief Sets the WDOG8 timeout value.
 *
 * This function writes a timeout value into the WDOG_TOVALH/L register.
 * The WDOG_TOVALH/L register is a write-once register. Ensure that the WCT window is still open and
 * this register has not been written in this WCT while the function is called.
 *
 * @param base WDOG8 peripheral base address
 * @param timeoutCount WDOG8 timeout value, count of WDOG8 clock ticks.
 */
static inline void WDOG8_SetTimeoutValue(WDOG_Type *base, uint16_t timeoutCount)
{
    base->TOVAL8B.TOVALH = (uint8_t)((timeoutCount >> 8U) & 0xFFU);
    base->TOVAL8B.TOVALL = (uint8_t)((timeoutCount)&0xFFU);
}

/*!
 * @brief Sets the WDOG8 window value.
 *
 * This function writes a window value into the WDOG_WINH/L register.
 * The WDOG_WINH/L register is a write-once register. Ensure that the WCT window is still open and
 * this register has not been written in this WCT while the function is called.
 *
 * @param base WDOG8 peripheral base address.
 * @param windowValue WDOG8 window value.
 */
static inline void WDOG8_SetWindowValue(WDOG_Type *base, uint16_t windowValue)
{
    base->WIN8B.WINH = (uint8_t)((windowValue >> 8U) & 0xFFU);
    base->WIN8B.WINL = (uint8_t)((windowValue)&0xFFU);
}

/*!
 * @brief Unlocks the WDOG8 register written.
 *
 * This function unlocks the WDOG8 register written.
 *
 * Before starting the unlock sequence and following the configuration, disable the global interrupts.
 * Otherwise, an interrupt could effectively invalidate the unlock sequence and the WCT may expire.
 * After the configuration finishes, re-enable the global interrupts.
 *
 * @param base WDOG8 peripheral base address
 */
static inline void WDOG8_Unlock(WDOG_Type *base)
{
    base->CNT = WDOG_UPDATE_KEY1;
    base->CNT = WDOG_UPDATE_KEY2;
}

/*!
 * @brief Refreshes the WDOG8 timer.
 *
 * This function feeds the WDOG8.
 * This function should be called before the Watchdog timer is in timeout. Otherwise, a reset is asserted.
 *
 * @param base WDOG8 peripheral base address
 */
static inline void WDOG8_Refresh(WDOG_Type *base)
{
    uint32_t primaskValue = 0U;

    /* Disable the global interrupts */
    primaskValue = DisableGlobalIRQ();
    base->CNT    = WDOG_REFRESH_KEY1;
    base->CNT    = WDOG_REFRESH_KEY2;
    EnableGlobalIRQ(primaskValue);
}

/*!
 * @brief Gets the WDOG8 counter value.
 *
 * This function gets the WDOG8 counter value.
 *
 * @param base WDOG8 peripheral base address.
 * @return     Current WDOG8 counter value.
 */
static inline uint16_t WDOG8_GetCounterValue(WDOG_Type *base)
{
    return ((uint16_t)(base->CNT8B.CNTH) << 8U) + (uint16_t)(base->CNT8B.CNTL);
}

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/

#endif /* _FSL_WDOG8_H_ */
