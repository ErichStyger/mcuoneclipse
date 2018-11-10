/*
 * NeoPixel.c
 *
 *  Created on: 02.06.2014
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_NEO_PIXEL
#include "NeoPixel.h"
#include "WAIT1.h"
#include "GDisp1.h"
#include "PixelDMA.h"
#include "LEDM1.h"

#define VAL0          0  /* 0 Bit: 0.396 us (need: 0.4 us low) */
#define VAL1          1  /* 1 Bit: 0.792 us (need: 0.8 us high */

#define NEO_NOF_BITS_PIXEL  (8*NEOC_USE_NOF_COLOR)  /* 24 bits for RGB, 32 for RGBW */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)
/* transmitBuf: Each bit in the byte is a lane/channel (X coordinate). Need 24bytes for all the RGB bits, 32bytes for RGBW.
 * The Pixel(0,0) is at transmitBuf[0], Pixel (0,1) at transmitBuf[24] for RGB, at transmitBuf[32] for RGBW.
 * */
static uint8_t transmitBuf[NEO_NOF_LEDS_IN_LANE*NEO_NOF_BITS_PIXEL];

/* gamma correction table, see https://learn.adafruit.com/led-tricks-gamma-correction/the-issue */
static const uint8_t gamma8[] = {
#if 0 /* original table */
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
#else /* have lowest values still show up */
    0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
#endif
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

/* sets the color of an individual pixel */
uint8_t NEO_SetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint32_t color) {
  NEO_PixelIdxT idx;
  int i;
#if NEOC_USE_NOF_COLOR==3 /* RGB */
  uint8_t red, green, blue;

  red = (color>>16)&0xff;
  green = (color>>8)&0xff;
  blue = color&0xff;
#else
  uint8_t red, green, blue, white;

  red   = (color>>24)&0xff;
  green = (color>>16)&0xff;
  blue  = (color>>8)&0xff;
  white = color&0xff;
#endif

  if (lane>=NEO_NOF_LANES || pos>=NEO_NOF_LEDS_IN_LANE) {
    return ERR_RANGE; /* error, out of range */
  }
  idx = pos*NEO_NOF_BITS_PIXEL; /* find index in array: Y==0 is at index 0, Y==1 is at index 24, and so on */
  /* green */
  for(i=0;i<8;i++) {
    if (green&0x80) {
      transmitBuf[idx] |= (VAL1<<lane); /* set bit */
    } else {
      transmitBuf[idx] &= ~(VAL1<<lane); /* clear bit */
    }
    green <<= 1; /* next bit */
    idx++;
  }
  /* red */
  for(i=0;i<8;i++) {
    if (red&0x80) {
      transmitBuf[idx] |= (VAL1<<lane); /* set bit */
    } else {
      transmitBuf[idx] &= ~(VAL1<<lane); /* clear bit */
    }
    red <<= 1; /* next bit */
    idx++;
  }
  /* blue */
  for(i=0;i<8;i++) {
    if (blue&0x80) {
      transmitBuf[idx] |= (VAL1<<lane); /* set bit */
    } else {
      transmitBuf[idx] &= ~(VAL1<<lane); /* clear bit */
    }
    blue <<= 1; /* next bit */
    idx++;
  }
#if NEOC_USE_NOF_COLOR==4 /* RGBW */
  /* white */
  for(i=0;i<8;i++) {
    if (white&0x80) {
      transmitBuf[idx] |= (VAL1<<lane); /* set bit */
    } else {
      transmitBuf[idx] &= ~(VAL1<<lane); /* clear bit */
    }
    white <<= 1; /* next bit */
    idx++;
  }
#endif
  return ERR_OK;
}


/* sets the color of an individual pixel */
uint8_t NEO_SetPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue) {
#if NEOC_USE_NOF_COLOR==3 /* RGB */
  return NEO_SetPixelColor(lane, pos, (red<<16)|(green<<8)|blue);
#else
  return NEO_SetPixelColor(lane, pos, (red<<24)|(green<<16)|(blue<<8));
#endif
}

/* returns the color of an individual pixel */
uint8_t NEO_GetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, NEO_Color *colorP) {
  NEO_PixelIdxT idx;
  uint8_t red, green, blue;
#if NEOC_USE_NOF_COLOR==4 /* RGBW */
  uint8_t white;
#endif
  int i;

  if (lane>=NEO_NOF_LANES || pos>=NEO_NOF_LEDS_IN_LANE) {
    return ERR_RANGE; /* error, out of range */
  }
  red = green = blue = 0; /* init */
  idx = pos*NEO_NOF_BITS_PIXEL;
  /* green */
  for(i=0;i<8;i++) {
    green <<= 1;
    if (transmitBuf[idx]&(VAL1<<lane)) {
      green |= 1;
    }
    idx++; /* next bit */
  }
  /* red */
  for(i=0;i<8;i++) {
    red <<= 1;
    if (transmitBuf[idx]&(VAL1<<lane)) {
      red |= 1;
    }
    idx++; /* next bit */
  }
  /* blue */
  for(i=0;i<8;i++) {
    blue <<= 1;
    if (transmitBuf[idx]&(VAL1<<lane)) {
      blue |= 1;
    }
    idx++; /* next bit */
  }
#if NEOC_USE_NOF_COLOR==4 /* RGBW */
  /* white */
  for(i=0;i<8;i++) {
    white <<= 1;
    if (transmitBuf[idx]&(VAL1<<lane)) {
      white |= 1;
    }
    idx++; /* next bit */
  }
  *colorP = NEO_MAKE_COLOR_RGBW(red, green, blue, white);
#else
  *colorP = NEO_MAKE_COLOR_RGB(red, green, blue);
#endif
  return ERR_OK;
}

/* binary OR the color of an individual pixel */
uint8_t NEO_OrPixelColor(NEO_PixelIdxT x, NEO_PixelIdxT y, NEO_Color color) {
  NEO_Color c;

  if (x>=NEO_NOF_LANES || y>=NEO_NOF_LEDS_IN_LANE) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelColor(x, y, &c);
  color |= c;
  NEO_SetPixelColor(x, y, color);
  return ERR_OK;
}

/* binary XOR the color of an individual pixel */
uint8_t NEO_XorPixelColor(NEO_PixelIdxT x, NEO_PixelIdxT y, NEO_Color color) {
  NEO_Color c;

  if (x>=NEO_NOF_LANES || y>=NEO_NOF_LEDS_IN_LANE) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelColor(x, y, &c);
  color ^= c;
  NEO_SetPixelColor(x, y, color);
  return ERR_OK;
}

uint8_t NEO_ClearPixel(NEO_PixelIdxT lane, NEO_PixelIdxT pos) {
  return NEO_SetPixelColor(lane, pos, 0);
}

GDisp1_PixelColor NEO_BrightnessPercentColor(GDisp1_PixelColor rgbColor, uint8_t percent) {
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

/* Set the color percent to 0..100% of the actual values */
NEO_Color NEO_SetColorPercent(NEO_Color color, uint8_t percent) {
  uint8_t red, green, blue;

  red = (color>>16)&0xff;
  green = (color>>8)&0xff;
  blue = color&0xff;
  red = ((uint32_t)red*percent)/100;
  green = ((uint32_t)green*percent)/100;
  blue = ((uint32_t)blue*percent)/100;
  color = (red<<16)|(green<<8)|blue;
  return color;
}

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t percent) {
  uint8_t red, green, blue;
  uint32_t dRed, dGreen, dBlue;
#if NEOC_USE_NOF_COLOR==4
  uint8_t white;
  uint32_t dWhite;
#endif
  uint8_t res;
  NEO_Color color;

  res = NEO_GetPixelColor(lane, pos, &color);
  if (res != ERR_OK) {
    return res;
  }
  red = NEO_GET_COLOR_RED(color);
  green = NEO_GET_COLOR_GREEN(color);
  blue = NEO_GET_COLOR_BLUE(color);
  dRed = ((uint32_t)red*(100-percent))/100;
  dGreen = ((uint32_t)green*(100-percent))/100;
  dBlue = ((uint32_t)blue*(100-percent))/100;
#if NEOC_USE_NOF_COLOR==4
  white = NEO_GET_COLOR_WHITE(color);
  dWhite = ((uint32_t)white*(100-percent))/100;
  color = NEO_MAKE_COLOR_RGBW(dRed, dGreen, dBlue, dWhite);
#else
  color = NEO_MAKE_COLOR_RGB(dRed, dGreen, dBlue);
#endif
  return NEO_SetPixelColor(lane, pos, color);
}

uint8_t NEO_ClearAllPixel(void) {
  NEO_PixelIdxT lane, pos;
  uint8_t res;

  for(pos=0;pos<NEO_NOF_LEDS_IN_LANE;pos++) {
    for(lane=0;lane<NEO_NOF_LANES;lane++) {
      res = NEO_ClearPixel(lane, pos);
      if (res!=ERR_OK) {
        return res;
      }
    }
  }
  return ERR_OK;
}

uint8_t NEO_SetAllPixelColor(uint32_t rgb) {
  NEO_PixelIdxT lane, pos;
  uint8_t res;

  for(pos=0;pos<NEO_NOF_LEDS_IN_LANE;pos++) {
    for(lane=0;lane<NEO_NOF_LANES;lane++) {
      res = NEO_SetPixelColor(lane, pos, rgb);
      if (res!=ERR_OK) {
        return res;
      }
    }
  }
  return ERR_OK;
}

uint8_t NEO_TransferPixels(void) {
  return PIXDMA_Transfer((uint32_t)&transmitBuf[0], sizeof(transmitBuf));
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[32];

  CLS1_SendStatusStr((unsigned char*)"neo", (const unsigned char*)"\r\n", io->stdOut);
  UTIL1_Num32uToStr(buf, sizeof(buf), NEO_NOF_LANES);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  Lanes", buf, io->stdOut);

  UTIL1_Num32uToStr(buf, sizeof(buf), NEO_NOF_LEDS_IN_LANE);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  LED in lanes", buf, io->stdOut);

  UTIL1_Num32uToStr(buf, sizeof(buf), NEO_NOF_PIXEL);
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  Pixels", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (uint8_t*)"x: ");
  UTIL1_Num32uToStr(buf, sizeof(buf), LEDM1_GetWidth());
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" y: ");
  UTIL1_Num32uToStr(buf, sizeof(buf), LEDM1_GetHeight());
  UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"\r\n");
  CLS1_SendStatusStr((uint8_t*)"  Matrix", buf, io->stdOut);

  return ERR_OK;
}

uint8_t NEO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  uint32_t color;
  int32_t tmp, lane, pos, x, y;
  const uint8_t *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "neo help")==0) {
    CLS1_SendHelpStr((unsigned char*)"neo", (const unsigned char*)"Group of neo commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  clear all", (const unsigned char*)"Clear all pixels\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  set all <rgb>", (const unsigned char*)"Set all pixel with RGB value\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  setlane <l> <pos> <rgb>", (const unsigned char*)"Set pixel in a lane l and position pos with RGB value\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  setmatrix <x> <y> <rgb>", (const unsigned char*)"Set matrix pixel at x,y with RGB value\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "neo status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "neo clear all")==0) {
    NEO_ClearAllPixel();
    NEO_TransferPixels();
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strncmp((char*)cmd, "neo set all", sizeof("neo set all")-1)==0) {
    p = cmd+sizeof("neo set all")-1;
    res = UTIL1_xatoi(&p, &tmp); /* read color RGB value */
    if (res==ERR_OK && tmp>=0 && tmp<=0xffffff) { /* within RGB value */
      color = tmp;
      NEO_SetAllPixelColor(color);
      NEO_TransferPixels();
      *handled = TRUE;
    }
  } else if (UTIL1_strncmp((char*)cmd, "neo setlane", sizeof("neo setlane")-1)==0) {
    p = cmd+sizeof("neo setlane")-1;
    res = UTIL1_xatoi(&p, &lane); /* read lane */
    if (res==ERR_OK && lane>=0 && lane<NEO_NOF_LANES) {
      res = UTIL1_xatoi(&p, &pos); /* read pos index */
      if (res==ERR_OK && pos>=0 && pos<NEO_NOF_LEDS_IN_LANE) {
        res = UTIL1_xatoi(&p, &tmp); /* read color RGB value */
        if (res==ERR_OK && tmp>=0 && tmp<=0xffffff) {
          color = tmp;
          NEO_SetPixelColor((NEO_PixelIdxT)lane, (NEO_PixelIdxT)pos, color);
          NEO_TransferPixels();
          *handled = TRUE;
        }
      }
    }
  } else if (UTIL1_strncmp((char*)cmd, "neo setmatrix", sizeof("neo setmatrix")-1)==0) {
    p = cmd+sizeof("neo setmatrix")-1;
    res = UTIL1_xatoi(&p, &x); /* read lane */
    if (res==ERR_OK && x>=0 && x<LEDM1_GetWidth()) {
      res = UTIL1_xatoi(&p, &y); /* read pos index */
      if (res==ERR_OK && y>=0 && y<LEDM1_GetHeight()) {
        res = UTIL1_xatoi(&p, &tmp); /* read color RGB value */
        if (res==ERR_OK && tmp>=0 && tmp<=0xffffff) {
          color = tmp;
          GDisp1_PutPixel((NEO_PixelIdxT)x, (NEO_PixelIdxT)y, color);
          NEO_TransferPixels();
          *handled = TRUE;
        }
      }
    }
  }
  return res;
}

void NEO_Init(void) {
  NEO_ClearAllPixel();
}
#endif /* PL_CONFIG_HAS_NEO_PIXEL */
