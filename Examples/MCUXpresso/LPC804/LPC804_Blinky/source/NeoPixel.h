/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOPIXEL_H_
#define NEOPIXEL_H_

#include <stdint.h>
#include "NeoConfig.h"
#include "McuShell.h"

#define NEO_NOF_PIXEL           NEOC_NOF_PIXEL /* total number of pixels */

#define NEO_PIXEL_FIRST         (0) /* index of first pixel */

uint8_t NEO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

typedef uint32_t NEO_PixelIdxT;
typedef uint32_t NEO_PixelColor;

#define NEO_SPLIT_RGB(u32)   (((u32)>>16)&0xff), (((u32)>>8)&0xff), ((u32)&0xff)
#define NEO_COMBINE_RGB(r,g,b)   ( ((uint32_t)(r)<<16) | ((uint32_t)(g)<<8) | (uint32_t)(b) )

uint8_t NEO_ClearPixel(NEO_PixelIdxT pos);

/*!
 * \brief Clears all pixels
 * \return Error code, or ERR_OK
 */
uint8_t NEO_ClearAllPixel(void);

uint8_t NEO_SetAllPixelColor(uint32_t rgb);
uint8_t NEO_SetPixelColor(NEO_PixelIdxT pos, uint32_t rgb);
uint8_t NEO_GetPixelColor(NEO_PixelIdxT pos, uint32_t *rgb);

uint8_t NEO_SetPixelRGB(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_GetPixelRGB(NEO_PixelIdxT pos, uint8_t *redP, uint8_t *greenP, uint8_t *blueP);

uint8_t NEO_OrPixelRGB(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_XorPixelRGB(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

NEO_PixelColor NEO_BrightnessPercentColor(NEO_PixelColor rgbColor, uint8_t percent);
NEO_PixelColor NEO_BrightnessFactorColor(NEO_PixelColor rgbColor, uint8_t factor);

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT pos, uint8_t percent);

uint8_t NEO_TransferPixels(void);

uint8_t NEO_GammaCorrect8(uint8_t color);

uint32_t NEO_GammaCorrect24(uint32_t rgb);

#if NEOC_NOF_COLORS==4
uint8_t NEO_SetPixelRGBW(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
uint8_t NEO_GetPixelRGBW(NEO_PixelIdxT pos, uint8_t *redP, uint8_t *greenP, uint8_t *blueP, uint8_t *whiteP);
#endif

/*!
 * \brief Driver initialization routine.
 */
void NEO_Init(void);

#endif /* NEOPIXEL_H_ */
