/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * 2-Channel I2C DAC module with a voltage of 0-10V
 */

#ifndef McuGP8403_CONFIG_H_
#define McuGP8403_CONFIG_H_

#ifndef McuGP8403_CONFIG_PARSE_COMMAND_ENABLED
  #define McuGP8403_CONFIG_PARSE_COMMAND_ENABLED    (1)
    /*!< If shell parser is enabled (1) or not (0). */
#endif

#ifndef McuGP8403_CONFIG_I2C_ADDRESS
  #define McuGP8403_CONFIG_I2C_ADDRESS              (0x58)
    /*! I2C address of the sensor, defined by A0,A1,A2, default 0x58. */
#endif

#endif /* McuGP8403_CONFIG_H_ */