/** ###################################################################
**     Filename  : Events.c
**     Project   : ProcessorExpert
**     Processor : MCF52259CAG80
**     Component : Events
**     Compiler  : CodeWarrior MCF C Compiler
**     Date/Time : 2010-11-02, 12:47, # CodeGen: 0
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         Cpu_OnCoreWatchdogINT - void Cpu_OnCoreWatchdogINT(void);
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Platform.h"
#include "RTOS.h"
#include "App.h"
#if PL_HAS_CALENDAR_DEMO
  #include "Calendar.h"
#endif
#if PL_HAS_TETRIS_DEMO
  #include "Tetris.h"
#endif
#if PL_HAS_I2C_COMM
  #include "I2C.h"
#endif
#if PL_HAS_BOOTLOADER || PL_IS_BOOTLOADER
  #include "Bootloader.h"
#endif
#include "AnalogDigital.h"
#if PL_HAS_SD_DEMO
  #include "TMOUT1.h"
  #include "SDCard.h"
#endif

/*
** ===================================================================
**     Event       :  Cpu_OnCoreWatchdogINT (module Events)
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
void Cpu_OnCoreWatchdogINT(void)
{
  /* Write your code here ... */
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
  RTOS_HandleEvent(event);
}

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
void FRTOS1_vApplicationStackOverflowHook(xTaskHandle pxTask, char *pcTaskName)
{
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
  /* Write your code here ... */
  (void)pxTask; (void)pcTaskName;
  for(;;) {}
}

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
void FRTOS1_vApplicationTickHook(void)
{
#if PL_HAS_SD_DEMO
  TMOUT1_AddTick();
#endif
#if PL_USE_RTOS
  TRG1_AddTick();
#endif
#if PL_HAS_TETRIS_DEMO
  TETRIS_AddTime(10); /* additional 10ms */
#endif  
}

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
void FRTOS1_vApplicationIdleHook(void)
{
  //Cpu_SetWaitMode();
}

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
void FRTOS1_vApplicationMallocFailedHook(void)
{
  /* Write your code here ... */
  for(;;) {}
}

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
#if PL_HAS_CALENDAR_DEMO
void UICalendar1_OnCalendarGetAppointments(UICalendar1_CalendarDateTime *startHint, UICalendar1_CalendarAppointment **appointmentList)
{
  CAL_OnCalendarGetAppointments(startHint, appointmentList);
}
#endif

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
#if PL_HAS_HW_ACCELEROMETER
void ACCEL1_OnADGet(void)
{
  AD_GetDevice();
}
#endif

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
#if PL_HAS_HW_ACCELEROMETER
void ACCEL1_OnADGive(void)
{
  AD_GiveDevice();
}
#endif

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
void KEY2_OnKeyPressed(byte keys)
{
#if PL_BOARD_TWR_CN128 && PL_TWR_LCD_REV_0
  /* navigation switch on the TWR-LCD1: some we get from here */
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_PRESSED);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON5_PRESSED);
  } else if (keys&4) {
    EVNT1_SetEvent(EVNT1_BUTTON3_PRESSED);
  }
#elif PL_HAS_HW_NAV_SWITCH /* we get events from the navigation switch */
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_PRESSED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_PRESSED);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_BUTTON3_PRESSED);
  } else if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_BUTTON4_PRESSED);
  } else if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_BUTTON5_PRESSED);
  }
#elif PL_BOARD_TWR_CN128 || PL_BOARD_TWR_52259 /* we get events from the two TWR-CN128 onboard switches */ 
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_PRESSED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_PRESSED);
  }
#else
  (void)keys; /* ignore compiler warning */
#endif}
}

/*
** ===================================================================
**     Event       :  KEY2_OnKeyReleased (module Events)
**
**     Component   :  KEY2 [Key]
**     Description :
**         Event generated after a key has been released.
**     Parameters  :
**         NAME            - DESCRIPTION
**         keys            - the key(s) pressed, as bitset (e.g. 1 is
**                           key 1, 2 is key 2, 4 is key 3, ....)
**     Returns     : Nothing
** ===================================================================
*/
void KEY2_OnKeyReleased(byte keys)
{
#if PL_BOARD_TWR_CN128 && PL_TWR_LCD_REV_0
  /* navigation switch on the TWR-LCD1: some we get from here */
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED);
  } else if (keys&4) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED);
  }
#elif PL_HAS_HW_NAV_SWITCH /* we get events from the navigation switch */
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED);
  } else if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_BUTTON4_RELEASED);
  } else if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED);
  }
#elif PL_BOARD_TWR_CN128 || PL_BOARD_TWR_52259 /* we get events from the two onboard switches */ 
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED);
  }
#else
  (void)keys; /* ignore compiler warning */
#endif
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
void KEY2_OnKeyReleasedLong(byte keys)
{
#if PL_BOARD_TWR_CN128 && PL_TWR_LCD_REV_0
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED_LONG);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED_LONG);
  } else if (keys&4) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED_LONG);
  }
#elif PL_HAS_HW_NAV_SWITCH /* we get events from the navigation switch */
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED_LONG);
  } else if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED_LONG);
  } else if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_BUTTON3_RELEASED_LONG);
  } else if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_BUTTON4_RELEASED_LONG);
  } else if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_BUTTON5_RELEASED_LONG);
  }
#elif PL_BOARD_TWR_CN128 || PL_BOARD_TWR_52259 /* we get events from the two on-board switches */ 
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BUTTON1_RELEASED_LONG);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BUTTON2_RELEASED_LONG);
  }
#else
  (void)keys;
#endif
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
  AD_GetDevice();
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
  AD_GiveDevice();
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 5.00 Beta [04.46]
**     for the Freescale MCF series of microcontrollers.
**
** ###################################################################
*/
