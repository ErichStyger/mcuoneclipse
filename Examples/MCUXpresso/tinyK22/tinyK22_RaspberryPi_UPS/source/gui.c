/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_GUI

#include "gui.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuRTOS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "oled.h"
#include "McuSSD1306.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuUtility.h"
#if PL_CONFIG_USE_SHUTDOWN
  #include "shutdown.h"
#endif
#if (PL_CONFIG_USE_SHT31 || PL_CONFIG_USE_SHT40)
  #include "gui_tempHum.h"
#endif
#if PL_CONFIG_USE_UPS
  #include "gui_ups.h"
#endif
#if PL_CONFIG_USE_GATEWAY
  #include "gui_uart.h"
  #include "RaspyUART.h"
#endif

static TaskHandle_t GUI_TaskHndl;

/* task notification bits */
#define GUI_SET_ORIENTATION_LANDSCAPE    (1<<0)
#define GUI_SET_ORIENTATION_LANDSCAPE180 (1<<1)
#define GUI_SET_ORIENTATION_PORTRAIT     (1<<2)
#define GUI_SET_ORIENTATION_PORTRAIT180  (1<<3)

#if PL_CONFIG_USE_GUI_KEY_NAV
#define GUI_GROUP_NOF_IN_STACK   4
typedef struct GUI_Group_t {
  lv_group_t *stack[GUI_GROUP_NOF_IN_STACK]; /* stack of GUI groups */
  uint8_t sp; /* stack pointer, points to next free element */
} GUI_Group_t;
static GUI_Group_t groups;

/* style modification callback for the focus of an element */
static void style_mod_cb(struct _lv_group_t *grp, lv_style_t *style) {
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
#endif /* PL_CONFIG_USE_GUI_KEY_NAV */

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

#if PL_CONFIG_USE_UPS
static void btn_click_ups_action(struct _lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    GUI_UPS_CreateView();
  }
}
#endif

#if PL_CONFIG_USE_GATEWAY
static void btn_click_uart_action(struct _lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    GUI_UART_CreateView();
  }
}
#endif

#if (PL_CONFIG_USE_SHT31 || PL_CONFIG_USE_SHT40)
static void btn_click_sht_action(struct _lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    GUI_TEMPHUM_CreateView();
  }
}
#endif

#if PL_CONFIG_USE_SHUTDOWN
static lv_obj_t *mboxShutdown, *mboxShutdownWait;

static void mbox_shutdownWait_apply_action(lv_obj_t *mbox, lv_event_t event) {
  if (event == LV_EVENT_DELETE && mbox==mboxShutdownWait) {
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_GroupPull();
    #endif
      mboxShutdownWait = NULL;
  } else if (event == LV_EVENT_VALUE_CHANGED) {
    const char *txt = lv_mbox_get_active_btn_text(mbox);
    if (McuUtility_strcmp(txt, "\221OK")==0) {
      lv_obj_del(mboxShutdownWait);
      mboxShutdownWait = NULL;
    }
  }
}

static void Btn_shutdown_CreateWaitBox(void) {
  mboxShutdownWait = lv_mbox_create(lv_scr_act(), NULL);
#if PL_CONFIG_USE_POWER_DOWN_RED_LED
  lv_mbox_set_text(mboxShutdownWait, "Shutdown in progress. Wait for RED LED.");  /* Set the text */
#else
  lv_mbox_set_text(mboxShutdownWait, "Shutdown in progress.");  /* Set the text */
#endif
  /*Add OK button*/
  static const char * btns[] ={"\221OK", ""}; /*Button description. '\221' lv_btnm like control char*/
  lv_mbox_add_btns(mboxShutdownWait, btns);
  lv_obj_set_event_cb(mboxShutdownWait, mbox_shutdownWait_apply_action);
  lv_obj_set_width(mboxShutdownWait, 100);
  lv_obj_align(mboxShutdownWait, lv_scr_act(), LV_ALIGN_CENTER, 0, 0); /*Align to center */

#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
  GUI_AddObjToGroup(mboxShutdownWait);
#endif
  lv_group_focus_obj(mboxShutdownWait);
}

static void mbox_shutdown_apply_action(lv_obj_t *mbox, lv_event_t event) {
  if (event == LV_EVENT_DELETE && mbox==mboxShutdown) {
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_GroupPull();
    #endif
      mboxShutdown = NULL;
  } else if (event == LV_EVENT_VALUE_CHANGED) {
    const char *txt = lv_mbox_get_active_btn_text(mbox);
    if (McuUtility_strcmp(txt, "\221Yes")==0) {
      SHUTDOWN_RequestPowerOff(); /* request shutdown to Linux */
      Btn_shutdown_CreateWaitBox();
    } else if (McuUtility_strcmp(txt, "\221Cancel")==0) {
      lv_obj_del(mboxShutdown);
    }
  }
}

static void btn_click_shutdown_action(struct _lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    mboxShutdown = lv_mbox_create(lv_scr_act(), NULL);
    lv_mbox_set_text(mboxShutdown, "Shutdown Raspy?");  /*Set the text*/
    /*Add two buttons*/
    static const char * btns[] ={"\221Yes", "\221Cancel", ""}; /*Button description. '\221' lv_btnm like control char*/
    lv_mbox_add_btns(mboxShutdown, btns);
    lv_obj_set_event_cb(mboxShutdown, mbox_shutdown_apply_action);
    lv_obj_set_width(mboxShutdown, 100);
    lv_obj_align(mboxShutdown, lv_scr_act(), LV_ALIGN_CENTER, 0, 0); /*Align to center */

  #if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_GroupPush();
    GUI_AddObjToGroup(mboxShutdown);
  #endif
    lv_group_focus_obj(mboxShutdown);
  }
}
#endif /* PL_CONFIG_USE_SHUTDOWN */

#if PL_CONFIG_USE_POWER_ON
static lv_obj_t *mboxPoweron, *mboxPoweronWait;

static void mbox_poweronWait_apply_action(lv_obj_t *mbox, lv_event_t event) {
  if (event == LV_EVENT_DELETE && mbox==mboxPoweronWait) {
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_GroupPull();
    #endif
      mboxPoweronWait = NULL;
  } else if (event == LV_EVENT_VALUE_CHANGED) {
    const char *txt = lv_mbox_get_active_btn_text(mbox);
    if (McuUtility_strcmp(txt, "\221OK")==0) {
      lv_obj_del(mboxPoweronWait);
    }
  }
}

static void Btn_poweron_CreateWaitBox(void) {
  mboxPoweronWait = lv_mbox_create(lv_scr_act(), NULL);
  lv_mbox_set_text(mboxPoweronWait, "Poweron in progress.");  /* Set the text */
  /*Add OK button*/
  static const char * btns[] ={"\221OK", ""}; /*Button description. '\221' lv_btnm like control char*/
  lv_mbox_add_btns(mboxPoweronWait, btns);
  lv_obj_set_event_cb(mboxPoweronWait, mbox_poweronWait_apply_action);
  lv_obj_set_width(mboxPoweronWait, 100);
  lv_obj_align(mboxPoweronWait, lv_scr_act(), LV_ALIGN_CENTER, 0, 0); /*Align to center */

#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
  GUI_AddObjToGroup(mboxPoweronWait);
#endif
  lv_group_focus_obj(mboxPoweronWait);
}

static void mbox_poweron_apply_action(lv_obj_t *mbox, lv_event_t event) {
  if (event == LV_EVENT_DELETE && mbox==mboxPoweron) {
    #if PL_CONFIG_USE_GUI_KEY_NAV
      GUI_GroupPull();
    #endif
      mboxPoweron = NULL;
  } else if (event == LV_EVENT_VALUE_CHANGED) {
    const char *txt = lv_mbox_get_active_btn_text(mbox);
    if (McuUtility_strcmp(txt, "\221Yes")==0) {
      SHUTDOWN_RequestPowerOn(); /* request power-on to Linux */
      Btn_poweron_CreateWaitBox();
    } else if (McuUtility_strcmp(txt, "\221Cancel")==0) {
      lv_obj_del(mboxPoweron);
    }
  }
}

static void btn_click_poweron_action(struct _lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    mboxPoweron = lv_mbox_create(lv_scr_act(), NULL);
    lv_mbox_set_text(mboxPoweron, "Poweron Raspy?");  /*Set the text*/
    /*Add two buttons*/
    static const char * btns[] ={"\221Yes", "\221Cancel", ""}; /*Button description. '\221' lv_btnm like control char*/
    lv_mbox_add_btns(mboxPoweron, btns);
    lv_obj_set_event_cb(mboxPoweron, mbox_poweron_apply_action);
    lv_obj_set_width(mboxPoweron, 100);
    lv_obj_align(mboxPoweron, lv_scr_act(), LV_ALIGN_CENTER, 0, 0); /*Align to center */

#if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_GroupPush();
    GUI_AddObjToGroup(mboxPoweron);
#endif
    lv_group_focus_obj(mboxPoweron);
  }
}

#endif /* #if PL_CONFIG_USE_POWER_ON */

void GUI_MainMenuCreate(void) {
  lv_obj_t *gui_win;
#define AUTO_POS (1) /* automatically place GUI elements */

#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_GroupPush();
#endif
  /* create window */
  gui_win = lv_win_create(lv_scr_act(), NULL);
  lv_win_set_title(gui_win, "Main Menu");
  lv_win_set_btn_size(gui_win, 15);
  lv_win_set_sb_mode(gui_win, LV_SB_MODE_OFF); /* no scroll bar */

  /* Make the window content responsive */
#if AUTO_POS
  lv_win_set_layout(gui_win, LV_LAYOUT_PRETTY); /* this will arrange the buttons */
#endif
  lv_obj_t *btn;
  lv_obj_t *label;

#if PL_CONFIG_USE_SHUTDOWN
  btn = lv_btn_create(gui_win, NULL);
#if !AUTO_POS
  lv_obj_set_size(btn, 45, 20);
  lv_obj_set_pos(btn, 5, 0);
#endif
  lv_obj_set_event_cb(btn, btn_click_shutdown_action);
  lv_btn_set_fit(btn, LV_FIT_TIGHT);

  label = lv_label_create(btn, NULL);
  lv_label_set_text(label, "Shutdown");
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif
#endif /* PL_CONFIG_USE_SHUTDOWN */

#if PL_CONFIG_USE_POWER_ON
  btn = lv_btn_create(gui_win, NULL);
  lv_obj_set_event_cb(btn, btn_click_poweron_action);
  lv_btn_set_fit(btn, LV_FIT_TIGHT);

  label = lv_label_create(btn, NULL);
  lv_label_set_text(label, "Poweron");
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif
#endif /* PL_CONFIG_USE_SHUTDOWN */

#if (PL_CONFIG_USE_SHT31 || PL_CONFIG_USE_SHT40)
  btn = lv_btn_create(gui_win, NULL);
#if !AUTO_POS
  lv_obj_set_size(btn, 40, 20);
  lv_obj_set_pos(btn, 60, 0);
#endif
  label = lv_label_create(btn, NULL);
#if PL_CONFIG_USE_SHT31
  lv_label_set_text(label, "SHT31");
#elif PL_CONFIG_USE_SHT40
  lv_label_set_text(label, "SHT40");
#else
  #error "need a sensor?"
#endif
  //lv_obj_set_free_num(btn, 1);   /*Set a unique number for the button*/
  lv_obj_set_event_cb(btn, btn_click_sht_action);
  lv_btn_set_fit(btn, LV_FIT_TIGHT);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif
#endif /* PL_CONFIG_USE_SHT31 || PL_CONFIG_USE_SHT40) */

#if PL_CONFIG_USE_UPS
  btn = lv_btn_create(gui_win, NULL);
#if !AUTO_POS
  lv_obj_set_size(btn, 40, 20);
  lv_obj_set_pos(btn, 5, 30);
#endif
  label = lv_label_create(btn, NULL);
  lv_label_set_text(label, "UPS");
  lv_obj_set_event_cb(btn, btn_click_ups_action);
  lv_btn_set_fit(btn, LV_FIT_TIGHT);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif
#endif /* PL_CONFIG_USE_UPS */

#if PL_CONFIG_USE_GATEWAY
  btn = lv_btn_create(gui_win, NULL);
#if !AUTO_POS
  lv_obj_set_size(btn, 60, 20);
  lv_obj_set_pos(btn, 5, 30);
#endif
  label = lv_label_create(btn, NULL);
  lv_label_set_text(label, "UART");
  lv_obj_set_event_cb(btn, btn_click_uart_action);
  lv_btn_set_fit(btn, LV_FIT_TIGHT);
#if PL_CONFIG_USE_GUI_KEY_NAV
  GUI_AddObjToGroup(btn);
#endif
#endif /* PL_CONFIG_USE_GATEWAY */
}

static void GuiTask(void *p) {
  uint32_t notifcationValue;

  vTaskDelay(pdMS_TO_TICKS(100)); /* give hardware time to power up */
  McuSSD1306_Init(); /* requires I2C interrupts enabled if using HW I2C! */
  McuSSD1306_SetDisplayClockDiv(0xA0); /* to increase refresh rate and reduce acoustic noise with white background */
#if TINYK22_HAT_VERSION>=4
  McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE);
#else
  McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE180);
#endif
  McuSSD1306_Clear();
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
        lv_inv_area(NULL, &area);
        lv_inv_area(NULL, &area);
      } else if (notifcationValue&GUI_SET_ORIENTATION_LANDSCAPE180) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE180);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(NULL, &area);
      } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(NULL, &area);
      } else if (notifcationValue&GUI_SET_ORIENTATION_PORTRAIT180) {
        McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_PORTRAIT180);
        area.x1 = 0;
        area.y1 = 0;
        area.x2 = McuGDisplaySSD1306_GetWidth()-1;
        area.y2 = McuGDisplaySSD1306_GetHeight()-1;
        lv_inv_area(NULL, &area);
        lv_obj_invalidate(lv_scr_act());
      }
    }
    LV_Task(); /* call this every 1-20 ms */
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

#define APP_PERIODIC_TIMER_PERIOD_MS   10
static TimerHandle_t timerHndl;

static void vTimerGuiTickCallbackExpired(TimerHandle_t pxTimer) {
  lv_tick_inc(APP_PERIODIC_TIMER_PERIOD_MS);
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

  if (xTaskCreate(GuiTask, "Gui", 3*1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, &GUI_TaskHndl) != pdPASS) {
    for(;;){} /* error */
  }
  timerHndl = xTimerCreate(  /* timer to handle periodic things */
        "guiTick", /* name */
        pdMS_TO_TICKS(APP_PERIODIC_TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerGuiTickCallbackExpired); /* callback */
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) { /* start the timer */
    for(;;); /* failure!?! */
  }
#if PL_CONFIG_USE_GUI_KEY_NAV
  groups.sp = 0;
#endif
}
#endif /* PL_CONFIG_HAS_GUI */
