/** ###################################################################
**     Filename  : Events.h
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

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "LED5.h"
#include "KB1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "TI1.h"
#include "Buzzer.h"
#include "AD1.h"
#include "ACCEL1.h"
#include "G11.h"
#include "G21.h"
#include "Sleep1.h"
#include "TEMP1.h"
#include "SMAC1.h"
#include "PHY1.h"
#include "Security1.h"
#include "TRSVR1.h"
#include "CE1.h"
#include "RESET1.h"
#include "RTXEN1.h"
#include "ATTN1.h"
#include "IRQ1.h"
#include "SM1.h"
#include "AS1.h"
#include "TMOUT1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "CLS1.h"

void KB1_OnInterrupt(void);
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

void TI1_OnInterrupt(void);
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


void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, signed portCHAR *pcTaskName);
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

void FRTOS1_vApplicationTickHook(void);
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

void FRTOS1_vApplicationIdleHook(void);
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

void FRTOS1_vApplicationMallocFailedHook(void);
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

void SMAC1_ResetIndication(void);
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

void PHY1_DataIndicationPacket(tRxPacket *sRxPacket);
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

void SMAC_OnInterrupt(void);
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

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
