/*
 * NeoRingClock.h
 *
 *  Created on: 07.07.2014
 *      Author: tastyger
 */

#ifndef NEORINGCLOCK_H_
#define NEORINGCLOCK_H_

#include <inttypes.h>

void CLOCK_Update(void);

void CLOCK_SetTime(uint8_t hour, uint8_t min, uint8_t second);

void CLOCK_Init(void);

#endif /* NEORINGCLOCK_H_ */
