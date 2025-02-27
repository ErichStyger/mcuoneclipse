/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL_UART        (0)
#define PL_CONFIG_USE_RTT               (1)
#define PL_CONFIG_USE_SEMIHOSTING       (1 && McuSemihost_CONFIG_IS_ENABLED)

/*!
 * \brief Module initialization
 */
void PL_Init(void);

#endif /* PLATFORM_H_ */
