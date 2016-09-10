/*
 * LEDFrame.h
 *
 *  Created on: 03.08.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_LEDFRAME_H_
#define SOURCES_LEDFRAME_H_

#include "CLS1.h"
uint8_t LEDFRAME_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void LEDFRAME_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec);

void LEDFRAME_Init(void);

#endif /* SOURCES_LEDFRAME_H_ */
