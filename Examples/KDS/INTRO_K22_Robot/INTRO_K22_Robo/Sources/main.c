/* ###################################################################
**     Filename    : main.c
**     Project     : INTRO_K22_Robo
**     Processor   : MK22FX512VLK12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-09-17, 17:16, # CodeGen: 0
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

#include "Platform.h"
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "MOTTU.h"
#include "DIRL.h"
#include "BitIoLdd9.h"
#include "PWMR.h"
#include "PwmLdd1.h"
#include "DIRR.h"
#include "BitIoLdd10.h"
#include "PWML.h"
#include "PwmLdd2.h"
#include "I2CSPY1.h"
#include "I2C1.h"
#include "GI2C1.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd2.h"
#include "LED_IR.h"
#include "LEDpin1.h"
#include "BitIoLdd11.h"
#include "RefCnt.h"
#include "IR1.h"
#include "BitIoLdd12.h"
#include "IR2.h"
#include "BitIoLdd13.h"
#include "IR3.h"
#include "BitIoLdd14.h"
#include "IR4.h"
#include "BitIoLdd15.h"
#include "IR5.h"
#include "BitIoLdd16.h"
#include "IR6.h"
#include "BitIoLdd17.h"
#include "TRG1.h"
#include "EVNT1.h"
#include "TMOUT1.h"
#include "HF1.h"
#include "Q4CLeft.h"
#include "C11.h"
#include "BitIoLdd18.h"
#include "C21.h"
#include "BitIoLdd19.h"
#include "Q4CRight.h"
#include "C12.h"
#include "BitIoLdd21.h"
#include "C23.h"
#include "BitIoLdd22.h"
#include "LED1.h"
#include "LEDpin2.h"
#include "BitIoLdd25.h"
#include "LED2.h"
#include "LEDpin3.h"
#include "BitIoLdd33.h"
#include "BUZ1.h"
#include "BitIoLdd26.h"
#include "SW1.h"
#include "ExtIntLdd4.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "RNET1.h"
#include "RF1.h"
#include "CE1.h"
#include "BitIoLdd28.h"
#include "CSN1.h"
#include "BitIoLdd29.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "ADC_Bat.h"
#include "CS1.h"
#include "MagInt.h"
#include "ExtIntLdd2.h"
#include "AccelInt.h"
#include "ExtIntLdd3.h"
#include "TU_MCP4728.h"
#include "MCP4728_LDAC.h"
#include "BitIoLdd30.h"
#include "MCP4728_RDY.h"
#include "BitIoLdd31.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "MMA1.h"
#include "QuadInt.h"
#include "TimerIntLdd1.h"
#include "TU_QuadInt.h"
#include "TmDt1.h"
#include "RTC1.h"
#include "XF1.h"
#include "TofPwr.h"
#include "BitIoLdd37.h"
#include "TofCE1.h"
#include "BitIoLdd46.h"
#include "TofCE2.h"
#include "BitIoLdd47.h"
#include "TofCE3.h"
#include "BitIoLdd48.h"
#include "TofCE4.h"
#include "BitIoLdd49.h"
#include "MCUC1.h"
#include "PTRC1.h"
#include "KIN1.h"
#include "RTT1.h"
#include "SYS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  APP_Run();
  //SEGGER_RTT_printf(0, "%sResetting in %d second..%s\n", RTT_CTRL_BG_BRIGHT_RED, 1, RTT_CTRL_RESET);
  //RTT1_printf(0, "Hello%s", "h");

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
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
