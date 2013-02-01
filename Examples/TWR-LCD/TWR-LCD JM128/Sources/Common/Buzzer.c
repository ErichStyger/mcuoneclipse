/** ###################################################################
**     Filename  : BuzzerPPG.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 29.01.2010, 13:07
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Buzzer */

#include "Platform.h"

#if PL_HAS_HW_SOUNDER && !PL_IS_BOOTLOADER /* bootloader is doing it it's own way */

#include "Buzzer.h"
#include "BuzzerPPG.h"
#include "EVNT1.h"
#include "TRG1.h"

static Sounder_FrequencyT Sounder_freq = SOUND_HZ_1000;
static bool Sounder_enabled = TRUE;

void BUZ_Enable(void) {
  Sounder_enabled = TRUE;
}

void BUZ_Disable(void) {
  Sounder_enabled = FALSE;
}

bool BUZ_IsEnabled(void) {
  return Sounder_enabled;
}

Sounder_FrequencyT BUZ_GetFrequency(void) {
  return Sounder_freq;
}

void BUZ_SetFrequency(Sounder_FrequencyT f) {
  Sounder_freq = f;
}

static void BuzzerOff(void) {
  BuzzerPPG_Disable();
}

void BUZ_Beep(void) {
  if (Sounder_enabled) {
    BuzzerPPG_SetFreqHz(Sounder_freq);
    BuzzerPPG_Enable();
#if PL_USE_RTOS /* we are using 10ms tick timer */
    TRG1_AddTrigger(TRG1_BUZZER_OFF, 10, BuzzerOff);
#else /* assume 25ms tick timer */
    TRG1_AddTrigger(TRG1_BUZZER_OFF, 4, BuzzerOff);
#endif
  }
}

void BUZ_Init(void) {
  Sounder_freq = SOUND_HZ_1000;
  Sounder_enabled = TRUE;
}

#endif /* PL_HAS_HW_SOUNDER */



/* END Buzzer */
