/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUA3967_H_
#define MCUA3967_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuGPIO.h"

typedef void *McuA3967_Handle_t;

typedef struct {
  McuGPIO_HwPin_t rst; /* reset pin */
} McuA3967_Config_t;

void McuA3967_GetDefaultConfig(McuA3967_Config_t *config);

McuA3967_Handle_t McuA3967_InitHandle(McuA3967_Config_t *config);

McuA3967_Handle_t McuA3967_DeinitHandle(McuA3967_Handle_t stepper);

void McuA3967_Deinit(void);

void McuA3967_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUA3967_H_ */
