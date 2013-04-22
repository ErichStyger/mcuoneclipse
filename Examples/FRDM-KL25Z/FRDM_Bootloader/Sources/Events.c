/* ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-04-01, 15:34, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @date 2013-04-01, 15:34, # CodeGen: 0
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Bootloader.h"
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
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  IFsh1_OnWriteEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after a write operation to FLASH memory is
**         finished (except <SetPage>). This event is available only if
**         an <Interrupt service/event> is selected.
*/
/* ===================================================================*/
void IFsh1_OnWriteEnd(void)
{
  /* Write your code here ... */
}


/*
** ===================================================================
**     Event       :  S19_OnError (module Events)
**
**     Component   :  S19 [S19]
**     Description :
**         Event called in case of an error
**     Parameters  :
**         NAME            - DESCRIPTION
**         errorCode       - 
**         iteratorInfo    - 
**     Returns     : Nothing
** ===================================================================
*/
void S19_OnError(S19_ErrorCode errorCode, S19_ParserStruct *iteratorInfo)
{
  /* Write your code here ... */
}

/* END Events */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0.12 [05.05]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
