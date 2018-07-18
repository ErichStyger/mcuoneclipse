/**
 * \file
 * \brief Application configuration file for SSD1306 display driver
 *
 * This header file is a configuration header file to configure the module LCD1 (SSD1306).
 * You can configure the defines directly in this file or with the compiler -D option.
 */

#ifndef __LCD1_CONFIG_H
#define __LCD1_CONFIG_H

#ifndef LCD1_CONFIG_I2C_HEADER_FILE
  #define LCD1_CONFIG_I2C_HEADER_FILE   "GI2C1.h"
    /*!< Header file to be included for the SPI driver */
#endif

/* Which display is used */
#define LCD1_CONFIG_SSD1306_128X64      (1)
#define LCD1_CONFIG_SSD1306_128X32      (0)

#ifndef LCD1_CONFIG_SSD1306_HAS_RST
  #define LCD1_CONFIG_SSD1306_HAS_RST         (0)
  #define LCD1_CONFIG_SSD1306_RESET_LOW()     Reset_ClrVal() /* RESET signal low (reset is low active) */
  #define LCD1_CONFIG_SSD1306_RESET_HIGH()    Reset_SetVal() /* RESET signal high */
  #define LCD1_CONFIG_RESET_HEADER_FILE       "ResetPin.h"
#endif
#if LCD1_CONFIG_SSD1306_HAS_RST
  #include LCD1_CONFIG_RESET_HEADER_FILE  /* reset pin interface */
#endif

#ifndef LCD1_CONFIG_SSD1306_EXTERNAL
  #define LCD1_CONFIG_SSD1306_EXTERNAL        (0)
    /*!< set to 1 if external vcc is connected, otherwise 0 if internal dc/dc converter is used */
#endif
#ifndef LCD1_CONFIG_SSD1306_I2C_ADDR
  #define LCD1_CONFIG_SSD1306_I2C_ADDR        (60)
    /*!< I2C 7bit (unshifted) device address, usually 0x3C (0b11'1100) or 0x3D (0b11'1101) */
#endif

#ifndef LCD1_CONFIG_SSD1306_DRIVER_TYPE
  #define LCD1_CONFIG_SSD1306_DRIVER_TYPE        (1106)
    /*!< Either 1306 for SSD1306 or 1106 for SH1106 */
#endif

#ifndef LCD1_CONFIG_SSD1306_I2C_DELAY_US
  #define LCD1_CONFIG_SSD1306_I2C_DELAY_US    (100)
    /*!< I2C transaction delay in us */
#endif

#ifndef LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  #define LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION (0)
  /*!< 1: Use SetDisplayOrientation() to change display orientation at runtime; 0: fixed display orientation */
#endif

/* display orientation types used in macro below: */
#define LCD1_CONFIG_ORIENTATION_PORTRAIT      0
#define LCD1_CONFIG_ORIENTATION_PORTRAIT180   1
#define LCD1_CONFIG_ORIENTATION_LANDSCAPE     2
#define LCD1_CONFIG_ORIENTATION_LANDSCAPE180  3

#ifndef LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION
  #define LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION    LCD1_CONFIG_ORIENTATION_LANDSCAPE
  /*!< Fixed display orientation setting, one of:
    LCD1_CONFIG_ORIENTATION_PORTRAIT
    LCD1_CONFIG_ORIENTATION_PORTRAIT180
    LCD1_CONFIG_ORIENTATION_LANDSCAPE
    LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  */
#endif

#ifndef LCD1_CONFIG_CLEAR_DISPLAY_IN_INIT
  #define LCD1_CONFIG_CLEAR_DISPLAY_IN_INIT (0)
  /*!< 1: Clear display at the end of Init(); 0: Do not clear display at the end of Init() */
#endif

#ifndef LCD1_CONFIG_INIT_DELAY_MS
  #define LCD1_CONFIG_INIT_DELAY_MS     (5)
  /*!< Additional delay (milliseconds) in Init(). Use zero for no delay. */
#endif

#ifndef LCD1_CONFIG_USE_I2C_BLOCK_TRANSFER
  #define LCD1_CONFIG_USE_I2C_BLOCK_TRANSFER (1)
  /*!< 1: use I2C Block transfer for better performance. 0: disabled, e.g. for slower displays */
#endif

#ifndef LCD1_CONFIG_USE_RAM_BUFFER
  #define LCD1_CONFIG_USE_RAM_BUFFER    (1)
  /*!< 1: Use RAM Buffer for display memory; 0: Do not use RAM buffer (write directly to display) */
#endif

#endif /* __LCD1_CONFIG_H */
