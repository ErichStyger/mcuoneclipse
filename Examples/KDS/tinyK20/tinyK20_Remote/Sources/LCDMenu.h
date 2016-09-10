/*
 * LCDMenu.h
 *
 *  Created on: 09.09.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_LCDMENU_H_
#define SOURCES_LCDMENU_H_

typedef enum {
  LCDMENU_EVENT_INIT,
  LCDMENU_EVENT_DRAW,
  LCDMENU_EVENT_UP,
  LCDMENU_EVENT_DOWN,
  LCDMENU_EVENT_LEFT,
  LCDMENU_EVENT_RIGHT,
  LCDMENU_EVENT_ENTER,
} LCDMenu_EventType;

void LCDMenu_OnEvent(LCDMenu_EventType event);

void LCDMenu_Update(void);

void LCDMenu_Init(void);


#endif /* SOURCES_LCDMENU_H_ */

