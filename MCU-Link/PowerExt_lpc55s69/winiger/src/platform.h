/*!
 * Copyright (c) 2023-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration of hardware and software.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* if LPC55S69-EVK or MCU-Link Pro: this is set in IncludeMcuLibConfig.h with PL_CONFIG_IS_LPC55S69_EVK  */

/* different settings for ARES: Set only one app mode */
#define PL_CONFIG_USE_BLINKY             (1) /* blinking LED task */
#define PL_CONFIG_USE_SPI                (1) /* SPI module for ADC */

#define PL_CONFIG_USE_RTT               (1)
#define PL_CONFIG_USE_SHELL             (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
#define PL_CONFIG_USE_SHELL_UART        (1 && McuLib_CONFIG_SDK_USE_FREERTOS) /* UART for shell */

/*!
 * \brief Module initialization
 */
void PL_Init(void);

#endif /* PLATFORM_H_ */
