/**
 * \file
 * \brief Configuration header file for GDisplay
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the GDisplay module.
 */

#ifndef __McuGDisplaySSD1306_CONFIG_H
#define __McuGDisplaySSD1306_CONFIG_H

#ifndef McuGDisplaySSD1306_CONFIG_DISPLAY_MODULE_NAME
  #define McuGDisplaySSD1306_CONFIG_DISPLAY_MODULE_NAME McuSSD1306
    /*!< Symbol name used for module */
#endif

#ifndef McuGDisplaySSD1306_CONFIG_DISPLAY_HEADER_FILE
  #define McuGDisplaySSD1306_CONFIG_DISPLAY_HEADER_FILE "McuSSD1306.h"
    /*!< Header file to be included as interface to the display */
#endif
#include McuGDisplaySSD1306_CONFIG_DISPLAY_HEADER_FILE  /* include LCD interface */

#ifndef McuGDisplaySSD1306_CONFIG_USE_WINDOW_CAPABILITY
  #define McuGDisplaySSD1306_CONFIG_USE_WINDOW_CAPABILITY  (0)
    /*!< 1: Use display window capability; 0: No display window capability */
#endif

#ifndef McuGDisplaySSD1306_CONFIG_USE_DOUBLE_BUFFER
  #define McuGDisplaySSD1306_CONFIG_USE_DOUBLE_BUFFER  (1)
    /*!< 1: Use double-buffering for display memory in RAM; 0: No display double-buffering */
#endif

#if McuGDisplaySSD1306_CONFIG_USE_WINDOW_CAPABILITY
  #define McuGDisplaySSD1306_CONFIG_FCT_NAME_OPENWINDOW     McuSSD1306_OpenWindow
  #define McuGDisplaySSD1306_CONFIG_FCT_NAME_WRITEPIXEL     McuSSD1306_WritePixel
  #define McuGDisplaySSD1306_CONFIG_FCT_NAME_CLOSEWINDOW    McuSSD1306_CloseWindow
#else
  #define McuGDisplaySSD1306_CONFIG_FCT_NAME_PUTPIXEL       McuSSD1306_PutPixel
#endif
#if McuGDisplaySSD1306_CONFIG_USE_DOUBLE_BUFFER
  #define McuGDisplaySSD1306_CONFIG_FCT_NAME_CLEAR_BUFFER   McuSSD1306_ClearBuffer
#endif

#ifndef McuGDisplaySSD1306_CONFIG_USE_DISPLAY_MEMORY_WRITE
  #define McuGDisplaySSD1306_CONFIG_USE_DISPLAY_MEMORY_WRITE  (0)
    /*!< 1: Use display memory write; 0: Do not use display memory write */
#endif

#ifndef McuGDisplaySSD1306_CONFIG_INVERTED_PIXEL_COLOR
  #define McuGDisplaySSD1306_CONFIG_INVERTED_PIXEL_COLOR  (0)
    /*!< 1: Invert pixel color; 0: Do not invert pixel color */
#endif

#ifndef McuGDisplaySSD1306_CONFIG_NOF_BITS_PER_PIXEL
  #define McuGDisplaySSD1306_CONFIG_NOF_BITS_PER_PIXEL  (1)
    /*!< Number of bits per pixel */
#endif

#ifndef McuGDisplaySSD1306_CONFIG_CLEAR_DISPLAY_IN_INIT
  #define McuGDisplaySSD1306_CONFIG_CLEAR_DISPLAY_IN_INIT  (0)
    /*!< 1: clear display during Init(); 0: do not clear display. */
#endif

#ifndef McuGDisplaySSD1306_CONFIG_USE_DISPLAY_SHARING
  #define McuGDisplaySSD1306_CONFIG_USE_DISPLAY_SHARING  (0)
  #define McuGDisplaySSD1306_CONFIG_USE_DISPLAY_SHARING_OnGet   OnGetDisplay
  #define McuGDisplaySSD1306_CONFIG_USE_DISPLAY_SHARING_OnGive  OnGiveDisplay
    /*!< 1: Share display and generate OnGetDisplay() and OnGiveDisplay() events. 0: do not share display */
#endif
/* prototypes */
extern void McuGDisplaySSD1306_CONFIG_USE_DISPLAY_SHARING_OnGet(void);  /* called at the start of display critical section */
extern void McuGDisplaySSD1306_CONFIG_USE_DISPLAY_SHARING_OnGive(void); /* called at the end of the display critical section */

#ifndef McuGDisplaySSD1306_CONFIG_USE_MUTEX
  #define McuGDisplaySSD1306_CONFIG_USE_MUTEX  (0)
    /*!< 1: use RTOS mutex for mutual access to display. 0: do not use mutex */
#endif

#endif /* __McuGDisplaySSD1306_CONFIG_H */
