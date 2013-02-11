/*
 * Buzzer.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Erich Styger
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "PE_Types.h"

void BUZ_Beep(uint16_t freqHz, uint16_t durationMs);

void BUZ_Init(void);

#endif /* BUZZER_H_ */
