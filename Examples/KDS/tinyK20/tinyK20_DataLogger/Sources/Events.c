/* ###################################################################
**     Filename    : Events.c
**     Project     : tinyK20_Demo
**     Processor   : MK20DX128VFT5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-19, 16:16, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
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

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Platform.h"

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX128EX5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

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
  TMOUT1_AddTick();
#if !PL_USE_HW_RTC
  TmDt1_AddTick();
#endif
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

/*
** ===================================================================
**     Event       :  TmDt1_OnTimeSet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         Called in the event of a new time set
**     Parameters  :
**         NAME            - DESCRIPTION
**         hour            - The new hour
**         minute          - The new minute
**         second          - The new second
**         hSecond         - The new 0.01 second part
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_OnTimeSet(uint8_t hour, uint8_t minute, uint8_t second, uint8_t hSecond)
{
#if 0 && PL_USE_HW_RTC
  LDD_RTC_TTime timeDate;

  (void)hSecond; /* not used */
  RTC1_GetTime(RTC1_DeviceData, &timeDate); /* get existing data */
  timeDate.Hour = hour;
  timeDate.Minute = minute;
  timeDate.Second = second;
  RTC1_SetTime(RTC1_DeviceData, &timeDate); /* store back information */
#endif
}

/*
** ===================================================================
**     Event       :  TmDt1_OnDateSet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         called in the event of a date set
**     Parameters  :
**         NAME            - DESCRIPTION
**         day             - the new day
**         month           - the new month
**         year            - the new year
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_OnDateSet(uint8_t day, uint8_t month, uint16_t year)
{
#if 0 && PL_USE_HW_RTC
  LDD_RTC_TTime timeDate;

  RTC1_GetTime(RTC1_DeviceData, &timeDate); /* get existing data */
  timeDate.Day = day;
  timeDate.Month = month;
  timeDate.Year = year;
  RTC1_SetTime(RTC1_DeviceData, &timeDate); /* store back information */
#endif
}

/*
** ===================================================================
**     Event       :  TmDt1_OnTimeGet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         Called in the event of a new time get
**     Parameters  :
**         NAME            - DESCRIPTION
**       * hour            - Pointer to the hour, can be overwritten
**                           in the event routine.
**       * minute          - Pointer to the minute, can be
**                           overwritten in the event routine.
**       * second          - Pointer to the second, can be
**                           overwritten in the event routine.
**       * hSecond         - Pointer to the 0.01 second, can be
**                           overwritten in the event routine.
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_OnTimeGet(uint8_t *hour, uint8_t *minute, uint8_t *second, uint8_t *hSecond)
{
#if 0 && PL_USE_HW_RTC
  LDD_RTC_TTime timeDate;

  RTC1_GetTime(RTC1_DeviceData, &timeDate); /* get existing data */
  *hour = timeDate.Hour;
  *minute = timeDate.Minute;
  *second = timeDate.Second;
  *hSecond = 0; /* not used */
#endif
}

/*
** ===================================================================
**     Event       :  TmDt1_OnDateGet (module Events)
**
**     Component   :  TmDt1 [GenericTimeDate]
**     Description :
**         called in the event of a date get
**     Parameters  :
**         NAME            - DESCRIPTION
**       * day             - Pointer to the day, can be written in the
**                           event routine.
**       * month           - Pointer to the month, can be written
**                           in the event routine.
**       * year            - Pointer to the year, can be written in
**                           the event routine.
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_OnDateGet(uint8_t *day, uint8_t *month, uint16_t *year)
{
#if 0 && PL_USE_HW_RTC
  LDD_RTC_TTime timeDate;

  RTC1_GetTime(RTC1_DeviceData, &timeDate); /* get existing data */
  *day = timeDate.Day;
  *month = timeDate.Month;
  *year = timeDate.Year;
#endif
}

/*
** ===================================================================
**     Event       :  Cpu_OnLLSWakeUpINT (module Events)
**
**     Component   :  Cpu [MK20DX128FT5]
*/
/*!
**     @brief
**         This event is called when Low Leakage WakeUp interrupt
**         occurs. LLWU flags indicating source of the wakeup can be
**         obtained by calling the [GetLLSWakeUpFlags] method. Flags
**         indicating the external pin wakeup source are automatically
**         cleared after this event is executed. It is responsibility
**         of user to clear flags corresponding to internal modules.
**         This event is automatically enabled when [LLWU interrupt
**         request] is enabled.
*/
/* ===================================================================*/
void Cpu_OnLLSWakeUpINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  PTRC1_OnTraceWrap (module Events)
**
**     Component   :  PTRC1 [PercepioTrace]
**     Description :
**         Called for trace ring buffer wrap around. This gives the
**         application a chance to dump the trace buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PTRC1_OnTraceWrap(void)
{
#if 0 /* default implementation for gdb below ... */
  /* Write your code here ... */
  uint8_t buf[64];

  /* GDB: dump binary memory <file> <hexStartAddr> <hexEndAddr> */
  PTRC1_vGetGDBDumpCommand(buf, sizeof(buf), "c:\\tmp\\trc.dump");
#endif
}

/*
** ===================================================================
**     Event       :  SM1_OnBlockSent (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
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
