/*
 * gui_hw.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_USE_GUI_HARDWARE
#include "gui_hw.h"
#include "gui_mainmenu.h"
#include "lvgl/lvgl.h"
#include "LED.h"
#include "accel/accel.h"
#include <stdio.h>

static lv_obj_t *win;
static lv_obj_t *led;
#if PL_CONFIG_USE_ACCEL
	static lv_obj_t *accel_label;
	#define CHART_POINT_NUM     100
	static lv_obj_t *accel_chart;
	static lv_chart_series_t *x_ser, *y_ser, *z_ser;
	#define ACCEL_MIN_VAL  -2048
	#define ACCEL_MAX_VAL   2048
	#define X_LABEL_COLOR     "FF0000"
	#define Y_LABEL_COLOR     "00FF00"
	#define Z_LABEL_COLOR     "0000FF"
#endif
static lv_task_t *refr_task;
#define REFR_TIME   (100)

/**
 * Called when the window's close button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t win_close_action(lv_obj_t *btn) {
    lv_obj_del(win);
    win = NULL;
    led = NULL;
    lv_task_del(refr_task);
    refr_task = NULL;
    GUI_MainMenu_Create();
    return LV_RES_INV;
}

/**
 * Called periodically to monitor the LED.
 * @param param unused
 */
static void refresh_task(void *param) {
    if (LED_IsOn()) {
      lv_led_on(led);
    } else {
      lv_led_off(led);
    }
#if PL_CONFIG_USE_ACCEL
	int x, y, z;

	if (ACCEL_GetAccelData(&x, &y, &z)==0) {
    	char buf[64];
    	if (x>ACCEL_MAX_VAL) {
    		x = ACCEL_MAX_VAL;
    	}
    	if (y>ACCEL_MAX_VAL) {
    		y = ACCEL_MAX_VAL;
    	}
    	if (z>ACCEL_MAX_VAL) {
    		z = ACCEL_MAX_VAL;
    	}
    	if (x<ACCEL_MIN_VAL) {
    		x = ACCEL_MIN_VAL;
    	}
    	if (y<ACCEL_MIN_VAL) {
    		y = ACCEL_MIN_VAL;
    	}
    	if (z<ACCEL_MIN_VAL) {
    		z = ACCEL_MIN_VAL;
    	}
        /*Add the CPU and memory data to the chart*/
        lv_chart_set_next(accel_chart, x_ser, x);
        lv_chart_set_next(accel_chart, y_ser, y);
        lv_chart_set_next(accel_chart, z_ser, z);

    	snprintf(buf, sizeof(buf), "%s%s x: %6d%s\n%s%s y: %6d%s\n%s%s z:%6d%s",
    			LV_TXT_COLOR_CMD, X_LABEL_COLOR, x, LV_TXT_COLOR_CMD,
				LV_TXT_COLOR_CMD, Y_LABEL_COLOR, y, LV_TXT_COLOR_CMD,
				LV_TXT_COLOR_CMD, Z_LABEL_COLOR, z, LV_TXT_COLOR_CMD);
        lv_label_set_text(accel_label, buf);
    }
#endif
}

void gui_hw_create(void) {
    refr_task = lv_task_create(refresh_task, REFR_TIME, LV_TASK_PRIO_LOW, NULL);

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Hardware");
    lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);

    /* Make the window content responsive */
//    lv_win_set_layout(win, LV_LAYOUT_PRETTY);

    /* Create a style for the LED */
    static lv_style_t style_led;
    lv_style_copy(&style_led, &lv_style_pretty_color);
    style_led.body.radius = LV_RADIUS_CIRCLE;
    style_led.body.main_color = LV_COLOR_MAKE(0xb5, 0x0f, 0x04);
    style_led.body.grad_color = LV_COLOR_MAKE(0x50, 0x07, 0x02);
    style_led.body.border.color = LV_COLOR_MAKE(0xfa, 0x0f, 0x00);
    style_led.body.border.width = 3;
    style_led.body.border.opa = LV_OPA_30;
    style_led.body.shadow.color = LV_COLOR_MAKE(0xb5, 0x0f, 0x04);
    style_led.body.shadow.width = 10;

    /* Create a LED */
    led  = lv_led_create(win, NULL);
    lv_obj_set_style(led, &style_led);
    //lv_obj_align(led, win, LV_ALIGN_IN_TOP_LEFT, 20, 20);
    lv_obj_set_pos(led, 10, 10);

    /* Create label next to the LED */
    lv_obj_t *label = lv_label_create(win, NULL);
    lv_label_set_text(label, "LED");
    lv_obj_align(label, led, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

#if PL_CONFIG_USE_ACCEL
    /*Create a chart with three data lines*/
    accel_chart = lv_chart_create(win, NULL);
    lv_obj_set_size(accel_chart, LV_HOR_RES / 2, LV_VER_RES / 2);

//    lv_obj_align(accel_chart, led, LV_ALIGN_OUT_TOP_RIGHT, 20, 20);
    //lv_obj_set_pos(accel_chart, LV_DPI / 10, LV_DPI / 10);
    lv_obj_set_pos(accel_chart, 70, 10);

    lv_chart_set_point_count(accel_chart, CHART_POINT_NUM);
    lv_chart_set_range(accel_chart, ACCEL_MIN_VAL, ACCEL_MAX_VAL);
    lv_chart_set_type(accel_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_series_width(accel_chart, 3);
    x_ser =  lv_chart_add_series(accel_chart, LV_COLOR_RED);
    y_ser =  lv_chart_add_series(accel_chart, LV_COLOR_GREEN);
    z_ser =  lv_chart_add_series(accel_chart, LV_COLOR_BLUE);

    /* Set the data series to zero */
    uint16_t i;
    for(i = 0; i < CHART_POINT_NUM; i++) {
        lv_chart_set_next(accel_chart, x_ser, 0);
        lv_chart_set_next(accel_chart, y_ser, 0);
        lv_chart_set_next(accel_chart, z_ser, 0);
    }
    /* label for accel/compass values: */
    accel_label = lv_label_create(win, NULL);
    lv_label_set_recolor(accel_label, true);
    lv_obj_align(accel_label, accel_chart, LV_ALIGN_OUT_RIGHT_TOP, LV_DPI / 5, 0);
#endif
    /*Refresh the chart and label manually at first*/
    refresh_task(NULL);
}
#endif /* PL_CONFIG_USE_GUI_HARDWARE */
