/*
 * Buzzer.c
 *
 *  Created on: Feb 8, 2013
 *      Author: Erich Styger
 */
#include "Buzzer.h"
#include "BUZ.h"
#include "TRG1.h"

static void Off(void) {
  (void)BUZ_SetRatio16(0);  
}

void BUZ_Beep(uint16_t freqHz, uint16_t durationMs) {
  (void)BUZ_SetRatio16(freqHz);  
  (void)TRG1_AddTrigger(TRG1_BUZ_BEEP, durationMs/TRG1_TICK_PERIOD_MS, Off);
}

void BUZ_Init(void) {
  BUZ_SetRatio16(0); /* off */ 
}
