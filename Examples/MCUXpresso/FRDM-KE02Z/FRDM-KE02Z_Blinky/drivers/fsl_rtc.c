/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rtc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rtc_1"
#endif

#define SECONDS_IN_A_DAY    (86400U)
#define SECONDS_IN_A_HOUR   (3600U)
#define SECONDS_IN_A_MINUTE (60U)
#define DAYS_IN_A_YEAR      (365U)
#define YEAR_RANGE_START    (1970U)
#define YEAR_RANGE_END      (2099U)

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile uint32_t s_CurrentTimeSeconds;
static volatile uint32_t s_AlarmTimeSeconds;
static rtc_alarm_callback_t s_RtcAlarmCallback;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Checks whether the date and time passed in is valid
 *
 * @param datetime Pointer to structure where the date and time details are stored
 *
 * @return Returns false if the date & time details are out of range; true if in range
 */
static bool RTC_CheckDatetimeFormat(const rtc_datetime_t *datetime);

/*!
 * @brief Converts time data from datetime to seconds
 *
 * @param datetime Pointer to datetime structure where the date and time details are stored
 *
 * @return The result of the conversion in seconds
 */
static uint32_t RTC_ConvertDatetimeToSeconds(const rtc_datetime_t *datetime);

/*!
 * @brief Converts time data from seconds to a datetime structure
 *
 * @param seconds  Seconds value that needs to be converted to datetime format
 * @param datetime Pointer to the datetime structure where the result of the conversion is stored
 */
static void RTC_ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime);

/*******************************************************************************
 * Code
 ******************************************************************************/
static bool RTC_CheckDatetimeFormat(const rtc_datetime_t *datetime)
{
    assert(datetime);

    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Check year, month, hour, minute, seconds */
    if ((datetime->year < YEAR_RANGE_START) || (datetime->year > YEAR_RANGE_END) || (datetime->month > 12U) ||
        (datetime->month < 1U) || (datetime->hour >= 24U) || (datetime->minute >= 60U) || (datetime->second >= 60U))
    {
        /* If not correct then error*/
        return false;
    }

    /* Adjust the days in February for a leap year */
    if ((((datetime->year & 3U) == 0U) && (datetime->year % 100U != 0U)) || (datetime->year % 400U == 0U))
    {
        daysPerMonth[2] = 29U;
    }

    /* Check the validity of the day */
    if ((datetime->day > daysPerMonth[datetime->month]) || (datetime->day < 1U))
    {
        return false;
    }

    return true;
}

static uint32_t RTC_ConvertDatetimeToSeconds(const rtc_datetime_t *datetime)
{
    assert(datetime);

    /* Number of days from begin of the non Leap-year*/
    /* Number of days from begin of the non Leap-year*/
    uint16_t monthDays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};
    uint32_t seconds;

    /* Compute number of days from 1970 till given year*/
    seconds = ((uint32_t)datetime->year - 1970U) * DAYS_IN_A_YEAR;
    /* Add leap year days */
    seconds += (((uint32_t)datetime->year / 4U) - (1970U / 4U));
    /* Add number of days till given month*/
    seconds += monthDays[datetime->month];
    /* Add days in given month. We subtract the current day as it is
     * represented in the hours, minutes and seconds field*/
    seconds += ((uint32_t)datetime->day - 1U);
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if (((datetime->year & 3U) == 0x00U) && (datetime->month <= 2U))
    {
        seconds--;
    }

    seconds = (seconds * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
              (datetime->minute * SECONDS_IN_A_MINUTE) + datetime->second;

    return seconds;
}

static void RTC_ConvertSecondsToDatetime(uint32_t seconds, rtc_datetime_t *datetime)
{
    assert(datetime);

    uint8_t i;
    uint16_t daysInYear;
    uint32_t secondsRemaining;
    uint32_t days;
    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Start with the seconds value that is passed in to be converted to date time format */
    secondsRemaining = seconds;

    /* Calcuate the number of days, we add 1 for the current day which is represented in the
     * hours and seconds field
     */
    days = secondsRemaining / SECONDS_IN_A_DAY + 1U;

    /* Update seconds left*/
    secondsRemaining = secondsRemaining % SECONDS_IN_A_DAY;

    /* Calculate the datetime hour, minute and second fields */
    datetime->hour   = (uint8_t)(secondsRemaining / SECONDS_IN_A_HOUR);
    secondsRemaining = secondsRemaining % SECONDS_IN_A_HOUR;
    datetime->minute = (uint8_t)(secondsRemaining / 60U);
    datetime->second = (uint8_t)(secondsRemaining % SECONDS_IN_A_MINUTE);

    /* Calculate year */
    daysInYear     = DAYS_IN_A_YEAR;
    datetime->year = YEAR_RANGE_START;
    while (days > daysInYear)
    {
        /* Decrease day count by a year and increment year by 1 */
        days -= daysInYear;
        datetime->year++;

        /* Adjust the number of days for a leap year */
        if ((datetime->year & 3U) != 0x00U)
        {
            daysInYear = DAYS_IN_A_YEAR;
        }
        else
        {
            daysInYear = DAYS_IN_A_YEAR + 1U;
        }
    }

    /* Adjust the days in February for a leap year */
    if ((datetime->year & 3U) == 0x00U)
    {
        daysPerMonth[2] = 29U;
    }

    for (i = 1U; i <= 12U; i++)
    {
        if (days <= daysPerMonth[i])
        {
            datetime->month = i;
            break;
        }
        else
        {
            days -= daysPerMonth[i];
        }
    }

    datetime->day = (uint8_t)days;
}

/*!
 * brief Ungates the RTC clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the RTC driver.
 *
 * param base   RTC peripheral base address
 */
void RTC_Init(RTC_Type *base, const rtc_config_t *config)
{
    assert(config);

    uint32_t srcClock_Hz = 0;
#if defined(RTC_CLOCKS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Rtc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* RTC_CLOCKS */

    /* Clear Real-Time Interrupt Flag to 0 */
    base->SC |= RTC_SC_RTIF_MASK;

    /* Select Real-Time Clock Source and Clock Prescaler */
    base->SC &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
    base->SC |= RTC_SC_RTCLKS(config->clockSource) | RTC_SC_RTCPS(config->prescaler);

    /* Get RTC clock frequency */
    if (config->clockSource == kRTC_ExternalClock)
    {
        srcClock_Hz = CLOCK_GetFreq(kCLOCK_Osc0ErClk);
    }

    if (config->clockSource == kRTC_LPOCLK)
    {
        srcClock_Hz = CLOCK_GetFreq(kCLOCK_LpoClk);
    }

    if (config->clockSource == kRTC_ICSIRCLK)
    {
        srcClock_Hz = CLOCK_GetFreq(kCLOCK_ICSInternalRefClk);
    }

    if (config->clockSource == kRTC_BusClock)
    {
        srcClock_Hz = CLOCK_GetFreq(kCLOCK_BusClk);
    }

    /* Set RTC module value */
    RTC_SetModuloValue(
        base,
        (uint32_t)(USEC_TO_COUNT(config->time_us, (uint64_t)srcClock_Hz / (uint64_t)RTC_GetDivideValue(base)) - 1U));
}

/*!
 * brief Stops the timer and gate the RTC clock.
 *
 * param base RTC peripheral base address
 */
void RTC_Deinit(RTC_Type *base)
{
#if defined(RTC_CLOCKS)
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the module clock */
    CLOCK_DisableClock(kCLOCK_Rtc0);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* RTC_CLOCKS */
}

/*!
 * brief Fills in the RTC config struct with the default settings.
 *
 * The default values are as follows.
 * code
 *    config->clockSource = kRTC_BusClock;
 *    config->prescaler = kRTC_ClockDivide_16_2048;
 *    config->time_us = 1000000U;
 * endcode
 * param config Pointer to the user's RTC configuration structure.
 */
void RTC_GetDefaultConfig(rtc_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->clockSource = kRTC_BusClock;

    config->prescaler = kRTC_ClockDivide_16_2048;

    /* Configure RTC to interrupt every 1000000us */
    config->time_us = 1000000U;
}

/*!
 * brief  Get the RTC Divide value.
 *
 * note This API should be called after selecting clock source and clock prescaler.
 *
 * param base    RTC peripheral base address
 * return  The Divider value. The Divider value depends on clock source and clock prescaler
 */
uint32_t RTC_GetDivideValue(RTC_Type *base)
{
    uint32_t clocks, divide, prescale;

    /* Get RTCLKS and RTCPS configuration value */
    clocks   = (uint32_t)((base->SC & RTC_SC_RTCLKS_MASK) >> RTC_SC_RTCLKS_SHIFT);
    prescale = (uint32_t)((base->SC & RTC_SC_RTCPS_MASK) >> RTC_SC_RTCPS_SHIFT);

    assert(prescale > 0UL);

    if ((clocks & 1UL) == 0UL)
    {
        divide = 1UL << (prescale - 1UL);
    }
    if ((clocks & 1UL) == 1UL)
    {
        if (prescale < 6UL)
        {
            divide = 1UL << (prescale + 6UL);
        }
        else if (prescale == 6UL)
        {
            divide = 100UL;
        }
        else
        {
            divide = 1000UL;
        }
    }
    return divide;
}

/*!
 * brief Sets the RTC date and time according to the given time structure.
 *
 * param datetime Pointer to the structure where the date and time details are stored.
 *
 * return kStatus_Success: Success in setting the time and starting the RTC
 *         kStatus_InvalidArgument: Error because the datetime format is incorrect
 */
status_t RTC_SetDatetime(rtc_datetime_t *datetime)
{
    assert(datetime != NULL);

    status_t status = kStatus_Success;

    /* Return error if the time provided is not valid */
    if (!(RTC_CheckDatetimeFormat(datetime)))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        /* Set current time seconds */
        s_CurrentTimeSeconds = RTC_ConvertDatetimeToSeconds(datetime);
    }

    return status;
}

/*!
 * brief Gets the RTC time and stores it in the given time structure.
 *
 * param datetime Pointer to the structure where the date and time details are stored.
 */
void RTC_GetDatetime(rtc_datetime_t *datetime)
{
    assert(datetime);

    /* Get current data time */
    RTC_ConvertSecondsToDatetime(s_CurrentTimeSeconds, datetime);
}

/*!
 * brief Sets the RTC alarm time.
 *
 * param second   Second value. User input the number of second.
 *                 After seconds user input, alarm occurs.
 */
void RTC_SetAlarm(uint32_t second)
{
    /* Set alarm time seconds */
    s_AlarmTimeSeconds = second + s_CurrentTimeSeconds;
}

/*!
 * brief Returns the RTC alarm time.
 *
 * param datetime Pointer to the structure where the alarm date and time details are stored.
 */
void RTC_GetAlarm(rtc_datetime_t *datetime)
{
    assert(datetime);

    /* Get alarm data time */
    RTC_ConvertSecondsToDatetime(s_AlarmTimeSeconds, datetime);
}

/*!
 * brief Set the RTC alarm callback.
 *
 * param callback The callback function.
 */
void RTC_SetAlarmCallback(rtc_alarm_callback_t callback)
{
    s_RtcAlarmCallback = callback;
}

void RTC_DriverIRQHandler(void);
void RTC_DriverIRQHandler(void)
{
    uint32_t alarmTimeSeconds = s_AlarmTimeSeconds; /* Fix the order of volatile accesses undefined issue. */

    if ((RTC_GetInterruptFlags(RTC) & (uint32_t)kRTC_InterruptFlag) != 0U)
    {
        s_CurrentTimeSeconds++;
        /* Clear second interrupt flag */
        RTC_ClearInterruptFlags(RTC, (uint32_t)kRTC_InterruptFlag);
    }

    if (alarmTimeSeconds == s_CurrentTimeSeconds)
    {
        if (s_RtcAlarmCallback != NULL)
        {
            s_RtcAlarmCallback();
        }
    }
}
