/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K20_MSD_Host
**     Processor   : MK20DN128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-11-01, 20:53, # CodeGen: 0
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
#include "USB1.h"
#include "USB0.h"
#include "MSD1.h"
#include "UTIL1.h"
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
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
#include "TU1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "FsMSD1.h"
#include "HF1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
  int val, val2, val3, msCycles, msCycles2, one = 1;


static void waitus(int us) {
#if 0
  #define WAIT1_Waitus(us)  \
       (  ((WAIT1_NofCyclesUs((us),CPU_BUS_CLK_HZ)==0)||(us)==0) ? \
          (void)0 : \
          ( ((us)/1000)==0 ? (void)0 : WAIT1_Waitms((uint16_t)((us)/1000))) \
          , (WAIT1_NofCyclesUs(((us)%1000), CPU_BUS_CLK_HZ)==0) ? (void)0 : \
            WAIT1_WAIT_C(WAIT1_NofCyclesUs(((us)%1000), CPU_BUS_CLK_HZ)) \
       )
#endif
  val = WAIT1_NofCyclesUs((us),CPU_BUS_CLK_HZ);
  val2 = WAIT1_NofCyclesUs(((us)%1000), CPU_BUS_CLK_HZ);
  val3 = WAIT1_NofCyclesMs(us, CPU_BUS_CLK_HZ);
  msCycles = WAIT1_NofCyclesMs(1, CPU_CORE_CLK_HZ);
  msCycles2 = WAIT1_NofCyclesMs(one, CPU_CORE_CLK_HZ);
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
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
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
