/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KL02Z_UART
**     Processor   : MKL02Z32VFM4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-04-11, 14:05, # CodeGen: 0
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
#include "WAIT1.h"
#include "LED1.h"
#include "Inhr1.h"
#include "PwmLdd1.h"
#include "LED2.h"
#include "Inhr2.h"
#include "PwmLdd2.h"
#include "LED3.h"
#include "Inhr3.h"
#include "PwmLdd3.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "XF1.h"
#include "MCUC1.h"
#include "MMA1.h"
#include "GI2C1.h"
#include "CI2C1.h"
#include "IntI2cLdd1.h"
#include "TU1.h"
#include "TU0.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
static unsigned char buffer[64];

static const CLS1_ConstParseCommandCallback cmdTable[] =
{
    CLS1_ParseCommand,
    LED1_ParseCommand,
    LED2_ParseCommand,
    LED3_ParseCommand,
    MMA1_ParseCommand,
    NULL/* sentinel */
};

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  int i;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  MMA1_Init();
  for(i=0;i<5;i++) {
    LED1_On();
    LED2_On();
    LED3_On();
    WAIT1_Waitms(200);
    LED2_Off();
    LED3_Off();
    LED1_Off();
    WAIT1_Waitms(100);
  }
  buffer[0] = '\0'; /* initialize buffer for ReadLine() */
  CLS1_SendStr("\r\nType 'help' with CR or LF at the end...\r\n", CLS1_GetStdio()->stdOut);
  for(;;) {
    //LED1_Neg();
    WAIT1_Waitms(200);
    (void)CLS1_ReadAndParseWithCommandTable(buffer, sizeof(buffer), CLS1_GetStdio(), cmdTable);
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
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
