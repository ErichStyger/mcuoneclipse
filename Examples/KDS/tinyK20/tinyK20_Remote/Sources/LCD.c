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
#include "RApp.h"
#include "LCDMenu.h"

static bool LedBackLightisOn = TRUE;

typedef enum {
  LCD_MENU_ID_NONE = LCDMENU_ID_NONE, /* special value! */
  LCD_MENU_ID_MAIN,
    LCD_MANU_ID_BACKLIGHT,
  LCD_MENU_ID_ROBOT,
    LCD_MENU_ID_ROBOT_REMOTE,
      LCD_MENU_ID_ROBOT_REMOTE_FORWARD,
      LCD_MENU_ID_ROBOT_REMOTE_BACKWARD,
      LCD_MENU_ID_ROBOT_REMOTE_LEFT,
      LCD_MENU_ID_ROBOT_REMOTE_RIGHT,
      LCD_MENU_ID_ROBOT_REMOTE_STOP,
      LCD_MENU_ID_ROBOT_REMOTE_ON,
      LCD_MENU_ID_ROBOT_REMOTE_OFF,
    LCD_MENU_ID_ROBOT_SENSOR,
  LCD_MENU_ID_NRF24L01P,
  LCD_MENU_ID_LORA,
  LCD_MENU_ID_SETTINGS,
} LCD_MenuIDs;

static void BackLightMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
    if (LedBackLightisOn) {
      *dataP = "Backlight is ON";
    } else {
      *dataP = "Backlight is OFF";
    }
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
    LedBackLightisOn = !LedBackLightisOn;
  }
}

static void RobotRemoteMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  uint8_t button = '\0';

  if (event==LCDMENU_EVENT_ENTER) {
    switch(item->id) {
      case LCD_MENU_ID_ROBOT_REMOTE_FORWARD:
        button = 'a';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_BACKWARD:
        button = 'c';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_LEFT:
        button = 'd';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_RIGHT:
        button = 'b';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_STOP:
        button = 's';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_ON:
        button = 'e';
        break;
      case LCD_MENU_ID_ROBOT_REMOTE_OFF:
        button = 'E';
        break;
    }
  }
  if (button!='\0') {
    (void)RAPP_SendPayloadDataBlock(&button, sizeof(button), RAPP_MSG_TYPE_JOYSTICK_BTN, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
  }
}

static const LCDMenu_MenuItem menus[] =
{/* id,                                   grp, pos,   up,                 down,                                   text,         callback */
    {LCD_MENU_ID_MAIN,                      0,   0,   LCD_MENU_ID_NONE,         LCD_MANU_ID_BACKLIGHT,            "General",    NULL},
      {LCD_MANU_ID_BACKLIGHT,               1,   0,   LCD_MENU_ID_MAIN,         LCD_MENU_ID_NONE,                 NULL,         BackLightMenuHandler},
    {LCD_MENU_ID_ROBOT,                     0,   1,   LCD_MENU_ID_NONE,         LCD_MENU_ID_ROBOT_REMOTE,         "Robot",      NULL},
      {LCD_MENU_ID_ROBOT_REMOTE,            2,   0,   LCD_MENU_ID_ROBOT,        LCD_MENU_ID_ROBOT_REMOTE_FORWARD, "Remote",     NULL},
        {LCD_MENU_ID_ROBOT_REMOTE_FORWARD,  3,   0,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Forward",    RobotRemoteMenuHandler},
        {LCD_MENU_ID_ROBOT_REMOTE_BACKWARD, 3,   1,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Backward",   RobotRemoteMenuHandler},
        {LCD_MENU_ID_ROBOT_REMOTE_LEFT,     3,   2,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Left",       RobotRemoteMenuHandler},
        {LCD_MENU_ID_ROBOT_REMOTE_RIGHT,    3,   3,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Right",      RobotRemoteMenuHandler},
        {LCD_MENU_ID_ROBOT_REMOTE_STOP,     3,   4,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Stop",       RobotRemoteMenuHandler},
        {LCD_MENU_ID_ROBOT_REMOTE_ON,       3,   5,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Remote On",  RobotRemoteMenuHandler},
        {LCD_MENU_ID_ROBOT_REMOTE_OFF,      3,   6,   LCD_MENU_ID_ROBOT_REMOTE, LCD_MENU_ID_NONE,                 "Remote Off", RobotRemoteMenuHandler},
      {LCD_MENU_ID_ROBOT_SENSOR,            2,   1,   LCD_MENU_ID_ROBOT,        LCD_MENU_ID_NONE,                 "Sensors",    NULL},
    {LCD_MENU_ID_NRF24L01P,                 0,   2,   LCD_MENU_ID_NONE,         LCD_MENU_ID_NONE,                 "nRF24L01+",  NULL},
    {LCD_MENU_ID_LORA,                      0,   3,   LCD_MENU_ID_NONE,         LCD_MENU_ID_NONE,                 "LoRa",       NULL},
    {LCD_MENU_ID_SETTINGS,                  0,   4,   LCD_MENU_ID_NONE,         LCD_MENU_ID_NONE,                 "Settings",    NULL},
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
      LCDMenu_OnEvent(LCDMENU_EVENT_LEFT);
//      ShowTextOnLCD("left");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_RIGHT)) { /* right */
      LCDMenu_OnEvent(LCDMENU_EVENT_RIGHT);
//      ShowTextOnLCD("right");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_UP)) { /* up */
      LCDMenu_OnEvent(LCDMENU_EVENT_UP);
//      ShowTextOnLCD("up");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_DOWN)) { /* down */
      LCDMenu_OnEvent(LCDMENU_EVENT_DOWN);
//      ShowTextOnLCD("down");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_BTN_CENTER)) { /* center */
      LCDMenu_OnEvent(LCDMENU_EVENT_ENTER);
//      ShowTextOnLCD("center");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_SIDE_BTN_UP)) { /* side up */
      LCDMenu_OnEvent(LCDMENU_EVENT_UP);
//      ShowTextOnLCD("side up");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_LCD_SIDE_BTN_DOWN)) { /* side down */
      LCDMenu_OnEvent(LCDMENU_EVENT_DOWN);
//      ShowTextOnLCD("side down");
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
