/* ###################################################################
**     Filename    : main.c
**     Project     : K64_PEx_Printf
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-07-10, 11:54, # CodeGen: 0
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
** @version 01.01
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
#include "Pins1.h"
#include "CsIO1.h"
#include "IO1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdio.h>
extern void  initialise_monitor_handles(void);
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

int _isatty(int file) {
  /* _isatty returns a nonzero value if the descriptor is associated with a character device (a terminal, console, printer, or serial port). Otherwise, _isatty returns 0. */
  return 1;
}

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	char temp0, temp1;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  //initialise_monitor_handles();

  temp0 = RCM_SRS0;
	temp0 &= 0;
	temp1 = RCM_SRS1;
	temp1 &= RCM_SRS1_LOCKUP_MASK;
	if(temp0 | temp1)	// If last reset was a Lockup reset
	{
		// Turn on Red LED, PTB22
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;	// Enable PortB Clock gate
		GPIOB_PCOR = (1 << 22);				// Set PTB22 output low
		GPIOB_PDDR |= (1 << 22);			// Set PTB22 as output
		PORTB_PCR22 = PORT_PCR_MUX(1);		// Set pin mux for GPIO
	}

  printf("Test printf\n\r");

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
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
