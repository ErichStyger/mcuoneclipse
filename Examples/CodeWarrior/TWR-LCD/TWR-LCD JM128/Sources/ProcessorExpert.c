/** ###################################################################
**     Filename  : ProcessorExpert.c
**     Project   : ProcessorExpert
**     Processor : MCF51JM128VLH
**     Version   : Driver 01.00
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2011-03-10, 20:45, # CodeGen: 0
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "PS2.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "FDisp1.h"
#include "GDisp1.h"
#include "Helv08n.h"
#include "LCD1.h"
#include "RESpin1.h"
#include "D_Cpin1.h"
#include "SCEpin1.h"
#include "UI1.h"
#include "UTIL1.h"
#include "AD1.h"
#include "Helv14n.h"
#include "Cour08n.h"
#include "Cour10n.h"
#include "Helv24n.h"
#include "Helv18n.h"
#include "Helv12n.h"
#include "Helv10n.h"
#include "Cour08b.h"
#include "EVNT1.h"
#include "TRG1.h"
#include "EuSD.h"
#include "JM_ELE.h"
#include "TP_SEL.h"
#include "BuzzerPPG.h"
#include "IFsh1.h"
#include "UICalendar1.h"
#include "TmDt1.h"
#include "I2C1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SDSS2.h"
#include "CD2.h"
#include "SM1.h"
#include "SM2.h"
#include "KEY1.h"
#include "keyPin1.h"
#include "MultiKey1.h"
#include "TCHS1.h"
#include "Sensor2.h"
#include "Xminus2.h"
#include "Yminus2.h"
#include "Xplus2.h"
#include "Yplus2.h"
#include "TMOUT1.h"
#include "UIG1.h"
#include "CS1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Boot.h"

void main(void)
{
  /* Write your local variable definition here */
  BOOT_PreInit();
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  BOOT_Start();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
