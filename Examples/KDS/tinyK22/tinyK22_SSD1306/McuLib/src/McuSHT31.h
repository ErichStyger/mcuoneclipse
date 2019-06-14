/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Driver for the SHT31 Temperature/Humidity sensor
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_MCUSHT31_H_
#define SOURCES_MCUSHT31_H_

#include "McuSHT31config.h"
#include <stdint.h>
#include <stdbool.h>

#if MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"
  uint8_t McuSHT31_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

uint8_t McuSHT31_Reset(void);
uint8_t McuSHT31_Heater(bool on);
uint8_t SHT31_ReadStatus(uint16_t *status);
uint8_t McuSHT31_ReadTempHum(float *temperature, float *humidity);

void McuSHT31_Deinit(void);
void McuSHT31_Init(void);

#endif /* SOURCES_MCUSHT31_H_ */
