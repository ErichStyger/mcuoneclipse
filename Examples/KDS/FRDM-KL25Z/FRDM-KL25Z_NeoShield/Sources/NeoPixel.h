/*
 * NeoPixel.h
 *
 *  Created on: 06.06.2014
 *      Author: tastyger
 */

#ifndef NEOPIXEL_H_
#define NEOPIXEL_H_

#include "NeoConfig.h"
#include "CLS1.h"

#define NEO_NOF_LANES           NEOC_NOF_LANES  /* number of LED lanes */
#define NEO_NOF_LEDS_IN_LANE    NEOC_NOF_LEDS_IN_LANE /* number of LEDS in each lane */
#define NEO_NOF_PIXEL           NEOC_NOF_PIXEL /* total number of pixels */

#define NEO_PIXEL_FIRST         (0) /* index of first pixel */
//#define NEO_PIXEL_LAST       (NEO_NOF_PIXEL-1)
#if (NEOC_NOF_LANES>8)
  #error "can only handle up to 8 bits"
#endif

uint8_t NEO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

typedef uint32_t NEO_PixelIdxT;

uint8_t NEO_ClearPixel(NEO_PixelIdxT x, NEO_PixelIdxT y);

/*!
 * \brief Clears all pixels
 * \return Error code, or ERR_OK
 */
uint8_t NEO_ClearAllPixel(void);

uint8_t NEO_SetAllPixelColor(uint32_t rgb);
uint8_t NEO_SetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint32_t rgb);
uint8_t NEO_GetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint32_t *rgb);

uint8_t NEO_SetPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_GetPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t *redP, uint8_t *greenP, uint8_t *blueP);

uint8_t NEO_OrPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_XorPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t percent);

uint8_t NEO_TransferPixels(void);

/*!
 * \brief Driver initialization routine.
 */
void NEO_Init(void);

#endif /* NEOPIXEL_H_ */
