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

static uint16_t dmaSrc[] /*__attribute__ ((aligned (32)))*/ = {
     /* LED1 */
     0, 0,     /* need trailing value, otherwise hardware is missing first transfer? */
     VAL0, VAL0, VAL0, VAL0, VAL1, VAL1, VAL1, VAL1,
     VAL0, VAL0, VAL0, VAL0, VAL1, VAL1, VAL1, VAL1,
     VAL0, VAL0, VAL0, VAL0, VAL1, VAL1, VAL1, VAL1,
     0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,/* latch, low for at least 50 us (40x1.25us) */
     //VAL0, 0 /* only to mark the end, to be removed */
};

void MyDMAComplete(void) {
  DMA_PDD_SetByteCount(DMA_BASE_PTR, 0, sizeof(dmaSrc));
}

static void Transfer(void) {
  TPM_PDD_WriteModuloReg(TPM0_BASE_PTR, TICKS_PERIOD); /* set period */
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 1, 0); /* PWM low, zero duty */
  TPM_PDD_EnableChannelDma(TPM0_DEVICE, 1); /* enable DMA for channel */

  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&dmaSrc[0]); /* set source address */
  DMA_PDD_SetSourceAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_EnableSourceAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* source address will be incremented by transfer size */
  DMA_PDD_SetSourceDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_16_BIT); /* Transfer size from source is 16bit */

  DMA_PDD_SetDestinationAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&TPM0_C1V); /* set destination address */
  DMA_PDD_SetDestinationAddressModulo(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_CIRCULAR_BUFFER_DISABLED); /* no circular buffer */
  DMA_PDD_EnableDestinationAddressIncrement(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* no auto-increment for destination address */
  DMA_PDD_SetDestinationDataTransferSize(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, DMA_PDD_16_BIT); /* Transfer to destination size is 16bit */

  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, sizeof(dmaSrc)); /* set number of bytes to transfer */
  DMA_PDD_EnableTransferCompleteInterrupt(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_DISABLE); /* request interrupt at the end of the DMA transfer to set new byte count */
  (void)DMA_PDD_GetRequestAutoDisableEnabled(DMA_BASE_PTR, DMA_PDD_CHANNEL_0); /* disable DMA request at the end of the sequence */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
}

void NP_Start(void) {
  Cpu_EnableInt(); /* enable interrupts */
  Transfer();
  for(;;) {
  }
}
