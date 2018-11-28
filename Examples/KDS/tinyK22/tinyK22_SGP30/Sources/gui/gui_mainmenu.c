/*
 * gui_mainmenu.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_CONFIG_HAS_GUI
#include "gui_mainmenu.h" /* own interface */
#include "gui.h"
#include "lvgl/lvgl.h" /* interface to GUI library */
#include "lv.h"
#if PL_CONFIG_HAS_MMA8451
  #include "gui_accel.h"
#endif
#if PL_CONFIG_HAS_SGP30
  #include "gui_air.h"
#endif
#if PL_CONFIG_HAS_TSL2561
  #include "gui_ambient.h"
#endif
#if PL_CONFIG_HAS_RTC_DS3231
  #include "gui_clock.h"
#endif
#if PL_CONFIG_HAS_SHT31
  #include "gui_tempHum.h"
#endif
#if PL_CONFIG_HAS_NEO_PIXEL
  #include "gui_neopixel.h"
#endif

#if PL_CONFIG_HAS_MMA8451
/**
 * Called when the Accel button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV if object is deleted, LV_RES_OK otherwise.
 */
static lv_res_t Btn_Accel_click_action(struct _lv_obj_t *obj) {
	GUI_ACCEL_Create();
	return LV_RES_OK;
}
#endif

#if PL_CONFIG_HAS_SGP30
/**
 * Called when the Air button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_Air_click_action(struct _lv_obj_t *obj) {
  GUI_AIR_Create();
  return LV_RES_OK;
}
#endif

#if PL_CONFIG_HAS_TSL2561
/**
 * Called when the Ambient button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_Ambient_click_action(struct _lv_obj_t *obj) {
  GUI_AMBIENT_Create();
  return LV_RES_OK;
}
#endif

#if PL_CONFIG_HAS_RTC_DS3231
/**
 * Called when the Clock button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_Clock_click_action(struct _lv_obj_t *obj) {
  GUI_CLOCK_Create();
  return LV_RES_OK;
}
#endif

#if PL_CONFIG_HAS_SHT31
/**
 * Called when the Temp/Hum button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_TempHum_click_action(struct _lv_obj_t *obj) {
  GUI_TEMPHUM_Create();
  return LV_RES_OK;
}
#endif

#if PL_CONFIG_HAS_NEO_PIXEL
/**
 * Called when the Neopixel button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static lv_res_t Btn_NeoPixel_click_action(struct _lv_obj_t *obj) {
  GUI_NEO_Create();
  return LV_RES_OK;
}
#endif


static lv_obj_t *win;

static lv_res_t win_close_action(lv_obj_t *btn) {
 // lv_group_focus_freeze(GUI_GetGroup(), false);
  lv_obj_del(win);
  win = NULL;
  return LV_RES_INV;
}

/*Called when a button is clicked*/
static lv_res_t mbox_apply_action(lv_obj_t * mbox, const char * txt)
{
    //printf("Mbox button: %s\n", txt);
    return LV_RES_OK; /*Return OK if the message box is not deleted*/
}

static lv_res_t Btn_About_click_action2(struct _lv_obj_t *obj) {
  /* create message box: */
  lv_obj_t * mbox1 = lv_mbox_create(lv_scr_act(), NULL);
  /* set message box text: */
  lv_mbox_set_text(mbox1, "Default message box\n" "with buttons");                    /*Set the text*/
  /*Add two buttons*/
  static const char *btns[] ={"\221Apply", "\221Close", ""}; /*Button description. '\221' lv_btnm like control char*/
  lv_mbox_add_btns(mbox1, btns, mbox_apply_action);
  lv_obj_set_width(mbox1, 120);
  lv_obj_align(mbox1, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 70); /*Align to the corner*/
  GUI_CreateGroup();
  GUI_AddObjToGroup(mbox1);
  lv_group_focus_obj(mbox1);
}

static lv_res_t Btn_About_click_action(struct _lv_obj_t *obj) {
  lv_obj_t *closeBtn;

  win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(win, "About");
  closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);
  GUI_CreateGroup();
  GUI_AddObjToGroup(closeBtn);
  //lv_group_focus_obj(closeBtn);
  //lv_group_focus_freeze(GUI_GetGroup(), true); /* otherwise the items of the underlying view are still active */
  return LV_RES_OK;
}

void GUI_MainMenuCreate(void) {
  lv_obj_t *gui_win;

  /* create window */
  gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");

  /* Make the window content responsive */
  lv_win_set_layout(gui_win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */

  /* create list of objects */
  lv_obj_t *list1;
  lv_obj_t *obj;

  list1 = lv_list_create(gui_win, NULL);
  /*Add list elements*/
#if PL_CONFIG_HAS_MMA8451
  obj = lv_list_add(list1, SYMBOL_FILE, "Accel", Btn_Accel_click_action);
  GUI_AddObjToGroup(obj);
#endif
#if PL_CONFIG_HAS_SGP30
  obj = lv_list_add(list1, SYMBOL_DIRECTORY, "Air", Btn_Air_click_action);
  GUI_AddObjToGroup(obj);
#endif
#if PL_CONFIG_HAS_TSL2561
  obj = lv_list_add(list1, SYMBOL_CLOSE, "Ambient", Btn_Ambient_click_action);
  GUI_AddObjToGroup(obj);
#endif
#if PL_CONFIG_HAS_RTC_DS3231
  obj = lv_list_add(list1, SYMBOL_CLOSE, "Clock", Btn_Clock_click_action);
  GUI_AddObjToGroup(obj);
#endif
#if PL_CONFIG_HAS_SHT31
  obj = lv_list_add(list1, SYMBOL_CLOSE, "Temp/Hum", Btn_TempHum_click_action);
  GUI_AddObjToGroup(obj);
#endif
#if PL_CONFIG_HAS_NEO_PIXEL
  obj = lv_list_add(list1, SYMBOL_CLOSE, "NeoPixel", Btn_NeoPixel_click_action);
  GUI_AddObjToGroup(obj);
#endif
  obj = lv_list_add(list1, SYMBOL_FILE, "About", Btn_About_click_action2);
  GUI_AddObjToGroup(obj);
  obj = lv_list_add(list1, SYMBOL_PLUS, "Test", NULL);
  GUI_AddObjToGroup(obj);
}

#endif /* PL_CONFIG_HAS_GUI */
