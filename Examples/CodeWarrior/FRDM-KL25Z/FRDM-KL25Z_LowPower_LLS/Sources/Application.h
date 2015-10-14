/*
 * Application.h
 *
 *  Created on: Mar 16, 2014
 *      Author: Erich Styger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

/*! \brief callback called from the LLS wake-up interrupt */
void APP_OnLLSWakeUpInterrupt(void);

/*! \brief callback called from low power timer interrupt */
void APP_TimerInterrupt(void);

/*! \brief application main entry point */
void APP_Run(void);

#endif /* APPLICATION_H_ */
