/*
 * LedCube.h
 *
 *  Created on: 29.01.2016
 *      Author: Erich Styger
 */

#ifndef SOURCES_LEDCUBE_H_
#define SOURCES_LEDCUBE_H_

#include "CLS1.h"

uint8_t LCUBE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void LCUBE_Init(void);


#endif /* SOURCES_LEDCUBE_H_ */
