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
#include "LEDBY.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "DIRR.h"
#include "BitIoLdd5.h"
#include "DIRL.h"
#include "BitIoLdd4.h"
#include "Buzzer.h"
#include "PwmLdd3.h"
#include "SW3.h"
#include "BitIoLdd6.h"
#include "GPIO1.h"
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
static uint8_t dirL, dirR; /* 0: forward */
static uint16_t dutyL=0xffff, dutyR=0xffff; /* 0: full speed */
static uint16_t dutyBuzzer=0; /* \todo: set frequency */

static int cnt = 0;

static void Test(void) {
//  LEDR_Neg();
//  LEDG_Neg();
  if (cnt==2000) {
    LEDBY_Neg();
    cnt=0;
  }
  cnt++;
  DIRL_PutVal(dirL);
  DIRR_PutVal(dirR);
  PWML_SetRatio16(dutyL);
  PWMR_SetRatio16(dutyR);
  Buzzer_SetRatio16(dutyBuzzer);
  if (SW3_GetVal()==0) {
    WAIT1_Waitms(50); /* simple debounce */
    if (SW3_GetVal()==0) { /* still pressed */
      dutyL += 0x2000;
      dutyR += 0x2000;
      LEDG_On();
      while(SW3_GetVal()==0) {
      } /* wait until released */
      LEDG_Off();

    }
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

  for(;;) {
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
