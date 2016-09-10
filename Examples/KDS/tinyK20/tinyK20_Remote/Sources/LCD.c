/*
 * LCD.c
 *
 *  Created on: 25.03.2016
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_LCD
#include "LCD.h"
#include "Application.h"
#include "LED1.h"
#include "LCD_LED.h"
#include "PDC1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "FDisp1.h"
#include "Event.h"
#include "FRTOS1.h"
#if PL_CONFIG_HAS_SNAKE
  #include "Snake.h"
#endif
#include "LCDMenu.h"

static bool LedBackLightisOn = TRUE;

static void BackLightMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
    if (LedBackLightisOn) {
      *dataP = "Backlight ON";
    } else {
      *dataP = "Backlight OFF";
    }
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
    LedBackLightisOn = !LedBackLightisOn;
  }
}

static const LCDMenu_MenuItem menus[] =
{/* id, lvl, pos, up, down, text, callback */
    {1, 0,   0,   0, 2,     "Settings >", NULL},
    {2, 1,   0,   1, 0,     NULL, BackLightMenuHandler},
    {3, 0,   1,   0, 4,     "2 >", NULL},
    {4, 2,   0,   3, 0,     "< 2.a", NULL},
    {5, 2,   1,   3, 0,     "< 2.b", NULL},
    {6, 0,   2,   0, 0,     "1d", NULL},
    {7, 0,   3,   0, 0,     "1e", NULL},
    {8, 0,   4,   0, 0,     "1f", NULL},
};

static void DrawLines(void) {
  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_UpdateFull();

  GDisp1_DrawBox(0, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));

  GDisp1_DrawBox(GDisp1_GetWidth()-10, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));

  GDisp1_DrawLine(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  GDisp1_DrawLine(0, GDisp1_GetHeight(), GDisp1_GetWidth(), 0, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  for(i=0;i<10;i++) {
    GDisp1_DrawCircle(GDisp1_GetWidth()/2, GDisp1_GetHeight()/2, 5+i*2, GDisp1_COLOR_BLACK);
    GDisp1_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void DrawFont(void) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  GDisp1_UpdateFull();
  x = 0;
  y = 10;
  FDisp1_WriteString("Hello World!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  x = 0;
  y += GFONT1_GetBoxHeight();
  FDisp1_WriteString("with Fonts!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  WAIT1_Waitms(1000);
}

static void DrawText(void) {
  GDisp1_Clear();
  GDisp1_UpdateFull();
  PDC1_WriteLineStr(1, "hello");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(2, "world");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(3, "out");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(4, "there");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(5, "!!!!!");
  vTaskDelay(pdMS_TO_TICKS(200));
}

static void ShowTextOnLCD(unsigned char *text) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  x = 0;
  y = 10;
  FDisp1_WriteString(text, GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
}

void LCD_Task(void *param) {
  (void)param; /* not used */
#if 0
  /* test/demo code */
  LCD_LED_On(); /* turn LCD backlight on */
  DrawText();
  LCD_LED_Off(); /* LCD backlight off */
  vTaskDelay(pdMS_TO_TICKS(500));
  LCD_LED_On(); /* turn LCD backlight on */
  DrawLines();
  vTaskDelay(pdMS_TO_TICKS(500));
  LCD_LED_Off(); /* LCD backlight off */
  vTaskDelay(pdMS_TO_TICKS(500));
  LCD_LED_On(); /* turn LCD backlight on */
  DrawFont();
  LCD_LED_Off(); /* LCD backlight off */
#endif
  //ShowTextOnLCD("Press a key!");
  LCDMenu_InitMenu(menus, sizeof(menus)/sizeof(menus[0]), 1);
  LCDMenu_OnEvent(LCDMENU_EVENT_DRAW);
  for(;;) {
    if (LedBackLightisOn) {
      LCD_LED_On(); /* LCD backlight on */
    } else {
      LCD_LED_Off(); /* LCD backlight off */
    }
    //LED1_Neg();
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_LEFT)) { /* left */
      LCDMenu_OnEvent(LCDMENU_EVENT_RIGHT);
//      ShowTextOnLCD("left");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_RIGHT)) { /* right */
      LCDMenu_OnEvent(LCDMENU_EVENT_LEFT);
//      ShowTextOnLCD("right");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_UP)) { /* up */
      LCDMenu_OnEvent(LCDMENU_EVENT_DOWN);
//      ShowTextOnLCD("up");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_DOWN)) { /* down */
      LCDMenu_OnEvent(LCDMENU_EVENT_UP);
//      ShowTextOnLCD("down");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_CENTER)) { /* center */
      LCDMenu_OnEvent(LCDMENU_EVENT_ENTER);
//      ShowTextOnLCD("center");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_SIDE_BTN_UP)) { /* side up */
      ShowTextOnLCD("side up");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_SIDE_BTN_DOWN)) { /* side down */
      ShowTextOnLCD("side down");
    }
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void LCD_Init(void) {
  LedBackLightisOn =  TRUE;
  LCDMenu_Init();
  if (xTaskCreate(LCD_Task, "LCD", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error! probably out of memory */
  }
}
#endif /* PL_CONFIG_HAS_LCD */
