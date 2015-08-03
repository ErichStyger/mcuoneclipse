/*
 * NeoPixel.c
 *
 *  Created on: 02.06.2014
 *      Author: tastyger
 */

#include "NeoPixel.h"
#include "DMAPixel.h"

#define VAL0          0  /* 0 Bit: 0.396 us (need: 0.4 us low) */
#define VAL1          1  /* 1 Bit: 0.792 us (need: 0.8 us high */

#define NEO_NOF_BITS_PIXEL  24  /* 24 bits for pixel */

static uint8_t transmitBuf[NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL];

uint8_t NEO_GetPixelColor(NEO_PixelIdxT pixelNo, uint32_t *rgb) {
  uint8_t res, r,g,b;

  res = NEO_GetPixelRGB(pixelNo, &r, &g, &b);
  *rgb = (r<<16)|(g<<8)|b;
  return res;
}

uint8_t NEO_SetPixelColor(NEO_PixelIdxT pixelNo, uint32_t rgb) {
  return NEO_SetPixelRGB(pixelNo, (rgb>>16)&0xff, (rgb>>8)&0xff, rgb&0xff);
}

/* sets the color of an individual pixel */
uint8_t NEO_SetPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT idx;
  int i;

  if (pixelNo>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  idx = pixelNo*NEO_NOF_BITS_PIXEL;
  /* green */
  for(i=0;i<8;i++) {
    if (green&0x80) {
      transmitBuf[idx] = VAL1;
    } else {
      transmitBuf[idx] = VAL0;
    }
    green <<= 1; /* next bit */
    idx++;
  }
  /* red */
  for(i=0;i<8;i++) {
    if (red&0x80) {
      transmitBuf[idx] = VAL1;
    } else {
      transmitBuf[idx] = VAL0;
    }
    red <<= 1; /* next bit */
    idx++;
  }
  /* blue */
  for(i=0;i<8;i++) {
    if (blue&0x80) {
      transmitBuf[idx] = VAL1;
    } else {
      transmitBuf[idx] = VAL0;
    }
    blue <<= 1; /* next bit */
    idx++;
  }
  return ERR_OK;
}

/* returns the color of an individual pixel */
uint8_t NEO_GetPixelRGB(NEO_PixelIdxT pixelNo, uint8_t *redP, uint8_t *greenP, uint8_t *blueP) {
  NEO_PixelIdxT idx;
  uint8_t red, green, blue;
  int i;

  if (pixelNo>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  red = green = blue = 0;
  idx = pixelNo*NEO_NOF_BITS_PIXEL;
  /* green */
  for(i=0;i<8;i++) {
    green <<= 1;
    if (transmitBuf[idx]==VAL1) {
      green |= 1;
    }
    idx++; /* next bit */
  }
  /* red */
  for(i=0;i<8;i++) {
    red <<= 1;
    if (transmitBuf[idx]==VAL1) {
      red |= 1;
    }
    idx++; /* next bit */
  }
  /* blue */
  for(i=0;i<8;i++) {
    blue <<= 1;
    if (transmitBuf[idx]==VAL1) {
      blue |= 1;
    }
    idx++; /* next bit */
  }
  *redP = red;
  *greenP = green;
  *blueP = blue;
  return ERR_OK;
}

/* binary OR the color of an individual pixel */
uint8_t NEO_OrPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t r, g, b;

  if (pixelNo>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelRGB(pixelNo, &r, &g, &b);
  r |= red;
  b |= blue;
  g |= blue;
  NEO_SetPixelRGB(pixelNo, red, green, blue);
  return ERR_OK;
}

/* binary XOR the color of an individual pixel */
uint8_t NEO_XorPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t r, g, b;

  if (pixelNo>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelRGB(pixelNo, &r, &g, &b);
  r ^= red;
  b ^= blue;
  g ^= blue;
  NEO_SetPixelRGB(pixelNo, red, green, blue);
  return ERR_OK;
}

uint8_t NEO_ClearPixel(NEO_PixelIdxT pixelNo) {
  return NEO_SetPixelRGB(pixelNo, 0, 0, 0);
}

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT pixelNo, uint8_t percent) {
  uint8_t red, green, blue;
  uint32_t dRed, dGreen, dBlue;
  uint8_t res;

  res = NEO_GetPixelRGB(pixelNo, &red, &green, &blue);
  if (res != ERR_OK) {
    return res;
  }
  dRed = ((uint32_t)red*(100-percent))/100;
  dGreen = ((uint32_t)green*(100-percent))/100;
  dBlue = ((uint32_t)blue*(100-percent))/100;
  return NEO_SetPixelRGB(pixelNo, (uint8_t)dRed, (uint8_t)dGreen, (uint8_t)dBlue);
}

uint8_t NEO_ClearAllPixel(void) {
  NEO_PixelIdxT i;
  uint8_t res;

  for(i=0;i<NEO_NOF_PIXEL;i++) {
    res = NEO_ClearPixel(i);
    if (res!=ERR_OK) {
      return res;
    }
  }
  return ERR_OK;
}

static void InitTransmitBuf(void) {
  NEO_ClearAllPixel();
}

uint8_t NEO_TransferPixels(void) {
  DMA_Transfer(transmitBuf, sizeof(transmitBuf));
  return ERR_OK;
}

void NEO_Init(void) {
  InitTransmitBuf();
  DMA_Init();
}
