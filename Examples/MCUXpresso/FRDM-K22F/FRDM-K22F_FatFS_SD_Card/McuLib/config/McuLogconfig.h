/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCULOGCONFIG_H_
#define MCULOGCONFIG_H_

#include "McuLib.h"

#ifndef MCULOG_CONFIG_IS_ENABLED
  #define MCULOG_CONFIG_IS_ENABLED            (1)
    /*!< 1: Logging is enabled; 0: Logging is disabled, not adding anything to the application code */
#endif

#ifndef MCULOG_CONFIG_USE_MUTEX
  #define MCULOG_CONFIG_USE_MUTEX             (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use a RTOS mutex for the logging module; 0: do not use a mutex */
#endif

#ifndef MCULOG_CONFIG_USE_COLOR
  #define MCULOG_CONFIG_USE_COLOR             (1)
    /*!< 1: use use ANSI color for terminal, 0: do not use color */
#endif

#ifndef MCULOG_CONFIG_USE_FILE
  #define MCULOG_CONFIG_USE_FILE              (0)
    /*!< 1: use use file for logging, 0: do not use file */
#endif

#ifndef MCULOG_CONFIG_LOG_TIMESTAMP_DATE
  #define MCULOG_CONFIG_LOG_TIMESTAMP_DATE    (1)
    /*!< 1: add date to timestamp, 0: do not date for timestamp */
#endif

#ifndef MCULOG_CONFIG_USE_RTT_LOGGER
  #define MCULOG_CONFIG_USE_RTT_LOGGER        (1)
    /*!< 1: use use SEGGER RTT Logger (Channel 1), 0: do not use SEGGER RTT Logger */
#endif

#ifndef MCULOG_CONFIG_PARSE_COMMAND_ENABLED
  #define MCULOG_CONFIG_PARSE_COMMAND_ENABLED  (1 && MCULOG_CONFIG_IS_ENABLED)
  /*! < 1: shell command line parser enabled; 0: not enabled */
#endif

#endif /* MCULOGCONFIG_H_ */
