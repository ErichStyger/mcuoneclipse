/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_GATEWAY && PL_CONFIG_USE_GUI
#include "gui_uart.h"
#include "LittlevGL/lvgl/lvgl.h"
#include "McuXFormat.h"
#include "gui.h"
#include "toaster.h"
#include "gateway.h"

static lv_obj_t *win;
static lv_task_t *refr_task;
#define REFR_TIME_MS   (1000)
static lv_obj_t *rxtx_label; /* label for nof rx/tx bytes */

/**
 * Called when the window's close button is clicked
 * @param btn pointer to the close button
 * @return LV_ACTION_RES_INV because the window is deleted in the function
 */
static void win_close_action(lv_obj_t *obj, lv_event_t event) {
  if (event==LV_EVENT_RELEASED) {
  #if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_GroupPull();
  #endif
    lv_obj_del(win);
    win = NULL;
    lv_task_del(refr_task);
    refr_task = NULL;
  }
}

static void cb_linuxToHost_click_action(lv_obj_t *cb, lv_event_t event) {
  if (event==LV_EVENT_VALUE_CHANGED) {
    GATEWAY_SetLinuxToHostEnabled(!GATEWAY_LinuxToHostIsEnabled()); /* toggle */
    lv_cb_set_checked(cb, GATEWAY_LinuxToHostIsEnabled());
  }
}

static void cb_hostToLinux_click_action(lv_obj_t *cb, lv_event_t event) {
  if (event==LV_EVENT_VALUE_CHANGED) {
    GATEWAY_SetHostToLinuxEnabled(!GATEWAY_HostToLinuxIsEnabled()); /* toggle */
    lv_cb_set_checked(cb, GATEWAY_HostToLinuxIsEnabled());
  }
}

static void refresh_task(struct _lv_task_t *param) {
  unsigned char buf[24];
  uint32_t rx, tx;

#if PL_CONFIG_USE_TOASTER
  if (TOASTER_IsRunning()) {
    return;
  }
#endif
  rx = GATEWAY_GetNofRx();
  tx = GATEWAY_GetNofTx();
  McuXFormat_xsnprintf((char*)buf, sizeof(buf), "Rx: %lu Tx: %lu", rx, tx);
  lv_label_set_text(rxtx_label, (char*)buf);
}

void GUI_UART_CreateView(void) {
    lv_obj_t *closeBtn;

    refr_task = lv_task_create(refresh_task, REFR_TIME_MS, LV_TASK_PRIO_LOW, NULL);
    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "UART");
    lv_win_set_btn_size(win, 15);
    closeBtn = lv_win_add_btn(win, LV_SYMBOL_CLOSE);
    lv_obj_set_event_cb(closeBtn, win_close_action);
#if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_GroupPush();
    GUI_AddObjToGroup(closeBtn);
#endif
    lv_group_focus_obj(closeBtn);

    /* checkboxes */
    lv_obj_t *cb;

    cb = lv_cb_create(win, NULL);
    lv_cb_set_text(cb, "Gateway Linux->Host");
    lv_cb_set_checked(cb, GATEWAY_LinuxToHostIsEnabled());
   //lv_obj_align(cb, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_event_cb(cb, cb_linuxToHost_click_action);
#if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_AddObjToGroup(cb);
#endif

    cb = lv_cb_create(win, NULL);
    lv_cb_set_text(cb, "Gateway Host->Linx");
    lv_cb_set_checked(cb, GATEWAY_HostToLinuxIsEnabled());
   //lv_obj_align(cb, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_event_cb(cb, cb_hostToLinux_click_action);
#if PL_CONFIG_USE_GUI_KEY_NAV
    GUI_AddObjToGroup(cb);
#endif

    rxtx_label = lv_label_create(win, NULL);
    lv_label_set_text(rxtx_label, "Rx: ???, Tx: ???");
    //lv_obj_align(rxtx_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 40);  /* Align to the top */

    /* Make the window content responsive */
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);
}
#endif /* PL_CONFIG_USE_GATEWAY && PL_CONFIG_USE_GUI */
