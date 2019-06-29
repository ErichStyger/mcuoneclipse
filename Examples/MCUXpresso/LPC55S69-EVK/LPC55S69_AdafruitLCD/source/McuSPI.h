/*
 * spi.h
 *
 *  Created on: 29.06.2019
 *      Author: Erich Styger
 */

#ifndef MCUSPI_H_
#define MCUSPI_H_

#include <stdint.h>

void McuSPI_WriteByte(uint8_t data);
void McuSPI_ReadByte(uint8_t *data);

void McuSPI_Init(void);

#endif /* MCUSPI_H_ */
