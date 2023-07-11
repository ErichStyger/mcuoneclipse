/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CUBEANIM_H_
#define CUBEANIM_H_

#include <stdbool.h>
#include "McuShell.h"
#include "McuRTOS.h"

uint8_t CubeAnim_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void CubeAnim_PlayRandom(void);

void CubeAnim_PlaySpecific(uint8_t nr);

bool CubeAnim_IsOn(void);

void CubeAnim_Init(void);

#endif /* CUBEANIM_H_ */
