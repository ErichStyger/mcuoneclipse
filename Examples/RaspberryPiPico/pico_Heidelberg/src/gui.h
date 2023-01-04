/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GUI_H_
#define GUI_H_

#include "app_platform.h"
#include "McuGDisplaySSD1306.h"

#define LV_USE_GROUP  (1)

#if PL_CONFIG_USE_GUI_KEY_NAV && LV_USE_GROUP
  #include "LittlevGL/lvgl/src/core/lv_group.h"
  #include "LittlevGL/lvgl/src/core/lv_obj.h"

  lv_group_t *GUI_GroupPeek(void);
  void GUI_GroupPull(void);
  void GUI_GroupPush(void);

  void GUI_AddObjToGroup(lv_obj_t *obj);
  void GUI_RemoveObjFromGroup(lv_obj_t *obj);
#endif

void GUI_NotifyUserAction(void);

void GUI_Init(void);

#endif /* GUI_H_ */
