/**
 * \file timer-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board specific timer functions implementation
 *
 */

#if !defined(FSL_RTOS_FREE_RTOS)

#include <math.h>
#include "board.h"
#include "timer-board.h"
#include "fsl_pit_driver.h"
#include "fsl_hwtimer.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"

/*------------------------- Local Defines --------------------------------*/
/*!
 * Hardware Timer
 */
#define HWTIMER_LL_DEVIF                                kSystickDevif
#define HWTIMER_LL_ID                                   0
#define HWTIMER_ISR_PRIOR                               0
#define HWTIMER_PERIOD                                  100 //us

/*------------------------ Local Variables -------------------------------*/
extern const hwtimer_devif_t kSystickDevif;
hwtimer_t hwtimer;

/*!
 * Hardware Timer tick counter
 */
volatile TimerTime_t TimerTickCounter = 1;

/*!
 * Saved value of the Tick counter at the start of the next event
 */
static TimerTime_t TimerTickCounterContext = 0;

/*!
 * Value trigging the IRQ
 */
volatile TimerTime_t TimeoutCntValue = 0;

/*!
 * Increment the Hardware Timer tick counter
 */
void TimerIncrementTickCounter( void );

/*!
 * Counter used for the Delay operations
 */
volatile uint32_t TimerDelayCounter = 0;

/*!
 * Retunr the value of the counter used for a Delay
 */
uint32_t TimerHwGetDelayValue( void );

/*!
 * Increment the value of TimerDelayCounter
 */
void TimerIncrementDelayCounter( void );

/*!
 * @brief Hardware timer callback function
 */
void hwtimer_callback( void* data );

extern void HWTIMER_SYS_SystickIsrAction( void );

void TimerHwInit( void )
{
    /*!
     * Hardware Timer init
     */
    HWTIMER_SYS_Init(&hwtimer, &HWTIMER_LL_DEVIF, HWTIMER_LL_ID, NULL);
    /* Set interrupt priority */
    NVIC_SetPriority(SysTick_IRQn, HWTIMER_ISR_PRIOR);
    /* Set timer period */
    HWTIMER_SYS_SetPeriod(&hwtimer, HWTIMER_PERIOD);
    /* Register hardware timer callback */
    HWTIMER_SYS_RegisterCallback(&hwtimer, hwtimer_callback, NULL);
    /* Start hardware timer */
    HWTIMER_SYS_Start(&hwtimer);

    /*!
     * Init delay timer (PIT)
     */
    PIT_DRV_Init(HWTIMER_PIT_INSTANCE, true);
    PIT_DRV_InitUs(HWTIMER_PIT_INSTANCE, HWTIMER_DELAY_CHANNEL);
}

void TimerHwDeInit( void )
{
    /* DeInit hardware timer (SysTick) */
    HWTIMER_SYS_Deinit(&hwtimer);

    /* DeInit delay timer (PIT) */
    PIT_DRV_Deinit (HWTIMER_PIT_INSTANCE);
}

uint32_t TimerHwGetMinimumTimeout( void )
{
    return (ceil(2 * HWTIMER_PERIOD));
}

void TimerHwStart( uint32_t val )
{
    TimerTickCounterContext = TimerHwGetTimerValue();

    if ( val <= HWTIMER_PERIOD + 1 ) {
        TimeoutCntValue = TimerTickCounterContext + 1;
    } else {
        TimeoutCntValue = TimerTickCounterContext + ((val - 1) / HWTIMER_PERIOD);
    }
}

void TimerHwStop( void )
{
    /* Stop hardware timer */
    HWTIMER_SYS_Stop(&hwtimer);
}

void TimerHwDelayMs( uint32_t delay )
{
    PIT_DRV_DelayUs(delay * 1000);
}

TimerTime_t TimerHwGetElapsedTime( void )
{
    return (((TimerHwGetTimerValue() - TimerTickCounterContext) + 1) * HWTIMER_PERIOD);
}

TimerTime_t TimerHwGetTimerValue( void )
{
    TimerTime_t val = 0;

    INT_SYS_DisableIRQGlobal();

    val = TimerTickCounter;

    INT_SYS_EnableIRQGlobal();

    return (val);
}

TimerTime_t TimerHwGetTime( void )
{

    return TimerHwGetTimerValue() * HWTIMER_PERIOD;
}

void TimerIncrementTickCounter( void )
{
    INT_SYS_DisableIRQGlobal();

    TimerTickCounter++;

    INT_SYS_EnableIRQGlobal();
}

void hwtimer_callback( void* data )
{
    TimerIncrementTickCounter();

    if ( TimerTickCounter == TimeoutCntValue ) {
        TimerIrqHandler();
    }
}

/*!
 * @brief Interrupt service routine.
 */
void SysTick_Handler( void )
{
    HWTIMER_SYS_SystickIsrAction();
}

void TimerHwEnterLowPowerStopMode( void )
{
#ifndef USE_DEBUGGER
    __WFI();
#endif
}
#endif /* FSL_RTOS_FREE_RTOS */
