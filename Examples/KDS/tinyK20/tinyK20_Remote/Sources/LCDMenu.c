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

/* LCD specific constants */ /*! \todo move this out */
#define LCDMENU_NOF_MENU_LINES            4  /* number of lines on display */
#define LCDMENU_SUBMENU_INDICATOR_CHAR    '>' /* submenu indicator */
#define LCDMENU_UPMENU_INDICATOR_CHAR     '<' /* up-menu indicator */
#define LCDMENU_V_SCROLLBAR_WIDTH         1   /* vertical scrollbar width */

typedef struct {
  const LCDMenu_MenuItem *menus; /* pointer to array of menu items */
  uint16_t nofMenuItems;   /* number of menu items */
  uint8_t selectedID;  /* currently selected menu ID */
  uint8_t topLevel, topPos;   /* display top position */
} LCDMenu_Status;

static LCDMenu_Status menuStatus;

void LCDMenu_InitMenu(const LCDMenu_MenuItem *menus, uint8_t nofMenuItems, uint8_t selectedID) {
  menuStatus.menus = menus;
  menuStatus.nofMenuItems = nofMenuItems;
  menuStatus.selectedID = selectedID;
  menuStatus.topLevel = 0;
  menuStatus.topPos = 0;
}

static const LCDMenu_MenuItem *LCDMenu_GetLevelPosMenuItem(uint8_t level, uint8_t pos) {
  int i;

  i = 0;
  while(i<menuStatus.nofMenuItems) {
    if (menuStatus.menus[i].level==level && menuStatus.menus[i].pos==pos) { /* match */
      return &menuStatus.menus[i];
    }
    i++;
  }
  return NULL; /* not found */
}

static const LCDMenu_MenuItem *LCDMenu_GeIdMenuItem(uint8_t id) {
  int i;

  i = 0;
  while(i<menuStatus.nofMenuItems) {
    if (menuStatus.menus[i].id==id) { /* match */
      return &menuStatus.menus[i];
    }
    i++;
  }
  return NULL; /* not found */
}

static uint16_t LCDMenu_NofMenuItemsOnLevel(uint8_t level) {
  int i;
  uint16_t cntr;

  i = 0;
  cntr = 0;
  while(i<menuStatus.nofMenuItems) {
    if (menuStatus.menus[i].level==level) { /* match */
      cntr++;
    }
    i++;
  }
  return cntr; /* return number of items found */

}

void LCDMenu_Draw(void) {
  PGFONT_Callbacks font;
  FDisp1_PixelDim x, y;
  FDisp1_PixelDim charHeight, fontHeight;
  int i, nofMaxMenuItems;
  const LCDMenu_MenuItem *item;
  uint8_t level, pos;
  uint8_t *text;
  GDisp1_PixelColor textColor;
  FDisp1_PixelDim charWidth, totalWidth;
  FDisp1_PixelDim scrollBarWidth;
  uint16_t nofTotalMenusOnLevel;

  font = GFONT1_GetFont();
  FDisp1_GetFontHeight(font, &charHeight, &fontHeight);
  nofMaxMenuItems = GDisp1_GetHeight()/fontHeight;
  GDisp1_Clear(); /* clear display */
  level = menuStatus.topLevel;
  pos = menuStatus.topPos;
  nofTotalMenusOnLevel = LCDMenu_NofMenuItemsOnLevel(level);
  if (nofTotalMenusOnLevel>LCDMENU_NOF_MENU_LINES) { /* show scrollbar only if needed */
    FDisp1_PixelDim h;

    scrollBarWidth = LCDMENU_V_SCROLLBAR_WIDTH+1; /* plus one for a border to the left */
    x = GDisp1_GetWidth()-LCDMENU_V_SCROLLBAR_WIDTH;
    y = (GDisp1_GetHeight()*menuStatus.topPos)/nofTotalMenusOnLevel;
    h = (GDisp1_GetHeight()*LCDMENU_NOF_MENU_LINES)/nofTotalMenusOnLevel; /* h proportional to the items visible */
    GDisp1_DrawFilledBox(x, y, LCDMENU_V_SCROLLBAR_WIDTH, h, GDisp1_COLOR_BLACK);
  } else {
    scrollBarWidth = 0; /* no scrollbar */
  }
  x = 0;
  y = 1; /* have a small border on top of the text */
  for(i=0; i<nofMaxMenuItems; i++) {
    item = LCDMenu_GetLevelPosMenuItem(level, pos);
    if (item!=NULL) {
      x = 0;
      text = item->menuText;
      if (text==NULL && item->handler!=NULL) {
         text = NULL;
         item->handler(item, LCDMENU_EVENT_GET_TEXT, (void**)&text);
         if (text==NULL) {
           text = "";
         }
      }
      if (item->id == menuStatus.selectedID) { /* selected item */
        GDisp1_DrawFilledBox(x, y-1, GDisp1_GetWidth()-scrollBarWidth, fontHeight, GDisp1_COLOR_BLACK); /* -1 because of small border */
        textColor = GDisp1_COLOR_WHITE; /* selection is white text on black background */
      } else {
        textColor = GDisp1_COLOR_BLACK;
      }
      /* up-menu indicator */
      if (item->lvlUpID!=0) { /* there is a upper level menu: write indicator */
        FDisp1_WriteChar(LCDMENU_UPMENU_INDICATOR_CHAR, textColor, &x, &y, font);
      } else if (item->level>0) { /* skip space, but not for root menu */
        FDisp1_GetCharWidth(LCDMENU_UPMENU_INDICATOR_CHAR, &charWidth, &totalWidth, font);
        x += totalWidth;
      }
      FDisp1_WriteString(text, textColor, &x, &y, font); /* write menu text */
      if (item->lvlDownID!=0) { /* menu entry with a sub-menu entry: write sub-menu indicator */
        /* sub-menu indicator */
        FDisp1_GetCharWidth(LCDMENU_SUBMENU_INDICATOR_CHAR, &charWidth, &totalWidth, font);
        x = GDisp1_GetWidth()-charWidth-scrollBarWidth; /* display width */
        FDisp1_WriteChar(LCDMENU_SUBMENU_INDICATOR_CHAR, textColor, &x, &y, font);
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
    if (item->pos<menuStatus.topPos) { /* check if outside visible area */
      menuStatus.topPos = item->pos;
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

static void LCDMenu_CursorEnter(void) {
  const LCDMenu_MenuItem *item;

  item = LCDMenu_GeIdMenuItem(menuStatus.selectedID); /* get current item */
  if (item!=NULL) {
    if (item->handler!=NULL) { /* custom handler */
      item->handler(item, LCDMENU_EVENT_ENTER, NULL);
      LCDMenu_OnEvent(LCDMENU_EVENT_DRAW);
    } else if (item->lvlDownID!=0) { /* enter on a main menu item: go down in menu hierarchy */
      LCDMenu_OnEvent(LCDMENU_EVENT_RIGHT); /* emulate key */
    }
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
  case LCDMENU_EVENT_ENTER:
    LCDMenu_CursorEnter();
    break;
  }
}

void LCDMenu_Init(void) {
  menuStatus.topLevel = 0;
  menuStatus.topPos = 0;
  menuStatus.selectedID = 1;
}

