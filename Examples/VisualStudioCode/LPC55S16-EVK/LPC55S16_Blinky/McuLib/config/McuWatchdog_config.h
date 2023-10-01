/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUWATCHDOG_CONFIG_H_
#define MCUWATCHDOG_CONFIG_H_

#ifndef McuWatchdog_CONFIG_USE_WATCHDOG
  #define McuWatchdog_CONFIG_USE_WATCHDOG (0)
    /*!< if using the McuWatchdog module */
#endif

#ifndef McuWatchdog_CONFIG_HEALT_CHECK_TIME_SEC
  #define McuWatchdog_CONFIG_HEALT_CHECK_TIME_SEC (5)  /*!< interval for checking health */
#endif

#ifndef McuWatchdog_CONFIG_TIMEOUT_MS
  #define McuWatchdog_CONFIG_TIMEOUT_MS           (1000) /*!< number of ms for hardware watchdog timer */
#endif

#ifndef McuWatchdog_CONFIG_DISABLED_FOR_DEBUG
  #define McuWatchdog_CONFIG_DISABLED_FOR_DEBUG   (0)  /* set to 1 for easier debugging, set to 0 for production code! */
#endif
#ifndef McuWatchdog_CONFIG_REPORT_TIME_VALUES
  #define McuWatchdog_CONFIG_REPORT_TIME_VALUES   (0)  /* 1: report time values during safety check, useful for debugging */
#endif

#ifndef McuWatchdog_CONFIG_REPORT_ID_INCLUDE_FILE
  #define McuWatchdog_CONFIG_REPORT_ID_INCLUDE_FILE  "McuWatchdog_IDs.inc"
    /*!< file with watchdog IDs (enumeration values) with McuWatchdog_REPORT_IDS macro */
#endif

#ifndef McuWatchdog_CONFIG_REPORT_ID_INCLUDE_HEADER_FILE
  #define McuWatchdog_CONFIG_REPORT_ID_INCLUDE_HEADER_FILE  "platform.h"
    /*!< header file which is used for the watchdog IDs */
#endif

#endif /* MCUWATCHDOG_CONFIG_H_ */
