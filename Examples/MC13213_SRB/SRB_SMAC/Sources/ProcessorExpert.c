/** ###################################################################
**     Filename  : ProcessorExpert.c
**     Project   : ProcessorExpert
**     Processor : MC13213
**     Version   : Driver 01.12
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2011-02-23, 13:32, # CodeGen: 0
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
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "LED5.h"
#include "KB1.h"
#include "UTIL1.h"
#include "TI1.h"
#include "Buzzer.h"
#include "AD1.h"
#include "ACCEL1.h"
#include "G11.h"
#include "G21.h"
#include "Sleep1.h"
#include "TEMP1.h"
#include "SMAC1.h"
#include "PHY1.h"
#include "Security1.h"
#include "TRSVR1.h"
#include "CE1.h"
#include "RESET1.h"
#include "RTXEN1.h"
#include "ATTN1.h"
#include "IRQ1.h"
#include "SM1.h"
#include "AS1.h"
#include "TMOUT1.h"
#include "WAIT1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "CLS1.h"
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

  /* Write your code here */
  APP_Init();

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
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
