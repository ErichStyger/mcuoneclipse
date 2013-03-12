/*
 * LineFollow.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Erich Styger
 */

#ifndef LINEFOLLOW_H_
#define LINEFOLLOW_H_

#include "CLS1.h"

void LF_TouchPress(uint8_t position);

uint8_t LF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void LF_Init(void);

#endif /* LINEFOLLOW_H_ */
