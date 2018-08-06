/*
 * gui_mainmenu.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "gui_mainmenu.h" /* own interface */
#include "lvgl.h" /* interface to GUI library */
#include "sysmon/sysmon.h" /* system monitor */
#include "demo/demo.h" /* LittlevGL demo */

static lv_obj_t *win = NULL;

/**
 * Called when the SysMon button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_SysMon_click_action(struct _lv_obj_t * obj) {
	/* delete main menu window and all its objects */
	lv_obj_del(win);
	win = NULL;
	/* create system monitor */
	sysmon_create();
	return LV_RES_INV;
}

/**
 * Called when the Demo button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_Demo_click_action(struct _lv_obj_t * obj) {
	/* delete main menu window and all its objects */
	lv_obj_del(win);
	win = NULL;
	/* create system monitor */
	demo_create();
	return LV_RES_INV;
}


void GUI_MainMenu_Create(void) {
	lv_obj_t *label;

	/* create window */
    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Main Menu");

    /*Make the window content responsive*/
    lv_win_set_layout(win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */

    /* Create SysMon menu buttons */
	lv_obj_t *btn1 = lv_btn_create(win, NULL);             /*Add to the active window */
	//lv_obj_set_pos(btn1, 5, 5);                                    /*Adjust the position*/
	//lv_obj_set_size(btn1, 96, 30);
	lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, Btn_SysMon_click_action);   /*Assign a callback for clicking*/
	label = lv_label_create(btn1, NULL);                  /*Put on 'btn1'*/
	lv_label_set_text(label, "SysMon");

    /* Create Demo menu buttons */
	lv_obj_t *btn2 = lv_btn_create(win, NULL);             /*Add to the active window */
	lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, Btn_Demo_click_action);   /*Assign a callback for clicking*/
	label = lv_label_create(btn2, NULL);                  /*Put on 'btn1'*/
	lv_label_set_text(label, "Demo");
}
