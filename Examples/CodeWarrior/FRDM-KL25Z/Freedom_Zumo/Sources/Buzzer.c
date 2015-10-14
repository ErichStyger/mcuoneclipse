/*
 * Buzzer.c
 *
 *  Created on: Feb 8, 2013
 *      Author: Erich Styger
 */
#include "Buzzer.h"
#include "BUZ1.h"
#include "TRG1.h"

static void Off(void) {
  (void)BUZ1_SetRatio16(0);  
}

void BUZ_Beep(uint16_t freqHz, uint16_t durationMs) {
  (void)BUZ1_SetRatio16(0xb000);  
  (void)TRG1_AddTrigger(TRG1_BUZ_BEEP, durationMs/TRG1_TICK_PERIOD_MS, Off);
}

void BUZ_Init(void) {
  BUZ1_Enable();
  BUZ1_SetRatio16(0); /* off */ 
}
