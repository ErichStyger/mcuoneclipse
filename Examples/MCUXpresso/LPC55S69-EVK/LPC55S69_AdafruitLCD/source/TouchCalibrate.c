/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "TouchCalibrate.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "gui.h"
#include "toaster.h"

static lv_obj_t *win;

/**
 * Called when the window's close button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static void closeWindowCallback(lv_obj_t *obj, lv_event_t event) {
  if (event==LV_EVENT_CLICKED) {
  #if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_GroupPull();
  #endif
    lv_win_close_event_cb(obj, event);
    lv_obj_del(win);
    win = NULL;
  }
}

void TouchCalib_CreateView(void) {
  lv_obj_t *closeBtn;

  win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(win, "Touch Calibration");
  closeBtn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
  GUI_AddObjToGroup(closeBtn);
#endif
  lv_group_focus_obj(closeBtn);
  lv_obj_set_event_cb(closeBtn, closeWindowCallback);

  /* Make the window content responsive */
  lv_win_set_layout(win, LV_LAYOUT_PRETTY);

  lv_obj_t * txt = lv_label_create(win, NULL);
  lv_label_set_text(txt, "Touch the markers\n\nto calibrate the touch screen!");
}
