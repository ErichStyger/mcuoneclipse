/*
 * FreeRTOShooks.c
 *
 * Copyright (c) 2019, 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 *  This is a default FreeRTOS hooks file you can use in your application.
 */

#include "McuLibconfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "McuTimeDate.h"

/*
** ===================================================================
**     Event       :  McuRTOS_vApplicationStackOverflowHook (module Events)
**
**     Component   :  McuRTOS [McuRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**         pxTask          - Task handle
**       * pcTaskName      - Pointer to task name
**     Returns     : Nothing
** ===================================================================
*/
void McuRTOS_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M
    __asm volatile("bkpt #0");
#elif McuLib_CONFIG_CPU_IS_RISC_V
    __asm volatile( "ebreak" );
#endif
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  McuRTOS_vApplicationMallocFailedHook (module Events)
**
**     Component   :  McuRTOS [McuRTOS]
**     Description :
**         If enabled, the McuRTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuRTOS_vApplicationMallocFailedHook(void)
{
  /* Called if a call to pvPortMalloc() fails because there is insufficient
     free memory available in the McuRTOS heap.  pvPortMalloc() is called
     internally by McuRTOS API functions that create tasks, queues, software
     timers, and semaphores.  The size of the McuRTOS heap is set by the
     configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
  taskDISABLE_INTERRUPTS();
  /* Write your code here ... */
#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M
    __asm volatile("bkpt #0");
#elif McuLib_CONFIG_CPU_IS_RISC_V
    __asm volatile( "ebreak" );
#endif
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  McuRTOS_vApplicationTickHook (module Events)
**
**     Component   :  McuRTOS [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuRTOS_vApplicationTickHook(void)
{
  McuTimeDate_AddTick();
}

/*
** ===================================================================
**     Event       :  McuRTOS_vApplicationIdleHook (module Events)
**
**     Component   :  McuRTOS [FreeRTOS]
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuRTOS_vApplicationIdleHook(void)
{
  /* Called whenever the RTOS is idle (from the IDLE task).
     Here would be a good place to put the CPU into low power mode. */
  //__asm volatile("wfi");
}


/*
** ===================================================================
**     Description :
**         Used in tickless idle mode only, but required in this mode.
**         Hook for the application to enter low power mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         expectedIdleTicks - expected idle
**                           time, in ticks
**     Returns     : Nothing
** ===================================================================
*/
void McuRTOS_vOnPreSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used */
#if McuLib_CONFIG_CPU_IS_ARM_CORTEX_M
  /* example for ARM Cortex-M (enable SetOperationMode() in CPU component): */
  /* Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); */ /* Processor Expert way to get into WAIT mode */
  /* or to wait for interrupt: */
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
#elif McuLib_CONFIG_CPU_IS_RISC_V
  #warning "NYI"
#elif 0
  /* example for S08/S12/ColdFire V1 (enable SetWaitMode() in CPU): */
  Cpu_SetWaitMode();
#elif 0
  /* example for ColdFire V2: */
   __asm("stop #0x2000"); */
#else
  #error "you *must* enter low power mode (wait for interrupt) here!"
#endif
  /* Write your code here ... */
}

/*
** ===================================================================
**     Description :
**         Event called after the CPU woke up after low power mode.
**         This event is optional.
**     Parameters  :
**         NAME            - DESCRIPTION
**         expectedIdleTicks - expected idle
**                           time, in ticks
**     Returns     : Nothing
** ===================================================================
*/
void McuRTOS_vOnPostSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used (yet?) */
  /* Write your code here ... */
}
