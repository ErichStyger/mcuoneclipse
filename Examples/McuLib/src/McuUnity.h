/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_UNITY_H_
#define MCU_UNITY_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void McuUnity_putc(int c);
void McuUnity_flush(void);
void McuUnity_start(void);
void McuUnity_complete(void);

uint32_t McuUnity_GetArgument(void);

int McuUnity_RTT_GetArgs(const char *buffer, size_t bufSize);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCU_UNITY_H_ */
