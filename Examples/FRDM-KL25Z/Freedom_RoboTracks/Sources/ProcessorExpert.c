/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-05-09, 15:54, # CodeGen: 0
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
** @version 01.01
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
#include "FRTOS1.h"
#include "RTOSTICKLDD1.h"
#include "UTIL1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "DIRRB.h"
#include "BitIoLdd4.h"
#include "DIRR.h"
#include "BitIoLdd6.h"
#include "DIRLB.h"
#include "BitIoLdd5.h"
#include "DIRL.h"
#include "BitIoLdd7.h"
#include "TU3.h"
#include "PWMR.h"
#include "PwmLdd1.h"
#include "PWML.h"
#include "PwmLdd2.h"
#include "WAIT1.h"
#include "SMAC1.h"
#include "PHY1.h"
#include "TRSVR1.h"
#include "CE1.h"
#include "BitIoLdd8.h"
#include "RESET1.h"
#include "BitIoLdd9.h"
#include "RTXEN1.h"
#include "BitIoLdd10.h"
#include "ATTN1.h"
#include "BitIoLdd11.h"
#include "IRQ1.h"
#include "ExtIntLdd1.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "TMOUT1.h"
#include "RadioTx.h"
#include "TU_US.h"
#include "TRIG.h"
#include "SW1.h"
#include "BitIoLdd12.h"
#include "LED_IR.h"
#include "LEDpin4.h"
#include "BitIoLdd13.h"
#include "IR1.h"
#include "BitIoLdd14.h"
#include "IR2.h"
#include "BitIoLdd15.h"
#include "IR3.h"
#include "BitIoLdd16.h"
#include "IR4.h"
#include "BitIoLdd17.h"
#include "IR5.h"
#include "BitIoLdd18.h"
#include "IR6.h"
#include "BitIoLdd19.h"
#include "IR7.h"
#include "BitIoLdd20.h"
#include "IR8.h"
#include "BitIoLdd21.h"
#include "RefCnt.h"
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
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.2 [05.06]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
