/** ###################################################################
**     Filename  : RTOS.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 21.01.2010, 08:24
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __RTOS_H
#define __RTOS_H

/* MODULE RTOS */

#include "PE_Types.h"
#include "platform.h"

void RTOS_HandleEvent(byte event);

void RTOS_Start(void);


/* END RTOS */

#endif

