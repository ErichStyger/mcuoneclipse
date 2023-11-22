/*!
 * Copyright (c) 2019, 2022 Erich Styger
 * All rights reserved.
 * \file
 * \brief Configuration header file for McuSHT40 (Sensirion SHT40 sensor).
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSHT40_CONFIG_H_
#define MCUSHT40_CONFIG_H_

/*
  SHT40-AD1B base RH&T accur., 0x44 I2C addr.
  SHT40-BD1B base RH&T accur., 0x45 I2C addr.
  SHT41-AD1B Intermed. RH&T accur., 0x44 I2C addr.
  SHT45-AD1B ±1.5 %RH, ±0.1°C accur., 0x44 I2C addr.
 */
#ifndef McuSHT40_CONFIG_I2C_ADDR
  #define McuSHT40_CONFIG_I2C_ADDR  (0x44) /* I2C address of the sensor */
#endif


#ifndef MCUSHT40_CONFIG_PARSE_COMMAND_ENABLED
  #define MCUSHT40_CONFIG_PARSE_COMMAND_ENABLED  (1)
#endif

#endif /* MCUSHT40_CONFIG_H_ */
