/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-02-12, 16:30, # CodeGen: 0
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
#include "SYS1.h"
#include "HF1.h"
#include "UTIL1.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "BT1.h"
#include "Serial1.h"
#include "ASerialLdd1.h"
#include "CS1.h"
#include "AS1.h"
#include "ASerialLdd2.h"
#include "FX1.h"
#include "GI2C1.h"
#include "I2C.h"
#include "FAT1.h"
#include "TmDt1.h"
#include "FATM1.h"
#include "SS1.h"
#include "CD2.h"
#include "SM2.h"
#include "MINI1.h"
#include "TMOUT1.h"
#include "KEY1.h"
#include "Inhr1.h"
#include "BitIoLdd8.h"
#include "Inhr2.h"
#include "BitIoLdd9.h"
#include "TRG1.h"
#include "KIN1.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "RTT1.h"
#include "XF1.h"
#include "MCUC1.h"
#include "Dir0.h"
#include "BitIoLdd16.h"
#include "Step0.h"
#include "BitIoLdd17.h"
#include "TU1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "Step1.h"
#include "BitIoLdd19.h"
#include "Dir1.h"
#include "BitIoLdd20.h"
#include "Dir3.h"
#include "BitIoLdd21.h"
#include "Step3.h"
#include "BitIoLdd24.h"
#include "Dir4.h"
#include "BitIoLdd25.h"
#include "Step4.h"
#include "BitIoLdd26.h"
#include "Dir5.h"
#include "BitIoLdd15.h"
#include "Step6.h"
#include "BitIoLdd28.h"
#include "Dir6.h"
#include "BitIoLdd27.h"
#include "Step7.h"
#include "BitIoLdd30.h"
#include "Dir7.h"
#include "BitIoLdd29.h"
#include "PTRC1.h"
#include "Step5.h"
#include "BitIoLdd18.h"
#include "Dir2.h"
#include "BitIoLdd23.h"
#include "Step2.h"
#include "BitIoLdd22.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Platform.h"
#include "Application.h"

#include "PORT_PDD.h"
#include "gcov_support.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
#if GCOV_DO_COVERAGE
  gcov_init();
  if (!gcov_check()) {
    for(;;) {} /* failed to use file system!?! */
  }
#endif
  /* Write your local variable definition here */
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

#if PL_HAS_SD_CARD
  /* SD card detection: PTE6 with pull-down! */
  PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 6, PORT_PDD_PULL_DOWN);
  PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);
#endif
#if PL_HAS_KEYS
  /* SW3: PTA4 */
  PORT_PDD_SetPinPullSelect(PORTA_BASE_PTR, 4, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTA_BASE_PTR, 4, PORT_PDD_PULL_ENABLE);
  /* SW2: PTC6 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 6, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 6, PORT_PDD_PULL_ENABLE);
#endif
#if PL_HAS_BLUETOOTH
  /* pull up Rx pin (PTC14) for Bluetooth module */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 14, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 14, PORT_PDD_PULL_ENABLE);
#endif
  LED1_On();
  WAIT1_Waitms(50);
  LED1_Off();
  WAIT1_Waitms(50);
  LED2_On();
  WAIT1_Waitms(50);
  LED2_Off();
  WAIT1_Waitms(50);
  LED3_On();
  WAIT1_Waitms(50);
  LED3_Off();
  WAIT1_Waitms(50);
  APP_Start();

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
