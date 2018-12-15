/*
 * gui_ambient.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_TSL2561 && PL_CONFIG_HAS_GUI
#include "gui_ambient.h"
#include "lvgl/lvgl.h"
#include "TSL1.h"
#include "XF1.h"
#include "gui.h"

static lv_obj_t *win;
static lv_obj_t *chart_label;
static lv_obj_t *chart;
static lv_chart_series_t *ir_ser, *broadband_ser, *lux_ser;
#define CHART_MAX_VALUE   16000
#define CHART_POINT_NUM     100
#define IR_LABEL_COLOR          "FF0000"
#define BROADBAND_LABEL_COLOR   "00FF00"
#define LUX_LABEL_COLOR         "0000FF"
static lv_task_t *refr_task;
#define REFR_TIME_MS   (500)

/**
 * Called when the window's close button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t win_close_action(lv_obj_t *btn) {
  GUI_GroupPull();
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
  char buf[64];
  uint8_t ambient;
  uint16_t broadband, ir;
  uint32_t lux;

  if (TSL1_ReadRawDataFull(&broadband)!=ERR_OK) {
    broadband = 0; /* error */
  }
  if (TSL1_ReadRawDataInfrared(&ir)!=ERR_OK) {
    ir = 0; /* error */
  }
  lux = TSL1_CalculateLux(broadband, ir);
  TSL1_LuxToAmbientPercentage(lux, &ambient);
  TSL1_GetLuminosity(&broadband, &ir);

  if (broadband>CHART_MAX_VALUE) {
    broadband = CHART_MAX_VALUE;
	}
	if (ir>CHART_MAX_VALUE) {
	  ir = CHART_MAX_VALUE;
	}
  if (lux>CHART_MAX_VALUE) {
    lux = CHART_MAX_VALUE;
  }
  /*Add the data to the chart*/
  lv_chart_set_next(chart, ir_ser, ir);
  lv_chart_set_next(chart, broadband_ser, broadband);
  lv_chart_set_next(chart, lux_ser, lux);

  XF1_xsnprintf(buf, sizeof(buf), "%s%s IR: %6d%s\n%s%s BB: %6d%s\n%s%s Lux: %6ld%s",
    LV_TXT_COLOR_CMD, IR_LABEL_COLOR,        ir, LV_TXT_COLOR_CMD,
    LV_TXT_COLOR_CMD, BROADBAND_LABEL_COLOR, broadband, LV_TXT_COLOR_CMD,
    LV_TXT_COLOR_CMD, LUX_LABEL_COLOR,       lux, LV_TXT_COLOR_CMD
    );
  lv_label_set_text(chart_label, buf);
}

void GUI_AMBIENT_Create(void) {
    lv_obj_t *closeBtn;
    refr_task = lv_task_create(refresh_task, REFR_TIME_MS, LV_TASK_PRIO_LOW, NULL);

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Ambient (TSL2561)");
    closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);
    GUI_GroupPush();
    GUI_AddObjToGroup(closeBtn);
    lv_group_focus_obj(closeBtn);

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
    ir_ser =  lv_chart_add_series(chart, LV_COLOR_RED);
    broadband_ser =  lv_chart_add_series(chart, LV_COLOR_GREEN);
    lux_ser =  lv_chart_add_series(chart, LV_COLOR_BLUE);

    /* Set the data series to zero */
    uint16_t i;
    for(i = 0; i < CHART_POINT_NUM; i++) {
        lv_chart_set_next(chart, ir_ser, 0);
        lv_chart_set_next(chart, broadband_ser, 0);
        lv_chart_set_next(chart, lux_ser, 0);
    }
    /* label for values: */
    chart_label = lv_label_create(win, NULL);
    lv_label_set_recolor(chart_label, true);
    lv_obj_align(chart_label, chart, LV_ALIGN_OUT_RIGHT_TOP, LV_DPI/5, 0);

    /* Refresh the chart and label manually at first */
    refresh_task(NULL);
}
#endif /* PL_CONFIG_HAS_SGP30 */
