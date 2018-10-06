/*
 * gui_mainmenu.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_CONFIG_HAS_GUI
#include "gui_mainmenu.h" /* own interface */
#include "lvgl/lvgl.h" /* interface to GUI library */
#include "lv.h"
#if PL_CONFIG_HAS_MMA8451
  #include "gui_accel.h"
#endif
#include "gui.h"

static lv_obj_t *gui_win = NULL;
static lv_obj_t *gui_btnAccel = NULL;
static lv_obj_t *gui_btnAir = NULL;

#if PL_CONFIG_HAS_MMA8451
/**
 * Called when the Accel button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_Accel_click_action(struct _lv_obj_t *obj) {
	/* delete main menu window and all its objects */
  //GUI_RemoveObjFromGroup(gui_btnAccel);
 // GUI_RemoveObjFromGroup(gui_btnAir);
//	lv_obj_del(gui_win);
//	gui_win = NULL;
	GUI_ACCEL_Create();
	return LV_RES_INV;
}
#endif


void GUI_MainMenuCreate(void) {
	lv_obj_t *label;

  /* create window */
	gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");
//  lv_win_set_btn_size(win, 6); /* reduce size of window title */

  /* Make the window content responsive */
  lv_win_set_layout(gui_win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */

#if PL_CONFIG_HAS_MMA8451
    /* Create Hardware menu buttons */
  gui_btnAccel = lv_btn_create(gui_win, NULL);
	lv_btn_set_action(gui_btnAccel, LV_BTN_ACTION_CLICK, Btn_Accel_click_action);
	label = lv_label_create(gui_btnAccel, NULL);
	lv_label_set_text(label, "Accel");
  //lv_obj_set_size(btn1, 64, 18);
#if PL_CONFIG_HAS_GUI_KEY_NAV
	GUI_AddObjToGroup(gui_btnAccel);
#endif
#endif

#if 1
    /* Create menu buttons */
	gui_btnAir = lv_btn_create(gui_win, NULL);
  label = lv_label_create(gui_btnAir, NULL);
  lv_label_set_text(label, "air");
#if PL_CONFIG_HAS_GUI_KEY_NAV
  GUI_AddObjToGroup(gui_btnAir);
#endif
#endif
}

#endif /* PL_CONFIG_HAS_GUI */
