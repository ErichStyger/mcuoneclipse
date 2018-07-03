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

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Events.h"
#include "Events.c" /* need to include the .c file! */

static void AppTask(void *param) {
	(void)param;
	for(;;) {
	  PINS_DRV_TogglePins(PTD, (1<<15U));
	  vTaskDelay(pdMS_TO_TICKS(1000));
	} /* for */
}

static void Components_Init(void) {
  #define CPU_INIT_MCUONECLIPSE_DRIVERS
  /* IMPORTANT: copy the content from Cpu.c! */
/*------------------------------------------------------------------*/
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  /* ### McuLibConfig "MCUC1" init code ... */
  MCUC1_Init();
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  UTIL1_Init(); /* ### Utility "UTIL1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  WAIT1_Init(); /* ### Wait "WAIT1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  XF1_Init(); /* ### XFormat "XF1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  CS1_Init(); /* ### CriticalSection "CS1" init code ... */
#endif
#ifdef CPU_INIT_MCUONECLIPSE_DRIVERS
  CLS1_Init(); /* ### Shell "CLS1" init code ... */
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
  /* PEX_RTOS_INIT(); */ /* ### FreeRTOS "FRTOS1" init code ... */
#endif
/*------------------------------------------------------------------*/
}

#if configUSE_TICKLESS_IDLE_DECISION_HOOK
BaseType_t xEnterTicklessIdle(void) {
  return pdTRUE; /* yes, enter tickless idle mode */
}
#endif

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
  CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
  CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_FORCIBLE);
  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
  PINS_DRV_SetPinsDirection(PTD,  (1<<0U) | (1<<15U) | (1<<16U)); /* set as output */
  PINS_DRV_SetPins(PTD, (1<<0U) | (1<<15U) | (1<<16U)); /* all off */
  PINS_DRV_ClearPins(PTD, (1<<15U));
  PINS_DRV_TogglePins(PTD, (1<<15U));
  Components_Init();

  if (xTaskCreate(AppTask, "App", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    __asm volatile("nop");
  }
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
