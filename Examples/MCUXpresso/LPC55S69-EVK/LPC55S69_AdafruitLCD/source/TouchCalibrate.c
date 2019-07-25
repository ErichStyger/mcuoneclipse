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
static struct {
  bool isCalibrated;
  lv_point_t point[4];
} cal_data =
  {
    .isCalibrated = true,
    .point[0] = {.x=705,  .y=549},
    .point[1] = {.x=3394, .y=527},
    .point[2] = {.x=3395, .y=3466},
    .point[3] = {.x=1587, .y=3433},
  };

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

bool TouchCalib_IsCalibrated(void) {
  return cal_data.isCalibrated;
}

void TouchCalib_SetCalibrated(bool isCalibrated) {
  cal_data.isCalibrated = isCalibrated;
}

void TouchCalib_set_cal_data(lv_point_t points[4]) {
  memcpy(cal_data.point, points, sizeof(cal_data.point)); /* store data */
  cal_data.isCalibrated = true;
}

static int32_t int_ext(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x)  {
  return y2 - (x2-x) / ((x2 - x1) / (y2 - y1));
}

void TouchCalib_Calibrate(uint16_t *x, uint16_t *y) {
  if (cal_data.isCalibrated) {
    /* see https://github.com/littlevgl/esp32_ili9341/issues/12 */
    #define LCD_HOR_RES     240
    #define LCD_VER_RES     320
    #define CIRCLE_SIZE      20
    #define CIRCLE_OFFSET    20

    int xval, yval;

    xval = int_ext(cal_data.point[0].x, CIRCLE_OFFSET + CIRCLE_SIZE/2, cal_data.point[1].x, LCD_HOR_RES - CIRCLE_OFFSET + CIRCLE_SIZE/2, *x);
    yval = int_ext(cal_data.point[1].y, CIRCLE_OFFSET + CIRCLE_SIZE/2, cal_data.point[2].y, LCD_VER_RES - CIRCLE_OFFSET + CIRCLE_SIZE/2, *y);
    if (xval<0) {
      xval = 0;
    }
    if (xval>LCD_HOR_RES-1) {
      xval = LCD_HOR_RES-1;
    }
    if (yval<0) {
      yval = 0;
    }
    if (yval>LCD_VER_RES-1) {
      yval = LCD_VER_RES-1;
    }
    *x = xval;
    *y = yval;
  } else {
#if 0
    int ix, iy;

    /* the STMPE610 delivers x and y in the range of 0...4096, and z is the pressure (the harder the press, the lower the number */
    #define TS_MINX 300
    #define TS_MAXX 3800
    #define TS_MINY 210
    #define TS_MAXY 3700

    ix = *x;
    iy = *y;
    ix = McuUtility_map(ix, TS_MINX, TS_MAXX, 0, LCD_HOR_RES);
    iy = McuUtility_map(iy, TS_MINY, TS_MAXY, 0, LCD_VER_RES);
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
#endif
  }
}
