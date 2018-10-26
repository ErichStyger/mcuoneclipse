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
}

#endif /* PL_CONFIG_HAS_GUI */
