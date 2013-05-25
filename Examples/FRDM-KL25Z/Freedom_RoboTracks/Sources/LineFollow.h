/*
 * LineFollow.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Erich Styger
 */

#ifndef LINEFOLLOW_H_
#define LINEFOLLOW_H_

#include "Platform.h"
#if PL_HAS_LINE_SENSOR
#include "CLS1.h"

uint8_t LF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void LF_StartFollowing(void);
void LF_StopFollowing(void);
bool LF_IsFollowing(void);

void LF_Init(void);
#endif /* PL_HAS_LINE_SENSOR */

#endif /* LINEFOLLOW_H_ */
