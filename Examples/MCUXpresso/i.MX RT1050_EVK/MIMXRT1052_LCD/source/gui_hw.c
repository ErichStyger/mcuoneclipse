/*
 * gui_hw.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "gui_hw.h"
#include "gui_mainmenu.h"
#include "lvgl.h"
#include "LED.h"

static lv_obj_t *win;
static lv_obj_t *led;
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
static void led_task(void *param) {
    if (LED_IsOn()) {
      lv_led_on(led);
    } else {
        lv_led_off(led);
    }
}

void gui_hw_create(void) {
    refr_task = lv_task_create(led_task, REFR_TIME, LV_TASK_PRIO_LOW, NULL);

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Hardware");
    lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);

    /* Make the window content responsive */
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);

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

    /*Create a LED and switch it ON*/
    led  = lv_led_create(win, NULL);
    lv_obj_set_style(led, &style_led);
    lv_obj_align(led, NULL, LV_ALIGN_IN_TOP_MID, 40, 40);
    if (LED_IsOn()) {
      lv_led_on(led);
    } else {
        lv_led_off(led);
    }
    /* Create label next to the LED */
    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "LED");
    lv_obj_align(label, led, LV_ALIGN_OUT_LEFT_MID, -40, 0);
}

