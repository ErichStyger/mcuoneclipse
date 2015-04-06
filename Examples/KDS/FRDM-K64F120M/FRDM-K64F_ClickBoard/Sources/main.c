/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-K64F_ClickBoard
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-06, 16:08, # CodeGen: 0
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
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "HF1.h"
#include "UTIL1.h"
#include "SDA.h"
#include "BitIoLdd4.h"
#include "SCL.h"
#include "BitIoLdd5.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "SHT11_driver.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  float temperature, humidity;
  uint8_t res;
  unsigned char buf[32];

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  CLS1_SendStr("\r\n-----------------------\r\nSHT11 Example\r\n-----------------------\r\n", CLS1_GetStdio()->stdOut);
  res = SHT11_SoftReset();
  if (res!=ERR_OK) {
    CLS1_SendStr("FAILED to reset device\r\n ", CLS1_GetStdio()->stdErr);
    for(;;){}
  }
  for(;;) {
    SHT11_Read(&temperature, &humidity);
    CLS1_SendStr("Temperature ", CLS1_GetStdio()->stdOut);
    buf[0] = '\0';
    UTIL1_strcatNum32sDotValue100(buf, sizeof(buf), temperature*100);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    CLS1_SendStr("°C, Humidity ", CLS1_GetStdio()->stdOut);
    buf[0] = '\0';
    UTIL1_strcatNum32sDotValue100(buf, sizeof(buf), humidity*100);
    CLS1_SendStr(buf, CLS1_GetStdio()->stdOut);
    CLS1_SendStr("%\r\n", CLS1_GetStdio()->stdOut);
    WAIT1_Waitms(1000);
    LED1_Neg();
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
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
