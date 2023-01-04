/*
 * Copyright (c) 2019-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_GUI

#include "gui.h"
#include "gui_config.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuRTOS.h"
#include "oled.h"
#include "McuSSD1306.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuUtility.h"
#include "McuLog.h"

static TaskHandle_t GUI_TaskHndl; /* GUI task handle */
static TimerHandle_t timerHndlGuiExpired; /* timeout user actions */
static TimerHandle_t timerHndlCycleScreens; /* timer for cycling screens */

/* direct task notification bits */
#define GUI_TASK_NOTIFY_BUTTON_PRESSED  (1<<0)  /* a button has been pressed */
#define GUI_TASK_NOTIFY_GUI_TIMEOUT     (1<<1)  /* user did not press a button for some time */
#define GUI_TASK_NOTIFY_NEXT_SCREEN     (1<<2)  /* show the next cycling screen */

#if PL_CONFIG_USE_GUI_KEY_NAV && LV_USE_GROUP
#define GUI_GROUP_NOF_IN_STACK   4
typedef struct GUI_Group_t {
  lv_group_t *stack[GUI_GROUP_NOF_IN_STACK]; /* stack of GUI groups */
  uint8_t sp; /* stack pointer, points to next free element */
} GUI_Group_t;
static GUI_Group_t groups;

void GUI_AddObjToGroup(lv_obj_t *obj) {
  lv_group_add_obj(GUI_GroupPeek(), obj);
}

void GUI_RemoveObjFromGroup(lv_obj_t *obj) {
  lv_group_remove_obj(obj);
}

lv_group_t *GUI_GroupPeek(void) {
  if (groups.sp == 0) {
    return NULL;
  }
  return groups.stack[groups.sp-1];
}

void GUI_GroupPull(void) {
  if (groups.sp == 0) {
    return;
  }
  lv_group_del(groups.stack[groups.sp-1]);
  groups.sp--;
  lv_indev_set_group(LV_GetInputDevice(), groups.stack[groups.sp-1]); /* assign group to input device */
}

void GUI_GroupPush(void) {
  lv_group_t *gui_group;

  if (groups.sp >= GUI_GROUP_NOF_IN_STACK) {
    return;
  }
  gui_group = lv_group_create();
  lv_indev_set_group(LV_GetInputDevice(), gui_group); /* assign group to input device */
  /* change the default focus style which is an orange'ish thing */
  //lv_group_set_style_mod_cb(gui_group, style_mod_cb);
  groups.stack[groups.sp] = gui_group;
  groups.sp++;
}
#endif /* PL_CONFIG_USE_GUI_KEY_NAV */


/* ------------------------------------------------------- PicoHouse GUI ----------------------------------------------- */
/* global GUI elements */
typedef enum GuiScreens_e {
  GUI_SCREEN_SETTINGS, /* Settings, must be first in list! */
  GUI_SCREEN_FIRST_CYCLING,
  GUI_SCREEN_ENERGY=GUI_SCREEN_FIRST_CYCLING,
  GUI_SCREEN_NOF_SCREENS /* sentinel, must be last! */
} GuiScreens_e;

static struct guiObjects {
  lv_obj_t *screens[GUI_SCREEN_NOF_SCREENS]; /* screen 0 or GUI_SCREEN_SETTINGS is the one with the settings */
  /* styles */
  lv_style_t style_customFont; /* style for custom font with symbols, needs to be global */

} guiObjects;

/*
 * How to add symbols: https://docs.lvgl.io/8.3/overview/font.html#add-new-symbols
 * Unicode to UTF-8: https://www.cogsci.ed.ac.uk/~richard/utf-8.cgi?input=f287&mode=hex
 * Note: lvgl uses V5 of FontAwesome, use
 * https://fontawesome.com/v5/search
 * for searching symbols, use 'free' filter
 *
 * MY_SYMBOL_CAR
 *    https://fontawesome.com/v5/icons/bus?s=solid&f=classic
 *    Unicode: 0xf207, Hex UTF-8: EF 88 87
 * MY_SYMBOL_LIGHT
 *    https://fontawesome.com/icons/lightbulb?s=regular&f=classic,
 *    Unicode: 0xf0eb, Hex UTF-8: EF 83 AB
 * MY_SYMBOL_X
 *    https://fontawesome.com/v5/icons/times-circle?s=solid&f=classic
 *    Unicode: 0xf057, Hex UTF-8: EF 81 97
 * MY_SYMBOL_SUN
 *    https://fontawesome.com/v5/icons/sun?s=solid&f=classic
 *    Unicode: 0xf185, Hex UTF-8: EF 86 85
 * MY_SYMBOL_ARROW_UP
 *    https://fontawesome.com/v5/icons/arrow-up?s=regular&f=classic
 *    Unicode: 0xf062, Hex UTF-8: EF 81 A2
 * MY_SYMBOL_ARROW_DOWN
 *    https://fontawesome.com/v5/icons/arrow-down?s=solid&f=classic
 *    Unicode: 0xf063, Hex UTF-8: EF 81 A3
 * MY_SYMBOL_ARROW_LEFT_RIGHT
 *    https://fontawesome.com/v5/icons/exchange-alt?s=solid&f=classic
 *    Unicode: 0xf362, Hex UTF-8: EF 8D A2
 *
 * Font Converter: https://lvgl.io/tools/fontconverter
 * Name: customSymbols_12
 * Size: 12
 * Bpp: 1 bit-per-pixel
 * Options: all three disabled
 * Range:  0xf207,0xf0eb,0xf057,0xf185,0xf062,0xf063,0xf362,   (use the Unicode!)
 * Add the ones below which are part of LVGL:
61441,61448,61451,61452,61452,61453,61457,61459,61461,61465,
61468,61473,61478,61479,61480,61502,61512,61515,61516,61517,
61521,61522,61523,61524,61543,61544,61550,61552,61553,61556,
61559,61560,61561,61563,61587,61589,61636,61637,61639,61671,
61674,61683,61724,61732,61787,61931,62016,62017,62018,62019,
62020,62087,62099,62212,62189,62810,63426,63650
 * Browse: use image/FontAwesome5-Solid+Brands+Regular.woff  (Note: that's version 5, not all symbols are available)
 * Symbols: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY0123456789
 */
LV_FONT_DECLARE(customSymbols_12); /* font name with custom symbols plus the normal symbols/characters */
/* IDs of the symbols, use the Hex UTF-8 code: */
#define MY_SYMBOL_CAR               "\xEF\x88\x87" /* a car */
#define MY_SYMBOL_LIGHT             "\xEF\x83\xAB" /* a light bulb */
#define MY_SYMBOL_X                 "\xEF\x81\x97" /* a round shape with a cross */
#define MY_SYMBOL_SUN               "\xEF\x86\x85" /* a sun */
#define MY_SYMBOL_ARROW_UP          "\xEF\x81\xA2" /* an arrow pointing up */
#define MY_SYMBOL_ARROW_DOWN        "\xEF\x81\xA3" /* an arrow pointing down */
#define MY_SYMBOL_ARROW_LEFT_RIGHT  "\xEF\x8D\xA2" /* two arrows pointing left and right */

/* ---------------------------------------------------------------------------------- */
static void createGUI(void) {
  /* initialize and create the screens */
  for(int i = 0; i<sizeof(guiObjects.screens)/sizeof(guiObjects.screens[0]); i++) {
    guiObjects.screens[i] = lv_obj_create(NULL);
  }
  /* initialize styles */
  lv_style_init(&guiObjects.style_customFont); /* style with custom symbol font */
  lv_style_set_text_font(&guiObjects.style_customFont, &customSymbols_12);

  /* create the different screens */
  lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]);
  /* \todo add widgets */
}

/* ------------------------------------------------------- creating main screen/menu ----------------------------------------------- */
static void Gui_Create(void) {
 #if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
#endif
  createGUI();
}

typedef enum GuiState_e {
  GUI_STATE_IDLE,                   /* idle mode */
  GUI_STATE_SHOW_SETTINGS,          /* show settings screen */
  GUI_STATE_START_CYCLING_SCREEN,   /* start the cycling screens */
  GUI_STATE_SHOW_CYCLING_SCREEN,    /* show cycling screens */
  GUI_STATE_IDLE_CYCLING_SCREEN,    /* idle between screen cycling */
  GUI_STATE_ENTER_SCREEN_SAVER,     /* enter screen saver mode */
  GUI_STATE_ACTIVE_SCREEN_SAVER,    /* screen saver running */
  GUI_STATE_EXIT_SCREEN_SAVER,      /* exit screen saver mode */
} GuiState_e;

static void GuiTask(void *pv) {
  GuiScreens_e currScreen = GUI_SCREEN_SETTINGS;
  int turnDisplayOffTimeout = GUI_CONFIG_NOF_SCREEN_CYCLING_UNTIL_DISPLAY_OFF;
  bool screenSaverIsOn = false;
  GuiState_e state = GUI_STATE_SHOW_SETTINGS;
  BaseType_t res;
  uint32_t notifcationValue;

  (void)pv; /* not used */
  vTaskDelay(pdMS_TO_TICKS(500)); /* give hardware time to power up */
  McuSSD1306_Init(); /* requires I2C interrupts enabled if using HW I2C! */
  McuSSD1306_Clear();
  Gui_Create();
  lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]);
  for(;;) {
    /* handle notification events */
    res = xTaskNotifyWait(0UL, /* pre-clear flags */
        GUI_TASK_NOTIFY_BUTTON_PRESSED|GUI_TASK_NOTIFY_GUI_TIMEOUT|GUI_TASK_NOTIFY_NEXT_SCREEN, /* flags to check */
        &notifcationValue, /* where to store the bits */
        pdMS_TO_TICKS(20) /* timeout */
    );
    if (res==pdTRUE) { /* received notification */
      if (notifcationValue&GUI_TASK_NOTIFY_BUTTON_PRESSED) { /* user pressed a button */
        switch(state) {
          case GUI_STATE_START_CYCLING_SCREEN:
          case GUI_STATE_IDLE_CYCLING_SCREEN:
          case GUI_STATE_SHOW_CYCLING_SCREEN: /* button press during cycling screens: show settings */
            if (xTimerIsTimerActive(timerHndlCycleScreens)==pdTRUE) { /* cycling screens active? */
              if (xTimerStop(timerHndlCycleScreens, pdMS_TO_TICKS(10))!=pdPASS) {
                McuLog_fatal("failed stopping timer");
                for(;;); /* failure!?! */
              }
            }
            state = GUI_STATE_SHOW_SETTINGS;
            break;

          case GUI_STATE_ACTIVE_SCREEN_SAVER: /* button press during screen saver: turn on display and show settings */
            state = GUI_STATE_EXIT_SCREEN_SAVER;
            break;

          default:
            break;
        } /* switch */
      } /* if */
      if (notifcationValue&GUI_TASK_NOTIFY_GUI_TIMEOUT) { /* no user action or button press for some time */
        switch(state) {
          case GUI_STATE_IDLE:
            state = GUI_STATE_START_CYCLING_SCREEN;
            break;

          default:
             break;
        } /* switch */
      } /* if */
      if (notifcationValue&GUI_TASK_NOTIFY_NEXT_SCREEN) { /* request to cycle to next screen */
        switch(state) {
          case GUI_STATE_IDLE:
            state = GUI_STATE_START_CYCLING_SCREEN;
            break;
          case GUI_STATE_SHOW_CYCLING_SCREEN:
          case GUI_STATE_IDLE_CYCLING_SCREEN:
            currScreen++;
            if (currScreen>=sizeof(guiObjects.screens)/sizeof(guiObjects.screens[0])) { /* reached the end of the list */
              currScreen = GUI_SCREEN_FIRST_CYCLING;
              turnDisplayOffTimeout--; /* count the iteration */
            }
            if (currScreen==GUI_SCREEN_SETTINGS) {
              currScreen++; /* skip settings screen */
            }
            if (turnDisplayOffTimeout<=0) {
              state = GUI_STATE_ENTER_SCREEN_SAVER;
            } else {
              state = GUI_STATE_SHOW_CYCLING_SCREEN;
            }
            break;

          default:
             break;
        } /* switch */
      } /* if */
    } /* if notification received */

    switch(state) {
      case GUI_STATE_IDLE:
        break;

      case GUI_STATE_SHOW_SETTINGS:
        lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]); /* show settings screen */
        state = GUI_STATE_IDLE;
        break;

      case GUI_STATE_START_CYCLING_SCREEN:
        currScreen = GUI_SCREEN_FIRST_CYCLING;
        turnDisplayOffTimeout = GUI_CONFIG_NOF_SCREEN_CYCLING_UNTIL_DISPLAY_OFF;
        if (xTimerStart(timerHndlCycleScreens, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed starting timer");
          for(;;); /* failure!?! */
        }
        state = GUI_STATE_SHOW_CYCLING_SCREEN;
        break;

      case GUI_STATE_SHOW_CYCLING_SCREEN:
        lv_scr_load(guiObjects.screens[currScreen]);
        state = GUI_STATE_IDLE_CYCLING_SCREEN;
        break;

      case GUI_STATE_IDLE_CYCLING_SCREEN:
        break;

      case GUI_STATE_ENTER_SCREEN_SAVER:
        McuSSD1306_DisplayOn(false); /* turn off */
        /* stop all timers */
        if (xTimerStop(timerHndlGuiExpired, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed stopping timer");
          for(;;); /* failure!?! */
        }
        if (xTimerStop(timerHndlCycleScreens, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed stopping timer");
          for(;;); /* failure!?! */
        }
        state = GUI_STATE_ACTIVE_SCREEN_SAVER;
        break;

      case GUI_STATE_ACTIVE_SCREEN_SAVER:
        break;

      case GUI_STATE_EXIT_SCREEN_SAVER:
        McuSSD1306_DisplayOn(true); /* turn display on */
        state = GUI_STATE_SHOW_SETTINGS;
        break;

      default:
        break;
    } /* switch */
    LV_Task(); /* call this every 1-20 ms */
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

static void StartOrResetGuiTimeoutTimer(void) {
  if (xTimerIsTimerActive(timerHndlGuiExpired)==pdFALSE) {
    /* timer is not active: start it */
    if (xTimerStart(timerHndlGuiExpired, pdMS_TO_TICKS(10))!=pdPASS) {
      McuLog_fatal("failed starting timer");
      for(;;); /* failure!?! */
    }
  } else {
    if (xTimerReset(timerHndlGuiExpired, pdMS_TO_TICKS(10))!=pdPASS) { /* reset timer, e.g. after key press or user input */
      McuLog_fatal("failed resetting timer");
      for(;;); /* failure?!? */
    }
  }
}

void GUI_NotifyUserAction(void) {
  /* called for each key press or user action. */
  StartOrResetGuiTimeoutTimer();
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_BUTTON_PRESSED, eSetBits);
}

static void vTimerCallbackGuiExpired(TimerHandle_t pxTimer) {
  (void)pxTimer; /* not used */
  /* start cycling screen timer */
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_GUI_TIMEOUT, eSetBits);
}

static void vTimerCallbackCycleScreen(TimerHandle_t pxTimer) {
  (void)pxTimer; /* not used */
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_NEXT_SCREEN, eSetBits);
}

void GUI_Init(void) {
  LV_Init(); /* initialize GUI library */
  if (xTaskCreate(GuiTask, "Gui", 3*1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
    for(;;){} /* error */
  }

  /* create a timer to timeout user actions */
  timerHndlGuiExpired = xTimerCreate(
    "guiExpired", /* name */
    pdMS_TO_TICKS(GUI_CONFIG_TIMEOUT_USER_ACTION_SEC*1000), /* period/time */
    pdFALSE, /* one-shot, no auto reload */
    (void*)1, /* timer ID */
    vTimerCallbackGuiExpired); /* callback */
  if (timerHndlGuiExpired==NULL) {
    McuLog_fatal("failed creating timer");
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndlGuiExpired, 0)!=pdPASS) {
    McuLog_fatal("failed starting timer");
    for(;;); /* failure!?! */
  }

  /* timer for screen cycling */
  timerHndlCycleScreens = xTimerCreate(
    "cycleScreen", /* name */
    pdMS_TO_TICKS(GUI_CONFIG_SCREEN_CYLCING_INTERVAL_SEC*1000), /* period/time */
    pdTRUE, /* do auto reload */
    (void*)1, /* timer ID */
    vTimerCallbackCycleScreen); /* callback */
  if (timerHndlCycleScreens==NULL) {
    McuLog_fatal("failed creating timer");
    for(;;); /* failure! */
  }
}
#endif /* PL_CONFIG_HAS_GUI */
