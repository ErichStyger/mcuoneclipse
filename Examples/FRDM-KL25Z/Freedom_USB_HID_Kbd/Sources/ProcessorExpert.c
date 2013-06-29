/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-06-24, 15:42, # CodeGen: 0
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
#include "USB1.h"
#include "USB0.h"
#include "HIDK1.h"
#include "Tx2.h"
#include "SW1.h"
#include "BitIoLdd4.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  int cnt=0; /* counter to slow down LED blinking */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  for(;;) {
    WAIT1_Waitms(10);
    cnt++;
    if (SW1_GetVal()==0) { /* button pressed */
      WAIT1_Waitms(100); /* wait for debouncing */
      if (SW1_GetVal()==0) { /* still pressed */
#if 0 /* send a string */
        //(void)HIDK1_SendStr((unsigned char*)"SW1 press "); /* send a string */
#endif
#if 0 /* send print screen */
        //HIDK1_Send(MODIFERKEYS_NONE, KEY_PRINTSCREEN);
        //HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release key */
#endif
#if 1 /* send CTRL+ALT+DELETE */
        HIDK1_Send(MODIFERKEYS_LEFT_CTRL|MODIFERKEYS_RIGHT_ALT, KEY_DELETE);
        HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release key */
#endif
      }
      while(SW1_GetVal()==0) {} /* wait until button is released */
    }
    if (HIDK1_App_Task()==ERR_OK) { /* run the USB application task: this will send the buffer */
      if ((cnt%100)==0) {
        LEDR_Off();
        LEDG_Neg(); /* blink Green LED if connected */
      }
    } else {
      if ((cnt%200)==0) {
        LEDG_Off();
        LEDR_Neg(); /* blink red LED if not connected */
      }
    }
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
