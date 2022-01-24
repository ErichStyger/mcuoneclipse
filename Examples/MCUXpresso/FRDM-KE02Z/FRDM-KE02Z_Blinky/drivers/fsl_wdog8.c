/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wdog8.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.wdog8"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Clears the WDOG8 flag.
 *
 * This function clears the WDOG8 status flag.
 *
 * Example to clear an interrupt flag:
 * code
 *   WDOG8_ClearStatusFlags(wdog_base,kWDOG8_InterruptFlag);
 * endcode
 * param base        WDOG8 peripheral base address.
 * param mask        The status flags to clear.
 *                    The parameter can be any combination of the following values:
 *                    arg kWDOG8_InterruptFlag
 */
void WDOG8_ClearStatusFlags(WDOG_Type *base, uint8_t mask)
{
    if (0U != (mask & (uint8_t)kWDOG8_InterruptFlag))
    {
        base->CS2 |= WDOG_CS2_FLG_MASK;
    }
}

/*!
 * brief Initializes the WDOG8 configuration structure.
 *
 * This function initializes the WDOG8 configuration structure to default values. The default
 * values are:
 * code
 *   wdog8Config->enableWdog8 = true;
 *   wdog8Config->clockSource = kWDOG8_ClockSource1;
 *   wdog8Config->prescaler = kWDOG8_ClockPrescalerDivide1;
 *   wdog8Config->workMode.enableWait = true;
 *   wdog8Config->workMode.enableStop = false;
 *   wdog8Config->workMode.enableDebug = false;
 *   wdog8Config->testMode = kWDOG8_TestModeDisabled;
 *   wdog8Config->enableUpdate = true;
 *   wdog8Config->enableInterrupt = false;
 *   wdog8Config->enableWindowMode = false;
 *   wdog8Config->windowValue = 0U;
 *   wdog8Config->timeoutValue = 0xFFFFU;
 * endcode
 *
 * param config Pointer to the WDOG8 configuration structure.
 * see wdog8_config_t
 */
void WDOG8_GetDefaultConfig(wdog8_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableWdog8          = true;
    config->clockSource          = kWDOG8_ClockSource1;
    config->prescaler            = kWDOG8_ClockPrescalerDivide1;
    config->workMode.enableWait  = true;
    config->workMode.enableStop  = false;
    config->workMode.enableDebug = false;
    config->testMode             = kWDOG8_TestModeDisabled;
    config->enableUpdate         = true;
    config->enableInterrupt      = false;
    config->enableWindowMode     = false;
    config->windowValue          = 0U;
    config->timeoutValue         = 0xFFFFU;
}

/*!
 * brief Initializes the WDOG8 module.
 *
 * This function initializes the WDOG8.
 * To reconfigure the WDOG8 without forcing a reset first, enableUpdate must be set to true
 * in the configuration.
 *
 * Example:
 * code
 *   wdog8_config_t config;
 *   WDOG8_GetDefaultConfig(&config);
 *   config.timeoutValue = 0x7ffU;
 *   config.enableUpdate = true;
 *   WDOG8_Init(wdog_base,&config);
 * endcode
 *
 * param base   WDOG8 peripheral base address.
 * param config The configuration of the WDOG8.
 */
void WDOG8_Init(WDOG_Type *base, const wdog8_config_t *config)
{
    assert(NULL != config);

    uint8_t value1        = 0U;
    uint8_t value2        = 0U;
    uint32_t primaskValue = 0U;

    value1 = WDOG_CS1_EN(config->enableWdog8) | WDOG_CS1_INT(config->enableInterrupt) |
             WDOG_CS1_UPDATE(config->enableUpdate) | WDOG_CS1_DBG(config->workMode.enableDebug) |
             WDOG_CS1_STOP(config->workMode.enableStop) | WDOG_CS1_WAIT(config->workMode.enableWait) |
             WDOG_CS1_TST(config->testMode);
    value2 =
        WDOG_CS2_CLK(config->clockSource) | WDOG_CS2_WIN(config->enableWindowMode) | WDOG_CS2_PRES(config->prescaler);

    /* Disable the global interrupts. Otherwise, an interrupt could effectively invalidate the unlock sequence
     * and the WCT may expire. After the configuration finishes, re-enable the global interrupts. */
    primaskValue = DisableGlobalIRQ();
    WDOG8_Unlock(base);
    WDOG8_SetWindowValue(base, config->windowValue);
    WDOG8_SetTimeoutValue(base, config->timeoutValue);
    base->CS1 = value1;
    base->CS2 = value2;
    EnableGlobalIRQ(primaskValue);
}

/*!
 * brief De-initializes the WDOG8 module.
 *
 * This function shuts down the WDOG8.
 * Ensure that the WDOG_CS1.UPDATE is 1, which means that the register update is enabled.
 *
 * param base   WDOG8 peripheral base address.
 */
void WDOG8_Deinit(WDOG_Type *base)
{
    uint32_t primaskValue = 0U;

    /* Disable the global interrupts */
    primaskValue = DisableGlobalIRQ();
    WDOG8_Unlock(base);
    WDOG8_Disable(base);
    EnableGlobalIRQ(primaskValue);
}
