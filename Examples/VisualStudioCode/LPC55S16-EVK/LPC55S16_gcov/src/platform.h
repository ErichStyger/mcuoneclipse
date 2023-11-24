/*!
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration of hardware and software.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL_UART        (1)
#define PL_CONFIG_USE_RTT               (1)
#define PL_CONFIG_USE_GCOV              (1 && McuRdimon_CONFIG_IS_ENABLED) /* if using gcov, we need file I/O semihosting */

/*!
 * \brief Module initialization
 */
void PL_Init(void);

#endif /* PLATFORM_H_ */
