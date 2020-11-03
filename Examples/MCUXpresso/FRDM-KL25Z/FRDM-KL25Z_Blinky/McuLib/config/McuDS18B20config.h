/**
 * \file
 * \brief Configuration header file for DS18B20
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the DS128B20 1-Wire temperature sensor.
 */

#ifndef __McuDS18B20_CONFIG_H
#define __McuDS18B20_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define McuDS18B20_CONFIG_NUMBER_OF_SENSORS      (1)
  /*!< Number of devices (1-n) */

#define McuDS18B20_CONFIG_MULTIPLE_BUS_DEVICES   (0)
  /*!< 1: there are multiple devices on the bus, need to use ROM code to address them; 0: single device on the 1-Wire bus */

#ifndef McuDS18B20_CONFIG_READ_AUTO
  #define McuDS18B20_CONFIG_READ_AUTO            (1)
  /*!< 1: automatic mode, temperature is read from sensor during StartConversion(). 0: Call ReadTemperature() after starting a conversion */
#endif

#if !defined(McuDS18B20_CONFIG_PARSE_COMMAND_ENABLED)
  #define McuDS18B20_CONFIG_PARSE_COMMAND_ENABLED (1)
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __McuDS18B20_CONFIG_H */
