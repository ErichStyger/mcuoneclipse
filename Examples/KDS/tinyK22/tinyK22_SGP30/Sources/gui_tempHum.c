/*
 * gui_tempHum.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_SHT31 && PL_CONFIG_HAS_GUI
#include "gui_tempHum.h"
#include "lvgl/lvgl.h"
#include "Sensor.h"
#include "XF1.h"
#include "gui.h"

static lv_obj_t *win;
static lv_obj_t *chart_label;
static lv_obj_t *chart;
static lv_chart_series_t *temperature_ser, *humidity_ser;
#define CHART_MAX_VALUE   100
#define CHART_POINT_NUM     100
#define TEMPERATURE_LABEL_COLOR   "FF0000"
#define HUMIDITY_LABEL_COLOR      "00FF00"
static lv_task_t *refr_task;
#define REFR_TIME_MS   (500)

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
  unsigned char buf[48];
  float temperature, humidity;
  int16_t chart_tvalue;
  int16_t chart_hvalue;

  temperature = SENSOR_GetTemperature();
  humidity = SENSOR_GetHumidity();
  chart_tvalue = temperature;
  if (chart_tvalue>CHART_MAX_VALUE) {
    chart_tvalue = CHART_MAX_VALUE;
	} else if (chart_tvalue<0) {
	  chart_tvalue = 0;
	}
  chart_hvalue = humidity;
  if (chart_hvalue>CHART_MAX_VALUE) {
    chart_hvalue = CHART_MAX_VALUE;
  } else if (chart_hvalue<0) {
    chart_hvalue = 0;
  }
  /*Add the data to the chart*/
  lv_chart_set_next(chart, temperature_ser, chart_tvalue);
  lv_chart_set_next(chart, humidity_ser, chart_hvalue);

  XF1_xsnprintf(buf, sizeof(buf), "%s%s T: %.1f°C%s\n%s%s RH: %.1f%%%s",
    LV_TXT_COLOR_CMD, TEMPERATURE_LABEL_COLOR, temperature, LV_TXT_COLOR_CMD,
    LV_TXT_COLOR_CMD, HUMIDITY_LABEL_COLOR,    humidity, LV_TXT_COLOR_CMD
    );
  lv_label_set_text(chart_label, buf);
}

void GUI_TEMPHUM_Create(void) {
    lv_obj_t *closeBtn;
    refr_task = lv_task_create(refresh_task, REFR_TIME_MS, LV_TASK_PRIO_LOW, NULL);

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Ambient (TSL2561)");
    closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);
    GUI_AddObjToGroup(closeBtn);
    lv_group_focus_obj(closeBtn);
    lv_group_focus_freeze(GUI_GetGroup(), true); /* otherwise the items of the underlying view are still active */
    /* Make the window content responsive */
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);

    /* Create a chart with two data lines */
    chart = lv_chart_create(win, NULL);
    lv_obj_set_size(chart, LV_HOR_RES, LV_VER_RES/2);

    lv_obj_set_pos(chart, LV_DPI / 10, LV_DPI / 10);

    lv_chart_set_point_count(chart, CHART_POINT_NUM);
    lv_chart_set_range(chart, 0, CHART_MAX_VALUE);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_series_width(chart, 3);
    temperature_ser =  lv_chart_add_series(chart, LV_COLOR_RED);
    humidity_ser =  lv_chart_add_series(chart, LV_COLOR_GREEN);

    /* Set the data series to zero */
    uint16_t i;
    for(i = 0; i < CHART_POINT_NUM; i++) {
        lv_chart_set_next(chart, temperature_ser, 0);
        lv_chart_set_next(chart, humidity_ser, 0);
    }
    /* label for values: */
    chart_label = lv_label_create(win, NULL);
    lv_label_set_recolor(chart_label, true);
    lv_obj_align(chart_label, chart, LV_ALIGN_OUT_RIGHT_TOP, LV_DPI/5, 0);

    /* Refresh the chart and label manually at first */
    refresh_task(NULL);
}
#endif /* PL_CONFIG_HAS_SGP30 */
