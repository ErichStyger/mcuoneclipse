/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef McuADS1115_CONFIG_H_
#define McuADS1115_CONFIG_H_

#ifndef McuADS1115_CONFIG_PARSE_COMMAND_ENABLED
  #define McuADS1115_CONFIG_PARSE_COMMAND_ENABLED    (1)
    /*!< If shell parser is enabled (1) or not (0). */
#endif

#ifndef McuADS1115_CONFIG_I2C_ADDRESS
  #define McuADS1115_CONFIG_I2C_ADDRESS              (0x48)
    /*! I2C address of the sensor, default 0x48. With pin ADDR pin Low, it is 0x48, with ADDR high, it is 0x49, with ADDR connected to SDA, it ix 0x4A, with ADDR connected to SCL, it is 0x4B */
#endif

#endif /* McuADS1115_CONFIG_H_ */