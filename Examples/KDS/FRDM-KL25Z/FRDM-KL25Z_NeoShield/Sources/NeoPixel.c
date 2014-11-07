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
#include "DMAMUX_PDD.h"
#include "TPM_PDD.h"
#include "WAIT1.h"

/* 48 MHz, WS2812(S) */
#define TICKS_PERIOD  59  /* 1.25 us  (need: 1.25 us)*/
#define VAL0          0  /* 0 Bit: 0.396 us (need: 0.4 us low) */
#define VAL1          1  /* 1 Bit: 0.792 us (need: 0.8 us high */
#define VAL00         0   /* data line low value, e.g. for reset/latch */

#define NEO_NOF_PRE         0 /* somehow needs trailing values? */
#define NEO_NOF_BITS_PIXEL  24  /* 24 bits for pixel */
#define NEO_NOF_POST        0  /* latch, low for at least 50 us (40x1.25us) */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)

static uint8_t transmitBuf[NEO_NOF_PRE+(NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL)+NEO_NOF_POST];

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

static void InitTimer(void) {
  TPM_PDD_WriteStatusControlReg(TPM0_DEVICE, 0); /* init timer */
  TPM_PDD_InitializeCounter(TPM0_DEVICE); /* reset timer counter */
  TPM_PDD_WriteModuloReg(TPM0_DEVICE, (3*18));
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 0, 18);
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 1, 36);
}

static void StartTimer(void) {
  TPM_PDD_InitializeCounter(TPM0_DEVICE); /* reset timer counter */
  TPM_PDD_SelectPrescalerSource(TPM0_DEVICE, TPM_PDD_SYSTEM); /* enable timer so I can reset the value below */
}

static void StopTimer(void) {
  /* set CMOD of SC register to zero to disable timer */
  TPM_PDD_SelectPrescalerSource(TPM0_DEVICE, TPM_PDD_DISABLED); /* disable timer */
}

static void InitDMA(void) {
  InitTimer(); /* timer setup */

  /* initialize PORT C as output */
  //GPIO_PDD_SetPortOutputDirectionMask(PTC_DEVICE, 0xff); /* PTC0..PTC7 as output */

  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* circular buffer */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* circular buffer */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* circular buffer */

  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* source address incremented by transfer size */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* source address incremented by transfer size */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_DISABLE); /* source address incremented by transfer size */

  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */

  /* destination settings */
  /* GPIOC_PDOR Data Out */
  /* GPIOC_PTOR Data Toggle */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&GPIOC_PSOR); /* set destination address: address of PTC Output register */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, (uint32_t)&GPIOC_PDOR); /* set destination address: address of PTC Output register */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, (uint32_t)&GPIOC_PCOR); /* set destination address: address of PTC Output register */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* no auto-increment for destination address */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_DISABLE); /* no auto-increment for destination address */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_DISABLE); /* no auto-increment for destination address */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */

  DMA_PDD_EnableRequestAutoDisable(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* disable DMA request at the end of the sequence */
  DMA_PDD_EnableRequestAutoDisable(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* disable DMA request at the end of the sequence */
  DMA_PDD_EnableRequestAutoDisable(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_ENABLE); /* disable DMA request at the end of the sequence */
}

static uint8_t Transfer(uint32_t dataAddress, size_t nofBytes) {
  static const uint8_t OneValue = 0xFF; /* value to clear or set the port bits */
  TMOUT1_CounterHandle handle;
  bool isTimeout;
  uint32_t done0, done1, done2;

  /* clear any pending done flags for DMA channels */
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_0);
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_1);
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_2);
  /* set DMA source addresses */
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&OneValue); /* set source address */
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, dataAddress); /* set source address */
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, (uint32_t)&OneValue); /* set source address */
  /* set byte count addresses */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, nofBytes); /* set number of bytes to transfer */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, nofBytes); /* set number of bytes to transfer */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, nofBytes); /* set number of bytes to transfer */
  /* reset TPM counter */
  TPM_PDD_InitializeCounter(TPM0_DEVICE); /* reset timer counter */
  TPM_PDD_ClearChannelFlags(TPM0_DEVICE, 0x00);
  TPM_PDD_ClearOverflowInterruptFlag(TPM0_DEVICE);
  /* re-enable DMA Muxing: it will disabled at the end of the transfer */
  DMAMUX_PDD_EnableChannel(DMAMUX0_BASE_PTR, 0, PDD_ENABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX0_BASE_PTR, 1, PDD_ENABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX0_BASE_PTR, 2, PDD_ENABLE);
  /* enable DMA peripheral requests */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
  /* clear timer flags and status so it starts from a clean starting point */
  TPM_PDD_ClearChannelFlags(TPM0_DEVICE, 0x00);
  TPM_PDD_ClearOverflowInterruptFlag(TPM0_DEVICE);
  /* enable TPM DMA */
  TPM_PDD_WriteStatusControlReg(TPM0_DEVICE,TPM_PDD_ReadStatusControlReg(TPM0_DEVICE)|TPM_SC_DMA_MASK);
  TPM_PDD_EnableChannelDma(TPM0_DEVICE, 1);
  TPM_PDD_EnableChannelDma(TPM0_DEVICE, 0);
  /* start the TPM timer */
  StartTimer();
  Bit2_SetVal(); /* toggle pin for debugging purpose */

  isTimeout = FALSE;
  handle = TMOUT1_GetCounter(100/TMOUT1_TICK_PERIOD_MS);
  for(;;) {
    /* wait until transfer is complete */
    if (TMOUT1_CounterExpired(handle)) {
      isTimeout = TRUE;
      break; /* leave loop */
    }
    done0 = DMA_PDD_GetDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_0);
    done1 = DMA_PDD_GetDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_1);
    done2 = DMA_PDD_GetDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_2);
    if (done0 && done1 && done2) {
      break; /* done! */
    }
    WAIT1_WaitOSms(1); /* give back some time */
  }
  TMOUT1_LeaveCounter(handle);
  WAIT1_Waitus(50); /* latch, low for at least 50 us (40x1.25us) */

  /* disable DMA-Muxing: necessary, otherwise DMA events on TPM0 channel 0 might be still latched.
   * Will enable muxing for next transfer */
  DMAMUX_PDD_EnableChannel(DMAMUX0_BASE_PTR, 0, PDD_DISABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX0_BASE_PTR, 1, PDD_DISABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX0_BASE_PTR, 2, PDD_DISABLE);
  /* disable peripheral DMA */
  TPM_PDD_WriteStatusControlReg(TPM0_DEVICE,TPM_PDD_ReadStatusControlReg(TPM0_DEVICE)&(~TPM_SC_DMA_MASK));
  TPM_PDD_DisableChannelDma(TPM0_DEVICE, 1);
  TPM_PDD_DisableChannelDma(TPM0_DEVICE, 0);

  StopTimer(); /* stop TPM */

  Bit2_ClrVal(); /* toggle pin for debugging purpose */

  if (isTimeout) {
    return ERR_BUSY;
  }
  return ERR_OK;
}

uint8_t NEO_TransferPixels(void) {
  return Transfer((uint32_t)&transmitBuf[0], sizeof(transmitBuf));
}

void NEO_Init(void) {
  InitTransmitBuf();
  InitDMA();
}
