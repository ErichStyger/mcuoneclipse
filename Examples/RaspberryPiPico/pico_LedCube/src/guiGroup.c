/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "guiGroup.h"
#if PL_CONFIG_USE_GUI_KEY_NAV && LV_USE_GROUP

#include "gui.h"
#include "lv.h"
#include "LittlevGL/lvgl/lvgl.h"

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
  groups.stack[groups.sp] = gui_group;
  groups.sp++;
}
#endif /* PL_CONFIG_USE_GUI_KEY_NAV */

