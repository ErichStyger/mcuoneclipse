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

#define WDT_WATCHDOG_TIMEOUT_MS   (1000) /* number of ms for watchdog timer */

#define WDT_DISABLED_FOR_DEBUG (0)  /* set to 1 for easier debugging */
#define WDT_REPORT_TIME_VALUES (0)  /* 1: report time values during safety check */


/* list of IDs to identify items monitored by the watchdog task */
typedef enum {
  WDT_REPORT_ID_TASK_APP,
#if PL_CONFIG_USE_GUI
  WDT_REPORT_ID_TASK_GUI,
#endif
#if PL_CONFIG_USE_SHELL
  WDT_REPORT_ID_TASK_SHELL,
#endif
#if PL_CONFIG_USE_LIGHTS
  WDT_REPORT_ID_TASK_LIGHTS,
#endif
#if PL_CONFIG_USE_GUI_ENERGY_DASHBOARD
  WDT_REPORT_ID_TASK_EMONITOR,
#endif
#if PL_CONFIG_USE_ROAD
  WDT_REPORT_ID_TASK_ROAD,
#endif
  WDT_REPORT_ID_NOF /* sentinel, must be last! */
} WDT_ReportID_e;


#endif /* MCUWATCHDOG_CONFIG_H_ */
