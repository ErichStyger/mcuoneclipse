/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MK60FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-10-25, 20:11, # CodeGen: 0
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
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "BitIoLdd4.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#ifdef PEcfg_RTOS /* defined in Cpu.h, based on configuration */
  #define USE_FREERTOS  1
#else
  #define USE_FREERTOS  0
#endif

static uint8_t cdc_buffer[USB1_DATA_BUFF_SIZE];
static uint8_t in_buffer[USB1_DATA_BUFF_SIZE];

#if USE_FREERTOS
static portTASK_FUNCTION(MainTask, pvParameters) {
  int i, cnt = 0;
  uint32_t val = 0;
  unsigned char buf[16];
  
  (void)pvParameters; /* not used */
  (void)CDC1_SendString((unsigned char*)"Hello world from the KL25Z with USB CDC\r\n");
  for(;;) {
    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      /* device not enumerated */
      LED1_Neg(); LED2_Off();
      FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
      cnt++;
      if (cnt==100) {
        LED3_Neg();
        cnt = 0;
      }
    }
    LED1_Off(); LED2_Neg(); LED3_Off();
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
      UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"val: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), val);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      (void)CDC1_SendString(buf);
      val++;
    } else {
      cnt++;
      if ((cnt%1024)==0) { /* from time to time, write some text */
        (void)CDC1_SendString((unsigned char*)"Type some text and it will echo.\r\n");
      }
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}
#else
static void CDC_Run(void) {
  int i, cnt = 0;
  uint32_t val = 0;
  unsigned char buf[16];

  (void)CDC1_SendString((unsigned char*)"Hello world from the KL25Z with USB CDC\r\n");
  for(;;) {
    while(CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer))==ERR_BUSOFF) {
      /* device not enumerated */
      LED1_Neg(); LED2_Off();
      WAIT1_Waitms(10);
      cnt++;
      if (cnt==100) {
        LED3_Neg();
        cnt = 0;
      }
    }
    LED1_Off(); LED2_Neg(); LED3_Off();
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
      UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"val: ");
      UTIL1_strcatNum32u(buf, sizeof(buf), val);
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
      (void)CDC1_SendString(buf);
      val++;
    } else {
      WAIT1_Waitms(10);
      cnt++;
      if ((cnt%1024)==0) { /* from time to time, write some text */
        (void)CDC1_SendString((unsigned char*)"Type some text and it will echo.\r\n");
      }
    }
  }
}
#endif

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  LED1_Neg();
  WAIT1_Waitms(200);
  LED2_Neg();
  WAIT1_Waitms(200);
  LED3_Neg();
  WAIT1_Waitms(200);
  LED4_Neg();
  WAIT1_Waitms(200);

#if USE_FREERTOS
  if (FRTOS1_xTaskCreate(MainTask, (signed portCHAR *)"Main", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#else
  CDC_Run();
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
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
