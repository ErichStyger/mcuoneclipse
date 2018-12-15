/*
 * gui_air.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_NEO_PIXEL && PL_CONFIG_HAS_GUI
#include "gui_neopixel.h"
#include "lvgl/lvgl.h"
#include "gui.h"
#include "../WS2812B/Neoapp.h"

static lv_obj_t *win; /* object for window */

#define SLIDER_LEVEL_MIN_RANGE    0
#define SLIDER_LEVEL_MAX_RANGE  100
#define SLIDER_LEVEL_LIGHT_MIN    0
#define SLIDER_LEVEL_LIGHT_MAX  255
static lv_obj_t *label_auto_light_level; /* label for auto mode */
static lv_obj_t *label_slider_level; /* label for level value */

static void SetLabelValue(lv_obj_t *label, int32_t val) {
  uint8_t buf[16];

  if (label!=NULL) {
    UTIL1_Num32sToStr(buf, sizeof(buf), val);
    lv_label_set_text(label, buf);
  }
}

/* Called when a new value id set on the slider */
static lv_res_t slider_action(lv_obj_t *slider) {
  int val;

  val = lv_slider_get_value(slider); /* get current value from slider */
  /* map to target range: */
  val = UTIL1_map(val, SLIDER_LEVEL_MIN_RANGE, SLIDER_LEVEL_MAX_RANGE, SLIDER_LEVEL_LIGHT_MIN, SLIDER_LEVEL_LIGHT_MAX);
  NEOA_SetLightLevel(val); /* update model */
  SetLabelValue(label_slider_level, val);
  return LV_RES_OK;
}

static lv_res_t auto_light_level_action(lv_obj_t *sw) {
  bool isOn = lv_sw_get_state(sw);

  NEOA_SetAutoLightLevelSetting(isOn); /* update model */
  if (isOn) {
    lv_label_set_text(label_auto_light_level, "on");
  } else {
    lv_label_set_text(label_auto_light_level, "off");
  }
  return LV_RES_OK;
}

/**
 * Called when the window's close button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t win_close_action(lv_obj_t *btn) {
  GUI_GroupPull();
  lv_obj_del(win);
  win = NULL;
  return LV_RES_INV;
}

static lv_res_t btn_play_click_action(lv_obj_t *btn) {
  return LV_RES_OK; /* Return OK if the button is not deleted */
}

static lv_res_t btn_pause_click_action(lv_obj_t *btn) {
  return LV_RES_OK; /* Return OK if the button is not deleted */
}

static lv_res_t btn_stop_click_action(lv_obj_t *btn) {
  return LV_RES_OK; /* Return OK if the button is not deleted */
}

static lv_res_t btn_prev_click_action(lv_obj_t *btn) {
  return LV_RES_OK; /* Return OK if the button is not deleted */
}

static lv_res_t btn_next_click_action(lv_obj_t *btn) {
  return LV_RES_OK; /* Return OK if the button is not deleted */
}

static lv_res_t btn_loop_click_action(lv_obj_t *btn) {
  return LV_RES_OK; /* Return OK if the button is not deleted */
}

void GUI_NEO_Create(void) {
  lv_obj_t *closeBtn, *slider1;

  /* Create the window */
  win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(win, "NeoPixel");
  closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);
  GUI_GroupPush();
  GUI_AddObjToGroup(closeBtn);
  lv_group_focus_obj(closeBtn);
  /* Make the window content responsive */
//   lv_win_set_layout(win, LV_LAYOUT_PRETTY);

  /*-------------------------------------------------------*/
  /* Switch to turn on/off the auto light level */
  /*-------------------------------------------------------*/
  /* Create a label left to the light 'auto' switch */
  lv_obj_t *switch1_label = lv_label_create(win, NULL);
  lv_label_set_text(switch1_label, "Auto");
  lv_obj_align(switch1_label, win, LV_ALIGN_IN_BOTTOM_LEFT, 5, 10);

  /* create a switch for the auto light level setting */
  lv_obj_t *sw1 = lv_sw_create(win, NULL);
  GUI_AddObjToGroup(sw1);
  if (NEOA_GetAutoLightLevelSetting()) {
    lv_sw_on(sw1); /* turn on */
  } else {
    lv_sw_off(sw1); /* turn on */
  }
  lv_sw_set_action(sw1, auto_light_level_action); /* register callback */
  lv_obj_align(sw1, switch1_label, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

  /* label for the switch status, on the right side of the switch  */
  label_auto_light_level = lv_label_create(win, NULL);
  if (lv_sw_get_state(sw1)) {
    lv_label_set_text(label_auto_light_level, "on");
  } else {
    lv_label_set_text(label_auto_light_level, "off");
  }
  lv_obj_align(label_auto_light_level, sw1, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

  /*-------------------------------------------------------*/
  /* Slider to adjust the light level */
  /*-------------------------------------------------------*/
  /* Create a label left to the light level slider */
  lv_obj_t *slider1_label = lv_label_create(win, NULL);
  lv_label_set_text(slider1_label, "Level");
  lv_obj_align(slider1_label, switch1_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 6);

  /* Create a slider for the light level */
  slider1 = lv_slider_create(win, NULL);
  GUI_AddObjToGroup(slider1);
  lv_obj_set_size(slider1, 50, 15);
  lv_slider_set_range(slider1, SLIDER_LEVEL_MIN_RANGE, SLIDER_LEVEL_MAX_RANGE);
  lv_obj_align(slider1, slider1_label, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
  lv_slider_set_action(slider1, slider_action);
  lv_bar_set_value(slider1, UTIL1_map(NEOA_GetLightLevel(), SLIDER_LEVEL_LIGHT_MIN, SLIDER_LEVEL_LIGHT_MAX, SLIDER_LEVEL_MIN_RANGE, SLIDER_LEVEL_MAX_RANGE));

  /* Create a label with the slider value right to the slider */
  label_slider_level = lv_label_create(win, NULL);
  SetLabelValue(label_slider_level, NEOA_GetLightLevel());
  lv_obj_align(label_slider_level, slider1, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

  /*Create a bar, an indicator and a knob style*/
  static lv_style_t style_bg;
  static lv_style_t style_indic;
  static lv_style_t style_knob;

  lv_style_copy(&style_bg, &lv_style_pretty);
  style_bg.body.main_color =  LV_COLOR_BLACK;
  style_bg.body.grad_color =  LV_COLOR_GRAY;
  style_bg.body.radius = LV_RADIUS_CIRCLE;
  style_bg.body.border.color = LV_COLOR_WHITE;

  lv_style_copy(&style_indic, &lv_style_pretty);
  style_indic.body.grad_color =  LV_COLOR_GREEN;
  style_indic.body.main_color =  LV_COLOR_LIME;
  style_indic.body.radius = LV_RADIUS_CIRCLE;
  style_indic.body.shadow.width = 10;
  style_indic.body.shadow.color = LV_COLOR_LIME;
  style_indic.body.padding.hor = 3;
  style_indic.body.padding.ver = 3;

  lv_style_copy(&style_knob, &lv_style_pretty);
  style_knob.body.radius = LV_RADIUS_CIRCLE;
  style_knob.body.opa = LV_OPA_70;
  style_knob.body.padding.ver = 10;

  /*-------------------------------------------------------*/
  /* buttons for play, pause, stop, ... */
  /*-------------------------------------------------------*/
  lv_obj_t *label;
  lv_obj_t *btn_play, *btn_pause, *btn_stop, *btn_next, *btn_prev, *btn_loop;

  /* play buttons */
  btn_play = lv_btn_create(win, NULL);
  lv_obj_align(btn_play, slider1_label, LV_ALIGN_OUT_BOTTOM_LEFT, 12, 6);
  lv_btn_set_action(btn_play, LV_BTN_ACTION_CLICK, btn_play_click_action);
  label = lv_label_create(btn_play, NULL);
  lv_label_set_text(label, SYMBOL_PLAY);
  GUI_AddObjToGroup(btn_play);
  /* pause button */
  btn_pause = lv_btn_create(win, NULL);
  lv_obj_align(btn_pause, btn_play, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
  lv_btn_set_action(btn_pause, LV_BTN_ACTION_CLICK, btn_pause_click_action);
  label = lv_label_create(btn_pause, NULL);
  lv_label_set_text(label, SYMBOL_PAUSE);
  GUI_AddObjToGroup(btn_pause);
  /* stop button */
  btn_stop = lv_btn_create(win, NULL);
  lv_obj_align(btn_stop, btn_pause, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
  lv_btn_set_action(btn_stop, LV_BTN_ACTION_CLICK, btn_stop_click_action);
  label = lv_label_create(btn_stop, NULL);
  lv_label_set_text(label, SYMBOL_STOP);
  GUI_AddObjToGroup(btn_stop);
  /* previous button */
  btn_prev = lv_btn_create(win, NULL);
  lv_obj_align(btn_prev, btn_play, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_btn_set_action(btn_prev, LV_BTN_ACTION_CLICK, btn_prev_click_action);
  label = lv_label_create(btn_prev, NULL);
  lv_label_set_text(label, SYMBOL_PREV);
  GUI_AddObjToGroup(btn_prev);
  /* next button */
  btn_next = lv_btn_create(win, NULL);
  lv_obj_align(btn_next, btn_prev, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
  lv_btn_set_action(btn_next, LV_BTN_ACTION_CLICK, btn_next_click_action);
  label = lv_label_create(btn_next, NULL);
  lv_label_set_text(label, SYMBOL_NEXT);
  GUI_AddObjToGroup(btn_next);
  /* loop button */
  btn_loop = lv_btn_create(win, NULL);
  lv_obj_align(btn_loop, btn_next, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
  lv_btn_set_action(btn_loop, LV_BTN_ACTION_CLICK, btn_loop_click_action);
  label = lv_label_create(btn_loop, NULL);
  lv_label_set_text(label, SYMBOL_LOOP);
  GUI_AddObjToGroup(btn_loop);
}
#endif /* PL_CONFIG_HAS_NEO_PIXEL */
