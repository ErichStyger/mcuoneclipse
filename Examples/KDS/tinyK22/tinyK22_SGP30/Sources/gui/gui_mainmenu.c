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
#include "UTIL1.h"
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
static lv_obj_t *mbox1;

/*Called when a button is clicked*/
static lv_res_t mbox_apply_action(lv_obj_t *mbox, const char * txt) {
    //printf("Mbox button: %s\n", txt);
  if (txt!=NULL) {
    if (UTIL1_strcmp(txt, "Apply")==0) {
      return LV_RES_OK; /* keep message box */
    } else if (UTIL1_strcmp(txt, "Close")==0) {
      GUI_GroupPull();
      lv_obj_del(mbox1);
      mbox1 = NULL;
      return LV_RES_INV; /* delete message box */
    }
  }
  return LV_RES_OK; /*Return OK if the message box is not deleted*/
}

static lv_res_t Btn_About_click_action(struct _lv_obj_t *obj) {
  /* create message box: */
  mbox1 = lv_mbox_create(lv_scr_act(), NULL);
  /* set message box text: */
  lv_mbox_set_text(mbox1, "About");                    /*Set the text*/
  /*Add two buttons*/
  static const char *btns[] ={"\221Apply", "\221Close", ""}; /*Button description. '\221' lv_btnm like control char*/
  lv_mbox_add_btns(mbox1, btns, mbox_apply_action);
  lv_obj_set_width(mbox1, 120);
  lv_obj_align(mbox1, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 70); /*Align to the corner*/
  GUI_GroupPush();
  GUI_AddObjToGroup(mbox1);
  lv_group_focus_obj(mbox1);
}

static lv_res_t btn_click_action(lv_obj_t * btn) {
    uint8_t id = lv_obj_get_free_num(btn);

   // printf("Button %d is released\n", id);
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void GUI_MainMenuCreate(void) {
  lv_obj_t *gui_win;

  GUI_GroupPush();
  /* create window */
  gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");

  /* Make the window content responsive */
  lv_win_set_layout(gui_win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */

  /*Create a normal button*/
  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_pos(btn1, 2, 25);
//  lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
//  lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  lv_obj_t *label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "Test");

  lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

  /*Add a label to the button*/
 // label = lv_label_create(btn1, NULL);
  //lv_label_set_text(label, "Normal");
  GUI_AddObjToGroup(btn1);

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
  obj = lv_list_add(list1, SYMBOL_FILE, "About", Btn_About_click_action);
  GUI_AddObjToGroup(obj);
  obj = lv_list_add(list1, SYMBOL_PLUS, "Test", NULL);
  GUI_AddObjToGroup(obj);
}

#endif /* PL_CONFIG_HAS_GUI */
