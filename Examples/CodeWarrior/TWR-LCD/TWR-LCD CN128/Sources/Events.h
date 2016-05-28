/** ###################################################################
**     Filename  : Events.h
**     Project   : ProcessorExpert
**     Processor : MCF51CN128CLK
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2011-03-17, 12:29, # CodeGen: 0
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
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "UTIL1.h"
#include "WAIT1.h"
#include "I2C1.h"
#include "LED2.h"
#include "LEDpin1.h"
#include "LED3.h"
#include "LEDpin2.h"
#include "LED4.h"
#include "LEDpin3.h"
#include "BuzzerPPG.h"
#include "LCD1.h"
#include "RESpin1.h"
#include "ALE1.h"
#include "KEY1.h"
#include "keyPin1.h"
#include "MultiKey1.h"
#include "TRG1.h"
#include "EVNT1.h"
#include "AD1.h"
#include "ACCEL1.h"
#include "TCHS1.h"
#include "Sensor1.h"
#include "Xminus1.h"
#include "Yminus1.h"
#include "Xplus1.h"
#include "Yplus1.h"
#include "GDisp1.h"
#include "Helv08n.h"
#include "Helv12n.h"
#include "Helv14n.h"
#include "Helv18n.h"
#include "Helv24n.h"
#include "Cour08n.h"
#include "Cour10n.h"
#include "Helv10n.h"
#include "Cour08b.h"
#include "FDisp1.h"
#include "UI1.h"
#include "TmDt1.h"
#include "UICalendar1.h"
#include "IFsh1.h"
#include "UIG1.h"
#include "CS1.h"
#include "KSDK1.h"


void UICalendar1_OnCalendarGetAppointments(UICalendar1_CalendarDateTime *startHint, UICalendar1_CalendarAppointment **appointmentList);
/*
** ===================================================================
**     Event       :  UICalendar1_OnCalendarGetAppointments (module Events)
**
**     Component   :  UICalendar1 [UICalendar]
**     Description :
**         Event called in order to get a list of appointment. Note
**         that the list needs to remain in memory until the next call.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * startHint       - Pointer to the start date/time
**                           the event is interested in. As the event is
**                           requesting only appointments for a certain
**                           day, you may limit the amount of data
**                           passed.
**       * appointmentList - Pointer to linked
**                           list of appointments. The callee has to
**                           return here the pointer to the first
**                           element of the list.
**     Returns     : Nothing
** ===================================================================
*/

void ACCEL1_OnADGet(void);
/*
** ===================================================================
**     Event       :  ACCEL1_OnADGet (module Events)
**
**     Component   :  ACCEL1 [MMA7260Q]
**     Description :
**         Called to get mutual access to the A/D converter
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void ACCEL1_OnADGive(void);
/*
** ===================================================================
**     Event       :  ACCEL1_OnADGive (module Events)
**
**     Component   :  ACCEL1 [MMA7260Q]
**     Description :
**         Called to give back mutual access to the A/D converter
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

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

void KEY1_OnKeyPressed(byte keys);
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

void KEY1_OnKeyReleased(byte keys);
/*
** ===================================================================
**     Event       :  KEY1_OnKeyReleased (module Events)
**
**     Component   :  KEY1 [Key]
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/

void KEY1_OnKeyReleasedLong(byte keys);
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

void I2C1_OnReceiveData(void);
/*
** ===================================================================
**     Event       :  I2C1_OnReceiveData (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the reception of the
**         data successfully. This event is not available for the SLAVE
**         mode and if both RecvChar and RecvBlock are disabled. This
**         event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void I2C1_OnTransmitData(void);
/*
** ===================================================================
**     Event       :  I2C1_OnTransmitData (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         This event is invoked when I2C finishes the transmission of
**         the data successfully. This event is not available for the
**         SLAVE mode and if both SendChar and SendBlock are disabled.
**         This event is enabled only if interrupts/events are enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void I2C1_OnRxChar(void);
/*
** ===================================================================
**     Event       :  I2C1_OnRxChar (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         Called when a correct character is received. This event is
**         not available for the MASTER mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void I2C1_OnTxChar(void);
/*
** ===================================================================
**     Event       :  I2C1_OnTxChar (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         Called when a correct character is sent (placed to the
**         transmitter). This event is not available for the MASTER
**         mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationStackOverflowHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         if enabled, this hook will be called in case of a stack
**         overflow.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * pxTask          - Pointer to task handle
**       * pcTaskName      - Pointer to 
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationTickHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationTickHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called by the RTOS for every
**         tick increment.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationIdleHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationIdleHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, this hook will be called when the RTOS is idle.
**         This might be a good place to go into low power mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FRTOS1_vApplicationMallocFailedHook(void);
/*
** ===================================================================
**     Event       :  FRTOS1_vApplicationMallocFailedHook (module Events)
**
**     Component   :  FRTOS1 [FreeRTOS]
**     Description :
**         If enabled, the RTOS will call this hook in case memory
**         allocation failed.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void UI1_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind event);
/*
** ===================================================================
**     Event       :  UI1_OnEvent (module Events)
**
**     Component   :  UI1 [UserInterface]
**     Description :
**         Event called for various element events
**     Parameters  :
**         NAME            - DESCRIPTION
**       * screen          - Pointer to screen
**       * window          - Pointer to window
**       * element         - Pointer to element
**         event           - kind of event
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
