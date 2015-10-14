/** ###################################################################
**     Filename  : Buzzer.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 29.01.2010, 13:07
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Buzzer_H
#define __Buzzer_H

/* MODULE Buzzer */

#include "PE_Types.h"

/* available fixed frequencies */
typedef enum {
  SOUND_HZ_100 = 100,
  SOUND_HZ_500 = 500,
  SOUND_HZ_1000 = 1000,
  SOUND_HZ_2000 = 2000,
  SOUND_HZ_3000 = 3000,
  SOUND_HZ_4000 = 4000
} Sounder_FrequencyT;


void BUZ_Enable(void);
  /* enables the sounder */

void BUZ_Disable(void);
  /* disables the sounder */

bool BUZ_IsEnabled(void);
  /* returns TRUE if buzzer is enabled */

void BUZ_Beep(void);
  /* let the sounder beep for a short time */

Sounder_FrequencyT BUZ_GetFrequency(void);
  /* return the current frequency */

void BUZ_SetFrequency(Sounder_FrequencyT f);
  /* sets a new frequency */

void BUZ_Init(void);
  /* initializes the sounder driver */

/* END Buzzer */

#endif

