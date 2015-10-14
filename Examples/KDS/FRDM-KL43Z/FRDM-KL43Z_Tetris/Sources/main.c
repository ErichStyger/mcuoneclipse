/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KL43Z_Tetris
**     Processor   : MKL43Z256VLH4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-10-14, 14:10, # CodeGen: 0
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
#include "osa1.h"
#include "pin_mux.h"
#include "gpio1.h"
#include "DbgCs1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Tetris.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

#if 0
  for(;;) {
    GPIO_DRV_TogglePinOutput(LED1);
    OSA_TimeDelay(500);
    GPIO_DRV_TogglePinOutput(LED2);
    OSA_TimeDelay(500);
    debug_printf("hello\r\n");
    if (!GPIO_DRV_ReadPinInput(Button1)) {
      debug_printf("Button1\r\n");
    }
    if (!GPIO_DRV_ReadPinInput(Button2)) {
      debug_printf("Button2\r\n");
    }
  }
#else
  TETRIS_Start();
  for(;;) {
    GPIO_DRV_TogglePinOutput(LED1);
    OSA_TimeDelay(50);
    if (TETRIS_Run()==0) {
      TETRIS_Start();
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
