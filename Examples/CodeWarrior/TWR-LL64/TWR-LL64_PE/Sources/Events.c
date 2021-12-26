/** ###################################################################
**     Filename  : Events.C
**     Project   : ProcessorExpert
**     Processor : MC9S08LL64CLK
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 03.05.2010, 16:28
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"
#include "EVNT1.h"
#include "TRG1.h"
#include "Application.h"

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
void KEY2_OnKeyPressed(uint8_t keys)
{
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_SW4_PRESSED);
  }
}

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
void TI1_OnInterrupt(void)
{
  TRG1_AddTick();
}

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
void KEY1_OnKeyPressed(uint8_t keys)
{
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_SW3_PRESSED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_SW2_PRESSED);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_SW1_PRESSED);
  }
}

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
void EVNT1_AppHandleEvent(uint8_t event)
{
  APP_HandleEvent(event);
}

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
void KEY2_OnKeyReleasedLong(uint8_t keys)
{
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_SW4_LONG_PRESSED);
  }
}

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
void KEY1_OnKeyReleasedLong(uint8_t keys)
{
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_SW1_LONG_PRESSED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_SW2_LONG_PRESSED);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_SW3_LONG_PRESSED);
  }
}

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
void FRTOS1_vOnPreSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used */
#if 0
  /* example for Kinetis (enable SetOperationMode() in CPU component): */
  /* Cpu_SetOperationMode(DOM_WAIT, NULL, NULL); */ /* Processor Expert way to get into WAIT mode */
  /* or to wait for interrupt: */
    __asm volatile("dsb");
    __asm volatile("wfi");
    __asm volatile("isb");
#elif 1
  /* example for S08/S12/ColdFire V1 (enable SetWaitMode() in CPU): */
  Cpu_SetWaitMode();
#elif 0
  /* example for ColdFire V2: */
   __asm("stop #0x2000"); */
#else
  #error "you *must* enter low power mode (wait for interrupt) here!"
#endif
  /* Write your code here ... */
}

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
void FRTOS1_vOnPostSleepProcessing(TickType_t expectedIdleTicks)
{
  (void)expectedIdleTicks; /* not used (yet?) */
  /* Write your code here ... */
}

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
void KEY2_OnKeyPressedLong(uint8_t keys)
{
  /* Write your code here ... */
}

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
void KEY1_OnKeyPressedLong(uint8_t keys)
{
  /* Write your code here ... */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 4.00 Beta [04.40]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
