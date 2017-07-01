/** ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MC9S08JM16CGT
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2012-03-14, 18:20, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
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
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "USB1.h"
#include "USBInit1.h"
#include "CS1.h"
#include "MCUC1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "XF1.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "WAIT1.h"


void HIDK1_OnEvent(byte error);
/*
** ===================================================================
**     Event       :  HIDK1_OnEvent (module Events)
**
**     Component   :  HIDK1 [FSL_USB_HID_Keyboard_Device]
**     Description :
**         Hook called in case of an error
**     Parameters  :
**         NAME            - DESCRIPTION
**         error           - Error or event code
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
