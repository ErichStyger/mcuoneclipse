/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NVMC_H_
#define NVMC_H_

#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

#define NVMC_VERSION_1_0  (10)

typedef struct {
  uint32_t version; /* NVMC_VERSION_1_0, must be 32bit type to have struct 4 byte aligned! */
  uint8_t addrRS485; /* device address on the RS-485 bus */
  int16_t zeroOffsets[4][2]; /* two offsets for each motor, offset from the magnet sensor to the zero position */
  /* fill up to 64 bytes, needed for flash programming */
  uint8_t filler[64-4-1-(4*2*2)-4];
} NVMC_Data_t;

/*!
 * \brief Returns a pointer to the data or NULL if the data is not present (erased)
 */
const NVMC_Data_t *NVMC_GetDataPtr(void);

uint8_t NVMC_WriteConfig(NVMC_Data_t *data);

int16_t NVMC_GetStepperZeroOffset(uint8_t clock, uint8_t motor);

uint8_t NVMC_GetRS485Addr(void);

bool NVMC_IsErased(void);

uint8_t NVMC_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void NVMC_Deinit(void);
void NVMC_Init(void);

#endif /* NVMC_H_ */
