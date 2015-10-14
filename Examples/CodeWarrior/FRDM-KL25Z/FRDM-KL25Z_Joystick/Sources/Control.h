/*
 * Control.h
 *
 *  Created on: Jul 2, 2014
 *      Author: tastyger
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "PE_Types.h"

void CTRL_OnKeyPressed(uint8_t keys);

void CTRL_OnKeyReleasedLong(uint8_t keys);

void CTRL_OnKeyReleased(uint8_t keys);

void CTRL_ScanKeys(void);

void CTRL_Init(void);

#endif /* CONTROL_H_ */
