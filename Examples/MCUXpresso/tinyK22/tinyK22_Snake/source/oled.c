/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "oled.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuSSD1306.h"


#include "McuFontDisplay.h"
#include "McuGFont.h"
#include "McuFontHelv08Normal.h"
#include "McuFontHelv12Bold.h"
#include "McuFontHelv18Bold.h"
#include "McuFontHelv24Bold.h"

static void test(void) {
  McuGDisplaySSD1306_Clear();

  for(int i=0; i<10; i++) {
    McuGDisplaySSD1306_DrawBox(i*2, i*2, McuGDisplaySSD1306_GetWidth()-(i*4)-1, McuGDisplaySSD1306_GetHeight()-(i*4)-1, 1, McuGDisplaySSD1306_COLOR_WHITE);
  }
  for(int i=0; i<10; i++) {
    McuGDisplaySSD1306_DrawCircle(McuGDisplaySSD1306_GetWidth()/2, McuGDisplaySSD1306_GetHeight()/2, 5+i*2, McuGDisplaySSD1306_COLOR_WHITE);
  }
  McuGDisplaySSD1306_UpdateFull();
}

static void test2(void) {
  McuFontDisplay_PixelDim x, y, w, h;
  uint8_t buf[24];
  McuFontDisplay_Font *font;

  McuGDisplaySSD1306_Clear();

  font = McuFontHelv24Bold_GetFont();
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"AEMBS");
  w = McuFontDisplay_GetStringWidth(buf, font, NULL);
  h = McuFontDisplay_GetStringHeight(buf, font, NULL);
  x = (McuGDisplaySSD1306_GetWidth()-w)/2;
  y = (McuGDisplaySSD1306_GetHeight()-h)/2;
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  McuGDisplaySSD1306_UpdateFull();
}


static void testgraphics(void) {
  McuFontDisplay_PixelDim x, y, w, h;
  float value = 23.28;
  uint8_t buf[24];

  McuGDisplaySSD1306_Clear();
  McuUtility_NumFloatToStr(buf,  sizeof(buf), value, 2);
  McuUtility_chcat(buf, sizeof(buf), 'C');
  w = McuFontDisplay_GetStringWidth(buf, McuFontHelv18Bold_GetFont(), NULL);
  h = McuFontDisplay_GetStringHeight(buf, McuFontHelv18Bold_GetFont(), NULL);
  x = (McuGDisplaySSD1306_GetWidth()-w)/2;
  y = (McuGDisplaySSD1306_GetHeight()-h)/2;
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv18Bold_GetFont());

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_WHITE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-5, McuGDisplaySSD1306_GetHeight()-5, 1, McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_UpdateFull();
}

static void testfont(void) {
  McuFontDisplay_PixelDim x, y;
  float value = 23.28;
  uint8_t buf[24];

  McuFontDisplay_Init();
  McuGFont_Init();
  McuFontHelv08Normal_Init();
  McuFontHelv12Bold_Init();

  McuGDisplaySSD1306_Clear();
  x = y = 0;
  McuFontDisplay_WriteString((uint8_t*)"Temperature: ", McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv08Normal_GetFont());
  McuUtility_NumFloatToStr(buf,  sizeof(buf), value, 2);
  McuUtility_chcat(buf, sizeof(buf), 'C');
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv08Normal_GetFont());

  McuGDisplaySSD1306_UpdateFull();
}

static void test0(void) {
  float value = 23.28;
  uint8_t buf[24], valBuf[8];
  McuSSD1306_Clear();

  McuUtility_strcpy(buf, sizeof(buf), (uint8_t*)"Temperature: ");
  McuUtility_NumFloatToStr(valBuf,  sizeof(buf), value, 2);
  McuUtility_strcat(buf, sizeof(buf), valBuf);
  McuUtility_chcat(buf, sizeof(buf), 'C');
  McuSSD1306_ClearLine(0);
  McuSSD1306_PrintString(0, 0, buf);
}


void OLED_Test(void) {
#if 0
  for(;;) {
    McuSSD1306_Clear();  /* clear the display */
    /* write text to different lines (first parameter) and columns (second parameter) */
    McuSSD1306_PrintString(0, 0, (unsigned char*)"Test");
    McuSSD1306_PrintString(1, 0, (unsigned char*)"Hello\nWorld!");
    McuSSD1306_PrintString(3, 0, (unsigned char*)"the quick\nbrown fox\njumps over\nthe lazy");
    McuSSD1306_PrintString(7, 0, (unsigned char*)"dog");
    McuWait_Waitms(100); /* slow down things a bit */
  }
#else
  for(;;) {
    McuSSD1306_Clear();  /* clear the display */
    /* write text to different lines (first parameter) and columns (second parameter) */

    McuSSD1306_PrintString(0, 0, (unsigned char*)"  -     Welcome to AEMBS!");
    McuSSD1306_PrintString(1, 0, (unsigned char*)" ) )");
    McuSSD1306_PrintString(2, 0, (unsigned char*)"( (  . -\"\"-.  A.-.A");
    McuSSD1306_PrintString(3, 0, (unsigned char*)" \\ \\/      \\/  , , \\");
    McuSSD1306_PrintString(4, 0, (unsigned char*)"   \\  \\    =;   t  /=");
    McuSSD1306_PrintString(5, 0, (unsigned char*)"    \\  |\"\".   ',--'");
    McuSSD1306_PrintString(6, 0, (unsigned char*)"    / //   | ||");
    McuSSD1306_PrintString(7, 0, (unsigned char*)"   /_,))   |_))");
    McuWait_Waitms(2000);

    test0();
    McuWait_Waitms(2000);
    testfont();
    McuWait_Waitms(2000);
    testgraphics();
    McuWait_Waitms(2000);
    test();
    McuWait_Waitms(2000);
    test2();
    McuWait_Waitms(2000);
  }
#endif
}

void OLED_Init(void) {
  McuSSD1306_Clear(); /* clear the display */
}

void OLED_DeInit(void) {
}
