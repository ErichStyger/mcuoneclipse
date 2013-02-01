/** ###################################################################
**     Filename  : Calendar.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 29.01.2010, 15:48
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE Calendar */

#include "Platform.h"

#if PL_HAS_CALENDAR_DEMO
#include "Calendar.h"
#include "UTIL1.h"
#include "TmDt1.h"
#include "App.h"
#include "Helv12n.h"

#define FONT  Helv12n_GetFont()


static CAL_WindowDesc *calW;

static UICalendar1_CalendarAppointmentSelection CalSelection[6]; /* UI needs some RAM to store information */

/* example appointments */
static const UICalendar1_CalendarAppointment appointList[] = {
 /* 0 */ {1,5,2011,  8,  0,  60, (unsigned char*)"Call with customer", (UICalendar1_CalendarAppointment*)&appointList[1], &CalSelection[0]},
 /* 1 */ {1,5,2011,  9, 30,  30, (unsigned char*)"1x1 with my boss", (UICalendar1_CalendarAppointment*)&appointList[2], &CalSelection[1]},
 /* 2 */ {1,5,2011, 10, 15,  15, (unsigned char*)"Coffee break", (UICalendar1_CalendarAppointment*)&appointList[3], &CalSelection[2]},
 /* 3 */ {1,5,2011, 11,  0,  60, (unsigned char*)"Customer visit", (UICalendar1_CalendarAppointment*)&appointList[4], &CalSelection[3]},
 /* 4 */ {1,5,2011, 12, 30,  30, (unsigned char*)"Meet my friends", (UICalendar1_CalendarAppointment*)&appointList[5], &CalSelection[4]},
 /* 5 */ {1,5,2011, 14, 30, 120, (unsigned char*)"Fix INTRO bugs", NULL, &CalSelection[5] }
};

void CAL_OnCalendarGetAppointments(UICalendar1_CalendarDateTime *startHint, UICalendar1_CalendarAppointment **appointmentList) {
  (void)startHint;
  *appointmentList = (UICalendar1_CalendarAppointment*)&appointList[0];
}

static void CalW_AppointmentDialog_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &calW->dialog.iconClose)) {
      (void)UI1_CloseDialogWindow(&calW->screen, window);
    }
  }
}

static void CalW_CreateAppointmentDialog(UI1_Element *element) {
  UICalendar1_CalendarAppointmentSelection *selection = (UICalendar1_CalendarAppointmentSelection*)element;
  UI1_PixelDim h;
  UI1_PixelDim yPos;
  word minutes;
  
  if (selection->isFreeAppointment) { /* free appointment */
    UICalendar1_CalendarFreeApointmentSelection *freeSelection = (UICalendar1_CalendarFreeApointmentSelection*)element;
    word minutes;
    word hours;
    
    (void)UI1_CreateDialogWindow(&calW->screen, &calW->dialog.window, UI1_COLOR_BRIGHT_YELLOW, 50, 50, 190, 65);
    UI1_WindowSetBorder(&calW->dialog.window);
    UI1_SetWindowEventCallback(&calW->dialog.window, CalW_AppointmentDialog_WindowCallback);
    (void)UI1_CreateHeader(&calW->dialog.window, &calW->dialog.header, (unsigned char*)"Free Appointment", FONT, UI1_COLOR_BLUE);
    UI1_HeaderSetLine(&calW->dialog.header);
    UI1_ChangeTextFgColor(&calW->dialog.header.element, UI1_COLOR_WHITE);
    h = (UI1_PixelDim)(UI1_GetElementHeight(&calW->dialog.header));
    (void)UI1_CreateIcon(&calW->dialog.window, &calW->dialog.iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
    calW->dialog.iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
    UI1_OnWindowResize(&calW->dialog.window); /* right align element(s) if needed */
    UI1_ChangeElementColor(&calW->dialog.iconClose, UI1_COLOR_BLUE);
    UI1_ChangeIconFgColor(&calW->dialog.iconClose, UI1_COLOR_WHITE);
    UI1_EnableElementSelection(&calW->dialog.iconClose);
    yPos = (UI1_PixelDim)(UI1_GetElementHeight(&calW->dialog.header)+2);

    calW->dialog.dateTimeBuf[0] = '\0';
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), freeSelection->hour, '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)":");
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), freeSelection->minute, '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)"-");
    minutes = (word)(freeSelection->hour*60+freeSelection->minute+freeSelection->durationMinutes);
    hours = (word)(minutes/60);
    minutes -= hours*60;
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (int16_t)hours, '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)":");
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (int16_t)minutes, '0', 2); 
    (void)UI1_CreateText(&calW->dialog.window, &calW->dialog.dateTime, 2, yPos, 0, 0, calW->dialog.dateTimeBuf, FONT);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&calW->dialog.dateTime)+2);

    (void)UI1_CreateButton(&calW->dialog.window, &calW->dialog.btn, 5, yPos, 0, 0, (unsigned char*)"Book!", FONT, UI1_COLOR_WHITE);
    UI1_EnableElementSelection(&calW->dialog.btn);

    UI1_RefreshDialogWindow(&calW->dialog.window);
  } else { /* booked appointment */
    (void)UI1_CreateDialogWindow(&calW->screen, &calW->dialog.window, UI1_COLOR_BRIGHT_YELLOW, 50, 50, 190, 70);
    UI1_WindowSetBorder(&calW->dialog.window);
    UI1_SetWindowEventCallback(&calW->dialog.window, CalW_AppointmentDialog_WindowCallback);
    (void)UI1_CreateHeader(&calW->dialog.window, &calW->dialog.header, (unsigned char*)"Booked Appointment", FONT, UI1_COLOR_BLUE);
    UI1_HeaderSetLine(&calW->dialog.header);
    UI1_ChangeTextFgColor(&calW->dialog.header.element, UI1_COLOR_WHITE);
    h = (UI1_PixelDim)(UI1_GetElementHeight(&calW->dialog.header));
    (void)UI1_CreateIcon(&calW->dialog.window, &calW->dialog.iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
    calW->dialog.iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
    UI1_OnWindowResize(&calW->dialog.window); /* right align element(s) if needed */
    UI1_ChangeElementColor(&calW->dialog.iconClose, UI1_COLOR_BLUE);
    UI1_ChangeIconFgColor(&calW->dialog.iconClose, UI1_COLOR_WHITE);
    UI1_EnableElementSelection(&calW->dialog.iconClose);
    
    yPos = (UI1_PixelDim)(UI1_GetElementHeight(&calW->dialog.header)+2);
    calW->dialog.dateTimeBuf[0] = '\0';
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), selection->appoint->start.day, '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)"-");
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), selection->appoint->start.month, '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)"-");
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (int16_t)selection->appoint->start.year, '0', 4); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)" ");
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), selection->appoint->start.hour, '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)":");
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), selection->appoint->start.minute, '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)"-");
    minutes = (word)(60*selection->appoint->start.hour+selection->appoint->start.minute+selection->appoint->durationMinutes);
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (int16_t)(minutes/60), '0', 2); 
    UTIL1_strcat(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (unsigned char*)":");
    UTIL1_strcatNum16sFormatted(calW->dialog.dateTimeBuf, sizeof(calW->dialog.dateTimeBuf), (int16_t)(minutes%60), '0', 2); 
    (void)UI1_CreateText(&calW->dialog.window, &calW->dialog.dateTime, 2, yPos, 0, 0, calW->dialog.dateTimeBuf, FONT);
    
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&calW->dialog.dateTime)+2);
    (void)UI1_CreateText(&calW->dialog.window, &calW->dialog.text, 2, yPos, 0, 0, selection->appoint->text, FONT);
   
    UI1_RefreshDialogWindow(&calW->dialog.window);
  }
}

static void CalW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element,&calW->iconClose)) {
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
    }
  } else if (kind == UI1_EVENT_CALENDARDAY_APPOINTMENT_CLICK) { /* click on a calendar appointment item */
    CalW_CreateAppointmentDialog(element);
  }
}

static void CreateWindow(void) {
  UICalendar1_CalendarDateTime startDateTime;
  DATEREC date;
  TIMEREC time;
  UI1_PixelDim h, yPos;

  /* screen and main window with header */
  UI1_CreateScreen(&calW->screen, UI1_COLOR_BRIGHT_YELLOW);
  (void)UI1_CreateWindow(&calW->screen, &calW->window, UI1_COLOR_BRIGHT_YELLOW, 0, 0, UI1_GetWidth(), UI1_GetHeight());
  (void)UI1_CreateHeader(&calW->window, &calW->header, (unsigned char*)"Calendar", FONT, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&calW->header.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&calW->window, CalW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&calW->header));
  (void)UI1_CreateIcon(&calW->window, &calW->iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  calW->iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&calW->window); /* right align element(s) if needed */
  UI1_ChangeElementColor(&calW->iconClose, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&calW->iconClose, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&calW->iconClose);
  yPos = (UI1_PixelDim)(UI1_GetElementHeight(&calW->header));
  /* CalendarDay */
  (void)TmDt1_GetDate(&date);
  (void)TmDt1_GetTime(&time);
  startDateTime.day = date.Day;
  startDateTime.month = date.Month;
  startDateTime.year = date.Year;
  startDateTime.hour = 8;
  startDateTime.minute = 0;
  (void)UICalendar1_CreateCalendarDay(&calW->window, &calW->calendarDay, 0, yPos, UI1_GetWidth(), (UI1_PixelDim)(UI1_GetHeight()-yPos), &startDateTime);
  /* now paint the screen */
  UI1_UpdateScreen(&calW->screen);
}

void CAL_StartTask(CAL_WindowDesc *desc) {
  calW = desc;
  CreateWindow();
}

#endif /* PL_HAS_CALENDAR_DEMO */


/* END Calendar */
