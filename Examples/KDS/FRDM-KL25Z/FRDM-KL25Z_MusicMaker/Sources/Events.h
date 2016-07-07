/* ###################################################################
**     Filename    : Events.h
**     Project     : FRDM-KL25Z_MusicMaker
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-11-18, 13:26, # CodeGen: 0
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

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "FRTOS1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "TmDt1.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "SM1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SS2.h"
#include "CD2.h"
#include "UTIL1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
#include "CS1.h"
#include "PTD.h"
#include "MCS.h"
#include "BitIoLdd4.h"
#include "DCS.h"
#include "BitIoLdd6.h"
#include "DREQ.h"
#include "BitIoLdd5.h"
#include "KSDK1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName);
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
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
