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

/* 48 MHz, WS2812(S) */
#define TPM_CH0_TICKS 18  /* 0.35 us */
#define TPM_CH1_TICKS 36  /* 0.9 us */
#define TPM_OVL_TICKS 54+6  /* 1.25 us  */
#define VAL0          0  /* 0 Bit: 0.396 us (need: 0.4 us low) */
#define VAL1          1  /* 1 Bit: 0.792 us (need: 0.8 us high */

#define NEO_NOF_BITS_PIXEL  24  /* 24 bits for pixel */
#define NEO_DMA_NOF_BYTES   sizeof(transmitBuf)

static uint8_t transmitBuf[NEOC_NOF_Y*NEO_NOF_BITS_PIXEL];

uint8_t NEO_GetPixelColor(NEO_PixelIdxT column, NEO_PixelIdxT row, uint32_t *rgb) {
  uint8_t res, r,g,b;

  res = NEO_GetPixelRGB(column, row, &r, &g, &b);
  *rgb = (r<<16)|(g<<8)|b;
  return res;
}

uint8_t NEO_SetPixelColor(NEO_PixelIdxT x, NEO_PixelIdxT y, uint32_t rgb) {
  return NEO_SetPixelRGB(x, y, (rgb>>16)&0xff, (rgb>>8)&0xff, rgb&0xff);
}

/* sets the color of an individual pixel */
uint8_t NEO_SetPixelRGB(NEO_PixelIdxT x, NEO_PixelIdxT y, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT idx;
  int i;

  if (x>=NEO_NOF_X || y>=NEO_NOF_Y) {
    return ERR_RANGE; /* error, out of range */
  }
  idx = y*NEO_NOF_BITS_PIXEL;
  /* green */
  for(i=0;i<8;i++) {
    if (green&0x80) {
      transmitBuf[idx] |= (VAL1<<x); /* set bit */
    } else {
      transmitBuf[idx] &= ~(VAL1<<x); /* clear bit */
    }
    green <<= 1; /* next bit */
    idx++;
  }
  /* red */
  for(i=0;i<8;i++) {
    if (red&0x80) {
      transmitBuf[idx] |= (VAL1<<x); /* set bit */
    } else {
      transmitBuf[idx] &= ~(VAL1<<x); /* clear bit */
    }
    red <<= 1; /* next bit */
    idx++;
  }
  /* blue */
  for(i=0;i<8;i++) {
    if (blue&0x80) {
      transmitBuf[idx] |= (VAL1<<x); /* set bit */
    } else {
      transmitBuf[idx] &= ~(VAL1<<x); /* clear bit */
    }
    blue <<= 1; /* next bit */
    idx++;
  }
  return ERR_OK;
}

/* returns the color of an individual pixel */
uint8_t NEO_GetPixelRGB(NEO_PixelIdxT x, NEO_PixelIdxT y, uint8_t *redP, uint8_t *greenP, uint8_t *blueP) {
  NEO_PixelIdxT idx;
  uint8_t red, green, blue;
  int i;

  if (x>=NEO_NOF_X || y>=NEO_NOF_Y) {
    return ERR_RANGE; /* error, out of range */
  }
  red = green = blue = 0; /* init */
  idx = y*NEO_NOF_BITS_PIXEL;
  /* green */
  for(i=0;i<8;i++) {
    green <<= 1;
    if (transmitBuf[idx]&(VAL1<<x)) {
      green |= 1;
    }
    idx++; /* next bit */
  }
  /* red */
  for(i=0;i<8;i++) {
    red <<= 1;
    if (transmitBuf[idx]&(VAL1<<x)) {
      red |= 1;
    }
    idx++; /* next bit */
  }
  /* blue */
  for(i=0;i<8;i++) {
    blue <<= 1;
    if (transmitBuf[idx]&(VAL1<<x)) {
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

  if (x>=NEO_NOF_X || y>=NEO_NOF_Y) {
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
uint8_t NEO_XorPixelRGB(NEO_PixelIdxT x, NEO_PixelIdxT y, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t r, g, b;

  if (x>=NEO_NOF_X || y>=NEO_NOF_Y) {
    return ERR_RANGE; /* error, out of range */
  }
  NEO_GetPixelRGB(x, y, &r, &g, &b);
  r ^= red;
  b ^= blue;
  g ^= blue;
  NEO_SetPixelRGB(x, y, red, green, blue);
  return ERR_OK;
}

uint8_t NEO_ClearPixel(NEO_PixelIdxT x, NEO_PixelIdxT y) {
  return NEO_SetPixelRGB(x, y, 0, 0, 0);
}

uint8_t NEO_DimmPercentPixel(NEO_PixelIdxT x, NEO_PixelIdxT y, uint8_t percent) {
  uint8_t red, green, blue;
  uint32_t dRed, dGreen, dBlue;
  uint8_t res;

  res = NEO_GetPixelRGB(x, y, &red, &green, &blue);
  if (res != ERR_OK) {
    return res;
  }
  dRed = ((uint32_t)red*(100-percent))/100;
  dGreen = ((uint32_t)green*(100-percent))/100;
  dBlue = ((uint32_t)blue*(100-percent))/100;
  return NEO_SetPixelRGB(x, y, (uint8_t)dRed, (uint8_t)dGreen, (uint8_t)dBlue);
}

uint8_t NEO_ClearAllPixel(void) {
  NEO_PixelIdxT x, y;
  uint8_t res;

  for(y=0;y<NEO_NOF_Y;y++) {
    for(x=0;x<NEO_NOF_X;x++) {
      res = NEO_ClearPixel(x, y);
      if (res!=ERR_OK) {
        return res;
      }
    }
  }
  return ERR_OK;
}

uint8_t NEO_SetAllPixelColor(uint32_t rgb) {
  NEO_PixelIdxT x, y;
  uint8_t res;

  for(y=0;y<NEO_NOF_Y;y++) {
    for(x=0;x<NEO_NOF_X;x++) {
      res = NEO_SetPixelColor(x, y, rgb);
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
  uint8_t buf[16];

  CLS1_SendStatusStr((unsigned char*)"neo", (const unsigned char*)"\r\n", io->stdOut);
  UTIL1_Num32uToStr(buf, sizeof(buf), NEO_NOF_X);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  X", buf, io->stdOut);

  UTIL1_Num32uToStr(buf, sizeof(buf), NEO_NOF_Y);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  Y", buf, io->stdOut);

  UTIL1_Num32uToStr(buf, sizeof(buf), NEO_NOF_PIXEL);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr("  Pixels", buf, io->stdOut);
  return ERR_OK;
}

uint8_t NEO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  uint32_t color;
  int32_t tmp, x, y;
  const uint8_t *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "neo help")==0) {
    CLS1_SendHelpStr((unsigned char*)"neo", (const unsigned char*)"Group of neo commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  clear all", (const unsigned char*)"Clear all pixels\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  set all <rgb>", (const unsigned char*)"Set all pixel with RGB value\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  set <x> <y> <rgb>", (const unsigned char*)"Set pixel with RGB value\r\n", io->stdOut);
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
  } else if (UTIL1_strncmp((char*)cmd, "neo set", sizeof("neo set")-1)==0) {
    p = cmd+sizeof("neo set")-1;
    res = UTIL1_xatoi(&p, &x); /* read x pixel index */
    if (res==ERR_OK && x>=0 && x<NEO_NOF_X) {
      res = UTIL1_xatoi(&p, &y); /* read y pixel index */
      if (res==ERR_OK && y>=0 && y<NEO_NOF_Y) {
        res = UTIL1_xatoi(&p, &tmp); /* read color RGB value */
        if (res==ERR_OK && tmp>=0 && tmp<=0xffffff) {
          color = tmp;
          NEO_SetPixelColor((NEO_PixelIdxT)x, (NEO_PixelIdxT)y, color);
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
