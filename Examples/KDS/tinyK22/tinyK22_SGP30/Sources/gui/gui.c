/*
 * gui.c
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */
#include "Platform.h"
#if PL_CONFIG_HAS_GUI

#include "gui.h"
#include "lv.h"
#include "lvgl/lvgl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LCD1.h"
#if PL_CONFIG_HAS_KEYS
  #include "KEY1.h"
#endif
#include "gui_mainmenu.h"

#if PL_CONFIG_HAS_GUI_KEY_NAV
static lv_group_t *gui_group; /* group for touchless navigation */

/* style modification callback for the focus of an element */
static void style_mod_cb(lv_style_t *style) {
#if LV_COLOR_DEPTH != 1
    /*Make the style to be a little bit orange*/
    style->body.border.opa = LV_OPA_COVER;
    style->body.border.color = LV_COLOR_ORANGE;

    /*If not empty or has border then emphasis the border*/
    if(style->body.empty == 0 || style->body.border.width != 0) style->body.border.width = LV_DPI / 50;

    style->body.main_color = lv_color_mix(style->body.main_color, LV_COLOR_ORANGE, LV_OPA_70);
    style->body.grad_color = lv_color_mix(style->body.grad_color, LV_COLOR_ORANGE, LV_OPA_70);
    style->body.shadow.color = lv_color_mix(style->body.shadow.color, LV_COLOR_ORANGE, LV_OPA_60);

    style->text.color = lv_color_mix(style->text.color, LV_COLOR_ORANGE, LV_OPA_70);
#else
    style->body.border.opa = LV_OPA_COVER;
    style->body.border.color = LV_COLOR_BLACK;
    style->body.border.width = 3;
#endif
}

void GUI_DeleteGroup(void) {
  lv_group_del(gui_group);
  gui_group = NULL;
}

void GUI_CreateGroup(void) {
  if (gui_group!=NULL) {
    GUI_DeleteGroup();
  }
  gui_group = lv_group_create(); /* create group for touchless navigation */
  lv_indev_set_group(LV_GetInputDevice(), gui_group); /* assign group to input device */
  /* change the default focus style which is an orangish thing */
  lv_group_set_style_mod_cb(gui_group, style_mod_cb);
}

lv_group_t *GUI_GetGroup(void) {
  return gui_group;
}

void GUI_AddObjToGroup(lv_obj_t * obj) {
  lv_group_add_obj(gui_group, obj);
}

void GUI_RemoveObjFromGroup(lv_obj_t * obj) {
  lv_group_remove_obj(obj);
}

#endif /* PL_CONFIG_HAS_GUI_KEY_NAV */

#include "GDisp1.h"
static void GuiTask(void *p) {
  vTaskDelay(pdMS_TO_TICKS(1000)); /* give hardware time to power up */
  LCD1_Init();

//  GDisp1_DrawBox(0, 0, 50, 20, 2, GDisp1_COLOR_RED);
//  GDisp1_UpdateFull();

#if PL_CONFIG_HAS_GUI_KEY_NAV
  GUI_CreateGroup();
#endif
  GUI_MainMenuCreate();
	for(;;) {
		LV_Task(); /* call this every 1-20 ms */
#if PL_CONFIG_HAS_KEYS
		KEY1_ScanKeys();
#endif
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void GUI_Init(void) {
	LV_Init(); /* initialize GUI library */
	//lv_theme_set_current(lv_theme_night_init(128, NULL));
  //lv_theme_set_current(lv_theme_alien_init(128, NULL));
  //lv_theme_set_current(lv_theme_default_init(128, NULL));
  //lv_theme_set_current(lv_theme_material_init(128, NULL));
  //lv_theme_set_current(lv_theme_mono_init(128, NULL));
  //lv_theme_set_current(lv_theme_zen_init(128, NULL));
  //lv_theme_set_current(lv_theme_nemo_init(128, NULL));

	//lv_theme_t *th = lv_theme_get_current();
	/* change default button style */
 // lv_style_btn_rel.body.radius = LV_DPI / 15;
 // lv_style_btn_rel.body.padding.hor = LV_DPI / 8;
 // lv_style_btn_rel.body.padding.ver = LV_DPI / 12;

  if (xTaskCreate(GuiTask, "Gui", 1700/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_CONFIG_HAS_GUI */
