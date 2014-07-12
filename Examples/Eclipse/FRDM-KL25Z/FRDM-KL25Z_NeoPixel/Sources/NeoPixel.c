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
  NEO_PIXEL_TYPE_WS2812S, /* 6-pin version WS2812S, 'old' device */
  NEO_PIXEL_TYPE_WS2812B  /* 4-pin version WS2812B, 'new' device */
} NEO_PixelType;

/* 48 MHz, WS2812(S) */
#define TICKS_PERIOD  59  /* 1.25 us  (need: 1.25 us)*/
#define VAL0          18  /* 0 Bit: 0.396 us (need: 0.4 us low) */
#define VAL1          37  /* 1 Bit: 0.792 us (need: 0.8 us high */
#define VAL00         0   /* data line low value, e.g. for reset/latch */

#define NEO_NOF_PRE         2 /* somehow need trailing values? */
#define NEO_NOF_BITS_PIXEL  24  /* 24 bits for pixel */
#define NEO_NOF_POST        40 /* latch, low for at least 50 us (40x1.25us) */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)

static bool transferComplete = FALSE;

static uint16_t transmitBuf[NEO_NOF_PRE+(NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL)+NEO_NOF_POST];

/* sets the color of an individual pixel */
uint8_t NEO_SetPixelRGB(NEO_PixelIdxT pixelNo, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT idx;
  int i;

  if (pixelNo>=NEO_NOF_PIXEL) {
    return ERR_RANGE; /* error, out of range */
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

static uint8_t Transfer(uint32_t src) {
  while(!transferComplete) {
    /* wait until previous transfer is complete */
  }
  transferComplete = FALSE;
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, src); /* set source address */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, NEO_DMA_NOF_BYTES); /* set number of bytes to transfer */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
  return ERR_OK;
}

uint8_t NEO_TransferPixels(void) {
  return Transfer((uint32_t)&transmitBuf[0]);
}

void NEO_Init(void) {
  InitTransmitBuf();
  InitTimer();
  InitDMA();
  transferComplete = FALSE;
}
