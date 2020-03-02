/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOSTEPPERRING_H_
#define NEOSTEPPERRING_H_

#include <stdint.h>

typedef void *NEOSR_Handle_t;

typedef struct NEOSR_Config_t {
  int dummy;
} NEOSR_Config_t;

void NEOSR_GetDefaultConfig(NEOSR_Config_t *config);

NEOSR_Handle_t NEOSR_InitDevice(NEOSR_Config_t *config);

int32_t NEOSR_GetPos(NEOSR_Handle_t device);

void NEOSR_SetPos(NEOSR_Handle_t device, int32_t pos);
int32_t NEOSR_GetPos(NEOSR_Handle_t device);

void NEOSR_SingleStep(NEOSR_Handle_t device, int step);

void NEOSR_Init(void);

#endif /* NEOSTEPPERRING_H_ */
