/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_kbi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.kbi"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to SEMC clocks for each instance. */
static const clock_ip_name_t s_kbiClock[FSL_FEATURE_SOC_KBI_COUNT] = KBI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to SEMC bases for each instance. */
static KBI_Type *const s_kbiBases[] = KBI_BASE_PTRS;

/*! @brief Pointers to Kbi IRQ number for each instance. */
static const IRQn_Type s_kbiIrqs[] = KBI_IRQS;
/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t KBI_GetInstance(KBI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_kbiBases); instance++)
    {
        if (s_kbiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_kbiBases));

    return instance;
}

/*!
 * brief KBI initialize.
 * This function ungates the KBI clock and initializes KBI.
 * This function must be called before calling any other KBI driver functions.
 *
 * param base KBI peripheral base address.
 * param configure The KBI configuration structure pointer.
 */
void KBI_Init(KBI_Type *base, kbi_config_t *configure)
{
    assert(configure);

    kbi_reg_t scReg;

    uint32_t instance = KBI_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Un-gate sdram controller clock. */
    CLOCK_EnableClock(s_kbiClock[KBI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Mask keyboard interrupts first to prevent false interrupt request during initialization */
    base->SC = 0;
    /* Setting KBI polarity. */
    base->ES = KBI_ES_KBEDG(configure->pinsEdge);
    /* Enable KBI pins. */
    base->PE = KBI_PE_KBIPE(configure->pinsEnabled);
    /* Clear any false interrupts. */
    scReg = KBI_SC_KBACK_MASK;
#if defined(FSL_FEATURE_KBI_HAS_SOURCE_PIN) && FSL_FEATURE_KBI_HAS_SOURCE_PIN
    /* Reset kbi sp register. */
    scReg |= KBI_SC_RSTKBSP_MASK | KBI_SC_KBSPEN_MASK;
#endif
    base->SC = scReg;

    /* Set KBI enable interrupts and KBI detect mode. */
    scReg    = base->SC;
    base->SC = ((kbi_reg_t)configure->mode & KBI_SC_KBMOD_MASK) | KBI_SC_KBIE_MASK | scReg;
    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_kbiIrqs[instance]);
}

/*!
 * brief Deinitializes the KBI module and gates the clock.
 * This function gates the KBI clock. As a result, the KBI
 * module doesn't work after calling this function.
 *
 * param base KBI peripheral base address.
 */
void KBI_Deinit(KBI_Type *base)
{
    kbi_reg_t scReg = KBI_SC_KBACK_MASK;

#if defined(FSL_FEATURE_KBI_HAS_SOURCE_PIN) && FSL_FEATURE_KBI_HAS_SOURCE_PIN
    /* Reset kbi sp register. */
    scReg |= KBI_SC_RSTKBSP_MASK;
#endif
    /* Disable interrupts. */
    base->SC = scReg;
    base->PE = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable Kbi clock. */
    CLOCK_DisableClock(s_kbiClock[KBI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
