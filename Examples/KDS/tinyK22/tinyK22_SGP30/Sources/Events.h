/* ###################################################################
**     Filename    : Events.h
**     Project     : tinyK22_SGP30
**     Processor   : MK22FN512VLH12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-09-30, 18:31, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
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
#include "Pins1.h"
#include "WAIT1.h"
#include "MCUC1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "FRTOS1.h"
#include "RTOSCNTRLDD1.h"
#include "UTIL1.h"
#include "RTT1.h"
#include "CLS1.h"
#include "CS1.h"
#include "KIN1.h"
#include "XF1.h"
#include "AS1.h"
#include "ASerialLdd2.h"
#include "USB1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "TMOUT1.h"
#include "TSL1.h"
#include "GI2C1.h"
#include "CI2C2.h"
#include "RTC1.h"
#include "TmDt1.h"
#include "MMA1.h"
#include "LCD1.h"
#include "SCEpin1.h"
#include "BitIoLdd2.h"
#include "RESpin1.h"
#include "BitIoLdd3.h"
#include "D_Cpin1.h"
#include "BitIoLdd4.h"
#include "SM1.h"
#include "RNG1.h"
#include "TRG1.h"
#include "GDisp1.h"
#include "KEY1.h"
#include "Inhr1.h"
#include "BitIoLdd8.h"
#include "HF1.h"
#include "DMA1.h"
#include "DMACH1.h"
#include "DMACH2.h"
#include "DMACH3.h"
#include "LEDM1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "MINI1.h"
#include "SYS1.h"

#ifdef __cplusplus
extern "C" {
#endif 

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
void Cpu_OnNMI(void);


void FRTOS1_vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
/*
** ===================================================================
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
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

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
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr);

void KEY1_OnKeyPressed(uint8_t keys);
/*
** ===================================================================
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY1_OnKeyReleased(uint8_t keys);
/*
** ===================================================================
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY1_OnKeyPressedLong(uint8_t keys);
/*
** ===================================================================
**     Description :
**         Event generated at the time a long key press has been
**         detected.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY1_OnKeyReleasedLong(uint8_t keys);
/*
** ===================================================================
**     Description :
**         Event generated after a key has been released (long key
**         press).
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void SD1_OnActivate(uint8_t mode);
/*
** ===================================================================
**     Description :
**         Event called when Activate() method is called. This gives an
**         opportunity to the application to synchronize access to a
**         shared bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**         mode            - 0: slow mode, 1: fast mode
**     Returns     : Nothing
** ===================================================================
*/

void SD1_OnDeactivate(uint8_t mode);
/*
** ===================================================================
**     Description :
**         Event called when Deactivate() method is called. This gives
**         an opportunity to the application to synchronize access to a
**         shared bus.
**     Parameters  :
**         NAME            - DESCRIPTION
**         mode            - 0: slow mode, 1: fast mode
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_OnGetLCD(void);
/*
** ===================================================================
**     Description :
**         Event called in the event of GetLCD() method called.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_OnGiveLCD(void);
/*
** ===================================================================
**     Description :
**         Event called in the event of GiveLCD() method called.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_OnGetDisplay(void);
/*
** ===================================================================
**     Description :
**         Event called from GetDisplay() method. This callback is
**         useful if you want to share the communication to the display
**         (e.g. SPI) with other peripherals, as this gives you a
**         chance to protect the access to it.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GDisp1_OnGiveDisplay(void);
/*
** ===================================================================
**     Description :
**         Event called from GetDisplay() method. This callback is
**         useful if you want to share the communication to the display
**         (e.g. SPI) with other peripherals, as this gives you a
**         chance to protect the access to it.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_OnGetBus(void);
/*
** ===================================================================
**     Description :
**         Called for SPI bus sharing
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_OnGiveBus(void);
/*
** ===================================================================
**     Description :
**         Used for SPI bus sharing
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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
