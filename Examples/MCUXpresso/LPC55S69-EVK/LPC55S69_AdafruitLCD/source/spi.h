/*
 * spi.h
 *
 *  Created on: 29.06.2019
 *      Author: Erich Styger
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void SPI_WriteByte(uint8_t data, uint8_t *rx);

void SPI_Init(void);

#endif /* SPI_H_ */
