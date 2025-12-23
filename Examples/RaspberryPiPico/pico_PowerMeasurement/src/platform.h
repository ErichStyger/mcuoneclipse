/*
 * Copyright (c) 2023-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PL_CONFIG_USE_LEDS          (1)
#define PL_CONFIG_USE_BLINKY_TASK   (1)
#define PL_CONFIG_USE_SHELL         (1)
#define PL_CONFIG_USE_SHT31         (0) /* Sensiriorn SHT31 temperature/humidity sensor */
#define PL_CONFIG_USE_INA260        (0) /* INA260 I2C voltage and current sensor */
#define PL_CONFIG_USE_ADS1115       (1) /* TI ADS1115 4channel I2C ADC converter */
#define PL_CONFIG_USE_GP8403        (1) /* GP8403 DAC I2C converter */
#define PL_CONFIG_USE_SPI           (1) /* enables SPI bus usage */
#define PL_CONFIG_USE_INA229        (1 && PL_CONFIG_USE_SPI) /* TI INA229 SPI power meter */
#define PL_CONFIG_USE_SENSOR_TASK   (1 && PL_CONFIG_USE_INA260)
#define PL_CONFIG_USE_RELAIS        (1) /* Panasonic TQ2-L2-5V 2coil latching Relay */

/*!
 * \brief de-initializes the platform
 */
void PL_Deinit(void);

/*!
 * \brief initializes the platform
 */
void PL_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* PLATFORM_H_ */
