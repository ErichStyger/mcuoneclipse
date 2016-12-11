/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K22F_FreeRTOS_ADC
**     Processor   : MK22FN512VDC12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-11-23, 14:46, # CodeGen: 0
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
#include "FRTOS1.h"
#include "UTIL1.h"
#include "MCUC1.h"
#include "LED1.h"
#include "LEDpin4.h"
#include "BitIoLdd4.h"
#include "LED2.h"
#include "LEDpin5.h"
#include "BitIoLdd5.h"
#include "LED3.h"
#include "LEDpin6.h"
#include "BitIoLdd6.h"
#include "PTRC1.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "XF1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

static void AppTask(void *pvParameters) {

  vTraceEnable(TRC_INIT);
  (void)pvParameters; /* parameter not used */
  for(;;) {
    vTaskDelay(500/portTICK_PERIOD_MS);
    LED1_Neg(); /* Red LED */
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
#if TRC_CFG_RECORDER_MODE==TRC_RECORDER_MODE_SNAPSHOT
  vTraceEnable(TRC_START); /* e.g., in task context, at some relevant event */
#endif
  /* Write your code here */
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "Main", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE+200, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
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
