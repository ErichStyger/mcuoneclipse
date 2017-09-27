/*
 * LCDMenu.h
 *
 *  Created on: 09.09.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_LCDMENU_H_
#define SOURCES_LCDMENU_H_

#include "Platform.h"
#include <stdint.h>

#if PL_CONFIG_HAS_LCD_MENU
typedef enum {
  LCDMENU_EVENT_INIT,
  LCDMENU_EVENT_DRAW,
  LCDMENU_EVENT_GET_TEXT, /* get menu text, returned in data handler */
  LCDMENU_EVENT_GET_EDIT_TEXT, /* get menu text in edit mode, returned in data handler */
  LCDMENU_EVENT_UP,
  LCDMENU_EVENT_DOWN,
  LCDMENU_EVENT_LEFT,
  LCDMENU_EVENT_RIGHT,
  LCDMENU_EVENT_ENTER,
  LCDMENU_EVENT_ENTER_EDIT,  /* entering edit mode */
  LCDMENU_EVENT_EXIT_EDIT,   /* exiting edit mode */
  LCDMENU_EVENT_INCREMENT,
  LCDMENU_EVENT_DECREMENT
} LCDMenu_EventType;

typedef enum {
  LCDMENU_STATUS_FLAGS_NONE           = 0,      /* default/initialization value */
  LCDMENU_STATUS_FLAGS_ERROR          = (1<<0), /* generic error */
  LCDMENU_STATUS_FLAGS_HANDLED        = (1<<1), /* menu item was handled */
  LCDMENU_STATUS_FLAGS_UPDATE_VIEW    = (1<<2), /* menu has changed, need update in view */
} LCDMenu_StatusFlags;

typedef enum {
  LCDMENU_MENU_FLAGS_NONE         = 0,      /* default/initialization value */
  LCDMENU_MENU_FLAGS_EDITABLE     = (1<<0), /* editable data value */
} LCDMenu_MenuFlags;

#define LCDMENU_ID_NONE     0   /* special menu ID for 'no' id */
#define LCDMENU_GROUP_ROOT  0   /* special ID for root menu group */

typedef struct LCDMenu_MenuItem_{
  uint8_t id;  /* unique ID of menu item, starting with 1 */
  uint8_t group; /* menu group, starting with 0 (root), then increasing numbers */
  uint8_t pos; /* position of menu in level, starting with 0 (top position) */
  uint8_t lvlUpID;  /* menu item level up, 0 for 'none' */
  uint8_t lvlDownID; /* menu item level down, 0 for 'none' */
  char *menuText; /* text of menu item */
  LCDMenu_StatusFlags (*handler)(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP); /* callback for menu item */
  LCDMenu_MenuFlags flags; /* menu flags */
} LCDMenu_MenuItem;

void LCDMenu_OnEvent(LCDMenu_EventType event, const LCDMenu_MenuItem *menu);

void LCDMenu_InitMenu(const LCDMenu_MenuItem *menus, uint8_t nofMenuItems, uint8_t selectedID);

/*!
 * \brief Driver de-initialization
 */
void LCDMenu_Deinit(void);

/*!
 * \brief Driver initialization
 */
void LCDMenu_Init(void);

#endif /* PL_CONFIG_HAS_LCD_MENU */

#endif /* SOURCES_LCDMENU_H_ */

