/** ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-02-02, 19:20, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Logic.h"

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
**     Event       :  DMAT1_OnComplete (module Events)
**
**     Component   :  DMAT1 [DMATransfer_LDD]
**     Description :
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is anabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**         This event is enabled only if Interrupts property in Channel
**         select section is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     Returns     : Nothing
** ===================================================================
*/
void DMA1_OnComplete(void)
{
  LOGIC_dmat1OnCompleted();
}

/*
** ===================================================================
**     Event       :  DMAT1_OnError (module Events)
**
**     Component   :  DMAT1 [DMATransfer_LDD]
**     Description :
**         Called when error in channel settings is detected. See
**         SetEventMask() and GetEventMask() methods. This event is
**         enabled only if Interrupts property in Channel select
**         section is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     Returns     : Nothing
** ===================================================================
*/
void DMA1_OnError(void)
{
	LOGIC_dmat1OnError();
}

/*
** ===================================================================
**     Event       :  DMACH1_OnComplete (module Events)
**
**     Component   :  DMACH1 [DMAChannel_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is enabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DMACH1_OnComplete(LDD_TUserData *UserDataPtr)
{
  (void)UserDataPtr;
  LOGIC_OnComplete();
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
