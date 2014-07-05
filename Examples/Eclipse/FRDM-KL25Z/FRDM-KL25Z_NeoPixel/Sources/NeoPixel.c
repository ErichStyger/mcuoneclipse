/*
 * NeoPixel.c
 *
 *  Created on: 02.06.2014
 *      Author: tastyger
 */

#include "NeoPixel.h"
#include "PE_Types.h"
#include "DMA1.h"
#include "DMACH1.h"
#include "DMA_PDD.h"
#include "TPM_PDD.h"

typedef enum {
  NEO_PIXEL_TYPE_WS2812,  /* 6-pin version WS2812 */
  NEO_PIXEL_TYPE_WS2812B  /* 4-pin version WS2812B */
} NEO_PixelType;

/* 48 MHz, WS2812 */
#define TICKS_PERIOD  59  /* 1.25 us  (need: 1.25 us)*/
#define VAL0  18          /* 0.396 us (need: 0.4 us low) */
#define VAL1  37          /* 0.792 us (need: 0.8 us high */
#define VAL00 0

#define NEO_NOF_PIXEL       (1+16) /* number of pixels */
#define NEO_PIXEL_FIRST      0
#define NEO_PIXEL_LAST      (NEO_NOF_PIXEL-1)
#define NEO_NOF_PRE         2 /* somehow need trailing values? */
#define NEO_NOF_BITS_PIXEL  24  /* 24 bits for pixel */
#define NEO_NOF_POST        40 /* latch, low for at least 50 us (40x1.25us) */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)

static bool transferComplete = FALSE;
typedef uint32_t NEO_PixelIdxT;
typedef enum {
  NEO_COLOR_RED,
  NEO_COLOR_GREEN,
  NEO_COLOR_BLUE
} NEO_ColorE;

static uint16_t transmitBuf[NEO_NOF_PRE+(NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL)+NEO_NOF_POST];

/* sets the color of an individual pixel */
void NEO_SetPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT idx;
  int i;

  if (pixelNo>=NEO_NOF_BITS_PIXEL) {
    return; /* error, out of range */
  }
  idx = NEO_NOF_PRE+(pixelNo*NEO_NOF_BITS_PIXEL);
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
}

/* returns the color of an individual pixel */
void NEO_GetPixelRGB(NEO_PixelIdxT pixelNo, uint8_t *redP, uint8_t *greenP, uint8_t *blueP) {
  NEO_PixelIdxT idx;
  uint8_t red, green, blue;
  int i;

  if (pixelNo>=NEO_NOF_BITS_PIXEL) {
    return; /* error, out of range */
  }
  red = green = blue = 0;
  idx = NEO_NOF_PRE+(pixelNo*NEO_NOF_BITS_PIXEL);
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
}


void NEO_ClearPixel(NEO_PixelIdxT pixelNo) {
  NEO_SetPixelRGB(pixelNo, 0, 0, 0);
}

void NEO_DimmPercentPixel(NEO_PixelIdxT pixelNo, NEO_ColorE color, uint8_t percent) {
  uint8_t red, green, blue;
  uint32_t val;

  NEO_GetPixelRGB(pixelNo, &red, &green, &blue);
  if (color==NEO_COLOR_RED) {
    val = (red*percent)/100;
    NEO_SetPixelRGB(pixelNo, (uint8_t)val, 0, 0);
  } else if (color==NEO_COLOR_GREEN) {
    val = (green*percent)/100;
    NEO_SetPixelRGB(pixelNo, 0, (uint8_t)val, 0);
  } else if (color==NEO_COLOR_BLUE) {
    val = (blue*percent)/100;
    NEO_SetPixelRGB(pixelNo, 0, 0, (uint8_t)val);
  }
}

void NEO_ClearAllPixel(void) {
  NEO_PixelIdxT i;

  for(i=0;i<NEO_NOF_PIXEL;i++) {
    NEO_ClearPixel(i);
  }
}

static void InitTransmitBuf(void) {
  uint32_t i;

  for(i=0;i<NEO_NOF_PRE;i++) {
    transmitBuf[i] = 0; /* pre sequence */
  }
  NEO_ClearAllPixel();
  for(i=NEO_NOF_PRE+(NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL);i<sizeof(transmitBuf)/sizeof(transmitBuf[0]);i++) {
    transmitBuf[i] = 0; /* post sequence */
  }
}

void MyDMAComplete(void) {
  transferComplete = TRUE;
}

static void InitTimer(void) {
  TPM_PDD_WriteModuloReg(TPM0_BASE_PTR, TICKS_PERIOD); /* set period */
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 1, 0); /* PWM low, zero duty */
  TPM_PDD_EnableChannelDma(TPM0_DEVICE, 1); /* enable DMA for channel */
}

static void InitDMA(void) {
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&transmitBuf[0]); /* set source address */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* source address will be incremented by transfer size */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_16_BIT); /* Transfer size from source is 16bit */

  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&TPM0_C1V); /* set destination address */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* no auto-increment for destination address */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_16_BIT); /* Transfer to destination size is 16bit */

  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, NEO_DMA_NOF_BYTES); /* set number of bytes to transfer */
  DMA_PDD_EnableTransferCompleteInterrupt(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* request interrupt at the end of the DMA transfer to set new byte count */
  (void)DMA_PDD_GetRequestAutoDisableEnabled(DMA_BASE_PTR, DMA_PDD_CHANNEL_0); /* disable DMA request at the end of the sequence */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
}

static void Transfer(uint32_t src) {
  while(!transferComplete) {
    /* wait until previous transfer is complete */
  }
  transferComplete = FALSE;
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, src); /* set source address */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, NEO_DMA_NOF_BYTES); /* set number of bytes to transfer */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
}

static void PixelTrail(uint16_t delayMs, NEO_ColorE color, NEO_PixelIdxT start, NEO_PixelIdxT end) {
  NEO_PixelIdxT pixel;

  for(pixel=start;pixel<=end+3;pixel++) {
    if (pixel-start>0 && pixel-1<=end) {
      NEO_DimmPercentPixel(pixel-1, color, 50);
    }
    if (pixel-start>1 && pixel-2<=end) {
      NEO_DimmPercentPixel(pixel-2, color, 25);
    }
    if (pixel-start>2 && pixel-3<=end) {
      NEO_ClearPixel(pixel-3);
    }
    if (pixel<=end) {
      if (color==NEO_COLOR_RED) {
        NEO_SetPixelRGB(pixel, 0xff, 0, 0);
      } else if (color==NEO_COLOR_GREEN) {
        NEO_SetPixelRGB(pixel, 0, 0xff, 0);
      } else if (color==NEO_COLOR_BLUE) {
        NEO_SetPixelRGB(pixel, 0, 0, 0xff);
      }
    }
    Transfer((uint32_t)&transmitBuf[0]);
    WAIT1_Waitms(delayMs);
  }
}

void NP_Start(void) {
#if 0
  uint8_t red, green, blue;
  uint32_t pixel;
#endif

  InitTransmitBuf();
  InitTimer();
  InitDMA();
  transferComplete = FALSE;
  Cpu_EnableInt(); /* enable interrupts */

  NEO_ClearAllPixel();
  Transfer((uint32_t)&transmitBuf[0]);

  for (;;) {
    PixelTrail(100, NEO_COLOR_RED, NEO_PIXEL_FIRST, NEO_PIXEL_LAST);
    PixelTrail(200, NEO_COLOR_GREEN, NEO_PIXEL_FIRST+2, 10);
    PixelTrail(100, NEO_COLOR_BLUE, NEO_PIXEL_FIRST, NEO_PIXEL_LAST);
  }
  NEO_ClearAllPixel();
  Transfer((uint32_t)&transmitBuf[0]);
#if 0
  red = green = blue = 0;
  for(;;) {
    for(pixel=1;pixel<NEO_NOF_PIXEL;pixel++) {
      NEO_SetPixelRGB(pixel, red, green, blue);
      Transfer((uint32_t)&transmitBuf[0]);
      WAIT1_Waitms(100);
      red += 2u;
      green += 2u;
      blue += 2u;
      NEO_ClearPixel(pixel); /* clear pixel again */
    }
  }
#endif
}
