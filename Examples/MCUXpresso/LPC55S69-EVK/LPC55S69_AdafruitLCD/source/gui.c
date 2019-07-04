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
#include "McuRTOS.h"
#include "leds.h"
#include "McuLED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "McuILI9341.h"
#include "McuFontDisplay.h"

static TaskHandle_t GUI_TaskHndl;

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

static lv_res_t btn_click_sensor_action(struct _lv_obj_t *obj) {
  //GUI_TEMPHUM_CreateView();
  return LV_RES_OK;
}

void GUI_MainMenuCreate(void) {
  lv_obj_t *gui_win;
#define AUTO_POS (1) /* automatically place GUI elements */

#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
#endif
  /* create window */
  gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");
  //int size = lv_win_get_btn_size(gui_win);
  //lv_win_set_btn_size(gui_win, 8);
  lv_win_set_sb_mode(gui_win, LV_SB_MODE_OFF); /* no scroll bar */

  /* Make the window content responsive */
#if AUTO_POS
  lv_win_set_layout(gui_win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */
#endif
  lv_obj_t *btn;
  lv_obj_t *label;

#if 1
  btn = lv_btn_create(gui_win, NULL);
#if !AUTO_POS
  lv_obj_set_size(btn, 45, 20);
  lv_obj_set_pos(btn, 5, 0);
#endif
  label = lv_label_create(btn, NULL);
  lv_label_set_text(label, "Sensor");
  lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_click_sensor_action);
  lv_btn_set_fit(btn, true, true); /* set auto fit to text */
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif
#endif /* PL_CONFIG_USE_SHUTDOWN */
}

static void ErrMsg(void) {
  for(;;) { /* error */
    McuLED_Neg(LED_Red);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void GuiTask(void *p) {
  uint32_t notifcationValue;

  vTaskDelay(pdMS_TO_TICKS(500)); /* give hardware time to power up */
  if (McuILI9341_InitLCD()!=ERR_OK) {
    ErrMsg();
  }
  McuILI9341_ClearDisplay(MCUILI9341_GREEN);
//  McuILI9341_ClearDisplay(MCUILI9341_BLUE);
  GUI_MainMenuCreate();
  for(;;) {
#if 0
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

  if (xTaskCreate(GuiTask, "Gui", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
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
