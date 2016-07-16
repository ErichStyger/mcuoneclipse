/**
 * \file rtc-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 21.09.2015
 * \brief MCU RTC timer and low power modes management
 *
 */

#if defined(FSL_RTOS_FREE_RTOS)

#include "board.h"
#include "rtc-board.h"

void BlockLowPowerDuringTask( bool status )
{
    (void)status;
}
#else

#include <math.h>
#include <time.h>
#include "board.h"
#include "rtc-board.h"
#include "fsl_rtc_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
/*----------------------- Local Definitions ------------------------------*/
/*!
 * RTC Time base in us
 */
#define RTC_ALARM_TIME_BASE                             122.07

/*!
 * MCU Wake Up Time
 */
#define MCU_WAKE_UP_TIME                                3400

/*----------------------- Local Functions ------------------------------*/
/*!
 * \brief Start the Rtc Alarm (time base 1s)
 */
static void RtcStartWakeUpAlarm( uint32_t timeoutValue );

/*!
 * \brief Read the MCU internal Calendar value
 *
 * \retval Calendar value
 */
static TimerTime_t RtcGetCalendarValue( void );

/*!
 * \brief Clear the RTC flags and Stop all IRQs
 */
static void RtcClearStatus( void );

/*------------------------ Local Variables -------------------------------*/
/* Table of base addresses for RTC instances. */
RTC_Type * const g_rtcBase[RTC_INSTANCE_COUNT] = RTC_BASE_PTRS;

/*!
 * \brief Indicates if the RTC is already Initalized or not
 */
static bool RtcInitalized = false;

/*!
 * \brief Flag to indicate if the timestamps until the next event is long enough 
 * to set the MCU into low power mode
 */
static bool RtcTimerEventAllowsLowPower = false;

/*!
 * \brief Flag to disable the LowPower Mode even if the timestamps until the
 * next event is long enough to allow Low Power mode 
 */
static bool LowPowerDisableDuringTask = false;

/*!
 * Keep the value of the RTC timer when the RTC alarm is set
 */
static TimerTime_t RtcTimerContext = 0;

/*!
 * RTC external clock configuration
 */
rtc_osc_user_config_t rtcOscConfig =
{
    .freq = RTC_XTAL_FREQ,
    .enableCapacitor2p = RTC_SC2P_ENABLE_CONFIG,
    .enableCapacitor4p = RTC_SC4P_ENABLE_CONFIG,
    .enableCapacitor8p = RTC_SC8P_ENABLE_CONFIG,
    .enableCapacitor16p = RTC_SC16P_ENABLE_CONFIG,
    .enableOsc = RTC_OSC_ENABLE_CONFIG,
};

void RtcInit( void )
{
    if ( RtcInitalized == false ) {
        rtc_datetime_t datetime;
        uint32_t srcClock = 0;
        uint32_t seconds = 0;
        uint16_t preScaler = 0;
        uint64_t tmp = 0;

        /* Enable clock gate to RTC module */
        CLOCK_SYS_EnableRtcClock(0U);

        /* Initialize the general configuration for RTC module.*/
        RTC_HAL_Init (RTC_BASE_PTR);

        /* Clear pending interrupts before enabling them */
        NVIC_ClearPendingIRQ (RTC_IRQn);
        INT_SYS_EnableIRQ(RTC_IRQn);

        /* Configure RTC external clock */
        CLOCK_SYS_RtcOscInit(0U, &rtcOscConfig);

        // Set a start date time and start RT.
        datetime.year = 2014U;
        datetime.month = 12U;
        datetime.day = 25U;
        datetime.hour = 19U;
        datetime.minute = 0;
        datetime.second = 0;

        RTC_HAL_ConvertDatetimeToSecs(&datetime, &seconds);

        if ( (srcClock = CLOCK_SYS_GetRtcFreq(0U)) != 32768U ) {
            /* As the seconds register will not increment every second, we need to adjust the value
             * programmed to the seconds register */
            tmp = (uint64_t) seconds * (uint64_t) srcClock;
            preScaler = (uint32_t)(tmp & 0x7FFFU);
            seconds = (uint32_t)(tmp >> 15U);
        }
        /* Set time in seconds */
        RTC_HAL_EnableCounter(RTC_BASE_PTR, false);
        /* Set seconds counter*/
        RTC_HAL_SetSecsReg(RTC_BASE_PTR, seconds);
        /* Set time counter*/
        RTC_HAL_SetPrescaler(RTC_BASE_PTR, preScaler);
        /* Enable the counter*/
        RTC_HAL_EnableCounter(RTC_BASE_PTR, true);
        RtcInitalized = true;
    }
}

void RtcStopTimer( void )
{
    RtcClearStatus();
}

uint32_t RtcGetMinimumTimeout( void )
{
    return (ceil(3 * RTC_ALARM_TIME_BASE));
}

void RtcSetTimeout( uint32_t timeout )
{
    uint32_t timeoutValue = 0;

    timeoutValue = timeout;

    if ( timeoutValue < (3 * RTC_ALARM_TIME_BASE) ) {
        timeoutValue = 3 * RTC_ALARM_TIME_BASE;
    }

    if ( timeoutValue < 55000 ) {
        // we don't go in Low Power mode for delay below 50ms (needed for LEDs)
        RtcTimerEventAllowsLowPower = false;
    } else {
        RtcTimerEventAllowsLowPower = true;
    }

    if ( (LowPowerDisableDuringTask == false) && (RtcTimerEventAllowsLowPower == true) ) {
        timeoutValue = timeoutValue - MCU_WAKE_UP_TIME;
    }

    RtcStartWakeUpAlarm(timeoutValue);
}

uint32_t RtcGetTimerElapsedTime( void )
{
    TimerTime_t CalendarValue = 0;

    CalendarValue = RtcGetCalendarValue();

    return ((uint32_t)(ceil(((CalendarValue - RtcTimerContext) + 2) * RTC_ALARM_TIME_BASE)));
}

TimerTime_t RtcGetTimerValue( void )
{
    TimerTime_t CalendarValue = 0;

    CalendarValue = RtcGetCalendarValue();

    return ((CalendarValue + 2) * RTC_ALARM_TIME_BASE);
}

static void RtcClearStatus( void )
{
    /* Deactivate the Alarm interrupt */
    RTC_HAL_SetAlarmIntCmd(RTC_BASE_PTR, false);
}

static void RtcStartWakeUpAlarm( uint32_t timeoutValue )
{
    uint32_t srcClock = 0;
    uint32_t alrmSeconds = 0;
    uint32_t currSeconds = 0;
    uint64_t tmp = 0;

    RtcClearStatus();

    RtcTimerContext = RtcGetCalendarValue();

    /* Get the current time */
    currSeconds = RTC_HAL_GetSecsReg(RTC_BASE_PTR);
    alrmSeconds = timeoutValue / RTC_ALARM_TIME_BASE;

    if ( (srcClock = CLOCK_SYS_GetRtcFreq(0)) != 32768U ) {
        /* As the seconds register will not increment every second, we need to adjust the value
         * programmed to the alarm register */
        tmp = (uint64_t) alrmSeconds * (uint64_t) srcClock;
        alrmSeconds = (uint32_t)(tmp >> 15U);
    }

    alrmSeconds += currSeconds;

    /* set alarm in seconds*/
    RTC_HAL_SetAlarmReg(RTC_BASE_PTR, alrmSeconds);

    /* Activate the Alarm interrupt */
    RTC_HAL_SetAlarmIntCmd(RTC_BASE_PTR, true);
}

void RtcEnterLowPowerStopMode( void )
{
    if ( (LowPowerDisableDuringTask == false) && (RtcTimerEventAllowsLowPower == true) ) {
        // Disable IRQ while the MCU is being deinitialized to prevent race issues
        INT_SYS_DisableIRQGlobal();
//      \todo Implement RtcEnterLowPowerStopMode
//        BoardDeInitMcu();

        INT_SYS_EnableIRQGlobal();
    }
}

void RtcRecoverMcuStatus( void )
{
    if ( TimerGetLowPowerEnable() == true ) {
        if ( (LowPowerDisableDuringTask == false) && (RtcTimerEventAllowsLowPower == true) ) {
            // Disable IRQ while the MCU is not running on HSE
            INT_SYS_DisableIRQGlobal();

//          \todo Implement RtcRecoverMcuStatus
//            BoardInitMcu();

            INT_SYS_EnableIRQGlobal();
        }
    }
}

/*!
 * \brief RTC IRQ Handler on the RTC Alarm
 */
void RTC_IRQHandler( void )
{
    if ( RTC_HAL_HasAlarmOccured (RTC_BASE_PTR) ) {
//        RtcRecoverMcuStatus();

        TimerIrqHandler();

        /* Writing to the alarm register clears the TAF flag in the Status register */
        RTC_HAL_SetAlarmReg(RTC_BASE_PTR, 0x0);
        RTC_HAL_SetAlarmIntCmd(RTC_BASE_PTR, false);
    }
}

void BlockLowPowerDuringTask( bool status )
{
    if ( status == true ) {
        RtcRecoverMcuStatus();
    }
    LowPowerDisableDuringTask = status;
}

void RtcDelayMs( uint32_t delay )
{
    TimerTime_t delayValue = 0;
    TimerTime_t timeout = 0;

    delayValue = (TimerTime_t)(delay * 1000);

    // Wait delay ms
    timeout = RtcGetTimerValue();
    while (((RtcGetTimerValue() - timeout)) < delayValue) {
        __NOP();
    }
}

TimerTime_t RtcGetCalendarValue( void )
{
    uint32_t seconds = 0;
    uint32_t srcClock = 0;
    uint64_t tmp = 0;

    RTC_HAL_GetDatetimeInSecs(RTC_BASE_PTR, &seconds);

    if ( (srcClock = CLOCK_SYS_GetRtcFreq(0U)) != 32768U ) {
        /* In case the input clock to the RTC counter is not 32KHz, the seconds register will not
         * increment every second, therefore the seconds register value needs to be adjusted.
         * to get actual seconds. We then add the prescaler register value to the seconds.
         */
        tmp = (uint64_t) seconds << 15U;
        tmp |= (uint64_t)(RTC_HAL_GetPrescaler(RTC_BASE_PTR) & 0x7FFFU);
        seconds = tmp / srcClock;
    }

    return (TimerTime_t) seconds;
}
#endif
