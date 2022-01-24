/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_irq.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.irq"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to irq bases for each instance. */
static IRQ_Type *const s_irqBases[] = IRQ_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to irq clocks for each instance. */
static const clock_ip_name_t s_irqClocks[] = IRQ_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Get irq instance.
 *
 * @param base   IRQ peripheral base pointer
 *
 * @retval Irq instance number.
 */
uint32_t IRQ_GetInstance(IRQ_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_irqBases); instance++)
    {
        if (s_irqBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_irqBases));

    return instance;
}

/*!
 * brief Initializes the IRQ pin used by the board.
 *
 * To initialize the IRQ pin, define a irq configuration, specify whhether enable pull-up, the edge and detect mode.
 * Then, call the IRQ_Init() function.
 *
 * This is an example to initialize irq configuration.
 * code
 * irq_config_t config =
 * {
 *   true,
 *   kIRQ_FallingEdgeorLowlevel,
 *   kIRQ_DetectOnEdgesOnly
 * }
 * endcode
 *
 * param base   IRQ peripheral base pointer
 * param config IRQ configuration pointer
 */
void IRQ_Init(IRQ_Type *base, const irq_config_t *config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable IRQ clock. */
    CLOCK_EnableClock(s_irqClocks[IRQ_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    uint8_t scValue = base->SC;
    scValue &= (uint8_t) ~(IRQ_SC_IRQMOD_MASK | IRQ_SC_IRQEDG_MASK | IRQ_SC_IRQPDD_MASK);
    if (!config->enablePullDevice)
    {
        scValue |= IRQ_SC_IRQPDD_MASK;
    }

    /* Enable IRQ pin. */
    scValue |= IRQ_SC_IRQMOD(config->detectMode) | IRQ_SC_IRQEDG(config->edgeSelect) | IRQ_SC_IRQPE_MASK;
    base->SC = scValue;
}

/*!
 * brief   Deinitialize IRQ peripheral.
 *
 * This function disables the IRQ clock.
 *
 * param base IRQ peripheral base pointer.
 *
 * retval None.
 */
void IRQ_Deinit(IRQ_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_irqClocks[IRQ_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
