/** ###################################################################
**     Filename    : Events.c
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
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

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
void HIDK1_OnEvent(byte error)
{
  (void)error;
  /* Write your code here ... */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
