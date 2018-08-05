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
	/* swap to rotate */
	tmp = y;
	y = x;
	x = tmp;
	s_frameBuffer[frameBufferIndex][x][y] = color;
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
