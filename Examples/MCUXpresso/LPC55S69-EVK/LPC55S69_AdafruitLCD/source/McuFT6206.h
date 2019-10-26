/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUFT6206_H_
#define MCUFT6206_H_

#include "platform.h"
#include "McuFT6206config.h"
#include <stdint.h>

#if MCUFT6206_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

  uint8_t McuFT6206_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
#endif

typedef struct {
  int16_t x, y, z;
} McuFT6206_TouchPoint;

/* hardware vendor and chip IDs */
#define MCUFT62XX_VENDID            0x11
#define MCUFT6206_CHIPID            0x06
#define MCUFT6236_CHIPID            0x36
#define MCUFT6236U_CHIPID           0x64 /* mystery! */

uint8_t McuFT6206_ReadVendorID(uint8_t *id);

uint8_t McuFT6206_ReadChipID(uint8_t *id);

uint8_t McuFT6206_ReadFirmwareVersion(uint8_t *version);

uint8_t McuFT6206_ReadPointRateHz(uint8_t *rate);

uint8_t McuFT6206_ReadThreshold(uint8_t *threshold);

uint8_t McuFT6206_WriteThreshold(uint8_t threshold);

uint8_t McuFT6206_ReadNofTouches(uint8_t *nof);

uint8_t McuFT6206_ReadPoint(uint8_t n, McuFT6206_TouchPoint *point);

void McuFT6206_Deinit(void);
void McuFT6206_Init(void);

#endif /* MCUFT6206_H_ */

