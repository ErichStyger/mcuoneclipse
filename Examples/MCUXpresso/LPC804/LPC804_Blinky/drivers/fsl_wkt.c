/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wkt.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.wkt"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Gets the instance from the base address
 *
 * @param base WKT peripheral base address
 *
 * @return The WKT instance
 */
static uint32_t WKT_GetInstance(WKT_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to WKT bases for each instance. */
static WKT_Type *const s_wktBases[] = WKT_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to WKT clocks for each instance. */
static const clock_ip_name_t s_wktClocks[] = WKT_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
/*! @brief Pointers to WKT resets for each instance. */
static const reset_ip_name_t s_wktResets[] = WKT_RSTS_N;
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t WKT_GetInstance(WKT_Type *base)
{
    uint32_t instance;
    uint32_t wktArrayCount = (sizeof(s_wktBases) / sizeof(s_wktBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < wktArrayCount; instance++)
    {
        if (s_wktBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < wktArrayCount);

    return instance;
}

/*!
 * brief Ungates the WKT clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the WKT driver.
 *
 * param base   WKT peripheral base address
 * param config Pointer to user's WKT config structure.
 */
void WKT_Init(WKT_Type *base, const wkt_config_t *config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the WKT peripheral clock */
    CLOCK_EnableClock(s_wktClocks[WKT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(s_wktResets[WKT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

    /* Clear wake-up or alarm timer flag */
    WKT_ClearStatusFlags(WKT, (uint32_t)kWKT_AlarmFlag);

#if defined(FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK) && FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK
    if (config->clockSource == kWKT_ExternalClockSource)
    {
        /* Select external clock source */
        base->CTRL |= WKT_CTRL_SEL_EXTCLK_MASK;
    }
    else
    {
#endif /* FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK */
        base->CTRL &= ~(
#if defined(FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK) && FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK
            WKT_CTRL_SEL_EXTCLK_MASK |
#endif /* FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK */
            WKT_CTRL_CLKSEL_MASK);
        /* Select divided FRO clock or Low power clock */
        base->CTRL |= WKT_CTRL_CLKSEL(config->clockSource);
#if defined(FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK) && FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK
    }
#endif /* FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK */
}

/*!
 * brief Gate the WKT clock
 *
 * param base WKT peripheral base address
 */
void WKT_Deinit(WKT_Type *base)
{
    /* Stop the timer */
    WKT_StopTimer(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the module clock */
    CLOCK_DisableClock(kCLOCK_Wkt);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
