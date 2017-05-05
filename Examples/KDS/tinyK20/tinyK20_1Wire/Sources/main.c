/* ###################################################################
**     Filename    : main.c
**     Project     : tinyK20_Blinky
**     Processor   : MK20DX128VFT5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-11, 13:30, # CodeGen: 0
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
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "OW1.h"
#include "DQ1.h"
#include "TU1.h"
#include "OutputRB1.h"
#include "InputRB1.h"
#include "TimeRB1.h"
#include "ProgramRB1.h"
#include "Bit1.h"
#include "BitIoLdd2.h"
#include "Bit2.h"
#include "BitIoLdd3.h"
#include "KIN1.h"
#include "UTIL1.h"
#include "CS1.h"
#include "DS1.h"
#include "SPI1.h"
#include "Clock1.h"
#include "BitIoLdd6.h"
#include "Input1.h"
#include "BitIoLdd7.h"
#include "Output1.h"
#include "BitIoLdd8.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

static void Test(void) {
  bool res;
  uint8_t data, count;

  res = OW1_SendReset();
  if (!res) {
    for(;;){}
  }
  while(OW1_isBusy()) {   /* wait */  }
  WAIT1_Waitms(1);
  res = OW1_SendByte(0x33);
  if (!res) {
    for(;;){}
  }
  while(OW1_isBusy()) {   /* wait */  }
 // WAIT1_Waitms(1);

  res = OW1_Receive(1);

  WAIT1_Waitms(1);

  count = OW1_Count();
  if (!res || count!=1) {
     for(;;){}
   }
  WAIT1_Waitms(1);
  res = OW1_GetByte(&data);
  if (!res) {
     for(;;){}
   }
  WAIT1_Waitms(1);
}

#define RC_READ_ROM          0x33

static void TestDS(void) {
  bool res;
  char *romCode;

   res = DS1_ReadRom(0);
   if (!res) {
     for(;;){}
   }
   WAIT1_Waitms(5);
   romCode = DS1_GetRomCode(0);
   WAIT1_Waitms(5);
   WAIT1_Waitms(5);
}

static void ReadTemp(void) {
  int32_t temperature;
  float f;
  bool res;

  res = DS1_StartConversion(0);
  //WAIT1_Waitms(5);
  res = DS1_ReadTemperature(0);
  //WAIT1_Waitms(5);
  temperature = DS1_GetTemperatureRaw(0);
  f = DS1_GetTemperatureFloat(0);
  WAIT1_Waitms(5);
}

static void Test2(void) {
  bool res;

  OW1_SendReset();
  while(OW1_isBusy()) {
     /* wait */
   }
  OW1_SendByte(RC_READ_ROM);
  while(OW1_isBusy()) {
     /* wait */
   }
  OW1_Receive(8);
  while(OW1_isBusy()) {
     /* wait */
   }
  OW1_SendByte(0xFF);
  while(OW1_isBusy()) {
     /* wait */
   }
  //OW1_ProgramEvent(EV_READ_ROM);
  while(OW1_isBusy()) {
     /* wait */
   }

   WAIT1_Waitms(5);
   res = DS1_ReadRom(0);
   if (!res) {
     for(;;){}
   }
   WAIT1_Waitms(5);
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/


  ReadTemp();
  //Test();
  //TestDS();
  //Test2();
#if 0
  {
    bool res;
    uint8_t data;
    OW1_Error err;
    char *romCode;
#if 0
    res = OW1_SendReset();
    if (!res) {
      for(;;){}
    }
    WAIT1_Waitms(2);
    res = OW1_SendByte(0x33);
    if (!res) {
      for(;;){}
    }
    WAIT1_Waitms(2);

#endif


    res = DS1_ReadRom(0);
    if (!res) {
      for(;;){}
    }
    while(OW1_isBusy()) {
      /* wait */
    }
    WAIT1_Waitms(5);

    romCode = DS1_GetRomCode(0);

    WAIT1_Waitms(10);

    OW1_SendReset();
    /* slave should respond with presence pulse */
    WAIT1_Waitms(1);

    err = OW1_GetError();
    if (err!=OWERR_OK) {
      LED1_On();
    }
    //res = OW1_GetByte(&data);
    OW1_SendByte(0x55); /* match ROM */

  }
#endif
  WAIT1_Waitms(5);
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(500);
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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
