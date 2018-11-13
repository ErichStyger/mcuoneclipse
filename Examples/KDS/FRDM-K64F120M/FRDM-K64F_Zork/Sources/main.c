/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K64F_Zork
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-11-09, 07:53, # CodeGen: 0
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
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "MCUC1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "KIN1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
#include "XF1.h"
#include "CS1.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "MINI1.h"
#include "FATM1.h"
#include "SDHC1.h"
#include "CD1.h"
#include "BitIoLdd4.h"
#include "TMOUT1.h"
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
void zork_main(void);
static FAT1_FATFS fileSystemObject;
static FIL fp;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  CLS1_SendStr("Welcome to ZORK!\r\n", CLS1_GetStdio()->stdOut);

  if (FAT1_Init()!=ERR_OK) { /* initialize FAT driver */
    for(;;){}
  }
  if (FAT1_mount(&fileSystemObject, "0", 1) != FR_OK) { /* mount file system */
    for(;;){}
  }
  if (FAT1_open(&fp, "./dtextc.dat", FA_OPEN_ALWAYS|FA_READ)!=FR_OK) {
     for(;;){}
  }
  if (FAT1_close(&fp)!=FR_OK) {
    for(;;){}
  }
   zork_main();
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
