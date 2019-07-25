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
#include "McuUtility.h"
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

static lv_point_t rawPoints[4];
static bool isCalibrated = false;

bool TouchCalib_IsCalibrated(void) {
  return isCalibrated;
}

void TouchCalib_set_cal_data(lv_point_t points[4]) {
  memcpy(rawPoints, points, sizeof(rawPoints)); /* store data */
  isCalibrated = true;
}

void TouchCalib_Calibrate(uint16_t *x, uint16_t *y) {
  #define LCD_HEIGHT 320
  #define LCD_WIDTH  240
  if (isCalibrated) {
    int x1_saved = (rawPoints[0].x+rawPoints[3].x)/2;
    int x2_saved = (rawPoints[1].x+rawPoints[2].x)/2;
    int y1_saved = (rawPoints[0].y+rawPoints[1].y)/2;
    int y2_saved = (rawPoints[2].y+rawPoints[2].y)/3;

    *x = ((*x - x1_saved) * LCD_WIDTH) / (x2_saved - x1_saved);
    *y = ((*y - y1_saved) * LCD_HEIGHT) / (y2_saved - y1_saved);
  } else {
    int ix, iy;

    /* the STMPE610 delivers x and y in the range of 0...4096, and z is the pressure (the harder the press, the lower the number */
    #define TS_MINX 300
    #define TS_MAXX 3800
    #define TS_MINY 210
    #define TS_MAXY 3700

    ix = *x;
    iy = *y;
    ix = McuUtility_map(ix, TS_MINX, TS_MAXX, 0, LCD_WIDTH);
    iy = McuUtility_map(iy, TS_MINY, TS_MAXY, 0, LCD_HEIGHT);
    if (ix < 0) {
      ix = 0;
    } else if (ix > LCD_WIDTH-1) {
      ix = LCD_WIDTH-1;
    }
    if (iy < 0) {
      iy = 0;
    } else if (iy > LCD_HEIGHT-1) {
      iy = LCD_HEIGHT-1;
    }
    *x = ix;
    *y = iy;
  }
}
