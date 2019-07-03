/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef MCUSPI_H_
#define MCUSPI_H_

#include <stdint.h>

void McuSPI_WriteByte(uint8_t data);
void McuSPI_ReadByte(uint8_t *data);

void McuSPI_Init(void);

#endif /* MCUSPI_H_ */
