/*!
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration header file for the LC709203 battery gauge I2C sensor.
 */

#ifndef SOURCES_MCULC709203FCONFIG_H_
#define SOURCES_MCULC709203FCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MCULC709203F_CONFIG_USE_THERMISTOR
  #define MCULC709203F_CONFIG_USE_THERMISTOR  (0)
    /*!< 1: using Thermistor in battery. 0: using I2C mode */
#endif

#ifndef MCULC_CONFIG_BLOCK_ON_I2C_ERROR
  #define MCULC_CONFIG_BLOCK_ON_I2C_ERROR   (1)
    /*!< if it should block on error and wait for the watchdog */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_MCULC709203FCONFIG_H_ */
