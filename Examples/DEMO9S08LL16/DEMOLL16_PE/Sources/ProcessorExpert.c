/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08LL16CLH
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2012-01-11, 09:37, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "LED5.h"
#include "LEDpin5.h"
#include "LED6.h"
#include "LEDpin6.h"
#include "LED7.h"
#include "LEDpin7.h"
#include "LED8.h"
#include "LEDpin8.h"
#include "WAIT1.h"
#include "EVNT1.h"
#include "UTIL1.h"
#include "TRG1.h"
#include "TI1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  APP_Start();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
