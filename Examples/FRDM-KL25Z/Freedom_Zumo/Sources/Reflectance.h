/*
 * Reflectance.h
 *
 *  Created on: Feb 5, 2013
 *      Author: Erich Styger
 */

#ifndef REFLECTANCE_H_
#define REFLECTANCE_H_

#include "CLS1.h"

byte REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void REF_Measure(void);

uint16_t REF_GetLine(bool *onLine);

void REF_Calibrate(bool on);

void REF_Init(void);

#endif /* REFLECTANCE_H_ */
