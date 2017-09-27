/* ###################################################################
**     Filename    : Events.h
**     Project     : Btl_K20
**     Processor   : MK20DX128VLH5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-06-25, 17:08, # CodeGen: 0
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
#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "S19.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "BL_SW.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd2.h"
#include "HF1.h"
#include "CS1.h"
#include "MCUC1.h"
#include "XF1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX128EX5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


void S19_OnSRecord(uint8_t *returnCode, uint8_t type, uint32_t addr, uint8_t *dataBuf, uint8_t dataBufSize, void *data);
/*
** ===================================================================
**     Event       :  S19_OnSRecord (module Events)
**
**     Component   :  S19 [S19]
**     Description :
**         Event called for every S-Record
**     Parameters  :
**         NAME            - DESCRIPTION
**       * returnCode      - Pointer to error code
**         type            - type of S-Record (as character), e.g. '3'
**         addr            - Address of data
**       * dataBuf         - Pointer to buffer of S-Record data
**                           (in binary form)
**         dataBufSize     - Size in bytes of the data
**                           buffer
**       * data            - Pointer to private data
**     Returns     : Nothing
** ===================================================================
*/

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
**       * iteratorInfo    - Pointer to parser info
**                           struct
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  IFsh1_OnWriteEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after a write operation to FLASH memory is
**         finished (except [SetPage]). This event is available only if
**         an [Interrupt service/event] is selected.
*/
/* ===================================================================*/
void IFsh1_OnWriteEnd(void);

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
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
