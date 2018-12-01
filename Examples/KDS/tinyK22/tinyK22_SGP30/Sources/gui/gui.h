/*
 * gui.h
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */

#ifndef GUI_H_
#define GUI_H_

#include "Platform.h"

#if PL_CONFIG_HAS_GUI_KEY_NAV
  #include "lvgl/lv_core/lv_group.h"

  lv_group_t *GUI_GroupPeek(void);
  void GUI_GroupPull(void);
  void GUI_GroupPush(void);

  void GUI_AddObjToGroup(lv_obj_t *obj);
  void GUI_RemoveObjFromGroup(lv_obj_t *obj);
#endif

void GUI_Init(void);

#endif /* GUI_H_ */
