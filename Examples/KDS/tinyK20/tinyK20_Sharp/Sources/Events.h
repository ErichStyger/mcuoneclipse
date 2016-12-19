/* ###################################################################
**     Filename    : Events.h
**     Project     : tinyK20_Sharp
**     Processor   : MK20DX128VFT5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-12-13, 11:22, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
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
#include "SPI1.h"
#include "Clock1.h"
#include "BitIoLdd4.h"
#include "Output1.h"
#include "BitIoLdd5.h"
#include "GDisp1.h"
#include "SHM1.h"
#include "SCEpin3.h"
#include "BitIoLdd8.h"
#include "Helv8.h"
#include "Helv8Bold.h"
#include "Helv10.h"
#include "Helv12.h"
#include "Cour8.h"
#include "Cour8Bold.h"
#include "Cour10.h"
#include "Cour12.h"
#include "FDisp1.h"
#include "WAIT1.h"
#include "LED1.h"
#include "LEDpin2.h"
#include "BitIoLdd7.h"
#include "MCUC1.h"
#include "UTIL1.h"

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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
