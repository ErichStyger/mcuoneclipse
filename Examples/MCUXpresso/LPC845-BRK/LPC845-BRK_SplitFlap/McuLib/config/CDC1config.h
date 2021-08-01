/**
 * \file
 * \brief Configuration header file for USB CDC
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the USB CDC module.
 */

#ifndef __CDC1_CONFIG_H
#define __CDC1_CONFIG_H


#ifndef CDC1_CONFIG_USE_TIMEOUT
  #define CDC1_CONFIG_USE_TIMEOUT           1
    /*!< 1: Use timeout; 0: do not use timeout */
#endif

#ifndef CDC1_CONFIG_APP_TASK_TIMEOUT_MS
  #define CDC1_CONFIG_APP_TASK_TIMEOUT_MS   20
    /*!< App Task timeout in milliseconds, 0 to disable timeout */
#endif

#endif /* __CDC1_CONFIG_H */
