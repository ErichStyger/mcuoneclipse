/*
 * Copyright (c) 2019-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_GUI

#include "gui.h"
#include "gui_config.h"
#include "guiGroup.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuRTOS.h"
#include "McuSSD1306.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuUtility.h"
#include "McuTimeDate.h"
#include "McuLog.h"
#include "lights.h"
#include "NeoPixel.h"
#if PL_CONFIG_USE_ROAD
  #include "road.h"
#endif
#if PL_CONFIG_USE_POWER
  #include "power.h"
#endif
#if PL_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif
#include "Modbus/McuHeidelberg.h"
#if PL_CONFIG_USE_MQTT_CLIENT
  #include "mqtt_client.h"
#endif

static TaskHandle_t GUI_TaskHndl; /* GUI task handle */
#if GUI_CONFIG_USE_SCREENSAVER
  static TimerHandle_t timerHndlGuiExpired; /* timeout user actions */
#endif
#if GUI_CONFIG_USE_CYCLING_SCREEN
  static TimerHandle_t timerHndlCycleScreens; /* timer for cycling screens */
#endif

/* direct task notification bits */
#define GUI_TASK_NOTIFY_BUTTON_PRESSED  (1<<0)  /* a button has been pressed */
#if GUI_CONFIG_USE_SCREENSAVER
#define GUI_TASK_NOTIFY_GUI_TIMEOUT     (1<<1)  /* user did not press a button for some time */
#endif
#if GUI_CONFIG_USE_CYCLING_SCREEN
  #define GUI_TASK_NOTIFY_NEXT_SCREEN     (1<<2)  /* show the next cycling screen */
#endif
/* ------------------------------------------------------- GUI ----------------------------------------------- */
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
  /* global objects */
  lv_obj_t *dropdown_user_charging_mode; /* drop down for the user charging mode: fast, slow, ... */
  lv_obj_t *label_charger_status; /* label/text for the charger hardware status: A1, A2, B1, .. */
  lv_obj_t *label_solar_watt; /* label/text for the available solar power */
  lv_obj_t *label_site_watt; /* label/text for the power consumed by site (without charger) */
  lv_obj_t *label_charger_watt; /* label/text for the actual charging power */
  lv_obj_t *label_grid_watt; /* label/text for the grid power */
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
 * TTF/WOFF: select file 'FontAwesome5-Solid+Brands+Regular.woff' inside image folder of this project
 * Range:  0xf207,0xf0eb,0xf057,0xf185,0xf062,0xf063,0xf362,   (use the Unicode!)
 * Add the ones below which are part of LVGL:
61441,61448,61451,61452,61452,61453,61457,61459,61461,61465,
61468,61473,61478,61479,61480,61502,61512,61515,61516,61517,
61521,61522,61523,61524,61543,61544,61550,61552,61553,61556,
61559,61560,61561,61563,61587,61589,61636,61637,61639,61671,
61674,61683,61724,61732,61787,61931,62016,62017,62018,62019,
62020,62087,62099,62212,62189,62810,63426,63650
 * Browse: use image/FontAwesome5-Solid+Brands+Regular.woff  (Note: that's version 5, not all symbols are available)
 * Symbols: abcdefghijklmnopqrstuvwxyz +-.,;:ABCDEFGHIJKLMNOPQRSTUVWXY0123456789
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
static void event_handler_drop_down_chargingMode(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    int idx = lv_dropdown_get_selected(obj); /* 0: fw, 1: bw, 2: auto */
    McuHeidelberg_SetUserChargingMode((McuHeidelberg_UserChargingMode_e)idx);
  }
}

static void event_handler_charger_status(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *label = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    uint8_t buf[16];
    McuHeidelbergChargerState_e state;

    buf[0] = '\0';
    state = McuHeidelberg_GetHWChargerState();
    switch(state) {
      case McuHeidelberg_ChargerState_A1:
        McuUtility_strcat(buf, sizeof(buf), LV_SYMBOL_CLOSE);
        break;
      case McuHeidelberg_ChargerState_A2:
        McuUtility_strcat(buf, sizeof(buf), LV_SYMBOL_OK);
        break;
      case McuHeidelberg_ChargerState_B1:
        McuUtility_strcat(buf, sizeof(buf), MY_SYMBOL_CAR " " LV_SYMBOL_CLOSE);
        break;
      case McuHeidelberg_ChargerState_B2:
        McuUtility_strcat(buf, sizeof(buf), MY_SYMBOL_CAR " " LV_SYMBOL_OK);
        break;
      case McuHeidelberg_ChargerState_C1:
        McuUtility_strcat(buf, sizeof(buf), MY_SYMBOL_CAR " " LV_SYMBOL_CHARGE LV_SYMBOL_CLOSE);
        break;
      case McuHeidelberg_ChargerState_C2:
        McuUtility_strcat(buf, sizeof(buf), MY_SYMBOL_CAR " " LV_SYMBOL_CHARGE LV_SYMBOL_OK);
        break;
      case McuHeidelberg_ChargerState_Derating:
        McuUtility_strcat(buf, sizeof(buf), LV_SYMBOL_SHUFFLE);
        break;
      case McuHeidelberg_ChargerState_F:
        McuUtility_strcat(buf, sizeof(buf), LV_SYMBOL_SETTINGS);
        break;
      case McuHeidelberg_ChargerState_E:
      case McuHeidelberg_ChargerState_Error:
        McuUtility_strcat(buf, sizeof(buf), LV_SYMBOL_WARNING);
        break;
    }
    McuUtility_chcat(buf, sizeof(buf), ' ');
    McuUtility_strcat(buf, sizeof(buf), McuHeidelberg_GetShortHWChargerStateString(state));
    lv_label_set_text(label, buf);
  }
}

static void strCatKiloWatt(unsigned char *buf, size_t bufSize, int32_t watt) {
  McuUtility_strcatNum32sFormatted(buf, bufSize, watt/1000, ' ', 2);
  McuUtility_chcat(buf, bufSize, '.');
  if (watt<0) { /* care about modulo for negative number */
    watt = - watt;
  }
  McuUtility_strcatNum32u(buf, bufSize, (watt%1000)/100);
  McuUtility_chcat(buf, bufSize, 'k');
}

static void event_handler_solar_power(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *label = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    uint8_t buf[16];
    uint32_t watt = McuHeidelberg_GetSolarPowerWatt();

    buf[0] = '\0';
    strCatKiloWatt(buf, sizeof(buf), watt);
    lv_label_set_text(label, buf);
  }
}

static void event_handler_site_power(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *label = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    uint8_t buf[16];
    uint32_t watt = McuHeidelberg_GetSiteWithoutChargerPowerWatt();

    buf[0] = '\0';
    strCatKiloWatt(buf, sizeof(buf), watt);
    lv_label_set_text(label, buf);
  }
}

static void event_handler_car_set_power(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *label = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    uint8_t buf[16];
    uint32_t watt = McuHeidelberg_GetCurrChargerPower();

    buf[0] = '\0';
    strCatKiloWatt(buf, sizeof(buf), watt);
    lv_label_set_text(label, buf);
  }
}

static void event_handler_grid_power(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *label = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    uint8_t buf[16];
    uint32_t watt = McuHeidelberg_GetGridPowerWatt();

    buf[0] = '\0';
    strCatKiloWatt(buf, sizeof(buf), watt);
    lv_label_set_text(label, buf);
  }
}

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

  lv_obj_t *panel_charger;
  {
    panel_charger = lv_obj_create(lv_scr_act());
    lv_obj_set_pos(panel_charger, 0, 0);
    lv_obj_set_size(panel_charger, 120, 64);
    lv_obj_add_flag(panel_charger, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    /* Create a drop down for the charger modes */
    guiObjects.dropdown_user_charging_mode = lv_dropdown_create(panel_charger);
    lv_dropdown_set_options(
        guiObjects.dropdown_user_charging_mode,
        LV_SYMBOL_STOP "\n"         /* stop */
        MY_SYMBOL_SUN MY_SYMBOL_SUN  "\n"         /* PV only */
        LV_SYMBOL_CHARGE "\n"       /* slow */
        LV_SYMBOL_CHARGE MY_SYMBOL_SUN "\n"    /* slow+pv */
        LV_SYMBOL_CHARGE LV_SYMBOL_CHARGE /* fast */
        /* pv only */
        );
    lv_obj_set_width(guiObjects.dropdown_user_charging_mode, 45);
    lv_obj_set_height(guiObjects.dropdown_user_charging_mode, 20);
    lv_obj_set_pos(guiObjects.dropdown_user_charging_mode, 0, 0);
    lv_dropdown_set_selected(guiObjects.dropdown_user_charging_mode, McuHeidelberg_GetUserChargingMode());
    lv_obj_add_style(guiObjects.dropdown_user_charging_mode, &guiObjects.style_customFont, LV_PART_MAIN); /* assign custom font */

    /* assign font to the list of items, when drop-down is open */
    lv_obj_t *list;
    list = lv_dropdown_get_list(guiObjects.dropdown_user_charging_mode); /* get the list */
    lv_obj_add_style(list, &guiObjects.style_customFont, LV_PART_MAIN); /* assign custom font */

    lv_obj_add_event_cb(guiObjects.dropdown_user_charging_mode, event_handler_drop_down_chargingMode, LV_EVENT_ALL, NULL);
  #if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_AddObjToGroup(guiObjects.dropdown_user_charging_mode);
  #endif

    /* label for the charger status */
    guiObjects.label_charger_status = lv_label_create(panel_charger);
    lv_label_set_text(guiObjects.label_charger_status, McuHeidelberg_GetShortHWChargerStateString(McuHeidelberg_GetHWChargerState()));
    lv_obj_add_style(guiObjects.label_charger_status, &guiObjects.style_customFont, LV_PART_MAIN);
    lv_obj_align_to(guiObjects.label_charger_status, guiObjects.dropdown_user_charging_mode, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_event_cb(guiObjects.label_charger_status, event_handler_charger_status, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(guiObjects.label_charger_status, LV_EVENT_VALUE_CHANGED, NULL); /* force update */

    /* symbols for the different watt values */
    lv_obj_t *symbol_sun, *symbol_site, *symbol_car, *symbol_charger;

    symbol_sun = lv_label_create(panel_charger);
    lv_label_set_text(symbol_sun, MY_SYMBOL_SUN);
    lv_obj_add_style(symbol_sun, &guiObjects.style_customFont, LV_PART_MAIN);
    lv_obj_align_to(symbol_sun, guiObjects.dropdown_user_charging_mode, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 4);

    symbol_site = lv_label_create(panel_charger);
    lv_label_set_text(symbol_site, LV_SYMBOL_HOME);
    lv_obj_add_style(symbol_site, &guiObjects.style_customFont, LV_PART_MAIN);
    lv_obj_align_to(symbol_site, symbol_sun, LV_ALIGN_OUT_LEFT_MID, 68, 0);

    symbol_car = lv_label_create(panel_charger);
    lv_label_set_text(symbol_car, MY_SYMBOL_CAR);
    lv_obj_add_style(symbol_car, &guiObjects.style_customFont, LV_PART_MAIN);
    lv_obj_align_to(symbol_car, symbol_sun, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 1);

    symbol_charger = lv_label_create(panel_charger);
    lv_label_set_text(symbol_charger, LV_SYMBOL_CHARGE);
    lv_obj_add_style(symbol_charger, &guiObjects.style_customFont, LV_PART_MAIN);
    lv_obj_align_to(symbol_charger, symbol_car, LV_ALIGN_OUT_LEFT_MID, 68, 0);

    /* label for the solar power status */
    {
      uint8_t buf[16];
      uint32_t watt = McuHeidelberg_GetSolarPowerWatt();

      guiObjects.label_solar_watt = lv_label_create(panel_charger);
      buf[0] = '\0';
      strCatKiloWatt(buf, sizeof(buf), watt);
      lv_label_set_text(guiObjects.label_solar_watt, buf);
      lv_label_set_long_mode(guiObjects.label_solar_watt, LV_LABEL_LONG_CLIP);
      lv_obj_set_width(guiObjects.label_solar_watt, 35);
      lv_obj_set_style_text_align(guiObjects.label_solar_watt, LV_TEXT_ALIGN_RIGHT, 0);
      lv_obj_add_style(guiObjects.label_solar_watt, &guiObjects.style_customFont, LV_PART_MAIN);
      lv_obj_align_to(guiObjects.label_solar_watt, symbol_sun, LV_ALIGN_OUT_RIGHT_MID, 0, 1);
      lv_obj_add_event_cb(guiObjects.label_solar_watt, event_handler_solar_power, LV_EVENT_VALUE_CHANGED, NULL);
    }

    /* label for the site power status */
    {
      uint8_t buf[16];
      uint32_t watt = McuHeidelberg_GetSitePowerWatt()-McuHeidelberg_GetCurrChargerPower();

      guiObjects.label_site_watt = lv_label_create(panel_charger);
      buf[0] = '\0';
      strCatKiloWatt(buf, sizeof(buf), watt);
      lv_label_set_text(guiObjects.label_site_watt, buf);
      lv_label_set_long_mode(guiObjects.label_site_watt, LV_LABEL_LONG_CLIP);
      lv_obj_set_width(guiObjects.label_site_watt, 40);
      lv_obj_set_style_text_align(guiObjects.label_site_watt, LV_TEXT_ALIGN_RIGHT, 0);
      lv_obj_add_style(guiObjects.label_site_watt, &guiObjects.style_customFont, LV_PART_MAIN);
      lv_obj_align_to(guiObjects.label_site_watt, symbol_site, LV_ALIGN_OUT_RIGHT_MID, 0, 2);
      lv_obj_add_event_cb(guiObjects.label_site_watt, event_handler_site_power, LV_EVENT_VALUE_CHANGED, NULL);
    }

    /* label for the car charging watt */
    {
      uint8_t buf[16];
      uint32_t watt = McuHeidelberg_GetCurrChargerPower();

      guiObjects.label_charger_watt = lv_label_create(panel_charger);
      buf[0] = '\0';
      strCatKiloWatt(buf, sizeof(buf), watt);
      lv_label_set_text(guiObjects.label_charger_watt, buf);
      lv_label_set_long_mode(guiObjects.label_charger_watt, LV_LABEL_LONG_CLIP);
      lv_obj_set_width(guiObjects.label_charger_watt, 35);
      lv_obj_set_style_text_align(guiObjects.label_charger_watt, LV_TEXT_ALIGN_RIGHT, 0);
      lv_obj_add_style(guiObjects.label_charger_watt, &guiObjects.style_customFont, LV_PART_MAIN);
      lv_obj_align_to(guiObjects.label_charger_watt, symbol_car, LV_ALIGN_OUT_RIGHT_MID, 0, 2);
      lv_obj_add_event_cb(guiObjects.label_charger_watt, event_handler_car_set_power, LV_EVENT_VALUE_CHANGED, NULL);
    }

    /* label for the grid power */
    {
      uint8_t buf[16];
      int32_t watt = McuHeidelberg_GetGridPowerWatt();

      guiObjects.label_grid_watt = lv_label_create(panel_charger);
      buf[0] = '\0';
      strCatKiloWatt(buf, sizeof(buf), watt);
      lv_label_set_text(guiObjects.label_grid_watt, buf);
      lv_label_set_long_mode(guiObjects.label_solar_watt, LV_LABEL_LONG_CLIP);
      lv_obj_set_width(guiObjects.label_grid_watt, 40);
      lv_obj_set_style_text_align(guiObjects.label_grid_watt, LV_TEXT_ALIGN_RIGHT, 0);
      lv_obj_add_style(guiObjects.label_grid_watt, &guiObjects.style_customFont, LV_PART_MAIN);
      lv_obj_align_to(guiObjects.label_grid_watt, symbol_charger, LV_ALIGN_OUT_RIGHT_MID, 0, 2);
      lv_obj_add_event_cb(guiObjects.label_grid_watt, event_handler_grid_power, LV_EVENT_VALUE_CHANGED, NULL);
      lv_obj_add_flag(guiObjects.label_grid_watt, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE);
    }
  }
}

/* event callback from the wallbox */
static void WallboxEventCallback(McuHeidelberg_Event_e event) {
  switch(event) {
    case McuHeidelberg_Event_HW_State_Changed:
      if (guiObjects.label_charger_status!=NULL) {
        lv_event_send(guiObjects.label_charger_status, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
    case McuHeidelberg_Event_UserChargingMode_Changed:
      if (guiObjects.dropdown_user_charging_mode!=NULL) {
        lv_dropdown_set_selected(guiObjects.dropdown_user_charging_mode, McuHeidelberg_GetUserChargingMode());
        lv_event_send(guiObjects.dropdown_user_charging_mode, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
    case McuHeidelberg_Event_SolarPower_Changed:
      if (guiObjects.label_solar_watt!=NULL) {
        lv_event_send(guiObjects.label_solar_watt, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
    case McuHeidelberg_Event_SitePower_Changed:
      if (guiObjects.label_site_watt!=NULL) {
        lv_event_send(guiObjects.label_site_watt, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
    case McuHeidelberg_Event_ChargerPower_Changed:
      if (guiObjects.label_charger_watt!=NULL) {
        lv_event_send(guiObjects.label_charger_watt, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
    case McuHeidelberg_Event_GridPower_Changed:
      if (guiObjects.label_grid_watt!=NULL) {
        lv_event_send(guiObjects.label_grid_watt, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
    default:
      break;
  }
}
/* ------------------------------------------------------- creating main screen/menu ----------------------------------------------- */
static void Gui_Create(void) {
  McuHeidelberg_RegisterEventCallback(WallboxEventCallback); /* register callback */
 #if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
#endif
  createGUI();
}

typedef enum GuiState_e {
  GUI_STATE_IDLE,                   /* idle mode */
  GUI_STATE_SHOW_SETTINGS,          /* show settings screen */
#if GUI_CONFIG_USE_CYCLING_SCREEN
  GUI_STATE_START_CYCLING_SCREEN,   /* start the cycling screens */
  GUI_STATE_SHOW_CYCLING_SCREEN,    /* show cycling screens */
  GUI_STATE_IDLE_CYCLING_SCREEN,    /* idle between screen cycling */
#endif
#if GUI_CONFIG_USE_SCREENSAVER
  GUI_STATE_ENTER_SCREEN_SAVER,     /* enter screen saver mode */
  GUI_STATE_ACTIVE_SCREEN_SAVER,    /* screen saver running */
  GUI_STATE_EXIT_SCREEN_SAVER,      /* exit screen saver mode */
#endif
} GuiState_e;

static void GuiTask(void *pv) {
  GuiScreens_e currScreen = GUI_SCREEN_SETTINGS;
#if GUI_CONFIG_USE_SCREENSAVER
  int turnDisplayOffTimeout = GUI_CONFIG_NOF_SCREEN_CYCLING_UNTIL_DISPLAY_OFF;
  bool screenSaverIsOn = false;
#endif
  GuiState_e state = GUI_STATE_SHOW_SETTINGS;
  BaseType_t res;
  uint32_t notifcationValue;
#if PL_CONFIG_USE_WATCHDOG
  TickType_t xLastWakeTime;
#endif

  (void)pv; /* not used */
#if PL_CONFIG_USE_WATCHDOG
  McuWatchdog_DelayAndReport(McuWatchdog_REPORT_ID_TASK_GUI, 5, 100);
#else
  vTaskDelay(pdMS_TO_TICKS(5*100)); /* give hardware time to power up */
#endif
  #if PL_CONFIG_USE_SHT31
  McuSHT31_Init();
#elif PL_CONFIG_USE_SHT40
  McuSHT40_Init();
#endif
  McuSSD1306_Init();
  McuSSD1306_Clear();
  Gui_Create();
  lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]);
  LV_ClearButtonEventQueue(); /* clear any pending button events created during startup */
  for(;;) {
  #if PL_CONFIG_USE_WATCHDOG
    xLastWakeTime = McuWatchdog_ReportTimeStart();
  #endif
    /* handle notification events */
    res = xTaskNotifyWait(0UL, /* pre-clear flags */
        GUI_TASK_NOTIFY_BUTTON_PRESSED
#if GUI_CONFIG_USE_SCREENSAVER
        |GUI_TASK_NOTIFY_GUI_TIMEOUT
#endif
#if GUI_CONFIG_USE_CYCLING_SCREEN
        |GUI_TASK_NOTIFY_NEXT_SCREEN
#endif
        , /* flags to check */
        &notifcationValue, /* where to store the bits */
        pdMS_TO_TICKS(20) /* timeout */
    );
    if (res==pdTRUE) { /* received notification */
      if (notifcationValue&GUI_TASK_NOTIFY_BUTTON_PRESSED) { /* user pressed a button */
        switch(state) {
      #if GUI_CONFIG_USE_CYCLING_SCREEN
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
      #endif
      #if GUI_CONFIG_USE_SCREENSAVER
          case GUI_STATE_ACTIVE_SCREEN_SAVER: /* button press during screen saver: turn on display and show settings */
            state = GUI_STATE_EXIT_SCREEN_SAVER;
            break;
      #endif
          default:
            break;
        } /* switch */
      } /* if */
    #if GUI_CONFIG_USE_SCREENSAVER
      if (notifcationValue&GUI_TASK_NOTIFY_GUI_TIMEOUT) { /* no user action or button press for some time */
        switch(state) {
          case GUI_STATE_IDLE:
            state = GUI_STATE_START_CYCLING_SCREEN;
            break;

          default:
             break;
        } /* switch */
      } /* if */
    #endif
    #if GUI_CONFIG_USE_CYCLING_SCREEN
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
          #if GUI_CONFIG_USE_SCREENSAVER
              turnDisplayOffTimeout--; /* count the iteration */
          #endif
            }
            if (currScreen==GUI_SCREEN_SETTINGS) {
              currScreen++; /* skip settings screen */
            }
          #if GUI_CONFIG_USE_SCREENSAVER
            if (turnDisplayOffTimeout<=0) {
              state = GUI_STATE_ENTER_SCREEN_SAVER;
            } else {
              state = GUI_STATE_SHOW_CYCLING_SCREEN;
            }
          #else
            state = GUI_STATE_SHOW_CYCLING_SCREEN;
          #endif
            break;

          default:
             break;
        } /* switch */
      } /* if */
    #endif
    } /* if notification received */

    switch(state) {
      case GUI_STATE_IDLE:
        break;

      case GUI_STATE_SHOW_SETTINGS:
        lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]); /* show settings screen */
        state = GUI_STATE_IDLE;
        break;

    #if GUI_CONFIG_USE_CYCLING_SCREEN
      case GUI_STATE_START_CYCLING_SCREEN:
        currScreen = GUI_SCREEN_FIRST_CYCLING;
      #if GUI_CONFIG_USE_SCREENSAVER
        turnDisplayOffTimeout = GUI_CONFIG_NOF_SCREEN_CYCLING_UNTIL_DISPLAY_OFF;
      #endif
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
    #endif

    #if GUI_CONFIG_USE_SCREENSAVER
     case GUI_STATE_ENTER_SCREEN_SAVER:
        McuSSD1306_DisplayOn(false); /* turn off */
        /* stop all timers */
        if (xTimerStop(timerHndlGuiExpired, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed stopping timer");
          for(;;); /* failure!?! */
        }
    #if GUI_CONFIG_USE_CYCLING_SCREEN
        if (xTimerStop(timerHndlCycleScreens, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed stopping timer");
          for(;;); /* failure!?! */
        }
    #endif
        state = GUI_STATE_ACTIVE_SCREEN_SAVER;
        break;

      case GUI_STATE_ACTIVE_SCREEN_SAVER:
        break;

      case GUI_STATE_EXIT_SCREEN_SAVER:
        McuSSD1306_DisplayOn(true); /* turn display on */
        state = GUI_STATE_SHOW_SETTINGS;
        break;
    #endif
      default:
        break;
    } /* switch */
    LV_Task(); /* call this every 1-20 ms */
    vTaskDelay(pdMS_TO_TICKS(20));
  #if PL_CONFIG_USE_WATCHDOG
    McuWatchdog_ReportTimeEnd(McuWatchdog_REPORT_ID_TASK_GUI, xLastWakeTime);
  #endif
  }
}

#if GUI_CONFIG_USE_SCREENSAVER
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
#endif

void GUI_Suspend(void) {
  vTaskSuspend(GUI_TaskHndl);
  McuSSD1306_DisplayOn(false); /* turn off display */
}

void GUI_Resume(void) {
  McuSSD1306_Init();
  vTaskResume(GUI_TaskHndl);
}

void GUI_SendEvent(Gui_Event_e event) {
  switch(event) {
#if PL_CONFIG_IS_APP_VHS
    case Gui_Event_Battery_Charge_Changed:
      if (guiObjects.label_battery!=NULL) {
        lv_event_send(guiObjects.label_battery, LV_EVENT_VALUE_CHANGED, NULL);
      }
      if (guiObjects.bar_battery!=NULL) {
        lv_bar_set_value(guiObjects.bar_battery, Power_GetBatteryChargeLevel(), LV_ANIM_ON);
      }
      break;
    case Gui_Event_USB_Connection_Changed:
      if (guiObjects.button_power!=NULL) {
        lv_event_send(guiObjects.button_power, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
#endif
#if PL_CONFIG_IS_APP_VHS
    case Gui_Event_HomePower_Changed:
      if (guiObjects.bar_home!=NULL) {
        lv_bar_set_value(guiObjects.bar_home, Energy_GetHousePowerW(), LV_ANIM_ON);
      }
      break;
    case Gui_Event_CarPower_Changed:
      if (guiObjects.bar_car!=NULL) {
        lv_bar_set_value(guiObjects.bar_car, Energy_GetCarPowerW(), LV_ANIM_ON);
      }
      break;
#endif
#if PL_CONFIG_IS_APP_VHS
    case Gui_Event_LightOnOff_Changed:
      if (guiObjects.switch_light!=NULL) {
        if (Lights_GetLightIsOn()) {
          lv_obj_add_state(guiObjects.switch_light, LV_STATE_CHECKED);
        } else {
          lv_obj_clear_state(guiObjects.switch_light, LV_STATE_CHECKED);
        }
        lv_event_send(guiObjects.switch_light, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
#endif
#if PL_CONFIG_IS_APP_VHS
    case Gui_Event_LightColor_Changed:
      int32_t r, g, b;
      if (Lights_GetLightIsOn()) {
        uint32_t color = Lights_GetColor();
        r = McuUtility_map(NEO_SPLIT_R(color), 0, 0xff, 0, 100);
        g = McuUtility_map(NEO_SPLIT_G(color), 0, 0xff, 0, 100);
        b = McuUtility_map(NEO_SPLIT_B(color), 0, 0xff, 0, 100);
      } else {
        r = g = b = 0;
      }
      if (guiObjects.slider_color_red!=NULL) {
        lv_slider_set_value(guiObjects.slider_color_red, r, LV_ANIM_ON);
        lv_event_send(guiObjects.slider_color_red, LV_EVENT_VALUE_CHANGED, NULL);
      }
      if (guiObjects.slider_color_green!=NULL) {
        lv_slider_set_value(guiObjects.slider_color_green, g, LV_ANIM_ON);
        lv_event_send(guiObjects.slider_color_green, LV_EVENT_VALUE_CHANGED, NULL);
      }
      if (guiObjects.slider_color_blue!=NULL) {
        lv_slider_set_value(guiObjects.slider_color_blue, b, LV_ANIM_ON);
        lv_event_send(guiObjects.slider_color_blue, LV_EVENT_VALUE_CHANGED, NULL);
      }
     	break;
#endif

#if PL_CONFIG_IS_APP_VHS
    case Gui_Event_LightBrightness_Changed:
      if (guiObjects.slider_light_brightness!=NULL) {
        lv_slider_set_value(guiObjects.slider_light_brightness, Lights_GetLightIsOn()?Lights_GetBrightnessPercent():0, LV_ANIM_ON);
        lv_event_send(guiObjects.slider_light_brightness, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
#endif

#if PL_CONFIG_IS_APP_VHS
    case Gui_Event_Clock_Changed:
      if (guiObjects.label_clock!=NULL) {
        lv_event_send(guiObjects.label_clock, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
#endif

#if GUI_CONFIG_USE_SENSOR
    case Gui_Event_Sensor_Changed:
      if (guiObjects.label_sensor!=NULL) {
        lv_event_send(guiObjects.label_sensor, LV_EVENT_VALUE_CHANGED, NULL);
      }
      break;
#endif

#if PL_CONFIG_IS_APP_VHS
    case Gui_Event_Road_Changed:
       /* \todo */
      break;
#endif

    default:
      break;
  }
}

void GUI_NotifyUserAction(void) {
  /* called for each key press or user action. */
#if GUI_CONFIG_USE_SCREENSAVER
  StartOrResetGuiTimeoutTimer();
#endif
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_BUTTON_PRESSED, eSetBits);
}

#if GUI_CONFIG_USE_SCREENSAVER
static void vTimerCallbackGuiExpired(TimerHandle_t pxTimer) {
  (void)pxTimer; /* not used */
  /* start cycling screen timer */
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_GUI_TIMEOUT, eSetBits);
}
#endif

#if GUI_CONFIG_USE_CYCLING_SCREEN
static void vTimerCallbackCycleScreen(TimerHandle_t pxTimer) {
  (void)pxTimer; /* not used */
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_NEXT_SCREEN, eSetBits);
}
#endif

void GUI_Init(void) {
  LV_Init(); /* initialize GUI library */
  if (xTaskCreate(GuiTask, "Gui", 3*1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
    for(;;){} /* error */
  }

#if GUI_CONFIG_USE_SCREENSAVER
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
#endif

#if GUI_CONFIG_USE_CYCLING_SCREEN
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
#endif
}
#endif /* PL_CONFIG_HAS_GUI */
