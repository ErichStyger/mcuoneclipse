/**
 * \file
 * \brief Timer driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 21.03.2011
 *
 * This module implements the driver for the timers used in the system.
 */

#ifndef TIMER_H_
#define TIMER_H_

#define TMR_TICK_MS  10  
  /*!< we get called every 10 ms */

/*! \brief Function called from timer interrupt every TMR_TICK_MS. */
void TMR_On10ms(void);

/*! \brief Timer driver initialization */
void TMR_Init(void);

#endif /* TIMER_H_ */
