/** ###################################################################
**     Filename  : Calendar.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 29.01.2010, 15:48
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __Calendar_H
#define __Calendar_H

/* MODULE Calendar */

#include "UI1.h"
#include "UICalendar1.h"

typedef struct {
  UI1_Screen screen;
  UI1_Window window;
  UI1_Header header;
  UI1_Icon iconClose;
  UICalendar1_CalendarDay calendarDay;
  struct {
    UI1_Window window;
    UI1_Header header;
    UI1_Icon iconClose;
    UI1_Text dateTime;
    UI1_Text text;
    UI1_Button btn;
    unsigned char dateTimeBuf[sizeof("02.15.2006 10:15-14:25")];
  } dialog;
} CAL_WindowDesc;


void CAL_OnCalendarGetAppointments(UICalendar1_CalendarDateTime *startHint, UICalendar1_CalendarAppointment **appointmentList);

void CAL_StartTask(CAL_WindowDesc *desc);



/* END Calendar */

#endif

