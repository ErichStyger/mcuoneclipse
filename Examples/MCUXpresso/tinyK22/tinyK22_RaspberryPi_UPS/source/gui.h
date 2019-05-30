/*

 * gui.h
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */

#ifndef GUI_H_
#define GUI_H_

#include "platform.h"
#include "McuGDisplaySSD1306.h"

#if PL_CONFIG_USE_GUI_KEY_NAV
  #include "LittlevGL/lvgl/lv_core/lv_group.h"

  lv_group_t *GUI_GroupPeek(void);
  void GUI_GroupPull(void);
  void GUI_GroupPush(void);

  void GUI_AddObjToGroup(lv_obj_t *obj);
  void GUI_RemoveObjFromGroup(lv_obj_t *obj);
#endif

void GUI_ChangeOrientation(McuGDisplaySSD1306_DisplayOrientation orientation);

void GUI_Init(void);

#endif /* GUI_H_ */
