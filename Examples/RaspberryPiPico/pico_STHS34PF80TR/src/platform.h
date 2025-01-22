/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "IncludeMcuLibConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PL_CONFIG_USE_RTT               (1) /* if using SEGGER RTT */
#define PL_CONFIG_USE_SHELL             (1)
#define PL_CONFIG_USE_SHELL_UART        (0 && PL_CONFIG_USE_SHELL) /* NYI, using an extra physical UART */
#define PL_CONFIG_USE_TUD_CDC           (1) /* tinyUSB CDC device with McuShellCdcDevice */
#define PL_CONFIG_USE_SHELL_CDC         (1 && PL_CONFIG_USE_TUD_CDC) /* if using CDC as shell interface */
#define PL_CONFIG_USE_I2C               (1)
#define PL_CONFIG_USE_PCF85063A         (1 && PL_CONFIG_USE_I2C) /* using external RTC */
#define PL_CONFIG_USE_EXT_RTC           (PL_CONFIG_USE_PCF85063A && PL_CONFIG_USE_I2C)
#define PL_CONFIG_USE_POWER             (1)
#define PL_CONFIG_USE_SPI               (1) /* if using SPI bus */
#define PL_HAS_RADIO                    (1 && PL_CONFIG_USE_SPI && McuRNET_CONFIG_IS_ENABLED && McuNRF24L01_CONFIG_IS_ENABLED) /* RNET with nRF24L01+ */

/* not used */
#define PL_CONFIG_USE_PICO_W (0)
#define PL_CONFIG_USE_GUI    (0)
#define PL_CONFIG_USE_ADC    (0)
#define PL_CONFIG_USE_SENSOR (0) /* \todo */

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
