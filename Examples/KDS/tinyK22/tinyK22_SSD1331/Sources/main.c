/* ###################################################################
**     Filename    : main.c
**     Project     : tinyK22_SSD1331
**     Processor   : MK22FN512VDC12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-07-30, 20:45, # CodeGen: 0
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
#include "SPI1.h"
#include "Clock1.h"
#include "BitIoLdd1.h"
#include "Output1.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd7.h"
#include "LCD1.h"
#include "SCEpin1.h"
#include "BitIoLdd8.h"
#include "RESpin1.h"
#include "BitIoLdd9.h"
#include "D_Cpin1.h"
#include "BitIoLdd10.h"
#include "GDisp1.h"
#include "GFont1.h"
#include "FDisp1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
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

  /* Write your code here */
  APP_Run();
  /* For example: for(;;) { } */

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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
