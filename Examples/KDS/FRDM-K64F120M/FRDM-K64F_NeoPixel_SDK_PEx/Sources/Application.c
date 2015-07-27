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
  FTM_DRV_PwmStart(instance, (ftm_pwm_param_t*)&flexTimer1_ChnConfig0, 0U);
  /* stop clock, so we can init second channel */
  FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);
  FTM_DRV_PwmStart(instance, (ftm_pwm_param_t*)&flexTimer1_ChnConfig1, 1U);
  /* stop it again */
  FTM_HAL_SetClockSource(ftmBase, kClock_source_FTM_None);

  FTM_DRV_SetTimeOverflowIntCmd(instance,false);
  FTM_DRV_SetFaultIntCmd(instance,false);
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

static bool start = false;

void APP_Run(void) {
  InitFlexTimer(FTM0_IDX);
  for(;;) {
    GPIO_DRV_TogglePinOutput(LEDRGB_BLUE);
    OSA_TimeDelay(1000);
    if (start) {
      StartTransfer(FTM0_IDX);
    }
  }
}
