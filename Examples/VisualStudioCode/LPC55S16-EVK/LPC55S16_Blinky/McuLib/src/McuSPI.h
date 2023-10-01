/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSPI_H_
#define MCUSPI_H_

#include "McuSPIconfig.h"
#include <stdint.h>
#include <stddef.h>

void McuSPI_SetCS_Low(void);

void McuSPI_SetCS_High(void);

int McuSPI_SendReceiveBlock(const uint8_t *txDataBuf, uint8_t *rxDataBuf, size_t dataSize);

int McuSPI_SendByte(unsigned char ch);

int McuSPI_SendReceiveByte(unsigned char ch, unsigned char *chp);

int McuSPI_ReceiveByte(unsigned char *chp);

int McuSPI_SetBaudRate(uint32_t baud);

void McuSPI_Init(void);

#endif /* MCUSPI_H_ */
