/** ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MCF51JM128VLH
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2012-01-17, 18:24, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * pxTask          - Pointer to task handle
**       * pcTaskName      - Pointer to 
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationTickHook(void)
{
  /* Called for every RTOS tick. */
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationIdleHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationIdleHook(void)
{
  /* Called whenever the RTOS is idle (from the IDLE task).
     Here would be a good place to put the CPU into low power mode. */
#if 0
  /* To put the CPU into lower power WAIT mode:
     - Make sure that in the CPU component the method 'SetWaitMode()' is enabled
     - Enable this code block (change '#if 0' to '#if 1')
   */
    Cpu_SetWaitMode();
#endif
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationMallocFailedHook(void)
{
  /* Called if a call to pvPortMalloc() fails because there is insufficient
     free memory available in the FreeRTOS heap.  pvPortMalloc() is called
     internally by FreeRTOS API functions that create tasks, queues, software
     timers, and semaphores.  The size of the FreeRTOS heap is set by the
     configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
  for(;;) {}
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
