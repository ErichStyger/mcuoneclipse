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

#if 0
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

static lv_group_t *navGroup;

static void tab_create_lux(lv_obj_t *parent) {
  lv_obj_t *label;

  /* Create SysMon menu buttons */
#if 0
  lv_obj_t *btn1 = lv_btn_create(parent, NULL);             /*Add to the active window */
  //lv_obj_set_pos(btn1, 5, 5);                                    /*Adjust the position*/
  lv_obj_set_size(btn1, 64, 18);
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, Btn_SysMon_click_action);   /*Assign a callback for clicking*/

  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "test");
  lv_group_add_obj(navGroup, btn1);
  lv_group_focus_obj(btn1);
#endif
#if 1
  label = lv_label_create(parent, NULL);;
  lv_label_set_text(label, "This the first tab");
  lv_group_add_obj(navGroup, label);
#endif
}

static void tab_create_air(lv_obj_t *parent) {
  lv_obj_t *label;

  label = lv_label_create(parent, NULL);;
  lv_label_set_text(label, "Air information");
}


static lv_obj_t *tv; /* main view, a tab view */

static void tabViewCreate(void) {
  lv_obj_t *tab1, *tab2;

  navGroup = lv_group_create(); /* create group for touchless navigation */
  lv_indev_set_group(LV_GetInputDevice(), navGroup); /* assign group to input device */
  /* change the default focus style which is an orangish thing */
  //lv_group_set_style_mod_cb(navGroup, style_mod_cb);

  tv = lv_tabview_create(lv_scr_act(), NULL);

  lv_style_t *tabStyle;

  tabStyle = lv_tabview_get_style(tv, LV_TABVIEW_STYLE_INDIC),
  lv_tabview_set_style(tv, LV_TABVIEW_STYLE_INDIC, tabStyle);

  tab1 = lv_tabview_add_tab(tv, "Lux");
 // tab2 = lv_tabview_add_tab(tv, "CO2");

 // lv_obj_set_height(tab1, 10);

 // lv_group_add_obj(navGroup, tv);
  lv_group_add_obj(navGroup, tab1); /* add tab to touchless navigation group */
  //lv_group_add_obj(navGroup, tab2); /* add tab to touchless navigation group */

  tab_create_lux(tab1);
  //tab_create_air(tab2);
}

static void GUI_MainMenu_Create(void) {
#if 1
  GUI_MainMenuCreate();
#elif 0
  tabViewCreate();
#else
  lv_obj_t *label;

  lv_group_t *group = lv_group_create(); /* create group */
  lv_indev_set_group(LV_GetInputDevice(), group); /* assign group to input device */

  /* change the default focus style which is an orangish thing */
  lv_group_set_style_mod_cb(group, style_mod_cb);

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
#endif

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

static void GuiTask(void *p) {
  vTaskDelay(pdMS_TO_TICKS(200)); /* give hardware time to power up */
  LCD1_Init();

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

  if (xTaskCreate(GuiTask, "gui", 1500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
#endif /* PL_CONFIG_HAS_GUI */
