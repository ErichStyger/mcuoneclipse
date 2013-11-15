/*
 * Radio.h
 *
 *  Created on: Aug 8, 2013
 *      Author: Erich Styger
 */

#ifndef RADIO_H_
#define RADIO_H_

#include "Platform.h"

void Radio_OnInterrupt(void);

#if PL_HAS_SHELL
#include "CLS1.h"
uint8_t RADIO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

uint8_t RADIO_Process(void);

void RADIO_Init(void);

void RADIO_Deinit(void);

#endif /* RADIO_H_ */
