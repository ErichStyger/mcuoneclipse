/** ###################################################################
**     Filename  : AnalogDigital.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51CN128CLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 13.02.2010, 17:50
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __AnalogDigital_H
#define __AnalogDigital_H

/* MODULE AnalogDigital */

void AD_GetDevice(void);
  /* get mutex for device */

void AD_GiveDevice(void);
  /* return mutex for device */

void AD_Init(void);
  /* module initialization */

/* END AnalogDigital */

#endif

