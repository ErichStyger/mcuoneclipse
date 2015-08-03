/*
 * DMAPixel.c
 *
 *  Created on: 03.08.2015
 *      Author: tastyger
 */
#include "DMAPixel.h"
#include <stdint.h>
#include <stdbool.h>
#include "fsl_ftm_driver.h"
#include "fsl_edma_driver.h"
#include "fsl_sim_hal_MK64F12.h"
#include "fsl_mcg_hal.h"
#include "fsl_port_hal.h"

/* FTM related */
#define NOF_FTM_CHANNELS  3 /* using three FTM0 channels */
#define FTM_CH0_TICKS     (0x10)  /* delay until 0xFF */
#define FTM_CH1_TICKS     (0x2A)  /* at 0.4us write data */
#define FTM_CH2_TICKS     (0x40)  /* at 0.8us clear bits  */
#define FTM_PERIOD_TICKS  (0x4B)  /* 1.25 us period */

static void StartStopFTM(uint32_t instance, bool startIt) {
  FTM_Type *ftmBase = g_ftmBase[instance];

  if (startIt) {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_SystemClk); /* clock timer */
  } else {
    FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None); /* disable clock */
  }
}

static void PrepareFTMforDMAStart(uint32_t instance) {
  FTM_Type *ftmBase = g_ftmBase[instance];
  uint8_t channel;

  /* reset all values */
  FTM_HAL_SetCounter(ftmBase, 0); /* reset FTM counter */
  FTM_HAL_ClearTimerOverflow(ftmBase); /* clear timer overflow flag (if any) */
  for(channel=0; channel<NOF_FTM_CHANNELS; channel++) {
    FTM_HAL_ClearChnEventFlag(ftmBase, channel); /* clear channel flag */
#if 1
    //FTM_HAL_SetChnDmaCmd(ftmBase, channel, false); /* disable DMA request */
    //FTM_HAL_DisableChnInt(ftmBase, channel); /* enable channel interrupt: need to have both DMA and CHnIE set for DMA transfers! See RM 40.4.23 */
#else
    FTM_HAL_SetChnDmaCmd(ftmBase, channel, true); /* enable DMA request */
    FTM_HAL_EnableChnInt(ftmBase, channel); /* enable channel interrupt: need to have both DMA and CHnIE set for DMA transfers! See RM 40.4.23 */
#endif
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
  FTM_HAL_SetMod(ftmBase, FTM_PERIOD_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 0, FTM_CH0_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 1, FTM_CH1_TICKS);
  FTM_HAL_SetChnCountVal(ftmBase, 2, FTM_CH2_TICKS);
}

void hardware_init(void) {
  /* Enable clock for PORTs */
  SIM_HAL_EnableClock(SIM, kSimClockGatePortA);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortB);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortC);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortD);
  SIM_HAL_EnableClock(SIM, kSimClockGatePortE);

  /* Setup board clock source. */
  g_xtal0ClkFreq = 50000000U;           /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  g_xtalRtcClkFreq = 32768U;            /* Value of the external 32k crystal or oscillator clock frequency of the RTC in Hz */

  PORT_HAL_SetMuxMode(PORTB,21UL,kPortMuxAsGpio); /* PTB21, Blue RGB LED */
  PORT_HAL_SetMuxMode(PORTB,22UL,kPortMuxAsGpio); /* PTB22, Red RGB LED */
  PORT_HAL_SetMuxMode(PORTE,26UL,kPortMuxAsGpio); /* PTE26, Green RGB LED */
  GPIO_PDDR_REG(PTB_BASE_PTR) |= (1<<21); /* PTB21 as output (blue) */
  GPIO_PDDR_REG(PTB_BASE_PTR) |= (1<<22); /* PTB22 as output (red) */
  GPIO_PDDR_REG(PTE_BASE_PTR) |= (1<<26); /* PTE26 as output (green) */
  /* turn off LED's */
  GPIO_PSOR_REG(PTB_BASE_PTR) = (1<<21); /* Port Set Output PTB21 (Blue LED) */
  GPIO_PSOR_REG(PTB_BASE_PTR) = (1<<22); /* Port Set Output PTB22 (Red LED) */
  GPIO_PSOR_REG(PTE_BASE_PTR) = (1<<26); /* Port Set Output PTE26 (Green LED) */

  PORT_HAL_SetMuxMode(PORTD,0UL,kPortMuxAsGpio); /* PTD0: DIN to NeoPixels */
  GPIO_PDDR_REG(PTD_BASE_PTR) |= (1<<0); /* PTD0 as output */

  /* FTM Muxing */
  PORT_HAL_SetMuxMode(PORTC,1UL,kPortMuxAlt4); /* use PTC1 for channel 0 of FTM0 */
  PORT_HAL_SetMuxMode(PORTC,2UL,kPortMuxAlt4); /* use PTC1 for channel 1 of FTM0 */
  PORT_HAL_SetMuxMode(PORTC,3UL,kPortMuxAlt4); /* use PTC1 for channel 2 of FTM0 */
}

void DMA_Init(void) {
  uint32_t uFTMhz;

  hardware_init();
  //OSA_Init();
  InitFlexTimer(FTM0_IDX);
  GPIO_PCOR_REG(PTD_BASE_PTR) = (1<<0); /* Port Clear Output PTD0 */

  PrepareFTMforDMAStart(FTM0_IDX);
  StartStopFTM(FTM0_IDX, true); /* start FTM timer */
  uFTMhz = FTM_DRV_GetClock(FTM0_IDX);

  for(;;) {
    GPIO_PCOR_REG(PTB_BASE_PTR) = (1<<21); /* Port Clear Output PTB21 (Blue LED) */
    GPIO_PSOR_REG(PTB_BASE_PTR) = (1<<21); /* Port Clear Output PTB21 (Blue LED) */
  }
}
