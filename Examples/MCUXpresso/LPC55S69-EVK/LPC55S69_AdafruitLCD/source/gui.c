/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_GUI

#include "gui.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "LittlevGL/lvgl/src/lv_objx/lv_btn.h"
#include "McuRTOS.h"
#include "leds.h"
#include "McuLED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "McuILI9341.h"
#include "McuFontDisplay.h"
#include "Shell.h"
#if PL_CONFIG_USE_STMPE610
  #include "McuSTMPE610.h"
  #include "TouchCalibrate.h"
  #include "tpcal.h"
#endif
#include "sysmon.h"
#include "demo/demo.h"

static TaskHandle_t GUI_TaskHndl;
static lv_obj_t *main_screen;

#if 0
/* task notification bits */
#define GUI_SET_ORIENTATION_LANDSCAPE    (1<<0)
#define GUI_SET_ORIENTATION_LANDSCAPE180 (1<<1)
#define GUI_SET_ORIENTATION_PORTRAIT     (1<<2)
#define GUI_SET_ORIENTATION_PORTRAIT180  (1<<3)
#endif

#if PL_CONFIG_USE_GUI_KEY_NAV
#define GUI_GROUP_NOF_IN_STACK   4
typedef struct {
  lv_group_t *stack[GUI_GROUP_NOF_IN_STACK]; /* stack of GUI groups */
  uint8_t sp; /* stack pointer, points to next free element */
} GUI_Group_t;
static GUI_Group_t groups;

/* style modification callback for the focus of an element */
static void style_mod_cb(lv_style_t *style) {
#if LV_COLOR_DEPTH != 1
    /*Make the style to be a little bit orange*/
    style->body.border.opa = LV_OPA_COVER;
    style->body.border.color = LV_COLOR_ORANGE;

    /*If not empty or has border then emphasis the border*/
    if(style->body.empty == 0 || style->body.border.width != 0) style->body.border.width = LV_DPI / 50;

    style->body.main_color = lv_color_mix(style->body.main_color, LV_COLOR_ORANGE, LV_OPA_70);
    style->body.grad_color = lv_color_mix(style->body.grad_color, LV_COLOR_ORANGE, LV_OPA_70);
    style->body.shadow.color = lv_color_mix(style->body.shadow.color, LV_COLOR_ORANGE, LV_OPA_60);

    style->text.color = lv_color_mix(style->text.color, LV_COLOR_ORANGE, LV_OPA_70);
#else
    style->body.border.opa = LV_OPA_COVER;
    style->body.border.color = LV_COLOR_BLACK;
    style->body.border.width = 3;
#endif
}

void GUI_AddObjToGroup(lv_obj_t *obj) {
  lv_group_add_obj(GUI_GroupPeek(), obj);
}

void GUI_RemoveObjFromGroup_(lv_obj_t *obj) {
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
  lv_group_set_style_mod_cb(gui_group, style_mod_cb);
  groups.stack[groups.sp] = gui_group;
  groups.sp++;
}
#endif /* PL_CONFIG_USE_GUI_KEY_NAV */

#if 0
void GUI_ChangeOrientation(McuSSD1306_DisplayOrientation orientation) {
  switch(orientation) {
    case McuSSD1306_ORIENTATION_LANDSCAPE:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_LANDSCAPE, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_LANDSCAPE180:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_LANDSCAPE180, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_PORTRAIT:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_PORTRAIT, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_PORTRAIT180:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_PORTRAIT180, eSetBits);
      break;
    default:
      break;
  }
}
#endif

#if PL_CONFIG_USE_STMPE610
static void btn_touchcalibrate_event_handler(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    //TouchCalib_CreateView();
    TouchCalib_SetCalibrated(false);
    tpcal_create();
  } else if(event == LV_EVENT_VALUE_CHANGED) {
//      printf("Toggled\n");
  }
}
#endif

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    SHELL_SendString((unsigned char*)"Clicked\n");
  } else if(event == LV_EVENT_VALUE_CHANGED) {
    SHELL_SendString((unsigned char*)"Toggled\n");
  }
}

static void btn_click_SysMon_action(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    GUI_SysMon_Create();
  }
}

static void btn_click_Demo_action(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    GUI_Demo_Create();
  }
}

void GUI_SwitchToMainScreen(void) {
  lv_scr_load(main_screen); /* load the screen */
}

void GUI_MainMenuCreate(void) {
	lv_obj_t * label;

#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
#endif

  /* create main screen */
  main_screen = lv_obj_create(NULL, NULL);
  lv_scr_load(main_screen); /* load the screen */

  /* create window */
  lv_obj_t *gui_win;

  gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");

  /* Add control button to the header */
  lv_obj_t *close_btn = lv_win_add_btn(gui_win, LV_SYMBOL_CLOSE);           /* Add close button and use built-in close action */
  //lv_obj_set_event_cb(close_btn, lv_win_close_event_cb);
  lv_win_add_btn(gui_win, LV_SYMBOL_SETTINGS);        /*Add a setup button*/

  lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_event_cb(btn1, event_handler);
	lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -110);

	label = lv_label_create(btn1, NULL);
	lv_label_set_text(label, "Sensor");
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn1);
#endif

	lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_event_cb(btn2, event_handler);
	lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, -70);
	lv_btn_set_toggle(btn2, true);
	lv_btn_toggle(btn2);
	lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

	label = lv_label_create(btn2, NULL);
	lv_label_set_text(label, "LED");
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn2);
#endif

  lv_obj_t *btn;

  btn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_event_cb(btn, btn_click_SysMon_action);
  lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, -30);
  lv_btn_set_fit2(btn, LV_FIT_NONE, LV_FIT_TIGHT);

  label = lv_label_create(btn, NULL);
  lv_label_set_text(label, "SysMon");
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif

  btn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_event_cb(btn, btn_click_Demo_action);
  lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 10);
  lv_btn_set_fit2(btn, LV_FIT_NONE, LV_FIT_TIGHT);

  label = lv_label_create(btn, NULL);
  lv_label_set_text(label, "Demo");
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif
}


static void ErrMsg(void) {
  for(;;) { /* error */
    McuLED_Toggle(LED_Red);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void GuiTask(void *p) {
  vTaskDelay(pdMS_TO_TICKS(500)); /* give hardware time to power up */
  if (McuILI9341_InitLCD()!=ERR_OK) {
    ErrMsg();
  }
  //McuILI9341_ClearDisplay(MCUILI9341_GREEN); /* testing only to see a change on the screen */
#if PL_CONFIG_USE_STMPE610
  if (McuSTMPE610_InitController()!=ERR_OK) {
    ErrMsg();
  }
  if (!TouchCalib_IsCalibrated()) {
    tpcal_create();
  }
  while(!TouchCalib_IsCalibrated()) {
    LV_Task(); /* call this every 1-20 ms */
    vTaskDelay(pdMS_TO_TICKS(10));
  }
#endif
  GUI_MainMenuCreate();
  for(;;) {
#if 0
    uint32_t notifcationValue;

    (void)xTaskNotifyWait(0UL, GUI_SET_ORIENTATION_LANDSCAPE|GUI_SET_ORIENTATION_LANDSCAPE180|GUI_SET_ORIENTATION_PORTRAIT|GUI_SET_ORIENTATION_PORTRAIT180, &notifcationValue, 0); /* check flags */
    if (notifcationValue!=0) {
      lv_area_t area;

      if (notifcationValue&GUI_SET_ORIENTATION_LANDSCAPE) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
        lv_refr_now();
      } else if (notifcationValue&GUI_SET_ORIENTATION_LANDSCAPE180) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE180);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
      } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
      } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT180) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT180);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
        lv_obj_invalidate(lv_scr_act());
      }
    }
#endif
    LV_Task(); /* call this every 1-20 ms */
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

#define APP_PERIODIC_TIMER_PERIOD_MS   10
static TimerHandle_t timerHndl;

static void vTimerGuiTickCallbackExpired(TimerHandle_t pxTimer) {
  lv_tick_inc(APP_PERIODIC_TIMER_PERIOD_MS);
}

void GUI_Init(void) {
  LV_Init(); /* initialize GUI library */
  //lv_theme_set_current(lv_theme_night_init(128, NULL));
  //lv_theme_set_current(lv_theme_alien_init(128, NULL));
  //lv_theme_set_current(lv_theme_default_init(128, NULL));
  //lv_theme_set_current(lv_theme_material_init(128, NULL));
  //lv_theme_set_current(lv_theme_mono_init(128, NULL));
  //lv_theme_set_current(lv_theme_zen_init(128, NULL));
  //lv_theme_set_current(lv_theme_nemo_init(128, NULL));

  //lv_theme_t *th = lv_theme_get_current();
	/* change default button style */
  // lv_style_btn_rel.body.radius = LV_DPI / 15;
  // lv_style_btn_rel.body.padding.hor = LV_DPI / 8;
  // lv_style_btn_rel.body.padding.ver = LV_DPI / 12;

  if (xTaskCreate(GuiTask, "Gui", 4000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
    for(;;){} /* error */
  }
  timerHndl = xTimerCreate(  /* timer to handle periodic things */
        "guiTick", /* name */
        pdMS_TO_TICKS(APP_PERIODIC_TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerGuiTickCallbackExpired); /* callback */
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) { /* start the timer */
    for(;;); /* failure!?! */
  }
#if PL_CONFIG_USE_GUI_KEY_NAV
  groups.sp = 0;
#endif
}
#endif /* PL_CONFIG_HAS_GUI */
