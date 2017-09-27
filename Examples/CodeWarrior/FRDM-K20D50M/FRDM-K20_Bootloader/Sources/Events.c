/* ###################################################################
**     Filename    : Events.c
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
** @file Events.c
** @version 01.00
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

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

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
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

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
void S19_OnSRecord(uint8_t *returnCode, uint8_t type, uint32_t addr, uint8_t *dataBuf, uint8_t dataBufSize, void *data)
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
**       * iteratorInfo    - Pointer to parser info
**                           struct
**     Returns     : Nothing
** ===================================================================
*/
void S19_OnError(S19_ErrorCode errorCode, S19_ParserStruct *iteratorInfo)
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
**         finished (except [SetPage]). This event is available only if
**         an [Interrupt service/event] is selected.
*/
/* ===================================================================*/
void IFsh1_OnWriteEnd(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
