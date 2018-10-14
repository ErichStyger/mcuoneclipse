/*
 * gui_air.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_SGP30 && PL_CONFIG_HAS_GUI
#include "gui_air.h"
#include "lvgl/lvgl.h"
#include "SGP30.h"
#include "XF1.h"
#include "gui.h"

static lv_obj_t *win;
static lv_obj_t *air_label;
static lv_obj_t *air_chart;
static lv_chart_series_t *voc_ser, *co2_ser;
#define AIR_CHART_MAX_VALUE   16000
#define CHART_POINT_NUM     100
#define VOC_LABEL_COLOR  "FF0000"
#define CO2_LABEL_COLOR  "00FF00"
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
	uint16_t voc, co2; /* sensor values */
	int16_t c_voc, c_co2; /* chart values */
  char buf[64];

	if (SGP30_IAQmeasure(&voc, &co2)!=ERR_OK) {
	  voc = co2 = 0; /* error case */
	}
	c_co2 = co2/3; /* scale into chart range */
	c_voc = voc;
	if (c_voc>AIR_CHART_MAX_VALUE) {
	  c_voc = AIR_CHART_MAX_VALUE;
	}
	if (c_co2>AIR_CHART_MAX_VALUE) {
	  c_co2 = AIR_CHART_MAX_VALUE;
	}
  /*Add the CPU and memory data to the chart*/
  lv_chart_set_next(air_chart, voc_ser, c_voc);
  lv_chart_set_next(air_chart, co2_ser, c_co2);

  XF1_xsnprintf(buf, sizeof(buf), "%s%s VOC: %6d%s\n%s%s CO2: %6d%s",
    LV_TXT_COLOR_CMD, VOC_LABEL_COLOR, voc, LV_TXT_COLOR_CMD,
    LV_TXT_COLOR_CMD, CO2_LABEL_COLOR, co2, LV_TXT_COLOR_CMD);
  lv_label_set_text(air_label, buf);
}

void GUI_AIR_Create(void) {
    lv_obj_t *closeBtn;
    refr_task = lv_task_create(refresh_task, REFR_TIME_MS, LV_TASK_PRIO_LOW, NULL);

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Air (SGP30)");
    closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);
    GUI_AddObjToGroup(closeBtn);
    lv_group_focus_obj(closeBtn);
    lv_group_focus_freeze(GUI_GetGroup(), true); /* otherwise the items of the underlying view are still active */
    /* Make the window content responsive */
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);

    /* Create a chart with two data lines */
    air_chart = lv_chart_create(win, NULL);
    lv_obj_set_size(air_chart, LV_HOR_RES, LV_VER_RES/2);

    lv_obj_set_pos(air_chart, LV_DPI / 10, LV_DPI / 10);

    lv_chart_set_point_count(air_chart, CHART_POINT_NUM);
    lv_chart_set_range(air_chart, 0, AIR_CHART_MAX_VALUE);
    lv_chart_set_type(air_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_series_width(air_chart, 2);
    voc_ser =  lv_chart_add_series(air_chart, LV_COLOR_RED);
    co2_ser =  lv_chart_add_series(air_chart, LV_COLOR_GREEN);

    /* Set the data series to zero */
    uint16_t i;
    for(i = 0; i < CHART_POINT_NUM; i++) {
        lv_chart_set_next(air_chart, voc_ser, 0);
        lv_chart_set_next(air_chart, co2_ser, 0);
    }
    /* label for values: */
    air_label = lv_label_create(win, NULL);
    lv_label_set_recolor(air_label, true);
    lv_obj_align(air_label, air_chart, LV_ALIGN_OUT_RIGHT_TOP, LV_DPI/5, 0);

    /* Refresh the chart and label manually at first */
    refresh_task(NULL);
}
#endif /* PL_CONFIG_HAS_SGP30 */
