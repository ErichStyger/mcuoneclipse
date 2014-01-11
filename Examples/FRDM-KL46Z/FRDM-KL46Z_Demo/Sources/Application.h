/**
 * \file
 * \brief Main application interface
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This header file is the interface for the main application.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "PE_Types.h"

void APP_HandleEvent(uint8_t event);

void APP_Run(void);

#endif /* APPLICATION_H_ */
