/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUILI9341_C_
#define MCUILI9341_C_

#include <stdint.h>
#include <stdbool.h>
#include "McuILI9341config.h"

#if MCUILI9341_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

  uint8_t McuILI9341_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
#endif

#define MCUILI9341_TFTWIDTH   240      /*!< ILI9341 max TFT width */
#define MCUILI9341_TFTHEIGHT  320      /*!< ILI9341 max TFT height */

/* Color definitions */
#define MCUILI9341_BLACK       0x0000  ///<   0,   0,   0
#define MCUILI9341_NAVY        0x000F  ///<   0,   0, 123
#define MCUILI9341_DARKGREEN   0x03E0  ///<   0, 125,   0
#define MCUILI9341_DARKCYAN    0x03EF  ///<   0, 125, 123
#define MCUILI9341_MAROON      0x7800  ///< 123,   0,   0
#define MCUILI9341_PURPLE      0x780F  ///< 123,   0, 123
#define MCUILI9341_OLIVE       0x7BE0  ///< 123, 125,   0
#define MCUILI9341_LIGHTGREY   0xC618  ///< 198, 195, 198
#define MCUILI9341_DARKGREY    0x7BEF  ///< 123, 125, 123
#define MCUILI9341_BLUE        0x001F  ///<   0,   0, 255
#define MCUILI9341_GREEN       0x07E0  ///<   0, 255,   0
#define MCUILI9341_CYAN        0x07FF  ///<   0, 255, 255
#define MCUILI9341_RED         0xF800  ///< 255,   0,   0
#define MCUILI9341_MAGENTA     0xF81F  ///< 255,   0, 255
#define MCUILI9341_YELLOW      0xFFE0  ///< 255, 255,   0
#define MCUILI9341_WHITE       0xFFFF  ///< 255, 255, 255
#define MCUILI9341_ORANGE      0xFD20  ///< 255, 165,   0
#define MCUILI9341_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define MCUILI9341_PINK        0xFC18  ///< 255, 130, 198

uint8_t McuILI9341_ClearDisplay(uint16_t color);

uint8_t McuILI9341_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

uint8_t McuILI9341_WritePixelData(uint16_t *pixels, size_t nofPixels);

uint8_t McuILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color); /* does set a window and writes pixel */

uint8_t McuILI9341_DrawBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

uint8_t McuILI9341_GetDisplayPowerMode(uint8_t *mode);

uint8_t McuILI9341_GetDisplayIdentification(uint8_t *manufacurer, uint8_t *driverVersion, uint8_t *driverID);

uint8_t McuILI9341_InvertDisplay(bool invert);

uint8_t McuILI9341_DisplayOn(bool on);

uint8_t McuILI9341_InitLCD(void);

void McuILI9341_Init(void);

#endif /* MCUILI9341_C_ */
