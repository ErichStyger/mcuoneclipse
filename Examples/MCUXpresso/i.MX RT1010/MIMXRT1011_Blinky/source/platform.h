/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL       (0)
#define PL_CONFIG_USE_RTT         (0)
#define PL_CONFIG_USE_SHELL_UART  (0 && PL_CONFIG_USE_SHELL)

void PL_InitFromTask(void);
void PL_Init(void);

#endif /* PLATFORM_H_ */
