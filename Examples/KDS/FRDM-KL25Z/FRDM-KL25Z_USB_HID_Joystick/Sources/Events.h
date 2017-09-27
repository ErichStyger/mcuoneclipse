/* ###################################################################
**     Filename    : Events.h
**     Project     : FRDM-KL25Z_USB_CDC
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-13, 17:24, # CodeGen: 0
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
#include "USB1.h"
#include "HIDJ1.h"
#include "USB0.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "WAIT1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDB.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "UTIL1.h"
#include "CS1.h"
#include "MCUC1.h"
#include "SW1.h"
#include "ExtIntLdd1.h"
#include "SW2.h"
#include "ExtIntLdd2.h"
#include "SW3.h"
#include "ExtIntLdd3.h"
#include "SW4.h"
#include "ExtIntLdd4.h"
#include "SW5.h"
#include "BitIoLdd9.h"
#include "SW6.h"
#include "BitIoLdd10.h"
#include "SW7.h"
#include "ExtIntLdd5.h"

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


void HIDJ1_OnEvent(uint8_t error);
/*
** ===================================================================
**     Event       :  HIDJ1_OnEvent (module Events)
**
**     Component   :  HIDJ1 [FSL_USB_HID_Joystick_Device]
**     Description :
**         Hook called in case of an error
**     Parameters  :
**         NAME            - DESCRIPTION
**         error           - Error or event code
**     Returns     : Nothing
** ===================================================================
*/

void SW7_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  SW7_OnInterrupt (module Events)
**
**     Component   :  SW7 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SW4_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  SW4_OnInterrupt (module Events)
**
**     Component   :  SW4 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SW3_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  SW3_OnInterrupt (module Events)
**
**     Component   :  SW3 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SW2_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  SW2_OnInterrupt (module Events)
**
**     Component   :  SW2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
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
