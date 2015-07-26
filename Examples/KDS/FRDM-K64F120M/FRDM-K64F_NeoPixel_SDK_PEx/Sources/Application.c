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
#if 0
static const ftm_pwm_param_t flexTimer1_ChnConfig0 = {
  .mode = kFtmEdgeAlignedPWM,
  .edgeMode = kFtmHighTrue,
  .uFrequencyHZ = 1000U,
  .uDutyCyclePercent = 50U,
  .uFirstEdgeDelayPercent = 0U,
};

static const ftm_pwm_param_t flexTimer1_ChnConfig1 = {
  .mode = kFtmEdgeAlignedPWM,
  .edgeMode = kFtmHighTrue,
  .uFrequencyHZ = 1000U,
  .uDutyCyclePercent = 25U,
  .uFirstEdgeDelayPercent = 0U,
};

static const ftm_user_config_t flexTimer1_InitConfig0 = {
  .tofFrequency      = 0U,
  .isWriteProtection = false,
  .BDMMode           = kFtmBdmMode_00,
  .syncMethod        = (uint32_t)(kFtmUseSoftwareTrig | kFtmUseHardwareTrig0 | kFtmUseHardwareTrig1 | kFtmUseHardwareTrig2)
};

#define FSL_FLEXTIMER1 FTM0_IDX

static void InitFlexTimer(void) {
  /*! flexTimer1 Auto initialization start */
  FTM_DRV_Init(FSL_FLEXTIMER1,&flexTimer1_InitConfig0);
  FTM_DRV_SetClock(FSL_FLEXTIMER1, kClock_source_FTM_SystemClk, kFtmDividedBy1);
  FTM_DRV_PwmStart(FSL_FLEXTIMER1, (ftm_pwm_param_t*)&flexTimer1_ChnConfig0, 0U);
  //CLOCK_SYS_DisableFtmClock(FSL_FLEXTIMER1);
  //FTM_DRV_PwmStart(FSL_FLEXTIMER1, (ftm_pwm_param_t*)&flexTimer1_ChnConfig1, 1U);
  FTM_DRV_SetTimeOverflowIntCmd(FSL_FLEXTIMER1,false);
  FTM_DRV_SetFaultIntCmd(FSL_FLEXTIMER1,false);
  /*! flexTimer1 Auto initialization end */
}
#endif
static bool init = false;

void APP_Run(void) {
  if (init) {
   // InitFlexTimer();
  }
  for(;;) {
    GPIO_DRV_TogglePinOutput(LEDRGB_BLUE);
    OSA_TimeDelay(1000);
  }
}
