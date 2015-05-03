/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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

#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"
#include "fsl_os_abstraction.h"
#include <assert.h>
#if defined(RTC_INSTANCE_COUNT)
extern RTC_Type * const g_rtcBase[RTC_INSTANCE_COUNT];
#include "fsl_rtc_hal.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Macro for clock manager critical section. */
#if (USE_RTOS)
    mutex_t g_clockLock;
    #define CLOCK_SYS_LOCK_INIT()    OSA_MutexCreate(&g_clockLock)
    #define CLOCK_SYS_LOCK()         OSA_MutexLock(&g_clockLock, OSA_WAIT_FOREVER)
    #define CLOCK_SYS_UNLOCK()       OSA_MutexUnlock(&g_clockLock)
    #define CLOCK_SYS_LOCK_DEINIT()  OSA_MutexDestroy(&g_clockLock)
#else
    #define CLOCK_SYS_LOCK_INIT()    do {}while(0)
    #define CLOCK_SYS_LOCK()         do {}while(0)
    #define CLOCK_SYS_UNLOCK()       do {}while(0)
    #define CLOCK_SYS_LOCK_DEINIT()  do {}while(0)
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static clock_manager_state_t g_clockState;

#if FSL_FEATURE_SYSTICK_HAS_EXT_REF
uint32_t CLOCK_SYS_GetSystickFreq(void)
{
    /* Use external reference clock. */
    if (!(SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk))
    {
#if FSL_FEATURE_SYSTICK_EXT_REF_CORE_DIV
        return CLOCK_SYS_GetCoreClockFreq() / FSL_FEATURE_SYSTICK_EXT_REF_CORE_DIV;
#else
        return 0U;
#endif
    }
    else // Use core clock.
    {
        return CLOCK_SYS_GetCoreClockFreq();
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_Init
 * Description   : Install pre-defined clock configurations.
 * This function installs the pre-defined clock configuration table to the
 * clock manager.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_Init(clock_manager_user_config_t const **clockConfigsPtr,
                              uint8_t configsNumber,
                              clock_manager_callback_user_config_t **callbacksPtr,
                              uint8_t callbacksNumber)
{
    assert(NULL != clockConfigsPtr);
    assert(NULL != callbacksPtr);

    CLOCK_SYS_LOCK_INIT();

    g_clockState.configTable     = clockConfigsPtr;
    g_clockState.clockConfigNum  = configsNumber;
    g_clockState.callbackConfig  = callbacksPtr;
    g_clockState.callbackNum     = callbacksNumber;

    /*
     * errorCallbackIndex is the index of the callback which returns error
     * during clock mode switch. If all callbacks return success, then the
     * errorCallbackIndex is callbacksnumber.
     */
    g_clockState.errorCallbackIndex = callbacksNumber;

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_UpdateConfiguration
 * Description   : Send notification and change system clock configuration.
 * This function sends the notification to all callback functions, if all
 * callbacks return OK or forceful policy is used, this function will change
 * system clock configuration.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex,
                                                   clock_manager_policy_t policy)
{
    uint8_t callbackIdx;
    clock_manager_error_code_t ret = kClockManagerSuccess;

    clock_manager_callback_user_config_t* callbackConfig;

    clock_notify_struct_t notifyStruct;
    notifyStruct.targetClockConfigIndex = targetConfigIndex;
    notifyStruct.policy                 = policy;

    /* Clock configuration index is out of range. */
    if (targetConfigIndex >= g_clockState.clockConfigNum)
    {
        return kClockManagerErrorOutOfRange;
    }

    OSA_EnterCritical(kCriticalLockSched);
    /* Set errorcallbackindex as callbackNum, which means no callback error now.*/
    g_clockState.errorCallbackIndex = g_clockState.callbackNum;

    /* First step: Send "BEFORE" notification. */
    notifyStruct.notifyType = kClockManagerNotifyBefore;

    /* Send notification to all callback. */
    for (callbackIdx=0; callbackIdx<g_clockState.callbackNum; callbackIdx++)
    {
        callbackConfig = g_clockState.callbackConfig[callbackIdx];
        if ((NULL != callbackConfig) &&
            ((uint8_t)callbackConfig->callbackType & (uint8_t)kClockManagerNotifyBefore))
        {
            if (kClockManagerSuccess !=
                    (*callbackConfig->callback)(&notifyStruct,
                        callbackConfig->callbackData))
            {
                g_clockState.errorCallbackIndex = callbackIdx;
                /* Save the error callback index. */
                ret = kClockManagerErrorNotificationBefore;

                if (kClockManagerPolicyAgreement == policy)
                {
                    break;
                }
            }
        }
    }

    /* If all callback success or forceful policy is used. */
    if ((kClockManagerSuccess == ret) ||
        (policy == kClockManagerPolicyForcible))
    {
        /* clock mode switch. */
        OSA_EnterCritical(kCriticalDisableInt);
        CLOCK_SYS_SetConfiguration(g_clockState.configTable[targetConfigIndex]);

        g_clockState.curConfigIndex = targetConfigIndex;
        OSA_ExitCritical(kCriticalDisableInt);

        notifyStruct.notifyType = kClockManagerNotifyAfter;

        for (callbackIdx=0; callbackIdx<g_clockState.callbackNum; callbackIdx++)
        {
            callbackConfig = g_clockState.callbackConfig[callbackIdx];
            if ((NULL != callbackConfig) &&
                ((uint8_t)callbackConfig->callbackType & (uint8_t)kClockManagerNotifyAfter))
            {
                if (kClockManagerSuccess !=
                        (*callbackConfig->callback)(&notifyStruct,
                            callbackConfig->callbackData))
                {
                    g_clockState.errorCallbackIndex = callbackIdx;
                    /* Save the error callback index. */
                    ret = kClockManagerErrorNotificationAfter;

                    if (kClockManagerPolicyAgreement == policy)
                    {
                        break;
                    }
                }
            }
        }
    }
    else /* Error occurs, need to send "RECOVER" notification. */
    {
        notifyStruct.notifyType = kClockManagerNotifyRecover;
        while (callbackIdx--)
        {
            callbackConfig = g_clockState.callbackConfig[callbackIdx];
            if (NULL != callbackConfig)
            {
                (*callbackConfig->callback)(&notifyStruct,
                        callbackConfig->callbackData);
            }
        }
    }

    OSA_ExitCritical(kCriticalLockSched);

    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetCurrentConfiguration
 * Description   : Get current clock configuration index.
 *
 *END**************************************************************************/
uint8_t CLOCK_SYS_GetCurrentConfiguration(void)
{
    return g_clockState.curConfigIndex;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetErrorCallback
 * Description   : Get the callback which returns error in last clock switch.
 *
 *END**************************************************************************/
clock_manager_callback_user_config_t* CLOCK_SYS_GetErrorCallback(void)
{
    /* If all callbacks return success. */
    if (g_clockState.errorCallbackIndex >= g_clockState.clockConfigNum)
    {
        return NULL;
    }
    else
    {
        return g_clockState.callbackConfig[g_clockState.errorCallbackIndex];
    }
}

#if (defined(CLOCK_USE_SCG))

#elif (defined(CLOCK_USE_MCG_LITE))
/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_SetMcgliteMode
 * Description  : Set MCG_Lite to some mode.
 * This function transitions the MCG_lite to some mode according to configuration
 * parameter.
 *
 *END***********************************************************************************/
mcglite_mode_error_t CLOCK_SYS_SetMcgliteMode(mcglite_config_t const *targetConfig)
{
    uint32_t outFreq = 0U;
    mcglite_mode_error_t ret = kMcgliteModeErrNone;

    assert(targetConfig->mcglite_mode < kMcgliteModeStop);

    /* MCG_LITE mode change. */
    switch (targetConfig->mcglite_mode)
    {
        case kMcgliteModeLirc8M:
            ret = CLOCK_HAL_SetLircMode(MCG,
                                        kMcgliteLircSel8M,
                                        targetConfig->fcrdiv,
                                        &outFreq);
            break;
        case kMcgliteModeLirc2M:
            ret = CLOCK_HAL_SetLircMode(MCG,
                                        kMcgliteLircSel2M,
                                        targetConfig->fcrdiv,
                                        &outFreq);
            break;
        case kMcgliteModeExt:
            ret = CLOCK_HAL_SetExtMode(MCG, &outFreq);
            break;
        default:
            ret = CLOCK_HAL_SetHircMode(MCG, &outFreq);
            break;
    }

    /* Set other registers. */
    if (kMcgliteModeErrNone == ret)
    {
        /* Enable HIRC when MCG_LITE is not in HIRC mode. */
        CLOCK_HAL_SetHircCmd(MCG, targetConfig->hircEnableInNotHircMode);

        /* Enable IRCLK. */
        CLOCK_HAL_SetLircCmd(MCG, targetConfig->irclkEnable);
        CLOCK_HAL_SetLircStopCmd(MCG, targetConfig->irclkEnableInStop);

        /* Set IRCS. */
        CLOCK_HAL_SetLircSelMode(MCG, targetConfig->ircs);

        /* Set LIRC_DIV2. */
        CLOCK_HAL_SetLircDiv2(MCG, targetConfig->lircDiv2);
    }

    return ret;
}
#else

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_SetMcgPeeToFbe
 * Description  : This function changes MCG from PEE mode to FBE mode, it is
 * only used internally.
 *
 *END***********************************************************************************/
#if FSL_FEATURE_MCG_HAS_PLL
static void CLOCK_SYS_SetMcgPeeToFbe(void)
{
    /* Change to use external clock first. */
    CLOCK_HAL_SetClkOutSrc(MCG, kMcgClkOutSrcExternal);
    /* Wait for clock status bits to update */
    while (CLOCK_HAL_GetClkOutStat(MCG) != kMcgClkOutStatExternal) {}

    /* Set PLLS to select FLL. */
    CLOCK_HAL_SetPllSelectCmd(MCG, false);
    // wait for PLLST status bit to set
    while ((CLOCK_HAL_IsPllSelected(MCG) != false)) {}
}
#endif

/*FUNCTION******************************************************************************
 *
 * Function name : CLOCK_SYS_SetMcgMode
 * Description  : This function sets MCG to some target mode defined by the configure
 * structure, if can not switch to target mode directly, this function will choose
 * the proper path. If external clock is used in the target mode, please make sure
 * it is enabled, for example, if the external oscillator is used, please setup EREFS/HGO
 * correctly and make sure OSCINIT is set.
 * This function is used by clock dynamic setting, it only supports some specific
 * mode transitions, including:
 * 1. FEI      ==>    FEE/PEE
 * 2. BLPI    <==>    FEE/PEE
 * 3. Reconfigure PLL in PEE mode.
 * 4. Reconfigure FLL in FEE mode.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_SetMcgMode(mcg_config_t const *targetConfig,
                                      void (* fllStableDelay)(void))
{
    uint32_t outClkFreq;
#if FSL_FEATURE_MCG_HAS_PLL
    /* Current mode is only used for PEE mode transition. */
    mcg_modes_t curMode;  // Current MCG mode.
#endif

#if FSL_FEATURE_MCG_USE_OSCSEL
    mcg_oscsel_select_t oscsel = targetConfig->oscsel;
#else
    mcg_oscsel_select_t oscsel = kMcgOscselOsc;
#endif

#if FSL_FEATURE_MCG_HAS_PLL
#if (FSL_FEATURE_MCG_HAS_PLL1 || FSL_FEATURE_MCG_HAS_EXTERNAL_PLL)
    mcg_pll_clk_select_t pllcs = targetConfig->pllcs;
#else
    mcg_pll_clk_select_t pllcs = kMcgPllClkSelPll0;
#endif
#endif

#if FSL_FEATURE_MCG_HAS_PLL
    curMode = CLOCK_HAL_GetMcgMode(MCG);
#endif

    if (kMcgModeBLPI == targetConfig->mcg_mode)
    {
#if FSL_FEATURE_MCG_HAS_PLL
        // If current mode is PEE mode, swith to FBE mode first.
        if (kMcgModePEE == curMode)
        {
            CLOCK_SYS_SetMcgPeeToFbe();
        }
#endif
        // Change to FBI mode.
        CLOCK_HAL_SetFbiMode(MCG,
                             targetConfig->drs,
                             targetConfig->ircs,
                             targetConfig->fcrdiv,
                             fllStableDelay,
                             &outClkFreq);

        // Enable low power mode to enter BLPI.
        CLOCK_HAL_SetLowPowerModeCmd(MCG, true);
    }
    else if (kMcgModeFEE == targetConfig->mcg_mode)
    {
#if FSL_FEATURE_MCG_HAS_PLL
        // If current mode is PEE mode, swith to FBE mode first.
        if (kMcgModePEE == curMode)
        {
            CLOCK_SYS_SetMcgPeeToFbe();
        }
#endif
        // Disalbe low power mode.
        CLOCK_HAL_SetLowPowerModeCmd(MCG, false);
        // Configure FLL in FBE mode then switch to FEE mode.
        CLOCK_HAL_SetFbeMode(MCG,
                             oscsel,
                             targetConfig->frdiv,
                             targetConfig->dmx32,
                             targetConfig->drs,
                             fllStableDelay,
                             &outClkFreq);
        // Change CLKS to enter FEE mode.
        CLOCK_HAL_SetClkOutSrc(MCG, kMcgClkOutSrcOut);
        while (CLOCK_HAL_GetClkOutStat(MCG) != kMcgClkOutStatFll) {}
    }
#if FSL_FEATURE_MCG_HAS_PLL
    else if (kMcgModePEE == targetConfig->mcg_mode)
    {
        /*
         * If current mode is FEI/FEE/BLPI, then switch to FBE mode first.
         * If current mode is PEE mode, which means need to reconfigure PLL,
         * fist switch to PBE mode and configure PLL, then switch to PEE.
         */

        if (kMcgModePEE != curMode)
        {
            // Disalbe low power mode.
            CLOCK_HAL_SetLowPowerModeCmd(MCG, false);

            // Change to FBE mode.
            CLOCK_HAL_SetFbeMode(MCG,
                                 oscsel,
                                 targetConfig->frdiv,
                                 targetConfig->dmx32,
                                 targetConfig->drs,
                                 fllStableDelay,
                                 &outClkFreq);
        }

        // Change to PBE mode.
        CLOCK_HAL_SetPbeMode(MCG,
                             oscsel,
                             pllcs,
                             targetConfig->prdiv0,
                             targetConfig->vdiv0,
                             &outClkFreq);

        // Set CLKS to enter PEE mode.
        CLOCK_HAL_SetClkOutSrc(MCG, kMcgClkOutSrcOut);
        while (CLOCK_HAL_GetClkOutStat(MCG) != kMcgClkOutStatPll) {}
    }
#endif
    else
    {
        return kMcgModeErrModeUnreachable;
    }

    /* Enable MCGIRCLK. */
    CLOCK_HAL_SetInternalRefClkEnableCmd(MCG, targetConfig->irclkEnable);
    CLOCK_HAL_SetInternalRefClkEnableInStopCmd(MCG, targetConfig->irclkEnableInStop);

    /* Configure MCGIRCLK. */
    if (targetConfig->irclkEnable)
    {
        if (kMcgIrcFast == targetConfig->ircs)
        {
            /* Update FCRDIV if necessary. */
            CLOCK_HAL_UpdateFastClkInternalRefDiv(MCG, targetConfig->fcrdiv);
        }

        CLOCK_HAL_SetInternalRefClkMode(MCG, targetConfig->ircs);
        while (targetConfig->ircs != CLOCK_HAL_GetInternalRefClkMode(MCG)) {}
    }

#if FSL_FEATURE_MCG_HAS_PLL
    /* Enable PLL0. */
    if (targetConfig->pll0EnableInFllMode)
    {
        CLOCK_HAL_EnablePll0InFllMode(MCG,
                                      targetConfig->prdiv0,
                                      targetConfig->vdiv0,
                                      targetConfig->pll0EnableInStop);
    }
    else
    {
        CLOCK_HAL_SetPll0EnableCmd(MCG, false);
    }
#endif

    return kMcgModeErrNone;
}

#endif

#if (defined(CLOCK_USE_SCG))  // USE SCG

#else

#if (defined(CLOCK_USE_MCG_LITE)) // USE MCG_LITE

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscInit
 * Description   : Initialize OSC.
 *
 * This function initializes OSC according to configuration.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_OscInit(uint32_t instance,
                                             osc_user_config_t *config)
{
    assert(instance < OSC_INSTANCE_COUNT);
    uint32_t capacitorMask = 0U;

    if (kOscSrcOsc == config->erefs) /* oscillator is used. */
    {
        capacitorMask = (config->enableCapacitor2p   ? kOscCapacitor2p   : 0U) |
                        (config->enableCapacitor4p   ? kOscCapacitor4p   : 0U) |
                        (config->enableCapacitor8p   ? kOscCapacitor8p   : 0U) |
                        (config->enableCapacitor16p  ? kOscCapacitor16p  : 0U);
        OSC_HAL_SetCapacitor(g_oscBase[instance], capacitorMask);
    }

#if FSL_FEATURE_MCGLITE_HAS_RANGE0
    CLOCK_HAL_SetRange0Mode(MCG, config->range);
#endif
#if FSL_FEATURE_MCGLITE_HAS_HGO0
    CLOCK_HAL_SetHighGainOsc0Mode(MCG, config->hgo);
#endif
    CLOCK_HAL_SetExtRefSelMode0(MCG, config->erefs);

    CLOCK_SYS_SetOscerConfigration(instance, &(config->oscerConfig));

    /* oscillator is used. */
    if ((kOscSrcOsc == config->erefs) &&
        (true == config->oscerConfig.enable))
    {
        while(!CLOCK_HAL_IsOscStable(MCG)){}
    }

    g_xtal0ClkFreq = config->freq;

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscDeinit
 * Description   : Deinitialize OSC.
 *
 *END**************************************************************************/
void CLOCK_SYS_OscDeinit(uint32_t instance)
{
    assert(instance < OSC_INSTANCE_COUNT);

    OSC_HAL_SetExternalRefClkInStopModeCmd(g_oscBase[instance], false);
    OSC_HAL_SetExternalRefClkCmd(g_oscBase[instance], false);
    CLOCK_HAL_SetExtRefSelMode0(MCG, kOscSrcExt);
#if FSL_FEATURE_MCGLITE_HAS_RANGE0
    CLOCK_HAL_SetRange0Mode(MCG, kOscRangeLow);
#endif
#if FSL_FEATURE_MCGLITE_HAS_HGO0
    CLOCK_HAL_SetHighGainOsc0Mode(MCG, kOscGainLow);
#endif

    g_xtal0ClkFreq = 0U;
}

#else // Use MCG

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscInit
 * Description   : Initialize OSC.
 *
 * This function initializes OSC according to configuration.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_OscInit(uint32_t instance,
                                             osc_user_config_t *config)
{
    assert(instance < OSC_INSTANCE_COUNT);
    uint32_t capacitorMask = 0U;

    if (kOscSrcOsc == config->erefs) /* oscillator is used. */
    {
        capacitorMask = (config->enableCapacitor2p   ? kOscCapacitor2p   : 0U) |
                        (config->enableCapacitor4p   ? kOscCapacitor4p   : 0U) |
                        (config->enableCapacitor8p   ? kOscCapacitor8p   : 0U) |
                        (config->enableCapacitor16p  ? kOscCapacitor16p  : 0U);
        OSC_HAL_SetCapacitor(g_oscBase[instance], capacitorMask);
    }

    CLOCK_SYS_SetOscerConfigration(instance, &(config->oscerConfig));

#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    if (0U == instance)
    {
#endif
        CLOCK_HAL_SetOsc0Mode(MCG, config->range, config->hgo, config->erefs);

        /* oscillator is used. */
        if ((kOscSrcOsc == config->erefs) &&
            (true == config->oscerConfig.enable))
        {
            while(!CLOCK_HAL_IsOsc0Stable(MCG)){}
        }
        g_xtal0ClkFreq = config->freq;
#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    }
    else
    {
        CLOCK_HAL_SetOsc1Mode(MCG, config->range, config->hgo, config->erefs);

        /* oscillator is used. */
        if ((kOscSrcOsc == config->erefs) &&
            (true == config->oscerConfig.enable))
        {
            while(!CLOCK_HAL_IsOsc1Stable(MCG)){}
        }
        g_xtal1ClkFreq = config->freq;
    }
#endif

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscDeinit
 * Description   : Deinitialize OSC.
 *
 *END**************************************************************************/
void CLOCK_SYS_OscDeinit(uint32_t instance)
{
    assert(instance < OSC_INSTANCE_COUNT);
    OSC_HAL_SetExternalRefClkInStopModeCmd(g_oscBase[instance], false);
    OSC_HAL_SetExternalRefClkCmd(g_oscBase[instance], false);

#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    if (0U == instance)
    {
#endif
        CLOCK_HAL_SetOsc0Mode(MCG,
                              kOscRangeLow,
                              kOscGainLow,
                              kOscSrcExt);
        g_xtal0ClkFreq = 0U;
#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    }
    else
    {
        CLOCK_HAL_SetOsc1Mode(MCG,
                              kOscRangeLow,
                              kOscGainLow,
                              kOscSrcExt);
        g_xtal1ClkFreq = 0U;
    }
#endif
}

#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetOscerConfigration
 * Description   : This funtion sets the OSCERCLK for clock transition.
 *
 *END**************************************************************************/
void CLOCK_SYS_SetOscerConfigration(uint32_t instance, oscer_config_t const *config)
{
#if FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER
    OSC_HAL_SetExternalRefClkDiv(g_oscBase[instance],
                                 config->erclkDiv);
#endif

    OSC_HAL_SetExternalRefClkCmd(g_oscBase[instance],
                                 config->enable);

    OSC_HAL_SetExternalRefClkInStopModeCmd(g_oscBase[instance],
                                           config->enableInStop);
}
#endif

#if defined(RTC_INSTANCE_COUNT)
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_RtcOscInit
 * Description   : This funtion initializes the RTC OSC.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_RtcOscInit(uint32_t instance,
                                                rtc_osc_user_config_t *config)
{
    assert(instance < RTC_INSTANCE_COUNT);
    RTC_Type * rtcBase = g_rtcBase[instance];

    CLOCK_SYS_EnableRtcClock(instance);
    g_xtalRtcClkFreq = config->freq;

    // If the oscillator is not enabled and should be enabled.
    if ((!RTC_HAL_IsOscillatorEnabled(rtcBase)) && (config->enableOsc))
    {
        RTC_HAL_SetOsc2pfLoadCmd(rtcBase, config->enableCapacitor2p);
        RTC_HAL_SetOsc4pfLoadCmd(rtcBase, config->enableCapacitor4p);
        RTC_HAL_SetOsc8pfLoadCmd(rtcBase, config->enableCapacitor8p);
        RTC_HAL_SetOsc16pfLoadCmd(rtcBase, config->enableCapacitor16p);
    }
    RTC_HAL_SetOscillatorCmd(rtcBase, config->enableOsc);
    RTC_HAL_SetClockOutCmd(rtcBase, config->enableClockOutput);

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_RtcOscDeinit
 * Description   : This funtion de-initializes the RTC OSC.
 *
 *END**************************************************************************/
void CLOCK_SYS_RtcOscDeinit(uint32_t instance)
{
    assert(instance < RTC_INSTANCE_COUNT);
    RTC_Type * rtcBase = g_rtcBase[instance];

    RTC_HAL_SetOscillatorCmd(rtcBase, false);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

