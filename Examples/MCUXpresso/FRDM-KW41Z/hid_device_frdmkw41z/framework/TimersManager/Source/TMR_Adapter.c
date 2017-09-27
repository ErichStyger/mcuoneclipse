/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file TMR_Adapter.c
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "TMR_Adapter.h"
#include "fsl_device_registers.h"
#include "fsl_os_abstraction.h"
#include "fsl_common.h"
#include "board.h"

#if FSL_FEATURE_SOC_FTM_COUNT
  #include "fsl_ftm.h"
#else
   #include "fsl_tpm.h"
#endif


/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
#if FSL_FEATURE_SOC_FTM_COUNT
static const IRQn_Type mFtmIrqId[] = FTM_IRQS;
static FTM_Type * mFtmBase[] = FTM_BASE_PTRS;
static const ftm_config_t mFtmConfig = {
    .prescale = kFTM_Prescale_Divide_128,
    .bdmMode = kFTM_BdmMode_0,
    .pwmSyncMode = kFTM_SoftwareTrigger,
    .reloadPoints = 0,
    .faultMode = kFTM_Fault_Disable,
    .faultFilterValue = 0,
    .deadTimePrescale = kFTM_Deadtime_Prescale_1,
    .deadTimeValue = 0,
    .extTriggers = 0,
    .chnlInitState = 0,
    .chnlPolarity = 0,
    .useGlobalTimeBase = 0
};

#else
static const IRQn_Type mTpmIrqId[] = TPM_IRQS;
static TPM_Type * mTpmBase[] = TPM_BASE_PTRS;
static const tpm_config_t mTpmConfig = {
    .prescale = kTPM_Prescale_Divide_128,
    .useGlobalTimeBase = 0,
    .enableDoze = 0,
    .enableDebugMode = 0,
    .enableReloadOnTrigger = 0,
    .enableStopOnOverflow = 0,
    .enableStartOnTrigger = 0,
    .triggerSelect = kTPM_Trigger_Select_0
};
#endif


/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
void StackTimer_Init(void (*cb)(void))
{
    IRQn_Type irqId;
#if FSL_FEATURE_SOC_FTM_COUNT
    FTM_Type *ftmBaseAddr = (FTM_Type*)mFtmBase[gStackTimerInstance_c];

    FTM_Init(ftmBaseAddr, &mFtmConfig);
    FTM_StopTimer(ftmBaseAddr);
    ftmBaseAddr->MOD = 0xFFFF;
    /* Configure channel to Software compare; output pin not used */
    FTM_SetupOutputCompare(ftmBaseAddr, (ftm_chnl_t)gStackTimerChannel_c, kFTM_NoOutputSignal, 0x01);

    /* Install ISR */
    irqId = mFtmIrqId[gStackTimerInstance_c];
    FTM_EnableInterrupts(ftmBaseAddr, kFTM_TimeOverflowInterruptEnable |  (1 << gStackTimerChannel_c));
#else
    TPM_Type *tpmBaseAddr = (TPM_Type*)mTpmBase[gStackTimerInstance_c];

    TPM_Init(tpmBaseAddr, &mTpmConfig);
    TPM_StopTimer(tpmBaseAddr);

    /* Set the timer to be in free-running mode */
    tpmBaseAddr->MOD = 0xFFFF;
    /* Configure channel to Software compare; output pin not used */
    TPM_SetupOutputCompare(tpmBaseAddr, (tpm_chnl_t)gStackTimerChannel_c, kTPM_NoOutputSignal, 0x01);
    
    /* Install ISR */
    irqId = mTpmIrqId[gStackTimerInstance_c];
    TPM_EnableInterrupts(tpmBaseAddr, kTPM_TimeOverflowInterruptEnable | (1 << gStackTimerChannel_c));
#endif
    /* Overwrite old ISR */
    OSA_InstallIntHandler(irqId, cb);
    /* set interrupt priority */
    NVIC_SetPriority(irqId, gStackTimer_IsrPrio_c >> (8 - __NVIC_PRIO_BITS));
    NVIC_ClearPendingIRQ(irqId);
    NVIC_EnableIRQ(irqId);
}

/*************************************************************************************/
void StackTimer_Enable(void)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    FTM_StartTimer(mFtmBase[gStackTimerInstance_c], kFTM_SystemClock);
#else
    TPM_StartTimer(mTpmBase[gStackTimerInstance_c], kTPM_SystemClock);
#endif
}

/*************************************************************************************/
void StackTimer_Disable(void)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    FTM_StopTimer(mFtmBase[gStackTimerInstance_c]);
#else
    TPM_StopTimer(mTpmBase[gStackTimerInstance_c]);
#endif
}

/*************************************************************************************/
uint32_t StackTimer_GetInputFrequency(void)
{
    uint32_t prescaller;
    uint32_t refClk;
#if FSL_FEATURE_SOC_FTM_COUNT
    refClk = BOARD_GetFtmClock(gStackTimerInstance_c);
    prescaller = mFtmConfig.prescale;
#else
    refClk = BOARD_GetTpmClock(gStackTimerInstance_c);
    prescaller = mTpmConfig.prescale;
#endif
    return refClk / (1 << prescaller);
}

/*************************************************************************************/
uint32_t StackTimer_GetCounterValue(void)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    return mFtmBase[gStackTimerInstance_c]->CNT;
#else
    return mTpmBase[gStackTimerInstance_c]->CNT;
#endif
}

/*************************************************************************************/
void StackTimer_SetOffsetTicks(uint32_t offset)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    FTM_SetupOutputCompare(mFtmBase[gStackTimerInstance_c], (ftm_chnl_t)gStackTimerChannel_c, kFTM_NoOutputSignal, offset);
#else
    TPM_SetupOutputCompare(mTpmBase[gStackTimerInstance_c], (tpm_chnl_t)gStackTimerChannel_c, kTPM_NoOutputSignal, offset);
#endif
}

/*************************************************************************************/
void StackTimer_ClearIntFlag(void)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    uint32_t status = FTM_GetStatusFlags(mFtmBase[gStackTimerInstance_c]);
    FTM_ClearStatusFlags(mFtmBase[gStackTimerInstance_c], status);
#else
    uint32_t status = TPM_GetStatusFlags(mTpmBase[gStackTimerInstance_c]);
    TPM_ClearStatusFlags(mTpmBase[gStackTimerInstance_c], status);
#endif
}

/*************************************************************************************/
/*                                       PWM                                         */
/*************************************************************************************/
void PWM_Init(uint8_t instance)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    ftm_config_t config;
    FTM_GetDefaultConfig(&config);
    FTM_Init(mFtmBase[instance], &config);
    FTM_StartTimer(mFtmBase[instance], kFTM_SystemClock);
#else
    tpm_config_t config;
    TPM_GetDefaultConfig(&config);
    TPM_Init(mTpmBase[instance], &config);
    TPM_StartTimer(mTpmBase[instance], kTPM_SystemClock);
#endif  
}

/*************************************************************************************/
void PWM_SetChnCountVal(uint8_t instance, uint8_t channel, uint16_t val)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    mFtmBase[instance]->CONTROLS[channel].CnV = val;
#else
    mTpmBase[instance]->CONTROLS[channel].CnV = val;
#endif  
}

/*************************************************************************************/
uint16_t PWM_GetChnCountVal(uint8_t instance, uint8_t channel)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    return mFtmBase[instance]->CONTROLS[channel].CnV;
#else
    return mTpmBase[instance]->CONTROLS[channel].CnV;
#endif
}

/*************************************************************************************/
void PWM_StartEdgeAlignedLowTrue(uint8_t instance, tmr_adapter_pwm_param_t *param, uint8_t channel)
{
#if FSL_FEATURE_SOC_FTM_COUNT
    ftm_chnl_pwm_signal_param_t pwmChannelConfig = {
        .chnlNumber = (ftm_chnl_t)channel,
        .level = kFTM_LowTrue,
        .dutyCyclePercent = param->initValue,
        .firstEdgeDelayPercent = 0
    };
    
    FTM_SetupPwm(mFtmBase[instance], &pwmChannelConfig, 1, kFTM_EdgeAlignedPwm, param->frequency, BOARD_GetFtmClock(instance));
#else
    tpm_chnl_pwm_signal_param_t pwmChannelConfig = {
        .chnlNumber = (tpm_chnl_t)channel,
        .level = kTPM_LowTrue,
        .dutyCyclePercent = param->initValue,
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
        .firstEdgeDelayPercent = 0
#endif
    };
    
    TPM_SetupPwm(mTpmBase[instance], &pwmChannelConfig, 1, kTPM_EdgeAlignedPwm, param->frequency, BOARD_GetTpmClock(instance));
#endif  
}
