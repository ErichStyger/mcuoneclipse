/*
 * Application.c
 *
 *  Created on: 26.07.2015
 *      Author: tastyger
 */

#include "Application.h"
#include "gpio1.h"
#include "osa1.h"
#include <stdbool.h>

static const ftm_pwm_param_t flexTimer1_ChnConfig0 = {
  .mode = kFtmEdgeAlignedPWM,
  .edgeMode = kFtmHighTrue,
  .uFrequencyHZ = 1000U,
  .uDutyCyclePercent = 25U,
  .uFirstEdgeDelayPercent = 0U,
};

static const ftm_pwm_param_t flexTimer1_ChnConfig1 = {
  .mode = kFtmEdgeAlignedPWM,
  .edgeMode = kFtmHighTrue,
  .uFrequencyHZ = 1000U,
  .uDutyCyclePercent = 50U,
  .uFirstEdgeDelayPercent = 0U,
};

static const ftm_user_config_t flexTimer1_InitConfig0 = {
  .tofFrequency      = 0U,
  .isWriteProtection = false,
  .BDMMode           = kFtmBdmMode_00,
  .syncMethod        = (uint32_t)(kFtmUseSoftwareTrig)
};

static void InitFlexTimer(uint32_t instance) {
  FTM_Type *ftmBase = g_ftmBase[instance];

  FTM_DRV_Init(instance, &flexTimer1_InitConfig0);
  FTM_DRV_SetClock(instance, kClock_source_FTM_SystemClk, kFtmDividedBy1);
  FTM_DRV_PwmStart(instance, (ftm_pwm_param_t*)&flexTimer1_ChnConfig0, 0U); /* this will start the clock! */
  /* stop clock, so we can init second channel */
  //FTM_DRV_CounterStop(instance);
  FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);
  FTM_DRV_PwmStart(instance, (ftm_pwm_param_t*)&flexTimer1_ChnConfig1, 1U); /* this will start the clock! */
  /* stop it again */
  //FTM_DRV_CounterStop(instance);
  FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);

  FTM_DRV_SetTimeOverflowIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetFaultIntCmd(instance, false); /* disable interrupt */
}

static void StartTransfer(uint32_t instance) {
  FTM_Type *ftmBase = g_ftmBase[instance];

  /*! \todo signals need to be low, are random now */
  /* enable DMA */
  FTM_HAL_SetChnDmaCmd(ftmBase, 0, true);
  //FTM_HAL_SetChnDmaCmd(ftmBase, 1, true);
  /* clock it */
  FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_SystemClk);
  OSA_TimeDelay(100);
  FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);
  /* disable DMA */
  FTM_HAL_SetChnDmaCmd(ftmBase, 0, false);
  //FTM_HAL_SetChnDmaCmd(ftmBase, 1, false);
}

//#define BUFFER_SIZE               16/*! Total transfer size */
//#define EDMA_TRANSFER_SIZE        2 /*! Transfer size on basic loop */
//#define EDMA_CHAIN_LENGTH         1 /*! Number of srcSG and destSG */
//#define EDMA_WARTERMARK_LEVEL     8 /*! number of bytes transfered on each EDMA request(minor loop) */

static volatile bool dmaDone = false;

#define NEO_NOF_PIXEL 1
#define NEO_NOF_BITS_PIXEL 24
static const uint8_t OneValue = 0xFF; /* value to clear or set the port bits */
static uint8_t transmitBuf[] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};

void EDMA_Callback(void *param, edma_chn_status_t chanStatus) {
  dmaDone = true;
}

static edma_software_tcd_t stcd; /* transfer control descriptor */
static edma_chn_state_t    chnState;
static edma_state_t         edmaState;
static edma_user_config_t   edmaUserConfig;
static edma_scatter_gather_list_t srcSG, destSG;

static void InitDMA(void) {
  uint32_t channel = 0;
  uint8_t res;

  /* Init eDMA modules. */
  edmaUserConfig.chnArbitration = kEDMAChnArbitrationRoundrobin;
  edmaUserConfig.notHaltOnError = false;
  EDMA_DRV_Init(&edmaState, &edmaUserConfig);

  /* EDMA channel request. */
//  res = EDMA_DRV_RequestChannel(channel, kDmaRequestMux0AlwaysOn62, &chnState);
  res = EDMA_DRV_RequestChannel(channel, kDmaRequestMux0FTM0Channel0, &chnState);
  if (res==kEDMAInvalidChannel) {
    for(;;);
  }

  /* Configure EDMA channel. */
  srcSG.address  = (uint32_t)&transmitBuf[0];//&OneValue;
  destSG.address = (uint32_t)&GPIO_PDOR_REG(PTD_BASE_PTR);//&GPIO_PSOR_REG(PTD_BASE_PTR);
  srcSG.length   = 4; /* number of total bytes to read */
  destSG.length  = 4; /* number of total bytes to write */

  /* Install callback for eDMA handler */
  EDMA_DRV_InstallCallback(&chnState, EDMA_Callback, NULL);
}

static void StartStopFTM(uint32_t instance, bool startIt) {
  FTM_Type *ftmBase = g_ftmBase[instance];

  if (startIt) {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_SystemClk); /* clock timer */
  } else {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None); /* disable clock */
  }
}

static void DoDMA(void) {
  /* configure single end descriptor chain. */
#if 1
  EDMA_DRV_ConfigScatterGatherTransfer(
          &chnState, /* channel information */
          &stcd, /* transfer control descriptor */
          kEDMAMemoryToPeripheral, /* perform memory to peripheral operation */
          1, //EDMA_TRANSFER_SIZE, /* 2: transfer size of basic loop */
          1, //EDMA_WARTERMARK_LEVEL, /* 8: number of bytes transfered on each EDMA request(minor loop) */
          &srcSG, &destSG, /* source and destination scatter-gather */
          1 /* number of scatter-gather in chain */
          );
#else
  EDMA_DRV_ConfigLoopTransfer(
      &chnState, /* channel information */
      &stcd, /* transfer control descriptor */
      kEDMAMemoryToPeripheral, /* perform memory to peripheral operation */
      (uint32_t)&transmitBuf[0], //srcAddr,
      (uint32_t)&GPIO_PDOR_REG(PTD_BASE_PTR), //dstAddr,
      1, //size ==> transferSize,
      1, //eachrequest,
      1, //totallength,
      1); //number);
#endif
  /* Initialize transfer. */
  dmaDone = false;
  EDMA_DRV_StartChannel(&chnState); /* enable DMA */
  StartStopFTM(FTM0_IDX, true); /* start timer */
  do {
    /* Wait until transfer is complete */
  } while(!dmaDone);
  StartStopFTM(FTM0_IDX, false); /* stop timer */
  EDMA_DRV_StopChannel(&chnState); /* stop DMA channel */
  /* Release channel */
  //EDMA_DRV_ReleaseChannel(&chnState);
}

static bool start = false;

void APP_Run(void) {
  int i;

  GPIO_PCOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Clear Output PTD0 */
  InitFlexTimer(FTM0_IDX);
  InitDMA();
  for(;;) {
    GPIO_DRV_TogglePinOutput(LEDRGB_BLUE);
    OSA_TimeDelay(100);
    if (start) {
      GPIO_PCOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Clear Output PTD0 */
      DoDMA();
      //GPIO_PTOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Toggle Output PTD0 */
      //GPIO_PSOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Set Output PTD0 */
//      GPIO_PTOR_REG(PTE_BASE_PTR) = (1<<26); /* toggle PTE26 (GREEN RGB) */
    }
  }
}

/*! @brief EDMA ERROR IRQ handler with the same name in the startup code*/
void DMA_Error_IRQHandler(void)
{
    EDMA_DRV_ErrorIRQHandler(0);
}

