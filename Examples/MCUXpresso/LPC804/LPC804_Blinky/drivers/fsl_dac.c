/*
 * Copyright 2017-2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dac.h"
#include "fsl_clock.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_dac"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of GPIO peripheral base address. */
static DAC_Type *const s_dacBases[] = DAC_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of GPIO clock name. */
static const clock_ip_name_t s_dacClocks[] = DAC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_DAC_HAS_NO_RESET) && FSL_FEATURE_DAC_HAS_NO_RESET)
static const reset_ip_name_t s_dacResets[] = DAC_RSTS_N;
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Gets the DAC instance according to the DAC base.
 *
 * @param base DAC peripheral base pointer.
 * @retval DAC instance.
 */
static uint32_t DAC_GetInstance(DAC_Type *base);

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t DAC_GetInstance(DAC_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dacBases); instance++)
    {
        if (s_dacBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dacBases));

    return instance;
}

/*!
 * brief Initialize the DAC module.
 *
 * param base DAC peripheral base address.
 * param config The pointer to configuration structure. Please refer to "dac_config_t" structure.
 */
void DAC_Init(DAC_Type *base, const dac_config_t *config)
{
    assert(config != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable clock. */
    CLOCK_EnableClock(s_dacClocks[DAC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_DAC_HAS_NO_RESET) && FSL_FEATURE_DAC_HAS_NO_RESET)
    /* Reset the DAC module */
    RESET_PeripheralReset(s_dacResets[DAC_GetInstance(base)]);
#endif

    base->CR &= ~DAC_CR_BIAS_MASK;
    base->CR |= DAC_CR_BIAS(config->settlingTime);
}

/*!
 * brief De-Initialize the DAC module.
 *
 * param base DAC peripheral base address.
 */
void DAC_Deinit(DAC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_dacClocks[DAC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Initializes the DAC user configuration structure.
 *
 * This function initializes the user configuration structure to a default value. The default values are as follows.
 * code
 *   config->settlingTime = kDAC_SettlingTimeIs1us;
 * endcode
 * param config Pointer to the configuration structure. See "dac_config_t".
 */
void DAC_GetDefaultConfig(dac_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->settlingTime = kDAC_SettlingTimeIs1us;
}

/*!
 * brief Enable/Diable double-buffering feature. Notice: Disabling the double-buffering feature will disable counter
 * opreation.
 *        If double-buffering feature is disabled, any writes to the CR address will go directly to the CR register.
 *        If double-buffering feature is enabled, any write to the CR register will only load the pre-buffer,
 *        which shares its register address with the CR register. The CR itself will be loaded from the pre-buffer
 *        whenever the counter reaches zero and the DMA request is set.
 *
 * param base DAC peripheral base address.
 * param enable Enable or disable the feature.
 */
void DAC_EnableDoubleBuffering(DAC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= DAC_CTRL_DBLBUF_ENA_MASK;
        base->CTRL |= DAC_CTRL_CNT_ENA_MASK;
    }
    else
    {
        base->CTRL &= ~DAC_CTRL_DBLBUF_ENA_MASK;
        base->CTRL &= ~DAC_CTRL_CNT_ENA_MASK;
    }
}

/*!
 * brief Write DAC output value into CR register or pre-buffer. The DAC output voltage is VALUE*((VREFP)/1024).
 *
 * param base DAC peripheral base address.
 * param value Setting the value for items in the buffer. 10-bits are available.
 */
void DAC_SetBufferValue(DAC_Type *base, uint32_t value)
{
    assert(value < 1024U);

    base->CR = (base->CR & ~DAC_CR_VALUE_MASK) | DAC_CR_VALUE(value);
}

/*!
 * brief Write DAC counter value into CNTVAL register.
 *        When the counter is enabled bit, the 16-bit counter will begin counting down, at the rate selected by PCLK,
 *        from the value programmed into the DACCNTVAL register. The counter is decremented Each time the counter
 * reaches zero, the counter will be reloaded by the value of DACCNTVAL and the DMA request bit INT_DMA_REQ will be set
 * in hardware.
 *
 * param base DAC peripheral basic address.
 * param value Setting the value for items in the counter. 16-bits are available.
 */
void DAC_SetCounterValue(DAC_Type *base, uint32_t value)
{
    assert(value < 65536U);

    base->CNTVAL &= ~DAC_CNTVAL_VALUE_MASK;
    base->CNTVAL |= DAC_CNTVAL_VALUE(value);
}
