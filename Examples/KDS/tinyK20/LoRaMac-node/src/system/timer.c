/*
 / _____)             _              | |
 ( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
 (______/|_____)_|_|_| \__)_____)\____)_| |_|
 (C)2013 Semtech

 Description: Timer objects and scheduling management

 License: Revised BSD License, see LICENSE.TXT file include in the project

 Maintainer: Miguel Luis and Gregory Cristian
 */
#if defined(FSL_RTOS_FREE_RTOS) || defined(USE_FREE_RTOS)
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "rtc-board.h"
#include "timer-board.h"

#define LOG_LEVEL_ERROR
#include "debug.h"

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
/*! Low power mode enabled */
static bool LowPowerModeEnable = true;

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
void TimerInit( TimerEvent_t *obj, const char* name, void *id, void (*callback)(TimerHandle_t xTimer), bool autoReload )
{
    obj->Handle = xTimerCreate( name,
            (TIMER_DEFAULT_PERIOD / portTICK_PERIOD_MS),
            autoReload,
            ( void * ) (id),
            callback
    );

    if(obj->Handle != NULL) {
        obj->PeriodInMs = TIMER_DEFAULT_PERIOD;
        obj->AutoReload = autoReload;
        obj->IsRunning = false;
        obj->HasChanged = false;

        LOG_TRACE("%s created.", name);
    } else {
        LOG_ERROR("Failed to create %s timer", name);
    }
}

void TimerStart( TimerEvent_t *obj )
{
    BaseType_t xReturn = pdFAIL, xHigherPriorityTaskWoken = pdFALSE;
#if defined(LOG_LEVEL_TRACE)
    TickType_t time = 0;
#endif

    if(obj->IsRunning) return;

    if(__get_IPSR()) {
        if(obj->HasChanged) {
            /* Period has to be changed - this will start the timer */
            xReturn = xTimerChangePeriodFromISR(obj->Handle, (obj->PeriodInMs / portTICK_PERIOD_MS), &xHigherPriorityTaskWoken);
        } else {
            xReturn = xTimerStartFromISR(obj->Handle, &xHigherPriorityTaskWoken);
        }
#if defined(LOG_LEVEL_TRACE)
        time = xTaskGetTickCountFromISR();
#endif
    } else {
        if(obj->HasChanged) {
            /* Period has to be changed - this will start the timer */
            xReturn = xTimerChangePeriod(obj->Handle, (obj->PeriodInMs / portTICK_PERIOD_MS), 100);
        } else {
            xReturn = xTimerStart( obj->Handle, 100 );
        }
#if defined(LOG_LEVEL_TRACE)
        time = xTaskGetTickCount();
#endif
    }

    if(xReturn != pdFAIL) {
        obj->IsRunning = true;
        LOG_TRACE("%s started at %u.", pcTimerGetTimerName(obj->Handle), time);
    } else {
        LOG_ERROR("Failed to start %s.", pcTimerGetTimerName(obj->Handle));
    }
}

void TimerStop( TimerEvent_t *obj )
{
    BaseType_t xReturn = pdFAIL, xHigherPriorityTaskWoken = pdFALSE;
#if defined(LOG_LEVEL_TRACE)
    TickType_t time = 0;
#endif

    if(!obj->IsRunning) return;

    if(__get_IPSR()) {
        xReturn = xTimerStopFromISR(obj->Handle, &xHigherPriorityTaskWoken);
#if defined(LOG_LEVEL_TRACE)
        time = xTaskGetTickCountFromISR();
#endif
    } else {
        xReturn = xTimerStop( obj->Handle, 100 );
#if defined(LOG_LEVEL_TRACE)
        time = xTaskGetTickCount();
#endif
    }

    if(xReturn != pdFAIL) {
        LOG_TRACE("%s stopped at %u.", pcTimerGetTimerName(obj->Handle), time);
        obj->IsRunning = false;
    } else {
        LOG_ERROR("Failed to stop %s timer", pcTimerGetTimerName(obj->Handle));
    }
}

void TimerReset( TimerEvent_t *obj )
{
    BaseType_t xReturn = pdFAIL, xHigherPriorityTaskWoken = pdFALSE;

    if(__get_IPSR()) {
        xReturn = xTimerResetFromISR(obj->Handle, &xHigherPriorityTaskWoken);
    } else {
        xReturn = xTimerReset(obj->Handle, 100);
    }

    if(xReturn != pdFAIL) {
        obj->IsRunning = true;
        LOG_TRACE("%s reset.", pcTimerGetTimerName(obj->Handle));
    } else {
        LOG_ERROR("Failed to reset %s timer", pcTimerGetTimerName(obj->Handle));
    }
}

void TimerSetValue( TimerEvent_t *obj, uint32_t periodInUs )
{
    uint32_t periodInMs = periodInUs / 1e3;

    if(periodInMs <= 0) {
        LOG_ERROR("Minimum period of the timer is 1 ms.");
        return;
    }

    if(periodInMs != obj->PeriodInMs ) {
        /* Value has changed */
        LOG_TRACE("%s period changed from %u ms to %u ms.", pcTimerGetTimerName(obj->Handle), obj->PeriodInMs, periodInMs);
        obj->PeriodInMs = periodInMs;
        obj->HasChanged = true;
    }
}

TimerTime_t TimerGetCurrentTime( void )
{
    if(__get_IPSR()) {
        return (TimerTime_t)xTaskGetTickCountFromISR();
    } else {
        return (TimerTime_t)xTaskGetTickCount();
    }
}

void TimerLowPowerHandler( void )
{

}
/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/

void TimerSetLowPowerEnable( bool enable )
{
    LowPowerModeEnable = enable;
}

bool TimerGetLowPowerEnable( void )
{
    return LowPowerModeEnable;
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

#else
/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
/*! Low power mode enabled */
static bool LowPowerModeEnable = true;

/*!
 * This flag is used to make sure we have looped through the main several time to avoid race issues
 */
volatile uint8_t HasLoopedThroughMain = 0;

/*!
 * Timers list head pointer
 */
static TimerEvent_t *TimerListHead = NULL;

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
/*!
 * \brief Adds or replace the head timer of the list.
 *
 * \remark The list is automatically sorted. The list head always contains the
 *         next timer to expire.
 *
 * \param [IN]  obj Timer object to be become the new head
 * \param [IN]  remainingTime Remaining time of the previous head to be replaced
 */
static void TimerInsertNewHeadTimer( TimerEvent_t *obj, uint32_t remainingTime );

/*!
 * \brief Adds a timer to the list.
 *
 * \remark The list is automatically sorted. The list head always contains the
 *         next timer to expire.
 *
 * \param [IN]  obj Timer object to be added to the list
 * \param [IN]  remainingTime Remaining time of the running head after which the object may be added
 */
static void TimerInsertTimer( TimerEvent_t *obj, uint32_t remainingTime );

/*!
 * \brief Sets a timeout with the duration "timestamp"
 * 
 * \param [IN] timestamp Delay duration
 */
static void TimerSetTimeout( TimerEvent_t *obj );

/*!
 * \brief Check if the Object to be added is not already in the list
 * 
 * \param [IN] timestamp Delay duration
 * \retval true (the object is already in the list) or false  
 */
static bool TimerExists( TimerEvent_t *obj );

/*!
 * \brief Read the timer value of the currently running timer
 *
 * \retval value current timer value
 */
uint32_t TimerGetValue( void );

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
void TimerInit( TimerEvent_t *obj, void (*callback)( void ) )
{
    obj->Timestamp = 0;
    obj->ReloadValue = 0;
    obj->IsRunning = false;
    obj->Callback = callback;
    obj->Next = NULL;
}

void TimerStart( TimerEvent_t *obj )
{
    uint32_t elapsedTime = 0;
    uint32_t remainingTime = 0;

    __disable_irq();

    if ( (obj == NULL) || (TimerExists(obj) == true) ) {
        __enable_irq();
        return;
    }

    obj->Timestamp = obj->ReloadValue;
    obj->IsRunning = false;

    if ( TimerListHead == NULL ) {
        TimerInsertNewHeadTimer(obj, obj->Timestamp);
    } else {
        if ( TimerListHead->IsRunning == true ) {
            elapsedTime = TimerGetValue();
            if ( elapsedTime > TimerListHead->Timestamp ) {
                elapsedTime = TimerListHead->Timestamp;   // security but should never occur
            }
            remainingTime = TimerListHead->Timestamp - elapsedTime;
        } else {
            remainingTime = TimerListHead->Timestamp;
        }

        if ( obj->Timestamp < remainingTime ) {
            TimerInsertNewHeadTimer(obj, remainingTime);
        } else {
            TimerInsertTimer(obj, remainingTime);
        }
    }
    __enable_irq();
}

static void TimerInsertTimer( TimerEvent_t *obj, uint32_t remainingTime )
{
    uint32_t aggregatedTimestamp = 0;      // hold the sum of timestamps 
    uint32_t aggregatedTimestampNext = 0;   // hold the sum of timestamps up to the next event

    TimerEvent_t* prev = TimerListHead;
    TimerEvent_t* cur = TimerListHead->Next;

    if ( cur == NULL ) {   // obj comes just after the head
        obj->Timestamp -= remainingTime;
        prev->Next = obj;
        obj->Next = NULL;
    } else {
        aggregatedTimestamp = remainingTime;
        aggregatedTimestampNext = remainingTime + cur->Timestamp;

        while ( prev != NULL ) {
            if ( aggregatedTimestampNext > obj->Timestamp ) {
                obj->Timestamp -= aggregatedTimestamp;
                if ( cur != NULL ) {
                    cur->Timestamp -= obj->Timestamp;
                }
                prev->Next = obj;
                obj->Next = cur;
                break;
            } else {
                prev = cur;
                cur = cur->Next;
                if ( cur == NULL ) {   // obj comes at the end of the list
                    aggregatedTimestamp = aggregatedTimestampNext;
                    obj->Timestamp -= aggregatedTimestamp;
                    prev->Next = obj;
                    obj->Next = NULL;
                    break;
                } else {
                    aggregatedTimestamp = aggregatedTimestampNext;
                    aggregatedTimestampNext = aggregatedTimestampNext + cur->Timestamp;
                }
            }
        }
    }
}

static void TimerInsertNewHeadTimer( TimerEvent_t *obj, uint32_t remainingTime )
{
    TimerEvent_t* cur = TimerListHead;

    if ( cur != NULL ) {
        cur->Timestamp = remainingTime - obj->Timestamp;
        cur->IsRunning = false;
    }

    obj->Next = cur;
    obj->IsRunning = true;
    TimerListHead = obj;
    TimerSetTimeout(TimerListHead);
}

void TimerIrqHandler( void )
{
    uint32_t elapsedTime = 0;

    if ( LowPowerModeEnable == false ) {
        if ( TimerListHead == NULL ) {
            return;   // Only necessary when the standard timer is used as a time base
        }
    }

    elapsedTime = TimerGetValue();

    TimerEvent_t* elapsedTimer = NULL;

    if ( elapsedTime > TimerListHead->Timestamp ) {
        TimerListHead->Timestamp = 0;
    } else {
        TimerListHead->Timestamp -= elapsedTime;
    }

    // save TimerListHead
    elapsedTimer = TimerListHead;

    // remove all the expired object from the list
    while ( (TimerListHead != NULL) && (TimerListHead->Timestamp == 0) ) {
        if ( TimerListHead->Next != NULL ) {
            TimerListHead = TimerListHead->Next;
        } else {
            TimerListHead = NULL;
        }
    }

    // execute the callbacks of all the expired objects
    // this is to avoid potential issues between the callback and the object list
    while ( (elapsedTimer != NULL) && (elapsedTimer->Timestamp == 0) ) {
        if ( elapsedTimer->Callback != NULL ) {
            elapsedTimer->Callback();
        }
        elapsedTimer = elapsedTimer->Next;
    }

    // start the next TimerListHead if it exists
    if ( TimerListHead != NULL ) {
        TimerListHead->IsRunning = true;
        TimerSetTimeout(TimerListHead);
    }
}

void TimerStop( TimerEvent_t *obj )
{
    __disable_irq();

    uint32_t elapsedTime = 0;
    uint32_t remainingTime = 0;

    TimerEvent_t* prev = TimerListHead;
    TimerEvent_t* cur = TimerListHead;

    // List is empty or the Obj to stop does not exist 
    if ( (TimerListHead == NULL) || (obj == NULL) ) {
        __enable_irq();
        return;
    }

    if ( TimerListHead == obj )   // Stop the Head                                    
            {
        if ( TimerListHead->IsRunning == true )   // The head is already running 
                {
            elapsedTime = TimerGetValue();
            if ( elapsedTime > obj->Timestamp ) {
                elapsedTime = obj->Timestamp;
            }

            remainingTime = obj->Timestamp - elapsedTime;

            if ( TimerListHead->Next != NULL ) {
                TimerListHead->IsRunning = false;
                TimerListHead = TimerListHead->Next;
                TimerListHead->Timestamp += remainingTime;
                TimerListHead->IsRunning = true;
                TimerSetTimeout(TimerListHead);
            } else {
                TimerListHead = NULL;
            }
        } else   // Stop the head before it is started
        {
            if ( TimerListHead->Next != NULL ) {
                remainingTime = obj->Timestamp;
                TimerListHead = TimerListHead->Next;
                TimerListHead->Timestamp += remainingTime;
            } else {
                TimerListHead = NULL;
            }
        }
    } else   // Stop an object within the list
    {
        remainingTime = obj->Timestamp;

        while ( cur != NULL ) {
            if ( cur == obj ) {
                if ( cur->Next != NULL ) {
                    cur = cur->Next;
                    prev->Next = cur;
                    cur->Timestamp += remainingTime;
                } else {
                    cur = NULL;
                    prev->Next = cur;
                }
                break;
            } else {
                prev = cur;
                cur = cur->Next;
            }
        }
    }
    __enable_irq();
}

static bool TimerExists( TimerEvent_t *obj )
{
    TimerEvent_t* cur = TimerListHead;

    while ( cur != NULL ) {
        if ( cur == obj ) {
            return true;
        }
        cur = cur->Next;
    }
    return false;
}

void TimerReset( TimerEvent_t *obj )
{
    TimerStop(obj);
    TimerStart(obj);
}

void TimerSetValue( TimerEvent_t *obj, uint32_t value )
{
    uint32_t minValue = 0;

    TimerStop(obj);

    if ( LowPowerModeEnable == true ) {
        minValue = RtcGetMinimumTimeout();
    } else {
        minValue = TimerHwGetMinimumTimeout();
    }

    if ( value < minValue ) {
        value = minValue;
    }

    obj->Timestamp = value;
    obj->ReloadValue = value;
}

uint32_t TimerGetValue( void )
{
    if ( LowPowerModeEnable == true ) {
        return RtcGetTimerElapsedTime();
    } else {
        return TimerHwGetElapsedTime();
    }
}

TimerTime_t TimerGetCurrentTime( void )
{
    if ( LowPowerModeEnable == true ) {
        return RtcGetTimerValue();
    } else {
        return TimerHwGetTime();
    }
}

static void TimerSetTimeout( TimerEvent_t *obj )
{
    HasLoopedThroughMain = 0;

    if ( LowPowerModeEnable == true ) {
        RtcSetTimeout(obj->Timestamp);
    } else {
        TimerHwStart(obj->Timestamp);
    }
}

void TimerLowPowerHandler( void )
{
    if ( (TimerListHead != NULL) && (TimerListHead->IsRunning == true) ) {
        if ( HasLoopedThroughMain < 5 ) {
            HasLoopedThroughMain++;
        } else {
            HasLoopedThroughMain = 0;

            if ( LowPowerModeEnable == true ) {
                RtcEnterLowPowerStopMode();
            } else {
                TimerHwEnterLowPowerStopMode();
            }
        }
    }
}

void TimerSetLowPowerEnable( bool enable )
{
    LowPowerModeEnable = enable;
}

bool TimerGetLowPowerEnable( void )
{
    return LowPowerModeEnable;
}
#endif
