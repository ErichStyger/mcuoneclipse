/**
 * \file rtc-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 21.09.2015
 * \brief MCU RTC timer and low power modes management
 *
 */

#if defined(USE_FREE_RTOS)

#include "board.h"
#include "rtc-board.h"

void BlockLowPowerDuringTask( bool status )
{
    (void) status;
}
#else
#include <math.h>
#include <time.h>
#include "board.h"
#include "rtc-board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * MCU Wake Up Time
 */
#define MCU_WAKE_UP_TIME                                3400

#define SECONDS_IN_A_DAY     (86400U)
#define SECONDS_IN_A_HOUR    (3600U)
#define SECONDS_IN_A_MIN     (60U)
#define MINS_IN_A_HOUR       (60U)
#define HOURS_IN_A_DAY       (24U)
#define DAYS_IN_A_YEAR       (365U)
#define DAYS_IN_A_LEAP_YEAR  (366U)
#define YEAR_RANGE_START     (1970U)
#define YEAR_RANGE_END       (2099U)

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of month length (in days) for the Un-leap-year*/
static const uint8_t ULY[] = { 0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U };

/* Table of month length (in days) for the Leap-year*/
static const uint8_t LY[] = { 0U, 31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U };

/* Number of days from begin of the non Leap-year*/
static const uint16_t MONTH_DAYS[] = { 0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U,
        304U, 334U };

/*----------------------- Local Functions ------------------------------*/
/*!
 * \brief Start the Rtc Alarm (time base 1s)
 */
static void RtcStartWakeUpAlarm( uint32_t timeoutValue );

/*!
 * \brief Clear the RTC flags and Stop all IRQs
 */
static void RtcClearStatus( void );

/*------------------------ Local Variables -------------------------------*/
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

void RtcInit( void )
{
    if ( RtcInitalized == false ) {
        /* Enable clock gating */
        SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_RTC_MASK;

        if ( ((RTC_BASE_PTR->SR) & RTC_SR_TIF_MASK) == 1 ) {
            /* Resets the RTC registers except for the SWR bit */
            RTC_BASE_PTR->CR |= RTC_CR_SWR_MASK;
            RTC_BASE_PTR->CR &= ~(RTC_CR_SWR_MASK);

            /* Set TSR register to 0x1 to avoid the TIF bit being set in the SR register */
            RTC_BASE_PTR->TPR = RTC_TPR_TPR(0);
            RTC_BASE_PTR->TSR = 1;
        }

        /* Clear the interrupt enable register */
        RTC_BASE_PTR->IER &= (RTC_IER_TIIE_MASK | RTC_IER_TOIE_MASK | RTC_IER_TAIE_MASK
                | RTC_IER_TSIE_MASK);

        NVIC_BASE_PTR->ICPR[(((uint32_t) (int32_t) RTC_IRQn) >> 5UL)] = (uint32_t)(
                1UL << (((uint32_t) (int32_t) RTC_IRQn) & 0x1FUL));
        NVIC_BASE_PTR->ICPR[(((uint32_t) (int32_t) RTC_Seconds_IRQn) >> 5UL)] = (uint32_t)(
                1UL << (((uint32_t) (int32_t) RTC_Seconds_IRQn) & 0x1FUL));
        NVIC_BASE_PTR->ISER[(((uint32_t) (int32_t) RTC_IRQn) >> 5UL)] = (uint32_t)(
                1UL << (((uint32_t) (int32_t) RTC_IRQn) & 0x1FUL));
        NVIC_BASE_PTR->ISER[(((uint32_t) (int32_t) RTC_Seconds_IRQn) >> 5UL)] = (uint32_t)(
                1UL << (((uint32_t) (int32_t) RTC_Seconds_IRQn) & 0x1FUL));

        RtcInitalized = true;
    }
}

void RtcStopTimer( void )
{
    RtcClearStatus();
}

uint32_t RtcGetMinimumTimeout( void )
{
    return 1;
}

void RtcSetTimeout( uint32_t timeout )
{
    uint32_t timeoutValue = 0;

    timeoutValue = timeout;

    if ( timeoutValue < 1 ) {
        timeoutValue = 1;
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
    TimerTime_t timeInSeconds = 0;

    timeInSeconds = RtcGetTimerValue();

    return ((uint32_t)(timeInSeconds - RtcTimerContext));
}

TimerTime_t RtcGetTimerValue( void )
{
    return RTC_BASE_PTR->TSR;
}

static void RtcClearStatus( void )
{
    /* Clear status flag */
    RTC_BASE_PTR->SR |= (RTC_SR_TIF_MASK | RTC_SR_TOF_MASK | RTC_SR_TAF_MASK | RTC_SR_TCE_MASK);
    /* Disable RTC interrupts.*/
    NVIC_BASE_PTR->ICER[(((uint32_t) (int32_t) INT_RTC) >> 5UL)] = (uint32_t)(
            1UL << (((uint32_t) (int32_t) INT_RTC) & 0x1FUL));
    NVIC_BASE_PTR->ICER[(((uint32_t) (int32_t) INT_RTC_Seconds) >> 5UL)] = (uint32_t)(
            1UL << (((uint32_t) (int32_t) INT_RTC_Seconds) & 0x1FUL));
}

static void RtcStartWakeUpAlarm( uint32_t timeoutValue )
{
    uint32_t srcClock = CPU_XTAL32k_CLK_HZ;
    uint32_t alrmSeconds = 0;
    uint32_t currSeconds = 0;
    uint64_t tmp = 0;

    /* Get the current time */
    currSeconds = RTC_BASE_PTR->TSR;

    /* Calculate alarm time */
    alrmSeconds = currSeconds + timeoutValue;

    if ( srcClock != 32768U ) {
        /* As the seconds register will not increment every second, we need to adjust the value
         * programmed to the alarm register */
        tmp = (uint64_t) alrmSeconds * (uint64_t) srcClock;
        alrmSeconds = (uint32_t)(tmp >> 15U);
    }

    /* Make sure the alarm is for a future time */
    if ( alrmSeconds < currSeconds ) {
        return;
    }

    /* set alarm in seconds*/
    RTC_BASE_PTR->TAR = alrmSeconds;

    /* Activate or deactivate the Alarm interrupt based on user choice */
    RTC_BASE_PTR->IER |= RTC_IER_TAIE_MASK;
}

void RtcEnterLowPowerStopMode( void )
{
    if ( (LowPowerDisableDuringTask == false) && (RtcTimerEventAllowsLowPower == true) ) {
        // Disable IRQ while the MCU is being deinitialized to prevent race issues

//      \todo Implement RtcEnterLowPowerStopMode
//        BoardDeInitMcu();

    }
}

void RtcRecoverMcuStatus( void )
{
    if ( TimerGetLowPowerEnable() == true ) {
        if ( (LowPowerDisableDuringTask == false) && (RtcTimerEventAllowsLowPower == true) ) {
            // Disable IRQ while the MCU is not running on HSE

//          \todo Implement RtcRecoverMcuStatus
//            BoardInitMcu();

        }
    }
}

/*!
 * \brief RTC IRQ Handler on the RTC Alarm
 */
void RTC_IRQHandler( void )
{

}

/*!
 * \brief RTC IRQ Handler on the RTC Seconds interrupt
 */
void RTC_Seconds_IRQHandler( void )
{

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
        _NOP();
    }
}
#endif /* FSL_RTOS_FREE_RTOS */
