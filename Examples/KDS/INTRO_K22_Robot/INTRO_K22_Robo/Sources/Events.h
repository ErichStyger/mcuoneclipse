/* ###################################################################
**     Filename    : Events.h
**     Project     : INTRO_K22_Robo
**     Processor   : MK22FX512VLK12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-09-17, 17:16, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "Platform.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "FRTOS1.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "MOTTU.h"
#include "DIRL.h"
#include "BitIoLdd9.h"
#include "PWMR.h"
#include "PwmLdd1.h"
#include "DIRR.h"
#include "BitIoLdd10.h"
#include "PWML.h"
#include "PwmLdd2.h"
#include "I2CSPY1.h"
#include "I2C1.h"
#include "GI2C1.h"
#include "CLS1.h"
#include "AS1.h"
#include "ASerialLdd2.h"
#include "LED_IR.h"
#include "LEDpin1.h"
#include "BitIoLdd11.h"
#include "RefCnt.h"
#include "IR1.h"
#include "BitIoLdd12.h"
#include "IR2.h"
#include "BitIoLdd13.h"
#include "IR3.h"
#include "BitIoLdd14.h"
#include "IR4.h"
#include "BitIoLdd15.h"
#include "IR5.h"
#include "BitIoLdd16.h"
#include "IR6.h"
#include "BitIoLdd17.h"
#include "TRG1.h"
#include "EVNT1.h"
#include "TMOUT1.h"
#include "HF1.h"
#include "Q4CLeft.h"
#include "C11.h"
#include "BitIoLdd18.h"
#include "C21.h"
#include "BitIoLdd19.h"
#include "Q4CRight.h"
#include "C12.h"
#include "BitIoLdd21.h"
#include "C23.h"
#include "BitIoLdd22.h"
#include "LED1.h"
#include "LEDpin2.h"
#include "BitIoLdd25.h"
#include "LED2.h"
#include "LEDpin3.h"
#include "BitIoLdd33.h"
#include "BUZ1.h"
#include "BitIoLdd26.h"
#include "SW1.h"
#include "ExtIntLdd4.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "RNET1.h"
#include "RF1.h"
#include "CE1.h"
#include "BitIoLdd28.h"
#include "CSN1.h"
#include "BitIoLdd29.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "ADC_Bat.h"
#include "CS1.h"
#include "MagInt.h"
#include "ExtIntLdd2.h"
#include "AccelInt.h"
#include "ExtIntLdd3.h"
#include "TU_MCP4728.h"
#include "MCP4728_LDAC.h"
#include "BitIoLdd30.h"
#include "MCP4728_RDY.h"
#include "BitIoLdd31.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "MMA1.h"
#include "QuadInt.h"
#include "TimerIntLdd1.h"
#include "TU_QuadInt.h"
#include "TmDt1.h"
#include "RTC1.h"
#include "XF1.h"
#include "TofPwr.h"
#include "BitIoLdd37.h"
#include "TofCE1.h"
#include "BitIoLdd46.h"
#include "TofCE2.h"
#include "BitIoLdd47.h"
#include "TofCE3.h"
#include "BitIoLdd48.h"
#include "TofCE4.h"
#include "BitIoLdd49.h"
#include "MCUC1.h"
#include "PTRC1.h"
#include "KIN1.h"
#include "RTT1.h"
#include "SYS1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK22FN1M0LQ12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  QuadInt_OnInterrupt (module Events)
**
**     Component   :  QuadInt [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void QuadInt_OnInterrupt(void);

#if PL_HAS_RADIO
void RNET1_OnRadioEvent(RNET1_RadioEvent event);
#endif
/*
** ===================================================================
**     Event       :  RNET1_OnRadioEvent (module Events)
**
**     Component   :  RNET1 [RNet]
**     Description :
**         Event created for various radio states, like timeout, ack
**         received, data sent, ...
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - 
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  TU_US_OnCounterRestart (module Events)
**
**     Component   :  TU_US [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU_US_OnCounterRestart(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  TU_US_OnChannel0 (module Events)
**
**     Component   :  TU_US [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU_US_OnChannel0(LDD_TUserData *UserDataPtr);

void EVNT1_AppHandleEvent(uint8_t event);
/*
** ===================================================================
**     Event       :  EVNT1_AppHandleEvent (module Events)
**
**     Component   :  EVNT1 [SimpleEvents]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - Event (event number) to be processed.
**     Returns     : Nothing
** ===================================================================
*/

void RTOSTRC1_OnTraceWrap(void);
/*
** ===================================================================
**     Event       :  RTOSTRC1_OnTraceWrap (module Events)
**
**     Component   :  RTOSTRC1 [PercepioTrace]
**     Description :
**         Called for trace ring buffer wrap around. This gives the
**         application a chance to dump the trace buffer.
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
**         pxTask          - Task handle
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

/*
** ===================================================================
**     Event       :  Cpu_OnLossOfLockINT (module Events)
**
**     Component   :  Cpu [MK22FN1M0LK12]
*/
/*!
**     @brief
**         This event is called when Loss of Lock interrupt had occured.
**         This event is automatically enabled when either [Loss of
**         lock interrupt] is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnLossOfLockINT(void);

void Tx1_OnItemPut(Tx1_ElementType elem);
/*
** ===================================================================
**     Event       :  Tx1_OnItemPut (module Events)
**
**     Component   :  Tx1 [RingBuffer]
**     Description :
**         Optional event created for every item added with the Put()
**         method.
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - item which gets added
**     Returns     : Nothing
** ===================================================================
*/

void Tx1_OnItemGet(Tx1_ElementType elem);
/*
** ===================================================================
**     Event       :  Tx1_OnItemGet (module Events)
**
**     Component   :  Tx1 [RingBuffer]
**     Description :
**         Optional event created for every item removed with the Get()
**         method.
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - item which gets removed
**     Returns     : Nothing
** ===================================================================
*/

void Tx1_OnClear(void);
/*
** ===================================================================
**     Event       :  Tx1_OnClear (module Events)
**
**     Component   :  Tx1 [RingBuffer]
**     Description :
**         Optional event called in case of Clear() call.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SD1_OnActivate(uint8_t mode);
/*
** ===================================================================
**     Event       :  SD1_OnActivate (module Events)
**
**     Component   :  SD1 [SD_Card]
**     Description :
**         Event called when Activate() method is called. This gives an
**         opportunity to the application to synchronize access to a
**         shared bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SD1_OnDeactivate(uint8_t mode);
/*
** ===================================================================
**     Event       :  SD1_OnDeactivate (module Events)
**
**     Component   :  SD1 [SD_Card]
**     Description :
**         Event called when Deactivate() method is called. This gives
**         an opportunity to the application to synchronize access to a
**         shared bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  SD1_OnBlockReceived (module SD1)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer. This method is available only if
**         the ReceiveBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SD1_OnBlockReceived(LDD_TUserData *UserDataPtr);

void RF1_OnActivate(void);
/*
** ===================================================================
**     Event       :  RF1_OnActivate (module Events)
**
**     Component   :  RF1 [nRF24L01]
**     Description :
**         Event called before accessing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void RF1_OnDeactivate(void);
/*
** ===================================================================
**     Event       :  RF1_OnDeactivate (module Events)
**
**     Component   :  RF1 [nRF24L01]
**     Description :
**         Event called before releasing the bus.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SW1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  SW1_OnInterrupt (module Events)
**
**     Component   :  SW1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void PTRC1_OnTraceWrap(void);
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

void PTRC1_OnTraceStop(void);
/*
** ===================================================================
**     Event       :  PTRC1_OnTraceStop (module Events)
**
**     Component   :  PTRC1 [PercepioTrace]
**     Description :
**         Called if the library calls vTraceStop(). Useful to dump the
**         trace if 'stop when recorder is full' mode is selected.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void PTRC1_OnTraceStart(void);
/*
** ===================================================================
**     Event       :  PTRC1_OnTraceStart (module Events)
**
**     Component   :  PTRC1 [PercepioTrace]
**     Description :
**         Called when vTraceStart() gets called.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void AccelInt_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  AccelInt_OnInterrupt (module Events)
**
**     Component   :  AccelInt [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void MagInt_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  MagInt_OnInterrupt (module Events)
**
**     Component   :  MagInt [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
