/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KL46Z_Demo
**     Processor   : MKL46Z256VMC4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-11-18, 07:10, # CodeGen: 0
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
#include "FRTOS1.h"
#include "RTOSCNTRLDD1.h"
#include "UTIL1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "MMA1.h"
#include "GI2C1.h"
#include "I2C0.h"
#include "I2CSPY1.h"
#include "SegLCD1.h"
#include "PTC.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "TMOUT1.h"
#include "MAG1.h"
#include "MINT1.h"
#include "ExtIntLdd1.h"
#include "TRG1.h"
#include "KEY1.h"
#include "Inhr1.h"
#include "BitIoLdd5.h"
#include "Inhr2.h"
#include "BitIoLdd6.h"
#include "EVNT1.h"
#include "CS1.h"
#include "WAIT1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  APP_Run();

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
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
