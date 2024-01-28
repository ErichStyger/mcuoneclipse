/**
 * \file
 * \brief Configuration header file for GDisplay
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the GDisplay module.
 */

#ifndef __GDisp1_CONFIG_H
#define __GDisp1_CONFIG_H

#ifndef GDisp1_CONFIG_DISPLAY_MODULE_NAME
  #define GDisp1_CONFIG_DISPLAY_MODULE_NAME LCD1
    /*!< Symbol name used for module */
#endif

#ifndef GDisp1_CONFIG_DISPLAY_HEADER_FILE
  #define GDisp1_CONFIG_DISPLAY_HEADER_FILE "LCD1.h"
    /*!< Header file to be included as interface to the display */
#endif
#include GDisp1_CONFIG_DISPLAY_HEADER_FILE  /* include LCD interface */

#ifndef GDisp1_CONFIG_USE_WINDOW_CAPABILITY
  #define GDisp1_CONFIG_USE_WINDOW_CAPABILITY  (0)
    /*!< 1: Use display window capability; 0: No display window capability */
#endif

#ifndef GDisp1_CONFIG_USE_DOUBLE_BUFFER
  #define GDisp1_CONFIG_USE_DOUBLE_BUFFER  (1)
    /*!< 1: Use double-buffering for display memory in RAM; 0: No display double-buffering */
#endif


#if GDisp1_CONFIG_USE_WINDOW_CAPABILITY
  #define GDisp1_CONFIG_FCT_NAME_OPENWINDOW     LCD1_OpenWindow
  #define GDisp1_CONFIG_FCT_NAME_WRITEPIXEL     LCD1_WritePixel
  #define GDisp1_CONFIG_FCT_NAME_CLOSEWINDOW    LCD1_CloseWindow
#else
  #define GDisp1_CONFIG_FCT_NAME_PUTPIXEL       LCD1_PutPixel
#endif
#if GDisp1_CONFIG_USE_DOUBLE_BUFFER
  #define GDisp1_CONFIG_FCT_NAME_CLEAR_BUFFER   LCD1_ClearBuffer
#endif

#ifndef GDisp1_CONFIG_USE_DISPLAY_MEMORY_WRITE
  #define GDisp1_CONFIG_USE_DISPLAY_MEMORY_WRITE  (0)
    /*!< 1: Use display memory write; 0: Do not use display memory write */
#endif

#ifndef GDisp1_CONFIG_INVERTED_PIXEL_COLOR
  #define GDisp1_CONFIG_INVERTED_PIXEL_COLOR  (0)
    /*!< 1: Invert pixel color; 0: Do not invert pixel color */
#endif

#ifndef GDisp1_CONFIG_NOF_BITS_PER_PIXEL
  #define GDisp1_CONFIG_NOF_BITS_PER_PIXEL  (16)
    /*!< Number of bits per pixel */
#endif

#ifndef GDisp1_CONFIG_CLEAR_DISPLAY_IN_INIT
  #define GDisp1_CONFIG_CLEAR_DISPLAY_IN_INIT  (0)
    /*!< 1: clear display during Init(); 0: do not clear display. */
#endif

#ifndef GDisp1_CONFIG_USE_DISPLAY_SHARING
  #define GDisp1_CONFIG_USE_DISPLAY_SHARING  (0)
  #define GDisp1_CONFIG_USE_DISPLAY_SHARING_OnGet   OnGetDisplay
  #define GDisp1_CONFIG_USE_DISPLAY_SHARING_OnGive  OnGiveDisplay
    /*!< 1: Share display and generate OnGetDisplay() and OnGiveDisplay() events. 0: do not share display */
#endif
/* prototypes */
extern void GDisp1_CONFIG_USE_DISPLAY_SHARING_OnGet(void);  /* called at the start of display critical section */
extern void GDisp1_CONFIG_USE_DISPLAY_SHARING_OnGive(void); /* called at the end of the display critical section */

#ifndef GDisp1_CONFIG_USE_MUTEX
  #define GDisp1_CONFIG_USE_MUTEX  (0)
    /*!< 1: use RTOS mutex for mutual access to display. 0: do not use mutex */
#endif

#endif /* __GDisp1_CONFIG_H */
