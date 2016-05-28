/** ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MCF52259CAG80
**     Component   : Events
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2012-10-31, 12:12, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnCoreWatchdogINT - void Cpu_OnCoreWatchdogINT(void);
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
#include "BuzzerPPG.h"
#include "LCD1.h"
#include "ALE2.h"
#include "WAIT1.h"
#include "GDisp1.h"
#include "FDisp1.h"
#include "Helv08n.h"
#include "TCHS1.h"
#include "Sensor1.h"
#include "Xminus1.h"
#include "Yminus1.h"
#include "Xplus1.h"
#include "Yplus1.h"
#include "UTIL1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "AD1.h"
#include "KSDK1.h"

void Cpu_OnCoreWatchdogINT0(void);
/*
** ===================================================================
**     Event       :  Cpu_OnCoreWatchdogINT0 (module Events)
**
**     Component   :  Cpu [MCF52259_144_LQFP]
**     Description :
**         This event is called when the OnCoreWatchdog interrupt had
**         occurred. This event is automatically enabled when the <Mode>
**         is set to 'Interrupt'.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Sensor1_OnADGet(void);
/*
** ===================================================================
**     Event       :  Sensor1_OnADGet (module Events)
**
**     Component   :  Sensor1 [TouchScreenSensor]
**     Description :
**         Event called to get mutual exclusive access to the A/D port
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Sensor1_OnADGive(void);
/*
** ===================================================================
**     Event       :  Sensor1_OnADGive (module Events)
**
**     Component   :  Sensor1 [TouchScreenSensor]
**     Description :
**         Event called to return the mutual exclusive access to the
**         A/D port
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TCHS1_OnEvent(TCHS1_TouchScreenEvent event, TCHS1_PixelDim x, TCHS1_PixelDim y);
/*
** ===================================================================
**     Event       :  TCHS1_OnEvent (module Events)
**
**     Component   :  TCHS1 [TouchScreen]
**     Description :
**         Event called touch screen events, like touched, untouched
**         etc.
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - 
**         x               - x coordinate
**         y               - y coordinate
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale MCF series of microcontrollers.
**
** ###################################################################
*/
