/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
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

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "S19.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "AS1.h"
#include "ASerialLdd2.h"
#include "WAIT1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd2.h"
#include "HF1.h"
#include "CS1.h"
#include "BL_SW.h"
#include "BitIoLdd3.h"

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
void Cpu_OnNMIINT(void);


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
void IFsh1_OnWriteEnd(void);

void S19_OnError(S19_ErrorCode errorCode, S19_ParserStruct *iteratorInfo);
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

/* END Events */
#endif /* __Events_H*/

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
