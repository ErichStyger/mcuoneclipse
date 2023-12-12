/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_UNITY_H_
#define MCU_UNITY_H_

#include <stdint.h>

void McuUnity_putc(int c);
void McuUnity_flush(void);
void McuUnity_start(void);
void McuUnity_complete(void);

uint32_t McuUnity_GetArgument(void);

#endif /* MCU_UNITY_H_ */
