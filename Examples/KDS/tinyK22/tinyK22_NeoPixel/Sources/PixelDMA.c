/*
 * PixelDMA.c
 *
 *  Created on: 14.07.2018
 *      Author: Erich Styger
 */

#include "PE_Error.h"
#include <stdint.h>
#include <stddef.h>
#include "Cpu.h"
#include "DMA_PDD.h"
#include "DMAMUX_PDD.h"
#include "FTM_PDD.h"
#include "PixelDMA.h"
#include "TMOUT1.h"
#include "WAIT1.h"

/* 48 MHz, WS2812(S) */
#define FTM_CH0_TICKS 100*18  /* 0.35 us */
#define FTM_CH1_TICKS 100*36  /* 0.9 us */
#define FTM_OVL_TICKS 100*(54+6)  /* 1.25 us  */

static void InitTimer(void) {
  FTM_PDD_WriteStatusControlReg(FTM0_BASE_PTR, 0); /* init timer status and control register */
  FTM_PDD_InitializeCounter(FTM0_BASE_PTR); /* reset timer counter */
  FTM_PDD_WriteModuloReg(FTM0_BASE_PTR, FTM_OVL_TICKS); /* set overflow to 1.25 us */
  FTM_PDD_WriteChannelValueReg(FTM0_BASE_PTR, 0, FTM_CH0_TICKS); /* channel 0 match at 0.4 us */
  FTM_PDD_WriteChannelValueReg(FTM0_BASE_PTR, 1, FTM_CH1_TICKS); /* channel 1 match at 0.8 us */
}

static void StartTimer(void) {
  FTM_PDD_InitializeCounter(FTM0_BASE_PTR); /* reset timer counter */
  FTM_PDD_SelectPrescalerSource(FTM0_BASE_PTR, FTM_PDD_SYSTEM); /* enable timer so I can reset the value below */
}

static void StopTimer(void) {
  FTM_PDD_SelectPrescalerSource(FTM0_BASE_PTR, FTM_PDD_DISABLED); /* disable timer */
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
  /* address increment is on by default on the K22? */
  //DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* source address incremented by transfer size */
//  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* source address incremented by transfer size */
//  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_DISABLE); /* source address incremented by transfer size */
  /* we transfer one byte every time */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_8_BIT); /* Transfer size from source is 8bit */
  /* set up destination address:
   * PSOR (Port Set Output Register) will use 0xff to set the bits
   * PDOR (Port Data Output Register) will use the data
   * PDCR (Port Data Clear Register) will use 0xff to clear the bits
   */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&GPIOD_PSOR); /* set destination address: address of PTD Output register */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, (uint32_t)&GPIOD_PDOR); /* set destination address: address of PTD Output register */
  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, (uint32_t)&GPIOD_PCOR); /* set destination address: address of PTD Output register */
  /* no destination address buffer module: we will stream data only once */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  /* no destination address increments needed */
//  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* no auto-increment for destination address */
//  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_DISABLE); /* no auto-increment for destination address */
//  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_DISABLE); /* no auto-increment for destination address */
  /* we are transferring 1 byte of data */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, DMA_PDD_8_BIT); /* Transfer to destination size is 16bit */
  /* at the and of the DMA sequence, disable DMA */
  DMA_PDD_EnableRequestAutoDisable(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* disable DMA request at the end of the sequence */
  DMA_PDD_EnableRequestAutoDisable(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* disable DMA request at the end of the sequence */
  DMA_PDD_EnableRequestAutoDisable(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_ENABLE); /* disable DMA request at the end of the sequence */
}

uint8_t PIXDMA_Transfer(uint32_t dataAddress, size_t nofBytes) {
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
  DMA_PDD_SetByteCount32(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, nofBytes); /* set number of bytes to transfer */
  DMA_PDD_SetByteCount32(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, nofBytes); /* set number of bytes to transfer */
  DMA_PDD_SetByteCount32(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, nofBytes); /* set number of bytes to transfer */

  /* reset TPM counter */
  FTM_PDD_InitializeCounter(FTM0_BASE_PTR); /* reset timer counter */
  FTM_PDD_ClearChannelFlags(FTM0_BASE_PTR, 0x00);
  FTM_PDD_ClearOverflowInterruptFlag(FTM0_BASE_PTR);
  /* re-enable DMA Muxing: it will disabled at the end of the transfer */
  DMAMUX_PDD_EnableChannel(DMAMUX_BASE_PTR, 0, PDD_ENABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX_BASE_PTR, 1, PDD_ENABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX_BASE_PTR, 2, PDD_ENABLE);
  /* enable DMA peripheral requests */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
  /* clear timer flags and status so it starts from a clean starting point */
  FTM_PDD_ClearChannelFlags(FTM0_BASE_PTR, 0x00);
  FTM_PDD_ClearOverflowInterruptFlag(FTM0_BASE_PTR);
  /* enable TPM DMA */
#if 0
  FTM_PDD_WriteStatusControlReg(FTM0_BASE_PTR, FTM_PDD_ReadStatusControlReg(FTM0_BASE_PTR)|FTM_SC_DMA_MASK);
#endif
  FTM_PDD_EnableChannelDma(FTM0_BASE_PTR, 1);
  FTM_PDD_EnableChannelDma(FTM0_BASE_PTR, 0);

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
  DMAMUX_PDD_EnableChannel(DMAMUX_BASE_PTR, 0, PDD_DISABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX_BASE_PTR, 1, PDD_DISABLE);
  DMAMUX_PDD_EnableChannel(DMAMUX_BASE_PTR, 2, PDD_DISABLE);
#if 0
  /* disable peripheral DMA */
  FTM_PDD_WriteStatusControlReg(FTM0_BASE_PTR, FTM_PDD_ReadStatusControlReg(FTM0_BASE_PTR)&(~FTM_SC_DMA_MASK));
#endif
  FTM_PDD_DisableChannelDma(FTM0_BASE_PTR, 1);
  FTM_PDD_DisableChannelDma(FTM0_BASE_PTR, 0);

  StopTimer(); /* stop TPM */

  if (isTimeout) {
    return ERR_BUSY;
  }
  return ERR_OK;
}

void PIXDMA_Init(void) {
  InitDMA();
}
