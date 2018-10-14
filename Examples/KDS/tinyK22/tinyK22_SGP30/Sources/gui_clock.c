/*
 * gui_clock.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTC_DS3231 && PL_CONFIG_HAS_GUI
#include "gui_clock.h"
#include "lvgl/lvgl.h"
#include "TmDt1.h"
#include "XF1.h"
#include "gui.h"

static lv_obj_t *win;
static lv_obj_t *clock_label_time, *clock_label_date;
static lv_task_t *refr_task;
#define REFR_TIME_MS   (200)

/**
 * Called when the window's close button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t win_close_action(lv_obj_t *btn) {
  lv_group_focus_freeze(GUI_GetGroup(), false);
  lv_obj_del(win);
  win = NULL;
  lv_task_del(refr_task);
  refr_task = NULL;
  return LV_RES_INV;
}

/**
 * Called periodically to monitor the LED.
 * @param param unused
 */
static void refresh_task(void *param) {
  unsigned char buf[32];
  TIMEREC time;
  DATEREC date;

  if (TmDt1_GetTimeDate(&time, &date)==ERR_OK) {
    XF1_xsnprintf((char*)buf, sizeof(buf), (char*)"%02d:%02d:%02d", time.Hour, time.Min, time.Sec);
    lv_label_set_text(clock_label_time, (char*)buf);
    XF1_xsnprintf((char*)buf, sizeof(buf), (char*)"%02d.%02d.%04d", date.Day, date.Month, date.Year);
    lv_label_set_text(clock_label_date, (char*)buf);
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"failed!");
    lv_label_set_text(clock_label_time, (char*)buf);
    lv_label_set_text(clock_label_date, (char*)buf);
  }
}

void GUI_CLOCK_Create(void) {
    lv_obj_t *closeBtn;
    refr_task = lv_task_create(refresh_task, REFR_TIME_MS, LV_TASK_PRIO_LOW, NULL);

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Clock");
    closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);
    GUI_AddObjToGroup(closeBtn);
    lv_group_focus_obj(closeBtn);
    lv_group_focus_freeze(GUI_GetGroup(), true); /* otherwise the items of the underlying view are still active */
    /* Make the window content responsive */
   // lv_win_set_layout(win, LV_LAYOUT_PRETTY);

    /* label for values: */
    clock_label_time = lv_label_create(win, NULL);

    static lv_style_t style_txt;
    lv_style_copy(&style_txt, &lv_style_plain);
    style_txt.text.font = &lv_font_dejavu_20;
    lv_obj_set_style(clock_label_time, &style_txt);

    lv_label_set_text(clock_label_time, "12:15:01");
    lv_obj_align(clock_label_time, win, LV_ALIGN_CENTER, 0, 0);

    clock_label_date = lv_label_create(win, NULL);
    lv_label_set_text(clock_label_date, "15.10.2018");
    lv_obj_set_style(clock_label_date, &style_txt);
    lv_obj_align(clock_label_date, clock_label_time, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI/5);

    /* Refresh the chart and label manually at first */
    refresh_task(NULL);
}
#endif /* PL_CONFIG_HAS_RTC_DS3231 */
