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
#include "pins_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Events.h"
#include "Events.c"

static void AppTask(void *param) {
  (void)param;
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  } /* for */
}


static void Components_Init(void) {
  #define CPU_INIT_MCUONECLIPSE_DRIVERS
  /* IMPORTANT: copy the content from Cpu.c! */
/*------------------------------------------------------------------*/
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  MCUC1_Init(); /* ### McuLibConfig "MCUC1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  UTIL1_Init(); /* ### Utility "UTIL1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  CS1_Init(); /* ### CriticalSection "CS1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  XF1_Init(); /* ### XFormat "XF1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  CLS1_Init(); /* ### Shell "CLS1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  WAIT1_Init(); /* ### Wait "WAIT1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  RTT1_Init(); /* ### SeggerRTT "RTT1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  SYS1_Init(); /* ### SeggerSystemView "SYS1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  /* PEX_RTOS_INIT() is a macro should already have been called either from main()
     or Processor Expert startup code. So we don't call it here again. */
  /* PEX_RTOS_INIT(); */ /* ### FreeRTOS "FreeRTOS" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  RNG1_Init(); /* ### RingBuffer "RNG1" init code ... */
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
  GFONT1_Init(); /* ### GFont "GFONT1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  GDisp1_Init(); /* ### GDisplay "GDisp1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  FDisp1_Init(); /* ### FontDisplay "FDisp1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  HF1_Init(); /* ### HardFault "HF1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
#if MMA1_CONFIG_INIT_DRIVER_IN_STARTUP
  MMA1_Init(); /* ### MMA8451Q "MMA1" init code ... */
#endif
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  KIN1_Init(); /* ### KinetisTools "KIN1" init code ... */
#endif
/*------------------------------------------------------------------*/
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
  Components_Init();

  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();

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
