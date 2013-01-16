/*
 * Application.h
 *
 *  Created on: Oct 14, 2012
 *      Author: Erich Styger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "FSSH1.h"

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const FSSH1_StdIOType *io);


void APP_Run(void);

#endif /* APPLICATION_H_ */
