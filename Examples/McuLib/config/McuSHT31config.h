/*!
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 * \file
 * \brief Configuration header file for McuSHT31 sensor from Sensirion.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSHT31_CONFIG_H_
#define MCUSHT31_CONFIG_H_

#ifndef MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED
  #define MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED  (1)
#endif

#ifndef McuSHT31_CONFIG_I2C_ADDR
  #define McuSHT31_CONFIG_I2C_ADDR  (0x44) /* default I2C address with ADDR pin pulled LOW (default on Adafruit board) */
  //#define McuSHT31_I2C_ADDR  (0x45) /* I2C address with ADDR pin pulled HIGH: pull ADR pin to VIN */
#endif

#endif /* MCUSHT31_CONFIG_H_ */
