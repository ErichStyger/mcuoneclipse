/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_capt.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.capt"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the CAPT instance from the peripheral base address.
 *
 * @param base CAPT peripheral base address.
 * @return CAPT instance.
 */
static uint32_t CAPT_GetInstance(CAPT_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of CAPT peripheral base address. */
static CAPT_Type *const s_captBases[] = CAPT_BASE_PTRS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name of CAPT. */
static const clock_ip_name_t s_captClock[] = CAPT_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_CAPT_HAS_NO_RESET) && FSL_FEATURE_CAPT_HAS_NO_RESET)
/*! @brief Pointers to CAPT resets for each instance. */
static const reset_ip_name_t s_captResets[] = CAPT_RSTS_N;
#endif

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t CAPT_GetInstance(CAPT_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_captBases); instance++)
    {
        if (s_captBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_captBases));

    return instance;
}
/*!
 * brief Initialize the CAPT module.
 *
 * param base CAPT peripheral base address.
 * param config Pointer to "capt_config_t" structure.
 */
void CAPT_Init(CAPT_Type *base, const capt_config_t *config)
{
    assert(config != NULL);

    uint32_t tmp32;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate. */
    CLOCK_EnableClock(s_captClock[CAPT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_CAPT_HAS_NO_RESET) && FSL_FEATURE_CAPT_HAS_NO_RESET)
    /* Reset the CAPT module */
    RESET_PeripheralReset(s_captResets[CAPT_GetInstance(base)]);
#endif

    /* Write CTRL register. */
    tmp32 = base->CTRL & (CAPT_CTRL_POLLMODE_MASK | CAPT_CTRL_TYPE_MASK
#if defined(FSL_FEATURE_CAPT_HAS_CTRL_DMA) && FSL_FEATURE_CAPT_HAS_CTRL_DMA
                          | CAPT_CTRL_DMA_MASK
#endif /* FSL_FEATURE_CAPT_HAS_CTRL_DMA */
                         );
    tmp32 |= CAPT_CTRL_TRIGGER(config->triggerMode) | CAPT_CTRL_FDIV(config->clockDivider) |
             CAPT_CTRL_XPINUSE(config->XpinsMode) | CAPT_CTRL_XPINSEL(config->enableXpins);
    if (config->enableWaitMode)
    {
        tmp32 |= CAPT_CTRL_WAIT_MASK;
    }
    /* Before writing into CTRL register, INCHANGE(bit 15)should equal '0'. */
    while (CAPT_CTRL_INCHANGE_MASK == (CAPT_CTRL_INCHANGE_MASK & base->CTRL))
    {
    }
    base->CTRL = tmp32;

    /* Write POLL_TCNT register. */
    tmp32 = base->POLL_TCNT & CAPT_POLL_TCNT_TCNT_MASK;
    tmp32 |= CAPT_POLL_TCNT_TOUT(config->timeOutCount) | CAPT_POLL_TCNT_POLL(config->pollCount) |
             CAPT_POLL_TCNT_MDELAY(config->mDelay) | CAPT_POLL_TCNT_RDELAY(config->rDelay);
    if (config->enableTouchLower)
    {
        tmp32 |= CAPT_POLL_TCNT_TCHLOW_ER_MASK;
    }
    base->POLL_TCNT = tmp32;
}

/*!
 * brief De-initialize the CAPT module.
 *
 * param base CAPT peripheral base address.
 */
void CAPT_Deinit(CAPT_Type *base)
{
    /* Make CAPT inactive. */
    /* Before writing into CTRL register, INCHANGE(bit 15)should equal '0'. */
    while (CAPT_CTRL_INCHANGE_MASK == (CAPT_CTRL_INCHANGE_MASK & base->CTRL))
    {
    }
    base->CTRL &= ~CAPT_CTRL_POLLMODE_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable clock gate. */
    CLOCK_DisableClock(s_captClock[CAPT_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets an available pre-defined settings for the CAPT's configuration.
 *
 * This function initializes the converter configuration structure with available settings. The default values are:
 * code
 *   config->enableWaitMode = false;
 *   config->enableTouchLower = true;
 *   config->clockDivider = 15U;
 *   config->timeOutCount = 12U;
 *   config->pollCount = 0U;
 *   config->enableXpins = 0U;
 *   config->triggerMode = kCAPT_YHPortTriggerMode;
 *   config->XpinsMode = kCAPT_InactiveXpinsDrivenLowMode;
 *   config->mDelay = kCAPT_MeasureDelayNoWait;
 *   config->rDelay = kCAPT_ResetDelayWait9FCLKs;
 * endcode
 * param base   CAPT peripheral base address.
 * param config Pointer to the configuration structure.
 */
void CAPT_GetDefaultConfig(capt_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableWaitMode   = false;
    config->enableTouchLower = true;
    config->clockDivider     = 15U;
    config->timeOutCount     = 12U;
    config->pollCount        = 0U;
    config->enableXpins      = 0U;
    config->triggerMode      = kCAPT_YHPortTriggerMode;
    config->XpinsMode        = kCAPT_InactiveXpinsDrivenLowMode;
    config->mDelay           = kCAPT_MeasureDelayNoWait;
    config->rDelay           = kCAPT_ResetDelayWait9FCLKs;
}

/*!
 * brief Set the CAPT polling mode.
 *
 * param base CAPT peripheral base address.
 * param mode The selection of polling mode.
 */
void CAPT_SetPollMode(CAPT_Type *base, capt_polling_mode_t mode)
{
    /* Before writing into CTRL register, INCHANGE(bit 15)should equal '0'. */
    while (CAPT_CTRL_INCHANGE_MASK == (CAPT_CTRL_INCHANGE_MASK & base->CTRL))
    {
    }

    base->CTRL &= ~CAPT_CTRL_POLLMODE_MASK;
    base->CTRL |= CAPT_CTRL_POLLMODE(mode);
}

#if defined(FSL_FEATURE_CAPT_HAS_CTRL_DMA) && FSL_FEATURE_CAPT_HAS_CTRL_DMA
/*!
 * brief Enable DMA feature.
 *
 * param base CAPT peripheral base address.
 * param mode Select how DMA triggers are generated.
 */
void CAPT_EnableDMA(CAPT_Type *base, capt_dma_mode_t mode)
{
    /* Before writing into CTRL register, INCHANGE(bit 15)should equal '0'. */
    while (CAPT_CTRL_INCHANGE_MASK == (CAPT_CTRL_INCHANGE_MASK & base->CTRL))
    {
    }
    base->CTRL = (base->CTRL & ~CAPT_CTRL_DMA_MASK) | CAPT_CTRL_DMA(mode);
}

/*!
 * brief Disable DMA feature.
 *
 * param base CAPT peripheral base address.
 */
void CAPT_DisableDMA(CAPT_Type *base)
{
    /* Before writing into CTRL register, INCHANGE(bit 15)should equal '0'. */
    while (CAPT_CTRL_INCHANGE_MASK == (CAPT_CTRL_INCHANGE_MASK & base->CTRL))
    {
    }
    base->CTRL &= ~CAPT_CTRL_DMA_MASK;
}
#endif /*FSL_FEATURE_CAPT_HAS_CTRL_DMA*/

/*!
 * brief Get CAPT touch data.
 *
 * param base CAPT peripheral base address.
 * param data The structure to store touch data.
 *
 * return If return 'true', which means get valid data.
 *         if return 'false', which means get invalid data.
 */
bool CAPT_GetTouchData(CAPT_Type *base, capt_touch_data_t *data)
{
    assert(NULL != data);

    uint32_t tmp32;
    bool ret;

    tmp32 = base->TOUCH;

    if (CAPT_TOUCH_CHANGE_MASK == (CAPT_TOUCH_CHANGE_MASK & tmp32))
    {
        ret = false;
    }
    else
    {
        if (CAPT_TOUCH_ISTOUCH_MASK == (CAPT_TOUCH_ISTOUCH_MASK & tmp32))
        {
            data->yesTouch = true;
        }
        else
        {
            data->yesTouch = false;
        }
        if (CAPT_TOUCH_ISTO_MASK == (CAPT_TOUCH_ISTO_MASK & tmp32))
        {
            data->yesTimeOut = true;
        }
        else
        {
            data->yesTimeOut = false;
        }
        data->XpinsIndex     = (uint8_t)((CAPT_TOUCH_XVAL_MASK & tmp32) >> CAPT_TOUCH_XVAL_SHIFT);
        data->sequenceNumber = (uint8_t)((CAPT_TOUCH_SEQ_MASK & tmp32) >> CAPT_TOUCH_SEQ_SHIFT);
        data->count          = (uint16_t)((CAPT_TOUCH_COUNT_MASK & tmp32) >> CAPT_TOUCH_COUNT_SHIFT);

        ret = true;
    }

    return ret;
}

/*
 * brief Start touch data polling using poll-now method.
 *
 * This function starts new data polling using polling-now method, CAPT stops when
 * the polling is finished, application could check the status or monitor interrupt
 * to know when the progress is finished.
 *
 * Note that this is simultaneous poll of all X pins, all enabled X pins are
 * activated concurrently, rather than walked one-at-a-time
 *
 * param base CAPT peripheral base address.
 * param enableXpins The X pins enabled in this polling.
 */
void CAPT_PollNow(CAPT_Type *base, uint16_t enableXpins)
{
    /* Before writing into CTRL register, INCHANGE(bit 15)should equal '0'. */
    while (0U != (CAPT_CTRL_INCHANGE_MASK & base->CTRL))
    {
    }

    /* If poll mode is not 0, change to 0. */
    if (0U != (base->CTRL & CAPT_CTRL_POLLMODE_MASK))
    {
        base->CTRL &= ~CAPT_CTRL_POLLMODE_MASK;

        while (0U != (CAPT_CTRL_INCHANGE_MASK & base->CTRL))
        {
        }
    }

    base->CTRL = (base->CTRL & ~(CAPT_CTRL_XPINSEL_MASK)) | CAPT_CTRL_POLLMODE(kCAPT_PollNowMode) |
                 CAPT_CTRL_XPINSEL(enableXpins);
}
