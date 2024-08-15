/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_OLED
#include "McuUtility.h"
#include "McuSSD1306.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "McuSSD1306.h"
#include "McuUtility.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuFontHelv10Normal.h"
#include "McuFontHelv12Normal.h"
#include "McuFontHelv18Bold.h"
#if PL_CONFIG_USE_SENSOR
  #include "sensor.h"
#endif

/*!
 * \brief Shows two lines of text centered on the display, with a border around it
 * \param text0 Line one of text
 * \param text1 Line two of text
 */
static void Show2Liner(const unsigned char *text0, const unsigned char *text1) {
  /*! \todo Make sure things are reentrant! */
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Lock();
  McuGDisplaySSD1306_DrawFilledBox(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE, McuGDisplaySSD1306_COLOR_PIXEL_CLR);
#else
  McuGDisplaySSD1306_Clear();
#endif
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth((unsigned char*)text0, font, NULL)/2;
  y = McuGDisplaySSD1306_GetHeight()/2 - (2*charHeight)/2; /* 2 lines */
  McuFontDisplay_WriteString((unsigned char*)text0, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth((unsigned char*)text1, font, NULL)/2;
  y += McuGDisplaySSD1306_GetHeight()/2 - (2*charHeight)/2;
  McuFontDisplay_WriteString((unsigned char*)text1, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-1-4, McuGDisplaySSD1306_GetHeight()-1-4, 1, McuGDisplaySSD1306_COLOR_BLUE);
#if PL_CONFIG_USE_OLED_LCD
  I2CBus_LockBus();
#endif
#if PL_CONFIG_USE_PARTIAL_UPDATE
  McuGDisplaySSD1306_UpdateRegion(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE);
#else
  McuGDisplaySSD1306_UpdateFull();
#endif
#if PL_CONFIG_USE_OLED_LCD
  I2CBus_ReleaseBus();
#endif
#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Unlock();
#endif
}

#if PL_CONFIG_USE_SENSOR
static void ShowSensorValues(void) {
  float t, h;
  unsigned char buf1[16], buf2[16];

  h = Sensor_GetHumidity();
  t = Sensor_GetTemperature();
  McuUtility_strcpy(buf1, sizeof(buf1), (unsigned char*)"T: ");
  McuUtility_strcatNumFloat(buf1, sizeof(buf1), t, 2);
  McuUtility_strcat(buf1, sizeof(buf1), (unsigned char*)" C");
  McuUtility_strcpy(buf2, sizeof(buf2), (unsigned char*)"H: ");
  McuUtility_strcatNumFloat(buf2, sizeof(buf2), h, 2);
  McuUtility_strcat(buf2, sizeof(buf2), (unsigned char*)" %");
  Show2Liner(buf1, buf2);
  vTaskDelay(pdMS_TO_TICKS(5000));
}
#endif

static void OledTask(void *pv) {
  McuSSD1306_Clear();
  Show2Liner((unsigned char*)"Welcome", (unsigned char*)"to");
  vTaskDelay(pdMS_TO_TICKS(3000));
  Show2Liner((unsigned char*)"picoRaspy", (unsigned char*)"V1.1");
  vTaskSuspend(NULL);
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void OLED_Init(void) {
  BaseType_t res;

  res = xTaskCreate(OledTask, "OledTask", (2*1024)/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+4, NULL);
  if (res!=pdPASS) {
    McuLog_fatal("creating OledTask task failed!");
  }
  McuSSD1306_Init();
  McuGDisplaySSD1306_Init();
}
#endif /* PL_CONFIG_USE_OLED */
