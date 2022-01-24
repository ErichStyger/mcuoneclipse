/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_RTC_H_
#define _FSL_RTC_H_

#include "fsl_common.h"

/*!
 * @addtogroup rtc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_RTC_DRIVER_VERSION (MAKE_VERSION(2, 0, 4)) /*!< Version 2.0.4 */
/*@}*/

/*! @brief Structure is used to hold the date and time */
typedef struct _rtc_datetime
{
    uint16_t year;  /*!< Range from 1970 to 2099.*/
    uint8_t month;  /*!< Range from 1 to 12.*/
    uint8_t day;    /*!< Range from 1 to 31 (depending on month).*/
    uint8_t hour;   /*!< Range from 0 to 23.*/
    uint8_t minute; /*!< Range from 0 to 59.*/
    uint8_t second; /*!< Range from 0 to 59.*/
} rtc_datetime_t;

/*! @brief List of RTC clock source */
typedef enum _rtc_clock_source
{
    kRTC_ExternalClock = 0U, /*!< External clock source */
    kRTC_LPOCLK        = 1U, /*!< Real-time clock source is 1 kHz (LPOCLK) */
    kRTC_ICSIRCLK      = 2U, /*!< Internal reference clock (ICSIRCLK) */
    kRTC_BusClock      = 3U, /*!< Bus clock */
} rtc_clock_source_t;

/*! @brief List of RTC clock prescaler */
typedef enum _rtc_clock_prescaler
{
    kRTC_ClockDivide_off     = 0U, /*!< Off */
    kRTC_ClockDivide_1_128   = 1U, /*!< If RTCLKS = x0, it is 1; if RTCLKS = x1, it is 128 */
    kRTC_ClockDivide_2_256   = 2U, /*!< If RTCLKS = x0, it is 2; if RTCLKS = x1, it is 256 */
    kRTC_ClockDivide_4_512   = 3U, /*!< If RTCLKS = x0, it is 4; if RTCLKS = x1, it is 512 */
    kRTC_ClockDivide_8_1024  = 4U, /*!< If RTCLKS = x0, it is 8; if RTCLKS = x1, it is 1024 */
    kRTC_ClockDivide_16_2048 = 5U, /*!< If RTCLKS = x0, it is 16; if RTCLKS = x1, it is 2048 */
    kRTC_ClockDivide_32_100  = 6U, /*!< If RTCLKS = x0, it is 32; if RTCLKS = x1, it is 100 */
    kRTC_ClockDivide_64_1000 = 7U, /*!< If RTCLKS = x0, it is 64; if RTCLKS = x1, it is 1000 */
} rtc_clock_prescaler_t;

/*! @brief List of RTC interrupts */
typedef enum _rtc_interrupt_enable
{
    kRTC_InterruptEnable = RTC_SC_RTIE_MASK, /*!< Interrupt enable */
} rtc_interrupt_enable_t;

/*! @brief List of RTC Interrupt flags */
typedef enum _RTC_interrupt_flags
{
    kRTC_InterruptFlag = RTC_SC_RTIF_MASK, /*!< Interrupt flag */
} rtc_interrupt_flags_t;

/*! @brief List of RTC Output */
typedef enum _RTC_output_enable
{
    kRTC_OutputEnable = RTC_SC_RTCO_MASK, /*!< Output enable */
} rtc_output_enable_t;

/*!
 * @brief RTC config structure
 *
 * This structure holds the configuration settings for the RTC peripheral. To initialize this
 * structure to reasonable defaults, call the RTC_GetDefaultConfig() function and pass a
 * pointer to your config structure instance.
 */
typedef struct _rtc_config
{
    rtc_clock_source_t clockSource;  /* select RTC clock source */
    rtc_clock_prescaler_t prescaler; /* select clock prescaler */
    uint32_t time_us;                /* set entering interrupt time */
} rtc_config_t;

/*! @brief RTC alarm callback function. */
typedef void (*rtc_alarm_callback_t)(void);

/*! @} */
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup rtc
 * @{
 */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Ungates the RTC clock and configures the peripheral for basic operation.
 *
 * @note This API should be called at the beginning of the application using the RTC driver.
 *
 * @param base   RTC peripheral base address
 * @param config Pointer to the user's RTC configuration structure.
 */
void RTC_Init(RTC_Type *base, const rtc_config_t *config);

/*!
 * @brief Stops the timer and gate the RTC clock.
 *
 * @param base RTC peripheral base address
 */
void RTC_Deinit(RTC_Type *base);

/*!
 * @brief Fills in the RTC config struct with the default settings.
 *
 * The default values are as follows.
 * @code
 *    config->clockSource = kRTC_BusClock;
 *    config->prescaler = kRTC_ClockDivide_16_2048;
 *    config->time_us = 1000000U;
 * @endcode
 * @param config Pointer to the user's RTC configuration structure.
 */
void RTC_GetDefaultConfig(rtc_config_t *config);

/*! @}*/

/*!
 * @name Current Time & Alarm
 * @{
 */

/*!
 * @brief Sets the RTC date and time according to the given time structure.
 *
 * @param datetime Pointer to the structure where the date and time details are stored.
 *
 * @return kStatus_Success: Success in setting the time and starting the RTC
 *         kStatus_InvalidArgument: Error because the datetime format is incorrect
 */
status_t RTC_SetDatetime(rtc_datetime_t *datetime);

/*!
 * @brief Gets the RTC time and stores it in the given time structure.
 *
 * @param datetime Pointer to the structure where the date and time details are stored.
 */
void RTC_GetDatetime(rtc_datetime_t *datetime);

/*!
 * @brief Sets the RTC alarm time.
 *
 * @param second   Second value. User input the number of second.
 *                 After seconds user input, alarm occurs.
 */
void RTC_SetAlarm(uint32_t second);

/*!
 * @brief Returns the RTC alarm time.
 *
 * @param datetime Pointer to the structure where the alarm date and time details are stored.
 */
void RTC_GetAlarm(rtc_datetime_t *datetime);

/*!
 * @brief Set the RTC alarm callback.
 *
 * @param callback The callback function.
 */
void RTC_SetAlarmCallback(rtc_alarm_callback_t callback);

/*! @}*/

/*!
 * @name Select Source clock
 * @{
 */

/*!
 * @brief Select Real-Time Clock Source and Clock Prescaler
 *
 * @param base   RTC peripheral base address
 * @param clock  Select RTC clock source
 * @param divide Select RTC clock prescaler value
 */
static inline void RTC_SelectSourceClock(RTC_Type *base, rtc_clock_source_t clock, rtc_clock_prescaler_t divide)
{
    base->SC &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
    base->SC |= RTC_SC_RTCLKS(clock) | RTC_SC_RTCPS(divide);
}

/*!
 * @brief  Get the RTC Divide value.
 *
 * @note This API should be called after selecting clock source and clock prescaler.
 *
 * @param base    RTC peripheral base address
 * @return  The Divider value. The Divider value depends on clock source and clock prescaler
 */
uint32_t RTC_GetDivideValue(RTC_Type *base);

/*! @}*/

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the selected RTC interrupts.
 *
 * @param base    RTC peripheral base address
 * @param mask    The interrupts to enable. This is a logical OR of members of the
 *                enumeration ::rtc_interrupt_enable_t
 */
static inline void RTC_EnableInterrupts(RTC_Type *base, uint32_t mask)
{
    base->SC |= mask;
}

/*!
 * @brief Disables the selected RTC interrupts.
 *
 * @param base    PIT peripheral base address
 * @param mask    The interrupts to disable. This is a logical OR of members of the
 *                enumeration ::rtc_interrupt_enable_t
 */
static inline void RTC_DisableInterrupts(RTC_Type *base, uint32_t mask)
{
    base->SC &= ~mask;
}

/*!
 * @brief Gets the enabled RTC interrupts.
 *
 * @param base    RTC peripheral base address
 *
 * @return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::rtc_interrupt_enable_t
 */
static inline uint32_t RTC_GetEnabledInterrupts(RTC_Type *base)
{
    return (base->SC & RTC_SC_RTIE_MASK);
}

/*!
 * @brief Gets the RTC interrupt flags.
 *
 * @param base    RTC peripheral base address
 *
 * @return The interrupt flags. This is the logical OR of members of the
 *         enumeration ::rtc_interrupt_flags_t
 */
static inline uint32_t RTC_GetInterruptFlags(RTC_Type *base)
{
    return (base->SC & RTC_SC_RTIF_MASK);
}

/*!
 * @brief  Clears the RTC interrupt flags.
 *
 * @param base    RTC peripheral base address
 * @param mask    The interrupt flags to clear. This is a logical OR of members of the
 *                enumeration ::rtc_interrupt_flags_t
 */
static inline void RTC_ClearInterruptFlags(RTC_Type *base, uint32_t mask)
{
    base->SC |= mask;
}

/*! @}*/

/*!
 * @name Output Interface
 * @{
 */

/*!
 * @brief  Enable the RTC output. If RTC output is enabled, the RTCO pinout will be
 *         toggled when RTC counter overflows
 *
 * @param base    RTC peripheral base address
 * @param mask    The Output to enable. This is a logical OR of members of the
 *                enumeration ::rtc_output_enable_t
 */
static inline void RTC_EnableOutput(RTC_Type *base, uint32_t mask)
{
    base->SC |= mask;
}

/*!
 * @brief  Disable the RTC output.
 *
 * @param base    RTC peripheral base address
 * @param mask    The Output to disable. This is a logical OR of members of the
 *                enumeration ::rtc_output_enable_t
 */
static inline void RTC_DisableOutput(RTC_Type *base, uint32_t mask)
{
    base->SC &= ~mask;
}

/*! @}*/

/*!
 * @name Set module value and Get Count value
 * @{
 */

/*!
 * @brief  Set the RTC module value.
 *
 * @param base    RTC peripheral base address
 * @param value   The Module Value. The RTC Modulo register allows the compare value
 *                to be set to any value from 0x0000 to 0xFFFF
 */
static inline void RTC_SetModuloValue(RTC_Type *base, uint32_t value)
{
    assert(value <= RTC_MOD_MOD_MASK);
    base->MOD = value;
}

/*!
 * @brief  Get the RTC Count value.
 *
 * @param base    RTC peripheral base address
 * @return  The Count Value. The Count Value is allowed from 0x0000 to 0xFFFF
 */
static inline uint16_t RTC_GetCountValue(RTC_Type *base)
{
    volatile const uint8_t *addr;
    addr = (volatile const uint8_t *)(&base->CNT);
    return (uint16_t)((uint16_t) * (addr) | (uint16_t)((uint16_t) * (addr + 1) << 8U));
}

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_RTC_H_ */
