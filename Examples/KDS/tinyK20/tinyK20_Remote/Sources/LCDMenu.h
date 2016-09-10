/*
 * LCDMenu.h
 *
 *  Created on: 09.09.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_LCDMENU_H_
#define SOURCES_LCDMENU_H_

#include <stdint.h>

typedef enum {
  LCDMENU_EVENT_INIT,
  LCDMENU_EVENT_GET_TEXT, /* get menu text, returned in data handler */
  LCDMENU_EVENT_DRAW,
  LCDMENU_EVENT_UP,
  LCDMENU_EVENT_DOWN,
  LCDMENU_EVENT_LEFT,
  LCDMENU_EVENT_RIGHT,
  LCDMENU_EVENT_ENTER,
} LCDMenu_EventType;

typedef struct LCDMenu_MenuItem_{
  uint8_t id;  /* unique ID of menu item, starting with 1 */
  uint8_t level; /* menu level, starting with 0 (root), then increasing numbers */
  uint8_t pos; /* position of menu in level, starting with 0 (top position) */
  uint8_t lvlUpID;  /* menu item level up, 0 for 'none' */
  uint8_t lvlDownID; /* menu item level down, 0 for 'none' */
  char *menuText; /* text of menu item */
  void(*handler)(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP); /* callback for menu item */
} LCDMenu_MenuItem;

void LCDMenu_OnEvent(LCDMenu_EventType event);

void LCDMenu_InitMenu(const LCDMenu_MenuItem *menus, uint8_t nofMenuItems, uint8_t selectedID);

void LCDMenu_Init(void);


#endif /* SOURCES_LCDMENU_H_ */

