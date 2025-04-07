/*!
 * Copyright (c) 2023-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration of hardware and software.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* if FRDM-K22F or tinyK22: this is set in IncludeMcuLibConfig.h with PL_CONFIG_IS_FRDM_K22F */
/* if LPC55S69-EVK or MCU-Link Pro: this is set in IncludeMcuLibConfig.h with PL_CONFIG_IS_LPC55S69_EVK  */

#define PL_CONFIG_USE_RTT               (0)
#define PL_CONFIG_USE_SHELL             (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
#define PL_CONFIG_USE_SHELL_UART        (1 && McuLib_CONFIG_SDK_USE_FREERTOS) /* UART for shell */

/*!
 * \brief Module initialization
 */
void PL_Init(void);

#endif /* PLATFORM_H_ */
