/* ###################################################################
**     Filename    : main.c
**     Project     : tinyK20_Remote
**     Processor   : MK20DX128VFT5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-03-25, 14:13, # CodeGen: 0
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
#include "RNET1.h"
#include "RF1.h"
#include "CE1.h"
#include "BitIoLdd1.h"
#include "CSN1.h"
#include "BitIoLdd2.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "CLS1.h"
#include "CS1.h"
#include "KSDK1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd3.h"
#include "RTT1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "BitIoLdd4.h"
#include "SCEpin1.h"
#include "BitIoLdd5.h"
#include "D_Cpin1.h"
#include "BitIoLdd6.h"
#include "SPI1.h"
#include "Clock1.h"
#include "BitIoLdd7.h"
#include "Output1.h"
#include "BitIoLdd8.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "FDisp1.h"
#include "LCD_LED.h"
#include "LEDpin2.h"
#include "BitIoLdd9.h"
#include "PTA.h"
#include "PTB.h"
#include "SW1.h"
#include "ExtIntLdd1.h"
#include "SW3.h"
#include "ExtIntLdd3.h"
#include "SW2.h"
#include "ExtIntLdd2.h"
#include "SW4.h"
#include "ExtIntLdd4.h"
#include "SW5.h"
#include "ExtIntLdd5.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "PTD.h"
#include "SW6.h"
#include "BitIoLdd15.h"
#include "SW7.h"
#include "BitIoLdd16.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "USB0.h"
#include "TMOUT1.h"
#include "SYS1.h"
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

  SEGGER_SYSVIEW_Start();
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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
