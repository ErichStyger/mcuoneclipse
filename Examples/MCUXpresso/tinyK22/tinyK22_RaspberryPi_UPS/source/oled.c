/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_OLED
#include "oled.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuArmTools.h"
#include "McuUtility.h"
#include "pin_mux.h"
#include "fsl_gpio.h"

#include "McuGenericI2C.h"
#include "McuSSD1306.h"
#include "McuGDisplaySSD1306.h"

#include "McuFontDisplay.h"
#include "McuGFont.h"
#include "McuFontCour08Normal.h"
#include "McuFontHelv12Bold.h"

/* enum for line numbers */
typedef enum OLED_Line_e {
#if PL_CONFIG_USE_GATEWAY
  OLED_LINE_RX_TX,
#endif
#if PL_CONFIG_USE_UPS
  OLED_LINE_UPS,
#endif
#if PL_CONFIG_USE_SHT31 || PL_CONFIG_USE_SHT40
  OLED_LINE_SHT,
#endif
#if PL_CONFIG_USE_SHUTDOWN
  OLED_LINE_SHUTDOWN_0,
  OLED_LINE_SHUTDOWN_1,
  OLED_LINE_SHUTDOWN_2,
#endif
  OLED_LINE_LAST
} OLED_Line_e;


#define OLED_FIXED_FONTH_CHAR_WIDTH  (5) /* a char needs this number of pixels */
#define OLED_NOF_CHARS_ON_LINE  (McuSSD1306_DISPLAY_HW_NOF_COLUMNS/OLED_FIXED_FONTH_CHAR_WIDTH)

#if PL_CONFIG_USE_SHT31 || PL_CONFIG_USE_SHUTDOWN || PL_CONFIG_USE_UPS
static void WritePadStringLine(uint8_t *buf, size_t bufSize, uint8_t *str, OLED_Line_e line) {
  buf[0] = '\0';
  McuUtility_strcatPad(buf, bufSize, str, ' ', bufSize); /* pad with spaces */
  McuSSD1306_PrintString(line, 0, buf);
}
#endif

#if PL_CONFIG_USE_SHUTDOWN
void OLED_PrintShutdownHelp(void) {
  uint8_t buf[OLED_NOF_CHARS_ON_LINE];

  WritePadStringLine(buf, sizeof(buf), (uint8_t*)"Press CENTER to", OLED_LINE_SHUTDOWN_0);
  WritePadStringLine(buf, sizeof(buf), (uint8_t*)"request power down", OLED_LINE_SHUTDOWN_1);
  WritePadStringLine(buf, sizeof(buf), (uint8_t*)"", OLED_LINE_SHUTDOWN_2);}

void OLED_PrintShutdownMsg(void) {
  uint8_t buf[OLED_NOF_CHARS_ON_LINE];

  WritePadStringLine(buf, sizeof(buf), (uint8_t*)"Powering down...", OLED_LINE_SHUTDOWN_0);
  WritePadStringLine(buf, sizeof(buf), (uint8_t*)"Wait for the red LED", OLED_LINE_SHUTDOWN_1);
  WritePadStringLine(buf, sizeof(buf), (uint8_t*)"********************", OLED_LINE_SHUTDOWN_2);}
#endif

#if PL_CONFIG_USE_UPS
void OLED_ShowUPS(float voltage, float charge, bool isCharging) {
  uint8_t linebuf[OLED_NOF_CHARS_ON_LINE];
  uint8_t buf[24], fbuf[6];

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"UPS: ");
  McuUtility_NumFloatToStr(fbuf, sizeof(fbuf), voltage, 1);
  McuUtility_strcat(buf, sizeof(buf), fbuf);

  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"V, ");
  McuUtility_NumFloatToStr(fbuf, sizeof(fbuf), charge, 1);
  McuUtility_strcat(buf, sizeof(buf), fbuf);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"%");
  if (isCharging) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", c:y");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", c:n");
  }
  /* write string */
  WritePadStringLine(linebuf, sizeof(linebuf), buf, OLED_LINE_UPS);
}
#endif

#if PL_CONFIG_USE_GATEWAY
void OLED_ShowRxTx(uint32_t nofRx, uint32_t nofTx) {
  uint8_t linebuf[OLED_NOF_CHARS_ON_LINE];
  uint8_t buf[24];

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"Tx: ");
  McuUtility_strcatNum32u(buf, sizeof(buf), nofRx);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", Rx: ");
  McuUtility_strcatNum32u(buf, sizeof(buf), nofTx);
  /* write string */
  WritePadStringLine(linebuf, sizeof(linebuf), buf, OLED_LINE_RX_TX);
}
#endif

#if PL_CONFIG_USE_SHT31 || PL_CONFIG_USE_SHT40
void OLED_ShowTemperatureHumidity(float temperature, float humidity) {
  uint8_t linebuf[OLED_NOF_CHARS_ON_LINE];
  uint8_t buf[24], fbuf[6];

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"T: ");
  McuUtility_NumFloatToStr(fbuf, sizeof(fbuf), temperature, 1);
  McuUtility_strcat(buf, sizeof(buf), fbuf);

  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"C, H: ");
  McuUtility_NumFloatToStr(fbuf, sizeof(fbuf), humidity, 1);
  McuUtility_strcat(buf, sizeof(buf), fbuf);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"%");
  /* write string */
  WritePadStringLine(linebuf, sizeof(linebuf), buf, OLED_LINE_SHT);
}
#endif

void doOLED(void) {
#if 1 /* text only */
  uint8_t buf[24];
  uint32_t cntr = 0;

  McuSSD1306_Clear();
  for(;;) {
    //GPIO_PortToggle(BOARD_LEDBLUE_GPIO, (1<<BOARD_LEDBLUE_PIN));
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"Counter: ");
    McuUtility_strcatNum32u(buf, sizeof(buf), cntr);
    cntr++;
    McuSSD1306_PrintString(0, 0, buf);

    McuSSD1306_PrintString(1, 0, (unsigned char*)"Hello\nWorld!");
    McuSSD1306_PrintString(3, 0, (unsigned char*)"the quick\nbrown fox\njumps over\nthe lazy");
    McuSSD1306_PrintString(7, 0, (unsigned char*)"dog");

    McuWait_Waitms(100);
  }
#elif 0 /* graphics */
  McuGDisplaySSD1306_Init();
  McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE);
  for (;;) {
    int i;
    McuGDisplaySSD1306_Clear();
    for(i=0; i<10; i++) {
      McuGDisplaySSD1306_DrawBox(i*2, i*2, McuGDisplaySSD1306_GetWidth()-1- 2*(i*2), McuGDisplaySSD1306_GetHeight()-1- 2*(i*2), 1, McuGDisplaySSD1306_COLOR_BLUE);
    }

    for(i=0;i<10;i++) {
      McuGDisplaySSD1306_DrawCircle((McuGDisplaySSD1306_GetWidth()-1)/2, (McuGDisplaySSD1306_GetHeight()-1)/2, i*3, McuGDisplaySSD1306_COLOR_BLUE);
    }
    McuGDisplaySSD1306_UpdateFull();
  }
#else /* Fonts */
  uint32_t cntr = 0;
  uint8_t buf[24];

  McuGDisplaySSD1306_Init();
  McuFontDisplay_PixelDim x, y;

  McuFontDisplay_Init();
  McuGFont_Init();
  McuFontCour08Normal_Init();
  McuFontHelv12Bold_Init();
  for(;;) {
    McuFontDisplay_PixelDim charHeight, totalHeight;

    McuGDisplaySSD1306_Clear();
    x = y = 0;
    McuFontDisplay_WriteString((uint8_t*)"hello ", McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuGFont_GetFont());
    McuFontDisplay_WriteString((uint8_t*)"World", McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontCour08Normal_GetFont());
#if 0
    x = 0;
    McuFontDisplay_GetFontHeight(McuGFont_GetFont(), &charHeight, &totalHeight);
    y+= totalHeight;
    McuFontDisplay_WriteString((uint8_t*)"Helv12Bold", McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv12Bold_GetFont());
#endif
    McuFontDisplay_GetFontHeight(McuFontCour08Normal_GetFont(), &charHeight, &totalHeight);
    y+= totalHeight;
    x = 0;
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"Counter: ");
    McuUtility_strcatNum32u(buf, sizeof(buf), cntr);
    cntr++;
    McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv12Bold_GetFont());

    McuGDisplaySSD1306_UpdateFull();
  }
#endif
}

static void OledTask(void *pv) {
  vTaskDelay(pdMS_TO_TICKS(100)); /* give hardware time to power up */
  McuSSD1306_Init(); /* requires I2C interrupts enabled if using HW I2C! */
#if TINYK22_HAT_VERSION>=4
  McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE);
#else
  McuGDisplaySSD1306_SetDisplayOrientation(McuGDisplaySSD1306_ORIENTATION_LANDSCAPE180);
#endif
  McuSSD1306_Clear();
  for(;;) {
    int i;
    McuGDisplaySSD1306_Clear();
    for(i=0; i<10; i++) {
      McuGDisplaySSD1306_DrawBox(i*2, i*2, McuGDisplaySSD1306_GetWidth()-1- 2*(i*2), McuGDisplaySSD1306_GetHeight()-1- 2*(i*2), 1, McuGDisplaySSD1306_COLOR_BLUE);
    }
    McuGDisplaySSD1306_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(500));
    for(i=0;i<10;i++) {
      McuGDisplaySSD1306_DrawCircle((McuGDisplaySSD1306_GetWidth()-1)/2, (McuGDisplaySSD1306_GetHeight()-1)/2, i*3, McuGDisplaySSD1306_COLOR_BLUE);
    }
    McuGDisplaySSD1306_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void OLED_Init(void) {
  if (xTaskCreate(OledTask, "Oled", 1*1024/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

void OLED_DeInit(void) {
}
#endif
