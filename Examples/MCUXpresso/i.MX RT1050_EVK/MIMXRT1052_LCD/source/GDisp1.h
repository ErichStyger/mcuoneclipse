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

#define APP_IMG_HEIGHT 272
#define APP_IMG_WIDTH 480
#define APP_ELCDIF LCDIF

extern uint32_t s_frameBuffer[2][APP_IMG_HEIGHT][APP_IMG_WIDTH];
extern volatile bool s_frameDone;

void GDisp1_PutPixel(unsigned int x, unsigned int y, uint16_t color);

void GDisp1_UpdateFull(void);

#endif /* GDISP1_H_ */
