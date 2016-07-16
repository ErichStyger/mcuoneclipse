/**
 * \file timer-board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board specific timer functions implementation
 *
 */

#ifndef __TIMER_BOARD_H__
#define __TIMER_BOARD_H__

#if !defined(FSL_RTOS_FREE_RTOS)

/*------------------------------ Defines ---------------------------------*/
/*!
 * Used PIT channels used for hwtimer and delay functions
 */
#define HWTIMER_PIT_INSTANCE        0
#define HWTIMER_DELAY_CHANNEL       1
/*!
 * \brief Timer time variable definition
 */
#ifndef TimerTime_t
typedef uint64_t TimerTime_t;
#endif

/*!
 * \brief Initializes the timer
 *
 * \remark The timer is based on TIM2 with a 10uS time basis
 */
void TimerHwInit( void );

/*!
 * \brief DeInitializes the timer
 */
void TimerHwDeInit( void );

/*!
 * \brief Return the minimum timeout the Timer is able to handle
 *
 * \retval minimum value for a timeout
 */
uint32_t TimerHwGetMinimumTimeout( void );

/*!
 * \brief Start the Standard Timer counter
 *
 * \param [IN] rtcCounter Timer duration
 */
void TimerHwStart( uint32_t rtcCounter );

/*!
 * \brief Perfoms a standard blocking delay in the code execution
 *
 * \param [IN] delay Delay value in ms
 */
void TimerHwDelayMs( uint32_t delay );

/*!
 * \brief Stop the the Standard Timer counter
 */
void TimerHwStop( void );

/*!
 * \brief Return the value of the timer counter
 */
TimerTime_t TimerHwGetTimerValue( void );

/*!
 * \brief Return the value of the current time in us
 */
TimerTime_t TimerHwGetTime( void );

/*!
 * \brief Return the value on the timer Tick counter
 */
TimerTime_t TimerHwGetElapsedTime( void );

/*!
 * \brief Set the ARM core in Wait For Interrupt mode (only working if Debug mode is not used)
 */
void TimerHwEnterLowPowerStopMode( void );

#endif /* FSL_RTOS_FREE_RTOS */
#endif // __TIMER_BOARD_H__
