/*
** ===================================================================
INFO: empty Drivers\common\GeneralDamage.inc file
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
void FreeRTOS_vOnPreSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used */
#if 0
  /* example for Kinetis (enable SetOperationMode() in CPU component): */
  // Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); /* Processor Expert way to get into WAIT mode */
  /* or to wait for interrupt: */
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
#elif 0
  /* example for S08/S12/ColdFire V1 (enable SetWaitMode() in CPU): */
  Cpu_SetWaitMode();
#elif 0
  /* example for ColdFire V2: */
   __asm("stop #0x2000"); */
#else
   __asm volatile("wfi");
  //#error "you *must* enter low power mode (wait for interrupt) here!"
#endif
  /* Write your code here ... */
}
/*
** ===================================================================
INFO: empty Drivers\common\GeneralDamage.inc file
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
void FreeRTOS_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
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
INFO: empty Drivers\common\GeneralDamage.inc file
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FreeRTOS_vApplicationTickHook(void)
{
  /* Called for every RTOS tick. */
  /* Write your code here ... */
}

/*
** ===================================================================
INFO: empty Drivers\common\GeneralDamage.inc file
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FreeRTOS_vApplicationIdleHook(void)
{
  /* Called whenever the RTOS is idle (from the IDLE task).
     Here would be a good place to put the CPU into low power mode. */
  /* Write your code here ... */
}

/*
** ===================================================================
INFO: empty Drivers\common\GeneralDamage.inc file
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FreeRTOS_vApplicationMallocFailedHook(void)
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

/*
** ===================================================================
INFO: empty Drivers\common\GeneralDamage.inc file
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
void FreeRTOS_vOnPostSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used (yet?) */
  /* Write your code here ... */
}


