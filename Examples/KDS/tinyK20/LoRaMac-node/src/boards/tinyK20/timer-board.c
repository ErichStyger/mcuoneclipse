/**
 * \file timer-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board specific timer functions implementation
 *
 */

#if !defined(USE_FREE_RTOS)
#include <math.h>
#include "board.h"
#include "timer-board.h"

/*------------------------- Local Defines --------------------------------*/
#define HWTIMER_PERIOD                                  100 //us
/*------------------------ Local Variables -------------------------------*/

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

void TimerHwInit( void )
{
    /*!
     * Initialize SysTick
     */
    SysTick_BASE_PTR->CSR = SysTick_CSR_CLKSOURCE_MASK;
    SysTick_BASE_PTR->RVR = 0u;
    SysTick_BASE_PTR->CVR = 0u;

    uint32_t divider = (((uint64_t) CPU_CORE_CLK_HZ * HWTIMER_PERIOD)) / 1000000U;

    if ( (divider - 1U) & ~SysTick_RVR_RELOAD_MASK ) {
        /* Divider exceeds possible range */
        while (1)
            ;
    }

    SysTick_BASE_PTR->RVR = divider - 1u;

    /* Run timer and enable interrupt */
    SysTick_BASE_PTR->CSR |= (SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK);
}

void TimerHwDeInit( void )
{
    /* Disable SysTick / Disable interrupt */
    SysTick_BASE_PTR->CSR &= ~(SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK);
    SysTick_BASE_PTR->RVR = 0u;
    SysTick_BASE_PTR->CVR = 0u;
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
    /* Disable SysTick */
    SysTick_BASE_PTR->CSR = 0u;
}

static __attribute__((naked, no_instrument_function)) void Wait10Cycles( void )
{
    /* This function will wait 10 CPU cycles (including call overhead). */
    /* NOTE: Cortex-M0 and M4 have 1 cycle for a NOP */
    /* Compiler is GNUC */
    __asm (
            /* bl Wai10Cycles() to here: [4] */
            "nop   \n\t" /* [1] */
            "nop   \n\t" /* [1] */
            "nop   \n\t" /* [1] */
            "bx lr \n\t" /* [3] */
    );
}

static __attribute__((naked, no_instrument_function)) void Wait100Cycles( void )
{
    /* This function will spend 100 CPU cycles (including call overhead). */
    __asm (
            /* bl to here:               [4] */
            "movs r0, #0 \n\t" /* [1] */
            "loop:       \n\t"
            "nop         \n\t" /* [1] */
            "nop         \n\t" /* [1] */
            "nop         \n\t" /* [1] */
            "nop         \n\t" /* [1] */
            "nop         \n\t" /* [1] */
            "add r0,#1   \n\t" /* [1] */
            "cmp r0,#9   \n\t" /* [1] */
            "bls loop    \n\t" /* [3] taken, [1] not taken */
            "nop         \n\t" /* [1] */
            "bx lr       \n\t" /* [3] */
    );
}

static void WaitCycles( uint16_t cycles )
{
    while (cycles > 100) {
        Wait100Cycles();
        cycles -= 100;
    }
    while (cycles > 10) {
        Wait10Cycles();
        cycles -= 10;
    }
}

static void WaitLongCycles( uint32_t cycles )
{
    while (cycles > 60000) {
        WaitCycles(60000);
        cycles -= 60000;
    }
    WaitCycles((uint16_t) cycles);
}

void TimerHwDelayMs( uint32_t ms )
{
    uint32_t msCycles; /* cycles for 1 ms */

    /* static clock/speed configuration */
    msCycles = (CPU_CORE_CLK_HZ / 1000);
    while (ms > 0) {
        WaitLongCycles(msCycles);
        ms--;
    }
}

TimerTime_t TimerHwGetElapsedTime( void )
{
    return (((TimerHwGetTimerValue() - TimerTickCounterContext) + 1) * HWTIMER_PERIOD);
}

TimerTime_t TimerHwGetTimerValue( void )
{
    TimerTime_t val = 0;

    __disable_irq();

    val = TimerTickCounter;

    __enable_irq();

    return (val);
}

TimerTime_t TimerHwGetTime( void )
{

    return TimerHwGetTimerValue() * HWTIMER_PERIOD;
}

void TimerIncrementTickCounter( void )
{
    __disable_irq();

    TimerTickCounter++;

    __enable_irq();
}

/*!
 * @brief Interrupt service routine.
 */
void SysTick_Handler( void )
{
    PTC_BASE_PTR->PTOR = (1U << 2);

    TimerIncrementTickCounter();

    if ( TimerTickCounter == TimeoutCntValue ) {
        TimerIrqHandler();
    }
}

void TimerHwEnterLowPowerStopMode( void )
{
#ifndef USE_DEBUGGER
    __WFI();
#endif
}
#endif /* USE_FREE_RTOS */
