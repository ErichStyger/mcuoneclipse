/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file TimersManager.h
* TIMER interface file for the ARM CORTEX-M4 processor
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

#ifndef __TMR_INTERFACE_H__
#define __TMR_INTERFACE_H__

#include "EmbeddedTypes.h"

/*****************************************************************************
******************************************************************************
* Public macros
******************************************************************************
*****************************************************************************/

/*
 * \brief   Enables / Disables the Timer platform component
 * VALID RANGE: TRUE/FALSE
 */
#ifndef gTMR_Enabled_d
#define gTMR_Enabled_d    1
#endif

/*
 * \brief   Enables / Disables the timestamp feature of the timers platform component
 * VALID RANGE: TRUE/FALSE
 */
#ifndef gTimestamp_Enabled_d 
#define gTimestamp_Enabled_d 1
#endif

/*
 * \brief   Enables / Disables the PIT based timestamp feature of the timers platform component
 * VALID RANGE: TRUE/FALSE
 */
#ifndef gTMR_PIT_Timestamp_Enabled_d 
#define gTMR_PIT_Timestamp_Enabled_d  1
#endif


#if gTMR_PIT_Timestamp_Enabled_d
/*
 * \brief   Set this define TRUE if the PIT frequency is an integer number of MHZ.
                The function TMR_PITGetTimestamp will be optimised and will have no jitter.
 * VALID RANGE: TRUE/FALSE
 */
#ifndef gTMR_PIT_FreqMultipleOfMHZ_d 
#define gTMR_PIT_FreqMultipleOfMHZ_d (((CORE_CLOCK_FREQ) % 1000000) == 0)
#endif
#endif

/*
 * \brief   Configures the timer task stack size.
 */
#ifndef gTmrTaskStackSize_c 
#define gTmrTaskStackSize_c 600
#endif

/*
 * \brief   Configures the timer task priority.
 */
#ifndef gTmrTaskPriority_c
#define gTmrTaskPriority_c                 2
#endif

/*
 * \brief   Enable/Disable Low Power Timer
 * VALID RANGE: TRUE/FALSE
 */
#ifndef gTMR_EnableLowPowerTimers_d
#define gTMR_EnableLowPowerTimers_d    (1)
#endif

/*
 * \brief    Enable/Disable Minutes and Seconds Timers
 * VALID RANGE: TRUE/FALSE
 */
#ifndef gTMR_EnableMinutesSecondsTimers_d
#define gTMR_EnableMinutesSecondsTimers_d   (1)
#endif

/*
 * \brief   Number of timers needed by the application
 * VALID RANGE: user defined
 */
#ifndef gTmrApplicationTimers_c
#define gTmrApplicationTimers_c 4
#endif

/*
 * \brief   Number of timers needed by the protocol stack
 * VALID RANGE: user defined
 */
#ifndef gTmrStackTimers_c
#define gTmrStackTimers_c   4
#endif

/*
 * \brief   Total number of timers
 * VALID RANGE: sum of application and stack timers
 */
#ifndef gTmrTotalTimers_c
#define gTmrTotalTimers_c   ( gTmrApplicationTimers_c + gTmrStackTimers_c )
#endif

/*
 * \brief   Typecast the macro argument into milliseconds
 */
#define TmrMilliseconds( n )    ( (tmrTimeInMilliseconds_t) (n) )
   
/*
 * \brief   Converts the macro argument from seconds to microseconds
 */
#define TmrSecondsToMicroseconds( n )   ( (uint64_t) ((n) * 1000000) )
   
/*
 * \brief   Converts the macro argument from microseconds to seconds
 */
#define TmrMicrosecondsToSeconds( n )   ( ((n) + 500000) / 1000000 )

/*
 * \brief   Converts the macro argument (i.e. seconds) into milliseconds
 */
#define TmrSeconds( n )         ( (tmrTimeInMilliseconds_t) (TmrMilliseconds(n) * 1000) )

/*
 * \brief   Converts the macro argument (i.e. minutes) into milliseconds
 */
#define TmrMinutes( n )         ( (tmrTimeInMilliseconds_t) (TmrSeconds(n) * 60) )

/*
 * \brief   Reserved for invalid timer id
 */
#define gTmrInvalidTimerID_c    0xFF

/*
 * \brief   Timer types coded values
 */
#define gTmrSingleShotTimer_c   0x01
#define gTmrIntervalTimer_c     0x02
#define gTmrSetMinuteTimer_c    0x04
#define gTmrSetSecondTimer_c    0x08
#define gTmrLowPowerTimer_c     0x10

/*
 * \brief   Minute timer definition
 */
#define gTmrMinuteTimer_c       ( gTmrSetMinuteTimer_c )

/*
 * \brief   Second timer definition
 */
#define gTmrSecondTimer_c       ( gTmrSetSecondTimer_c )

/*
 * \brief   LP minute/second/millisecond timer definitions
 */
#define gTmrLowPowerMinuteTimer_c           ( gTmrMinuteTimer_c     | gTmrLowPowerTimer_c )
#define gTmrLowPowerSecondTimer_c           ( gTmrSecondTimer_c     | gTmrLowPowerTimer_c )
#define gTmrLowPowerSingleShotMillisTimer_c ( gTmrSingleShotTimer_c | gTmrLowPowerTimer_c )
#define gTmrLowPowerIntervalMillisTimer_c   ( gTmrIntervalTimer_c   | gTmrLowPowerTimer_c )
#define gTmrAllTypes_c                      ( gTmrSingleShotTimer_c | gTmrIntervalTimer_c  | \
                                              gTmrSetMinuteTimer_c  | gTmrSetSecondTimer_c | \
                                              gTmrLowPowerTimer_c)


/*****************************************************************************
******************************************************************************
* Public type definitions
******************************************************************************
*****************************************************************************/

typedef enum tmrErrCode_tag{
    gTmrSuccess_c,
    gTmrInvalidId_c,
    gTmrOutOfRange_c
}tmrErrCode_t;

/*
 * \brief   16-bit timer ticks type definition
 */
typedef uint16_t tmrTimerTicks16_t;

/*
 * \brief   32-bit timer ticks type definition
 */
typedef uint32_t tmrTimerTicks32_t;

/*
 * \brief   64-bit timer ticks type definition
 */
typedef uint64_t tmrTimerTicks64_t;

/*
 * \brief   Times specified in milliseconds (max 0xFFFFFFFF)
 */
typedef uint32_t    tmrTimeInMilliseconds_t;

/*
 * \brief   Times specified in minutes (up to 0xFFFFFFFF/60000)
 */
typedef uint32_t    tmrTimeInMinutes_t;

/*
 * \brief   Times specified in seconds (up to 0xFFFFFFFF/1000)
 */
typedef uint32_t    tmrTimeInSeconds_t;

/*
 * \brief   Timer type
 */
typedef uint8_t     tmrTimerID_t;

/*
 * \brief   Timer type
 */
typedef uint8_t     tmrTimerType_t;

/*
 * \brief   Timer callback function
 */
typedef void ( *pfTmrCallBack_t ) ( void * param );


/*****************************************************************************
******************************************************************************
* Public memory declarations
******************************************************************************
*****************************************************************************/


/*****************************************************************************
******************************************************************************
* Public prototypes
******************************************************************************
*****************************************************************************/

#if gTMR_Enabled_d

/*! -------------------------------------------------------------------------
 * \brief   initialize the timer module
 *---------------------------------------------------------------------------*/
void TMR_Init
(
    void
);

/*! -------------------------------------------------------------------------
 * \brief     This function is called when the clock is changed
 * \param[in] clkKhz (uint32_t) - new clock
 *---------------------------------------------------------------------------*/
void TMR_NotifyClkChanged
(
    void
);

/*! -------------------------------------------------------------------------
 * \brief   allocate a timer
 * \return  timer ID
 *---------------------------------------------------------------------------*/
tmrTimerID_t TMR_AllocateTimer
(
    void
);

/*! -------------------------------------------------------------------------
 * \brief   Check if all timers except the LP timers are OFF.
 * \return  TRUE if there are no active non-low power timers, FALSE otherwise
 *---------------------------------------------------------------------------*/
bool_t TMR_AreAllTimersOff
(
    void
);

/*! -------------------------------------------------------------------------
 * \brief     Free a timer
 * \param[in] timerID - the ID of the timer
 *
 * \return the error code
 * \details   Safe to call even if the timer is running.
 *            Harmless if the timer is already free.
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_FreeTimer
(
    tmrTimerID_t timerID
);

/*! -------------------------------------------------------------------------
 * \brief     Check if a specified timer is active
 * \param[in] timerID - the ID of the timer
 * \return    TRUE if the timer (specified by the timerID) is active,
 *            FALSE otherwise
 *---------------------------------------------------------------------------*/
bool_t TMR_IsTimerActive
(
    tmrTimerID_t timerID
);

/*! -------------------------------------------------------------------------
 * \brief     Check if a specified timer is ready
 * \param[in] timerID - the ID of the timer
 * \return    TRUE if the timer (specified by the timerID) is ready,
 *            FALSE otherwise
 *---------------------------------------------------------------------------*/
bool_t TMR_IsTimerReady
(
    tmrTimerID_t timerID
);

/*! -------------------------------------------------------------------------
 * \brief     Returns the remaining time until timeout, for the specified
 *            timer
 * \param[in] timerID - the ID of the timer
 * \return    remaining time in milliseconds until timer timeouts.
 *---------------------------------------------------------------------------*/
uint32_t TMR_GetRemainingTime
(
    tmrTimerID_t tmrID
);

/*! -------------------------------------------------------------------------
 * \brief     Returns the remaining time until first timeout, for the specified
 *            timer types
 * \param[in] timerType mask of timer types 
 * \return    remaining time in milliseconds until first timer timeouts.
 *---------------------------------------------------------------------------*/
uint32_t TMR_GetFirstExpireTime
(
tmrTimerType_t timerType
);

/*! -------------------------------------------------------------------------
 * \brief     Start a specified timer
 *
 * \param[in] timerId - the ID of the timer
 * \param[in] timerType - the type of the timer
 * \param[in] timeInMilliseconds - time expressed in millisecond units
 * \param[in] pfTmrCallBack - callback function
 * \param[in] param - parameter to callback function
 *
 * \return    the error code
 * \details   When the timer expires, the callback function is called in
 *            non-interrupt context. If the timer is already running when
 *            this function is called, it will be stopped and restarted.
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartTimer
(
    tmrTimerID_t timerID,
    tmrTimerType_t timerType,
    tmrTimeInMilliseconds_t timeInMilliseconds,
    pfTmrCallBack_t callback,
    void *param
);

/*! -------------------------------------------------------------------------
 * \brief   Start a low power timer. When the timer goes off, call the
 *              callback function in non-interrupt context.
 *              If the timer is running when this function is called, it will
 *              be stopped and restarted.
 *              Start the timer with the following timer types:
 *                          - gTmrLowPowerMinuteTimer_c
 *                          - gTmrLowPowerSecondTimer_c
 *                          - gTmrLowPowerSingleShotMillisTimer_c
 *                          - gTmrLowPowerIntervalMillisTimer_c
 *              The MCU can enter in low power if there are only active low
 *              power timers.
 *
 * \param[in]  timerId - the ID of the timer
 * \param[in]  timerType - the type of the timer
 * \param[in]  time - time in milliseconds
 * \param[in]  pfTmrCallBack - callback function
 * \param[in]  param - parameter to callback function
 *
 * \return     the error code
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartLowPowerTimer
(
    tmrTimerID_t timerId,
    tmrTimerType_t timerType,
    uint32_t time,
    pfTmrCallBack_t callback,
    void *param
);

/*! -------------------------------------------------------------------------
 * \brief     Starts a low power minutes timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timeInMinutes - time expressed in minutes
 * \param[in] pfTmrCallBack - callback function
 * \param[in] param - parameter to callback function
 *
 * \details Customized form of TMR_StartLowPowerTimer(). This is a single shot timer.
 *        There are no interval minute timers.
 *---------------------------------------------------------------------------*/
#if gTMR_EnableMinutesSecondsTimers_d
tmrErrCode_t TMR_StartLowPowerMinuteTimer
(
    tmrTimerID_t timerId,
    tmrTimeInMinutes_t timeInMinutes,
    pfTmrCallBack_t callback,
    void *param
);
#endif

/*! -------------------------------------------------------------------------
 * \brief     Starts a low power seconds timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timeInSeconds - time expressed in seconds
 * \param[in] pfTmrCallBack - callback function
 *
 * \details Customized form of TMR_StartLowPowerTimer(). This is a single shot timer.
 *        There are no interval seconds timers.
 *---------------------------------------------------------------------------*/
#if gTMR_EnableMinutesSecondsTimers_d
tmrErrCode_t TMR_StartLowPowerSecondTimer
(
    tmrTimerID_t timerId,
    tmrTimeInSeconds_t timeInSeconds,
    pfTmrCallBack_t callback,
    void *param
);
#endif

/*! -------------------------------------------------------------------------
 * \brief   Starts a minutes timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timeInMinutes - time expressed in minutes
 * \param[in] callback - callback function
 * \param[in] param - parameter to callback function
 *
 * \return    the error code
 * \details   Customized form of TMR_StartTimer(). This is a single shot timer.
 *        There are no interval minute timers.
 *---------------------------------------------------------------------------*/
#if gTMR_EnableMinutesSecondsTimers_d
tmrErrCode_t TMR_StartMinuteTimer
(
    tmrTimerID_t timerId,
    tmrTimeInMinutes_t timeInMinutes,
    pfTmrCallBack_t callback,
    void *param
);
#endif

/*! -------------------------------------------------------------------------
 * \brief   Starts a seconds timer
 * \param[in] timerID - the ID of the timer
 * \param[in] timeInSeconds - time expressed in seconds
 * \param[in] callback - callback function
 * \param[in] param - parameter to callback function
 *
 * \return    the error code
 * \details   Customized form of TMR_StartTimer(). This is a single shot timer.
 *        There are no interval seconds timers.
 *---------------------------------------------------------------------------*/
#if gTMR_EnableMinutesSecondsTimers_d
tmrErrCode_t TMR_StartSecondTimer
(
    tmrTimerID_t timerId,
    tmrTimeInSeconds_t timeInSeconds,
    pfTmrCallBack_t callback,
    void *param
);
#endif

/*! -------------------------------------------------------------------------
 * \brief     Starts an interval count timer
 *
 * \param[in] timerID - the ID of the timer
 * \param[in] timeInMilliseconds - time expressed in milliseconds
 * \param[in] callback - callback function
 * \param[in] param - parameter to callback function
 *
 * \return    the error code
 * \details   Customized form of TMR_StartTimer()
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartIntervalTimer
(
    tmrTimerID_t timerID,
    tmrTimeInMilliseconds_t timeInMilliseconds,
    pfTmrCallBack_t callback,
    void *param
);

/*! -------------------------------------------------------------------------
 * \brief     Starts an single-shot timer
 *
 * \param[in] timerID - the ID of the timer
 * \param[in] timeInMilliseconds - time expressed in milliseconds
 * \param[in] callback - callback function
 * \param[in] param - parameter to callback function
 *
 * \return    the error code
 * \details   Customized form of TMR_StartTimer()
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartSingleShotTimer
(
    tmrTimerID_t timerID,
    tmrTimeInMilliseconds_t timeInMilliseconds,
    pfTmrCallBack_t callback,
    void *param
);

/*! -------------------------------------------------------------------------
 * \brief     Stop a timer
 * \param[in] timerID - the ID of the timer
 *
 * \return   the error code
 * \details  Associated timer callback function is not called, even if the timer
 *           expires. Does not frees the timer. Safe to call anytime, regardless
 *           of the state of the timer.
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StopTimer
(
    tmrTimerID_t timerID
);


/*! -------------------------------------------------------------------------
 * \brief     Enable the specified timer
 * \param[in] tmrID - the timer ID
 *---------------------------------------------------------------------------*/
void TMR_EnableTimer
(
    tmrTimerID_t tmrID
);

/*! -------------------------------------------------------------------------
 * \brief   This function is called by Low Power module;
 *          Also this function stops the hardware timer.
 * \return  TMR ticks that wasn't counted before entering in sleep
 *---------------------------------------------------------------------------*/
uint16_t TMR_NotCountedTicksBeforeSleep
(
    void
);

/*! -------------------------------------------------------------------------
 * \brief      This function is called by the Low Power module
 *             each time the MCU wakes up.
 * \param[in]  sleepDurationTmrTicks
 *
 *
 *---------------------------------------------------------------------------*/
void TMR_SyncLpmTimers
(
    uint32_t sleepDurationTmrTicks
);

/*! -------------------------------------------------------------------------
 * \brief   This function is called by the Low Power module
 * each time the MCU wakes up after low power timers synchronisation.
 *---------------------------------------------------------------------------*/
void TMR_MakeTMRThreadReady
(
 void   
);

/*! -------------------------------------------------------------------------
 * \brief     Convert milliseconds to ticks
 * \param[in] milliseconds
 * \return    tmrTimerTicks64_t - ticks number
 *
 *---------------------------------------------------------------------------*/
tmrTimerTicks64_t TmrTicksFromMilliseconds
(
    tmrTimeInMilliseconds_t milliseconds
);

/*! -------------------------------------------------------------------------
 * \brief   Returns the frequency in Hz of the TMR counter
 *---------------------------------------------------------------------------*/
uint32_t TMR_GetTimerFreq(void);

/*! -------------------------------------------------------------------------
 * \brief   Initialize the TMR Time-stamp module
 *---------------------------------------------------------------------------*/
void TMR_TimeStampInit(void);

/*! -------------------------------------------------------------------------
 * \brief   Get a time-stamp value
 *---------------------------------------------------------------------------*/
uint64_t TMR_GetTimestamp(void);

/*! -------------------------------------------------------------------------
 * \brief   Reserve a minute timer
 * \return   gTmrInvalidTimerID_c if there are no timers available
 *---------------------------------------------------------------------------*/
#define TMR_AllocateMinuteTimer() TMR_AllocateTimer()

/*! -------------------------------------------------------------------------
 * \brief   Reserve a second timer
 * \return   gTmrInvalidTimerID_c if there are no timers available
 *---------------------------------------------------------------------------*/
#define TMR_AllocateSecondTimer() TMR_AllocateTimer()

/*! -------------------------------------------------------------------------
 * \brief   Free a minute timer. Safe to call even if the timer is running
 * \param[in] timerID
 *---------------------------------------------------------------------------*/
#define TMR_FreeMinuteTimer(timerID) TMR_FreeTimer(timerID)

/*! -------------------------------------------------------------------------
 * \brief   Free a second timer. Safe to call even if the timer is running
 * \param[in] timerID
 *---------------------------------------------------------------------------*/
#define TMR_FreeSecondTimer(timerID) TMR_FreeTimer(timerID)

/*! -------------------------------------------------------------------------
 * \brief     Stop a timer started by TMR_StartMinuteTimer()
 * \param[in] timerID
 *---------------------------------------------------------------------------*/
#define TMR_StopMinuteTimer(timerID)  TMR_StopTimer(timerID)

/*! -------------------------------------------------------------------------
 * \brief     stop a timer started by TMR_StartSecondTimer()
 * \param[in] timerID
 *---------------------------------------------------------------------------*/
#define TMR_StopSecondTimer(timerID)  TMR_StopTimer(timerID)

#else /* stub functions */

#define TMR_Init()
#define TMR_NotifyClkChanged()
#define TMR_AllocateTimer()         gTmrInvalidTimerID_c
#define TMR_AreAllTimersOff()       1
#define TMR_FreeTimer(timerID)      0
#define TMR_IsTimerActive(timerID)  0
#define TMR_StartTimer(timerID,timerType,timeInMilliseconds, pfTimerCallBack, param) 0
#define TMR_StartLowPowerTimer(timerId,timerType,timeIn,pfTmrCallBack,param) 0
#if gTMR_EnableMinutesSecondsTimers_d
#define TMR_StartMinuteTimer(timerId,timeInMinutes,pfTmrCallBack,param) 0
#endif
#if gTMR_EnableMinutesSecondsTimers_d
#define TMR_StartSecondTimer(timerId,timeInSeconds,pfTmrCallBack,param) 0
#endif
#define TMR_StartIntervalTimer(timerID,timeInMilliseconds,pfTimerCallBack,param) 0
#define TMR_StartSingleShotTimer(timerID,timeInMilliseconds,pfTimerCallBack,param) 0
#define TMR_StopTimer(timerID)              0
#define TMR_Thread(events)
#define TMR_EnableTimer(tmrID)
#define TMR_NotCountedTicksBeforeSleep()    0
#define TMR_SyncLpmTimers(sleepDurationTmrTicks)
#define TMR_MakeTMRThreadReady()
#define TmrTicksFromMilliseconds(milliseconds)      0
#define TMR_GetTimerFreq()                          0
#define TMR_GetRemainingTime(tmrID)                 0
#define TMR_GetFirstExpireTime                      0xFFFFFFFF
#define TMR_AllocateMinuteTimer()     TMR_AllocateTimer()
#define TMR_AllocateSecondTimer()     TMR_AllocateTimer()
#define TMR_FreeMinuteTimer(timerID)  TMR_FreeTimer(timerID)
#define TMR_FreeSecondTimer(timerID)  TMR_FreeTimer(timerID)
#define TMR_StopMinuteTimer(timerID)  TMR_StopTimer(timerID)
#define TMR_StopSecondTimer(timerID)  TMR_StopTimer(timerID)
#define TMR_TimeStampInit()
#define TMR_GetTimestamp()                          0

#endif /* gTMR_Enabled_d */

   
/*! -------------------------------------------------------------------------
 * \brief   Get the state of the RTC oscillator
 * \return  TRUE if the RTC oscillator is on
 *---------------------------------------------------------------------------*/
bool_t TMR_RTCIsOscStarted(void);

#if gTimestamp_Enabled_d

/*! -------------------------------------------------------------------------
 * \brief   initialize the RTC part of the timer module
 *---------------------------------------------------------------------------*/
void TMR_RTCInit(void);

/*! -------------------------------------------------------------------------
 * \brief   Returns the absolute time at the moment of the call.
 * \return  Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t TMR_RTCGetTimestamp(void);

/*! -------------------------------------------------------------------------
 * \brief     Sets the absolute time.
 * \param[in] microseconds
 *---------------------------------------------------------------------------*/
void TMR_RTCSetTime(uint64_t microseconds);

/*! -------------------------------------------------------------------------
 * \brief     Sets the alarm absolute time in seconds.
 * \param[in] seconds Time in seconds for the alarm. 
 * \param[in] callback function pointer. 
 * \param[in] param Parameter for callback.
 *---------------------------------------------------------------------------*/
void TMR_RTCSetAlarm(uint64_t seconds, pfTmrCallBack_t callback, void *param);

/*! -------------------------------------------------------------------------
 * \brief     Sets the alarm relative time in seconds.
 * \param[in] seconds number of seconds until the alarm. 
 * \param[in] callback function pointer. 
 * \param[in] param Parameter for callback.
 *---------------------------------------------------------------------------*/
void TMR_RTCSetAlarmRelative(uint32_t seconds, pfTmrCallBack_t callback, void *param);

#else /*stub functions*/

#define TMR_RTCInit()
#define TMR_RTCGetTimestamp() 0
#define TMR_RTCSetTime()
#define TMR_RTCSetAlarm()
#define TMR_RTCSetAlarmRelative()

#endif /*gTimestamp_Enabled_d*/

#if gTMR_PIT_Timestamp_Enabled_d
/*! -------------------------------------------------------------------------
 * \brief   initialize the PIT part of the timer module
 *---------------------------------------------------------------------------*/
void TMR_PITInit(void);

/*! -------------------------------------------------------------------------
 * \brief   Returns the absolute time at the moment of the call.
 * \return   Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t TMR_PITGetTimestamp(void);

#else
#define TMR_PITInit()
#define TMR_PITGetTimestamp() 0
#endif


#endif /* #ifndef __TMR_INTERFACE_H__ */

/*****************************************************************************
 *                               <<< EOF >>>                                 *
 *****************************************************************************/
