/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MK60DN512ZVMD10
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior ARM C Compiler
**     Date/Time   : 2012-05-22, 19:31, # CodeGen: 0
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
#include "USB1.h"
#include "USBInit1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "GPIO1.h"
#include "AS1.h"
#include "WAIT1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];
static LDD_TDeviceData *serialHandle = NULL; /* handle to device data */
volatile uint8_t SentFlag = 0; /* this will be set to 1 once the block has been sent */

static void SendChar(unsigned char ch) {
  SentFlag = 0; /* this will be set to 1 once the block has been sent */
  while(AS1_SendBlock(serialHandle, (LDD_TData*)&ch, 1)!=ERR_OK) {} /* Send char */
  while(SentFlag==0) {} /* wait until we get the green flag from the TX interrupt */
}

static void SendStr(const unsigned char *str) {
  while(*str!='\0') {
    SendChar(*str++);
  }
}

static void CDC_Run(void) {
  int i;

  SendStr((unsigned char*)"Hello World to Kinetis SCI3!\r\n");
  for(;;) {
    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      /* device not enumerated */
      LED1_Neg(); LED2_Off();
     // WAIT1_Waitms(1); /* just give back some CPU time. */
      SendStr((unsigned char*)"waiting to enumerate...\r\n");
   }
    LED1_Off(); LED2_Neg();
    if (CDC1_GetCharsInRxBuf()!=0) {
      i = 0;
      while(   i<sizeof(in_buffer)-1
            && CDC1_GetChar(&in_buffer[i])==ERR_OK
           )
      {
        i++;
      }
      in_buffer[i] = '\0';
      (void)CDC1_SendString((unsigned char*)"echo: ");
      (void)CDC1_SendString(in_buffer);
      (void)CDC1_SendString((unsigned char*)"\r\n");
      SendStr((unsigned char*)"echo to SCI3: ");
      SendStr(in_buffer);
      SendStr((unsigned char*)"\r\n");
    } else {
     // WAIT1_Waitms(5);
    }
  }
}

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  serialHandle = AS1_Init(NULL);
  CDC_Run();

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
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
