/*!
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration header file for the McuLog module.
 */

#ifndef MCULOGCONFIG_H_
#define MCULOGCONFIG_H_

#include "McuLib.h"

#ifndef McuLog_CONFIG_IS_ENABLED
  #define McuLog_CONFIG_IS_ENABLED            (1)
    /*!< 1: Logging is enabled; 0: Logging is disabled, not adding anything to the application code */
#endif

#ifndef McuLog_CONFIG_DEFAULT_LEVEL
  #define McuLog_CONFIG_DEFAULT_LEVEL            (McuLog_TRACE)
    /*!< one of McuLog_Levels_e */
#endif

#ifndef McuLog_CONFIG_USE_MUTEX
  #define McuLog_CONFIG_USE_MUTEX             (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use a RTOS mutex for the logging module; 0: do not use a mutex */
#endif

#ifndef McuLog_CONFIG_USE_COLOR
  #define McuLog_CONFIG_USE_COLOR             (1)
    /*!< 1: use use ANSI color for terminal, 0: do not use color */
#endif

#ifndef McuLog_CONFIG_USE_PRINTF_STYLE
  #define McuLog_CONFIG_USE_PRINTF_STYLE      (1)
    /*!< 1: use printf open argument list for printing */
#endif

#ifndef McuLog_CONFIG_USE_FILE
  #define McuLog_CONFIG_USE_FILE              (0)
    /*!< 1: use use file for logging, 0: do not use file */
#endif

#ifndef McuLog_CONFIG_NOF_CONSOLE_LOGGER
  #define McuLog_CONFIG_NOF_CONSOLE_LOGGER    (1)
    /*!< Number of console loggers */
#endif

#ifndef McuLog_CONFIG_LOG_TIMESTAMP_DATE
  #define McuLog_CONFIG_LOG_TIMESTAMP_DATE    (1)
    /*!< 1: add date to time stamp, 0: do not date for time stamp */
#endif

#ifndef McuLog_CONFIG_LOG_TIMESTAMP_TIME
  #define McuLog_CONFIG_LOG_TIMESTAMP_TIME    (1)
    /*!< 1: add time to time stamp, 0: do not time for time stamp */
#endif

#ifndef McuLog_CONFIG_LOG_STRIP_FILENAME_PATH
  #define McuLog_CONFIG_LOG_STRIP_FILENAME_PATH    (1)
    /*!< 1: strip path from file name, 0: keep file name untouched */
#endif

#ifndef McuLog_CONFIG_USE_RTT_CONSOLE
  #define McuLog_CONFIG_USE_RTT_CONSOLE        (0)
    /*!< 1: use SEGGER RTT console output, 0: do not use SEGGER RTT */
#endif

#ifndef McuLog_CONFIG_USE_RTT_DATA_LOGGER
  #define McuLog_CONFIG_USE_RTT_DATA_LOGGER        (0)
    /*!< 1: use SEGGER RTT Logger (Channel 1), 0: do not use SEGGER RTT Logger */
#endif

#ifndef McuLog_CONFIG_RTT_DATA_LOGGER_BUFFER_SIZE
  #define McuLog_CONFIG_RTT_DATA_LOGGER_BUFFER_SIZE        (256)
    /*!< Buffer size in bytes for the RTT data logger channel */
#endif

#ifndef McuLog_CONFIG_RTT_DATA_LOGGER_CHANNEL_MODE
  #define McuLog_CONFIG_RTT_DATA_LOGGER_CHANNEL_MODE      (SEGGER_RTT_MODE_NO_BLOCK_SKIP)
    /*!< RTT channel mode to be used */
#endif

#ifndef McuLog_CONFIG_PARSE_COMMAND_ENABLED
  #define McuLog_CONFIG_PARSE_COMMAND_ENABLED  (1 && McuLog_CONFIG_IS_ENABLED)
  /*! < 1: shell command line parser enabled; 0: not enabled */
#endif

#endif /* MCULOGCONFIG_H_ */
