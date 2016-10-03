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

void LEDFRAME_SetBrightnessPercent(uint8_t brightnessPercent);

uint8_t LEDFRAME_GetBrightnessPercent(void);

uint8_t LEDFRAME_GetColorRedValue(void);
uint8_t LEDFRAME_GetColorGreenValue(void);
uint8_t LEDFRAME_GetColorBlueValue(void);

void LEDFRAME_SetColorRedValue(uint8_t val);
void LEDFRAME_SetColorGreenValue(uint8_t val);
void LEDFRAME_SetColorBlueValue(uint8_t val);

void LEDFRAME_TurnClockOnOff(bool on);

void LEDFRAME_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec);

void LEDFRAME_Init(void);

#endif /* SOURCES_LEDFRAME_H_ */
