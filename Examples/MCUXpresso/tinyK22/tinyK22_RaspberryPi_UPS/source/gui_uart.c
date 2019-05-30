/*
 * gui_tempHum.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
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
static lv_res_t win_close_action(lv_obj_t *btn) {
  GUI_GroupPull();
  lv_obj_del(win);
  win = NULL;
  lv_task_del(refr_task);
  refr_task = NULL;
  return LV_RES_INV;
}

static lv_res_t cb_linuxToHost_click_action(lv_obj_t *cb) {
  GATEWAY_SetLinuxToHostEnabled(!GATEWAY_LinuxToHostIsEnabled()); /* toggle */
  lv_cb_set_checked(cb, GATEWAY_LinuxToHostIsEnabled());
  return LV_RES_INV;
}

static lv_res_t cb_hostToLinux_click_action(lv_obj_t *cb) {
  GATEWAY_SetHostToLinuxEnabled(!GATEWAY_HostToLinuxIsEnabled()); /* toggle */
  lv_cb_set_checked(cb, GATEWAY_HostToLinuxIsEnabled());
  return LV_RES_INV;
}

static void refresh_task(void *param) {
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
    closeBtn = lv_win_add_btn(win, SYMBOL_CLOSE, win_close_action);
    GUI_GroupPush();
    GUI_AddObjToGroup(closeBtn);
    lv_group_focus_obj(closeBtn);

    /* checkboxes */
    lv_obj_t *cb;

    cb = lv_cb_create(win, NULL);
    lv_cb_set_text(cb, "Gateway Linux->Host");
    lv_cb_set_checked(cb, GATEWAY_LinuxToHostIsEnabled());
   //lv_obj_align(cb, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_cb_set_action(cb, cb_linuxToHost_click_action);
    GUI_AddObjToGroup(cb);

    cb = lv_cb_create(win, NULL);
    lv_cb_set_text(cb, "Gateway Host->Linx");
    lv_cb_set_checked(cb, GATEWAY_HostToLinuxIsEnabled());
   //lv_obj_align(cb, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_cb_set_action(cb, cb_hostToLinux_click_action);
    GUI_AddObjToGroup(cb);

    rxtx_label = lv_label_create(win, NULL);
    lv_label_set_text(rxtx_label, "Rx: ???, Tx: ???");
    //lv_obj_align(rxtx_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 40);  /* Align to the top */

    /* Make the window content responsive */
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);
}
#endif /* PL_CONFIG_USE_GATEWAY && PL_CONFIG_USE_GUI */
