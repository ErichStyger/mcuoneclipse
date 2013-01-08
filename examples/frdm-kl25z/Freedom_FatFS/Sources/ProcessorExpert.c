/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2012-11-16, 18:52, # CodeGen: 0
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
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "LEDG.h"
#include "LEDpin4.h"
#include "BitIoLdd4.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "WP1.h"
#include "TI1.h"
#include "TU1.h"
#include "GPIO_D.h"
#include "GPIO_A.h"
#include "SD_GreenLed.h"
#include "SD_RedLed.h"
#include "RTC1.h"
#include "GI2C1.h"
#include "I2C2.h"
#include "UTIL1.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "SM1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
static FATFS fs;
static FIL fp;

static void Test(void) {
  UINT bw; /* number of bytes written */

  if (FAT1_isDiskPresent()) { /* if no hardware CardDetect pin is assigned, it will always return TRUE */
    LEDR_On(); /* turn red RGB LED on */
    FAT1_mount(0, &fs); /* mount file system */
    if (!FAT1_isWriteProtected()) { /* if no hardware WritePtotect pin is assigned, it will always return FALSE */
      LEDG_On(); /* turn green RGB LED on */
      if (FAT1_open(&fp, "./test.txt", FA_CREATE_ALWAYS|FA_WRITE)!=FR_OK) { /* open file, will always create it if not already on disk */
        for(;;){} /* error! */
      }
      if (FAT1_write(&fp, "Hello World!", sizeof("Hello World!")-1, &bw)!=FR_OK) { /* write string to file */
        for(;;){} /* error! */
      }
    }
    (void)FAT1_close(&fp); /* close file */
    FAT1_mount(0, NULL); /* unmount file system */
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

  /* Write your code here */
  SD_GreenLed_ClrVal(NULL);
  SD_RedLed_ClrVal(NULL);
  for(;;) {
    LEDR_Off();
    LEDG_Off();
    Test();
  }

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
