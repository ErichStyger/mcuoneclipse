/**
 * \file
 * \brief Configuration header file for GDisplay
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
  #define GDisp1_CONFIG_USE_WINDOW_CAPABILITY  (1)
    /*!< 1: Use display window capability; 0: No display window capability */
#endif

#if GDisp1_CONFIG_USE_WINDOW_CAPABILITY
  #define GDisp1_CONFIG_FCT_NAME_OPENWINDOW     LCD1_OpenWindow
  #define GDisp1_CONFIG_FCT_NAME_WRITEPIXEL     LCD1_WritePixel
  #define GDisp1_CONFIG_FCT_NAME_CLOSEWINDOW    LCD1_CloseWindow
#else
  #define GDisp1_CONFIG_FCT_NAME_SETPIXEL       LCD1_SetPixel
  #define GDisp1_CONFIG_FCT_NAME_CLRPIXEL       LCD1_ClrPixel
#endif

#ifndef GDisp1_CONFIG_USE_DISPLAY_MEMORY_WRITE
  #define GDisp1_CONFIG_USE_DISPLAY_MEMORY_WRITE  (1)
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

#ifndef GDisp1_CONFIG_USE_MUTEX
  #define GDisp1_CONFIG_USE_MUTEX  (0)
    /*!< 1: use RTOS mutex for mutual access to display. 0: do not use mutex */
#endif

#endif /* __GDisp1_CONFIG_H */
