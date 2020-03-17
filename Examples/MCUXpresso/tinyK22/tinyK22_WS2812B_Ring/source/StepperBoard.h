/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef STEPPERBOARD_H_
#define STEPPERBOARD_H_

#include <stdint.h>
#include <stdbool.h>

typedef void *STEPBOARD_Handle_t;

typedef struct STEPBOARD_Config_t {
  uint8_t addr;      /* RS-485 address */
  bool enabled;      /* if board is enabled or not */
} STEPBOARD_Config_t;

void STEPBOARD_GetDefaultConfig(STEPBOARD_Config_t *config);

uint8_t STEPBOARD_GetAddress(STEPBOARD_Handle_t device);
bool STEPBOARD_IsEnabled(STEPBOARD_Handle_t device);

STEPBOARD_Handle_t STEPBOARD_DeinitDevice(STEPBOARD_Handle_t device);
STEPBOARD_Handle_t STEPBOARD_InitDevice(STEPBOARD_Config_t *config);

void STEPBOARD_Deinit(void);
void STEPBOARD_Init(void);

#endif /* STEPPERBOARD_H_ */
