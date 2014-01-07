/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-01-07, 09:52, # CodeGen: 0
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
#include "Row0.h"
#include "BitIoLdd1.h"
#include "Row1.h"
#include "BitIoLdd2.h"
#include "Row2.h"
#include "BitIoLdd3.h"
#include "Row3.h"
#include "BitIoLdd4.h"
#include "Column0.h"
#include "BitIoLdd5.h"
#include "Column1.h"
#include "BitIoLdd6.h"
#include "Column2.h"
#include "BitIoLdd7.h"
#include "Column3.h"
#include "BitIoLdd8.h"
#include "WAIT1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
#include "UTIL1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "KeyMatrix.h"

static void ScanKeys(void) {
  int key;
  CLS1_ConstStdIOTypePtr io;
  
  KM_Init(); /* initialize driver */
  io = CLS1_GetStdio();
  CLS1_SendStr((unsigned char*)"Matrix Key Demo\r\n", io->stdOut);
  for(;;) {
    key = KM_ScanTask(); /* get scan code */
    if (key!=KM_NO_KEY) {
      CLS1_SendStr((unsigned char*)"Key ", io->stdOut);
      CLS1_SendNum8u(key, io->stdOut);
      CLS1_SendStr((unsigned char*)" pressed!\r\n", io->stdOut);
    }
    WAIT1_Waitms(50); /* for debouncing */
  }
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  ScanKeys();
  
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
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
