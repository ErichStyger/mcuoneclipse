/* ###################################################################
**     Filename    : Events.c
**     Project     : tinyK22_NeoPixel
**     Processor   : MK22FN512VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-07-14, 07:01, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK22FN512DC12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  DMACH1_OnComplete (module Events)
**
**     Component   :  DMACH1 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is enabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. You can use GetTransferCompleteStatus() in
**         order to distinguish "Full complete" and "Half complete"
**         case. See SetEventMask() and GetEventMask() methods.
**         [Note:] If Half complete is enabled and interrupts are
**         disabled or your code doesn't handle OnComplete event before
**         all data are transferred by DMA peripheral, OnComplete event
**         will be invoked only once and GetTransferCompleteStatus()
**         called from this event will always return TRUE = "Full
**         complete".
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH1_OnComplete(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  DMACH1_OnError (module Events)
**
**     Component   :  DMACH1 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH1_OnError(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  DMACH3_OnComplete (module Events)
**
**     Component   :  DMACH3 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is enabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. You can use GetTransferCompleteStatus() in
**         order to distinguish "Full complete" and "Half complete"
**         case. See SetEventMask() and GetEventMask() methods.
**         [Note:] If Half complete is enabled and interrupts are
**         disabled or your code doesn't handle OnComplete event before
**         all data are transferred by DMA peripheral, OnComplete event
**         will be invoked only once and GetTransferCompleteStatus()
**         called from this event will always return TRUE = "Full
**         complete".
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH3_OnComplete(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  DMACH3_OnError (module Events)
**
**     Component   :  DMACH3 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH3_OnError(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  DMACH2_OnComplete (module Events)
**
**     Component   :  DMACH2 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is enabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. You can use GetTransferCompleteStatus() in
**         order to distinguish "Full complete" and "Half complete"
**         case. See SetEventMask() and GetEventMask() methods.
**         [Note:] If Half complete is enabled and interrupts are
**         disabled or your code doesn't handle OnComplete event before
**         all data are transferred by DMA peripheral, OnComplete event
**         will be invoked only once and GetTransferCompleteStatus()
**         called from this event will always return TRUE = "Full
**         complete".
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH2_OnComplete(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  DMACH2_OnError (module Events)
**
**     Component   :  DMACH2 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH2_OnError(LDD_TUserData *UserDataPtr)
{
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
INFO: empty Drivers\common\GeneralDamage.inc file
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
  TMOUT1_AddTick();
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
void FRTOS1_vApplicationIdleHook(void)
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

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
