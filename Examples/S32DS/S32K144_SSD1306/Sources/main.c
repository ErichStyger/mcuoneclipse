/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K14x
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
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"

  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */
//#include "FreeRTOS.h"
//#include "task.h"
//#include "Events.h"
//#include "Events.c"

static void Components_Init(void) {
  #define CPU_INIT_MCUONECLIPSE_DRIVERS
  /* IMPORTANT: copy the content from Cpu.c! */
  /*------------------------------------------------------------------*/
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  MCUC1_Init(); /* ### McuLibConfig "MCUC1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  GFONT1_Init(); /* ### GFont "GFONT1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  WAIT1_Init(); /* ### Wait "WAIT1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  SDA1_Init(); /* ### SDK_BitIO "SDA1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  SCL1_Init(); /* ### SDK_BitIO "SCL1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  I2C1_Init(); /* ### GenericSWI2C "I2C1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  GI2C1_Init(); /* ### GenericI2C "GI2C1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  LCD1_Init(); /* ### SSD1306 "LCD1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  GDisp1_Init(); /* ### GDisplay "GDisp1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  FDisp1_Init(); /* ### FontDisplay "FDisp1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  LEDpin1_Init(); /* ### SDK_BitIO "LEDpin1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  LEDR_Init(); /* ### LED "LEDR" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  LEDpin2_Init(); /* ### SDK_BitIO "LEDpin2" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  LEDG_Init(); /* ### LED "LEDG" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  LEDpin3_Init(); /* ### SDK_BitIO "LEDpin3" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  LEDB_Init(); /* ### LED "LEDB" init code ... */
#endif
  /*------------------------------------------------------------------*/
}

static void TestLCD(void) {
  FDisp1_PixelDim x, y;
  for(;;) {
    GDisp1_Clear();
    GDisp1_DrawBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), 1, GDisp1_COLOR_WHITE);
    x = 2; y = 2;
    FDisp1_WriteString((uint8_t*)"hello world", GDisp1_COLOR_WHITE, &x, &y, GFONT1_GetFont());
    GDisp1_DrawBox(20, 20, 20, 40, 1, GDisp1_COLOR_WHITE);
    GDisp1_DrawCircle(40, 40, 15, GDisp1_COLOR_WHITE);
    GDisp1_UpdateFull();
  }
}

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
  CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_FORCIBLE);
  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

  Components_Init();

  LEDR_On();
  LEDR_Off();
  LEDG_On();
  LEDG_Off();
  LEDB_On();
  LEDB_Off();

  TestLCD();
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
