/** ###################################################################
**     Filename  : TWR_S12G240_FreeRTOS.c
**     Project   : TWR_S12G240_FreeRTOS
**     Processor : MC9S12G240CLL
**     Version   : Driver 01.14
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 04.09.2018, 14:00
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE TWR_S12G240_FreeRTOS */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
static void appTask(void *pvParameters) {
  (void)pvParameters;
  for (;;) {
    LED1_Neg();
    LED2_Neg();
    LED3_Neg();
    LED4_Neg();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
 	if (xTaskCreate(appTask, "app", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS)  {
		for(;;){}
	}
	vTaskStartScheduler();

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END TWR_S12G240_FreeRTOS */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.03 [04.46]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
