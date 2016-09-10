/*
 * LCDMenu.c
 *
 *  Created on: 09.09.2016
 *      Author: Erich Styger Local
 */

#include "LCDMenu.h"
#include "GDisp1.h"
#include "FDisp1.h"
#include "GFONT1.h"

#define LCDMENU_NOF_MENU_LINES    4  /* number of lines on display */

typedef struct LCDMenu_MenuItem_{
  uint8_t id;  /* unique ID of menu item, starting with 1 */
  uint8_t level; /* menu level, starting with 0 (root), then increasing numbers */
  uint8_t pos; /* position of menu in level, starting with 0 (top position) */
  uint8_t lvlUpID;  /* menu item level up, 0 for 'none' */
  uint8_t lvlDownID; /* menu item level down, 0 for 'none' */
  char *menuText; /* text of menu item */
  void(*fn)(struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event); /* callback for menu item */
} LCDMenu_MenuItem;

static const LCDMenu_MenuItem menus[] =
{/* id, lvl, pos, up, down, text, callback */
    {1, 0,   0,   0, 0,     "1a", NULL},
    {2, 0,   1,   0, 0,     "1b", NULL},
    {3, 0,   2,   0, 4,     "1c>", NULL},
    {4, 1,   0,   3, 0,     "<2.a", NULL},
    {5, 1,   1,   3, 0,     "<2.b", NULL},
    {6, 0,   3,   0, 0,     "1d", NULL},
    {7, 0,   4,   0, 0,     "1e", NULL},
    {8, 0,   5,   0, 0,     "1f", NULL},
};

typedef struct {
  uint8_t topLevel, topPos;   /* display top position */
  uint8_t selectedID;  /* currently selected menu ID */
} LCDMenu_Status;

static LCDMenu_Status menuStatus;

static const LCDMenu_MenuItem *LCDMenu_GetLevelPosMenuItem(uint8_t level, uint8_t pos) {
  int i;

  i = 0;
  while(i<sizeof(menus)/sizeof(menus[0])) {
    if (menus[i].level==level && menus[i].pos==pos) { /* match */
      return &menus[i];
    }
    i++;
  }
  return NULL; /* not found */
}

static const LCDMenu_MenuItem *LCDMenu_GeIdMenuItem(uint8_t id) {
  int i;

  i = 0;
  while(i<sizeof(menus)/sizeof(menus[0])) {
    if (menus[i].id==id) { /* match */
      return &menus[i];
    }
    i++;
  }
  return NULL; /* not found */
}

void LCDMenu_Draw(void) {
  PGFONT_Callbacks font;
  FDisp1_PixelDim x, y;
  FDisp1_PixelDim charHeight, fontHeight;
  int i, nofMaxMenuItems;
  const LCDMenu_MenuItem *item;
  uint8_t level, pos;

  font = GFONT1_GetFont();
  FDisp1_GetFontHeight(font, &charHeight, &fontHeight);
  nofMaxMenuItems = GDisp1_GetHeight()/fontHeight;
  GDisp1_Clear(); /* clear display */
  x = 0; y = 0;
  level = menuStatus.topLevel;
  pos = menuStatus.topPos;
  for(i=0; i<nofMaxMenuItems; i++) {
    item = LCDMenu_GetLevelPosMenuItem(level, pos);
    if (item!=NULL) {
      x = 0;
      if (item->id == menuStatus.selectedID) {
        GDisp1_DrawFilledBox(x, y, GDisp1_GetWidth(), fontHeight, GDisp1_COLOR_BLACK);
        FDisp1_WriteString(item->menuText, GDisp1_COLOR_WHITE, &x, &y, font);
      } else {
        FDisp1_WriteString(item->menuText, GDisp1_COLOR_BLACK, &x, &y, font);
      }
      y += fontHeight;
    }
    pos++;
  }
  GDisp1_UpdateFull();
}

static void LCDMenu_CursorUp(void) {
  const LCDMenu_MenuItem *item;

  item = LCDMenu_GeIdMenuItem(menuStatus.selectedID); /* get current item */
  if (item!=NULL && item->pos>0) {
    item = LCDMenu_GetLevelPosMenuItem(item->level, item->pos-1); /* get next possible item */
    /* NULL if not found */
  }
  if (item !=NULL) {
    menuStatus.selectedID = item->id;
    if (item->pos>=LCDMENU_NOF_MENU_LINES-1) { /* check if outside visible area */
      menuStatus.topPos = item->pos-LCDMENU_NOF_MENU_LINES+1;
    }
    LCDMenu_OnEvent(LCDMENU_EVENT_DRAW);
  }
}

static void LCDMenu_CursorDown(void) {
  const LCDMenu_MenuItem *item;

  item = LCDMenu_GeIdMenuItem(menuStatus.selectedID); /* get current item */
  if (item!=NULL) {
    item = LCDMenu_GetLevelPosMenuItem(item->level, item->pos+1); /* get next possible item */
    /* NULL if not found */
  }
  if (item!=NULL) { /* yes, it exists */
    menuStatus.selectedID = item->id;
    if (item->pos>=LCDMENU_NOF_MENU_LINES) { /* check if outside visible area */
      menuStatus.topPos = item->pos-LCDMENU_NOF_MENU_LINES+1;
    }
    LCDMenu_OnEvent(LCDMENU_EVENT_DRAW);
  }
}

static void LCDMenu_CursorRight(void) {
  const LCDMenu_MenuItem *item;

  item = LCDMenu_GeIdMenuItem(menuStatus.selectedID); /* get current item */
  if (item!=NULL && item->lvlDownID!=0) {
    item = LCDMenu_GeIdMenuItem(item->lvlDownID); /* get target item */
    menuStatus.selectedID = item->id;
    menuStatus.topLevel = item->level;
    menuStatus.topPos = 0;
    LCDMenu_OnEvent(LCDMENU_EVENT_DRAW);
  }
}

static void LCDMenu_CursorLeft(void) {
  const LCDMenu_MenuItem *item;

  item = LCDMenu_GeIdMenuItem(menuStatus.selectedID); /* get current item */
  if (item!=NULL && item->lvlUpID!=0) {
    item = LCDMenu_GeIdMenuItem(item->lvlUpID); /* get target item */
    menuStatus.selectedID = item->id;
    menuStatus.topLevel = item->level;
    if (item->pos>=LCDMENU_NOF_MENU_LINES) { /* check if outside visible area */
      menuStatus.topPos = item->pos-LCDMENU_NOF_MENU_LINES+1;
    } else {
      menuStatus.topPos = 0;
    }
    LCDMenu_OnEvent(LCDMENU_EVENT_DRAW);
  }
}


void LCDMenu_OnEvent(LCDMenu_EventType event) {
  switch(event) {
  case LCDMENU_EVENT_INIT:
    break;
  case LCDMENU_EVENT_DRAW:
    LCDMenu_Draw();
    break;
  case LCDMENU_EVENT_UP:
    LCDMenu_CursorUp();
    break;
  case LCDMENU_EVENT_DOWN:
    LCDMenu_CursorDown();
    break;
  case LCDMENU_EVENT_LEFT:
    LCDMenu_CursorLeft();
    break;
  case LCDMENU_EVENT_RIGHT:
    LCDMenu_CursorRight();
    break;
  }
}

void LCDMenu_Init(void) {
  menuStatus.topLevel = 0;
  menuStatus.topPos = 0;
  menuStatus.selectedID = 1;
}

