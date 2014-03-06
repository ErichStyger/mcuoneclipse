/*
 * Application.h
 *
 *      Author: Erich Styger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "CLS1.h"

byte APP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void APP_Run(void);

#endif /* APPLICATION_H_ */
