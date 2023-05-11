/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GUIGROUP_H_
#define GUIGROUP_H_

#include "platform.h"
#include "gui.h"

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

#endif /* GUIGROUP_H_ */
