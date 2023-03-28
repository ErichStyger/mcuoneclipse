/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GUI_CONFIG_H_
#define GUI_CONFIG_H_

#include "app_platform.h"

#define GUI_CONFIG_USE_SCREENSAVER         (1)
  /*!< if using a screensaver or not */

#if GUI_CONFIG_USE_SCREENSAVER
  #define GUI_CONFIG_TIMEOUT_USER_ACTION_SEC      (10*60)
    /*!< Time in seconds with no user (button) interaction after which it will do screen cycling (or screen saving). */
#endif

#define GUI_CONFIG_USE_CYCLING_SCREEN      (1)
  /*!< if a cycling screen or not */

#if GUI_CONFIG_USE_CYCLING_SCREEN
  #define GUI_CONFIG_SCREEN_CYLCING_INTERVAL_SEC  (5)
    /*!< Time in seconds between the screen cycling (logos, energy status, ...) */
#endif

#if GUI_CONFIG_USE_CYCLING_SCREEN && GUI_CONFIG_USE_SCREENSAVER
  #define GUI_CONFIG_NOF_SCREEN_CYCLING_UNTIL_DISPLAY_OFF  (3)
    /*!< Number of complete screen cycling until it enters low power mode with the display turning off */
#endif

#ifndef GUI_CONFIG_USE_SENSOR
  #define GUI_CONFIG_USE_SENSOR  (1 && PL_CONFIG_USE_SENSOR)
#endif

#endif /* GUI_CONFIG_H_ */
