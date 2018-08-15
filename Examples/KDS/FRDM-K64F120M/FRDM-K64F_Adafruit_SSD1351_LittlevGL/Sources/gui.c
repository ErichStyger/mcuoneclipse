/*
 * gui.c
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */
#include "gui.h"
#include "lv.h"
#include "lvgl/lvgl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LCD1.h"
#include "GDisp1.h"
#include "KEY1.h"

static lv_obj_t *win = NULL;

static lv_res_t Btn_SysMon_click_action(struct _lv_obj_t * obj) {
  /* delete main menu window and all its objects */
 // lv_obj_del(win);
//  win = NULL;
  /* create system monitor gui */
//  sysmon_create();
  return LV_RES_OK;
}

static lv_res_t Btn_Demo_click_action(struct _lv_obj_t *obj) {
   return LV_RES_OK;
}


static lv_res_t Btn_Hardware_click_action(struct _lv_obj_t *obj) {
 return LV_RES_OK;
}

static void GUI_MainMenu_Create(void) {
  lv_obj_t *label;

#if 0
  static lv_style_t style1;
  lv_style_copy(&style1, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
  style1.body.main_color = LV_COLOR_RED;
  style1.body.grad_color = LV_COLOR_RED;
  style1.body.radius = 10;
  style1.body.border.color = LV_COLOR_GRAY;
  style1.body.border.width = 2;
  style1.body.border.opa = LV_OPA_50;
  style1.body.padding.hor = 5;            /*Horizontal padding, used by the bar indicator below*/
  style1.body.padding.ver = 5;            /*Vertical padding, used by the bar indicator below*/
  style1.text.color = LV_COLOR_RED;

  /*Create a simple object*/
  lv_obj_t *obj1 = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_style(obj1, &style1);                        /*Apply the created style*/
  lv_obj_set_pos(obj1, 5, 5);                           /*Set the position*/

  /*Create a label on the object. The label's style is NULL by default*/
  label = lv_label_create(obj1, NULL);
  lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);       /*Align the label to the middle*/
#endif

#if 1
  lv_group_t *group = lv_group_create(); /* create group */
  lv_indev_set_group(LV_GetInputDevice(), group); /* assign group to input device */

  /* create window */
  win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(win, "Main Menu");
  lv_win_set_btn_size(win, 8);

  /*Make the window content responsive*/
  lv_win_set_layout(win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */

    /* Create SysMon menu buttons */
  lv_obj_t *btn1 = lv_btn_create(win, NULL);             /*Add to the active window */
  //lv_obj_set_pos(btn1, 5, 5);                                    /*Adjust the position*/
  lv_obj_set_size(btn1, 64, 18);
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, Btn_SysMon_click_action);   /*Assign a callback for clicking*/
  label = lv_label_create(btn1, NULL);                  /*Put on 'btn1'*/
  lv_label_set_text(label, "SysMon");
  lv_group_add_obj(group, btn1);

  /* Create Demo menu buttons */
  lv_obj_t *btn2 = lv_btn_create(win, NULL);             /*Add to the active window */
  lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, Btn_Demo_click_action);   /*Assign a callback for clicking*/
  lv_obj_set_size(btn2, 64, 18);
  label = lv_label_create(btn2, NULL);                  /*Put on 'btn1'*/
  lv_label_set_text(label, "Demo");
  lv_group_add_obj(group, btn2);

    /* Create Hardware menu buttons */
  lv_obj_t *btn3 = lv_btn_create(win, NULL);             /*Add to the active window */
  lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, Btn_Hardware_click_action);   /*Assign a callback for clicking*/
  lv_obj_set_size(btn3, 64, 18);
  label = lv_label_create(btn3, NULL);                  /*Put on 'btn1'*/
  lv_label_set_text(label, "Hardware");
  lv_group_add_obj(group, btn3);
#endif
}

static void GuiTask(void *p) {
  LCD1_Init();
  LCD1_Clear();
  //GDisp1_DrawBox(0, 0, 50, 20, 1, GDisp1_COLOR_RED);
  //GDisp1_UpdateFull();
	GUI_MainMenu_Create();
	for(;;) {
		LV_Task(); /* call this every 1-20 ms */
		KEY1_ScanKeys();
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void GUI_Init(void) {
	LV_Init(); /* initialize GUI library */
	lv_theme_set_current(lv_theme_night_init(128, NULL));
  if (xTaskCreate(GuiTask, "gui", 1200/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
