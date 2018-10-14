/*
 * NeoLine.c
 *
 *  Created on: 07.07.2014
 *      Author: Erich Styger
 */

#include "NeoLine.h"
#include "NeoPixel.h"
#include "WAIT1.h"

uint8_t NEOL_PixelTrail(NEO_Color color, NEO_PixelIdxT start, NEO_PixelIdxT end, NEO_PixelIdxT nofTail, uint8_t dimmPercent, uint16_t delayMs) {
  NEO_PixelIdxT pixel;
  unsigned int i;

  for(pixel=start;pixel<=end+nofTail+1;pixel++) {
    /* move head */
    if (pixel<=end) {
      NEO_SetPixelColor(0, pixel, color);
    }
    /* clear tail pixel */
    if (pixel-start>nofTail && pixel-(nofTail+1)<=end) {
      NEO_ClearPixel(0, pixel-(nofTail+1));
    }
    /* dim remaining tail pixel */
    for(i=0;i<nofTail;i++) {
      if (pixel-start>i && pixel-(i+1)<=end) {
        NEO_DimmPercentPixel(0, pixel-(i+1), dimmPercent);
      }
    }
    NEO_TransferPixels();
    WAIT1_WaitOSms(delayMs);
  }
  return ERR_OK;
}
