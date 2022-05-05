
/**
 * \file
 * \brief Configuration header file for FSL_USB_CDC_Device
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the USB CDC Device I/O module.
 */

#ifndef __CDC1_CONFIG_H
#define __CDC1_CONFIG_H

#ifndef CDC1_CONFIG_USE_TIMEOUT
  #define CDC1_CONFIG_USE_TIMEOUT           1
    /*!< 1: Use timeout; 0: do not use timeout */
#endif

#ifndef CDC1_CONFIG_APP_TASK_TIMEOUT_MS
  #define CDC1_CONFIG_APP_TASK_TIMEOUT_MS   50
    /*!< App Task timeout in milliseconds, 0 to disable timeout */
#endif

#ifndef CDC1_CONFIG_DATA_BUF_SIZE
  #define CDC1_CONFIG_DATA_BUF_SIZE           (64)
    /*!< Value used for CDC1_DATA_BUF_SIZE, must be a multiple of endpoint size. The greater the value, the better the performance */
#endif


#endif /* __CDC1_CONFIG_H */
