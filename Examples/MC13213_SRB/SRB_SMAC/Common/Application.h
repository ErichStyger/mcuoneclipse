/**
 * \file
 * \brief Platform interface.
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 04.02.2011
 *
 * This module implements the interface to the application part.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Event.h"

/*!
 * \brief Application event handler
 * \param[in] event Event number
 */
void APP_HandleEvent(EVNT_Handle event);

/*!
 * \brief Application initialization routine.
 * It calls as well all the used platform drivers.
 */ 
void APP_Init(void);

#endif /* APPLICATION_H_ */
