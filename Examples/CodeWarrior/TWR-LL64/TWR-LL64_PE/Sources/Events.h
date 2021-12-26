/** ###################################################################
**     Filename  : Events.H
**     Project   : ProcessorExpert
**     Processor : MC9S08LL64CLK
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 03.05.2010, 20:10
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         EVNT1_AppHandleEvent   - void EVNT1_AppHandleEvent(byte event);
**         KEY2_OnKeyPressed      - void KEY2_OnKeyPressed(byte keys);
**         KEY2_OnKeyReleasedLong - void KEY2_OnKeyReleasedLong(byte keys);
**         TI1_OnInterrupt        - void TI1_OnInterrupt(void);
**         KEY1_OnKeyPressed      - void KEY1_OnKeyPressed(byte keys);
**         KEY1_OnKeyReleasedLong - void KEY1_OnKeyReleasedLong(byte keys);
**
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "LED3.h"
#include "LEDpin3.h"
#include "LED4.h"
#include "LEDpin4.h"
#include "WAIT1.h"
#include "KEY1.h"
#include "keyPin1.h"
#include "MultiKey1.h"
#include "TRG1.h"
#include "TI1.h"
#include "KEY2.h"
#include "keyPin2.h"
#include "KeyISRpin2.h"
#include "EVNT1.h"
#include "UTIL1.h"
#include "LCD1.h"
#include "TOD1.h"
#include "TmDt1.h"
#include "AD1.h"
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "CS1.h"
#include "MCUC1.h"

void EVNT1_AppHandleEvent(uint8_t event);
/*
** ===================================================================
**     Event       :  EVNT1_AppHandleEvent (module Events)
**
**     Component   :  EVNT1 [SimpleEvents]
**     Description :
**         
**     Parameters  :
**         NAME            - DESCRIPTION
**         event           - Event (event number) to be processed.
**     Returns     : Nothing
** ===================================================================
*/

void KEY2_OnKeyPressed(uint8_t keys);
/*
** ===================================================================
**     Event       :  KEY2_OnKeyPressed (module Events)
**
**     Component   :  KEY2 [Key]
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY2_OnKeyReleasedLong(uint8_t keys);
/*
** ===================================================================
**     Event       :  KEY2_OnKeyReleasedLong (module Events)
**
**     Component   :  KEY2 [Key]
**     Description :
**         Event generated after a key has been released (long key
**         press).
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void TI1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void KEY1_OnKeyPressed(uint8_t keys);
/*
** ===================================================================
**     Event       :  KEY1_OnKeyPressed (module Events)
**
**     Component   :  KEY1 [Key]
**     Description :
**         Event generated at the time a key has been pressed.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY1_OnKeyReleasedLong(uint8_t keys);
/*
** ===================================================================
**     Event       :  KEY1_OnKeyReleasedLong (module Events)
**
**     Component   :  KEY1 [Key]
**     Description :
**         Event generated after a key has been released (long key
**         press).
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/


void FRTOS1_vOnPreSleepProcessing(TickType_t expectedIdleTicks);
/*
** ===================================================================
**     Description :
**         Used in tickless idle mode only, but required in this mode.
**         Hook for the application to enter low power mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         expectedIdleTicks - expected idle
**                           time, in ticks
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vOnPostSleepProcessing(TickType_t expectedIdleTicks);
/*
** ===================================================================
**     Description :
**         Event called after the CPU woke up after low power mode.
**         This event is optional.
**     Parameters  :
**         NAME            - DESCRIPTION
**         expectedIdleTicks - expected idle
**                           time, in ticks
**     Returns     : Nothing
** ===================================================================
*/

void KEY2_OnKeyPressedLong(uint8_t keys);
/*
** ===================================================================
**     Description :
**         Event generated at the time a long key press has been
**         detected.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY1_OnKeyPressedLong(uint8_t keys);
/*
** ===================================================================
**     Description :
**         Event generated at the time a long key press has been
**         detected.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by Processor Expert 4.00 Beta [04.40]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
