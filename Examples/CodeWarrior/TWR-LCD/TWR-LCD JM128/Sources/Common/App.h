/** ###################################################################
**     Filename  : App.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 21.01.2010, 08:34
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __App_H
#define __App_H

/* MODULE App */

#include "Platform.h"

#if PL_HAS_UI
#include "PE_Types.h"
#include "UI1.h"

#if PL_HAS_CALENDAR_DEMO
  #include "UICalendar1.h"
#endif

typedef enum {
#if PL_HAS_FONT_DEMO
  APP_MODE_FONT_DEMO,    /* Font demo */
#endif
#if PL_HAS_CALENDAR_DEMO
  APP_MODE_CALENDAR,     /* Calendar demo */
#endif
#if PL_HAS_TETRIS_DEMO
  APP_MODE_TETRIS,       /* Tetris game */
#endif
#if PL_HAS_CUBE_DEMO
  APP_MODE_3D_CUBE,      /* 3D cube demo */
#endif
#if PL_HAS_SD_DEMO
  APP_MODE_SD_CARD,      /* SD Card demo */
#endif
#if PL_HAS_TASKLIST
  APP_MODE_TASKLIST,      /* task list demo */
#endif
#if PL_HAS_ACCEL_DEMO
  APP_MODE_ACCEL_DEMO,    /* accelerometer demo */
#endif
#if PL_HAS_MOTOR_GRAPH    /* motor graph window */
  APP_MODE_MOTOR_GRAPH,
#endif
#if PL_HAS_EKG    /* EKG graph window */
  APP_MODE_EKG_GRAPH,
#endif
#if PL_HAS_CALIBRATION_DEMO
  APP_MODE_CALIBRATION,  /* calibration screen */
#endif
#if PL_HAS_TOUCHSCREEN_DEMO
  APP_MODE_TOUCHSCREEN_DEMO, /* touch screen demo */
#endif
#if PL_HAS_SOLAR
  APP_MODE_SOLAR,
#endif
#if PL_HAS_RUNNER
  APP_MODE_RUNNER,
#endif
  APP_MODE_MAIN_MENU,    /* main menu */
  APP_MODE_MAIN_CONFIG  /* configuration dialog */
} APP_ApplicationMode;


void APP_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind event);

void APP_SetApplicationMode(APP_ApplicationMode mode);

void APP_HandleEvent(byte event);

void APP_Init(void);
#endif /* PL_HAS_UI */
/* END App */

#endif

