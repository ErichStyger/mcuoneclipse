/**
 * \file
 * \brief Application interface
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This is the application interface.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "PE_Types.h"
#include "CLS1.h"

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

/*!
 * \brief Application event handler.
 * \param event Event to be handled.
 */
void APP_HandleEvent(uint8_t event);

/*!
 * \brief Application main start routine.
 */
void APP_Run(void);

#endif /* APPLICATION_H_ */
