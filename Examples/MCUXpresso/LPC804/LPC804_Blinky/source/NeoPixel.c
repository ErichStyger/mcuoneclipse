/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "NeoPixel.h"
#include "McuUtility.h"
#include "PixelTransfer.h"

static const uint8_t gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

uint8_t NEO_GammaCorrect8(uint8_t color) {
  return gamma8[color];
}

uint32_t NEO_GammaCorrect24(uint32_t rgb) {
  uint8_t r, g, b;

  r = NEO_GammaCorrect8((rgb>>16)&0xff);
  g = NEO_GammaCorrect8((rgb>>8)&0xff);
  b = NEO_GammaCorrect8(rgb&0xff);
  rgb = (r<<16)|(g<<8)|b;
  return rgb;
}

/* the ones below do not depend on hardware */

NEO_PixelColor NEO_BrightnessPercentColor(NEO_PixelColor rgbColor, uint8_t percent) {
  uint8_t red, green, blue;

  red = (rgbColor>>16)&0xff;
  green = (rgbColor>>8)&0xff;
  blue = rgbColor&0xff;
  red = ((uint32_t)red*percent)/100;
  green = ((uint32_t)green*percent)/100;
  blue = ((uint32_t)blue*percent)/100;
  rgbColor = (red<<16)|(green<<8)|blue;
  return rgbColor;
}

NEO_PixelColor NEO_BrightnessFactorColor(NEO_PixelColor rgbColor, uint8_t factor) {
  uint8_t red, green, blue;

  red = (rgbColor>>16)&0xff;
  green = (rgbColor>>8)&0xff;
  blue = rgbColor&0xff;
  red = ((uint32_t)red*factor)/255;
  green = ((uint32_t)green*factor)/255;
  blue = ((uint32_t)blue*factor)/255;
  rgbColor = (red<<16)|(green<<8)|blue;
  return rgbColor;
}

#define VAL0          0  /* 0 Bit: 0.396 us (need: 0.4 us low) */
#define VAL1          1  /* 1 Bit: 0.792 us (need: 0.8 us high */

#define NEO_NOF_BITS_PIXEL  (NEOC_NOF_COLORS*8)  /* number of bits for pixel */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)
/* transmitBuf: Each bit in the byte is a lane/channel (X coordinate). Need 24bytes for all the RGB bits. The Pixel(0,0) is at transmitBuf[0], Pixel (0,1) at transmitBuf[24]. */
static uint8_t transmitBuf[NEO_NOF_PIXEL*NEOC_NOF_COLORS];

uint8_t NEO_GetPixelColor(NEO_PixelIdxT pos, uint32_t *rgb) {
  uint8_t res, r,g,b;

  res = NEO_GetPixelRGB(pos, &r, &g, &b);
  *rgb = (r<<16)|(g<<8)|b;
  return res;
}

uint8_t NEO_SetPixelColor(NEO_PixelIdxT pos, uint32_t rgb) {
  return NEO_SetPixelRGB(pos, (rgb>>16)&0xff, (rgb>>8)&0xff, rgb&0xff);
}

/* sets the color of an individual pixel */
uint8_t NEO_SetPixelRGB(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT idx;

  if (pos>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  idx = pos*NEOC_NOF_COLORS; /* find index in array */
  transmitBuf[idx] = green;
  transmitBuf[idx+1] = red;
  transmitBuf[idx+2] = blue;
  return ERR_OK;
}

#if NEOC_NOF_COLORS==4
uint8_t NEO_SetPixelRGBW(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  NEO_PixelIdxT idx;

  if (pos>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  idx = pos*NEOC_NOF_COLORS; /* find index in array */
  transmitBuf[idx] = green;
  transmitBuf[idx+1] = red;
  transmitBuf[idx+2] = blue;
  transmitBuf[idx+3] = white;
  return ERR_OK;
}
#endif /* NEOC_NOF_COLORS */

/* returns the color of an individual pixel */
uint8_t NEO_GetPixelRGB(NEO_PixelIdxT pos, uint8_t *redP, uint8_t *greenP, uint8_t *blueP) {
  NEO_PixelIdxT idx;

  if (pos>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  idx = pos*NEOC_NOF_COLORS; /* find index in array */
  *greenP = transmitBuf[idx];
  *redP = transmitBuf[idx+1];
  *blueP = transmitBuf[idx+2];
  return ERR_OK;
}

#if NEOC_NOF_COLORS==4
uint8_t NEO_GetPixelRGBW(NEO_PixelIdxT pos, uint8_t *redP, uint8_t *greenP, uint8_t *blueP, uint8_t *whiteP) {
  NEO_PixelIdxT idx;

  if (pos>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  idx = pos*NEOC_NOF_COLORS; /* find index in array */
  *greenP = transmitBuf[idx];
  *redP = transmitBuf[idx+1];
  *blueP = transmitBuf[idx+2];
  *whiteP = transmitBuf[idx+3];
  return ERR_OK;
}
#endif /* NEOC_NOF_COLORS */

/* binary OR the color of an individual pixel */
uint8_t NEO_OrPixelRGB(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t r, g, b;

  if (pos>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  if (red==0 && green==0 && blue==0) { /* only makes sense if they are not zero */
    return ERR_OK;
  }
  NEO_GetPixelRGB(pos, &r, &g, &b);
  r |= red;
  g |= green;
  b |= blue;
  NEO_SetPixelRGB(pos, r, g, b);
  return ERR_OK;
}

#if NEOC_NOF_COLORS==4
uint8_t NEO_OrPixelRGBW(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  uint8_t r, g, b, w;

  if (pos>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  if (red==0 && green==0 && blue==0 && white==0) { /* only makes sense if they are not zero */
    return ERR_OK;
  }
  NEO_GetPixelRGBW(pos, &r, &g, &b, &w);
  r |= red;
  g |= green;
  b |= blue;
  w |= white;
  NEO_SetPixelRGBW(pos, r, g, b, w);
  return ERR_OK;
}
#endif /* NEOC_NOF_COLORS */

/* binary XOR the color of an individual pixel */
uint8_t NEO_XorPixelRGB(NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t r, g, b;

  if (pos>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelRGB(pos, &r, &g, &b);
  r ^= red;
  b ^= blue;
  g ^= blue;
  NEO_SetPixelRGB(pos, red, green, blue);
  return ERR_OK;
}

uint8_t NEO_ClearPixel(NEO_PixelIdxT pos) {
#if NEOC_NOF_COLORS==4
  return NEO_SetPixelRGBW(pos, 0, 0, 0, 0);
#else
  return NEO_SetPixelRGB(pos, 0, 0, 0);
#endif
}

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT pos, uint8_t percent) {
  uint8_t red, green, blue;
  uint32_t dRed, dGreen, dBlue;
  uint8_t res;

  res = NEO_GetPixelRGB(pos, &red, &green, &blue);
  if (res != ERR_OK) {
    return res;
  }
  dRed = ((uint32_t)red*(100-percent))/100;
  dGreen = ((uint32_t)green*(100-percent))/100;
  dBlue = ((uint32_t)blue*(100-percent))/100;
  return NEO_SetPixelRGB(pos, (uint8_t)dRed, (uint8_t)dGreen, (uint8_t)dBlue);
}

uint8_t NEO_ClearAllPixel(void) {
  memset(transmitBuf, 0, sizeof(transmitBuf));
  return ERR_OK;
}

uint8_t NEO_SetAllPixelColor(uint32_t rgb) {
  NEO_PixelIdxT pos;
  uint8_t res;

  for(pos=0;pos<NEO_NOF_PIXEL;pos++) {
    res = NEO_SetPixelColor(pos, rgb);
    if (res!=ERR_OK) {
      return res;
    }
  }
  return ERR_OK;
}

uint8_t NEO_TransferPixels(void) {
  return PIXELTRANS_Send(&transmitBuf[0], sizeof(transmitBuf));
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[32];

  McuShell_SendStatusStr((unsigned char*)"neo", (const unsigned char*)"Status of NeoPixels\r\n", io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), NEO_NOF_PIXEL);
  McuUtility_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  Pixels", buf, io->stdOut);

  return ERR_OK;
}

uint8_t NEO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t pos;
  const uint8_t *p;
  uint32_t rgb;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "neo help")==0) {
    McuShell_SendHelpStr((unsigned char*)"neo", (const unsigned char*)"Group of neo commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  clear all", (const unsigned char*)"Clear all pixels\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set all <rgb>", (const unsigned char*)"Set all pixel with RGB value\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  set <pos> <rgb>", (const unsigned char*)"Set pixel in a lane and position with RGB value\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "neo status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "neo clear all")==0) {
    NEO_ClearAllPixel();
    NEO_TransferPixels();
    *handled = TRUE;
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "neo set all", sizeof("neo set all")-1)==0) {
    p = cmd+sizeof("neo set all")-1;
    res = McuUtility_ScanRGB32(&p, &rgb); /* read color RGB value */
    if (res==ERR_OK) { /* within RGB value */
      NEO_SetAllPixelColor(rgb);
      NEO_TransferPixels();
      *handled = TRUE;
    }
  } else if (McuUtility_strncmp((char*)cmd, "neo set ", sizeof("neo set ")-1)==0) {
    p = cmd+sizeof("neo set ")-1;
    res = McuUtility_xatoi(&p, &pos); /* read pos index */
    if (res==ERR_OK && pos>=0 && pos<NEO_NOF_PIXEL) {
      res = McuUtility_ScanRGB32(&p, &rgb); /* read color RGB value */
      if (res==ERR_OK) {
        NEO_SetPixelColor((NEO_PixelIdxT)pos, rgb);
        NEO_TransferPixels();
        *handled = TRUE;
      }
    }
  }
  return res;
}

void NEO_Init(void) {
  NEO_ClearAllPixel();
}
