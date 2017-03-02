/* ###################################################################
**     Filename    : main.c
**     Project     : DEMOQE_S08QE128
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2017-03-02, 20:07, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "MCUC1.h"
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
#include "UTIL1.h"
#include "WAIT1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;) {
	  LED1_On();
	  WAIT1_Waitms(50);
	  LED2_On();
	  WAIT1_Waitms(50);
	  LED3_On();
	  WAIT1_Waitms(50);
	  LED4_On();
	  WAIT1_Waitms(50);
	  LED5_On();
	  WAIT1_Waitms(50);
	  LED6_On();
	  WAIT1_Waitms(50);
	  LED7_On();
	  WAIT1_Waitms(50);
	  LED8_On();
	  WAIT1_Waitms(50);

	  LED1_Off();
	  WAIT1_Waitms(50);
	  LED2_Off();
	  WAIT1_Waitms(50);
	  LED3_Off();
	  WAIT1_Waitms(50);
	  LED4_Off();
	  WAIT1_Waitms(50);
	  LED5_Off();
	  WAIT1_Waitms(50);
	  LED6_Off();
	  WAIT1_Waitms(50);
	  LED7_Off();
	  WAIT1_Waitms(50);
	  LED8_Off();
	  WAIT1_Waitms(50);
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
