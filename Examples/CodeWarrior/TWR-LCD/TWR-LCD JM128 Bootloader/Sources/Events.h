/** ###################################################################
**     Filename  : Events.h
**     Project   : ProcessorExpert
**     Processor : MCF51JM128VLH
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2011-03-12, 10:15, # CodeGen: 0
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
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
#include "PE_Timer.h"
#include "PS2.h"
#include "WAIT1.h"
#include "FDisp1.h"
#include "GDisp1.h"
#include "Helv08n.h"
#include "LCD1.h"
#include "RESpin1.h"
#include "D_Cpin1.h"
#include "SCEpin1.h"
#include "UTIL1.h"
#include "EuSD.h"
#include "JM_ELE.h"
#include "TP_SEL.h"
#include "BuzzerPPG.h"
#include "IFsh1.h"
#include "SM1.h"
#include "S191.h"
#include "BLD1.h"
#include "BLUSB1.h"
#include "MCUC1.h"


void S191_OnSRecord(uint8_t *returnCode, uint8_t type, uint32_t addr, uint8_t *dataBuf, uint8_t dataBufSize, void *data);
/*
** ===================================================================
**     Event       :  S191_OnSRecord (module Events)
**
**     Component   :  S191 [S19]
**     Description :
**         Event called for every S-Record
**     Parameters  :
**         NAME            - DESCRIPTION
**         type            - type of S-Record (as character), e.g. '3'
**       * dataBuf         - Pointer to buffer of S-Record data
**                           (in binary form)
**         dataBufLenght   - Size in bytes of the
**                           data buffer
**     Returns     : Nothing
** ===================================================================
*/

void S191_OnError(S191_ErrorCode errorCode, S191_ParserStruct *iteratorInfo);
/*
** ===================================================================
**     Event       :  S191_OnError (module Events)
**
**     Component   :  S191 [S19]
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

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 [04.48]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
