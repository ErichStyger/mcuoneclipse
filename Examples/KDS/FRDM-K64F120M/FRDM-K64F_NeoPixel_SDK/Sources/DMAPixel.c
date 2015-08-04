/**
 * \file
 * \brief WS2812B Driver using DMA.
 * \author Erich Styger
 *
 * This module deals with the low level timer and eDMA to
 * generate the bitstream for multiple WS2812B lanes.
 * \license
 *  This is a free software and is opened for education,  research and commercial developments under license policy of following terms:
 *  This is a free software and there is NO WARRANTY.
 *  No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *  Redistributions of source code must retain the above copyright notice.
 */

#include "DMAPixel.h"
#include <stdint.h>
#include <stdbool.h>
#include "fsl_ftm_driver.h"
#include "fsl_edma_driver.h"
#include "fsl_sim_hal_MK64F12.h"
#include "fsl_mcg_hal.h"
#include "fsl_port_hal.h"
#include <string.h> /* for memset() */

/* FTM related */
#define NOF_FTM_CHANNELS  3 /* using three FTM0 channels, running with 60 MHz system clock */
#define FTM_CH0_TICKS     (0x10)  /* delay until 0xFF */
#define FTM_CH1_TICKS     (0x2A)  /* at 0.4us write data */
#define FTM_CH2_TICKS     (0x40)  /* at 0.8us clear bits  */
#define FTM_PERIOD_TICKS  (0x4B)  /* 1.25 us period */

/* DMA related */
#define NOF_EDMA_CHANNELS  3 /* using three DMA channels */
static edma_chn_state_t chnStates[NOF_EDMA_CHANNELS]; /* array of DMA channel states */
static volatile bool dmaDone = false; /* set by DMA complete interrupt on DMA channel 3 */
static const uint8_t OneValue = 0xFF; /* value to clear or set the port bits */

/* --------------------------------------- */
/* FTM                                     */
/* --------------------------------------- */
static void StartStopFTM(uint32_t instance, bool startIt) {
  FTM_Type *ftmBase = g_ftmBase[instance];

  if (startIt) {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_SystemClk); /* clock timer */
  } else {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None); /* disable clock */
  }
}

static void ResetFTM(uint32_t instance) {
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

static void StopFTMDMA(uint32_t instance) {
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

  /* initialize the driver */
  FTM_DRV_Init(instance, &flexTimer0_InitConfig0); /* initialize the driver with a default configuration */
  FTM_DRV_SetTimeOverflowIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetFaultIntCmd(instance, false); /* disable interrupt */
  FTM_DRV_SetClock(instance, kClock_source_FTM_SystemClk, kFtmDividedBy1); /* use system clock with a divider of 1 */

  /* configure timer */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow */

  /* enable PWM mode for the channels */
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 0);
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 1);
  FTM_HAL_EnablePwmMode(ftmBase, (ftm_pwm_param_t*)&flexTimer0_ChnConfig0, 2);

  /* based on Ref manual, in PWM mode CNTIN is to be set 0*/
  FTM_HAL_SetCounterInitVal(ftmBase, 0);

  /* set the module counters */
  FTM_HAL_SetMod(ftmBase, FTM_PERIOD_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 0, FTM_CH0_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 1, FTM_CH1_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 2, FTM_CH2_TICKS);
}

/* --------------------------------------- */
/* DMA                                     */
/* --------------------------------------- */

/*! @brief Dma channel 2 ISR */
void DMA2_IRQHandler(void){
   EDMA_DRV_IRQHandler(2U);
}

void EDMA_Callback(void *param, edma_chn_status_t chanStatus) {
  dmaDone = true;
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

void DMA_Transfer(uint8_t *transmitBuf, uint32_t nofBytes) {
  edma_transfer_config_t config;
  uint8_t channel;
  uint8_t res;

  ResetFTM(FTM0_IDX); /* clear FTFM and prepare for DMA */

  /* DMA Muxing: Allocate EDMA channel request trough DMAMUX */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    res = EDMA_DRV_RequestChannel(channel, kDmaRequestMux0FTM0Channel0+channel, &chnStates[channel]);
    if (res==kEDMAInvalidChannel) { /* check error code */
      for(;;); /* ups!?! */
    }
  }
  /* Install callback for eDMA handler on last channel which is channel 2 */
  EDMA_DRV_InstallCallback(&chnStates[NOF_EDMA_CHANNELS-1], EDMA_Callback, NULL);

  /* prepare DMA configuration */
  config.srcLastAddrAdjust = 0; /* no address adjustment needed after last transfer */
  config.destLastAddrAdjust = 0; /* no address adjustment needed after last transfer */
  config.srcModulo = kEDMAModuloDisable; /* no address modulo (no ring buffer) */
  config.destModulo = kEDMAModuloDisable; /* no address modulo (no ring buffer) */
  config.srcTransferSize = kEDMATransferSize_1Bytes; /* transmitting one byte in each DMA transfer */
  config.destTransferSize = kEDMATransferSize_1Bytes; /* transmitting one byte in each DMA transfer */
  config.minorLoopCount = 1; /* one byte transmitted for each request */
  config.majorLoopCount = nofBytes; /* total number of bytes to send */
  config.destOffset = 0; /* do not increment destination address */

  config.srcAddr = (uint32_t)&OneValue; /* Bit set */
  config.destAddr = (uint32_t)&GPIO_PSOR_REG(PTD_BASE_PTR); /* Port Set Output register */
  config.srcOffset = 0; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[0], false); /* write configuration to DMA channel 0 */

  config.srcAddr = (uint32_t)transmitBuf; /* pointer to data */
  config.destAddr = (uint32_t)&GPIO_PDOR_REG(PTD_BASE_PTR); /* Port Data Output register */
  config.srcOffset = 1; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[1], false); /* write configuration to DMA channel 1 */

  config.srcAddr = (uint32_t)&OneValue; /* Bit set */
  config.destAddr = (uint32_t)&GPIO_PCOR_REG(PTD_BASE_PTR); /* Port Clear Output register */
  config.srcOffset = 0; /* do not increment source address */
  PushDMADescriptor(&config, &chnStates[2], true); /* write configuration to DMA channel 1 */

  /* enable the DMA channels */
  for (channel=0; channel<NOF_EDMA_CHANNELS; channel++) {
    EDMA_DRV_StartChannel(&chnStates[channel]); /* enable DMA */
  }
  dmaDone = false; /* reset done flag */
  StartStopFTM(FTM0_IDX, true); /* start FTM timer to fire sequence of DMA transfers */
  do {
    /* wait until transfer is complete */
  } while(!dmaDone);
  StopFTMDMA(FTM0_IDX); /* stop FTM DMA tranfers */
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

static void InitDMADriver(void) {
  edma_user_config_t  edmaUserConfig;
  static edma_state_t edmaState;
  uint8_t res, channel;

  /* Initialize eDMA modules. */
  edmaUserConfig.chnArbitration = kEDMAChnArbitrationRoundrobin; /* use round-robin arbitration */
  edmaUserConfig.notHaltOnError = false; /* do not halt in case of errors */
  EDMA_DRV_Init(&edmaState, &edmaUserConfig); /* initialize DMA with configuration */
}

static void InitHardware(void) {
  /* Enable clock for PORTs */
  SIM_HAL_EnableClock(SIM, kSimClockGatePortA);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortB);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortC);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortD);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortE);

  /* Setup board clock source. */
  g_xtal0ClkFreq = 50000000U;           /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  g_xtalRtcClkFreq = 32768U;            /* Value of the external 32k crystal or oscillator clock frequency of the RTC in Hz */
#if 0
  PORT_HAL_SetMuxMode(PORTB, 21UL, kPortMuxAsGpio); /* PTB21, Blue RGB LED */
  PORT_HAL_SetMuxMode(PORTB, 22UL, kPortMuxAsGpio); /* PTB22, Red RGB LED */
  PORT_HAL_SetMuxMode(PORTE, 26UL, kPortMuxAsGpio); /* PTE26, Green RGB LED */
  GPIO_PDDR_REG(PTB_BASE_PTR) |= (1<<21); /* PTB21 as output (blue) */
  GPIO_PDDR_REG(PTB_BASE_PTR) |= (1<<22); /* PTB22 as output (red) */
  GPIO_PDDR_REG(PTE_BASE_PTR) |= (1<<26); /* PTE26 as output (green) */
  /* turn off LED's */
  GPIO_PSOR_REG(PTB_BASE_PTR) = (1<<21); /* Port Set Output PTB21 (Blue LED) */
  GPIO_PSOR_REG(PTB_BASE_PTR) = (1<<22); /* Port Set Output PTB22 (Red LED) */
  GPIO_PSOR_REG(PTE_BASE_PTR) = (1<<26); /* Port Set Output PTE26 (Green LED) */
#endif
  /* Use PTD0 as DIN to the Neopixels: mux it as GPIO and output pin */
  PORT_HAL_SetMuxMode(PORTD, 0UL, kPortMuxAsGpio); /* PTD0: DIN to NeoPixels */
  GPIO_PDDR_REG(PTD_BASE_PTR) |= (1<<0); /* PTD0 as output */

  /* FTM and FTM Muxing */
  InitFlexTimer(FTM0_IDX);
  PORT_HAL_SetMuxMode(PORTC,1UL,kPortMuxAlt4); /* use PTC1 for channel 0 of FTM0 */
  PORT_HAL_SetMuxMode(PORTC,2UL,kPortMuxAlt4); /* use PTC2 for channel 1 of FTM0 */
  PORT_HAL_SetMuxMode(PORTC,3UL,kPortMuxAlt4); /* use PTC3 for channel 2 of FTM0 */

  InitDMADriver(); /* initialize DMA driver */
}

void DMA_Init(void) {
  //uint32_t uFTMhz;

  InitHardware();
//  GPIO_PCOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Clear Output PTD0 */

  ResetFTM(FTM0_IDX);
  StartStopFTM(FTM0_IDX, true); /* start FTM timer */
  //uFTMhz = FTM_DRV_GetClock(FTM0_IDX);

  for(;;) {
  //  GPIO_PCOR_REG(PTB_BASE_PTR) = (1<<21); /* Port Clear Output PTB21 (Blue LED) */
  //  GPIO_PSOR_REG(PTB_BASE_PTR) = (1<<21); /* Port Clear Output PTB21 (Blue LED) */
  }
}
