/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC56F8257
**     Version     : Driver 01.14
**     Compiler    : Metrowerks DSP C Compiler
**     Date/Time   : 2012-01-28, 14:08, # CodeGen: 0
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
#include "UTIL1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "Application.h"

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  APP_Run();
  
  for(;;) {}
}

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
