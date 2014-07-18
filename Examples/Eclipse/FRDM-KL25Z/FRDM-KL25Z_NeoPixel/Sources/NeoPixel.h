/*
 * NeoPixel.h
 *
 *  Created on: 06.06.2014
 *      Author: tastyger
 */

#ifndef NEOPIXEL_H_
#define NEOPIXEL_H_

#include "NeoConfig.h"

#define NEO_NOF_PIXEL       NEOC_NOF_PIXEL /* number of pixels */
#define NEO_PIXEL_FIRST     (0) /* index of first pixel */
#define NEO_PIXEL_LAST      (NEO_NOF_PIXEL-1)

typedef uint32_t NEO_PixelIdxT;

uint8_t NEO_ClearPixel(NEO_PixelIdxT pixelNo);

/*!
 * \brief Clears all pixels
 * \return Error code, or ERR_OK
 */
uint8_t NEO_ClearAllPixel(void);

uint8_t NEO_SetPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_GetPixelRGB(NEO_PixelIdxT pixelNo, uint8_t *redP, uint8_t *greenP, uint8_t *blueP);

uint8_t NEO_OrPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_XorPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT pixelNo, uint8_t percent);

uint8_t NEO_TransferPixels(void);

/*!
 * \brief Driver initialization routine.
 */
void NEO_Init(void);

#endif /* NEOPIXEL_H_ */
