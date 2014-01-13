/**
 * \file
 * \brief Sounder driver
 * \author Erich Styger, erich.styger@hslu.ch
 * \date 21.03.2011
 *
 * This module implements the driver for the sounder.
  */
#include "Platform.h"
#if PL_HAS_SOUNDER
#include "Sounder.h"
#include "Trigger.h"
#include "Buzzer.h"

#define USE_PPG 0

static void SND_Off(void *p) {
  (void)p; /* avoid compiler warning */
#if USE_PPG /* using PPG */
  (void)Buzzer_Disable();
#else /* using BitIO */
  Buzzer_ClrVal(); /* turn buzzer off */
#endif
}

void SND_Beep(uint16_t ms, uint16_t Hz) {
#if USE_PPG /* using PPG */
  (void)Buzzer_SetFreqHz(Hz);  
  (void)Buzzer_Enable();
#else /* using BitIO */
  (void)Hz;
  Buzzer_SetVal(); /* turn buzzer on */
#endif
  (void)TRG_SetTrigger(TRG_BTNSND_OFF, ms/TRG_TICKS_MS, SND_Off, 0);
}

/*! \brief Sounder initialization */
void SND_Init(void) {
  /* nothing needed right now */
}
#endif
