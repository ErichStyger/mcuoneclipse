/* ###################################################################
**     Filename    : main.c
**     Project     : TWR-S08MM128_Demo
**     Processor   : MC9S08MM128VMB
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2016-11-07, 18:40, # CodeGen: 0
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
** @version 01.12
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
#include "WAIT1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "KSDK1.h"
#include "IFsh1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
//static uint8_t data[] = {0xff,0xff,0xff,0xff,0xff};
static uint8_t data[] = {0x1,0x2,0x3,0x4,0x5};
#define FLASH_ADDR 0xE000

static void TestFlash(void) {
    //IFsh1_Init();
	LED3_On();
	WAIT1_Waitms(500);
#if 1
	if (IFsh1_EraseSector(FLASH_ADDR)!=ERR_OK) {
		  for(;;) {
			  LED1_Neg();
			  WAIT1_Waitms(50);
		  }
	}
	if (IFsh1_SetBlockFlash(&data[0], FLASH_ADDR, sizeof(data))!=ERR_OK) {
		  for(;;) {
			  LED2_Neg();
			  WAIT1_Waitms(100);
		  }
	}
#endif
	LED3_Off();
}

const unsigned char boot@0x040A = 0x00;   //zero out checksum to bypass boot loader


void main(void)
{
  /* Write your local variable definition here */
  int i = 0;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;) {
	  i++;
	  if ((i%5)==0) {
		  data[0]++; /* change data */
		  TestFlash();
	  }
	  LED1_Neg();
	  WAIT1_Waitms(250);
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

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
