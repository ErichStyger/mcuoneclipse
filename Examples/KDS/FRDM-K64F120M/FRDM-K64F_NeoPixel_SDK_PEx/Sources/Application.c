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

static volatile bool dmaDone = false;

#define NEO_NOF_PIXEL       1
#define NEO_NOF_BITS_PIXEL 24
static const uint8_t OneValue[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /* value to clear or set the port bits */
static uint8_t transmitBuf[] = {0x11,0x20,0x31,0x40,0x51,0x60,0x71,0x80}; /* bit values */

static const ftm_user_config_t flexTimer0_InitConfig0 = {
  .tofFrequency      = 0U,
  .isWriteProtection = false,
  .BDMMode           = kFtmBdmMode_00,
  .syncMethod        = (uint32_t)(kFtmUseSoftwareTrig)
};

static const ftm_pwm_param_t flexTimer0_ChnConfig0 = { /* FTM0, channel 0 */
  .mode = kFtmEdgeAlignedPWM,
  .edgeMode = kFtmHighTrue,
  .uFrequencyHZ = 1000U,
  .uDutyCyclePercent = 10U,
  .uFirstEdgeDelayPercent = 0U,
};

static const ftm_pwm_param_t flexTimer0_ChnConfig1 = { /* FTM0, channel 1 */
  .mode = kFtmEdgeAlignedPWM,
  .edgeMode = kFtmHighTrue,
  .uFrequencyHZ = 1000U,
  .uDutyCyclePercent = 20U,
  .uFirstEdgeDelayPercent = 0U,
};

static const ftm_pwm_param_t flexTimer0_ChnConfig2 = { /* FTM0, channel 2 */
  .mode = kFtmEdgeAlignedPWM,
  .edgeMode = kFtmHighTrue,
  .uFrequencyHZ = 1000U,
  .uDutyCyclePercent = 50U,
  .uFirstEdgeDelayPercent = 0U,
};

static void InitFlexTimer(uint32_t instance) {
  uint8_t channel;
  FTM_Type *ftmBase = g_ftmBase[instance];

  FTM_DRV_Init(instance, &flexTimer0_InitConfig0);
  FTM_DRV_SetTimeOverflowIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetFaultIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetClock(instance, kClock_source_FTM_SystemClk, kFtmDividedBy1);
  /* channel 0 */
  FTM_DRV_PwmStart(instance, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 0U); /* this will start the clock! */
  FTM_DRV_CounterStop(instance); /* stop clock, so we can init second channel */
  /* channel 1 */
  FTM_DRV_PwmStart(instance, (ftm_pwm_param_t*)&flexTimer0_ChnConfig1, 1U); /* this will start the clock! */
  FTM_DRV_CounterStop(instance); /* stop it again */
  /* channel 2 */
  FTM_DRV_PwmStart(instance, (ftm_pwm_param_t*)&flexTimer0_ChnConfig2, 2U); /* this will start the clock! */
  FTM_DRV_CounterStop(instance); /* stop it again */

  /* reset all values */
  FTM_HAL_SetCounter(ftmBase, 0); /* reset counter */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow flag (if any) */
  for(channel=0; channel<=2; channel++) {
    FTM_HAL_ClearChnEventFlag(ftmBase, channel); /* clear channel 0 flag */
    FTM_HAL_SetChnDmaCmd(ftmBase, channel, true); /* enable DMA request */
    FTM_HAL_EnableChnInt(ftmBase, channel); /* enable channel interrupt: need to have both DMA and CHnIE set for DMA transfers! See RM 40.4.23 */
  }
}

void EDMA_Callback(void *param, edma_chn_status_t chanStatus) {
  dmaDone = true;
}

static edma_software_tcd_t stcd0, stcd1, stcd2; /* transfer control descriptor */
static edma_chn_state_t    chn0State, chn1State, chn2State;
static edma_state_t        edmaState;
static edma_user_config_t  edmaUserConfig;
static edma_scatter_gather_list_t src0SG, src1SG, src2SG, dest0SG, dest1SG, dest2SG;

static void InitDMA(void) {
  uint8_t res;

  /* Initialize eDMA modules. */
  edmaUserConfig.chnArbitration = kEDMAChnArbitrationRoundrobin; /* use round-robin arbitration */
  edmaUserConfig.notHaltOnError = false; /* do not halt in case of errors */
  EDMA_DRV_Init(&edmaState, &edmaUserConfig); /* initialize DMA with configuration */

  /* EDMA channel request. */
//  res = EDMA_DRV_RequestChannel(channel, kDmaRequestMux0AlwaysOn62, &chn0State); /* always on channel */
  res = EDMA_DRV_RequestChannel(0, kDmaRequestMux0FTM0Channel0, &chn0State);
  if (res==kEDMAInvalidChannel) { /* check error code */
    for(;;); /* ups!?! */
  }
  res = EDMA_DRV_RequestChannel(1, kDmaRequestMux0FTM0Channel1, &chn1State);
  if (res==kEDMAInvalidChannel) { /* check error code */
    for(;;); /* ups!?! */
  }
  res = EDMA_DRV_RequestChannel(2, kDmaRequestMux0FTM0Channel2, &chn2State);
  if (res==kEDMAInvalidChannel) { /* check error code */
    for(;;); /* ups!?! */
  }

  /* Configure EDMA channels */
  src0SG.address  = (uint32_t)&OneValue[0];
  dest0SG.address = (uint32_t)&GPIO_PSOR_REG(PTD_BASE_PTR);
  src0SG.length   = 8; /* number of total bytes to read */
  dest0SG.length  = 8; /* number of total bytes to write */

  src1SG.address  = (uint32_t)&transmitBuf[0];//&OneValue;
  dest1SG.address = (uint32_t)&GPIO_PDOR_REG(PTD_BASE_PTR);
  src1SG.length   = 8; /* number of total bytes to read */
  dest1SG.length  = 8; /* number of total bytes to write */

  src2SG.address  = (uint32_t)&OneValue[0];
  dest2SG.address = (uint32_t)&GPIO_PCOR_REG(PTD_BASE_PTR);
  src2SG.length   = 8; /* number of total bytes to read */
  dest2SG.length  = 8; /* number of total bytes to write */

  /* Install callback for eDMA handler on channel 2 */
  EDMA_DRV_InstallCallback(&chn2State, EDMA_Callback, NULL);
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
  /* configure single end descriptor chain */
  EDMA_DRV_ConfigScatterGatherTransfer(
          &chn0State, /* channel information */
          &stcd0, /* transfer control descriptor */
          kEDMAMemoryToPeripheral, /* perform memory to peripheral operation */
          1, /* transfer size of basic loop */
          1, /* number of bytes transfered on each EDMA request(minor loop) */
          &src0SG, &dest0SG, /* source and destination scatter-gather */
          1 /* number of scatter-gather in chain */
          );
  EDMA_DRV_ConfigScatterGatherTransfer(
          &chn1State, /* channel information */
          &stcd1, /* transfer control descriptor */
          kEDMAMemoryToPeripheral, /* perform memory to peripheral operation */
          1, /* transfer size of basic loop */
          1, /* number of bytes transfered on each EDMA request(minor loop) */
          &src1SG, &dest1SG, /* source and destination scatter-gather */
          1 /* number of scatter-gather in chain */
          );
  EDMA_DRV_ConfigScatterGatherTransfer(
          &chn2State, /* channel information */
          &stcd2, /* transfer control descriptor */
          kEDMAMemoryToPeripheral, /* perform memory to peripheral operation */
          1, /* transfer size of basic loop */
          1, /* number of bytes transfered on each EDMA request(minor loop) */
          &src2SG, &dest2SG, /* source and destination scatter-gather */
          1 /* number of scatter-gather in chain */
          );
  /* initialize transfer */
  dmaDone = false; /* reset done flag */
  EDMA_DRV_StartChannel(&chn0State); /* enable DMA */
  EDMA_DRV_StartChannel(&chn1State); /* enable DMA */
  EDMA_DRV_StartChannel(&chn2State); /* enable DMA */
  StartStopFTM(FTM0_IDX, true); /* start timer */
  do {
    /* wait until transfer is complete */
  } while(!dmaDone);
  StartStopFTM(FTM0_IDX, false); /* stop timer */
  EDMA_DRV_StopChannel(&chn0State); /* stop DMA channel */
  EDMA_DRV_StopChannel(&chn1State); /* stop DMA channel */
  EDMA_DRV_StopChannel(&chn2State); /* stop DMA channel */
}

static bool start = false;

void APP_Run(void) {
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
      //GPIO_PTOR_REG(PTE_BASE_PTR) = (1<<26); /* toggle PTE26 (GREEN RGB) */
    }
  }
}

/*! @brief EDMA ERROR IRQ handler with the same name in the startup code*/
void DMA_Error_IRQHandler(void) {
  EDMA_DRV_ErrorIRQHandler(0);
}

