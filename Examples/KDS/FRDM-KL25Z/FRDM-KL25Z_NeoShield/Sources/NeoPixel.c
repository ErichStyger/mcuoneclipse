/*
 * NeoPixel.c
 *
 *  Created on: 02.06.2014
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_NEO_PIXEL
#include "NeoPixel.h"
#include "PE_Types.h"
#include "DMA1.h"
#include "DMACH1.h"
#include "DMA_PDD.h"
#include "DMAMUX_PDD.h"
#include "TPM_PDD.h"
#include "WAIT1.h"
#include "GDisp1.h"

/* 48 MHz, WS2812(S) */
#define TPM_CH0_TICKS 18  /* 0.35 us */
#define TPM_CH1_TICKS 36  /* 0.9 us */
#define TPM_OVL_TICKS 54+6  /* 1.25 us  */
#define VAL0          0  /* 0 Bit: 0.396 us (need: 0.4 us low) */
#define VAL1          1  /* 1 Bit: 0.792 us (need: 0.8 us high */

#define NEO_NOF_BITS_PIXEL  24  /* 24 bits for pixel */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)
/* transmitBuf: Each bit in the byte is a lane/channel (X coordinate). Need 24bytes for all the RGB bits. The Pixel(0,0) is at transmitBuf[0], Pixel (0,1) at transmitBuf[24]. */
static uint8_t transmitBuf[NEO_NOF_LEDS_IN_LANE*NEO_NOF_BITS_PIXEL];

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

uint8_t NEO_GetPixelColor(NEO_PixelIdxT column, NEO_PixelIdxT row, uint32_t *rgb) {
  uint8_t res, r,g,b;

  res = NEO_GetPixelRGB(column, row, &r, &g, &b);
  *rgb = (r<<16)|(g<<8)|b;
  return res;
}

uint8_t NEO_SetPixelColor(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint32_t rgb) {
  return NEO_SetPixelRGB(lane, pos, (rgb>>16)&0xff, (rgb>>8)&0xff, rgb&0xff);
}

/* sets the color of an individual pixel */
uint8_t NEO_SetPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT idx;
  int i;

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
  return ERR_OK;
}

/* returns the color of an individual pixel */
uint8_t NEO_GetPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t *redP, uint8_t *greenP, uint8_t *blueP) {
  NEO_PixelIdxT idx;
  uint8_t red, green, blue;
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
  *redP = red;
  *greenP = green;
  *blueP = blue;
  return ERR_OK;
}

/* binary OR the color of an individual pixel */
uint8_t NEO_OrPixelRGB(NEO_PixelIdxT x, NEO_PixelIdxT y, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t r, g, b;

  if (x>=NEO_NOF_LANES || y>=NEO_NOF_LEDS_IN_LANE) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelRGB(x, y, &r, &g, &b);
  r |= red;
  b |= blue;
  g |= blue;
  NEO_SetPixelRGB(x, y, red, green, blue);
  return ERR_OK;
}

/* binary XOR the color of an individual pixel */
uint8_t NEO_XorPixelRGB(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t r, g, b;

  if (lane>=NEO_NOF_LANES || pos>=NEO_NOF_LEDS_IN_LANE) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelRGB(lane, pos, &r, &g, &b);
  r ^= red;
  b ^= blue;
  g ^= blue;
  NEO_SetPixelRGB(lane, pos, red, green, blue);
  return ERR_OK;
}

uint8_t NEO_ClearPixel(NEO_PixelIdxT lane, NEO_PixelIdxT pos) {
  return NEO_SetPixelRGB(lane, pos, 0, 0, 0);
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


uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT lane, NEO_PixelIdxT pos, uint8_t percent) {
  uint8_t red, green, blue;
  uint32_t dRed, dGreen, dBlue;
  uint8_t res;

  res = NEO_GetPixelRGB(lane, pos, &red, &green, &blue);
  if (res != ERR_OK) {
    return res;
  }
  dRed = ((uint32_t)red*(100-percent))/100;
  dGreen = ((uint32_t)green*(100-percent))/100;
  dBlue = ((uint32_t)blue*(100-percent))/100;
  return NEO_SetPixelRGB(lane, pos, (uint8_t)dRed, (uint8_t)dGreen, (uint8_t)dBlue);
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

static void InitTransmitBuf(void) {
  NEO_ClearAllPixel();
}

static void InitTimer(void) {
  TPM_PDD_WriteStatusControlReg(TPM0_DEVICE, 0); /* init timer status and control register */
  TPM_PDD_InitializeCounter(TPM0_DEVICE); /* reset timer counter */
  TPM_PDD_WriteModuloReg(TPM0_DEVICE, TPM_OVL_TICKS); /* set overflow to 1.25 us */
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 0, TPM_CH0_TICKS); /* channel 0 match at 0.4 us */
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 1, TPM_CH1_TICKS); /* channel 1 match at 0.8 us */
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
  /* setup address modulo: we are not using it as we stream out the data once and then latch it */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* circular buffer */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* circular buffer */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* circular buffer */
  /* the 'set all bits' and 'clear all bits' DMA events will use a single value, so no address increment.
   * But for the data we will increment the source address counter
   */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* source address incremented by transfer size */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* source address incremented by transfer size */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_DISABLE); /* source address incremented by transfer size */
  /* we transfer one byte every time */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  /* set up destination address:
   * PSOR (Port Set Output Register) will use 0xff to set the bits
   * PDOR (Port Data Output Register) will use the data
   * PDCR (Port Data Clear Register) will use 0xff to clear the bits
   */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&GPIOC_PSOR); /* set destination address: address of PTC Output register */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, (uint32_t)&GPIOC_PDOR); /* set destination address: address of PTC Output register */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, (uint32_t)&GPIOC_PCOR); /* set destination address: address of PTC Output register */
  /* no destination address buffer module: we will stream data only once */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  /* no destination address increments needed */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* no auto-increment for destination address */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_DISABLE); /* no auto-increment for destination address */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_DISABLE); /* no auto-increment for destination address */
  /* we are transferring 1 byte of data */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  /* at the and of the DMA sequence, disable DMA */
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

  if (isTimeout) {
    return ERR_BUSY;
  }
  return ERR_OK;
}

uint8_t NEO_TransferPixels(void) {
  return Transfer((uint32_t)&transmitBuf[0], sizeof(transmitBuf));
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
  InitTransmitBuf();
  InitDMA();
}
#endif /* PL_HAS_NEO_PIXEL */
