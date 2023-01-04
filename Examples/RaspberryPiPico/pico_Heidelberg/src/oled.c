/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_OLED
#include "McuLog.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "McuSSD1306.h"
#include "McuFontDisplay.h"
#include "McuGFont.h"
#include "McuFontHelv08Normal.h"
#include "McuFontHelv12Normal.h"
#include "McuFontHelv12Bold.h"
#include "McuFontHelv18Bold.h"
#include "McuFontHelv24Bold.h"
#include "McuTimeDate.h"
#if PL_CONFIG_USE_SHT31
  #include "McuSHT31.h"
#endif

static const uint8_t vh_pixData[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xef, 0xff, 0xfe, 0xa8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x5f, 0xff, 0xff, 0xff, 0xff, 0x40, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0xff, 0x55, 0x11, 0x55, 0x7f, 0xff, 0xf4, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0xa8, 0x00, 0x00, 0x00, 0xab, 0xff, 0xff, 0xe8, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0xfd, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0xff, 0xf8,
  0x00, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff,
  0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe,
  0x00, 0x00, 0x00, 0x1f, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5e,
  0x00, 0x00, 0x00, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a,
  0x00, 0x00, 0x01, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const TIMAGE vh_image = {
  .width = 128, /* .header.w */
  .height = 28, /* .header.h */
  .size = sizeof(vh_pixData),
  .pixmap = vh_pixData,
  .name = "verkehrshaus",
};

static void ShowVHimage(void) {
  McuGDisplaySSD1306_Clear();
  McuGDisplaySSD1306_DrawMonoBitmap(0, 0, (PIMAGE)&vh_image, McuGDisplaySSD1306_COLOR_WHITE, McuGDisplaySSD1306_COLOR_BLACK);

  McuFontDisplay_Font *font;
  McuFontDisplay_PixelDim x, y;

  font = McuFontHelv12Normal_GetFont();
  x = 25;
  y = vh_image.height-12;
  McuFontDisplay_WriteString((unsigned char*)"verkehrshaus", McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  McuGDisplaySSD1306_UpdateFull();
}

static void ShowCenteredText(const unsigned char *text, McuFontDisplay_Font *font) {
  McuFontDisplay_PixelDim x, y, w, h;
  uint8_t buf[32];

  McuGDisplaySSD1306_Clear();

  McuUtility_strcpy(buf, sizeof(buf), text);
  w = McuFontDisplay_GetStringWidth(buf, font, NULL);
  h = McuFontDisplay_GetStringHeight(buf, font, NULL);
  x = (McuGDisplaySSD1306_GetWidth()-w)/2;
  y = (McuGDisplaySSD1306_GetHeight()-h)/2;
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

  McuGDisplaySSD1306_UpdateFull();
}

void Show2Liner(const unsigned char *text0, const unsigned char *text1) {
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth((unsigned char*)text0, font, NULL)/2;
  y = McuGDisplaySSD1306_GetHeight()/2 - (2*charHeight)/2; /* 2 lines */
  McuFontDisplay_WriteString((unsigned char*)text0, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth((unsigned char*)text1, font, NULL)/2;
  y += McuGDisplaySSD1306_GetHeight()/2 - (2*charHeight)/2;
  McuFontDisplay_WriteString((unsigned char*)text1, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-1-4, McuGDisplaySSD1306_GetHeight()-1-4, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_UpdateFull();
}

void Sensor_ShowTemperature(float value) {
  McuFontDisplay_PixelDim x, y, w, h;
  uint8_t buf[24];

  McuGDisplaySSD1306_Clear();
  McuUtility_NumFloatToStr(buf,  sizeof(buf), value, 2);
  McuUtility_chcat(buf, sizeof(buf), ' ');
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

void Sensor_ShowHumidity(float value) {
  McuFontDisplay_PixelDim x, y, w, h;
  uint8_t buf[24];

  McuGDisplaySSD1306_Clear();
  McuUtility_NumFloatToStr(buf,  sizeof(buf), value, 2);
  McuUtility_chcat(buf, sizeof(buf), '%');
  McuUtility_chcat(buf, sizeof(buf), ' ');
  McuUtility_chcat(buf, sizeof(buf), 'H');
  w = McuFontDisplay_GetStringWidth(buf, McuFontHelv18Bold_GetFont(), NULL);
  h = McuFontDisplay_GetStringHeight(buf, McuFontHelv18Bold_GetFont(), NULL);
  x = (McuGDisplaySSD1306_GetWidth()-w)/2;
  y = (McuGDisplaySSD1306_GetHeight()-h)/2;
  McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv18Bold_GetFont());

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_WHITE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-5, McuGDisplaySSD1306_GetHeight()-5, 1, McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_UpdateFull();
}

#if 0
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
#if 0
    /* write text to different lines (first parameter) and columns (second parameter) */
    McuSSD1306_Clear();  /* clear the display */
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
    McuWait_WaitOSms(2000);
    testfont();
    McuWait_WaitOSms(2000);
    testgraphics();
    McuWait_WaitOSms(2000);
    test();
    McuWait_WaitOSms(2000);
    test2();
    McuWait_WaitOSms(2000);
#else
    LargeText((const unsigned char*)"Split");
    McuWait_WaitOSms(2000);
    LargeText((const unsigned char*)"Flap");
    McuWait_WaitOSms(2000);
#endif
  }
#endif
}
#endif

#if PL_CONFIG_USE_OLED_CLOCK
static void ShowDateTime(void) {
  TIMEREC time;
  DATEREC date;
  unsigned char bufTime[16];
  unsigned char bufDate[16];
  uint8_t oldSec = 0;

  for(int i=0; i<50; i++) {
    McuTimeDate_GetTimeDate(&time, &date);
    if (time.Sec != oldSec) {
      oldSec = time.Sec;
      bufTime[0] = '\0';
      bufDate[0] = '\0';
      McuTimeDate_AddDateString(bufDate, sizeof(bufDate), &date, (unsigned char*)"dd.mm.yyyy");

      McuUtility_strcatNum16sFormatted(bufTime, sizeof(bufTime), time.Hour, '0', 2);
      McuUtility_chcat(bufTime, sizeof(bufTime), ':');
      McuUtility_strcatNum16sFormatted(bufTime, sizeof(bufTime), time.Min, '0', 2);
      McuUtility_chcat(bufTime, sizeof(bufTime), ':');
      McuUtility_strcatNum16sFormatted(bufTime, sizeof(bufTime), time.Sec, '0', 2);

      Show2Liner(bufTime, bufDate);
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
#endif /* PL_CONFIG_USE_OLED_CLOCK */

static void ShowEnergy(void) {
  int32_t pvP, houseP, gridP;
  McuFontDisplay_PixelDim x, y, charHeight, totalHeight, rightXpos;
  uint8_t buf[32];
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();

  rightXpos = McuGDisplaySSD1306_GetWidth()-10;

  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);
  for(int i=0; i<10; i++) {
    pvP = McuUtility_random(1000, 1050);
    houseP = McuUtility_random(200, 500);
    gridP = houseP-pvP;

    McuGDisplaySSD1306_Clear();
    McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_WHITE);
    McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-5, McuGDisplaySSD1306_GetHeight()-5, 1, McuGDisplaySSD1306_COLOR_WHITE);
    x = 7;
    y = 7;
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"PV:");
    McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
    McuUtility_Num32sToStrFormatted(buf, sizeof(buf), pvP, ' ', 5);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W");
    x = rightXpos - McuFontDisplay_GetStringWidth(buf, font, NULL);
    McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

    x = 7;
    y += totalHeight;
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"House:");
    McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
    McuUtility_Num32sToStrFormatted(buf, sizeof(buf), houseP, ' ', 5);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W");
    x = rightXpos - McuFontDisplay_GetStringWidth(buf, font, NULL);
    McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

    x = 7;
    y += totalHeight;
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"Grid:");
    McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);
    McuUtility_Num32sToStrFormatted(buf, sizeof(buf), gridP, ' ', 5);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W");
    x = rightXpos - McuFontDisplay_GetStringWidth(buf, font, NULL);
    McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_WHITE, &x, &y, font);

    McuGDisplaySSD1306_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void OledTask(void *pv) {
  float temperature = 20.0f, humidity = 50.0f;

  McuSSD1306_Init();
  McuTimeDate_Init();
#if PL_CONFIG_USE_SHT31
  McuSHT31_Init();
#endif
  for(;;) {
    ShowVHimage();
    vTaskDelay(pdMS_TO_TICKS(2000));
  #if PL_CONFIG_USE_SHT31
    McuSHT31_ReadTempHum(&temperature, &humidity);
    Sensor_ShowTemperature(temperature);
    vTaskDelay(pdMS_TO_TICKS(2000));
    Sensor_ShowHumidity(humidity);
    vTaskDelay(pdMS_TO_TICKS(2000));
  #endif
    ShowCenteredText((const unsigned char*)"Verkehrshaus\nder Schweiz", McuFontHelv12Bold_GetFont());
    vTaskDelay(pdMS_TO_TICKS(2000));
  #if PL_CONFIG_USE_OLED_CLOCK
    ShowDateTime();
  #endif
    ShowEnergy();
  }
}

void OLED_Init(void) {
  if (xTaskCreate(
      OledTask,  /* pointer to the task */
      "oled", /* task name for kernel awareness debugging */
      1500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating Shell task");
    for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_OLED */

