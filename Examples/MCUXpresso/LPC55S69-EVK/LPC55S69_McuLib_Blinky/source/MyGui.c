/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSSD1306.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuGFont.h"
#include "McuFontHelv08Normal.h"
#include "McuFontHelv08Bold.h"
#include "McuFontCour08Normal.h"
#include "McuFontCour08Bold.h"
#include "McuFontHelv12Normal.h"
#include "McuFontHelv12Bold.h"
#include "McuFontHelv14Normal.h"
#include "McuFontHelv14Bold.h"
#include "McuFontHelv18Normal.h"
#include "McuFontHelv18Bold.h"

static void WriteNameTag(unsigned char *firstname, unsigned char *lastname, PGFONT_Callbacks font) {
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth(firstname, font, NULL)/2;
  y = McuGDisplaySSD1306_GetHeight()/2 - (2*charHeight)/2;
  McuFontDisplay_WriteString(firstname, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth(lastname, font, NULL)/2;
  y += charHeight;
  McuFontDisplay_WriteString(lastname, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);
  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-1-4, McuGDisplaySSD1306_GetHeight()-1-4, 1, McuGDisplaySSD1306_COLOR_BLUE);
}

static void drawText(int32_t value) {
  McuFontDisplay_PixelDim x, y;
  uint8_t buf[24];

  x = 20;
  y = 10;
  McuFontDisplay_WriteString((uint8_t*)"Value: ", McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv08Normal_GetFont());
  McuUtility_Num32uToStr(buf,  sizeof(buf), value);
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv08Normal_GetFont());
}

static void drawTriangle(void) {
  struct { McuGDisplaySSD1306_PixelDim x; McuGDisplaySSD1306_PixelDim y; } triangle[3] = {{10,10},{50,30},{20,40}};

  for(int i=0; i<(sizeof(triangle)/sizeof(triangle[0])-1); i++) {
    McuGDisplaySSD1306_DrawLine(triangle[i].x, triangle[i].y, triangle[i+1].x, triangle[i+1].y, McuGDisplaySSD1306_COLOR_BLUE);
  }
  McuGDisplaySSD1306_DrawLine(triangle[(sizeof(triangle)/sizeof(triangle[0]))-1].x, triangle[(sizeof(triangle)/sizeof(triangle[0]))-1].y, triangle[0].x, triangle[0].y, McuGDisplaySSD1306_COLOR_BLUE);
}

static void drawArcCircles(void) {
//  McuGDisplaySSD1306_DrawCircle(McuGDisplaySSD1306_GetWidth()/2, McuGDisplaySSD1306_GetHeight(), McuGDisplaySSD1306_GetShorterSide(), McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawCircle(70, 30, 20, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawCircle(40, 10, 5, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawCircle(20, 30, 10, McuGDisplaySSD1306_COLOR_BLUE);
}

static void drawLine(void) {
  McuGDisplaySSD1306_DrawLine(0, McuGDisplaySSD1306_GetHeight()-1, McuGDisplaySSD1306_GetWidth()-1, 0, McuGDisplaySSD1306_COLOR_BLUE);
}

static void guiTask(void *pv) {
  /* initialize extra modules */
  McuFontDisplay_Init();
  McuGFont_Init();
  McuFontHelv08Normal_Init();
  McuFontHelv08Bold_Init();
  McuFontHelv12Normal_Init();
  McuFontHelv12Bold_Init();
  McuFontHelv14Normal_Init();
  McuFontHelv14Bold_Init();
  McuFontHelv18Normal_Init();
  McuFontHelv18Bold_Init();
  for(;;) {
    McuGDisplaySSD1306_Clear();
    McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_BLUE);
    //McuGDisplaySSD1306_DrawCircle(20 /*x*/, 30/*y*/, 10/*r*/, McuGDisplaySSD1306_COLOR_BLUE);
    drawArcCircles();
    drawTriangle();
    drawLine();
    drawText(20);
    McuGDisplaySSD1306_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(100));

    McuGDisplaySSD1306_Clear();
    WriteNameTag((unsigned char*)"Chuck", (unsigned char*)"Norris", McuFontHelv12Normal_GetFont());
    McuGDisplaySSD1306_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(100));

    McuGDisplaySSD1306_Clear();
    WriteNameTag((unsigned char*)"Bruce", (unsigned char*)"Lee", McuFontHelv18Bold_GetFont());
    McuGDisplaySSD1306_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void MyGui_Init(void) {
  McuSSD1306_Clear();
  McuSSD1306_PrintString(0, 0, (uint8_t*)"hello OLED!");

  BaseType_t res;

  res = xTaskCreate(guiTask, "guiTask", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL);
  if (res!=pdPASS) {
    /* error! */
    for(;;) {}
  }
}
