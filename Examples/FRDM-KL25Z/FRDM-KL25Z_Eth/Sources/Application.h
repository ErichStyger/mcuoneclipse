/*
 * Application.h
 *
 *      Author: Erich Styger
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "CLS1.h"

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io);

void APP_Run(void);

#endif /* APPLICATION_H_ */
