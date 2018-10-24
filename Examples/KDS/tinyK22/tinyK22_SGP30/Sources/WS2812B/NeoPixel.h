/*
 * NeoPixel.h
 *
 *  Created on: 06.06.2014
 *      Author: Erich Styger
 */

#ifndef NEOPIXEL_H_
#define NEOPIXEL_H_

#include "NeoConfig.h"
#include "CLS1.h"
#include "GDisp1.h"

#define NEO_NOF_LANES           NEOC_NOF_LANES  /* number of LED lanes */
#define NEO_NOF_LEDS_IN_LANE    NEOC_NOF_LEDS_IN_LANE /* number of LEDS in each lane */
#define NEO_NOF_PIXEL           NEOC_NOF_PIXEL /* total number of pixels */

typedef uint32_t NEO_Color;
#if NEOC_USE_NOF_COLOR==4
  #define NEO_MAKE_COLOR_RGB(r,g,b)     (((r)<<24)|((g)<<16)|((b)<<8))
  #define NEO_MAKE_COLOR_RGBW(r,g,b,w)  (((r)<<24)|((g)<<16)|((b)<<8)|(w))
#else /* 3 */
  #define NEO_MAKE_COLOR_RGB(r,g,b)     (((r)<<16)|((g)<<8)|(b))
  #define NEO_MAKE_COLOR_RGBW(r,g,b,w)  (((r)<<16)|((g)<<8)|(b))
#endif

#if NEOC_USE_NOF_COLOR==4
  #define NEO_GET_COLOR_RED(color)     (((color)>>24)&0xff)
  #define NEO_GET_COLOR_GREEN(color)   (((color)>>16)&0xff)
  #define NEO_GET_COLOR_BLUE(color)    (((color)>>8)&0xff)
  #define NEO_GET_COLOR_WHITE(color)   ((color)&0xff)
#else
  #define NEO_GET_COLOR_RED(color)     (((color)>>16)&0xff)
  #define NEO_GET_COLOR_GREEN(color)   (((color)>>8)&0xff)
  #define NEO_GET_COLOR_BLUE(color)    ((color)&0xff)
#endif

#define NEO_PIXEL_FIRST         (0) /* index of first pixel */
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
uint8_t NEO_SetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, NEO_Color color);
uint8_t NEO_GetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, NEO_Color *color);

uint8_t NEO_OrPixelColor(NEO_PixelIdxT x, NEO_PixelIdxT y, NEO_Color color);
uint8_t NEO_XorPixelColor(NEO_PixelIdxT x, NEO_PixelIdxT y, NEO_Color color);

/* Set the color percent to 0..100% of the actual values */
NEO_Color NEO_SetColorPercent(NEO_Color color, uint8_t percent);

GDisp1_PixelColor NEO_BrightnessPercentColor(GDisp1_PixelColor rgbColor, uint8_t percent);

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t percent);

uint8_t NEO_TransferPixels(void);

uint8_t NEO_GammaCorrect8(uint8_t color);

uint32_t NEO_GammaCorrect24(uint32_t rgb);

/*!
 * \brief Driver initialization routine.
 */
void NEO_Init(void);

#endif /* NEOPIXEL_H_ */
