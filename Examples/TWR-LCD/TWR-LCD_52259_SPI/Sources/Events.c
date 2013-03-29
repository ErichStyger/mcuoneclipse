/** ###################################################################
**     Filename    : Events.c
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
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "lcd.h"

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
void Cpu_OnCoreWatchdogINT0(void)
{
  /* Write your code here ... */
}

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
void Sensor1_OnADGet(void)
{
  /* Write your code here ... */
}

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
void Sensor1_OnADGive(void)
{
  /* Write your code here ... */
}

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
void TCHS1_OnEvent(TCHS1_TouchScreenEvent event, TCHS1_PixelDim x, TCHS1_PixelDim y)
{
  OnTouch(event, x, y);
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale MCF series of microcontrollers.
**
** ###################################################################
*/
