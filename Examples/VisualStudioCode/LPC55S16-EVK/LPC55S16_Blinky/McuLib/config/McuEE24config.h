/**
 * \file
 * \brief Configuration header file for 24AA_EEPROM
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings the External I2C EEPROM module.
 */

#ifndef __McuEE24_CONFIG_H
#define __McuEE24_CONFIG_H

/* actual device */
#ifndef McuEE24_CONFIG_DEVICE_ID
  #define McuEE24_CONFIG_DEVICE_ID      8
    /*!< Supported Device IDs: 8 (24AA08, 24LC08), 16 (24AA16, 24LC16), 32 (24AA32, 24LC32), 256 (24AA256, 24LC256, 24FC256), 512 (24AA512, 24LC512, 24FC256) or 1025 (24AA1025, 24LC1025, 24FC1025) */
#endif

#ifndef McuEE24_CONFIG_HAS_WP_PIN
  #define McuEE24_CONFIG_HAS_WP_PIN      (1)
    /*!<< 1: Write Protect Pin available. 0: no Write Protect pin */
#endif

#ifndef McuEE24_CONFIG_DEVICE_I2C_ADDRESS_BITS
  #define McuEE24_CONFIG_DEVICE_I2C_ADDRESS_BITS   (0)
    /* Address bits for I2C address, usually formed by the A0, A1 and A3 pins. Admissible range: 0..7 */
#endif

#ifndef McuEE24_CONFIG_BLOCK_BUF_SIZE
  #define McuEE24_CONFIG_BLOCK_BUF_SIZE   (32)
    /*!< buffer used for block read/write. Max is 128. Keep it small to reduce stack consumption. */
#endif

#ifndef McuEE24_CONFIG_DO_ACKNOWLEDGE_POLLING
  #define McuEE24_CONFIG_DO_ACKNOWLEDGE_POLLING    (1)
    /*!< 1: Perform acknowledge polling in the driver. 0: no acknowledge polling */
#endif

#ifndef McuEE24_CONFIG_PAGE_WRITE_TIME_MS
  #define McuEE24_CONFIG_PAGE_WRITE_TIME_MS        (5)
    /*!< Page Write Time as per data sheet, used with McuEE24_CONFIG_DO_ACKNOWLEDGE_POLLING */
#endif

#ifndef McuEE24_CONFIG_ACK_POLLING_TIME_US
  #define McuEE24_CONFIG_ACK_POLLING_TIME_US       (100)
    /*!< Acknowledge polling time in the I2C driver, used with McuEE24_CONFIG_DO_ACKNOWLEDGE_POLLING  */
#endif

#ifndef McuEE24_CONFIG_USE_TIMEOUT
  #define McuEE24_CONFIG_USE_TIMEOUT               (1)
    /*!< 1: use timeout, 0: do not use timeout */
#endif

#ifndef McuEE24_CONFIG_TIMEOUT_BYTE_MS
  #define McuEE24_CONFIG_TIMEOUT_BYTE_MS           (10)
    /*!< number of milli seconds for timeout using byte write */
#endif

#ifndef McuEE24_CONFIG_TIMEOUT_BLOCK_MS
  #define McuEE24_CONFIG_TIMEOUT_BLOCK_MS          (60)
    /*!< number of milliseconds for timeout using for block write */
#endif

#ifndef McuEE24_CONFIG_USE_SHELL
  #define McuEE24_CONFIG_USE_SHELL               (1)
    /*!< 1: use shell, 0: do not use shell */
#endif

#ifndef McuEE24_CONFIG_USE_UTILITY
  #define McuEE24_CONFIG_USE_UTILITY               (1)
    /*!< 1: use utility module, 0: do not use utility module */
#endif

#endif /* __McuEE24_CONFIG_H */
