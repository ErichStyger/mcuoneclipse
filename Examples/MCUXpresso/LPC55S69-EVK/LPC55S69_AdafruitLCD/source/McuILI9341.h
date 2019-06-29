/*
 * McuILI9341.h
 *
 *  Created on: 29.06.2019
 *      Author: Erich Styger
 */

#ifndef MCUILI9341_C_
#define MCUILI9341_C_

#include <stdint.h>
#include <stdbool.h>

uint8_t McuILI9341_GetDisplayIdentification(uint8_t *manufacurer, uint8_t *driverVersion, uint8_t *driverID);

uint8_t McuILI9341_InvertDisplay(bool invert);

uint8_t McuILI9341_DisplayOn(bool on);

uint8_t McuILI9341_InitLCD(void);

void McuILI9341_Init(void);

#endif /* MCUILI9341_C_ */
