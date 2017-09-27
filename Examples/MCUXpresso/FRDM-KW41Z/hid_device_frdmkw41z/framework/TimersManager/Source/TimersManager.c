/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file TimersManager.c
* TIMER implementation file for the ARM CORTEX-M4 processor
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

#include "EmbeddedTypes.h"
#include "TimersManagerInternal.h"
#include "TimersManager.h"
#include "Panic.h"
#include "TMR_Adapter.h"

#include "fsl_os_abstraction.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "pin_mux.h"


/*****************************************************************************
******************************************************************************
* Private macros
******************************************************************************
*****************************************************************************/
#define mTmrDummyEvent_c (1<<16)

/*****************************************************************************
******************************************************************************
* Public memory declarations
******************************************************************************
*****************************************************************************/
extern const uint8_t gUseRtos_c;

/*****************************************************************************
 *****************************************************************************
 * Private prototypes
 *****************************************************************************
 *****************************************************************************/

#if defined(FWK_SMALL_RAM_CONFIG)
void FwkInit(void);
#endif

#if gTMR_Enabled_d

/*! -------------------------------------------------------------------------
 * \brief     RETURNs the timer status
 * \param[in] timerID - the timer ID
 * \return    see definition of tmrStatus_t
 *---------------------------------------------------------------------------*/
static tmrStatus_t TMR_GetTimerStatus
(
    tmrTimerID_t timerID
);

/*! -------------------------------------------------------------------------
 * \brief     Set the timer status
 * \param[in] timerID - the timer ID
 * \param[in] status - the status of the timer
 *---------------------------------------------------------------------------*/
static void TMR_SetTimerStatus
(
    tmrTimerID_t timerID,
    tmrStatus_t status
);

/*! -------------------------------------------------------------------------
 * \brief     RETURNs the timer type
 * \param[in] timerID - the timer ID
 * \return    see definition of tmrTimerType_t
 *---------------------------------------------------------------------------*/
static tmrTimerType_t TMR_GetTimerType
(
    tmrTimerID_t timerID
);

/*! -------------------------------------------------------------------------
 * \brief     Set the timer type
 * \param[in] timerID - the timer ID
 * \param[in] type - timer type
 *---------------------------------------------------------------------------*/
static void TMR_SetTimerType
(
    tmrTimerID_t timerID,
    tmrTimerType_t type
);



/*! -------------------------------------------------------------------------
 * \brief Function called by driver ISR on channel match in interrupt context.
 *---------------------------------------------------------------------------*/
static void StackTimer_ISR
(
    void
);

/*! -------------------------------------------------------------------------
 * \brief     Timer thread.
 *            Called by the kernel when the timer ISR posts a timer event.
 * \param[in] param - User parameter to timer thread; not used.
 *---------------------------------------------------------------------------*/

void TMR_Task
(
osaTaskParam_t param
);
#endif /*gTMR_Enabled_d*/


#if gTimestamp_Enabled_d

/*! -------------------------------------------------------------------------
 * \brief Function called by driver ISR on RTC alarm in interrupt context.
 *---------------------------------------------------------------------------*/
void TMR_RTCAlarmNotify
(
    void
);

#endif /*gTimestamp_Enabled_d*/


/*****************************************************************************
 *****************************************************************************
 * Private memory definitions
 *****************************************************************************
 *****************************************************************************/

#if gTMR_Enabled_d

/*
 * \brief The previous time in ticks when the counter register was read
 * VALUES: 0..65535
 */
static tmrTimerTicks16_t previousTimeInTicks;

/*
 * \brief  Count to maximum (0xffff - 2*4ms(in ticks)), to be sure that
 * the currentTimeInTicks will never roll over previousTimeInTicks in the
 * TMR_Task(); A thread have to be executed at most in 4ms.
 * VALUES: 0..65535
 */
static uint16_t mMaxToCountDown_c;

/*
 * \brief  Ticks for 4ms. The TMR_Task()event will not be issued faster than 4ms
 * VALUES: uint16_t range
 */
static uint16_t mTicksFor4ms;

/*
 * \brief  The counter frequency in hz.
 * VALUES: see definition
 */
static uint32_t mCounterFreqHz;

/*
 * \brief  Main timer table. All allocated timers are stored here.
 *               A timer's ID is it's index in this table.
 * VALUES: see definition
 */
static tmrTimerTableEntry_t maTmrTimerTable[gTmrTotalTimers_c];

/*
 * \brief timer status stable. Making the single-byte-per-timer status
 *              table a separate array saves a bit of code space.
 *              If an entry is == 0, the timer is not allocated.
 * VALUES: see definition
 */
static tmrStatus_t maTmrTimerStatusTable[gTmrTotalTimers_c];

/*
 * \brief Number of Active timers (without low power capability)
 *              the MCU can not enter low power if numberOfActiveTimers!=0
 * VALUES: 0..255
 */
static uint8_t numberOfActiveTimers = 0;

/*
 * \brief Number of low power active timer.
 *              The MCU can enter in low power if more low power timers are active
 * VALUES:
 */
static uint8_t numberOfLowPowerActiveTimers = 0;

#define IncrementActiveTimerNumber(type)  (((type) & gTmrLowPowerTimer_c) \
                                          ?(++numberOfLowPowerActiveTimers) \
                                          :(++numberOfActiveTimers) )
#define DecrementActiveTimerNumber(type)  (((type) & gTmrLowPowerTimer_c) \
                                          ?(--numberOfLowPowerActiveTimers) \
                                          :(--numberOfActiveTimers) )

/*
 * \brief Flag if the hardware timer is running or not
 * VALUES: TRUE/FALSE
 */
static bool_t timerHardwareIsRunning = FALSE;



#if defined(FWK_SMALL_RAM_CONFIG)
extern osaEventId_t  gFwkCommonEventId;
#define mTimerThreadEventId gFwkCommonEventId

#else
/*
 * \brief Defines the timer thread's stack
 */
OSA_TASK_DEFINE( TMR_Task, gTmrTaskPriority_c, 1, gTmrTaskStackSize_c, FALSE );

/*
 * \brief The OS threadId for TMR task.
 */
static osaEventId_t        mTimerThreadEventId;
#endif
#endif /*gTMR_Enabled_d*/


#if gTimestamp_Enabled_d

/*
 * \brief Holds time offset in microseconds, used to calculate the date
 */
static volatile uint64_t gRTCTimeOffset;

/*
 * \brief Holds time prescaler offset in ticks, used to calculate the date
 */
static volatile uint16_t gRTCPrescalerOffset;

/*
 * \brief Callback for the alarm.
 */
static pfTmrCallBack_t gRTCAlarmCallback;

/*
 * \brief Parameter for the alarm callback.
 */
static void *gRTCAlarmCallbackParam;

/*
 * \brief signals the state of the RTC.
 */
static uint8_t gRTCInitFlag = 0;
#endif /*gTimestamp_Enabled_d*/


#if gTMR_PIT_Timestamp_Enabled_d
PIT_Type * mPitBase[] = PIT_BASE_PTRS;
static uint8_t gPITInitFlag = FALSE;
#if FSL_FEATURE_PIT_TIMER_COUNT < 3
static void TMR_PIT_ISR(void);
static uint32_t mPIT_TimestampHigh;
#endif
#endif

/*****************************************************************************
******************************************************************************
* Private functions
******************************************************************************
*****************************************************************************/

#if gTMR_Enabled_d

/*! -------------------------------------------------------------------------
* \brief     Returns the timer status
* \param[in] timerID - the timer ID
* \return    see definition of tmrStatus_t
*---------------------------------------------------------------------------*/
static tmrStatus_t TMR_GetTimerStatus
(
    tmrTimerID_t timerID
)
{
    return maTmrTimerStatusTable[timerID] & mTimerStatusMask_c;
}

/*! -------------------------------------------------------------------------
* \brief     Set the timer status
* \param[in] timerID - the timer ID
* \param[in] status - the status of the timer
*---------------------------------------------------------------------------*/
static void TMR_SetTimerStatus
(
    tmrTimerID_t timerID,
    tmrStatus_t status
)
{
    maTmrTimerStatusTable[timerID] = (tmrStatus_t)(maTmrTimerStatusTable[timerID] & (tmrStatus_t)(~mTimerStatusMask_c)) | status;
}

/*! -------------------------------------------------------------------------
* \brief     Returns the timer type
* \param[in] timerID - the timer ID
* \return    see definition of tmrTimerType_t
*---------------------------------------------------------------------------*/
static tmrTimerType_t TMR_GetTimerType
(
    tmrTimerID_t timerID
)
{
    return maTmrTimerStatusTable[timerID] & mTimerType_c;
}

/*! -------------------------------------------------------------------------
* \brief     Set the timer type
* \param[in] timerID - the timer ID
* \param[in] type - timer type
*---------------------------------------------------------------------------*/
static void TMR_SetTimerType
(
    tmrTimerID_t timerID,
    tmrTimerType_t type
)
{
    maTmrTimerStatusTable[timerID] = (tmrStatus_t)(maTmrTimerStatusTable[timerID] & (tmrStatus_t)(~mTimerType_c)) | type;
}

#endif /*gTMR_Enabled_d*/


#if gTimestamp_Enabled_d
/*! -------------------------------------------------------------------------
 * \brief Function called by driver ISR on RTC alarm in interrupt context.
 *---------------------------------------------------------------------------*/
void TMR_RTCAlarmNotify
(
    void
)
{
    /* Disable alarm interrupt */
    RTC->IER &= ~RTC_IER_TAIE_MASK;
    /* Clear Interrupt Flag */
    RTC->TAR = RTC->TAR;
    
    if( gRTCAlarmCallback != NULL )
    {
        gRTCAlarmCallback(gRTCAlarmCallbackParam);
    }
}

#endif /*gTimestamp_Enabled_d*/

#if (gTMR_PIT_Timestamp_Enabled_d) && (FSL_FEATURE_PIT_TIMER_COUNT < 3)
static void TMR_PIT_ISR(void)
{
    mPitBase[gTmrPitInstance_c]->CHANNEL[1].TFLG = PIT_TFLG_TIF_MASK;
    mPIT_TimestampHigh--;
}

#endif

/*****************************************************************************
******************************************************************************
* Public functions
******************************************************************************
*****************************************************************************/

#if gTMR_Enabled_d
/*! -------------------------------------------------------------------------
 *
 * \brief     Convert milliseconds to ticks
 * \param[in] milliseconds
 * \return    tmrTimerTicks64_t - ticks number
 *
 *---------------------------------------------------------------------------*/
tmrTimerTicks64_t TmrTicksFromMilliseconds
(
    tmrTimeInMilliseconds_t milliseconds
)
{
  return (tmrTimerTicks64_t)milliseconds * mCounterFreqHz / 1000;
}

/*! -------------------------------------------------------------------------
 * \brief initialize the timer module
 *---------------------------------------------------------------------------*/
void TMR_Init
(
    void
)
{
    static uint8_t initialized = FALSE;

    /* Check if TMR is already initialized */
    if( !initialized )
    {
        initialized = TRUE;
        
        StackTimer_Init(StackTimer_ISR);

        TMR_NotifyClkChanged();

#if defined(FWK_SMALL_RAM_CONFIG)
        FwkInit();
#else
        osaTaskId_t timerThreadId;    
        
        mTimerThreadEventId = OSA_EventCreate(TRUE);
        
        if( NULL == mTimerThreadEventId )
        {
            panic( 0, (uint32_t)TMR_Init, 0, 0 );
        }
        else
        {
            timerThreadId = OSA_TaskCreate(OSA_TASK(TMR_Task), NULL);
            
            if( NULL == timerThreadId )
            {
                panic( 0, (uint32_t)TMR_Init, 0, 0 );
            }
        }
#endif
    }
}

/*! -------------------------------------------------------------------------
 * \brief This function is called when the clock is changed
 * PARAMETERS: IN: clkKhz (uint32_t) - new clock
 *---------------------------------------------------------------------------*/
void TMR_NotifyClkChanged
(
    void
)
{
    mCounterFreqHz = (uint32_t)((StackTimer_GetInputFrequency()));
    /* Clock was changed, so calculate again  mMaxToCountDown_c.
    Count to maximum (0xffff - 2*4ms(in ticks)), to be sure that the currentTimeInTicks
    will never roll over previousTimeInTicks in the TMR_Task() */
    mMaxToCountDown_c = 0xFFFF - TmrTicksFromMilliseconds(8);
    /* The TMR_Task()event will not be issued faster than 4ms*/
    mTicksFor4ms = TmrTicksFromMilliseconds(4);
}

/*! -------------------------------------------------------------------------
 * \brief   allocate a timer
 * \return  timer ID
 *---------------------------------------------------------------------------*/
tmrTimerID_t TMR_AllocateTimer
(
    void
)
{
    uint32_t i;
    tmrTimerID_t id = gTmrInvalidTimerID_c;

    for (i = 0; i < NumberOfElements(maTmrTimerTable); ++i)
    {
        if (!TMR_IsTimerAllocated(i))
        {
            TMR_SetTimerStatus(i, mTmrStatusInactive_c);
            id = i;
            break;
        }
   }

   return id;
}

/*! -------------------------------------------------------------------------
 * \brief  Check if all timers except the LP timers are OFF.
 * \return TRUE if there are no active non-low power timers, FALSE otherwise
 *---------------------------------------------------------------------------*/
bool_t TMR_AreAllTimersOff
(
    void
)
{
    return !numberOfActiveTimers;
}

/*! -------------------------------------------------------------------------
 * \brief     Free a timer
 * \param[in] timerID - the ID of the timer
 * \details   Safe to call even if the timer is running.
 *            Harmless if the timer is already free.
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_FreeTimer
(
    tmrTimerID_t timerID
)
{
    tmrErrCode_t status;

    status = TMR_StopTimer(timerID);

    if( status == gTmrSuccess_c )
    {
        TMR_MarkTimerFree(timerID);
    }

    return gTmrSuccess_c;
}

/*! -------------------------------------------------------------------------
 * \brief Function called by driver ISR on channel match in interrupt context.
 *---------------------------------------------------------------------------*/
static void StackTimer_ISR(void)
{
    StackTimer_ClearIntFlag();
    (void)OSA_EventSet(mTimerThreadEventId, mTmrDummyEvent_c);
}

/*! -------------------------------------------------------------------------
 * \brief     Check if a specified timer is active
 * \param[in] timerID - the ID of the timer
 * \return    TRUE if the timer (specified by the timerID) is active,
 *            FALSE otherwise
 *---------------------------------------------------------------------------*/
bool_t TMR_IsTimerActive
(
    tmrTimerID_t timerID
)
{
    return TMR_GetTimerStatus(timerID) == mTmrStatusActive_c;
}

/*! -------------------------------------------------------------------------
 * \brief     Check if a specified timer is ready
 * \param[in] timerID - the ID of the timer
 * \return    TRUE if the timer (specified by the timerID) is ready,
 *            FALSE otherwise
 *---------------------------------------------------------------------------*/
bool_t TMR_IsTimerReady
(
    tmrTimerID_t timerID
)
{
    return TMR_GetTimerStatus(timerID) == mTmrStatusReady_c;
}

/*! -------------------------------------------------------------------------
 * \brief Returns the remaining time until timeout, for the specified timer
 * \param[in] timerID - the ID of the timer
 * \return    remaining time in milliseconds until next timer timeout
 *---------------------------------------------------------------------------*/
uint32_t TMR_GetRemainingTime
(
    tmrTimerID_t tmrID
)
{
    tmrTimerTicks16_t currentTime, elapsedRemainingTicks;
    uint32_t remainingTime, freq = mCounterFreqHz;
    
    if( (tmrID >= gTmrTotalTimers_c) || (!TMR_IsTimerAllocated(tmrID)) ||
        (maTmrTimerTable[tmrID].remainingTicks == 0) )
    {
        remainingTime = 0;
    }
    else
    {
        TmrIntDisableAll();
        
        currentTime = StackTimer_GetCounterValue();
        
        if(currentTime < maTmrTimerTable[tmrID].timestamp)
        {
            currentTime += 0xFFFF;
        }
        
        elapsedRemainingTicks = currentTime - maTmrTimerTable[tmrID].timestamp;
        
        if(elapsedRemainingTicks > maTmrTimerTable[tmrID].remainingTicks)
        {
            remainingTime = 1;
        }
        else
        {
            remainingTime = ((uint64_t)(maTmrTimerTable[tmrID].remainingTicks - elapsedRemainingTicks) * 1000 + freq - 1) / freq;
        }
        
        TmrIntRestoreAll();
    }
    
    return remainingTime;
}

/*! -------------------------------------------------------------------------
 * \brief     Returns the remaining time until first timeout, for the
 *            specified timer types
 * \param[in] timerType mask of timer types 
 * \return    remaining time in milliseconds until first timer timeouts.
 *---------------------------------------------------------------------------*/
uint32_t TMR_GetFirstExpireTime(tmrTimerType_t timerType)
{
    uint32_t min = 0xFFFFFFFF;
    uint32_t remainingTime;
    uint32_t timerID;
    
    for( timerID = 0; timerID < NumberOfElements(maTmrTimerTable); ++timerID )
    {
        if( TMR_IsTimerActive(timerID) && ((timerType & TMR_GetTimerType(timerID)) > 0) )
        {
            remainingTime = TMR_GetRemainingTime(timerID);

            if( remainingTime < min )
            {
                min = remainingTime;
            }
        }
    }
    
    return min;
}

/*! -------------------------------------------------------------------------
 * \brief Start a specified timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timerType - the type of the timer
 * \param[in] timeInMilliseconds - time expressed in millisecond units
 * \param[in] pfTmrCallBack - callback function
 * \param[in] param - parameter to callback function
 *
 * \details When the timer expires, the callback function is called in
 *        non-interrupt context. If the timer is already running when
 *        this function is called, it will be stopped and restarted.
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartTimer
(
    tmrTimerID_t timerID,
    tmrTimerType_t timerType,
    tmrTimeInMilliseconds_t timeInMilliseconds,
    pfTmrCallBack_t callback,
    void *param
)
{
    tmrErrCode_t status;
    tmrTimerTicks64_t intervalInTicks;

    /* Stopping an already stopped timer is harmless. */
    status = TMR_StopTimer(timerID);

    if( status == gTmrSuccess_c )
    {
        intervalInTicks = TmrTicksFromMilliseconds(timeInMilliseconds);
        maTmrTimerTable[timerID].timestamp = StackTimer_GetCounterValue();
        
        if( !intervalInTicks )
        {
            intervalInTicks = 1;
        }
        
        TMR_SetTimerType(timerID, timerType);
        maTmrTimerTable[timerID].intervalInTicks = intervalInTicks;
        maTmrTimerTable[timerID].remainingTicks = intervalInTicks;
        maTmrTimerTable[timerID].pfCallBack = callback;
        maTmrTimerTable[timerID].param = param;
        
        /* Enable timer, the timer thread will do the rest of the work. */
        TMR_EnableTimer(timerID);
    }

    return status;
}

/*! -------------------------------------------------------------------------
 * \brief Start a low power timer. When the timer goes off, call the
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
 * \param[in] timerId - the ID of the timer
 * \param[in] timerType - the type of the timer
 * \param[in] time - time in milliseconds
 * \param[in] pfTmrCallBack - callback function
 * \param[in] param - parameter to callback function
 * \return type/DESCRIPTION
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartLowPowerTimer
(
    tmrTimerID_t timerId,
    tmrTimerType_t timerType,
    uint32_t time,
    pfTmrCallBack_t callback,
    void *param
)
{
#if(gTMR_EnableLowPowerTimers_d)
    return TMR_StartTimer(timerId, timerType | gTmrLowPowerTimer_c, time, callback, param);
#else
    timerId = timerId;
    timerType = timerType;
    timeIn = timeIn;
    callback = callback;
    param = param;
    return gTmrSuccess_c;
#endif
}

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
)
{
    return TMR_StartLowPowerTimer(timerId, gTmrMinuteTimer_c, TmrMinutes(timeInMinutes), callback, param);
}
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
)
{
    return TMR_StartLowPowerTimer(timerId, gTmrSecondTimer_c, TmrSeconds(timeInSeconds), callback, param);
}
#endif

/*! -------------------------------------------------------------------------
 * \brief     Starts a minutes timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timeInMinutes - time expressed in minutes
 * \param[in] pfTmrCallBack - callback function
 * \param[in] param - parameter to callback function
 *
 * \details Customized form of TMR_StartTimer(). This is a single shot timer.
 *        There are no interval minute timers.
 *---------------------------------------------------------------------------*/
#if gTMR_EnableMinutesSecondsTimers_d
tmrErrCode_t TMR_StartMinuteTimer
(
    tmrTimerID_t timerId,
    tmrTimeInMinutes_t timeInMinutes,
    pfTmrCallBack_t callback,
    void *param
)
{
    return TMR_StartTimer(timerId, gTmrMinuteTimer_c, TmrMinutes(timeInMinutes), callback, param);
}
#endif

/*! -------------------------------------------------------------------------
 * \brief     Starts a seconds timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timeInSeconds - time expressed in seconds
 * \param[in] pfTmrCallBack - callback function
 *
 * \details Customized form of TMR_StartTimer(). This is a single shot timer.
 *        There are no interval seconds timers.
 *---------------------------------------------------------------------------*/
#if gTMR_EnableMinutesSecondsTimers_d
tmrErrCode_t TMR_StartSecondTimer
(
    tmrTimerID_t timerId,
    tmrTimeInSeconds_t timeInSeconds,
    pfTmrCallBack_t callback,
    void *param
)
{
    return TMR_StartTimer(timerId, gTmrSecondTimer_c, TmrSeconds(timeInSeconds), callback, param);
}
#endif

/*! -------------------------------------------------------------------------
 * \brief     Starts an interval count timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timeInMilliseconds - time expressed in milliseconds
 * \param[in] pfTmrCallBack - callback function
 * \param[in] param - parameter to callback function
 *
 * \details Customized form of TMR_StartTimer()
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartIntervalTimer
(
    tmrTimerID_t timerID,
    tmrTimeInMilliseconds_t timeInMilliseconds,
    pfTmrCallBack_t callback,
    void *param
)
{
    return TMR_StartTimer(timerID, gTmrIntervalTimer_c, timeInMilliseconds, callback, param);
}

/*! -------------------------------------------------------------------------
 * \brief     Starts an single-shot timer
 * \param[in] timerId - the ID of the timer
 * \param[in] timeInMilliseconds - time expressed in milliseconds
 * \param[in] pfTmrCallBack - callback function
 * \param[in] param - parameter to callback function
 *
 * \details Customized form of TMR_StartTimer()
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StartSingleShotTimer
(
    tmrTimerID_t timerID,
    tmrTimeInMilliseconds_t timeInMilliseconds,
    pfTmrCallBack_t callback,
    void *param
)
{
    return TMR_StartTimer(timerID, gTmrSingleShotTimer_c, timeInMilliseconds, callback, param);
}

/*! -------------------------------------------------------------------------
 * \brief     Stop a timer
 * \param[in] timerID - the ID of the timer
 *
 * \details Associated timer callback function is not called, even if the timer
 *        expires. Does not frees the timer. Safe to call anytime, regardless
 *        of the state of the timer.
 *---------------------------------------------------------------------------*/
tmrErrCode_t TMR_StopTimer
(
    tmrTimerID_t timerID
)
{
    tmrStatus_t status = gTmrSuccess_c;
    tmrErrCode_t err = gTmrSuccess_c;
	
    /* check if timer is not allocated or if it has an invalid ID (fix@ENGR00323423) */
    if( (timerID >= gTmrTotalTimers_c) || (!TMR_IsTimerAllocated(timerID)) )
    {
        err = gTmrInvalidId_c;
    }
    else
    {
        TmrIntDisableAll();
        status = TMR_GetTimerStatus(timerID);
        
        if ( (status == mTmrStatusActive_c) || (status == mTmrStatusReady_c) )
        {
            TMR_SetTimerStatus(timerID, mTmrStatusInactive_c);
            DecrementActiveTimerNumber(TMR_GetTimerType(timerID));
            /* if no sw active timers are enabled, */
            /* call the TMR_Task() to countdown the ticks and stop the hw timer*/
            if ( (!numberOfActiveTimers) && (!numberOfLowPowerActiveTimers) )
            {
                TmrIntDisableAll();
                if( timerHardwareIsRunning )
                {
                  StackTimer_Disable();
                  timerHardwareIsRunning = FALSE;
                }
                TmrIntRestoreAll();
            }
            
        }
        
        TmrIntRestoreAll();
    }

    return err;
}

/*! -------------------------------------------------------------------------
 * \brief     Timer thread.
 *            Called by the kernel when the timer ISR posts a timer event.
 * \param[in] param
 *---------------------------------------------------------------------------*/
void TMR_Task
(
    osaTaskParam_t param
)
{
    tmrTimerTicks16_t nextInterruptTime;
    tmrTimerTicks16_t currentTimeInTicks;
    tmrTimerTicks16_t ticksSinceLastHere, ticksdiff;
    pfTmrCallBack_t   pfCallBack;
    tmrTimerType_t    timerType;
    tmrTimerStatus_t  status;
    uint8_t timerID;

    param=param;

#if defined(FWK_SMALL_RAM_CONFIG)
    {
#else
    osaEventFlags_t     ev;
    
    while(1)
    {
        (void)OSA_EventWait(mTimerThreadEventId, osaEventFlagsAll_c, FALSE, osaWaitForever_c, &ev);
#endif
        TmrIntDisableAll();

        currentTimeInTicks = StackTimer_GetCounterValue();

        TmrIntRestoreAll();

        /* calculate difference between current and previous.  */
        ticksSinceLastHere = (currentTimeInTicks - previousTimeInTicks);
        /* remember for next time */
        previousTimeInTicks = currentTimeInTicks;
        /* Find the shortest active timer. */
        nextInterruptTime = mMaxToCountDown_c;

        for (timerID = 0; timerID < NumberOfElements(maTmrTimerTable); ++timerID)
        {
            timerType = TMR_GetTimerType(timerID);

            TmrIntDisableAll();
            status = TMR_GetTimerStatus(timerID);
            /* If TMR_StartTimer() has been called for this timer, start it's count */
            /* down as of now. */
            if( status == mTmrStatusReady_c )
            {
                TMR_SetTimerStatus(timerID, mTmrStatusActive_c);
                TmrIntRestoreAll();

                if (nextInterruptTime > maTmrTimerTable[timerID].remainingTicks)
                {
                    nextInterruptTime = maTmrTimerTable[timerID].remainingTicks;
                }                
            }
            else if (status == mTmrStatusActive_c)
            {
                TmrIntRestoreAll();
                /* This timer is active. Decrement it's countdown.. */
                if (maTmrTimerTable[timerID].remainingTicks > ticksSinceLastHere)
                {
                    TmrIntDisableAll();
                    maTmrTimerTable[timerID].remainingTicks -= ticksSinceLastHere;
                    maTmrTimerTable[timerID].timestamp = StackTimer_GetCounterValue();
                    TmrIntRestoreAll();
                    
                    if (nextInterruptTime > maTmrTimerTable[timerID].remainingTicks)
                    {
                        nextInterruptTime = maTmrTimerTable[timerID].remainingTicks;
                    }
                }
                else
                {
                    /* If this is an interval timer, restart it. Otherwise, mark it as inactive. */
                    if ( (timerType & gTmrSingleShotTimer_c) ||
                         (timerType & gTmrSetMinuteTimer_c)  ||
                         (timerType & gTmrSetSecondTimer_c)  )
                    {
                        maTmrTimerTable[timerID].remainingTicks = 0;
                        (void)TMR_StopTimer(timerID);
                    }
                    else
                    {
                        TmrIntDisableAll();
                        
                        maTmrTimerTable[timerID].remainingTicks = maTmrTimerTable[timerID].intervalInTicks;
                        maTmrTimerTable[timerID].timestamp = StackTimer_GetCounterValue();
                        if (nextInterruptTime > maTmrTimerTable[timerID].remainingTicks)
                        {
                            nextInterruptTime = maTmrTimerTable[timerID].remainingTicks;
                        }
                        
                        TmrIntRestoreAll();
                    }
                    /* This timer has expired. */
                    pfCallBack = maTmrTimerTable[timerID].pfCallBack;
                    /*Call callback if it is not NULL
                    This is done after the timer got updated,
                    in case the timer gets stopped or restarted in the callback*/
                    if (pfCallBack)
                    {
                        pfCallBack(maTmrTimerTable[timerID].param);
                    }
                }
            }
            else
            {
                TmrIntRestoreAll();
                /* Ignore any timer that is not active. */
            }
        }  /* for (timerID = 0; timerID < ... */

        TmrIntDisableAll();

        /* Check to be sure that the timer was not programmed in the past for different source clocks.
         * The interrupts are now disabled.
         */
        ticksdiff = StackTimer_GetCounterValue();

        /* Number of ticks to be here */
        ticksdiff = (uint16_t)(ticksdiff - currentTimeInTicks);

        /* Next ticks to count already expired?? */
        if(ticksdiff >= nextInterruptTime)
        {
            /* Is assumed that a thread has to be executed in 4ms...
            so if the ticks already expired enter in TMR_Task() after 4ms*/
            nextInterruptTime = ticksdiff + mTicksFor4ms;
        }
        else
        {
            /* Time reference is 4ms, so be sure that won't be loaded
               in Cmp Reg. less that 4ms in ticks */
            if((nextInterruptTime - ticksdiff) < mTicksFor4ms)
            {
                nextInterruptTime = ticksdiff + mTicksFor4ms;
            }
        }
        /* Update the compare register */
        nextInterruptTime += currentTimeInTicks;

        if( numberOfActiveTimers || numberOfLowPowerActiveTimers ) /*not about to stop*/
        {
            /*Causes a bug with flex timers if CxV is set before hw timer switches off*/
            StackTimer_Disable();
            StackTimer_SetOffsetTicks(nextInterruptTime);
            StackTimer_Enable();
            timerHardwareIsRunning = TRUE;
        }
        else
        {
            if( timerHardwareIsRunning )
            {
                StackTimer_Disable();
                timerHardwareIsRunning = FALSE;
            }
        }
            
        TmrIntRestoreAll();      

#if !defined(FWK_SMALL_RAM_CONFIG)        
        /* For BareMetal break the while(1) after 1 run */
        if (gUseRtos_c == 0)
        {
            break;
        }        
#endif
    }
}

/*! -------------------------------------------------------------------------
 * \brief     Enable the specified timer
 * \param[in] tmrID - the timer ID
 *---------------------------------------------------------------------------*/
void TMR_EnableTimer
(
    tmrTimerID_t tmrID
)
{
    TmrIntDisableAll();

    if (TMR_GetTimerStatus(tmrID) == mTmrStatusInactive_c)
    {
        IncrementActiveTimerNumber(TMR_GetTimerType(tmrID));
        TMR_SetTimerStatus(tmrID, mTmrStatusReady_c);
        (void)OSA_EventSet(mTimerThreadEventId, mTmrDummyEvent_c);
    }

    TmrIntRestoreAll();
}

/*! -------------------------------------------------------------------------
 * \brief  This function is called by Low Power module;
 *         Also this function stops the hardware timer.
 * \return TMR ticks that wasn't counted before entering in sleep
 *---------------------------------------------------------------------------*/
uint16_t TMR_NotCountedTicksBeforeSleep
(
    void
)
{
    uint16_t ticks = 0;
#if (gTMR_EnableLowPowerTimers_d)
    uint16_t currentTimeInTicks;

    if (numberOfLowPowerActiveTimers)
    {
        currentTimeInTicks = StackTimer_GetCounterValue();
        StackTimer_Disable();
        timerHardwareIsRunning = FALSE;
        
        /* The hw timer is stopped but keep timerHardwareIsRunning = TRUE...*/
        /* The Lpm timers are considered as being in running mode, so that  */
        /* not to start the hw timer if a TMR event occurs (this shouldn't happen) */
        
        ticks = (uint16_t)(currentTimeInTicks - previousTimeInTicks);
    }
#endif
    return ticks;
}

/*! -------------------------------------------------------------------------
 * \brief      This function is called by the Low Power module
 *             each time the MCU wakes up.
 * \param[in]  sleep duration in TMR ticks
 *---------------------------------------------------------------------------*/
void TMR_SyncLpmTimers
(
    uint32_t sleepDurationTmrTicks
)
{
#if (gTMR_EnableLowPowerTimers_d)
    uint32_t  timerID;
    tmrTimerType_t timerType;

    /* Check if there are low power active timer */
    if (numberOfLowPowerActiveTimers)
    {
        /* For each timer, detect the timer type and count down the spent duration in sleep */
        for (timerID = 0; timerID < NumberOfElements(maTmrTimerTable); ++timerID)
        {
            /* Detect the timer type and count down the spent duration in sleep */
            timerType = TMR_GetTimerType(timerID);
            
            /* Sync. only the low power timers that are active */
            if ( (TMR_GetTimerStatus(timerID) == mTmrStatusActive_c)
                && (IsLowPowerTimer(timerType)) )
            {
                /* Timer expired when MCU was in sleep mode??? */
                if( maTmrTimerTable[timerID].remainingTicks > sleepDurationTmrTicks)
                {
                    maTmrTimerTable[timerID].remainingTicks -= sleepDurationTmrTicks;
                    
                }
                else
                {
                    maTmrTimerTable[timerID].remainingTicks = 0;
                }
                
            }
            
        }/* end for (timerID = 0;.... */
        
        StackTimer_Enable();
        previousTimeInTicks = StackTimer_GetCounterValue();
    }
#else
    sleepDurationTmrTicks = sleepDurationTmrTicks;
#endif /* #if (gTMR_EnableLowPowerTimers_d) */
}
/*! -------------------------------------------------------------------------
 * \brief This function is called by the Low Power module
 *        each time the MCU wakes up after low power timers synchronisation.
 *---------------------------------------------------------------------------*/
void TMR_MakeTMRThreadReady
(
 void
)
{
#if (gTMR_EnableLowPowerTimers_d)

    (void)OSA_EventSet(mTimerThreadEventId, mTmrDummyEvent_c);

#endif /* #if (gTMR_EnableLowPowerTimers_d) */
}

/*! -------------------------------------------------------------------------
 * \brief Get the frequency in Hz of the TMR counter
 *---------------------------------------------------------------------------*/
uint32_t TMR_GetTimerFreq
(
    void
)
{
  return mCounterFreqHz ;
}

/*! -------------------------------------------------------------------------
 * \brief Initialize the timestamp module
 *---------------------------------------------------------------------------*/
void TMR_TimeStampInit(void)
{
#if gTMR_PIT_Timestamp_Enabled_d
    TMR_PITInit();
#else
    TMR_RTCInit();
#endif
}

/*! -------------------------------------------------------------------------
 * \brief  return an 64-bit absolute timestamp
 * \return absolute timestamp in us
 *---------------------------------------------------------------------------*/
uint64_t TMR_GetTimestamp(void)
{
#if gTMR_PIT_Timestamp_Enabled_d
    return TMR_PITGetTimestamp();
#else
    return TMR_RTCGetTimestamp();
#endif
}

#endif /*gTMR_Enabled_d*/


/*! -------------------------------------------------------------------------
 * \brief returns the state of the RTC oscillator
 *---------------------------------------------------------------------------*/
bool_t TMR_RTCIsOscStarted(void)
{
  return (RTC->CR & RTC_CR_OSCE_MASK) == RTC_CR_OSCE_MASK;
}

#if gTimestamp_Enabled_d

/*! -------------------------------------------------------------------------
 * \brief initialize the RTC part of the timer module
 *---------------------------------------------------------------------------*/
void TMR_RTCInit(void)
{
    TmrIntDisableAll();
    
    if( !gRTCInitFlag )
    {
        CLOCK_EnableClock(kCLOCK_Rtc0);
        
        if( RTC->SR & RTC_SR_TIF_MASK )
        {
            RTC->CR |= RTC_CR_SWR_MASK;
            RTC->CR &= ~RTC_CR_SWR_MASK;
            /* Set TSR register to 0x1 to avoid the timer invalid (TIF) bit being set in the SR register */
            RTC->TSR = 1U;
        }
        
        /* Check OSCE value to enable in case of TIF was set and RTC module was reseted */
        if( !TMR_RTCIsOscStarted() )
        {
            RTC->CR |= RTC_CR_OSCE_MASK;
        }
        
        /* Setup the update mode and supervisor access mode */
        RTC->CR |= RTC_CR_UM_MASK | RTC_CR_SUP_MASK;
        /* Stop counter */
        RTC->SR &= ~RTC_SR_TCE_MASK;
        /* Disable alarm interrupt */
        RTC->IER &= ~RTC_IER_TAIE_MASK;
        /* set RTC seconds */
        RTC->TSR = 1;
        /* Set prescaller */
        RTC->TPR = 0;
        /* Start counter */
        RTC->SR |= RTC_SR_TCE_MASK;
        
        gRTCTimeOffset = 0;
        gRTCPrescalerOffset = 0;
        gRTCAlarmCallback = NULL;
        gRTCAlarmCallbackParam = NULL;
        
        /* Overwrite old ISR */
        OSA_InstallIntHandler(RTC_IRQn, TMR_RTCAlarmNotify);
        NVIC_SetPriority(RTC_IRQn, 0x80 >> (8 - __NVIC_PRIO_BITS));
        NVIC_EnableIRQ(RTC_IRQn);
        gRTCInitFlag = TRUE;
    }
    
    TmrIntRestoreAll();
}

/*! -------------------------------------------------------------------------
 * \brief  Returns the absolute time at the moment of the call.
 * \return Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t TMR_RTCGetTimestamp(void)
{
    uint32_t seconds1, seconds2, prescaler0, prescaler1, prescaler2;
    uint64_t useconds, offset, prescalerOffset;
    
    if( !gRTCInitFlag )
    {
        useconds = 0;
        offset = 0;
    }
    else
    {
        TmrIntDisableAll();
        offset = gRTCTimeOffset;
        prescalerOffset = gRTCPrescalerOffset;
        
        prescaler0 = RTC->TPR;
        seconds1   = RTC->TSR;
        prescaler1 = RTC->TPR;
        seconds2   = RTC->TSR; 
        prescaler2 = RTC->TPR;
        
        TmrIntRestoreAll();
        
        prescaler0 &= 0x7fff;
        seconds1 -= 1;
        prescaler1 &= 0x7fff;
        seconds2 -= 1;
        prescaler2 &= 0x7fff;
        
        if(seconds1 != seconds2)
        {
            seconds1 = seconds2;
            prescaler1 = prescaler2;
        }
        else
        {
            if(prescaler1 != prescaler2)
            {
                prescaler1 = prescaler0;
            }
        }
        
        useconds = ((prescaler1 + prescalerOffset + ((uint64_t)seconds1<<15))*15625)>>9;
    }
    
    return useconds + offset;
}

/*! -------------------------------------------------------------------------
 * \brief     Sets the absolute time.
 * \param[in] microseconds - Time in microseconds.
 *---------------------------------------------------------------------------*/
void TMR_RTCSetTime(uint64_t microseconds)
{
    uint64_t initialAlarm;
    
    if( gRTCInitFlag )
    {
        TmrIntDisableAll();
        /* Stop counter */
        RTC->SR &= ~RTC_SR_TCE_MASK;
        
        initialAlarm = gRTCTimeOffset;
        initialAlarm = RTC->TAR + (initialAlarm/1000000L);
        gRTCTimeOffset = microseconds;
        /* Set RTC seconds */
        RTC->TSR = 0x01;
        /* Set RTC Prescaller */
        RTC->TPR = 0x00;
        
        if( (initialAlarm * 1000000L) <= microseconds )
        {
            /* Disable alarm interrupt */
            RTC->IER &= ~RTC_IER_TAIE_MASK;
            if( gRTCAlarmCallback != NULL )
            {
                gRTCAlarmCallback(gRTCAlarmCallbackParam);
            }
        }
        else
        {
            /* Set alarm time */
            RTC->TAR = initialAlarm - (microseconds/1000000L);
        }
        
        /* Start counter */
        RTC->SR |= RTC_SR_TCE_MASK;;
        
        TmrIntRestoreAll();
    }
}

/*! -------------------------------------------------------------------------
 * \brief     Sets the alarm absolute time in seconds.
 * \param[in] seconds - Time in seconds for the alarm. 
 * \param[in] callback - Callback function pointer. 
 * \param[in] param - Parameter for callback.
 *---------------------------------------------------------------------------*/
void TMR_RTCSetAlarm(uint64_t seconds, pfTmrCallBack_t callback, void *param)
{
    if( gRTCInitFlag )
    {
        TmrIntDisableAll();
        
        gRTCAlarmCallback = callback;
        gRTCAlarmCallbackParam = param;
        seconds = seconds - (gRTCTimeOffset/1000000L);
        /* Set alarm time */
        RTC->TAR = seconds;
        /* Enable alarm interrupt */
        RTC->IER |= RTC_IER_TAIE_MASK;;
        
        TmrIntRestoreAll();
    }
}

/*! -------------------------------------------------------------------------
 * \brief Sets the alarm relative time in seconds.
 * \param[in] seconds - Time in seconds for the alarm. 
 * \param[in] callback - Callback function pointer. 
 * \param[in] param - Parameter for callback.
 *---------------------------------------------------------------------------*/
void TMR_RTCSetAlarmRelative(uint32_t seconds, pfTmrCallBack_t callback, void *param)
{
    uint32_t rtcSeconds, rtcPrescaler;
    
    if( gRTCInitFlag )
    {
        if( seconds == 0 )
        {
            callback(param);
        }
        else
        {
            TmrIntDisableAll();
            /* Stop counter */
            RTC->SR &= ~RTC_SR_TCE_MASK;
            rtcSeconds = RTC->TSR;
            rtcPrescaler = RTC->TPR;
            RTC->TPR = 0x00;
            /*If bit prescaler 14 transitions from 1 to 0 the seconds reg get incremented.
            Rewrite seconds register to prevent this.*/
            RTC->TSR = rtcSeconds;
            /* Start counter */
            RTC->SR |= RTC_SR_TCE_MASK;
            rtcPrescaler &= 0x7fff;
            
            gRTCPrescalerOffset += rtcPrescaler;
            
            if(gRTCPrescalerOffset & 0x8000)
            {
                rtcSeconds++;
                /* Stop counter */
                RTC->SR &= ~RTC_SR_TCE_MASK;
                RTC->TSR = rtcSeconds;
                /* Start counter */
                RTC->SR |= RTC_SR_TCE_MASK;
                gRTCPrescalerOffset = gRTCPrescalerOffset & 0x7FFF;
            }
            
            gRTCAlarmCallback = callback;
            gRTCAlarmCallbackParam = param;
            /* Set alarm time */
            RTC->TAR = seconds + rtcSeconds - 1;
            /* Enable alarm interrupt */
            RTC->IER |= RTC_IER_TAIE_MASK;
            
            TmrIntRestoreAll();
        }
    }
}


#endif /*gTimestamp_Enabled_d*/

#if gTMR_PIT_Timestamp_Enabled_d

#if (FSL_FEATURE_PIT_TIMER_COUNT >= 3)
/*! -------------------------------------------------------------------------
 * \brief initialize the PIT part of the timer module
 *---------------------------------------------------------------------------*/
void TMR_PITInit()
{
    PIT_Type * baseAddr = mPitBase[gTmrPitInstance_c];
    clock_ip_name_t pitClocks[] = PIT_CLOCKS;
    uint32_t pitFreq;
    
    if( gPITInitFlag )
    {
        return; /*already inited*/
    }
    
    TmrIntDisableAll();
    
    CLOCK_EnableClock(pitClocks[gTmrPitInstance_c]);

    baseAddr->MCR |= PIT_MCR_MDIS_MASK;
    
    pitFreq = CLOCK_GetBusClkFreq();

    /* Set Channel max count */
    baseAddr->CHANNEL[0].LDVAL = pitFreq/1000000U -1;
    baseAddr->CHANNEL[1].LDVAL = 0xFFFFFFFFU;
    baseAddr->CHANNEL[2].LDVAL = 0xFFFFFFFFU;
    /* Chain Channels 0, 1 and 2 */
    baseAddr->CHANNEL[1].TCTRL |= PIT_TCTRL_CHN_MASK;
    baseAddr->CHANNEL[2].TCTRL |= PIT_TCTRL_CHN_MASK;
    /* Enable timers */
    baseAddr->CHANNEL[2].TCTRL |= PIT_TCTRL_TEN_MASK;
    baseAddr->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
    baseAddr->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
    
    baseAddr->MCR &= ~PIT_MCR_MDIS_MASK;
    
    gPITInitFlag = TRUE;
    
    TmrIntRestoreAll();
}

/*! -------------------------------------------------------------------------
 * \brief Returns the absolute time at the moment of the call.
 * \return Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t TMR_PITGetTimestamp()
{
    PIT_Type * baseAddr = mPitBase[gTmrPitInstance_c];
    uint32_t pit2_0, pit2_1 , pit1_0, pit1_1;
    uint64_t useconds;
    
    if( !gPITInitFlag )
    {
        return 0;
    }
    
    TmrIntDisableAll();
    pit1_0 = baseAddr->CHANNEL[1].CVAL;
    pit2_0 = baseAddr->CHANNEL[2].CVAL;
    pit1_1 = baseAddr->CHANNEL[1].CVAL;
    pit2_1 = baseAddr->CHANNEL[2].CVAL;
    TmrIntRestoreAll();

    if( pit1_1 <= pit1_0)
    {
        useconds = pit2_0;
    }
    else
    {
        useconds = pit2_1;
    }

    useconds <<= 32;
    useconds += pit1_1;
    useconds = ~useconds ;
#if !gTMR_PIT_FreqMultipleOfMHZ_d
    {
        uint32_t pitFreq;
        uint32_t pitLoadVal;

        pitFreq = CLOCK_GetBusClkFreq();
        pitLoadVal = baseAddr->CHANNEL[0].LDVAL + 1;
        pitLoadVal *= 1000000;

        if( pitFreq != pitLoadVal)
        {
            /*
            To adjust the value to useconds the following formula is used.
            useconds = (useconds*pitLoadVal)/pitFreq;
            Because this formula causes overflow the useconds/pitFreq is split in its Integer  and Fractional part.
            */
            uint64_t uSecAdjust1 , uSecAdjust2;
            uSecAdjust1  = useconds/pitFreq;
            uSecAdjust2  = useconds%pitFreq;
            uSecAdjust1 *= pitLoadVal;
            uSecAdjust2 *= pitLoadVal;
            uSecAdjust2 /= pitFreq;
            useconds = uSecAdjust1 + uSecAdjust2;
        }
    }
#endif /* gTMR_PIT_FreqMultipleOfMHZ_d */
    return useconds;
}

#else

/*! -------------------------------------------------------------------------
 * \brief initialize the PIT part of the timer module
 *---------------------------------------------------------------------------*/
void TMR_PITInit(void)
{
    PIT_Type * baseAddr = mPitBase[gTmrPitInstance_c];
    clock_ip_name_t pitClocks[] = PIT_CLOCKS;
    IRQn_Type pitIrqs[] = PIT_IRQS;
    uint32_t pitFreq;
    
    TmrIntDisableAll();
    
    if( !gPITInitFlag )
    {
        mPIT_TimestampHigh = (uint32_t)-1;
        
        CLOCK_EnableClock(pitClocks[gTmrPitInstance_c]);
        
        baseAddr->MCR |= PIT_MCR_MDIS_MASK;
        
        pitFreq = CLOCK_GetBusClkFreq();
        
        /* Set channel max count */
        baseAddr->CHANNEL[0].LDVAL = pitFreq/1000000U -1;
        baseAddr->CHANNEL[1].LDVAL = 0xFFFFFFFFU;
        
        /* Chain Channel 1 to Channel 0 */
        baseAddr->CHANNEL[1].TCTRL |= PIT_TCTRL_CHN_MASK;
        /* Enable Channel 1 interrupt */
        baseAddr->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;
        
        /* Overwrite old ISR */
        OSA_InstallIntHandler(pitIrqs[gTmrPitInstance_c], TMR_PIT_ISR);
        NVIC_ClearPendingIRQ(pitIrqs[gTmrPitInstance_c]);
        NVIC_EnableIRQ(pitIrqs[gTmrPitInstance_c]);
        
        /* Enable timers */
        baseAddr->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;;
        baseAddr->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;;
        
        baseAddr->MCR &= ~PIT_MCR_MDIS_MASK;
        
        gPITInitFlag = TRUE;        
    }
    
    TmrIntRestoreAll();
}

/*! -------------------------------------------------------------------------
 * \brief Returns the absolute time at the moment of the call.
 * \return Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t TMR_PITGetTimestamp(void)
{
    PIT_Type * baseAddr = mPitBase[gTmrPitInstance_c];
    uint32_t  pit2, pit1_0, pit1_1, pitIF;
    uint64_t useconds;
	
    if( !gPITInitFlag )
    {
        useconds = 0;
    }
    else
    {
        TmrIntDisableAll();
        
        pit2 = mPIT_TimestampHigh;
        pit1_0 = baseAddr->CHANNEL[1].CVAL;
        pitIF =  baseAddr->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK;
        pit1_1 = baseAddr->CHANNEL[1].CVAL;
        
        TmrIntRestoreAll();
        
        if(pitIF)
        {
            useconds = pit2-1;
        }
        else
        {
            useconds = pit2;
        }
        useconds <<= 32;
        if(pitIF)
        {
            useconds += pit1_1;
        }
        else
        {
            useconds += pit1_0;
        }
        useconds = ~useconds ;
#if !gTMR_PIT_FreqMultipleOfMHZ_d
        {
            uint32_t pitFreq;
            uint32_t pitLoadVal;
            
            pitFreq = CLOCK_GetBusClkFreq();
            pitLoadVal = baseAddr->CHANNEL[0].LDVAL + 1;
            pitLoadVal *= 1000000U;
            
            if( pitFreq != pitLoadVal)
            {
                /*
                To adjust the value to useconds the following formula is used.
                useconds = (useconds*pitLoadVal)/pitFreq;
                Because this formula causes overflow the useconds/pitFreq is split in its Integer  and Fractional part.
                */
                uint64_t uSecAdjust1 , uSecAdjust2;
                uSecAdjust1  = useconds/pitFreq;
                uSecAdjust2  = useconds%pitFreq;
                uSecAdjust1 *= pitLoadVal;
                uSecAdjust2 *= pitLoadVal;
                uSecAdjust2 /= pitFreq;
                useconds = uSecAdjust1 + uSecAdjust2;
            }
        }
#endif /*gTMR_PIT_FreqMultipleOfMHZ_d */
    }
    return useconds;
}

#endif

#endif /*gTMR_PIT_Timestamp_Enabled_d*/


/*****************************************************************************
 *                               <<< EOF >>>                                 *
 *****************************************************************************/
