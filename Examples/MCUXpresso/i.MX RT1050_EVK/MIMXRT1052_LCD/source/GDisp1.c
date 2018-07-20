/*
 * GDisp1.c
 *
 *  Created on: 19.07.2018
 *      Author: Erich Styger
 */

#include "GDisp1.h"
#include <stdint.h>
#include "fsl_elcdif.h"
#include "FreeRTOS.h"
#include "task.h"

uint32_t msCntr;

static uint32_t frameBufferIndex = 0;

void GDisp1_PutPixel(unsigned int x, unsigned int y, uint16_t color) {
	int tmp;
  /* left eye */
	/* swap to rotate */
	tmp = y;
	y = x;
	x = tmp;
//	x += 50; /* x is is from top to ethernet connecter */
	s_frameBuffer[frameBufferIndex][x][y] = color;
#if 0
    /* right eye */
	y += 200; /* y is from left to right (ethernet to power plug */
	s_frameBuffer[frameBufferIndex][x][y] = color;
#endif
}

void GDisp1_UpdateFull(void) {
    ELCDIF_SetNextBufferAddr(APP_ELCDIF, (uint32_t)s_frameBuffer[frameBufferIndex]);
    s_frameDone = false;
    /* Wait for previous frame complete. */
    while (!s_frameDone) {
    	vTaskDelay(pdMS_TO_TICKS(1)); /* wait */
    }
    frameBufferIndex ^= 1U;
}
