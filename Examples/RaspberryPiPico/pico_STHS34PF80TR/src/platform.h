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

#define PL_CONFIG_USE_RTT               (0) /* if using SEGGER RTT */
#define PL_CONFIG_USE_SHELL             (0)
#define PL_CONFIG_USE_SHELL_UART        (0 && PL_CONFIG_USE_SHELL) /* NYI, using an extra physical UART */
#define PL_CONFIG_USE_TUD_CDC           (0) /* tinyUSB CDC device with McuShellCdcDevice */
#define PL_CONFIG_USE_SHELL_CDC         (0 && PL_CONFIG_USE_TUD_CDC) /* if using CDC as shell interface */

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
