/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KL03Z_LED
**     Processor   : MKL03Z32VFK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-07-03, 15:44, # CodeGen: 0
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
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "KIN1.h"
#include "UTIL1.h"
#include "GI2C1.h"
#include "I2C1.h"
#include "SDA1.h"
#include "SCL1.h"
#include "MMA1.h"
#include "gpio1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */

void NMI_Handler(void) {
	/* SW3/PTB5 is on NMI pin */
	int i;

	LED1_Off();
	LED2_Off();
	LED3_Off();
    for(i=0;i<10;i++) {
    	LED1_Neg();
		WAIT1_Waitms(50);
	}
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int16_t x, y, z;
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  MMA1_Enable();
  for(;;) {
	  LED1_On();
	  WAIT1_Waitms(100);
	  LED1_Off();

	  LED2_On();
	  WAIT1_Waitms(100);
	  LED2_Off();

	  LED3_On();
	  WAIT1_Waitms(100);
	  LED3_Off();
      x = MMA1_GetXmg();
      y = MMA1_GetYmg();
      z = MMA1_GetZmg();
	 // KIN1_SoftwareReset();
  }
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
