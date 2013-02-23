/** ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2012-10-07, 12:33, # CodeGen: 0
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
#include "WAIT1.h"
#include "LEDR.h"
#include "LEDpin4.h"
#include "BitIoLdd4.h"
#include "LEDG.h"
#include "LEDpin5.h"
#include "BitIoLdd5.h"
#include "LEDB.h"
#include "LEDpin6.h"
#include "BitIoLdd6.h"
#include "USB1.h"
#include "USBInit2.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
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


void USB1_OnError(byte error);
/*
** ===================================================================
**     Event       :  USB1_OnError (module Events)
**
**     Component   :  USB1 [FSL_USB_Stack]
**     Description :
**         Hook called in case of an error
**     Parameters  :
**         NAME            - DESCRIPTION
**         error           - Error code
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
