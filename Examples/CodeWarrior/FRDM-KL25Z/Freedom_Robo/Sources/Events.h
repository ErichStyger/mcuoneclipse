/** ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-01-02, 18:58, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "WAIT1.h"
#include "DIRL.h"
#include "BitIoLdd14.h"
#include "DIRR.h"
#include "BitIoLdd13.h"
#include "BrakeL.h"
#include "BitIoLdd15.h"
#include "BrakeR.h"
#include "BitIoLdd16.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "TRG1.h"
#include "LED_IR.h"
#include "LEDpin4.h"
#include "BitIoLdd4.h"
#include "IR1.h"
#include "BitIoLdd6.h"
#include "IR2.h"
#include "BitIoLdd10.h"
#include "IR3.h"
#include "BitIoLdd5.h"
#include "IR4.h"
#include "BitIoLdd7.h"
#include "IR5.h"
#include "BitIoLdd8.h"
#include "IR6.h"
#include "BitIoLdd9.h"
#include "IR7.h"
#include "BitIoLdd11.h"
#include "IR8.h"
#include "BitIoLdd12.h"
#include "RefCnt.h"
#include "SW1.h"
#include "BitIoLdd17.h"
#include "BT1.h"
#include "Serial2.h"
#include "ASerialLdd3.h"
#include "HF1.h"
#include "Q4CLeft.h"
#include "C13.h"
#include "BitIoLdd24.h"
#include "C24.h"
#include "BitIoLdd25.h"
#include "Q4CRight.h"
#include "C14.h"
#include "BitIoLdd27.h"
#include "C26.h"
#include "BitIoLdd28.h"
#include "CS1.h"
#include "MCUC1.h"
#include "XF1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "TU3.h"
#include "PWML.h"
#include "PwmLdd1.h"
#include "TU4.h"
#include "PWMR.h"
#include "PwmLdd2.h"
#include "TU_US.h"
#include "TRIG.h"
#include "TMOUT1.h"
#include "CLS1.h"
#include "PE_LDD.h"

void Cpu_OnNMIINT(void);
/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
**     Description :
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the <NMI
**         interrrupt> property is set to 'Enabled'.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
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
**       * pcTaskName      - Pointer to task name
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

void TU_US_OnCounterRestart(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Event       :  TU_US_OnCounterRestart (module Events)
**
**     Component   :  TU_US [TimerUnit_LDD]
**     Description :
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         <SetEventMask> and <GetEventMask> methods. This event is
**         available only if a <Interrupt> is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
**     Returns     : Nothing
** ===================================================================
*/

void TU_US_OnChannel0(LDD_TUserData *UserDataPtr);
/*
** ===================================================================
**     Event       :  TU_US_OnChannel0 (module Events)
**
**     Component   :  TU_US [TimerUnit_LDD]
**     Description :
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See <SetEventMask> and
**         <GetEventMask> methods. This event is available only if a
**         <Interrupt> is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  Serial1_OnError (module Events)
**
**     Component   :  Serial1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
** ===================================================================
**     Event       :  Serial1_OnRxChar (module Events)
**
**     Component   :  Serial1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
** ===================================================================
**     Event       :  Serial1_OnTxChar (module Events)
**
**     Component   :  Serial1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
** ===================================================================
**     Event       :  Serial1_OnFullRxBuf (module Events)
**
**     Component   :  Serial1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
** ===================================================================
**     Event       :  Serial1_OnFreeTxBuf (module Events)
**
**     Component   :  Serial1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Q4CLeft_OnError(void);
/*
** ===================================================================
**     Event       :  Q4CLeft_OnError (module Events)
**
**     Component   :  Q4CLeft [QuadCounter]
**     Description :
**         Called in case of a failure during decoding.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
