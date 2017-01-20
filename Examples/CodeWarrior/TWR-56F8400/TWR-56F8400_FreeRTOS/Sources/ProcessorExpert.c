/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC56F84789VLL
**     Version     : Driver 01.16
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2013-11-16, 09:32, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.16
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "WAIT1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "FRTOS1.h"
#include "TickCntr1.h"
#include "UTIL1.h"
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
#include "LED9.h"
#include "LEDpin9.h"
#include "MCUC1.h"
#include "WDog1.h"
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
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
