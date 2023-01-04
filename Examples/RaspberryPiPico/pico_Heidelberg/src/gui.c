/*
 * Copyright (c) 2019-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_GUI

#include "gui.h"
#include "gui_config.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuRTOS.h"
#include "oled.h"
#include "McuSSD1306.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuUtility.h"
#include "McuLog.h"

static TaskHandle_t GUI_TaskHndl; /* GUI task handle */
static TimerHandle_t timerHndlGuiExpired; /* timeout user actions */
static TimerHandle_t timerHndlCycleScreens; /* timer for cycling screens */

/* direct task notification bits */
#define GUI_TASK_NOTIFY_BUTTON_PRESSED  (1<<0)  /* a button has been pressed */
#define GUI_TASK_NOTIFY_GUI_TIMEOUT     (1<<1)  /* user did not press a button for some time */
#define GUI_TASK_NOTIFY_NEXT_SCREEN     (1<<2)  /* show the next cycling screen */

#if PL_CONFIG_USE_GUI_KEY_NAV && LV_USE_GROUP
#define GUI_GROUP_NOF_IN_STACK   4
typedef struct GUI_Group_t {
  lv_group_t *stack[GUI_GROUP_NOF_IN_STACK]; /* stack of GUI groups */
  uint8_t sp; /* stack pointer, points to next free element */
} GUI_Group_t;
static GUI_Group_t groups;

void GUI_AddObjToGroup(lv_obj_t *obj) {
  lv_group_add_obj(GUI_GroupPeek(), obj);
}

void GUI_RemoveObjFromGroup(lv_obj_t *obj) {
  lv_group_remove_obj(obj);
}

lv_group_t *GUI_GroupPeek(void) {
  if (groups.sp == 0) {
    return NULL;
  }
  return groups.stack[groups.sp-1];
}

void GUI_GroupPull(void) {
  if (groups.sp == 0) {
    return;
  }
  lv_group_del(groups.stack[groups.sp-1]);
  groups.sp--;
  lv_indev_set_group(LV_GetInputDevice(), groups.stack[groups.sp-1]); /* assign group to input device */
}

void GUI_GroupPush(void) {
  lv_group_t *gui_group;

  if (groups.sp >= GUI_GROUP_NOF_IN_STACK) {
    return;
  }
  gui_group = lv_group_create();
  lv_indev_set_group(LV_GetInputDevice(), gui_group); /* assign group to input device */
  /* change the default focus style which is an orange'ish thing */
  //lv_group_set_style_mod_cb(gui_group, style_mod_cb);
  groups.stack[groups.sp] = gui_group;
  groups.sp++;
}
#endif /* PL_CONFIG_USE_GUI_KEY_NAV */

#if 0 /* examples and tests, not used */
/* ------------------------------------------------------- Button ----------------------------------------------- */
static void btn_event_cb(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_target(e);
  if(code == LV_EVENT_PRESSED) {
    static uint8_t cnt = 0;
    cnt++;

    /*Get the first child of the button which is the label and change its text*/
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "B:%d", cnt);
  }
}

static void btn2_event_cb(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * btn = lv_event_get_target(e);
  if(code == LV_EVENT_PRESSED) {
    static uint8_t cnt = 0;
    cnt++;

    /*Get the first child of the button which is the label and change its text*/
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "B:%d", cnt);
  }
}

void lv_example_button(void) {
  lv_obj_t *btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
  lv_obj_set_pos(btn, 2, 2);                            /*Set its position*/
  lv_obj_set_size(btn, 40, 15);                          /*Set its size*/
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

  lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
  lv_label_set_text(label, "B0");                     /*Set the labels text*/
  lv_obj_center(label);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
  lv_group_focus_obj(btn);
#endif
#if 1
  lv_obj_t *btn2 = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
  lv_obj_set_pos(btn2, 80, 2);                            /*Set its position*/
  lv_obj_set_size(btn2, 40, 15);                          /*Set its size*/
  lv_obj_add_event_cb(btn2, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

  lv_obj_t * label2 = lv_label_create(btn2);          /*Add a label to the button*/
  lv_label_set_text(label2, "B2");                     /*Set the labels text*/
  lv_obj_center(label2);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn2);
  lv_group_focus_obj(btn2);
#endif
#endif
}
/* ------------------------------------------------------- Slider ----------------------------------------------- */
static lv_obj_t *slider_label;

static void slider_event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *slider = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -3);
  }
}

/**
 * Create a slider and write its value on a label.
 */
void lv_example_slider(void) {
  lv_obj_t * slider = lv_slider_create(lv_scr_act());
  lv_obj_set_pos(slider, 10, 32);
  lv_obj_set_width(slider, 70);                          /*Set the width*/
  lv_slider_set_range(slider, 0, 100);
  //lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
  lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

  /*Create a label above the slider*/
  slider_label = lv_label_create(lv_scr_act());
  lv_label_set_text(slider_label, "0%");
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_TOP_MID, 0, -3);    /*Align top of the slider*/
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(slider);
  lv_group_focus_obj(slider);
#endif
}

/* ------------------------------------------------------- Bar ----------------------------------------------- */
void lv_example_bar(void) {
  lv_obj_t *bar1 = lv_bar_create(lv_scr_act());
  lv_obj_set_size(bar1, 80, 6);
  lv_bar_set_range(bar1, 0, 100);
  lv_obj_set_pos(bar1, 10, 45);
  lv_bar_set_value(bar1, 70, LV_ANIM_OFF);
}

/* ------------------------------------------------------- Text ----------------------------------------------- */
static void lv_example_text(void) {
  /*Create a white label, set its text and align it to the center*/
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Hello world");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

/* -------------------------------- Textarea with input buttons ----------------------------------------------- */
static void textarea_event_handler(lv_event_t *e) {
  lv_obj_t *ta = lv_event_get_target(e);
  LV_LOG_USER("Enter was pressed. The current text is: %s", lv_textarea_get_text(ta));
}

static void btnm_event_handler(lv_event_t * e) {
  lv_obj_t * obj = lv_event_get_target(e);
  lv_obj_t * ta = lv_event_get_user_data(e);
  const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

  if(strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) {
    lv_textarea_del_char(ta);
  } else if(strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) {
    lv_event_send(ta, LV_EVENT_READY, NULL);
  } else {
    lv_textarea_add_text(ta, txt);
  }
}

void lv_example_textarea_1(void) {
  lv_obj_t *ta = lv_textarea_create(lv_scr_act());
  lv_textarea_set_one_line(ta, true);
  //lv_obj_set_size(ta, 80, 16);
  lv_obj_set_width(ta, 80);
  lv_obj_set_scrollbar_mode(ta, LV_SCROLLBAR_MODE_OFF);
  lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_READY, ta);
  lv_obj_add_state(ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/

  static const char * btnm_map[] = {"1", "2", "3", "4", "5", "6", "\n",
                                     LV_SYMBOL_BACKSPACE, "7", "8", "9", "0", LV_SYMBOL_NEW_LINE, ""
                                   };

  lv_obj_t *btnm = lv_btnmatrix_create(lv_scr_act());
  lv_obj_set_size(btnm, 128, 42);
  lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta);
  lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
  lv_btnmatrix_set_map(btnm, btnm_map);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(ta);
  GUI_AddObjToGroup(btnm);
  lv_group_focus_obj(ta);
#endif
}

/* ------------------------------------------------------- Arc ----------------------------------------------- */
static void value_changed_event_cb(lv_event_t *e) {
  lv_obj_t *arc = lv_event_get_target(e);
  lv_obj_t *label = lv_event_get_user_data(e);

  lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));

  /*Rotate the label to the current position of the arc*/
  lv_arc_rotate_obj_to_angle(arc, label, 25);
}

void lv_example_arc_1(void) {
  lv_obj_t * label = lv_label_create(lv_scr_act());

  /*Create an Arc*/
  lv_obj_t * arc = lv_arc_create(lv_scr_act());
  lv_obj_set_size(arc, 50, 50);
  lv_arc_set_rotation(arc, 135);
  lv_arc_set_bg_angles(arc, 0, 270);
  lv_arc_set_value(arc, 10);
  lv_obj_center(arc);
  lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, label);

  /*Manually update the label for the first time*/
  lv_event_send(arc, LV_EVENT_VALUE_CHANGED, NULL);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(arc);
  lv_group_focus_obj(arc);
#endif
}

/* ------------------------------------------------------- Checkbox ----------------------------------------------- */
static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    const char * txt = lv_checkbox_get_text(obj);
    const char * state = lv_obj_get_state(obj) & LV_STATE_CHECKED ? "Checked" : "Unchecked";
    LV_LOG_USER("%s: %s", txt, state);
  }
}

void lv_example_checkbox_1(void) {
  lv_obj_set_flex_flow(lv_scr_act(), LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(lv_scr_act(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

  lv_obj_t *cb;
  cb = lv_checkbox_create(lv_scr_act());
  lv_checkbox_set_text(cb, "Apple");
  lv_obj_add_event_cb(cb, event_handler, LV_EVENT_ALL, NULL);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(cb);
 #endif

  cb = lv_checkbox_create(lv_scr_act());
  lv_checkbox_set_text(cb, "Banana");
  lv_obj_add_state(cb, LV_STATE_CHECKED);
  lv_obj_add_event_cb(cb, event_handler, LV_EVENT_ALL, NULL);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(cb);
 #endif
#if 0
  cb = lv_checkbox_create(lv_scr_act());
  lv_checkbox_set_text(cb, "Lemon");
  lv_obj_add_state(cb, LV_STATE_DISABLED);
  lv_obj_add_event_cb(cb, event_handler, LV_EVENT_ALL, NULL);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(cb);
#endif
#endif
#if 0

  cb = lv_checkbox_create(lv_scr_act());
  lv_obj_add_state(cb, LV_STATE_CHECKED | LV_STATE_DISABLED);
  lv_checkbox_set_text(cb, "Melon\nand a new line");
  lv_obj_add_event_cb(cb, event_handler, LV_EVENT_ALL, NULL);
#endif
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(cb);
  lv_group_focus_obj(cb);
#endif
  lv_obj_update_layout(cb);
}

static void checkbox_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    LV_LOG_USER("State: %s\n", lv_checkbox_is_checked(obj) ? "Checked" : "Unchecked");
  }
}

void lv_ex_checkbox_1(void) {
  lv_obj_t * cb = lv_checkbox_create(lv_scr_act());
  lv_checkbox_set_text(cb, "I agree");
  lv_obj_align(cb, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(cb, checkbox_event_handler, LV_EVENT_ALL, NULL);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(cb);
  lv_group_focus_obj(cb);
#endif
}

/* ------------------------------------------------------- radio buttons ----------------------------------------------- */
static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static uint32_t active_index_1 = 0;
static uint32_t active_index_2 = 0;

static void radio_event_handler(lv_event_t * e) {
  uint32_t * active_id = lv_event_get_user_data(e);
  lv_obj_t * cont = lv_event_get_current_target(e);
  lv_obj_t * act_cb = lv_event_get_target(e);
  lv_obj_t * old_cb = lv_obj_get_child(cont, *active_id);

  /*Do nothing if the container was clicked*/
  if(act_cb == cont) return;

  lv_obj_clear_state(old_cb, LV_STATE_CHECKED);   /*Uncheck the previous radio button*/
  lv_obj_add_state(act_cb, LV_STATE_CHECKED);     /*Uncheck the current radio button*/

  *active_id = lv_obj_get_index(act_cb);

  LV_LOG_USER("Selected radio buttons: %d, %d", (int)active_index_1, (int)active_index_2);
}

static void radiobutton_create(lv_obj_t * parent, const char * txt) {
  lv_obj_t * obj = lv_checkbox_create(parent);
  lv_checkbox_set_text(obj, txt);
  lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_add_style(obj, &style_radio, LV_PART_INDICATOR);
  lv_obj_add_style(obj, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(obj);
#endif
}

/**
 * Checkboxes as radio buttons
 */
void lv_example_radiobuttons_2(void) {
  /* The idea is to enable `LV_OBJ_FLAG_EVENT_BUBBLE` on checkboxes and process the
   * `LV_EVENT_CLICKED` on the container.
   * A variable is passed as event user data where the index of the active
   * radiobutton is saved */
  lv_style_init(&style_radio);
  lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE);
  lv_style_set_pad_all(&style_radio, 0); /* https://forum.lvgl.io/t/how-to-set-size-of-checkbox/4257 */

  lv_style_init(&style_radio_chk);
  lv_style_set_bg_img_src(&style_radio_chk, NULL);

  uint32_t i;
  char buf[32];

  lv_obj_t *cont1 = lv_obj_create(lv_scr_act());
  lv_obj_set_flex_flow(cont1, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_size(cont1, lv_pct(40), lv_pct(100));
  lv_obj_add_event_cb(cont1, radio_event_handler, LV_EVENT_CLICKED, &active_index_1);

  for(i = 0; i < 5; i++) {
      lv_snprintf(buf, sizeof(buf), "A %d", (int)i + 1);
      radiobutton_create(cont1, buf);
  }
  /*Make the first checkbox checked*/
  lv_obj_add_state(lv_obj_get_child(cont1, 0), LV_STATE_CHECKED);

  lv_obj_t * cont2 = lv_obj_create(lv_scr_act());
  lv_obj_set_flex_flow(cont2, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_size(cont2, lv_pct(40), lv_pct(80));
  lv_obj_set_x(cont2, lv_pct(50));
  lv_obj_add_event_cb(cont2, radio_event_handler, LV_EVENT_CLICKED, &active_index_2);

  for(i = 0; i < 3; i++) {
      lv_snprintf(buf, sizeof(buf), "B %d", (int)i + 1);
      radiobutton_create(cont2, buf);
  }

  /*Make the first checkbox checked*/
  lv_obj_add_state(lv_obj_get_child(cont2, 0), LV_STATE_CHECKED);
}

/* ------------------------------------------------------- drop down ----------------------------------------------- */
static void event_handler_drop_down(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
      char buf[32];
      lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
      LV_LOG_USER("Option: %s", buf);
  }
}

void lv_example_dropdown_1(void) {
  /*Create a normal drop down list*/
  lv_obj_t * dd = lv_dropdown_create(lv_scr_act());
  lv_dropdown_set_options(dd, "Apple\n"
                          "Banana\n"
                          "Orange\n"
                          "Cherry\n"
                          "Grape\n"
                          "Raspberry\n"
                          "Melon\n"
                          "Orange\n"
                          "Lemon\n"
                          "Nuts");
  //lv_obj_set_pos(dd, 0, 0);
  lv_obj_set_width(dd, 80);
  lv_obj_align(dd, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_add_event_cb(dd, event_handler_drop_down, LV_EVENT_ALL, NULL);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(dd);
  lv_group_focus_obj(dd);
#endif
}

/* ------------------------------------------------------- switch ----------------------------------------------- */
static void event_handler_switch(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
      LV_LOG_USER("State: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
  }
}

void lv_example_switch_1(void) {
  lv_obj_set_flex_flow(lv_scr_act(), LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(lv_scr_act(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  lv_obj_t *sw;

  sw = lv_switch_create(lv_scr_act());
  lv_obj_add_state(sw, LV_STATE_CHECKED);
  lv_obj_add_event_cb(sw, event_handler_switch, LV_EVENT_ALL, NULL);

  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Lights");
  lv_obj_align_to(label, sw, LV_ALIGN_OUT_RIGHT_MID, 0, 0); /* \todo does not work as expected? is placed below the switch: because of column? */

#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(sw);
  lv_group_focus_obj(sw);
#endif
}

/* ------------------------------------------------------- line ----------------------------------------------- */
void lv_example_line_1(void) {
  /*Create an array for the points of the line*/
  static lv_point_t line_points[] = { {5, 5}, {20, 5}, {20, 15}, {5, 15}, {5, 5} };

#if 1
  /*Create style*/
  static lv_style_t style_line;
  lv_style_init(&style_line);
  lv_style_set_line_width(&style_line, 1);
//  lv_style_set_line_color(&style_line, lv_color_black());
  lv_style_set_line_color(&style_line, lv_color_white());
  lv_style_set_line_rounded(&style_line, true);
#endif
  /*Create a line and apply the new style*/
  lv_obj_t * line1;
  line1 = lv_line_create(lv_scr_act());
  lv_line_set_points(line1, line_points, sizeof(line_points)/sizeof(line_points[0]));     /*Set the points*/
  lv_obj_add_style(line1, &style_line, 0);
  lv_obj_center(line1);
}

/* ------------------------------------------------------- image ----------------------------------------------- */
void lv_example_img_1(void) {
  LV_IMG_DECLARE(LogoVerkehrshaus);
  lv_obj_t *img1 = lv_img_create(lv_scr_act());
  lv_img_set_src(img1, &LogoVerkehrshaus);
  lv_obj_set_pos(img1, 0, 0);
  //lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
 // lv_obj_set_size(img1, 60, 60);

  lv_obj_t *img2 = lv_img_create(lv_scr_act());
  lv_img_set_src(img2, LV_SYMBOL_OK "Accept");
  lv_obj_align_to(img2, img1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

/* ------------------------------------------------------- roller ----------------------------------------------- */
static void event_handler_roller(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    char buf[32];
    lv_roller_get_selected_str(obj, buf, sizeof(buf));
    LV_LOG_USER("Selected month: %s\n", buf);
  }
}

/**
 * An infinite roller with the name of the months
 */
void lv_example_roller_1(void) {
  lv_obj_t *roller1 = lv_roller_create(lv_scr_act());
  lv_roller_set_options(roller1,
                      "January\n"
                      "February\n"
                      "March\n"
                      "April\n"
                      "May\n"
                      "June\n"
                      "July\n"
                      "August\n"
                      "September\n"
                      "October\n"
                      "November\n"
                      "December",
                      LV_ROLLER_MODE_INFINITE);

  lv_roller_set_visible_row_count(roller1, 4);
  lv_obj_center(roller1);
  lv_obj_add_event_cb(roller1, event_handler_roller, LV_EVENT_ALL, NULL);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(roller1);
  lv_group_focus_obj(roller1);
#endif
}
#endif /* not used examples and tests */

/* ------------------------------------------------------- PicoHouse GUI ----------------------------------------------- */
/* global GUI elements */
typedef enum GuiScreens_e {
  GUI_SCREEN_SETTINGS, /* Settings, must be first in list! */
  GUI_SCREEN_LOGO_VHS, /* Verkehrshaus logo */
  GUI_SCREEN_LOGO_HSLU, /* HSLU logo */
  GUI_SCREEN_ENERGY_STATUS, /* status about energy */
  GUI_SCREEN_NOF_SCREENS /* sentinel, must be last! */
} GuiScreens_e;

static struct guiObjects {
  lv_obj_t *screens[GUI_SCREEN_NOF_SCREENS]; /* screen 0 or GUI_SCREEN_SETTINGS is the one with the settings */
  /* styles */
  lv_style_t style_customFont; /* style for custom font with symbols, needs to be global */

  lv_obj_t *slider_car_speed; /* slider for the car speed */
  lv_obj_t *label_slider_car_speed; /* label for car speed */

  lv_obj_t *label_light_switch; /* label for the light switch: a bulp (on) or a cross (off) */
  lv_obj_t *slider_light_brightness, *label_slider_brightness; /* slider for light, global because we change the value depending on the light on/off status */

  lv_obj_t *slider_color_red, *label_slider_color_red; /* label for red color */
  lv_obj_t *slider_color_green, *label_slider_color_green; /* label for green color */
  lv_obj_t *slider_color_blue, *label_slider_color_blue; /* label for blue color */
  lv_obj_t *bar_pv; /* bar for PV power */
} guiObjects;

/*
 * How to add symbols: https://docs.lvgl.io/8.3/overview/font.html#add-new-symbols
 * Unicode to UTF-8: https://www.cogsci.ed.ac.uk/~richard/utf-8.cgi?input=f287&mode=hex
 * Note: lvgl uses V5 of FontAwesome, use
 * https://fontawesome.com/v5/search
 * for searching symbols, use 'free' filter
 *
 * MY_SYMBOL_CAR
 *    https://fontawesome.com/v5/icons/bus?s=solid&f=classic
 *    Unicode: 0xf207, Hex UTF-8: EF 88 87
 * MY_SYMBOL_LIGHT
 *    https://fontawesome.com/icons/lightbulb?s=regular&f=classic,
 *    Unicode: 0xf0eb, Hex UTF-8: EF 83 AB
 * MY_SYMBOL_X
 *    https://fontawesome.com/v5/icons/times-circle?s=solid&f=classic
 *    Unicode: 0xf057, Hex UTF-8: EF 81 97
 * MY_SYMBOL_SUN
 *    https://fontawesome.com/v5/icons/sun?s=solid&f=classic
 *    Unicode: 0xf185, Hex UTF-8: EF 86 85
 * MY_SYMBOL_ARROW_UP
 *    https://fontawesome.com/v5/icons/arrow-up?s=regular&f=classic
 *    Unicode: 0xf062, Hex UTF-8: EF 81 A2
 * MY_SYMBOL_ARROW_DOWN
 *    https://fontawesome.com/v5/icons/arrow-down?s=solid&f=classic
 *    Unicode: 0xf063, Hex UTF-8: EF 81 A3
 * MY_SYMBOL_ARROW_LEFT_RIGHT
 *    https://fontawesome.com/v5/icons/exchange-alt?s=solid&f=classic
 *    Unicode: 0xf362, Hex UTF-8: EF 8D A2
 *
 * Font Converter: https://lvgl.io/tools/fontconverter
 * Name: customSymbols_12
 * Size: 12
 * Bpp: 1 bit-per-pixel
 * Options: all three disabled
 * Range:  0xf207,0xf0eb,0xf057,0xf185,0xf062,0xf063,0xf362,   (use the Unicode!)
 * Add the ones below which are part of LVGL:
61441,61448,61451,61452,61452,61453,61457,61459,61461,61465,
61468,61473,61478,61479,61480,61502,61512,61515,61516,61517,
61521,61522,61523,61524,61543,61544,61550,61552,61553,61556,
61559,61560,61561,61563,61587,61589,61636,61637,61639,61671,
61674,61683,61724,61732,61787,61931,62016,62017,62018,62019,
62020,62087,62099,62212,62189,62810,63426,63650
 * Browse: use image/FontAwesome5-Solid+Brands+Regular.woff  (Note: that's version 5, not all symbols are available)
 * Symbols: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY0123456789
 */
LV_FONT_DECLARE(customSymbols_12); /* font name with custom symbols plus the normal symbols/characters */
/* IDs of the symbols, use the Hex UTF-8 code: */
#define MY_SYMBOL_CAR               "\xEF\x88\x87" /* a car */
#define MY_SYMBOL_LIGHT             "\xEF\x83\xAB" /* a light bulb */
#define MY_SYMBOL_X                 "\xEF\x81\x97" /* a round shape with a cross */
#define MY_SYMBOL_SUN               "\xEF\x86\x85" /* a sun */
#define MY_SYMBOL_ARROW_UP          "\xEF\x81\xA2" /* an arrow pointing up */
#define MY_SYMBOL_ARROW_DOWN        "\xEF\x81\xA3" /* an arrow pointing down */
#define MY_SYMBOL_ARROW_LEFT_RIGHT  "\xEF\x8D\xA2" /* two arrows pointing left and right */

static void event_handler_button_car(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *btn = lv_event_get_target(e);
  if(code == LV_EVENT_PRESSED) {
    Road_SetIsOn(!Road_GetIsOn()); /* toggle start/stopping the car */
    /* update button symbol */
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    lv_label_set_text(label, Road_GetIsOn()? LV_SYMBOL_STOP : LV_SYMBOL_PLAY);
    /* enabling/disabling controls */
    if (Road_GetIsOn()) {
      lv_slider_set_value(guiObjects.slider_car_speed, Road_GetSpeed(), LV_ANIM_ON);
      lv_obj_clear_state(guiObjects.slider_car_speed, LV_STATE_DISABLED);
    } else {
      lv_slider_set_value(guiObjects.slider_car_speed, 0, LV_ANIM_ON);
      lv_obj_add_state(guiObjects.slider_car_speed, LV_STATE_DISABLED);
    }
    /* set an event to update the value */
    lv_event_send(guiObjects.slider_car_speed, LV_EVENT_VALUE_CHANGED, NULL);
  }
}

static void event_handler_slider_road_speed(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *slider = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    char buf[8];
    int val;

    if (Road_GetIsOn()) { /* road enabled? */
      lv_obj_clear_state(slider, LV_STATE_DISABLED); /* enable slider */
      val = lv_slider_get_value(slider);
      Road_SetSpeed(val); /* store setting */
    } else { /* road is off */
      lv_obj_add_state(slider, LV_STATE_DISABLED); /* disable slider */
      val = 0;
    }
    lv_snprintf(buf, sizeof(buf), "%d%%", val);
    lv_label_set_text(guiObjects.label_slider_car_speed, buf);
  }
}

static void event_handler_switch_lights(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  uint32_t color;

  if(code == LV_EVENT_VALUE_CHANGED) {
    if (lv_obj_has_state(obj, LV_STATE_CHECKED)) {
      Lights_SetLightIsOn(true);
      lv_label_set_text(guiObjects.label_light_switch, MY_SYMBOL_LIGHT); /* change label symbol */
      lv_slider_set_value(guiObjects.slider_light_brightness, Lights_GetBrightnessPercent(), LV_ANIM_ON);

      color = NEO_SPLIT_R(Lights_GetColor());
      color = McuUtility_map(color, 0, 0xff, 0, 100);
      lv_slider_set_value(guiObjects.slider_color_red,  color, LV_ANIM_ON);
      lv_obj_clear_state(guiObjects.slider_color_red, LV_STATE_DISABLED);

      color = NEO_SPLIT_G(Lights_GetColor());
      color = McuUtility_map(color, 0, 0xff, 0, 100);
      lv_slider_set_value(guiObjects.slider_color_green,  color, LV_ANIM_ON);
      lv_obj_clear_state(guiObjects.slider_color_green, LV_STATE_DISABLED);

      color = NEO_SPLIT_B(Lights_GetColor());
      color = McuUtility_map(color, 0, 0xff, 0, 100);
      lv_slider_set_value(guiObjects.slider_color_blue,  color, LV_ANIM_ON);
      lv_obj_clear_state(guiObjects.slider_color_blue, LV_STATE_DISABLED);
    } else { /* off */
      Lights_SetLightIsOn(false);
      lv_label_set_text(guiObjects.label_light_switch, MY_SYMBOL_X); /* change label symbol */
      lv_slider_set_value(guiObjects.slider_light_brightness, 0, LV_ANIM_ON);
      lv_obj_add_state(guiObjects.slider_color_red, LV_STATE_DISABLED);
      lv_slider_set_value(guiObjects.slider_color_red, 0, LV_ANIM_ON);
      lv_obj_add_state(guiObjects.slider_color_green, LV_STATE_DISABLED);
      lv_slider_set_value(guiObjects.slider_color_green, 0, LV_ANIM_ON);
      lv_obj_add_state(guiObjects.slider_color_blue, LV_STATE_DISABLED);
      lv_slider_set_value(guiObjects.slider_color_blue, 0, LV_ANIM_ON);
    }
    /* set an event to update the value */
    lv_event_send(guiObjects.slider_light_brightness, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(guiObjects.slider_color_red, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(guiObjects.slider_color_green, LV_EVENT_VALUE_CHANGED, NULL);
    lv_event_send(guiObjects.slider_color_blue, LV_EVENT_VALUE_CHANGED, NULL);
  }
}

static void event_handler_slider_light_brightness(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *slider = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    char buf[8];
    int val;

    if (Lights_GetLightIsOn()) {
      lv_obj_clear_state(slider, LV_STATE_DISABLED); /* enable slider */
      val = lv_slider_get_value(slider);
      Lights_SetBrightnessPercent(val); /* store setting */
    } else { /* light is off */
      lv_obj_add_state(slider, LV_STATE_DISABLED); /* disable slider */
      val = 0;
    }
    lv_snprintf(buf, sizeof(buf), "%d%%", val);
    lv_label_set_text(guiObjects.label_slider_brightness, buf);
  }
}

static void event_handler_slider_light_color_red(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *slider = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    char buf[8];
    int val;
    uint32_t color;

    if (Lights_GetLightIsOn()) {
      lv_obj_clear_state(slider, LV_STATE_DISABLED); /* enable slider */
      val = lv_slider_get_value(slider);
      color = McuUtility_map(val, 0, 100, 0, 255);
      color = NEO_INSERT_R(Lights_GetColor(), color);
      Lights_SetColor(color);
    } else { /* light is off */
      lv_obj_add_state(slider, LV_STATE_DISABLED); /* disable slider */
      val = 0;
    }
    lv_snprintf(buf, sizeof(buf), "%d%%", val);
    lv_label_set_text(guiObjects.label_slider_color_red, buf);
  }
}

static void event_handler_slider_light_color_green(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *slider = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    char buf[8];
    int val;
    uint32_t color;

    if (Lights_GetLightIsOn()) {
      lv_obj_clear_state(slider, LV_STATE_DISABLED); /* enable slider */
      val = lv_slider_get_value(slider);
      color = McuUtility_map(val, 0, 100, 0, 255);
      color = NEO_INSERT_G(Lights_GetColor(), color);
      Lights_SetColor(color);
    } else { /* light is off */
      lv_obj_add_state(slider, LV_STATE_DISABLED); /* disable slider */
      val = 0;
    }
    lv_snprintf(buf, sizeof(buf), "%d%%", val);
    lv_label_set_text(guiObjects.label_slider_color_green, buf);
  }
}

static void event_handler_slider_light_color_blue(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *slider = lv_event_get_target(e);
  if (code==LV_EVENT_VALUE_CHANGED) {
    char buf[8];
    int val;
    uint32_t color;

    if (Lights_GetLightIsOn()) {
      lv_obj_clear_state(slider, LV_STATE_DISABLED); /* enable slider */
      val = lv_slider_get_value(slider);
      color = McuUtility_map(val, 0, 100, 0, 255);
      color = NEO_INSERT_B(Lights_GetColor(), color);
      Lights_SetColor(color);
    } else { /* light is off */
      lv_obj_add_state(slider, LV_STATE_DISABLED); /* disable slider */
      val = 0;
    }
    lv_snprintf(buf, sizeof(buf), "%d%%", val);
    lv_label_set_text(guiObjects.label_slider_color_blue, buf);
  }
}
/* ---------------------------------------------------------------------------------- */
static void event_handler_drop_down_car(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    char buf[32];
    int idx = lv_dropdown_get_selected(obj); /* 0: fw, 1: bw, 2: auto */
    Road_SetMode((RoadMode_e)idx);
  } else if (code==LV_EVENT_READY) { /* see https://forum.lvgl.io/t/dropdown-list-change-font/6101 */
   // lv_obj_add_style(lv_dropdown_get_list(obj), &guiObjects.style_customFont, LV_PART_MAIN|LV_PART_SELECTED); /* assign custom font */
  }
}
/* ---------------------------------------------------------------------------------- */
static void createGUI(void) {
  /* initialize and create the screens */
  for(int i = 0; i<sizeof(guiObjects.screens)/sizeof(guiObjects.screens[0]); i++) {
    guiObjects.screens[i] = lv_obj_create(NULL);
  }
  /* initialize styles */
  lv_style_init(&guiObjects.style_customFont); /* style with custom symbol font */
  lv_style_set_text_font(&guiObjects.style_customFont, &customSymbols_12);

  /* create the different screens */
  /* ----------------------------------------------------------- */
  lv_scr_load(guiObjects.screens[GUI_SCREEN_LOGO_VHS]);
  {
    /* logo VHS */
    LV_IMG_DECLARE(LogoVerkehrshaus);
    lv_obj_t *img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, &LogoVerkehrshaus);
    lv_obj_center(img);
  }
  /* ----------------------------------------------------------- */
  lv_scr_load(guiObjects.screens[GUI_SCREEN_LOGO_HSLU]);
  {
    /* logo HSLU */
    LV_IMG_DECLARE(HSLU_Logo_DE_Weiss_rgb);
    lv_obj_t *img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, &HSLU_Logo_DE_Weiss_rgb);
    lv_obj_center(img);
  }
  /* -------------------- Energy status --------------------------------------- */
  lv_scr_load(guiObjects.screens[GUI_SCREEN_ENERGY_STATUS]);
  {
    guiObjects.bar_pv = lv_bar_create(lv_scr_act());
    lv_obj_set_size(guiObjects.bar_pv, 80, 6);
    lv_bar_set_range(guiObjects.bar_pv, 0, 100);
    lv_obj_set_pos(guiObjects.bar_pv, 10, 45);
    lv_bar_set_value(guiObjects.bar_pv, 70, LV_ANIM_OFF);
    /* \todo add more */
  }
  /* ----------------------------------------------------------- */
  lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]);

  /* controls for the car */
  lv_obj_t *panel_car;
  {
    panel_car = lv_obj_create(lv_scr_act());
    lv_obj_set_pos(panel_car, 0, 0);
    lv_obj_set_size(panel_car, 120, 28+22);
    lv_obj_add_flag(panel_car, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    {
      lv_obj_t *label_car;
      lv_obj_t *btn;
      lv_obj_t *label_button;

      /* label with symbol for the car */
      label_car = lv_label_create(panel_car);
      lv_label_set_text(label_car, MY_SYMBOL_CAR);
      lv_obj_add_style(label_car, &guiObjects.style_customFont, LV_PART_MAIN);
      lv_obj_set_pos(label_car, 0, 2);

      /* button to run/stop the car */
      btn = lv_btn_create(panel_car);
      lv_obj_align_to(btn, label_car, LV_ALIGN_OUT_RIGHT_MID, 5, -1);
      lv_obj_set_size(btn, 18, 15); /* reduce size of button */
      lv_obj_add_event_cb(btn, event_handler_button_car, LV_EVENT_ALL, NULL);
      lv_obj_add_flag(btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE);

      label_button = lv_label_create(btn); /* create label with btn as parent */
      lv_obj_add_style(label_button, &guiObjects.style_customFont, LV_PART_MAIN);
      lv_label_set_text(label_button, Road_GetIsOn()? LV_SYMBOL_STOP : LV_SYMBOL_PLAY);
      lv_obj_center(label_button);
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(btn);
      lv_group_focus_obj(btn); /* make it the current focus one */
    #endif

      /* slider for car speed */
      guiObjects.slider_car_speed = lv_slider_create(panel_car);
      lv_obj_add_flag(guiObjects.slider_car_speed, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE);
      lv_obj_align_to(guiObjects.slider_car_speed, btn, LV_ALIGN_OUT_RIGHT_MID, 7, 0);
      lv_obj_set_width(guiObjects.slider_car_speed, 25);
      lv_slider_set_range(guiObjects.slider_car_speed, 1, 100);
      lv_obj_set_style_bg_color(guiObjects.slider_car_speed, lv_color_white(), LV_PART_KNOB|LV_STATE_FOCUS_KEY); /* make knob white if selected */

      uint32_t speed;
      if (Road_GetIsOn()) {
        speed = Road_GetSpeed();
      } else {
        speed = 0;
      }
      lv_slider_set_value(guiObjects.slider_car_speed, speed, LV_ANIM_ON);
      lv_obj_add_event_cb(guiObjects.slider_car_speed, event_handler_slider_road_speed, LV_EVENT_VALUE_CHANGED, NULL);
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(guiObjects.slider_car_speed);
    #endif

      /* Create a label right of the slider */
      guiObjects.label_slider_car_speed = lv_label_create(panel_car);
      lv_label_set_text(guiObjects.label_slider_car_speed, "0%");
      lv_obj_align_to(guiObjects.label_slider_car_speed, guiObjects.slider_car_speed, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

      lv_event_send(guiObjects.slider_car_speed, LV_EVENT_VALUE_CHANGED, NULL); /* set an event to update the value */
    }

    {
      /* Create a drop down list for the car settings */
      lv_obj_t *dd = lv_dropdown_create(panel_car);
      lv_dropdown_set_options(dd,
          MY_SYMBOL_ARROW_UP "\n"
          MY_SYMBOL_ARROW_DOWN "\n"
          MY_SYMBOL_ARROW_LEFT_RIGHT);
      lv_obj_set_width(dd, 40);
      lv_obj_set_height(dd, 20);
      lv_obj_set_pos(dd, 0, 23);
      lv_dropdown_set_selected(dd, Road_GetMode());

      lv_obj_add_style(dd, &guiObjects.style_customFont, LV_PART_MAIN); /* assign custom font */

      /* assign font to the list of items, when drop-down is open */
      lv_obj_t *list;
      list = lv_dropdown_get_list(dd); /* get the list */
      lv_obj_add_style(list, &guiObjects.style_customFont, LV_PART_MAIN); /* assign custom font */

      lv_obj_add_event_cb(dd, event_handler_drop_down_car, LV_EVENT_ALL, NULL);
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(dd);
    #endif
    }
  }

#if PL_CONFIG_USE_LIGHTS
  {
    #define SLIDER_RGB_WIDHT  (43)
    lv_obj_t *panel_light;
    panel_light = lv_obj_create(lv_scr_act());
    lv_obj_align_to(panel_light, panel_car, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_obj_set_size(panel_light, 120, 60);
    lv_obj_add_flag(panel_light, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    /* label, switch and slider for the light */
    {
      guiObjects.label_light_switch = lv_label_create(panel_light);
      lv_obj_set_pos(guiObjects.label_light_switch, 0, 0);
      lv_obj_add_style(guiObjects.label_light_switch, &guiObjects.style_customFont, 0);
      lv_label_set_text(guiObjects.label_light_switch, Lights_GetLightIsOn() ? MY_SYMBOL_LIGHT : MY_SYMBOL_X);

      lv_obj_t *sw_light;
      sw_light = lv_switch_create(panel_light);
      lv_obj_add_flag(sw_light, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE);
      lv_obj_align_to(sw_light, guiObjects.label_light_switch, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
      if (Lights_GetLightIsOn()) {
        lv_obj_add_state(sw_light, LV_STATE_CHECKED);
      }
      lv_obj_add_event_cb(sw_light, event_handler_switch_lights, LV_EVENT_VALUE_CHANGED, NULL);
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(sw_light);
    #endif

      /* slider for light brightness */
      guiObjects.slider_light_brightness = lv_slider_create(panel_light);
      lv_obj_add_flag(guiObjects.slider_light_brightness, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE);
      lv_obj_align_to(guiObjects.slider_light_brightness, sw_light, LV_ALIGN_OUT_RIGHT_MID, 7, 0);
      lv_obj_set_width(guiObjects.slider_light_brightness, 38);
      lv_slider_set_range(guiObjects.slider_light_brightness, 1, 100);
      lv_obj_set_style_bg_color(guiObjects.slider_light_brightness, lv_color_white(), LV_PART_KNOB|LV_STATE_FOCUS_KEY); /* make knob white if selected */
      lv_slider_set_value(guiObjects.slider_light_brightness, Lights_GetLightIsOn()?Lights_GetBrightnessPercent():0, LV_ANIM_ON);
      lv_obj_add_event_cb(guiObjects.slider_light_brightness, event_handler_slider_light_brightness, LV_EVENT_VALUE_CHANGED, NULL);

      /* Create a label right of the slider */
      guiObjects.label_slider_brightness = lv_label_create(panel_light);
      lv_label_set_text(guiObjects.label_slider_brightness, "0%");
      lv_obj_align_to(guiObjects.label_slider_brightness, guiObjects.slider_light_brightness, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
      lv_event_send(guiObjects.slider_light_brightness, LV_EVENT_VALUE_CHANGED, NULL); /* set an event to update the value */
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(guiObjects.slider_light_brightness);
    #endif
    }

    /* slider for red color */
    lv_obj_t *label_red; /* label for color */
    {
      label_red = lv_label_create(panel_light);
      lv_label_set_text(label_red, "R");
      lv_obj_align_to(label_red, guiObjects.label_light_switch, LV_ALIGN_OUT_BOTTOM_LEFT, 8, -4);

      guiObjects.slider_color_red = lv_slider_create(panel_light);
      lv_obj_add_flag(guiObjects.slider_color_red, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE);
      lv_obj_set_width(guiObjects.slider_color_red, SLIDER_RGB_WIDHT);
      lv_obj_align_to(guiObjects.slider_color_red, label_red, LV_ALIGN_OUT_RIGHT_MID, 8, 0);
      lv_slider_set_range(guiObjects.slider_color_red, 0, 100);
      lv_obj_set_style_bg_color(guiObjects.slider_color_red, lv_color_white(), LV_PART_KNOB|LV_STATE_FOCUS_KEY); /* make knob white if selected */
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(guiObjects.slider_color_red);
    #endif

      uint32_t color;
      if (Lights_GetLightIsOn()) {
        color = NEO_SPLIT_R(Lights_GetColor()); /* this is 0-0xff */
        color = McuUtility_map(color, 0, 0xff, 0, 100);
      } else {
        color = 0;
      }
      lv_slider_set_value(guiObjects.slider_color_red, color, LV_ANIM_ON);
      lv_obj_add_event_cb(guiObjects.slider_color_red, event_handler_slider_light_color_red, LV_EVENT_VALUE_CHANGED, NULL);

      /* Create a % label right of the slider */
      guiObjects.label_slider_color_red = lv_label_create(panel_light);
      lv_label_set_text(guiObjects.label_slider_color_red, "0%");
      lv_obj_align_to(guiObjects.label_slider_color_red, guiObjects.slider_color_red, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
      lv_event_send(guiObjects.slider_color_red, LV_EVENT_VALUE_CHANGED, NULL); /* set an event to update the value */
    }

    /* slider for green color */
    lv_obj_t *label_green; /* label for color */
    {
      label_green = lv_label_create(panel_light);
      lv_label_set_text(label_green, "G");
      lv_obj_align_to(label_green, label_red, LV_ALIGN_OUT_BOTTOM_LEFT, 0, -4);
      guiObjects.slider_color_green = lv_slider_create(panel_light);
      lv_obj_add_flag(guiObjects.slider_color_green, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE);
      lv_obj_set_width(guiObjects.slider_color_green, SLIDER_RGB_WIDHT);
      lv_obj_align_to(guiObjects.slider_color_green, label_green, LV_ALIGN_OUT_RIGHT_MID, 7, 0);
      lv_slider_set_range(guiObjects.slider_color_green, 0, 100);
      lv_obj_set_style_bg_color(guiObjects.slider_color_green, lv_color_white(), LV_PART_KNOB|LV_STATE_FOCUS_KEY); /* make knob white if selected */
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(guiObjects.slider_color_green);
    #endif

      uint32_t color;
      if (Lights_GetLightIsOn()) {
        color = NEO_SPLIT_G(Lights_GetColor());
        color = McuUtility_map(color, 0, 0xff, 0, 100);
      } else {
        color = 0;
      }
      lv_slider_set_value(guiObjects.slider_color_green, color, LV_ANIM_ON);
      lv_obj_add_event_cb(guiObjects.slider_color_green, event_handler_slider_light_color_green, LV_EVENT_VALUE_CHANGED, NULL);

      /* Create a % label right of the slider */
      guiObjects.label_slider_color_green = lv_label_create(panel_light);
      lv_label_set_text(guiObjects.label_slider_color_green, "0%");
      lv_obj_align_to(guiObjects.label_slider_color_green, guiObjects.slider_color_green, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
      lv_event_send(guiObjects.slider_color_green, LV_EVENT_VALUE_CHANGED, NULL); /* set an event to update the value */
    }

    /* slider for blue color */
    lv_obj_t *label_blue; /* label for color */
    {
      label_blue = lv_label_create(panel_light);
      lv_label_set_text(label_blue, "B");
      lv_obj_align_to(label_blue, label_green, LV_ALIGN_OUT_BOTTOM_LEFT, 0, -4);

      guiObjects.slider_color_blue = lv_slider_create(panel_light);
      lv_obj_add_flag(guiObjects.slider_color_blue, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_EVENT_BUBBLE);
      lv_obj_set_width(guiObjects.slider_color_blue, SLIDER_RGB_WIDHT);
      lv_obj_align_to(guiObjects.slider_color_blue, label_blue, LV_ALIGN_OUT_RIGHT_MID, 7, 0);
      lv_slider_set_range(guiObjects.slider_color_blue, 0, 100);
      lv_obj_set_style_bg_color(guiObjects.slider_color_blue, lv_color_white(), LV_PART_KNOB|LV_STATE_FOCUS_KEY); /* make knob white if selected */
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_AddObjToGroup(guiObjects.slider_color_blue);
    #endif

      uint32_t color;
      if (Lights_GetLightIsOn()) {
        color = NEO_SPLIT_B(Lights_GetColor());
        color = McuUtility_map(color, 0, 0xff, 0, 100);
      } else {
        color = 0;
      }
      lv_slider_set_value(guiObjects.slider_color_blue, color, LV_ANIM_ON);
      lv_obj_add_event_cb(guiObjects.slider_color_blue, event_handler_slider_light_color_blue, LV_EVENT_VALUE_CHANGED, NULL);

      /* Create a label right of slider */
      guiObjects.label_slider_color_blue = lv_label_create(panel_light);
      lv_label_set_text(guiObjects.label_slider_color_blue, "0%");
      lv_obj_align_to(guiObjects.label_slider_color_blue, guiObjects.slider_color_blue, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
      lv_event_send(guiObjects.slider_color_blue, LV_EVENT_VALUE_CHANGED, NULL); /* set an event to update the value */
    }
  }
#endif /* PL_CONFIG_USE_LIGHTS */
}

/* ------------------------------------------------------- creating main screen/menu ----------------------------------------------- */
static void Gui_Create(void) {
 #if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
#endif
  /* create window */
  //lv_obj_t *gui_win;
  //gui_win = lv_win_create(lv_scr_act(), NULL);
  //lv_win_set_title(gui_win, "Main Menu");
  //lv_win_set_btn_size(gui_win, 15);
  //lv_win_set_sb_mode(gui_win, LV_SB_MODE_OFF); /* no scroll bar */

  //lv_example_text();
  //lv_example_button();
  //lv_example_slider();
  //lv_example_bar();
  //lv_ex_checkbox_1(); /* \todo reduce size of box */
  //lv_example_checkbox_1(); /* \todo how to highlight currently selected one? */
  //lv_example_radiobuttons_2();
  //lv_example_textarea_1();
  //lv_example_arc_1(); /* \todo label is not shown? */
  //lv_example_dropdown_1();
  //lv_example_switch_1();
  //lv_example_line_1();
  //lv_example_img_1();
  //lv_example_roller_1();
  createGUI();
}

typedef enum GuiState_e {
  GUI_STATE_IDLE,                   /* idle mode */
  GUI_STATE_SHOW_SETTINGS,          /* show settings screen */
  GUI_STATE_START_CYCLING_SCREEN,   /* start the cycling screens */
  GUI_STATE_SHOW_CYCLING_SCREEN,    /* show cycling screens */
  GUI_STATE_IDLE_CYCLING_SCREEN,    /* idle between screen cycling */
  GUI_STATE_ENTER_SCREEN_SAVER,     /* enter screen saver mode */
  GUI_STATE_ACTIVE_SCREEN_SAVER,    /* screen saver running */
  GUI_STATE_EXIT_SCREEN_SAVER,      /* exit screen saver mode */
} GuiState_e;

static void GuiTask(void *pv) {
  GuiScreens_e currScreen = GUI_SCREEN_SETTINGS;
  int turnDisplayOffTimeout = GUI_CONFIG_NOF_SCREEN_CYCLING_UNTIL_DISPLAY_OFF;
  bool screenSaverIsOn = false;
  GuiState_e state = GUI_STATE_SHOW_SETTINGS;
  BaseType_t res;
  uint32_t notifcationValue;

  (void)pv; /* not used */
  vTaskDelay(pdMS_TO_TICKS(500)); /* give hardware time to power up */
  McuSSD1306_Init(); /* requires I2C interrupts enabled if using HW I2C! */
  McuSSD1306_Clear();
  Gui_Create();
  lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]);
  for(;;) {
    /* handle notification events */
    res = xTaskNotifyWait(0UL, /* pre-clear flags */
        GUI_TASK_NOTIFY_BUTTON_PRESSED|GUI_TASK_NOTIFY_GUI_TIMEOUT|GUI_TASK_NOTIFY_NEXT_SCREEN, /* flags to check */
        &notifcationValue, /* where to store the bits */
        pdMS_TO_TICKS(20) /* timeout */
    );
    if (res==pdTRUE) { /* received notification */
      if (notifcationValue&GUI_TASK_NOTIFY_BUTTON_PRESSED) { /* user pressed a button */
        switch(state) {
          case GUI_STATE_START_CYCLING_SCREEN:
          case GUI_STATE_IDLE_CYCLING_SCREEN:
          case GUI_STATE_SHOW_CYCLING_SCREEN: /* button press during cycling screens: show settings */
            if (xTimerIsTimerActive(timerHndlCycleScreens)==pdTRUE) { /* cycling screens active? */
              if (xTimerStop(timerHndlCycleScreens, pdMS_TO_TICKS(10))!=pdPASS) {
                McuLog_fatal("failed stopping timer");
                for(;;); /* failure!?! */
              }
            }
            state = GUI_STATE_SHOW_SETTINGS;
            break;

          case GUI_STATE_ACTIVE_SCREEN_SAVER: /* button press during screen saver: turn on display and show settings */
            state = GUI_STATE_EXIT_SCREEN_SAVER;
            break;

          default:
            break;
        } /* switch */
      } /* if */
      if (notifcationValue&GUI_TASK_NOTIFY_GUI_TIMEOUT) { /* no user action or button press for some time */
        switch(state) {
          case GUI_STATE_IDLE:
            state = GUI_STATE_START_CYCLING_SCREEN;
            break;

          default:
             break;
        } /* switch */
      } /* if */
      if (notifcationValue&GUI_TASK_NOTIFY_NEXT_SCREEN) { /* request to cycle to next screen */
        switch(state) {
          case GUI_STATE_IDLE:
            state = GUI_STATE_START_CYCLING_SCREEN;
            break;
          case GUI_STATE_SHOW_CYCLING_SCREEN:
          case GUI_STATE_IDLE_CYCLING_SCREEN:
            currScreen++;
            if (currScreen>=sizeof(guiObjects.screens)/sizeof(guiObjects.screens[0])) { /* reached the end of the list */
              currScreen = GUI_SCREEN_LOGO_VHS;
              turnDisplayOffTimeout--; /* count the iteration */
            }
            if (currScreen==GUI_SCREEN_SETTINGS) {
              currScreen++; /* skip settings screen */
            }
            if (turnDisplayOffTimeout<=0) {
              state = GUI_STATE_ENTER_SCREEN_SAVER;
            } else {
              state = GUI_STATE_SHOW_CYCLING_SCREEN;
            }
            break;

          default:
             break;
        } /* switch */
      } /* if */
    } /* if notification received */

    switch(state) {
      case GUI_STATE_IDLE:
        break;

      case GUI_STATE_SHOW_SETTINGS:
        lv_scr_load(guiObjects.screens[GUI_SCREEN_SETTINGS]); /* show settings screen */
        state = GUI_STATE_IDLE;
        break;

      case GUI_STATE_START_CYCLING_SCREEN:
        currScreen = GUI_SCREEN_LOGO_VHS;
        turnDisplayOffTimeout = GUI_CONFIG_NOF_SCREEN_CYCLING_UNTIL_DISPLAY_OFF;
        if (xTimerStart(timerHndlCycleScreens, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed starting timer");
          for(;;); /* failure!?! */
        }
        state = GUI_STATE_SHOW_CYCLING_SCREEN;
        break;

      case GUI_STATE_SHOW_CYCLING_SCREEN:
        lv_scr_load(guiObjects.screens[currScreen]);
        state = GUI_STATE_IDLE_CYCLING_SCREEN;
        break;

      case GUI_STATE_IDLE_CYCLING_SCREEN:
        break;

      case GUI_STATE_ENTER_SCREEN_SAVER:
        McuSSD1306_DisplayOn(false); /* turn off */
        /* stop all timers */
        if (xTimerStop(timerHndlGuiExpired, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed stopping timer");
          for(;;); /* failure!?! */
        }
        if (xTimerStop(timerHndlCycleScreens, pdMS_TO_TICKS(10))!=pdPASS) {
          McuLog_fatal("failed stopping timer");
          for(;;); /* failure!?! */
        }
        state = GUI_STATE_ACTIVE_SCREEN_SAVER;
        break;

      case GUI_STATE_ACTIVE_SCREEN_SAVER:
        break;

      case GUI_STATE_EXIT_SCREEN_SAVER:
        McuSSD1306_DisplayOn(true); /* turn display on */
        state = GUI_STATE_SHOW_SETTINGS;
        break;

      default:
        break;
    } /* switch */
    LV_Task(); /* call this every 1-20 ms */
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

static void StartOrResetGuiTimeoutTimer(void) {
  if (xTimerIsTimerActive(timerHndlGuiExpired)==pdFALSE) {
    /* timer is not active: start it */
    if (xTimerStart(timerHndlGuiExpired, pdMS_TO_TICKS(10))!=pdPASS) {
      McuLog_fatal("failed starting timer");
      for(;;); /* failure!?! */
    }
  } else {
    if (xTimerReset(timerHndlGuiExpired, pdMS_TO_TICKS(10))!=pdPASS) { /* reset timer, e.g. after key press or user input */
      McuLog_fatal("failed resetting timer");
      for(;;); /* failure?!? */
    }
  }
}

void GUI_NotifyUserAction(void) {
  /* called for each key press or user action. */
  StartOrResetGuiTimeoutTimer();
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_BUTTON_PRESSED, eSetBits);
}

static void vTimerCallbackGuiExpired(TimerHandle_t pxTimer) {
  (void)pxTimer; /* not used */
  /* start cycling screen timer */
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_GUI_TIMEOUT, eSetBits);
}

static void vTimerCallbackCycleScreen(TimerHandle_t pxTimer) {
  (void)pxTimer; /* not used */
  (void)xTaskNotify(GUI_TaskHndl, GUI_TASK_NOTIFY_NEXT_SCREEN, eSetBits);
}

void GUI_Init(void) {
  LV_Init(); /* initialize GUI library */
  if (xTaskCreate(GuiTask, "Gui", 3*1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
    for(;;){} /* error */
  }

  /* create a timer to timeout user actions */
  timerHndlGuiExpired = xTimerCreate(
    "guiExpired", /* name */
    pdMS_TO_TICKS(GUI_CONFIG_TIMEOUT_USER_ACTION_SEC*1000), /* period/time */
    pdFALSE, /* one-shot, no auto reload */
    (void*)1, /* timer ID */
    vTimerCallbackGuiExpired); /* callback */
  if (timerHndlGuiExpired==NULL) {
    McuLog_fatal("failed creating timer");
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndlGuiExpired, 0)!=pdPASS) {
    McuLog_fatal("failed starting timer");
    for(;;); /* failure!?! */
  }

  /* timer for screen cycling */
  timerHndlCycleScreens = xTimerCreate(
    "cycleScreen", /* name */
    pdMS_TO_TICKS(GUI_CONFIG_SCREEN_CYLCING_INTERVAL_SEC*1000), /* period/time */
    pdTRUE, /* do auto reload */
    (void*)1, /* timer ID */
    vTimerCallbackCycleScreen); /* callback */
  if (timerHndlCycleScreens==NULL) {
    McuLog_fatal("failed creating timer");
    for(;;); /* failure! */
  }
}
#endif /* PL_CONFIG_HAS_GUI */
