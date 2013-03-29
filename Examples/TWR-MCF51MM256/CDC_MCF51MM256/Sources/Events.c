/** ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MCF51MM256VLL
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2012-05-21, 17:04, # CodeGen: 0
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
void USB1_OnError(byte error)
{
  void APP_Error(byte error);

  APP_Error(error);
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
