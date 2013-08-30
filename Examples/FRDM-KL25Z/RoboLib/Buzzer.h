/*
 * Buzzer.h
 *
 *  Created on: Aug 29, 2013
 *      Author: Erich Styger
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "CLS1.h"

uint8_t BUZ_Beep(uint16_t freqHz, uint16_t durationMs);

uint8_t BUZ_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void BUZ_Init(void);

#endif /* BUZZER_H_ */
