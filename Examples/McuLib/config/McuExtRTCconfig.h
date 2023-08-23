/**
 * \file
 * \brief Configuration header file for external I2C RTC devices
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings the External I2C RTC module.
 */

#ifndef __McuExtRTC_CONFIG_H
#define __McuExtRTC_CONFIG_H

#ifndef McuExtRTC_CONFIG_DEVICE
  #define McuExtRTC_CONFIG_DEVICE 3232 /* DS1307, DS3231, DS3232 or DS1342 */
#endif

/* I2C address of the device on the bus: */
#ifndef McuExtRTC_CONFIG_DEVICE_ADDRESS
  #if McuExtRTC_CONFIG_DEVICE==3231
    #define McuExtRTC_CONFIG_DEVICE_ADDRESS 0x68  /* I2C DS3232 device address */
  #elif McuExtRTC_CONFIG_DEVICE==3232
    #define McuExtRTC_CONFIG_DEVICE_ADDRESS 0x68  /* I2C DS3232 device address */
  #elif McuExtRTC_CONFIG_DEVICE==1307
    #define McuExtRTC_CONFIG_DEVICE_ADDRESS 0x68  /* I2C DS1307 device address */
  #elif McuExtRTC_CONFIG_DEVICE==1342
    #define McuExtRTC_CONFIG_DEVICE_ADDRESS 0x68  /* I2C DS1342 device address */
  #else
    #error "Unknown device"
  #endif
#endif

#endif /* __McuExtRTC_CONFIG_H */
