/*
 * Test.c
 *
 *  Created on: 20.10.2014
 *      Author: tastyger
 */

#include "Test.h"
#include "PTC.h"
#include "GPIO_PDD.h"
#include "TPM_PDD.h"
#include "DMA_PDD.h"
#include "WAIT1.h"
#include "TMOUT1.h"
#include "TPM0.h"
#include "Bit2.h"
#include "NeoPixel.h"

//static volatile int nofTransfersToGo = 0;
/*! \todo only one 0xFF value, move to flash */
static uint8_t DataValue[] = {1,2,3,4,5,6,8,9,10,11,12,13,14};

#if 0
void TPM0_OnOverflow(void) {
  TPM_PDD_ClearOverflowInterruptFlag(TPM0_DEVICE);
}
#endif

#if 0
void MyDMAComplete0(void) {
  /*! \todo remove need for interrupt */
}

void MyDMAComplete1(void) {
  /*! \todo remove need for interrupt */
}

void MyDMAComplete2(void) {
  if (nofTransfersToGo>0) {
    nofTransfersToGo--;
  }
}
#endif

static void InitTimer(void) {
  TPM_PDD_SelectPrescalerSource(TPM0_DEVICE, TPM_PDD_SYSTEM); /* enable timer so I can reset the value below */
  TPM_PDD_InitializeCounter(TPM0_DEVICE); /* reset timer counter */
  TPM_PDD_SelectPrescalerSource(TPM0_DEVICE, TPM_PDD_DISABLED); /* disable timer */
  TPM_PDD_WriteModuloReg(TPM0_DEVICE, 6000);
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 0, 1000);
  TPM_PDD_WriteChannelValueReg(TPM0_DEVICE, 1, 3000);
}

static void StartTimer(void) {
  TPM_PDD_SelectPrescalerSource(TPM0_DEVICE, TPM_PDD_SYSTEM); /* enable timer so I can reset the value below */
}

static void StopTimer(void) {
  TPM_PDD_SelectPrescalerSource(TPM0_DEVICE, TPM_PDD_DISABLED); /* disable timer */
}

static uint8_t Transfer(uint32_t dataAddress, size_t nofData) {
  static const uint8_t OneValue = 0xFF; /* value to clear or set the port bits */
  TMOUT1_CounterHandle handle;
  bool isTimeout;
  uint32_t done0, done1, done2;

#if 1
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_0);
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_1);
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_2);
#endif

  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, (uint32_t)&OneValue); /* set source address */
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, dataAddress); /* set source address */
  DMA_PDD_SetSourceAddress(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, (uint32_t)&OneValue); /* set source address */

  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, nofData); /* set number of bytes to transfer */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, nofData); /* set number of bytes to transfer */
  DMA_PDD_SetByteCount(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, nofData); /* set number of bytes to transfer */

  //nofTransfersToGo = 1;

  Bit2_SetVal(); /* toggle pin for debugging purpose */

  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_ENABLE); /* enable request from peripheral */

  StartTimer();

  isTimeout = FALSE;
  handle = TMOUT1_GetCounter(100/TMOUT1_TICK_PERIOD_MS);
  //while(nofTransfersToGo>0) {
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
  }
  StopTimer();
#if 0
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_0);
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_1);
  DMA_PDD_ClearDoneFlag(DMA_BASE_PTR, DMA_PDD_CHANNEL_2);
#endif

  TMOUT1_LeaveCounter(handle);

  Bit2_ClrVal(); /* toggle pin for debugging purpose */

  if (isTimeout) {
    return ERR_BUSY;
  }
  return ERR_OK;
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

#if 1
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_0, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_1, PDD_ENABLE); /* enable request from peripheral */
  DMA_PDD_EnablePeripheralRequest(DMA_BASE_PTR, DMA_PDD_CHANNEL_2, PDD_ENABLE); /* enable request from peripheral */
#endif
}

static int transferCntr = 10;
static portTASK_FUNCTION(TaskT0, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    if (transferCntr>0) {
      NEO_TransferPixels();
      transferCntr--;
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  } /* for */
}

void Test(void) {
  //InitDMA();
  NEO_Init();
  NEO_SetPixelRGB(0, 0xff, 0x00, 0x00);
  NEO_SetPixelRGB(1, 0x00, 0xFF, 0x00);
  NEO_SetPixelRGB(2, 0x00, 0x00, 0xff);
  NEO_SetPixelRGB(3, 0xff, 0x00, 0x00);
  NEO_SetPixelRGB(4, 0xff, 0x00, 0xFF);
  NEO_SetPixelRGB(5, 0xff, 0x00, 0xFF);
  NEO_SetPixelRGB(6, 0xff, 0x00, 0xFF);
  NEO_SetPixelRGB(7, 0xff, 0x00, 0xFF);
#if 0
  //for(;;) {
//#if 0
    //GPIO_PDD_TogglePortDataOutputMask(FPTC_BASE_PTR, 0xff);
    GPIO_PDD_SetPortDataOutputMask(FPTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);
    GPIO_PDD_ClearPortDataOutputMask(FPTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);

    GPIO_PDD_SetPortDataOutputMask(PTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);
    GPIO_PDD_ClearPortDataOutputMask(PTC_BASE_PTR, 0xff);
    WAIT1_Waitms(10);
//#endif
 // }
#endif
#if 0
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0xff);
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0x00);
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0xff);
  GPIO_PDD_SetPortDataOutput(PTC_DEVICE, 0x00);
#endif
  if (FRTOS1_xTaskCreate(TaskT0, "T0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL) != pdPASS) {
    for(;;){} /* error */
  }

}


