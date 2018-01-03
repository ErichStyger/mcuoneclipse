/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2012-11-08, 19:47, # CodeGen: 0
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
#include "RED.h"
#include "SW1.h"
#include "GREEN.h"
#include "BLUE.h"
#include "WAIT1.h"
#include "GPIO1.h"
#include "MCUC1.h"
#include "SW2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#define OPTIMIZE_BIT_ACCESS   1 /* set to 1 if using optimized bit access */
#if OPTIMIZE_BIT_ACCESS
  #define RED_Clr()     GPIO_PDD_ClearPortDataOutputMask(RED_MODULE_BASE_ADDRESS, RED_PORT_MASK)
  #define RED_Set()     GPIO_PDD_SetPortDataOutputMask(RED_MODULE_BASE_ADDRESS, RED_PORT_MASK)
  #define GREEN_Clr()   GPIO_PDD_ClearPortDataOutputMask(GREEN_MODULE_BASE_ADDRESS, GREEN_PORT_MASK)
  #define GREEN_Set()   GPIO_PDD_SetPortDataOutputMask(GREEN_MODULE_BASE_ADDRESS, GREEN_PORT_MASK)
  #define BLUE_Clr()    GPIO_PDD_ClearPortDataOutputMask(BLUE_MODULE_BASE_ADDRESS, BLUE_PORT_MASK)
  #define BLUE_Set()    GPIO_PDD_SetPortDataOutputMask(BLUE_MODULE_BASE_ADDRESS, BLUE_PORT_MASK)
  #define SW1_Get()     (GPIO_PDD_GetPortDataInput(SW1_MODULE_BASE_ADDRESS) & SW1_PORT_MASK)
  #define SW2_Get()     (GPIO_PDD_GetPortDataInput(SW2_MODULE_BASE_ADDRESS) & SW2_PORT_MASK)
#endif

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

#if OPTIMIZE_BIT_ACCESS
  GREEN_Clr(); /* turn on green LED */
  WAIT1_Waitms(1000);
  GREEN_Set(); /* turn off green LED */
  for(;;) {
    if (SW1_Get()==0) { /* button low level => pressed */
      RED_Clr(); /* LED cathode is connected to microcontroller pin: low level turns it on */
      BLUE_Set(); /* turn off blue led */
    } else {
      RED_Set(); /* turn off red led */
      BLUE_Clr(); /* turn on blue led */
    }
    if (SW2_Get()==0) { /* switch low level => pressed */
      BLUE_Clr(); /* turn on blue led */
    } else {
      BLUE_Set(); /* turn off blue led */
    }
  }
#else
  GREEN_ClrVal(GREEN_DeviceData); /* turn on green LED */
  WAIT1_Waitms(1000);
  GREEN_SetVal(GREEN_DeviceData); /* turn off green LED */
  for(;;) {
    if (SW1_GetVal(SW1_DeviceData)==0) { /* button low level => pressed */
      RED_ClrVal(RED_DeviceData); /* LED cathode is connected to microcontroller pin: low level turns it on */
      BLUE_SetVal(BLUE_DeviceData); /* turn off blue led */
    } else {
      RED_SetVal(RED_DeviceData); /* turn off red led */
      BLUE_ClrVal(BLUE_DeviceData); /* turn on blue led */
    }
    if (SW2_GetVal(SW2_DeviceData)==0) { /* switch low level => pressed */
      BLUE_ClrVal(BLUE_DeviceData); /* turn on blue led */
    } else {
      BLUE_SetVal(BLUE_DeviceData); /* turn off blue led */
    }
  }
#endif
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
