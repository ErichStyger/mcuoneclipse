/** ###################################################################
**     Filename  : App.C
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 21.01.2010, 08:34
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE App */

#include "Platform.h"

#if PL_HAS_UI
#include "Cour08n.h"
#include "Cour08b.h"
#include "Helv08n.h"
#include "Helv10n.h"
#include "Helv12n.h"
#include "Helv14n.h"
#include "Helv18n.h"
#include "Helv24n.h"
#include "EVNT1.h"
#include "Touchscreen.h"
#include "UI1.h"
#if PL_HAS_RUNNER
  #include "Runner.h"
#endif
#if PL_HAS_WATCHDOG
  #include "Watchdog.h"
#endif
#if PL_USE_RTOS
  #include "FRTOS1.h"
#endif
#include "RTOS.h"
#include "App.h"
#if PL_HAS_CUBE_DEMO
  #include "Cube.h"
#endif
#if PL_HAS_TETRIS_DEMO
  #include "Tetris.h"
#endif
#if PL_HAS_SD_DEMO
  #include "SDcard.h"
#endif
#if PL_HAS_CALENDAR_DEMO
  #include "Calendar.h"
  #include "UICalendar1.h"
  #include "TmDt1.h"
#endif
#if PL_HAS_HW_SOUNDER
  #include "Buzzer.h"
#endif
#if PL_HAS_ACCEL_DEMO
  #include "Accelerometer.h"
#endif
#if PL_HAS_MOTOR_GRAPH
  #include "Motor.h"
#endif
#if PL_HAS_SOLAR
  #include "Solar.h"
#endif
#if PL_HAS_EKG
  #include "EKG.h"
#endif

#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT                PL_FONT()
  #define FONT_08             PL_FONT()
  #define FONT_10             PL_FONT()
  #define FONT_12             PL_FONT()
  #define FONT_14             PL_FONT()
  #define FONT_18             PL_FONT()
  #define FONT_24             PL_FONT()
  #define FONT_C08N           PL_FONT()
  #define FONT_C08B           PL_FONT()
#else
  #define FONT                Helv12n_GetFont()
  #define FONT_08             Helv08n_GetFont()
  #define FONT_10             Helv10n_GetFont()
  #define FONT_12             Helv12n_GetFont()
  #define FONT_14             Helv14n_GetFont()
  #define FONT_18             Helv18n_GetFont()
  #define FONT_24             Helv24n_GetFont()
  #define FONT_C08N           Cour08n_GetFont()
  #define FONT_C08B           Cour08b_GetFont()
#endif

#define COLOR_HEADER        UI1_COLOR_BLUE   /* background color header */
#define COLOR_WINDOW        UI1_COLOR_BRIGHT_YELLOW  /* background color window */
#define COLOR_TEXT_HDR      UI1_COLOR_WHITE  /* text color header */
#define COLOR_TEXT          UI1_COLOR_BLACK  /* text color */
#define COLOR_TEXT_BG       COLOR_WINDOW       /* text background color */


static struct {
  APP_ApplicationMode mode;
  UI1_Screen screen;
  union { /* we are using a union to save memory */
    struct { /* main menu window */
      UI1_Window window;
      UI1_Header header;
      UI1_Button btnConfig;
#if PL_HAS_CALENDAR_DEMO
      UI1_Button btnCalendar;
#endif
#if PL_HAS_FONT_DEMO
      UI1_Button btnFontDemo;
#endif
#if PL_HAS_TETRIS_DEMO
      UI1_Button btnTetris;
#endif
#if PL_HAS_CUBE_DEMO
      UI1_Button btn3Dcube;
#endif
#if PL_HAS_SD_DEMO
      UI1_Button btnSDcard;
#endif
#if PL_HAS_TASKLIST
      UI1_Button btnTaskList;
#endif
#if PL_HAS_ACCEL_DEMO
      UI1_Button btnAccelDemo;
#endif
#if PL_HAS_MOTOR_GRAPH
      UI1_Button btnMotorGraph;
#endif
#if PL_HAS_EKG
      UI1_Button btnEKGGraph;
#endif
#if PL_HAS_SOLAR
      UI1_Button btnSolar;
#endif
#if PL_HAS_RUNNER
      UI1_Button btnRunner;
#endif
#if PL_HAS_CALIBRATION_DEMO
      UI1_Button btnCalibration;
#endif
#if PL_HAS_TOUCHSCREEN_DEMO
      UI1_Button btnTouchScreenDemo;
#endif
      struct {
        UI1_Window window;
        UI1_Header header;
#if PL_HAS_HW_SOUNDER
        UI1_CheckBox soundEnable;
        UI1_ScrollMenu soundFreq;
#endif /* PL_HAS_HW_SOUNDER */
#if PL_HAS_SOLAR
        UI1_Text selection;
        UI1_CheckBox regler1;
        UI1_CheckBox regler2;
        UI1_CheckBox regler3;
#endif /* PL_HAS_SOALR */
#if PL_HAS_ACCEL_DEMO
        UI1_CheckBox accelOrientationEnable;
#endif
        UI1_ScrollMenu orientation;
        UI1_Text txtConfig;
        UI1_Button btnOk, btnCancel;
      } config;
    } mainW;
#if PL_HAS_TETRIS_DEMO
    TETRIS_WindowDesc tetrisW;
#endif
#if PL_HAS_CUBE_DEMO
    CUBE_WindowDesc cubeW;
#endif
#if PL_HAS_SD_DEMO
    SDC_WindowDesc sdW;
#endif
#if PL_HAS_ACCEL_DEMO
    ACCEL_WindowDesc accelW;
#endif
#if PL_HAS_MOTOR_GRAPH
    MOTOR_WindowDesc motorW;
#endif
#if PL_HAS_EKG
    EKG_WindowDesc ekgW;
#endif
#if PL_HAS_SOLAR
    SOLAR_WindowDesc solarW;
#endif
#if PL_HAS_RUNNER
    RUNNER_WindowDesc runnerW;
#endif
#if PL_HAS_TASKLIST
    struct { /* task list window */
      UI1_Window window;
      UI1_Header header;
      UI1_Icon iconClose;
      UI1_Text txtTaskList;
      unsigned char *taskListBufferP; /* about 40 bytes for each task, on the heap! */
    } taskListW;
#endif
#if PL_HAS_FONT_DEMO
    struct { /* font demo window */
      UI1_Window window;
      UI1_Header header;
      UI1_Icon iconClose;
      UI1_Text txtHelv08n;
      UI1_Text txtHelv10n;
      UI1_Text txtHelv12n;
  #if PL_HAS_LARGE_FONT_DEMO
      UI1_Text txtHelv14n;
      UI1_Text txtHelv18n;
      UI1_Text txtHelv24n;
      UI1_Text txtCour08n;
      UI1_Text txtCour08b;
  #endif
    } fontDemoW;
#endif
#if PL_HAS_CALENDAR_DEMO
    CAL_WindowDesc calW;
#endif
#if PL_HAS_TOUCHSCREEN_DEMO
    struct { /* touch screen demo window */
      UI1_Window window;
      UI1_Header header;
      UI1_Icon iconClose;
      UI1_Space space;
    } touchScreenDemoW;
#endif
  } u;
} App;

#if PL_HAS_ACCEL_DEMO
  static bool AccelOrientation_enabled = FALSE;
#endif

#if PL_HAS_HW_SOUNDER
#define SOUND_SCROLL_MENU_ITEMS "100Hz\r500Hz\r1kHz\r2kHz\r3kHz\r4kHz"

static byte SoundRangeGetMenuItemNo(Sounder_FrequencyT value) {
  switch(value) {
    case SOUND_HZ_100: return 0;
    case SOUND_HZ_500: return 1;
    case SOUND_HZ_1000: return 2;
    case SOUND_HZ_2000: return 3;
    case SOUND_HZ_3000: return 4;
    case SOUND_HZ_4000: return 5;
  }
  return 0;
}

static Sounder_FrequencyT SoundGetFreqFromMenuNo(byte menuNo) {
  switch(menuNo) {
    default:
    case 0: return SOUND_HZ_100;
    case 1: return SOUND_HZ_500;
    case 2: return SOUND_HZ_1000;
    case 3: return SOUND_HZ_2000;
    case 4: return SOUND_HZ_3000;
    case 5: return SOUND_HZ_4000;
  }
}
#endif

static byte DisplayOrientationGetMenuItemNo(GDisp1_DisplayOrientation value) {
  switch(value) {
    default:
    case GDisp1_ORIENTATION_PORTRAIT: return 0;
    case GDisp1_ORIENTATION_PORTRAIT180: return 1;
    case GDisp1_ORIENTATION_LANDSCAPE: return 2;
    case GDisp1_ORIENTATION_LANDSCAPE180: return 3;
  }
}

static GDisp1_DisplayOrientation DisplayOrientationFromMenuNo(byte menuNo) {
  switch(menuNo) {
    default:
    case 0: return GDisp1_ORIENTATION_PORTRAIT;
    case 1: return GDisp1_ORIENTATION_PORTRAIT180;
    case 2: return GDisp1_ORIENTATION_LANDSCAPE;
    case 3: return GDisp1_ORIENTATION_LANDSCAPE180;
  }
}

#define DISPLAY_ORIENTATION_MENU_ITEMS "Portrait\rPortrait 180\rLandscape\rLandscape 180"

static bool ButtonClick_Config_Ok(UI1_Window *window, UI1_Element* element) {
  /* returns TRUE if display orientation has been changed */
  bool changedDisplayOrientation;
  GDisp1_DisplayOrientation newOrientation;

  (void)window;
  (void)element;
  /* update state variables: */
#if PL_HAS_SOLAR
  if (UI1_CheckBoxIsChecked(&App.u.mainW.config.regler1)) {
    /* Enable Regler 1 */
    R_Enable(1);
  }
  else if(UI1_CheckBoxIsChecked(&App.u.mainW.config.regler2)){
    /* Enable Regler 2 */
    R_Enable(2);
  }
  else if(UI1_CheckBoxIsChecked(&App.u.mainW.config.regler3)){
    /* Enable Regler 3 */
    R_Enable(3);
  }
#endif
#if PL_HAS_HW_SOUNDER
  if (UI1_CheckBoxIsChecked(&App.u.mainW.config.soundEnable)) {
    BUZ_Enable();
  } else {
    BUZ_Disable();
  }
  BUZ_SetFrequency(SoundGetFreqFromMenuNo(UI1_ScrollMenuGetSelection(&App.u.mainW.config.soundFreq)));
#endif
#if PL_HAS_ACCEL_DEMO
  if (!AccelOrientation_enabled && UI1_CheckBoxIsChecked(&App.u.mainW.config.accelOrientationEnable)) {
    AccelOrientation_enabled = TRUE;
    ACCEL_ResumeOrientationTask();
  } else if (AccelOrientation_enabled && !UI1_CheckBoxIsChecked(&App.u.mainW.config.accelOrientationEnable)) {
    AccelOrientation_enabled = FALSE;
    ACCEL_SuspendOrientationTask();
  }
#endif
  newOrientation = DisplayOrientationFromMenuNo(UI1_ScrollMenuGetSelection(&App.u.mainW.config.orientation));
  changedDisplayOrientation = (bool)(newOrientation != GDisp1_GetDisplayOrientation());
  UI1_SetDisplayOrientation(newOrientation);
  return changedDisplayOrientation;
}

#if PL_HAS_TOUCHSCREEN_DEMO
static void touchScreenDemoW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &App.u.touchScreenDemoW.iconClose)) {
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
    }
  } else if (kind==UI1_EVENT_CLICK_MOVE) {
    if (UI1_EqualElement(element,&App.u.touchScreenDemoW.space)) {
      if (data != NULL) {
        UI1_Coordinate *coord = (UI1_Coordinate*)data;
        #define BOX_SIZE 10

        if (coord->x+BOX_SIZE > UI1_GetElementWidth(window)) {
          coord->x = (UI1_PixelDim)(UI1_GetElementWidth(window)-BOX_SIZE);
        }
        if (coord->y+BOX_SIZE > UI1_GetElementHeight(window)) {
          coord->y = (UI1_PixelDim)(UI1_GetElementHeight(window)-BOX_SIZE);
        }
        UI1_DrawFilledBox(window, coord->x, coord->y, BOX_SIZE, BOX_SIZE, UI1_COLOR_RED);
      }
    }
  }
}
#endif

#if PL_HAS_TASKLIST
static void taskListW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &App.u.taskListW.iconClose)) {
      FRTOS1_vPortFree(App.u.taskListW.taskListBufferP);
      App.u.taskListW.taskListBufferP = NULL;
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
      return;
    }
  }
}
#endif

static void APP_WindowCallback_MainMenu(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK || kind==UI1_EVENT_CLICK_LONG) {
    if (UI1_EqualElement(element, &App.u.mainW.btnConfig)) {
      APP_SetApplicationMode(APP_MODE_MAIN_CONFIG);
#if PL_HAS_CALENDAR_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btnCalendar)) {
      APP_SetApplicationMode(APP_MODE_CALENDAR);
#endif
#if PL_HAS_FONT_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btnFontDemo)) {
      APP_SetApplicationMode(APP_MODE_FONT_DEMO);
#endif
#if PL_HAS_TETRIS_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btnTetris)) {
      APP_SetApplicationMode(APP_MODE_TETRIS);
#endif
#if PL_HAS_CUBE_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btn3Dcube)) {
      APP_SetApplicationMode(APP_MODE_3D_CUBE);
#endif
#if PL_HAS_SD_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btnSDcard)) {
      APP_SetApplicationMode(APP_MODE_SD_CARD);
#endif
#if PL_HAS_TASKLIST
    } else if (UI1_EqualElement(element, &App.u.mainW.btnTaskList)) {
      APP_SetApplicationMode(APP_MODE_TASKLIST);
#endif
#if PL_HAS_CALIBRATION_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btnCalibration)) {
      APP_SetApplicationMode(APP_MODE_CALIBRATION);
#endif
#if PL_HAS_ACCEL_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btnAccelDemo)) {
      APP_SetApplicationMode(APP_MODE_ACCEL_DEMO);
#endif
#if PL_HAS_MOTOR_GRAPH
    } else if (UI1_EqualElement(element, &App.u.mainW.btnMotorGraph)) {
      APP_SetApplicationMode(APP_MODE_MOTOR_GRAPH);
#endif
#if PL_HAS_EKG
    } else if (UI1_EqualElement(element, &App.u.mainW.btnEKGGraph)) {
      APP_SetApplicationMode(APP_MODE_EKG_GRAPH);
#endif
#if PL_HAS_SOLAR
    } else if (UI1_EqualElement(element, &App.u.mainW.btnSolar)) {
      APP_SetApplicationMode(APP_MODE_SOLAR);
#endif
#if PL_HAS_RUNNER
    } else if (UI1_EqualElement(element, &App.u.mainW.btnRunner)) {
      APP_SetApplicationMode(APP_MODE_RUNNER);
#endif
#if PL_HAS_TOUCHSCREEN_DEMO
    } else if (UI1_EqualElement(element, &App.u.mainW.btnTouchScreenDemo)) {
      APP_SetApplicationMode(APP_MODE_TOUCHSCREEN_DEMO);
#endif
    } else if(UI1_EqualElement(element, &App.u.mainW.config.btnOk)) {
      if (ButtonClick_Config_Ok(window, element)) {
        APP_SetApplicationMode(APP_MODE_MAIN_MENU); /* recreate windows and screen, as orientation has been changed */
      } else {
        UI1_CloseDialogWindow(&App.screen, window);
        App.mode = APP_MODE_MAIN_MENU; /* was in dialog mode, now back to main menu */
      }
    } else if(UI1_EqualElement(element, &App.u.mainW.config.btnCancel)) {
      UI1_CloseDialogWindow(&App.screen, window);
    }
  }
}

#if PL_HAS_FONT_DEMO
static void fontDemoW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)window;
  (void)data; /* unused argument */
  if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &App.u.fontDemoW.iconClose)) {
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
    }
  }
}
#endif

void APP_SetApplicationMode(APP_ApplicationMode mode) {
  UI1_PixelDim yPos, xPos;
  UI1_PixelDim h=0;

  (void)h;
#if PL_HAS_WATCHDOG
  WDOG_Clear();
#endif
  App.mode = mode;
  if (mode==APP_MODE_MAIN_MENU) {
    UI1_CreateScreen(&App.screen, UI1_COLOR_GREEN);
    (void)UI1_CreateWindow(&App.screen, &App.u.mainW.window, COLOR_WINDOW, 0, 0, UI1_GetWidth(), UI1_GetHeight());
    UI1_SetWindowEventCallback(&App.u.mainW.window, APP_WindowCallback_MainMenu);

#if PL_HAS_AUTO_DEMO
    (void)UI1_CreateHeader(&App.u.mainW.window, &App.u.mainW.header, (unsigned char*)"Elektrotechnik", FONT_18, COLOR_HEADER);
#else
    (void)UI1_CreateHeader(&App.u.mainW.window, &App.u.mainW.header, (unsigned char*)"Main Menu", FONT_18, COLOR_HEADER);
#endif
    UI1_ChangeTextFgColor((UI1_Element*)&App.u.mainW.header, UI1_COLOR_WHITE);
    yPos = (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.header)+3);

    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnConfig, 5, yPos, 0, 0, (unsigned char*)"Configuration", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnConfig);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnConfig)+3);

#if PL_HAS_FONT_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnFontDemo, 5, yPos, 0, 0, (unsigned char*)"Font Demo", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnFontDemo);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnFontDemo)+3);
#endif

#if PL_HAS_CALENDAR_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnCalendar, 5, yPos, 0, 0, (unsigned char*)"Calendar", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnCalendar);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnCalendar)+3);
#endif

#if PL_HAS_TETRIS_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnTetris, 5, yPos, 0, 0, (unsigned char*)"TetriClone", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnTetris);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnTetris)+3);
#endif

#if PL_HAS_CUBE_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btn3Dcube, 5, yPos, 0, 0, (unsigned char*)"3D Cube", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btn3Dcube);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btn3Dcube)+3);
#endif

#if PL_HAS_SD_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnSDcard, 5, yPos, 0, 0, (unsigned char*)"SD Card", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnSDcard);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnSDcard)+3);
#endif

#if PL_HAS_TASKLIST
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnTaskList, 5, yPos, 0, 0, (unsigned char*)"TaskList", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnTaskList);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnTaskList)+3);
#endif

#if PL_HAS_ACCEL_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnAccelDemo, 5, yPos, 0, 0, (unsigned char*)"Accelerometer", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnAccelDemo);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnAccelDemo)+5);
#endif

#if PL_HAS_MOTOR_GRAPH
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnMotorGraph, 5, yPos, 0, 0, (unsigned char*)"Motor Graph", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnMotorGraph);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnMotorGraph)+5);
#endif

#if PL_HAS_EKG
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnEKGGraph, 5, yPos, 0, 0, (unsigned char*)"EKG Graph", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnEKGGraph);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnEKGGraph)+5);
#endif

#if PL_HAS_SOLAR
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnSolar, 5, yPos, 0, 0, (unsigned char*)"Solar Control", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnSolar);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnSolar)+5);
#endif

#if PL_HAS_RUNNER
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnRunner, 5, yPos+15, 120, 30, (unsigned char*)"Zeitmessung", FONT_12, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnRunner);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnRunner)+5);
#endif

#if PL_HAS_TOUCHSCREEN_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnTouchScreenDemo, 5, yPos, 0, 0, (unsigned char*)"Touchscreen Demo", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnTouchScreenDemo);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnTouchScreenDemo)+3);
#endif

#if PL_HAS_CALIBRATION_DEMO
    (void)UI1_CreateButton(&App.u.mainW.window, &App.u.mainW.btnCalibration, 5, yPos, 0, 0, (unsigned char*)"Touchscreen Calibration", FONT_10, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.btnCalibration);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.btnCalibration)+3);
#endif
#if PL_HAS_WATCHDOG
    WDOG_Clear();
#endif
    UI1_UpdateScreen(&App.screen);
  } else if (mode==APP_MODE_MAIN_CONFIG) {
    /* create dialog window */
    (void)UI1_CreateDialogWindow(&App.screen, &App.u.mainW.config.window, UI1_COLOR_YELLOW, 10, 30, 210, 150);
    UI1_WindowSetBorder(&App.u.mainW.config.window);
    UI1_SetWindowEventCallback(&App.u.mainW.config.window, APP_WindowCallback_MainMenu);

    (void)UI1_CreateHeader(&App.u.mainW.config.window, &App.u.mainW.config.header, (unsigned char*)"Configuration", FONT, UI1_COLOR_BLUE);
    UI1_ChangeTextFgColor((UI1_Element*)&App.u.mainW.config.header, UI1_COLOR_WHITE);
    yPos = (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.header)+5);

#if PL_HAS_SOLAR
    /* text about the configuration */
    (void)UI1_CreateText(&App.u.mainW.config.window, &App.u.mainW.config.selection, 5, yPos, 0, 0, (unsigned char*)"Wählen Sie einen Regler:", FONT_10);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.selection)+5);
    /* checkbox: Regler enable */
    (void)UI1_CreateCheckBox(&App.u.mainW.config.window, &App.u.mainW.config.regler1, 5, yPos, 0, 0, UI1_COLOR_BLACK, UI1_COLOR_WHITE, (unsigned char*)"Regler1", FONT, UI1_COLOR_YELLOW);
    UI1_EnableElementSelection(&App.u.mainW.config.regler1);
    UI1_CheckBoxSet(&App.u.mainW.config.regler1, R_IsEnabled(1));
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.regler1)+5);
    (void)UI1_CreateCheckBox(&App.u.mainW.config.window, &App.u.mainW.config.regler2, 5, yPos, 0, 0, UI1_COLOR_BLACK, UI1_COLOR_WHITE, (unsigned char*)"Regler2", FONT, UI1_COLOR_YELLOW);
    UI1_EnableElementSelection(&App.u.mainW.config.regler2);
    UI1_CheckBoxSet(&App.u.mainW.config.regler2, R_IsEnabled(2));
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.regler2)+5);
    (void)UI1_CreateCheckBox(&App.u.mainW.config.window, &App.u.mainW.config.regler3, 5, yPos, 0, 0, UI1_COLOR_BLACK, UI1_COLOR_WHITE, (unsigned char*)"Regler3", FONT, UI1_COLOR_YELLOW);
    UI1_EnableElementSelection(&App.u.mainW.config.regler3);
    UI1_CheckBoxSet(&App.u.mainW.config.regler3, R_IsEnabled(3));
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.regler3)+5);
#endif

#if PL_HAS_HW_SOUNDER
    /* checkbox: sound enable */
    (void)UI1_CreateCheckBox(&App.u.mainW.config.window, &App.u.mainW.config.soundEnable, 5, yPos, 0, 0, UI1_COLOR_BLACK, UI1_COLOR_WHITE, (unsigned char*)"Sound", FONT, UI1_COLOR_YELLOW);
    UI1_EnableElementSelection(&App.u.mainW.config.soundEnable);
    UI1_CheckBoxSet(&App.u.mainW.config.soundEnable, BUZ_IsEnabled());
    /* scrollMenu sound frequency */
    xPos = (UI1_PixelDim)(UI1_GetElementPosX(&App.u.mainW.config.soundEnable)+UI1_GetElementWidth(&App.u.mainW.config.soundEnable)+15);
    (void)UI1_CreateScrollMenu(&App.u.mainW.config.window, &App.u.mainW.config.soundFreq, xPos, yPos, 0, 0, (unsigned char*)SOUND_SCROLL_MENU_ITEMS, FONT, UI1_COLOR_YELLOW, UI1_COLOR_BLACK, UI1_COLOR_WHITE);
    UI1_ScrollMenuSetSelection(&App.u.mainW.config.soundFreq, SoundRangeGetMenuItemNo(BUZ_GetFrequency()));
    UI1_EnableElementSelection(&App.u.mainW.config.soundFreq);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.soundFreq)+5);
    xPos = (UI1_PixelDim)(UI1_GetElementPosX(&App.u.mainW.config.soundEnable));
#else
    xPos = 5;
#endif
#if PL_HAS_ACCEL_DEMO
    (void)UI1_CreateCheckBox(&App.u.mainW.config.window, &App.u.mainW.config.accelOrientationEnable, 5, yPos, 0, 0, UI1_COLOR_BLACK, UI1_COLOR_WHITE, (unsigned char*)"Accelerometer Orientation", FONT, UI1_COLOR_YELLOW);
    UI1_EnableElementSelection(&App.u.mainW.config.accelOrientationEnable);
    UI1_CheckBoxSet(&App.u.mainW.config.accelOrientationEnable, AccelOrientation_enabled);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.accelOrientationEnable)+5);
#endif
    /* scrollMenu display orientation */
    (void)UI1_CreateScrollMenu(&App.u.mainW.config.window, &App.u.mainW.config.orientation, xPos, yPos, 0, 0, (unsigned char*)DISPLAY_ORIENTATION_MENU_ITEMS, FONT, UI1_COLOR_YELLOW, UI1_COLOR_BLACK, UI1_COLOR_WHITE);
    UI1_ScrollMenuSetSelection(&App.u.mainW.config.orientation, DisplayOrientationGetMenuItemNo(GDisp1_GetDisplayOrientation()));
    UI1_EnableElementSelection(&App.u.mainW.config.orientation);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.orientation)+5);

    /* text about the configuration */
    (void)UI1_CreateText(&App.u.mainW.config.window, &App.u.mainW.config.txtConfig, 5, yPos, 0, 0,
      (unsigned char*)
      #if PL_CPU_MCF51JM128
        "JM128"
      #elif PL_CPU_MCF51CN128
        "CN128"
      #elif PL_CPU_MCF52259
        "52259"
      #endif
      #if PL_TWR_LCD_REV_0
       /* ", LCD_Rev0" */
      #elif PL_TWR_LCD_REV_A
       /* ", LCD_RevA" */
      #endif
      #if PL_TWR_LCD_SPI4
        ", 4-SPI"
      #elif PL_TWR_LCD_16BIT
        ", 16bitP"
      #endif
      #if PL_APP_MODE_I2C_LCD
        ", I2C to TWR"
      #elif PL_APP_MODE_I2C_TWR
        ", I2C from LCD"
      #endif
      ,
      FONT_10);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.mainW.config.txtConfig)+5);

    /* Button: OK */
    (void)UI1_CreateButton(&App.u.mainW.config.window, &App.u.mainW.config.btnOk, 10, yPos, 0, 0, (unsigned char*)"OK", FONT, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.config.btnOk);

    /* Button: Cancel */
    (void)UI1_CreateButton(&App.u.mainW.config.window, &App.u.mainW.config.btnCancel, 50, yPos, 0, 0, (unsigned char*)"Cancel", FONT, UI1_COLOR_BRIGHT_BLUE);
    UI1_EnableElementSelection(&App.u.mainW.config.btnCancel);

    UI1_UpdateScreen(&App.screen);
#if PL_HAS_TETRIS_DEMO
  } else if (App.mode == APP_MODE_TETRIS) {
    TETRIS_CreateWindow(&App.u.tetrisW);
#endif /* PL_HAS_TETRIS_DEMO */
#if PL_HAS_CUBE_DEMO
  } else if (App.mode == APP_MODE_3D_CUBE) {
    CUBE_CreateWindow(&App.u.cubeW);
#endif /* PL_HAS_CUBE_DEMO */
#if PL_HAS_SD_DEMO
  } else if (App.mode == APP_MODE_SD_CARD) {
    SDC_StartTask(&App.u.sdW);
#endif /* PL_HAS_CUBE_DEMO */
#if PL_HAS_TASKLIST
  } else if (App.mode == APP_MODE_TASKLIST) {
    size_t bufSize;

    UI1_CreateScreen(&App.screen, UI1_COLOR_WHITE);
    (void)UI1_CreateWindow(&App.screen, &App.u.taskListW.window, UI1_COLOR_BRIGHT_GREEN, 0, 0, UI1_GetWidth(), UI1_GetHeight());
    (void)UI1_CreateHeader(&App.u.taskListW.window, &App.u.taskListW.header, (unsigned char*)"FreeRTOS TaskList", FONT_14, UI1_COLOR_BLUE);
    UI1_ChangeTextFgColor(&App.u.taskListW.header.element, UI1_COLOR_WHITE);
    UI1_SetWindowEventCallback(&App.u.taskListW.window, taskListW_WindowCallback);
    /* Icon: Close */
    h = (UI1_PixelDim)(UI1_GetElementHeight(&App.u.taskListW.header));
    (void)UI1_CreateIcon(&App.u.taskListW.window, &App.u.taskListW.iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
    App.u.taskListW.iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
    UI1_OnWindowResize(&App.u.taskListW.window); /* right align element(s) if needed */
    UI1_ChangeElementColor(&App.u.taskListW.iconClose, UI1_COLOR_BLUE);
    UI1_ChangeIconFgColor(&App.u.taskListW.iconClose, UI1_COLOR_WHITE);
    UI1_EnableElementSelection(&App.u.taskListW.iconClose);
    yPos = (UI1_PixelDim)(UI1_GetElementHeight(&App.u.taskListW.header)+3);

    /* text for task list */
    bufSize = 40*uxTaskGetNumberOfTasks(); /* about 40 bytes for a task should be enough */
    App.u.taskListW.taskListBufferP = FRTOS1_pvPortMalloc(bufSize);
    if (App.u.taskListW.taskListBufferP != NULL) {
      FRTOS1_vTaskList((char*)App.u.taskListW.taskListBufferP, bufSize);
    }
    (void)UI1_CreateText(&App.u.taskListW.window, &App.u.taskListW.txtTaskList, 2, yPos, 0, 0, App.u.taskListW.taskListBufferP, FONT_12);

    /* update the screen */
    UI1_UpdateScreen(&App.screen);
#endif /* PL_HAS_TASKLIST */
#if PL_HAS_ACCEL_DEMO
  } else if (App.mode == APP_MODE_ACCEL_DEMO) {
    ACCEL_StartDemoTask(&App.u.accelW);
#endif
#if PL_HAS_MOTOR_GRAPH
  } else if (App.mode == APP_MODE_MOTOR_GRAPH) {
    MOTOR_StartTask(&App.u.motorW);
#endif
#if PL_HAS_EKG
  } else if (App.mode == APP_MODE_EKG_GRAPH) {
    EKG_StartTask(&App.u.ekgW);
#endif
#if PL_HAS_SOLAR
  } else if (App.mode == APP_MODE_SOLAR) {
    SOLAR_StartTask(&App.u.solarW);
#endif
#if PL_HAS_FONT_DEMO
  } else if (App.mode == APP_MODE_FONT_DEMO) {
    /* screen and main window with header */
    UI1_CreateScreen(&App.screen, UI1_COLOR_WHITE);
    (void)UI1_CreateWindow(&App.screen, &App.u.fontDemoW.window, UI1_COLOR_WHITE, 0, 0, UI1_GetWidth(), UI1_GetHeight());
    /*UI1_WindowSetBorder(&App.u.fontDemoW.window);*/
#if PL_HAS_AUTO_DEMO
    (void)UI1_CreateHeader(&App.u.fontDemoW.window, &App.u.fontDemoW.header, (unsigned char*)"Elektrotechnik in Horw", FONT, UI1_COLOR_BLUE);
#else
    (void)UI1_CreateHeader(&App.u.fontDemoW.window, &App.u.fontDemoW.header, (unsigned char*)"Font Demo", FONT, UI1_COLOR_BLUE);
#endif
    UI1_HeaderSetLine(&App.u.fontDemoW.header);
    UI1_ChangeTextFgColor(&App.u.fontDemoW.header.element, UI1_COLOR_WHITE);
    UI1_SetWindowEventCallback(&App.u.fontDemoW.window, fontDemoW_WindowCallback);
    /* Icon: Close */
    h = (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.header));
    (void)UI1_CreateIcon(&App.u.fontDemoW.window, &App.u.fontDemoW.iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
    App.u.fontDemoW.iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
    UI1_OnWindowResize(&App.u.fontDemoW.window); /* right align element(s) if needed */
    UI1_ChangeElementColor(&App.u.fontDemoW.iconClose, UI1_COLOR_BLUE);
    UI1_ChangeIconFgColor(&App.u.fontDemoW.iconClose, UI1_COLOR_WHITE);
    UI1_EnableElementSelection(&App.u.fontDemoW.iconClose);
    yPos = (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.header)+3);
#if PL_HAS_AUTO_DEMO
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv12n, 2, yPos, 0, 0,
        (unsigned char*)"\nEin Studium in Elektrotechnik:\nDas macht Spass!\n", FONT_12);
    UI1_ChangeTextFgColor(&App.u.fontDemoW.txtHelv12n.element, UI1_COLOR_BLUE);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv12n));
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv10n, 2, yPos, 0, 0,
        (unsigned char*)"Diese Anwendung zeigt das Zusammenspiel\nvon Hardware und Software.\n\nDie Anwendung zeigt 3D Grafik Routinen\nund Werte des Beschleunigungssensors:\nkleinste Erschütterungen werden erfasst\nund angezeigt.", FONT_10);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv10n));
#else
    /* text Helv08n */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv08n, 2, yPos, 0, 0, (unsigned char*)"Bitmap Fonts using Adobe BDF format:\nHelv08 normal", FONT_08);
    UI1_ChangeTextFgColor(&App.u.fontDemoW.txtHelv08n.element, UI1_COLOR_RED);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtHelv08n);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv08n));
    /* text Helv10n */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv10n, 2, yPos, 0, 0, (unsigned char*)"Helv10 normal", FONT_10);
    UI1_ChangeTextFgColor(&App.u.fontDemoW.txtHelv10n.element, UI1_COLOR_RED);
    UI1_ChangeTextBgColor(&App.u.fontDemoW.txtHelv10n.element, UI1_COLOR_BRIGHT_GREEN);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtHelv10n);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv10n));
    /* text Helv12n */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv12n, 2, yPos, 0, 0, (unsigned char*)"Helv12 normal", FONT_12);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtHelv12n);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv12n));
#endif
    #if PL_HAS_LARGE_FONT_DEMO
    /* text Helv14n */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv14n, 2, yPos, 0, 0, (unsigned char*)"Helv14 normal", FONT_14);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtHelv14n);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv14n));
    /* text Helv18n */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv18n, 2, yPos, 0, 0, (unsigned char*)"Helv18 normal", FONT_18);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtHelv18n);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv18n));
    /* text Helv24n */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtHelv24n, 2, yPos, 0, 0, (unsigned char*)"Helv24 normal", FONT_24);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtHelv24n);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtHelv24n));
    /* text Cour08n */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtCour08n, 2, yPos, 0, 0, (unsigned char*)"Cour08 normal", FONT_C08N);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtCour08n);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtCour08n));
    /* text Cour08b */
    (void)UI1_CreateText(&App.u.fontDemoW.window, &App.u.fontDemoW.txtCour08b, 2, yPos, 0, 0, (unsigned char*)"Cour08 bold", FONT_C08B);
    UI1_EnableElementSelection(&App.u.fontDemoW.txtCour08b);
    yPos += (UI1_PixelDim)(UI1_GetElementHeight(&App.u.fontDemoW.txtCour08b));
  #endif
    /* now paint the screen */
    UI1_UpdateScreen(&App.screen);
#endif /* PL_HAS_FONT_DEMO */
#if PL_HAS_RUNNER
  } else if (App.mode == APP_MODE_RUNNER) {
    RUNNER_StartTask(&App.u.runnerW);
#endif
#if PL_HAS_CALENDAR_DEMO
  } else if (App.mode == APP_MODE_CALENDAR) {
    CAL_StartTask(&App.u.calW);
#endif /* PL_HAS_CALENDAR_DEMO */
#if PL_HAS_TOUCHSCREEN_DEMO
  } else if (App.mode == APP_MODE_TOUCHSCREEN_DEMO) {
    /* screen and main window with header */
    UI1_CreateScreen(&App.screen, UI1_COLOR_BRIGHT_YELLOW);
    (void)UI1_CreateWindow(&App.screen, &App.u.touchScreenDemoW.window, UI1_COLOR_BRIGHT_YELLOW, 0, 0, UI1_GetWidth(), UI1_GetHeight());
    /*UI1_WindowSetBorder(&App.u.touchScreenDemoW.window); */
    (void)UI1_CreateHeader(&App.u.touchScreenDemoW.window, &App.u.touchScreenDemoW.header, (unsigned char*)"TouchScreen Demo", FONT, UI1_COLOR_BLUE);
    UI1_ChangeTextFgColor(&App.u.touchScreenDemoW.header.element, UI1_COLOR_WHITE);
    UI1_SetWindowEventCallback(&App.u.touchScreenDemoW.window, touchScreenDemoW_WindowCallback);
    /* Icon: Close */
    h = (UI1_PixelDim)(UI1_GetElementHeight(&App.u.touchScreenDemoW.header));
    (void)UI1_CreateIcon(&App.u.touchScreenDemoW.window, &App.u.touchScreenDemoW.iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
    App.u.touchScreenDemoW.iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
    UI1_OnWindowResize(&App.u.touchScreenDemoW.window); /* right align element(s) if needed */
    UI1_ChangeElementColor(&App.u.touchScreenDemoW.iconClose, UI1_COLOR_BLUE);
    UI1_ChangeIconFgColor(&App.u.touchScreenDemoW.iconClose, UI1_COLOR_WHITE);
    UI1_EnableElementSelection(&App.u.touchScreenDemoW.iconClose);

    UI1_CreateSpace(&App.u.touchScreenDemoW.window, &App.u.touchScreenDemoW.space,
      UI1_GetElementPosX(&App.u.touchScreenDemoW.header),
      (UI1_PixelDim)(UI1_GetElementPosY(&App.u.touchScreenDemoW.header)+UI1_GetElementHeight(&App.u.touchScreenDemoW.header)),
      UI1_GetElementWidth(&App.u.touchScreenDemoW.header),
      (UI1_PixelDim)(UI1_GetElementHeight(&App.u.touchScreenDemoW.window)-UI1_GetElementHeight(&App.u.touchScreenDemoW.header))
      );
    UI1_EnableElementSelection(&App.u.touchScreenDemoW.space);

    UI1_UpdateScreen(&App.screen);
#endif
#if PL_HAS_CALIBRATION_DEMO
  } else if (App.mode == APP_MODE_CALIBRATION) {
#if PL_HAS_ACCEL_DEMO
    if (AccelOrientation_enabled) {
      ACCEL_SuspendOrientationTask();
    }
#endif
    TouchScreen_CalibrateAndFlash();
#if PL_HAS_ACCEL_DEMO
    if (AccelOrientation_enabled) {
      ACCEL_ResumeOrientationTask();
    }
#endif
    APP_SetApplicationMode(APP_MODE_MAIN_MENU); /* go back to main menu screen after calibration */
#endif
  } /* if */
}

void APP_HandleEvent(byte event) {
  switch(event) {
    case EVNT1_BUTTON_UI_LEFT:
      UI1_SelectNextElement(UI1_GetScreen(), FALSE);
      break;
    case EVNT1_BUTTON_UI_UP:
      UI1_SelectNextElement(UI1_GetScreen(), FALSE);
      break;
    case EVNT1_BUTTON_UI_RIGHT:
      UI1_SelectNextElement(UI1_GetScreen(), TRUE);
      break;
    case EVNT1_BUTTON_UI_DOWN:
      UI1_SelectNextElement(UI1_GetScreen(), TRUE);
      break;
   #if UI1_ANIMATED_BUTTONS
    case EVNT1_BUTTON_UI_MIDDLE_DOWN:
      UI1_ClickSelectedElement(UI1_GetScreen(), UI1_EVENT_CLICK, NULL);
      break;
    case EVNT1_BUTTON_UI_MIDDLE:
      UI1_ClickSelectedElement(UI1_GetScreen(), UI1_EVENT_CLICK_RELEASE, NULL);
      break;
   #else
    case EVNT1_BUTTON_UI_MIDDLE:
      UI1_ClickSelectedElement(UI1_GetScreen(), UI1_EVENT_CLICK, NULL);
      break;
   #endif
  } /* switch */
}

void APP_OnEvent(UI1_Screen *screen, UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind event) {
  (void)screen;
  (void)window;
  (void)element;
  switch(event) {
    case UI1_EVENT_POST_ORIENTATION_CHANGE:
    #if PL_HAS_TETRIS_DEMO
      TETRIS_RefreshWindow();
    #endif
      break;

    case UI1_EVENT_CLICK:
    #if PL_HAS_HW_SOUNDER
      EVNT1_SetEvent(EVNT1_BUZZER_BEEP);
    #endif
      break;
  } /* switch */
#if PL_HAS_CUBE_DEMO
  CUBE_OnEvent(screen, window, element, event);
#endif
}

void APP_Init(void) {
#if PL_HAS_RUNNER
  APP_SetApplicationMode(APP_MODE_RUNNER);
#else
  APP_SetApplicationMode(APP_MODE_MAIN_MENU);
#endif
}
#endif /*PL_HAS_UI*/

/* END App */
