/*
 * Hoval.h
 *
 *  Created on: Jul 7, 2013
 *      Author: Erich Styger
 */

#ifndef HOVAL_H_
#define HOVAL_H_

#include "CLS1.h"

#define HOVAL_PARSE_COMMAND_ENABLED  1

byte HOVAL_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void HOVAL_Init(void);

#endif /* HOVAL_H_ */
