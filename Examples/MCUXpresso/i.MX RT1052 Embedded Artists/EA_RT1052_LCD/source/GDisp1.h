/*
 * GDisp1.h
 *
 *  Created on: 19.07.2018
 *      Author: Erich Styger
 */

#ifndef GDISP1_H_
#define GDISP1_H_

#include <stdint.h>
#include <stdbool.h>

void GDisp1_PutPixel(unsigned int x, unsigned int y, uint16_t color);

void GDisp1_UpdateFull(void);

#endif /* GDISP1_H_ */
