/**
 * \file
 * \brief Configuration header file for FXOS8700CQ accelerometer
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the FXOS8700CQ module.
 */

#ifndef __McuFXOS8700_CONFIG_H
#define __McuFXOS8700_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(McuFXOS8700_CONFIG_I2C_DEVICE_ADDRESS)
  #define McuFXOS8700_CONFIG_I2C_DEVICE_ADDRESS  (0x1E)
    /*!< I2C 7bit device address */
    /*       SDA0  SDA1
       0x1E  low   low
       0x1D  high  low
       0x1C  low   high
       0x1F  high  high
    */
#endif

#if !defined(McuFXOS8700_CONFIG_TEMP_OFFSET)
  #define McuFXOS8700_CONFIG_TEMP_OFFSET  (24)
    /*!< die temperature offset for real temperature calculation */
#endif

#if !defined(McuFXOS8700_CONFIG_PARSE_COMMAND_ENABLED)
  #define McuFXOS8700_CONFIG_PARSE_COMMAND_ENABLED  1
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __McuFXOS8700_CONFIG_H */
