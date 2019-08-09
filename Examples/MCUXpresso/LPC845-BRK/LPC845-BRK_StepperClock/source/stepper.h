/*
 * stepper.h
 *
 *  Created on: 08.08.2019
 *      Author: Erich Styger
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include "McuShell.h"
uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void STEPPER_Init(void);

#endif /* STEPPER_H_ */
