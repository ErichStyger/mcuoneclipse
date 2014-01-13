/** ###################################################################
**     Filename  : Events.c
**     Project   : ProcessorExpert
**     Processor : MC13213
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 2011-02-23, 13:32, # CodeGen: 0
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Platform.h"
#include "Keys.h"
#if PL_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_HAS_RADIO
  #include "Radio.h"
#endif
/*
** ===================================================================
**     Event       :  KB1_OnInterrupt (module Events)
**
**     Component   :  KB1 [KBI]
**     Description :
**         This event is called when the active signal edge/level
**         occurs. This event is enabled only if <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void KB1_OnInterrupt(void)
{
#if PL_HAS_KBI
  KEY_OnInterrupt();
#endif
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
#if PL_HAS_TIMER
  TMR_On10ms();
#endif
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
#if PL_HAS_TIMER
  TMR_On10ms();
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
  Cpu_SetWaitMode();
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
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  SMAC1_ResetIndication (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event in case of transceiver reset.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SMAC1_ResetIndication(void)
{
#if PL_HAS_RADIO
  RADIO_ResetIndication();
#endif
}

/*
** ===================================================================
**     Event       :  PHY1_DataIndicationPacket (module Events)
**
**     Component   :  PHY1 [SPHY]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         sRxPacket       - 
**     Returns     : Nothing
** ===================================================================
*/
void PHY1_DataIndicationPacket(tRxPacket *sRxPacket)
{
#if PL_HAS_RADIO
  RADIO_DataIndicationPacket(sRxPacket);
#else
  (void)sRxPacket;
#endif
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
**       * pxTask          - Pointer to task handle
**       * pcTaskName      - Pointer to 
**     Returns     : Nothing
** ===================================================================
*/
void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, signed portCHAR *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  /* Write your code here ... */
  (void)pxTask; (void)pcTaskName;
  for(;;) {}
}

/*
** ===================================================================
**     Event       :  SMAC_OnInterrupt (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event raised in case of transceiver interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SMAC_OnInterrupt(void)
{
  /* Write your code here ... */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
