/**
 * \file
 * \brief Application configuration file for SSD1306 display driver
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is a configuration header file to configure the module McuSSD1306 (SSD1306).
 * You can configure the defines directly in this file or with the compiler -D option.
 */

#ifndef __McuSSD1306_CONFIG_H
#define __McuSSD1306_CONFIG_H

#ifndef McuSSD1306_CONFIG_I2C_HEADER_FILE
  #define McuSSD1306_CONFIG_I2C_HEADER_FILE "McuGenericI2C.h"
    /*!< Header file to be included for the SPI driver */
#endif

/* Which display is used: only one of the two options below can be enabled: */
#define McuSSD1306_CONFIG_SSD1306_SIZE_TYPE (12864)
  /*!< either 12864 (128x64) or 12832 (128x32) */

#ifndef McuSSD1306_CONFIG_SSD1306_HAS_RST
  #define McuSSD1306_CONFIG_SSD1306_HAS_RST         (0)
  #define McuSSD1306_CONFIG_SSD1306_RESET_LOW()     Reset_ClrVal() /* RESET signal low (reset is low active) */
  #define McuSSD1306_CONFIG_SSD1306_RESET_HIGH()    Reset_SetVal() /* RESET signal high */
  #define McuSSD1306_CONFIG_RESET_HEADER_FILE       "ResetPin.h"
#endif
#if McuSSD1306_CONFIG_SSD1306_HAS_RST
  #include McuSSD1306_CONFIG_RESET_HEADER_FILE  /* reset pin interface */
#endif

#ifndef McuSSD1306_CONFIG_SSD1306_EXTERNAL
  #define McuSSD1306_CONFIG_SSD1306_EXTERNAL        (0)
    /*!< set to 1 if external vcc is connected, otherwise 0 if internal dc/dc converter is used */
#endif
#ifndef McuSSD1306_CONFIG_SSD1306_I2C_ADDR
  #define McuSSD1306_CONFIG_SSD1306_I2C_ADDR        (60)
    /*!< I2C 7bit (unshifted) device address, usually 0x3C (60) (0b11'1100) or 0x3D (61) (0b11'1101) */
#endif

#ifndef McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE        (1306)
    /*!< Either 1306 for SSD1306 or 1106 for SH1106 */
#endif

#ifndef McuSSD1306_CONFIG_SSD1306_START_COLUMN_OFFSET
  #define McuSSD1306_CONFIG_SSD1306_START_COLUMN_OFFSET  (0)
    /*!< Some SH1106 displays need a start column of 2 instead of the default 0 */
#endif

#ifndef McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US
  #define McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US    (0)
    /*!< I2C transaction delay in us */
#endif

#ifndef McuSSD1306_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  #define McuSSD1306_CONFIG_DYNAMIC_DISPLAY_ORIENTATION (0)
  /*!< 1: Use SetDisplayOrientation() to change display orientation at runtime; 0: fixed display orientation */
#endif

/* display orientation types used in macro below: */
#define McuSSD1306_CONFIG_ORIENTATION_PORTRAIT      0
#define McuSSD1306_CONFIG_ORIENTATION_PORTRAIT180   1
#define McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE     2
#define McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE180  3

#ifndef McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION
  #define McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION    McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE
  /*!< Fixed display orientation setting, one of:
    McuSSD1306_CONFIG_ORIENTATION_PORTRAIT
    McuSSD1306_CONFIG_ORIENTATION_PORTRAIT180
    McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE
    McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE180
  */
#endif

#ifndef McuSSD1306_CONFIG_INITIALIZE_IN_INIT
  #define McuSSD1306_CONFIG_INITIALIZE_IN_INIT (1)
  /*!< 1: Initialize LCD during PE_low_level_init(); 0: Do not initialize during PE_low_level_init() */
#endif

#ifndef McuSSD1306_CONFIG_CLEAR_DISPLAY_IN_INIT
  #define McuSSD1306_CONFIG_CLEAR_DISPLAY_IN_INIT (0)
  /*!< 1: Clear display at the end of Init(); 0: Do not clear display at the end of Init() */
#endif

#ifndef McuSSD1306_CONFIG_INIT_DELAY_MS
  #define McuSSD1306_CONFIG_INIT_DELAY_MS (100)
  /*!< Additional delay (milliseconds) in Init(). Use zero for no delay. */
#endif

#ifndef McuSSD1306_CONFIG_USE_I2C_BLOCK_TRANSFER
  #define McuSSD1306_CONFIG_USE_I2C_BLOCK_TRANSFER (1)
  /*!< 1: use I2C Block transfer for better performance. 0: disabled, e.g. for slower displays */
#endif

#ifndef McuSSD1306_CONFIG_USE_RAM_BUFFER
  #define McuSSD1306_CONFIG_USE_RAM_BUFFER (1)
  /*!< 1: Use RAM Buffer for display memory; 0: Do not use RAM buffer (write directly to display) */
#endif

#endif /* __McuSSD1306_CONFIG_H */
