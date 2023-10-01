/**
 * \file
 * \brief Configuration header file for LCDHTA
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the character LCD module.
 */

#ifndef __McuHD44780_CONFIG_H
#define __McuHD44780_CONFIG_H

#ifndef McuHD44780_CONFIG_LCD_TYPE
  #define McuHD44780_CONFIG_LCD_TYPE   (0)
    /*!< 1: Diplaytech 162c: use different timing than the default. 0: use default timing */
#endif

#define McuHD44780_CONFIG_LCD_NOF_LINES                        (2) /* 1, 2, 3 or 4 */

#define McuHD44780_CONFIG_LCD_DATA_BUS_WIDTH                   (8) /* 4 or 8 */

#define McuHD44780_CONFIG_LCD_DATA_BUS_PORT_8BIT               (0)
  /*!< 1: using 8bit data port; 0: not using 8bit data port */

#include "RS1.h" /* RS signal pin header file */
#include "EN1.h" /* EN signal pin header file */
#if McuHD44780_CONFIG_LCD_DATA_BUS_WIDTH==8 /* extra includes for 8bit data bus */
  #include "DB01.h" /* DB0 signal pin header file */
  #include "DB11.h" /* DB1 signal pin header file */
  #include "DB21.h" /* DB2 signal pin header file */
  #include "DB31.h" /* DB3 signal pin header file */
#endif /* McuHD44780_CONFIG_LCD_DATA_BUS_WIDTH==8 */
#include "DB41.h" /* DB4 signal pin header file */
#include "DB51.h" /* DB5 signal pin header file */
#include "DB61.h" /* DB6 signal pin header file */
#include "DB71.h" /* DB7 signal pin header file */

#ifndef McuHD44780_CONFIG_USE_E2_SIGNAL
  #define McuHD44780_CONFIG_USE_E2_SIGNAL   (1)
  /*!< 1: Use E2 signal to control upper and lower half of display. 0: do not use E2 signal */
#endif

#if McuHD44780_CONFIG_USE_E2_SIGNAL
  #include "EN2.h"
#endif

#ifndef McuHD44780_CONFIG_USE_DISPLAY_READ
  #define McuHD44780_CONFIG_USE_DISPLAY_READ   (1)
  /*!< 1: Read from the display. Requires R/W signal. 0: do not read from the display */
#endif

#ifndef McuHD44780_CONFIG_USE_DISPLAY_READ_CHECK_BUSY_FLAG
#if McuHD44780_CONFIG_USE_DISPLAY_READ && McuHD44780_CONFIG_USE_DISPLAY_READ_CHECK_BUSY_FLAG
  #define McuHD44780_CONFIG_USE_DISPLAY_READ_CHECK_BUSY_FLAG   (1 && McuHD44780_CONFIG_USE_DISPLAY_READ)
#else
  #define McuHD44780_CONFIG_USE_DISPLAY_READ_CHECK_BUSY_FLAG   (0 && McuHD44780_CONFIG_USE_DISPLAY_READ)
#endif
  /*!< 1: Check the busy flag Requires reading from the display. 0: do not check busy flag */
#endif

#ifndef McuHD44780_CONFIG_USE_RW_SIGNAL
  #define McuHD44780_CONFIG_USE_RW_SIGNAL   (1 && McuHD44780_CONFIG_USE_DISPLAY_READ)
  /*!< 1: Use RW signal to read/write from the display. 0: do not use RW signal */
#endif

#if McuHD44780_CONFIG_USE_RW_SIGNAL
  #include "RW1.h"
#endif

#define McuHD44780_CONFIG_WAIT_DISPLAY_US                      0 /* wait time as specified in properties */
#define McuHD44780_CONFIG_WAIT_LCD_CMD_AFTER_4BIT_DATA1_US     15 /* wait time after first 4bit data */
#define McuHD44780_CONFIG_WAIT_LCD_CMD_AFTER_4BIT_DATA2_US     60 /* wait time after second 4bit data */

#endif /* __McuHD44780_CONFIG_H */
