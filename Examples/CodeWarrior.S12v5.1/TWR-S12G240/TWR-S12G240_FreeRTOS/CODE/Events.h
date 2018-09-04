/* ###################################################################
**     Filename    : Events.h
**     Project     : TWR_S12G240_FreeRTOS
**     Processor   : MC9S12G240CLL
**     Component   : Events
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior HC12 C Compiler
**     Date/Time   : 04.09.2018, 14:00
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         FRTOS1_vApplicationStackOverflowHook - void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char...
**         FRTOS1_vApplicationTickHook          - void FRTOS1_vApplicationTickHook(void);
**         FRTOS1_vApplicationIdleHook          - void FRTOS1_vApplicationIdleHook(void);
**         FRTOS1_vApplicationMallocFailedHook  - void FRTOS1_vApplicationMallocFailedHook(void);
**
**Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**
**http      : www.freescale.com
**mail      : support@freescale.com
** ###################################################################*/
/*!
** @file Events.h
** @version 01.04
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
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"

#pragma CODE_SEG DEFAULT

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


/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.03 [04.46]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
