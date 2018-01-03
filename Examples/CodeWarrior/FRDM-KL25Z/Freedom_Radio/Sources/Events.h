/** ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-01-08, 20:25, # CodeGen: 0
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
#include "SMAC1.h"
#include "PHY1.h"
#include "TRSVR1.h"
#include "CE2.h"
#include "BitIoLdd5.h"
#include "RESET2.h"
#include "BitIoLdd6.h"
#include "RTXEN2.h"
#include "BitIoLdd7.h"
#include "ATTN2.h"
#include "BitIoLdd8.h"
#include "IRQ2.h"
#include "ExtIntLdd2.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "UTIL1.h"
#include "MCUC1.h"
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


void SMAC1_ResetIndication(void);
/*
** ===================================================================
**     Event       :  SMAC1_ResetIndication (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event in case of transceiver reset.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void PHY1_DataIndicationPacket(tRxPacket *sRxPacket);
/*
** ===================================================================
**     Event       :  PHY1_DataIndicationPacket (module Events)
**
**     Component   :  PHY1 [SPHY]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         sRxPacket       - 
**     Returns     : Nothing
** ===================================================================
*/

void SMAC1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  SMAC1_OnInterrupt (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event raised in case of transceiver interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TRSVR1_DataIndication(void);
/*
** ===================================================================
**     Event       :  TRSVR1_DataIndication (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event in case a data packet has been received.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TRSVR1_ResetIndication(void);
/*
** ===================================================================
**     Event       :  TRSVR1_ResetIndication (module Events)
**
**     Component   :  TRSVR1 [MC13192]
**     Description :
**         Event in case of transceiver reset.
**     Parameters  : None
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
