/** ###################################################################
**     Filename  : Events.h
**     Project   : ProcessorExpert
**     Processor : MCF51JM128VLH
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2011-03-10, 20:45, # CodeGen: 0
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         KEY1_OnKeyPressed                     - void KEY1_OnKeyPressed(byte keys);
**         KEY1_OnKeyReleased                    - void KEY1_OnKeyReleased(byte keys);
**         KEY1_OnKeyReleasedLong                - void KEY1_OnKeyReleasedLong(byte keys);
**         SD1_OnIdle                            - void SD1_OnIdle(void);
**         SD1_OnError                           - void SD1_OnError(void);
**         FAT1_OnIdle                           - void FAT1_OnIdle(void);
**         FAT1_OnSchedule                       - void FAT1_OnSchedule(void);
**         UICalendar1_OnCalendarGetAppointments - void UICalendar1_OnCalendarGetAppointments(UICalendar1_CalendarDateTime...
**         EVNT1_AppHandleEvent                  - void EVNT1_AppHandleEvent(byte event);
**         UI1_OnEvent                           - void UI1_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element...
**         FRTOS1_vApplicationStackOverflowHook  - void FRTOS1_vApplicationStackOverflowHook(xTaskHandle *pxTask, signed...
**         FRTOS1_vApplicationTickHook           - void FRTOS1_vApplicationTickHook(void);
**         FRTOS1_vApplicationIdleHook           - void FRTOS1_vApplicationIdleHook(void);
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
#include "FRTOS1.h"
#include "RTOSSWI1.h"
#include "TickCntr1.h"
#include "FDisp1.h"
#include "GDisp1.h"
#include "Helv08n.h"
#include "LCD1.h"
#include "RESpin1.h"
#include "D_Cpin1.h"
#include "SCEpin1.h"
#include "UI1.h"
#include "UTIL1.h"
#include "AD1.h"
#include "Helv14n.h"
#include "Cour08n.h"
#include "Cour10n.h"
#include "Helv24n.h"
#include "Helv18n.h"
#include "Helv12n.h"
#include "Helv10n.h"
#include "Cour08b.h"
#include "EVNT1.h"
#include "TRG1.h"
#include "EuSD.h"
#include "JM_ELE.h"
#include "TP_SEL.h"
#include "BuzzerPPG.h"
#include "IFsh1.h"
#include "UICalendar1.h"
#include "TmDt1.h"
#include "I2C1.h"
#include "FAT1.h"
#include "SD1.h"
#include "SDSS2.h"
#include "CD2.h"
#include "SM1.h"
#include "SM2.h"
#include "KEY1.h"
#include "keyPin1.h"
#include "MultiKey1.h"
#include "TCHS1.h"
#include "Sensor2.h"
#include "Xminus2.h"
#include "Yminus2.h"
#include "Xplus2.h"
#include "Yplus2.h"
#include "TMOUT1.h"
#include "UIG1.h"
#include "CS1.h"

#include "Platform.h"

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

void SD1_OnError(void);
/*
** ===================================================================
**     Event       :  SD1_OnError (module Events)
**
**     Component   :  SD1 [SD_Card]
**     Description :
**         Event called in case of an low level error communicating
**         with the device
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#if PL_HAS_UI
void UICalendar1_OnCalendarGetAppointments(UICalendar1_CalendarDateTime *startHint, UICalendar1_CalendarAppointment **appointmentList);
#endif
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

void EVNT1_AppHandleEvent(byte event);
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
#if PL_HAS_UI
void UI1_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind event);
#endif
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


void Sensor2_OnADGet(void);
/*
** ===================================================================
**     Event       :  Sensor2_OnADGet (module Events)
**
**     Component   :  Sensor2 [TouchScreenSensor]
**     Description :
**         Event called to get mutual exclusive access to the A/D port
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Sensor2_OnADGive(void);
/*
** ===================================================================
**     Event       :  Sensor2_OnADGive (module Events)
**
**     Component   :  Sensor2 [TouchScreenSensor]
**     Description :
**         Event called to return the mutual exclusive access to the
**         A/D port
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

void SD1_OnIdle(void);
/*
** ===================================================================
**     Event       :  SD1_OnIdle (module Events)
**
**     Component   :  SD1 [SD_Card]
**     Description :
**         Event called in case we are waiting on the device. Useful to
**         make a task switch for an RTOS.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FAT1_OnIdle(void);
/*
** ===================================================================
**     Event       :  FAT1_OnIdle (module Events)
**
**     Component   :  FAT1 [FAT_FileSystem]
**     Description :
**         Event called while driver is waiting. Useful to call the OS
**         scheduler.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void FAT1_OnSchedule(void);
/*
** ===================================================================
**     Event       :  FAT1_OnSchedule (module Events)
**
**     Component   :  FAT1 [FAT_FileSystem]
**     Description :
**         Event called to give an RTOS scheduler a chance.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void I2C1_OnReadReq(void);
/*
** ===================================================================
**     Event       :  I2C1_OnReadReq (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         This event is invoked when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address equal to 1, ie., the
**         Master requests reading from slave (the slave will be
**         sending). After the return from the event call the first
**         data byte sending will start. This event is not available
**         for the MASTER mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void I2C1_OnWriteReq(void);
/*
** ===================================================================
**     Event       :  I2C1_OnWriteReq (module Events)
**
**     Component   :  I2C1 [InternalI2C]
**     Description :
**         This event is invoked when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address is set to 0, ie., the
**         Master requests writing to the slave (the slave will be
**         receiving). After the return from the event call the first
**         data byte receiving starts. This event is not available for
**         the MASTER mode.
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
