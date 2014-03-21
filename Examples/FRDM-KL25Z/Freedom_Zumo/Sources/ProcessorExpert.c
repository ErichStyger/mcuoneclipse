/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-01-29, 20:43, # CodeGen: 0
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
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDB.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "DIRR.h"
#include "BitIoLdd5.h"
#include "DIRL.h"
#include "BitIoLdd4.h"
#include "BUZ1.h"
#include "PwmLdd3.h"
#include "SW1.h"
#include "BitIoLdd6.h"
#include "GPIO1.h"
#include "I2C1.h"
#include "I2C2.h"
#include "I2CSPY1.h"
#include "TMOUT1.h"
#include "HF1.h"
#include "CS1.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "FRTOS1.h"
#include "LED_IR.h"
#include "LEDpin4.h"
#include "BitIoLdd8.h"
#include "IR1.h"
#include "BitIoLdd7.h"
#include "IR4.h"
#include "BitIoLdd10.h"
#include "IR3.h"
#include "BitIoLdd11.h"
#include "IR2.h"
#include "BitIoLdd12.h"
#include "IR5.h"
#include "BitIoLdd13.h"
#include "TRG1.h"
#include "RefCnt.h"
#include "IR6.h"
#include "BitIoLdd9.h"
#include "PWML.h"
#include "PwmLdd1.h"
#include "TU3.h"
#include "PWMR.h"
#include "PwmLdd2.h"
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

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
