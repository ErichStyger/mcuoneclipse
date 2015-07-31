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
#include "fsl_ftm_driver.h"
#include "fsl_edma_driver.h"
#include <string.h> /* for memset() */

#define NEO_NOF_PIXEL       1
#define NEO_NOF_BITS_PIXEL 24
static const uint8_t OneValue = 0xFF; /* value to clear or set the port bits */
static uint8_t transmitBuf[] =
  {0x11,0x21,0x31,0x41,0x51,0x61,0x71,0x81,
   0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
   0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1
  }; /* bit values */

#define FTM_CH0_TICKS     (0x10)  /* delay until 0xFF */
#define FTM_CH1_TICKS     (0x2A)  /* at 0.4us write data */
#define FTM_CH2_TICKS     (0x40)  /* at 0.8us clear bits  */
#define FTM_PERIOD_TICKS  (0x4A)  /* 1.25 us period */

/* FTM related */
#define NOF_FTM_CHANNELS  3 /* using three FTM0 channels */

/* DMA related */
#define NOF_EDMA_CHANNELS  3 /* using three DMA channels */
static edma_chn_state_t chnStates[NOF_EDMA_CHANNELS]; /* using three DMA channels */
static volatile bool dmaDone = false;

static void InitFlexTimer(uint32_t instance) {
  ftm_pwm_param_t flexTimer0_ChnConfig0 = { /* FTM channel configuration */
    .mode = kFtmEdgeAlignedPWM,
    .edgeMode = kFtmHighTrue,
    .uFrequencyHZ = 1000U, /* dummy value, will change it later on */
    .uDutyCyclePercent = 10U, /* dummy value, will change it later on */
    .uFirstEdgeDelayPercent = 0U,
  };
  ftm_user_config_t flexTimer0_InitConfig0 = {
    .tofFrequency      = 0U,
    .isWriteProtection = false, /* FTM is not write protected */
    .BDMMode           = kFtmBdmMode_00, /* default mode for debug: timer will be stopped, can modify registers */
    .syncMethod        = (uint32_t)(kFtmUseSoftwareTrig) /* using software synchronization */
  };
  FTM_Type *ftmBase = g_ftmBase[instance];
  //uint32_t uFTMhz;

  FTM_DRV_Init(instance, &flexTimer0_InitConfig0);
  FTM_DRV_SetTimeOverflowIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetFaultIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetClock(instance, kClock_source_FTM_SystemClk, kFtmDividedBy1); /* use system clock with a divider of 1 */

  /* configure timer */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow */

  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 0);
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 1);
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 2);
  /* Based on Ref manual, in PWM mode CNTIN is to be set 0*/
  FTM_HAL_SetCounterInitVal(ftmBase, 0);

  //uFTMhz = FTM_DRV_GetClock(instance);
  FTM_HAL_SetMod(ftmBase, FTM_PERIOD_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 0, FTM_CH0_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 1, FTM_CH1_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 2, FTM_CH2_TICKS);
}

static void PrepareFTMforDMAStart(uint32_t instance) {
  FTM_Type *ftmBase = g_ftmBase[instance];
  uint8_t channel;

  /* reset all values */
  FTM_HAL_SetCounter(ftmBase, 0); /* reset FTM counter */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow flag (if any) */
  for(channel=0; channel<NOF_FTM_CHANNELS; channel++) {
    FTM_HAL_ClearChnEventFlag(ftmBase, channel); /* clear channel flag */
    FTM_HAL_SetChnDmaCmd(ftmBase, channel, true); /* enable DMA request */
    FTM_HAL_EnableChnInt(ftmBase, channel); /* enable channel interrupt: need to have both DMA and CHnIE set for DMA transfers! See RM 40.4.23 */
  }
}

static void StartStopFTM(uint32_t instance, bool startIt) {
  FTM_Type *ftmBase = g_ftmBase[instance];

  if (startIt) {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_SystemClk); /* clock timer */
  } else {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None); /* disable clock */
  }
}

static void PrepareFTMforDMAStopped(uint32_t instance) {
  FTM_Type *ftmBase = g_ftmBase[instance];
  uint8_t channel;

  StartStopFTM(instance, false); /* stop FTM timer */
  /* reset all values */
  FTM_HAL_SetCounter(ftmBase, 0); /* reset FTM counter */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow flag (if any) */
  for(channel=0; channel<NOF_FTM_CHANNELS; channel++) {
    FTM_HAL_DisableChnInt(ftmBase, channel); /* disable channel interrupt */
    FTM_HAL_SetChnDmaCmd(ftmBase, channel, false); /* disable DMA request */
    FTM_HAL_ClearChnEventFlag(ftmBase, channel); /* clear channel flag */
  }
}

void EDMA_Callback(void *param, edma_chn_status_t chanStatus) {
  dmaDone = true;
}

static void InitDMA(void) {
  edma_user_config_t  edmaUserConfig;
  static edma_state_t edmaState;
  uint8_t res, channel;

  /* Initialize eDMA modules. */
  edmaUserConfig.chnArbitration = kEDMAChnArbitrationRoundrobin; /* use round-robin arbitration */
  edmaUserConfig.notHaltOnError = false; /* do not halt in case of errors */
  EDMA_DRV_Init(&edmaState, &edmaUserConfig); /* initialize DMA with configuration */
#if 0
  /* Allocate EDMA channel request trough DMAMUX */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    res = EDMA_DRV_RequestChannel(channel, kDmaRequestMux0FTM0Channel0+channel, &chnStates[channel]);
    if (res==kEDMAInvalidChannel) { /* check error code */
      for(;;); /* ups!?! */
    }
  }
  /* Install callback for eDMA handler on last channel which is channel 2 */
  EDMA_DRV_InstallCallback(&chnStates[NOF_EDMA_CHANNELS-1], EDMA_Callback, NULL);
#endif
}

static void PushDMADescriptor(edma_transfer_config_t *config, edma_chn_state_t *chn, bool enableInt) {
  /* If only one TCD is required, only hardware TCD is required and user
   * is not required to prepare the software TCD memory. */
  edma_software_tcd_t temp[2]; /* make it larger so we can have a 32byte aligned address into it */
  edma_software_tcd_t *tempTCD = STCD_ADDR(temp); /* ensure that we have a 32byte aligned address */

  memset((void*) tempTCD, 0, sizeof(edma_software_tcd_t)); /* initialize temporary descriptor with zeros */
  EDMA_DRV_PrepareDescriptorTransfer(chn, tempTCD, config, enableInt, true); /* prepare and copy descriptor into temporary one */
  EDMA_DRV_PushDescriptorToReg(chn, tempTCD); /* write EDMA registers */
}

static void DoDMA(uint32_t nofBytes) {
  edma_transfer_config_t config;
  uint8_t channel;
  uint8_t res;

  /* clear FTFM and prepare for DMA */
  PrepareFTMforDMAStart(FTM0_IDX);

  /* Allocate EDMA channel request trough DMAMUX */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    res = EDMA_DRV_RequestChannel(channel, kDmaRequestMux0FTM0Channel0+channel, &chnStates[channel]);
    if (res==kEDMAInvalidChannel) { /* check error code */
      for(;;); /* ups!?! */
    }
  }
  /* Install callback for eDMA handler on last channel which is channel 2 */
  EDMA_DRV_InstallCallback(&chnStates[NOF_EDMA_CHANNELS-1], EDMA_Callback, NULL);

  /* prepare DMA configuration */
  config.srcLastAddrAdjust = 0;
  config.destLastAddrAdjust = 0;
  config.srcModulo = kEDMAModuloDisable;
  config.destModulo = kEDMAModuloDisable;
  config.srcTransferSize = kEDMATransferSize_1Bytes;
  config.destTransferSize = kEDMATransferSize_1Bytes;
  config.minorLoopCount = 1; /* one byte transmitted for each request */
  config.majorLoopCount = nofBytes; /* total number of bytes to send */
  config.destOffset = 0; /* do not increment destination address */

  config.srcAddr = (uint32_t)&OneValue;
  config.destAddr = (uint32_t)&GPIO_PSOR_REG(PTD_BASE_PTR);
  config.srcOffset = 0; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[0], false);

  config.srcAddr = (uint32_t)&transmitBuf[0];
  config.destAddr = (uint32_t)&GPIO_PDOR_REG(PTD_BASE_PTR);
  config.srcOffset = 1; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[1], false);

  config.srcAddr = (uint32_t)&OneValue;
  config.destAddr = (uint32_t)&GPIO_PCOR_REG(PTD_BASE_PTR);
  config.srcOffset = 0; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[2], true);

  /* initialize transfer */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    EDMA_DRV_StartChannel(&chnStates[channel]); /* enable DMA */
  }
  dmaDone = false; /* reset done flag */
  StartStopFTM(FTM0_IDX, true); /* start FTM timer to fire sequence of DMA transfers */
  do {
    /* wait until transfer is complete */
  } while(!dmaDone);
  PrepareFTMforDMAStopped(FTM0_IDX);
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    EDMA_DRV_StopChannel(&chnStates[channel]); /* stop DMA channel */
  }
  /* Release EDMA channel request trough DMAMUX, otherwise events might still be latched! */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    res = EDMA_DRV_ReleaseChannel(&chnStates[channel]);
    if (res!=kStatus_EDMA_Success) { /* check error code */
      for(;;); /* ups!?! */
    }
  }
}

static bool start = true;

void APP_Run(void) {
  GPIO_PCOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Clear Output PTD0 */
  InitFlexTimer(FTM0_IDX);
  InitDMA();
  for(;;) {
    GPIO_DRV_TogglePinOutput(LEDRGB_BLUE);
    OSA_TimeDelay(10);
    if (start) {
      DoDMA(sizeof(transmitBuf));
      //GPIO_PTOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Toggle Output PTD0 */
      //GPIO_PSOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Set Output PTD0 */
      //GPIO_PTOR_REG(PTE_BASE_PTR) = (1<<26); /* toggle PTE26 (GREEN RGB) */
    }
  }
}

#if 0
/*! @brief Dma channel 0 ISR */
void DMA0_IRQHandler(void){
   EDMA_DRV_IRQHandler(0U);
}

/*! @brief Dma channel 1 ISR */
void DMA1_IRQHandler(void){
   EDMA_DRV_IRQHandler(1U);
}
#endif

#if 1
/*! @brief Dma channel 2 ISR */
void DMA2_IRQHandler(void){
   EDMA_DRV_IRQHandler(2U);
}
#endif
