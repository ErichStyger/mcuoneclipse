/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2012-12-20, 19:11, # CodeGen: 0
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
#include "WAIT1.h"
#include "LCD1.h"
#include "RW1.h"
#include "BitIoLdd12.h"
#include "EN1.h"
#include "BitIoLdd1.h"
#include "RS1.h"
#include "BitIoLdd2.h"
#include "Inhr1.h"
#include "BitIoLdd4.h"
#include "DB51.h"
#include "BitIoLdd9.h"
#include "DB61.h"
#include "BitIoLdd10.h"
#include "DB71.h"
#include "BitIoLdd11.h"
#include "UTIL1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#if 0
static void LCD_Demo1(void) {
  uint8_t cnt;
  uint8_t buf[5];
  
  LCD1_Clear();
  LCD1_WriteLineStr(1, "Hello FRDM-KL25Z");
  cnt = 0;
  for(;;) {
    LCD1_GotoXY(2,1);
    UTIL1_Num16uToStr(buf, sizeof(buf), cnt);
    LCD1_WriteString((char*)buf);
    cnt++;
    WAIT1_Waitms(100);
  }
}
#else
/* LCD Demo with an LCD having two E lines (E1 and E2): that makes 2x2 lines */
static void LCD_Demo1(void) {
  uint8_t cnt;
  uint8_t buf[5];
  
  LCD1_UseDisplay(1);  /* switch to upper/first display */
  LCD1_Clear();
  LCD1_WriteLineStr(1, "Hello LCD 1");
  
  LCD1_UseDisplay(2);  /* switch to second display */
  LCD1_Clear();
  LCD1_WriteLineStr(1, "Hello LCD 2");
  cnt = 0;
  for(;;) {
    UTIL1_Num16uToStr(buf, sizeof(buf), cnt);
    LCD1_UseDisplay(1);  /* switch to first display */
    LCD1_GotoXY(2,1);
    LCD1_WriteString((char*)buf);
    LCD1_UseDisplay(2);  /* switch to second display */
    LCD1_GotoXY(2,1);
    LCD1_WriteString((char*)buf);
    cnt++;
    WAIT1_Waitms(100);
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

  /* Write your code here */
  LCD_Demo1();
  
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
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
