/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_RTT           (0) /* if using RTT */
#define PL_CONFIG_USE_SEMIHOSTING   (1) /* if using semihosting */

void PL_Init(void);

#endif /* PLATFORM_H_ */
