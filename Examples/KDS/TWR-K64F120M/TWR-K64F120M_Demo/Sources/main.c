/* ###################################################################
**     Filename    : main.c
**     Project     : TWR-K64F120M_Demo
**     Processor   : MK64FN1M0VMD12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-09, 10:07, # CodeGen: 0
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
#include "FRTOS1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "BitIoLdd4.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "TmDt1.h"
#include "KEY1.h"
#include "Inhr1.h"
#include "BitIoLdd6.h"
#include "Inhr2.h"
#include "BitIoLdd7.h"
#include "TRG1.h"
#include "MMA1.h"
#include "GI2C1.h"
#include "I2C.h"
#include "KSDK1.h"
#include "XF1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"
#include "KinetisTrace.h"
#include "swo.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  int i;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
#if 0 /* this is not necessary if using Segger and GNU ARM Eclipse: the Segger will do that initialization in the hardware */
  #define CPU_CORE_FREQUENCY_HZ 120000000 /* CPU core frequency in Hz */
  SWO_Init(0x1, CPU_CORE_FREQUENCY_HZ);
#endif
#if 0
  for(i=0; i<5; i++) {
    SWO_PrintString("hello world with SWO\r\n", 0);
    WAIT1_Waitms(100);
  }
#endif
  KinetisTrace_Init();
  APP_Start();
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
