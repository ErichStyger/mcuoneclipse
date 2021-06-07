/**
 * \file
 * \brief Interface to the timer on the PRG_G board.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements to functions to use the timer module.
 */

#ifndef BOARD_TIMER_H_
#define BOARD_TIMER_H_

#include <stdint.h>

/** @addtogroup Timer
  * @{
  */

/*!
 * \brief Start the timer interrupts
 */
void TMR_StartInterrupts(void);

/*!
 * \brief Stop the timer interrupts
 */
void TMR_StopInterrupts(void);

/*!
 * \brief Get the timer counter register
 * \return Timer counter register value
 */
uint32_t TMR_GetCounter(void);

/*!
 * \brief Start timer with no interrupts
 */
void TMR_Start(void);

/*!
 * \brief Stop timer with no interrupts
 */
void TMR_Stop(void);

/*!
 * \brief Timer initialization routine
 */
void TMR_Init(void);

/**
  * @}
  */

#endif /* BOARD_TIMER_H_ */
