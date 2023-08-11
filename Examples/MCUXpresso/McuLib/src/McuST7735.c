/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * Register values and driver IC initialization: https://github.com/afiskon/stm32-st7735
 */

#include "McuST7735.h"

#if McuST7735_CONFIG_IS_ENABLED
#include "McuSPI.h"
#include "McuGPIO.h"
#include "McuLog.h"
#include "McuWait.h"
#include <stdbool.h>

#define McuST7735_DELAY 0x80

#define McuST7735_MADCTL_MY  0x80
#define McuST7735_MADCTL_MX  0x40
#define McuST7735_MADCTL_MV  0x20
#define McuST7735_MADCTL_ML  0x10
#define McuST7735_MADCTL_RGB 0x00
#define McuST7735_MADCTL_BGR 0x08
#define McuST7735_MADCTL_MH  0x04

#define McuST7735_NOP     0x00
#define McuST7735_SWRESET 0x01
#define McuST7735_RDDID   0x04
#define McuST7735_RDDST   0x09

#define McuST7735_SLPIN   0x10
#define McuST7735_SLPOUT  0x11
#define McuST7735_PTLON   0x12
#define McuST7735_NORON   0x13

#define McuST7735_INVOFF  0x20
#define McuST7735_INVON   0x21
#define McuST7735_DISPOFF 0x28
#define McuST7735_DISPON  0x29
#define McuST7735_CASET   0x2A
#define McuST7735_RASET   0x2B
#define McuST7735_RAMWR   0x2C
#define McuST7735_RAMRD   0x2E

#define McuST7735_PTLAR   0x30
#define McuST7735_COLMOD  0x3A
#define McuST7735_MADCTL  0x36

#define McuST7735_FRMCTR1 0xB1
#define McuST7735_FRMCTR2 0xB2
#define McuST7735_FRMCTR3 0xB3
#define McuST7735_INVCTR  0xB4
#define McuST7735_DISSET5 0xB6

#define McuST7735_PWCTR1  0xC0
#define McuST7735_PWCTR2  0xC1
#define McuST7735_PWCTR3  0xC2
#define McuST7735_PWCTR4  0xC3
#define McuST7735_PWCTR5  0xC4
#define McuST7735_VMCTR1  0xC5

#define McuST7735_RDID1   0xDA
#define McuST7735_RDID2   0xDB
#define McuST7735_RDID3   0xDC
#define McuST7735_RDID4   0xDD

#define McuST7735_PWCTR6  0xFC

#define McuST7735_GMCTRP1 0xE0
#define McuST7735_GMCTRN1 0xE1

static int16_t curr_width;       /*!< current display with, based on rotation */
static int16_t curr_height;      /*!< current display height, based on rotation */
static uint8_t curr_rotation;    /*!< current display rotation: 0, 1, 2 or 4 */
static uint8_t curr_xstart;      /*!< current x starting position, based on rotation */
static uint8_t curr_ystart;      /*!< current y starting position, based on rotation */

/* different displays have different column and row start values */
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
  #define McuST7735_HW_COL_START   24
  #define McuST7735_HW_ROW_START   0
#elif McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_128X128
  #define McuST7735_HW_COL_START   2
  #define McuST7735_HW_ROW_START   3
#elif McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160x128
  #define McuST7735_HW_COL_START   0
  #define McuST7735_HW_ROW_START   0
#endif


static McuGPIO_Handle_t csPin;    /* CS pin, LOW active, used to select device (chip select) */
static McuGPIO_Handle_t resetPin; /* RESET pin, LOW active, used to reset device  */
static McuGPIO_Handle_t dcPin;    /* DC pin (data or command), LOW active, used to send commands (low) and data (high) */

#define McuST7735_Select()        McuGPIO_SetLow(csPin)
#define McuST7735_Unselect()      McuGPIO_SetHigh(csPin)
#define McuST7735_SetDataMode()   McuGPIO_SetHigh(dcPin)
#define McuST7735_SetCmdMode()    McuGPIO_SetLow(dcPin)

uint16_t McuST7735_GetWidth(void) {
  return curr_width;
}

uint16_t McuST7735_GetHeight(void) {
  return curr_height;
}

static uint8_t McuST7735_WriteSPI(unsigned char *data, size_t dataSize) {
  McuSPI_SendReceiveBlock(data, NULL, dataSize);
  return ERR_OK;
}

static void McuST7735_WriteCommand(uint8_t cmd) {
  uint8_t error = 0;

  McuST7735_SetCmdMode();
  error = McuST7735_WriteSPI(&cmd, sizeof(cmd));
}

static void McuST7735_WriteData(uint8_t* data, size_t dataSize) {
  McuST7735_SetDataMode();
  McuST7735_WriteSPI(data, dataSize);
}

void McuST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
  McuST7735_WriteCommand(McuST7735_CASET); /* column address set */
  uint8_t data[] = { 0x00, x0 + curr_xstart, 0x00, x1 + curr_xstart };
  McuST7735_WriteData(data, sizeof(data));

  McuST7735_WriteCommand(McuST7735_RASET); /* row address set */
  data[1] = y0 + curr_ystart;
  data[3] = y1 + curr_ystart;
  McuST7735_WriteData(data, sizeof(data));

  McuST7735_WriteCommand(McuST7735_RAMWR); /* write to RAM */
}

void McuST7735_SetRotation(uint8_t m) {
  uint8_t madctl = 0;

  curr_rotation = m%4; /* can only 0-3 */
  switch (curr_rotation) {
  case 0:
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
    madctl = McuST7735_MADCTL_MX | McuST7735_MADCTL_MY | McuST7735_MADCTL_BGR;
#else
    madctl = McuST7735_MADCTL_MX | McuST7735_MADCTL_MY | McuST7735_MADCTL_RGB;
    curr_height = McuST7735_GetHwHeight();
    curr_width = McuST7735_GetHwWidth();
    curr_xstart = McuST7735_HW_COL_START;
    curr_ystart = McuST7735_HW_ROW_START;
#endif
    break;
  case 1:
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
    madctl = McuST7735_MADCTL_MY | McuST7735_MADCTL_MV | McuST7735_MADCTL_BGR;
#else
    madctl = McuST7735_MADCTL_MY | McuST7735_MADCTL_MV | McuST7735_MADCTL_RGB;
    curr_width = McuST7735_GetHwHeight();
    curr_height = McuST7735_GetHwWidth();
    curr_ystart = McuST7735_HW_COL_START;
    curr_xstart = McuST7735_HW_ROW_START;
#endif
    break;
  case 2:
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
    madctl = McuST7735_MADCTL_BGR;
#else
    madctl = McuST7735_MADCTL_RGB;
    curr_height = McuST7735_GetHwHeight();
    curr_width = McuST7735_GetHwWidth();
    curr_xstart = McuST7735_HW_COL_START;
    curr_ystart = McuST7735_HW_ROW_START;
#endif
    break;
  case 3:
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
    madctl = McuST7735_MADCTL_MX | McuST7735_MADCTL_MV | McuST7735_MADCTL_BGR;
#else
    madctl = McuST7735_MADCTL_MX | McuST7735_MADCTL_MV | McuST7735_MADCTL_RGB;
    curr_width = McuST7735_GetHwHeight();
    curr_height = McuST7735_GetHwWidth();
    curr_ystart = McuST7735_HW_COL_START;
    curr_xstart = McuST7735_HW_ROW_START;
#endif
    break;
  } /* switch */
  McuST7735_Select();
  McuST7735_WriteCommand(McuST7735_MADCTL);
  McuST7735_WriteData(&madctl,1);
  McuST7735_Unselect();
}

void McuST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
  if((x >= curr_width) || (y >= curr_height)) {
    return;
  }
  McuST7735_Select();

  McuST7735_SetAddressWindow(x, y, x+1, y+1);
  uint8_t data[] = { color>>8, color&0xFF };
  McuST7735_WriteData(data, sizeof(data));

  McuST7735_Unselect();
}

void McuST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
  if((x >= curr_width) || (y >= curr_height)) {
    return;
  }
  if((x + w - 1) >= curr_width) {
    w = curr_width - x;
  }
  if((y + h - 1) >= curr_height) {
    h = curr_height - y;
  }

  McuST7735_Select();
  McuST7735_SetAddressWindow(x, y, x+w-1, y+h-1);

  uint8_t data[] = { color >> 8, color & 0xFF };
  McuST7735_SetDataMode();
  for(y = h; y > 0; y--) {
    for(x = w; x > 0; x--) {
      McuST7735_WriteSPI(data, sizeof(data));
    }
  }
  McuST7735_Unselect();
}

void McuST7735_InvertColors(bool invert) {
  McuST7735_Select();
  McuST7735_WriteCommand(invert ? McuST7735_INVON : McuST7735_INVOFF);
  McuST7735_Unselect();
}

void McuST7735_Reset(void) {
  McuGPIO_SetLow(resetPin);
  McuWait_Waitms(5);
  McuGPIO_SetHigh(resetPin);
}

static void SendDisplayInitCommands(const uint8_t *addr) {
  uint8_t numCommands, numArgs;
  uint16_t ms;

  numCommands = *addr++;
  while(numCommands--) {
    uint8_t cmd = *addr++;
    McuST7735_WriteCommand(cmd);

    numArgs = *addr++;
    /* If high bit set, delay follows args */
    ms = numArgs & McuST7735_DELAY;
    numArgs &= ~McuST7735_DELAY;
    if(numArgs) {
        McuST7735_WriteData((uint8_t*)addr, numArgs);
        addr += numArgs;
    }
    if(ms) {
      ms = *addr++;
      if(ms == 255) {
        ms = 500;
      }
      McuWait_Waitms(ms);
    }
  }
}

static const uint8_t
  init_cmds1[] = {            // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    McuST7735_SWRESET,   McuST7735_DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
      McuST7735_SLPOUT ,   McuST7735_DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    McuST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    McuST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    McuST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    McuST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    McuST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    McuST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    McuST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    McuST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,
    McuST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    McuST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    McuST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    McuST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_128X128 || McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X128
  init_cmds2[] = {            // Init for 7735R, part 2 (1.44" display)
    2,                        //  2 commands in list:
    McuST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    McuST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F },           //     XEND = 127
#endif
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
  init_cmds2[] = {            // Init for 7735S, part 2 (160x80 display)
    3,                        //  3 commands in list:
    McuST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x4F,             //     XEND = 79
    McuST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x9F ,            //     XEND = 159
    McuST7735_INVON, 0 },        //  3: Invert colors
#endif
  init_cmds3[] = {            // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    McuST7735_GMCTRP1, 16      , //  1: Magical unicorn dust, 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    McuST7735_GMCTRN1, 16      , //  2: Sparkles and rainbows, 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    McuST7735_NORON  ,    McuST7735_DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    McuST7735_DISPON ,    McuST7735_DELAY, //  4: Main screen turn on, no args w/delay
      100 };                  //     100 ms delay

static void InitDisplay(uint8_t rotation) {
  McuST7735_Select();
  McuST7735_Reset();
  SendDisplayInitCommands(init_cmds1);
  SendDisplayInitCommands(init_cmds2);
  SendDisplayInitCommands(init_cmds3);
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
  /* not tested yet, might not work! */
  uint8_t data = 0xC0;
  ST7735_Select();
  ST7735_WriteCommand(ST7735_MADCTL);
  ST7735_WriteData(&data,1);
  ST7735_Unselect();
#endif
  McuST7735_SetRotation (rotation);
  McuST7735_Unselect();
}

static void InitPins(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);

#if McuLib_CONFIG_CPU_IS_ESP32
  config.hw.pin = McuST7735_CONFIG_CS_PIN_NUMBER;
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  config.hw.pin   = McuST7735_CONFIG_CS_PIN_NUMBER;
#else
  config.hw.gpio  = McuST7735_CONFIG_CS_PIN_GPIO;
  config.hw.port  = McuST7735_CONFIG_CS_PIN_PORT;
  config.hw.pin   = McuST7735_CONFIG_CS_PIN_NUMBER;
#endif
  config.isInput = false;
  config.isHighOnInit = true; /* CS is Low active, set it to high (deactivated) */

  csPin = McuGPIO_InitGPIO(&config);
  if (csPin==NULL) {
    McuLog_fatal("failed initializing display CS pin");
    for(;;) {} /* error */
  }

#if McuLib_CONFIG_CPU_IS_ESP32
  config.hw.pin = McuST7735_CONFIG_DC_PIN_NUMBER;
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  config.hw.pin   = McuST7735_CONFIG_DC_PIN_NUMBER;
#else
  config.hw.gpio  = McuST7735_CONFIG_DC_PIN_GPIO;
  config.hw.port  = McuST7735_CONFIG_DC_PIN_PORT;
  config.hw.pin   = McuST7735_CONFIG_DC_PIN_NUMBER;
#endif
  config.isInput = false;
  config.isHighOnInit = false; /* DC initially low, command mode */

  dcPin = McuGPIO_InitGPIO(&config);
  if (dcPin==NULL) {
    McuLog_fatal("failed initializing display DC pin");
    for(;;) {} /* error */
  }

#if McuLib_CONFIG_CPU_IS_ESP32
  config.hw.pin = McuST7735_CONFIG_RESET_PIN_NUMBER;
#elif McuLib_CONFIG_CPU_IS_RPxxxx
  config.hw.pin   = McuST7735_CONFIG_RESET_PIN_NUMBER;
#else
  config.hw.gpio  = McuST7735_CONFIG_RESET_PIN_GPIO;
  config.hw.port  = McuST7735_CONFIG_RESET_PIN_PORT;
  config.hw.pin   = McuST7735_CONFIG_RESET_PIN_NUMBER;
#endif
  config.isInput = false;
  config.isHighOnInit = true; /* RESET is LOW active */

  resetPin = McuGPIO_InitGPIO(&config);
  if (resetPin==NULL) {
    McuLog_fatal("failed initializing display RESET pin");
    for(;;) {} /* error */
  }
}

void McuST7735_Init(void) {
  InitPins();
  InitDisplay(0);
}

#endif /* McuST7735_CONFIG_IS_ENABLED */
