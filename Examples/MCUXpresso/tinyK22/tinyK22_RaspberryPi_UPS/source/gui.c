/*
 * gui.c
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */
#include "platform.h"
#if PL_CONFIG_USE_LVGL

#include "gui.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuRTOS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "KeyDebounce.h"
#include "McuSSD1306.h"
//#include "gui_mainmenu.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "Trigger.h"
#include "Event.h"

static TaskHandle_t GUI_TaskHndl;

/* task notification bits */
#define GUI_SET_ORIENTATION_LANDSCAPE    (1<<0)
#define GUI_SET_ORIENTATION_LANDSCAPE180 (1<<1)
#define GUI_SET_ORIENTATION_PORTRAIT     (1<<2)
#define GUI_SET_ORIENTATION_PORTRAIT180  (1<<3)

#if PL_CONFIG_HAS_GUI_KEY_NAV
#define GUI_GROUP_NOF_IN_STACK   4
typedef struct {
  lv_group_t *stack[GUI_GROUP_NOF_IN_STACK]; /* stack of GUI groups */
  uint8_t sp; /* stack pointer, points to next free element */
} GUI_Group_t;
static GUI_Group_t groups;

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

void GUI_AddObjToGroup(lv_obj_t *obj) {
  lv_group_add_obj(GUI_GroupPeek(), obj);
}

void GUI_RemoveObjFromGroup_(lv_obj_t *obj) {
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
  lv_group_set_style_mod_cb(gui_group, style_mod_cb);
  groups.stack[groups.sp] = gui_group;
  groups.sp++;
}

#endif /* PL_CONFIG_HAS_GUI_KEY_NAV */

void GUI_ChangeOrientation(McuSSD1306_DisplayOrientation orientation) {
  switch(orientation) {
    case McuSSD1306_ORIENTATION_LANDSCAPE:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_LANDSCAPE, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_LANDSCAPE180:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_LANDSCAPE180, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_PORTRAIT:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_PORTRAIT, eSetBits);
      break;
    case McuSSD1306_ORIENTATION_PORTRAIT180:
      (void)xTaskNotify(GUI_TaskHndl, GUI_SET_ORIENTATION_PORTRAIT180, eSetBits);
      break;
    default:
      break;
  }
}

static lv_res_t btn_click_action(lv_obj_t *btn) {
   // uint8_t id = lv_obj_get_free_num(btn);
   // printf("Button %d is released\n", id);
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t Btn_Accel_click_action(struct _lv_obj_t *obj) {
  //  GUI_ACCEL_Create();
    return LV_RES_OK;
}

void GUI_MainMenuCreate(void) {
  lv_obj_t *gui_win;

  GUI_GroupPush();
  /* create window */
  gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");
  lv_win_set_btn_size(gui_win, 8);

  /* Make the window content responsive */
  //lv_win_set_layout(gui_win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */
#if 1
  /*Create a normal button*/
  lv_obj_t *btn1;
  lv_obj_t *label1;

  btn1 = lv_btn_create(gui_win, NULL);
  lv_obj_set_pos(btn1, 10, 5);
  lv_obj_set_size(btn1, 40, 30);
  //lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
//  lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  label1 = lv_label_create(btn1, NULL);
  lv_label_set_text(label1, "Btn1");
  //lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);
  GUI_AddObjToGroup(btn1);

  lv_obj_t *btn2;
  lv_obj_t *label2;

  btn2 = lv_btn_create(gui_win, NULL);
  lv_obj_set_pos(btn2, 40, 5);
  lv_obj_set_size(btn2, 30, 20);
  //lv_cont_set_fit(btn2, true, true); /*Enable resizing horizontally and vertically*/
//  lv_obj_align(btn2, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  label2 = lv_label_create(btn2, NULL);
  lv_label_set_text(label2, "222");
  //lv_obj_set_free_num(btn2, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);
  GUI_AddObjToGroup(btn2);
#endif

#if 0
  /* create list of objects */
  lv_obj_t *list1;
  lv_obj_t *obj;

  list1 = lv_list_create(gui_win, NULL);
  /*Add list elements*/

//  obj = lv_list_add(list1, SYMBOL_FILE, "About", Btn_About_click_action);
//  GUI_AddObjToGroup(obj);
#if 1 || PL_CONFIG_HAS_MMA8451
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
  lv_obj_set_size(list1, 100, 40); /* fixed size */
#endif
}

#if PL_CONFIG_HAS_KEYS
static void btnCallback(EVNT_Handle event) {
  switch(event) {
    case EVNT_SW1_PRESSED:
      LV_ButtonEvent(LV_HW_BTN_LEFT, LV_MASK_PRESSED);
      break;
    case EVNT_SW1_RELEASED:
      LV_ButtonEvent(LV_HW_BTN_LEFT, LV_MASK_RELEASED);
      break;
    case EVNT_SW1_LPRESSED:
      LV_ButtonEvent(LV_HW_BTN_LEFT, LV_MASK_PRESSED_LONG);
      break;
    case EVNT_SW1_LRELEASED:
      LV_ButtonEvent(LV_HW_BTN_LEFT, LV_MASK_RELEASED_LONG);
      break;

    case EVNT_SW2_PRESSED:
      LV_ButtonEvent(LV_HW_BTN_RIGHT, LV_MASK_PRESSED);
      break;
    case EVNT_SW2_RELEASED:
      LV_ButtonEvent(LV_HW_BTN_RIGHT, LV_MASK_RELEASED);
      break;
    case EVNT_SW2_LPRESSED:
      LV_ButtonEvent(LV_HW_BTN_RIGHT, LV_MASK_PRESSED_LONG);
      break;
    case EVNT_SW2_LRELEASED:
      LV_ButtonEvent(LV_HW_BTN_RIGHT, LV_MASK_RELEASED_LONG);
      break;

    case EVNT_SW3_PRESSED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_PRESSED);
      break;
    case EVNT_SW3_RELEASED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_RELEASED);
      break;
    case EVNT_SW3_LPRESSED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_PRESSED_LONG);
      break;
    case EVNT_SW3_LRELEASED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_RELEASED_LONG);
      break;

    case EVNT_SW4_PRESSED:
      LV_ButtonEvent(LV_HW_BTN_UP, LV_MASK_PRESSED);
      break;
    case EVNT_SW4_RELEASED:
      LV_ButtonEvent(LV_HW_BTN_UP, LV_MASK_RELEASED);
      break;
    case EVNT_SW4_LPRESSED:
      LV_ButtonEvent(LV_HW_BTN_UP, LV_MASK_PRESSED_LONG);
      break;
    case EVNT_SW4_LRELEASED:
      LV_ButtonEvent(LV_HW_BTN_UP, LV_MASK_RELEASED_LONG);
      break;

    case EVNT_SW5_PRESSED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_PRESSED);
      break;
    case EVNT_SW5_RELEASED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_RELEASED);
      break;
    case EVNT_SW5_LPRESSED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_PRESSED_LONG);
      break;
    case EVNT_SW5_LRELEASED:
      LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_RELEASED_LONG);
      break;
    default:
      break;
  }
}
#endif

static void GuiTask(void *p) {
  uint32_t notifcationValue;

  vTaskDelay(pdMS_TO_TICKS(500)); /* give hardware time to power up */
  //LCD1_Init();
  GUI_MainMenuCreate();
  for(;;) {
    (void)xTaskNotifyWait(0UL, GUI_SET_ORIENTATION_LANDSCAPE|GUI_SET_ORIENTATION_LANDSCAPE180|GUI_SET_ORIENTATION_PORTRAIT|GUI_SET_ORIENTATION_PORTRAIT180, &notifcationValue, 0); /* check flags */
    if (notifcationValue!=0) {
      lv_area_t area;

      if (notifcationValue&GUI_SET_ORIENTATION_LANDSCAPE) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
        lv_refr_now();
      } else if (notifcationValue&GUI_SET_ORIENTATION_LANDSCAPE180) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE180);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
      } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
      } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT180) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT180);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(&area);
        lv_obj_invalidate(lv_scr_act());
      }
    }
    LV_Task(); /* call this every 1-20 ms */
#if PL_CONFIG_HAS_KEYS
    KEYDBNC_Process();
    EVNT_HandleEvent(btnCallback, true);
#endif
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

#define APP_PERIODIC_TIMER_PERIOD_MS   10
static TimerHandle_t timerHndl;

static void vTimerCallbackExpired(TimerHandle_t pxTimer) {
  lv_tick_inc(APP_PERIODIC_TIMER_PERIOD_MS);
  TRG_AddTick();
}

void GUI_Init(void) {
  LV_Init(); /* initialize GUI library */
  //lv_theme_set_current(lv_theme_night_init(128, NULL));
  //lv_theme_set_current(lv_theme_alien_init(128, NULL));
  //lv_theme_set_current(lv_theme_default_init(128, NULL));
  //lv_theme_set_current(lv_theme_material_init(128, NULL));
  lv_theme_set_current(lv_theme_mono_init(128, NULL));
  //lv_theme_set_current(lv_theme_zen_init(128, NULL));
  //lv_theme_set_current(lv_theme_nemo_init(128, NULL));

  //lv_theme_t *th = lv_theme_get_current();
	/* change default button style */
  // lv_style_btn_rel.body.radius = LV_DPI / 15;
  // lv_style_btn_rel.body.padding.hor = LV_DPI / 8;
  // lv_style_btn_rel.body.padding.ver = LV_DPI / 12;

  if (xTaskCreate(GuiTask, "Gui", 2000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
    for(;;){} /* error */
  }
  timerHndl = xTimerCreate(
        "timer", /* name */
        pdMS_TO_TICKS(APP_PERIODIC_TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackExpired); /* callback */
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) { /* start the timer */
    for(;;); /* failure!?! */
  }
#if PL_CONFIG_HAS_GUI_KEY_NAV
  groups.sp = 0;
#endif
}
#endif /* PL_CONFIG_HAS_GUI */
