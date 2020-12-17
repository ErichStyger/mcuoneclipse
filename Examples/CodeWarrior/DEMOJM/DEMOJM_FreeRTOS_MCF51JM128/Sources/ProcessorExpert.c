/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MCF51JM128VQH
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2013-08-30, 09:39, # CodeGen: 0
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
** @version 01.00
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
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "FRTOS1.h"
#include "VL1swi.h"
#include "TickCntr1.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "UTIL1.h"
#include "MCUC1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED2_Neg();
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void main(void)
{
  /* Write your local variable definition here */
  PEX_RTOS_INIT();

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        (signed portCHAR *)"Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
        Task2,  /* pointer to the task */
        (signed portCHAR *)"Task2", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  
  FRTOS1_vTaskStartScheduler();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
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
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
