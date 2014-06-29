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

/* 48 MHz, WS2812 */
#define TICKS_PERIOD  59  /* 1.25 us  (need: 1.25 us)*/
#define VAL0  18          /* 0.396 us (need: 0.4 us low) */
#define VAL1  37          /* 0.792 us (need: 0.8 us high */
#define VAL00 0

#define NEO_NOF_PIXEL       13 /* number of pixels */
#define NEO_NOF_PRE         2 /* somehow need trailing values? */
#define NEO_NOF_BITS_PIXEL  24  /* 24 bits for pixel */
#define NEO_NOF_POST        40 /* latch, low for at least 50 us (40x1.25us) */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)

static bool transferComplete = FALSE;

static uint16_t transmitBuf[NEO_NOF_PRE+(NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL)+NEO_NOF_POST];

static void SetPixelColor(int pixelIndex, uint8_t r, uint8_t g, uint8_t b) {
  int idx;
  int i;

  if (pixelIndex>=NEO_NOF_BITS_PIXEL) {
    return; /* error, out of range */
  }
  idx = NEO_NOF_PRE+(pixelIndex*NEO_NOF_BITS_PIXEL);
  /* green */
  for(i=0;i<8;i++) {
    if (g&0x80) {
      transmitBuf[idx] = VAL1;
    } else {
      transmitBuf[idx] = VAL0;
    }
    g <<= 1; /* next bit */
    idx++;
  }
  /* red */
  for(i=0;i<8;i++) {
    if (r&0x80) {
      transmitBuf[idx] = VAL1;
    } else {
      transmitBuf[idx] = VAL0;
    }
    r <<= 1; /* next bit */
    idx++;
  }
  /* blue */
  for(i=0;i<8;i++) {
    if (b&0x80) {
      transmitBuf[idx] = VAL1;
    } else {
      transmitBuf[idx] = VAL0;
    }
    b <<= 1; /* next bit */
    idx++;
  }
}

static void InitTransmitBuf(void) {
  uint32_t i;

  for(i=0;i<NEO_NOF_PRE;i++) {
    transmitBuf[i] = 0; /* pre sequence */
  }
  for(i=0;i<NEO_NOF_PIXEL;i++) {
    SetPixelColor(i, 0, 0, 0);
  }
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

void NP_Start(void) {
  uint8_t red, green, blue;
  uint32_t pixel;

  InitTransmitBuf();
  InitTimer();
  InitDMA();
  transferComplete = FALSE;
  Cpu_EnableInt(); /* enable interrupts */
  red = green = blue = 0;
  for(;;) {
    for(pixel=0;pixel<NEO_NOF_PIXEL;pixel++) {
      SetPixelColor(pixel, red, green, blue);
      Transfer((uint32_t)&transmitBuf[0]);
      WAIT1_Waitms(10);
      red += 2;
      green += 2;
      blue += 2;
      SetPixelColor(pixel, 0, 0, 0); /* clear pixel again */
      Transfer((uint32_t)&transmitBuf[0]);
      WAIT1_Waitms(5);
    }
  }
}
