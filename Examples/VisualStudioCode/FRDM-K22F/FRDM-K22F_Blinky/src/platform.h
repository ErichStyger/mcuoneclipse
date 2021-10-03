/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_IS_TINY_K22  (1) /* if board is the tinyK22 instead of the FRDM-K22F */

/* platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
