/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUWATCHDOG_CONFIG_H_
#define MCUWATCHDOG_CONFIG_H_

#include "app_platform.h"

#ifndef McuWatchdog_CONFIG_USE_WATCHDOG
  #define McuWatchdog_CONFIG_USE_WATCHDOG (0)
#endif

#define McuWatchdog_CONFIG_HEALT_CHECK_TIME_SEC (5)  /*!< interval for checking health */

#define McuWatchdog_CONFIG_TIMEOUT_MS   (1000) /*!< number of ms for hardware watchdog timer */

#define McuWatchdog_CONFIG_DISABLED_FOR_DEBUG (0)  /* set to 1 for easier debugging, set to 0 for production code! */
#define McuWatchdog_CONFIG_REPORT_TIME_VALUES (0)  /* 1: report time values during safety check, useful for debugging */

/* list of IDs to identify items monitored by the watchdog task */
typedef enum McuWatchdog_ReportID_e {
  McuWatchdog_REPORT_ID_TASK_APP,
#if PL_CONFIG_USE_GUI
  McuWatchdog_REPORT_ID_TASK_GUI,
#endif
#if PL_CONFIG_USE_SHELL
  McuWatchdog_REPORT_ID_TASK_SHELL,
#endif
#if PL_CONFIG_USE_LIGHTS
  McuWatchdog_REPORT_ID_TASK_LIGHTS,
#endif
#if PL_CONFIG_USE_WIFI
  McuWatchdog_REPORT_ID_TASK_WIFI,
#endif
  McuWatchdog_REPORT_ID_NOF /* sentinel, must be last! */
} McuWatchdog_ReportID_e;


#endif /* MCUWATCHDOG_CONFIG_H_ */
