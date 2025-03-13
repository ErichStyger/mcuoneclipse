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

#define NEO_LANE_START          NEOC_LANE_START  /* starting lane number */
#define NEO_LANE_END            NEOC_LANE_END  /* end lane number */
#define NEO_NOF_LANES           NEOC_NOF_LANES
#define NEO_NOF_LEDS_IN_LANE    NEOC_NOF_LEDS_IN_LANE /* number of LEDS in each lane */
#define NEO_NOF_PIXEL           NEOC_NOF_PIXEL /* total number of pixels */
#define NEO_NOF_BITS_PIXEL      (NEOC_NOF_COLORS*8)  /* number of bits for pixel */
#define NEO_NOF_BYTES_PIXEL     (NEOC_NOF_COLORS)

#define NEO_PIXEL_FIRST         (0) /* index of first pixel */

uint8_t NEO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

typedef uint32_t NEO_PixelIdxT;
typedef uint32_t NEO_PixelColor; /* bit coding is WRGB or 0RGB, depending on number of colors */

#define NEO_SPLIT_W(u32)    (((u32)>>24)&0xff)
#define NEO_SPLIT_R(u32)    (((u32)>>16)&0xff)
#define NEO_SPLIT_G(u32)    (((u32)>>8)&0xff)
#define NEO_SPLIT_B(u32)    ((u32)&0xff)

#define NEO_INSERT_W(u32, r8)   (u32&0x00ffffff)|((r8)<<24);
#define NEO_INSERT_R(u32, r8)   (u32&0xff00ffff)|((r8)<<16);
#define NEO_INSERT_G(u32, r8)   (u32&0xffff00ff)|((r8)<<8);
#define NEO_INSERT_B(u32, r8)   (u32&0xffffff00)|(r8);

#define NEO_SPLIT_RGB(u32)        (((u32)>>16)&0xff), (((u32)>>8)&0xff), ((u32)&0xff)
#define NEO_COMBINE_RGB(r,g,b)    (((uint32_t)(r)<<16) | ((uint32_t)(g)<<8) | (uint32_t)(b))
#if NEOC_NOF_COLORS==4
  #define NEO_SPLIT_WRGB(u32)          (((u32)>>24)&0xff), (((u32)>>16)&0xff), (((u32)>>8)&0xff), ((u32)&0xff)
  #define NEO_COMBINE_WRGB(w,r,g,b)    (((uint32_t)(w)<<24) | ((uint32_t)(r)<<16) | ((uint32_t)(g)<<8) | (uint32_t)(b))
#endif

uint8_t NEO_ClearPixel(NEO_PixelIdxT x, NEO_PixelIdxT y);

/*!
 * \brief Clears all pixels
 * \return Error code, or ERR_OK
 */
uint8_t NEO_ClearAllPixel(void);

uint8_t NEO_SetAllPixelColor(uint32_t color);
uint8_t NEO_SetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint32_t color);
uint8_t NEO_GetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint32_t *color);

/*!
 * \brief Return the pixel value as 32bit value ready to transmit for the RP2040 PIO, means it will be in grbw order
 * \param lane Lane to be used.
 * \param pos Position of pixel in lane
 * \return Pixel value in grbw order, or 0xggrrbbww. For rgb, the white part will be zero
 */
uint32_t NEO_GetPixel32bitForPIO(NEO_PixelIdxT lane, NEO_PixelIdxT pos);

uint8_t NEO_SetPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_GetPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t *redP, uint8_t *greenP, uint8_t *blueP);

uint8_t NEO_OrPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

uint8_t NEO_XorPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue);

/*!
 * \brief Transform a color into a new one based on a brightness percent value
 * \param color Color to transform (rgb or wrgb)
 * \param percent Percentage to apply, from 0 to 100
 * \return The new color value
 */
NEO_PixelColor NEO_BrightnessPercentColor(NEO_PixelColor color, uint8_t percent);

/*!
 * \brief Transform a color into a new one based on a brightness value from 0 to 0xff
 * \param color Color to transform (rgb or wrgb)
 * \param percent Percentage to apply, from 0 to 0xff
 * \return The new color value
 */
NEO_PixelColor NEO_BrightnessFactorColor(NEO_PixelColor color, uint8_t factor);

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t percent);

uint8_t NEO_TransferPixels(void);

uint8_t NEO_GammaCorrect8(uint8_t color);

uint32_t NEO_GammaCorrect24(uint32_t rgb);

uint32_t NEO_GammaCorrect32(uint32_t wrgb);

#if NEOC_NOF_COLORS==4
  uint8_t NEO_SetPixelWRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t white, uint8_t red, uint8_t green, uint8_t blue);
  uint8_t NEO_GetPixelWRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t *whiteP, uint8_t *redP, uint8_t *greenP, uint8_t *blueP);
#endif

/*!
 * \brief Driver initialization routine.
 */
void NEO_Init(void);

#endif /* NEOPIXEL_H_ */
