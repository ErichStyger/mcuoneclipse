/**
 * \file
 * \brief Configuration header file for DS18B20
 *
 * This header file is used to configure settings of the DS128B20 1-Wire temperature sensor.
 */

#ifndef __DS1_CONFIG_H
#define __DS1_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define DS1_CONFIG_NUMBER_OF_SENSORS             (2)
  /*!< Number of devices (1-n) */

#define DS1_CONFIG_MULTIPLE_BUS_DEVICES          (1)
  /*!< 1: there are multiple devices on the bus, need to use ROM code to address them; 0: single device on the 1-Wire bus */

#ifndef DS1_CONFIG_READ_AUTO
  #define DS1_CONFIG_READ_AUTO                   (1)
  /*!< 1: automatic mode, temperature is read from sensor during StartConversion(). 0: Call ReadTemperature() after starting a conversion */
#endif

#if !defined(DS1_CONFIG_PARSE_COMMAND_ENABLED)
  #define DS1_CONFIG_PARSE_COMMAND_ENABLED       (1)
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __DS1_CONFIG_H */
