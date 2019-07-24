/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSPI_H_
#define MCUSPI_H_

#include "platform.h"
#include <stdint.h>
#include <stddef.h>

typedef enum {
  McuSPI_ConfigLCD,
#if 1 || PL_CONFIG_USE_STMPE610
  McuSPI_ConfigTouch1,
  McuSPI_ConfigTouch2,
#endif
} McuSPI_Config;

void McuSPI_SwitchConfig(McuSPI_Config newConfig);

void McuSPI_WriteByte(McuSPI_Config config, uint8_t data);
void MCUSPI_WriteBytes(McuSPI_Config config, uint8_t *data, size_t nofBytes);
void McuSPI_WriteReadByte(McuSPI_Config config, uint8_t write, uint8_t *read);
void McuSPI_ReadByte(McuSPI_Config config, uint8_t *data);

void McuSPI_Deinit(void);
void McuSPI_Init(void);

#endif /* MCUSPI_H_ */
