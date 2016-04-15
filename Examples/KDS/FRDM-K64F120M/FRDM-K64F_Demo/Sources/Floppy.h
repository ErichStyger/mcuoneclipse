/*
 * Floppy.h
 *
 *  Created on: 14.04.2016
 *      Author: Erich Styger
 */

#ifndef FLOPPY_H_
#define FLOPPY_H_

#include "CLS1.h"

uint8_t FLOPPY_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void FLOPPY_Init(void);

#endif /* FLOPPY_H_ */


