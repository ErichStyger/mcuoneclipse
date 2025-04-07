/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexbus.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexbus"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Gets the instance from the base address
 *
 * @param base FLEXBUS peripheral base address
 *
 * @return The FLEXBUS instance
 */
static uint32_t FLEXBUS_GetInstance(FB_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to FLEXBUS bases for each instance. */
static FB_Type *const s_flexbusBases[] = FB_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to FLEXBUS clocks for each instance. */
static const clock_ip_name_t s_flexbusClocks[] = FLEXBUS_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t FLEXBUS_GetInstance(FB_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_flexbusBases); instance++)
    {
        if (s_flexbusBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_flexbusBases));

    return instance;
}

/*!
 * brief Initializes and configures the FlexBus module.
 *
 * This function enables the clock gate for FlexBus module.
 * Only chip 0 is validated and set to known values. Other chips are disabled.
 * Note that in this function, certain parameters, depending on external memories,  must
 * be set before using the FLEXBUS_Init() function.
 * This example shows how to set up the uart_state_t and the
 * flexbus_config_t parameters and how to call the FLEXBUS_Init function by passing
 * in these parameters.
   code
    flexbus_config_t flexbusConfig;
    FLEXBUS_GetDefaultConfig(&flexbusConfig);
    flexbusConfig.waitStates            = 2U;
    flexbusConfig.chipBaseAddress       = 0x60000000U;
    flexbusConfig.chipBaseAddressMask   = 7U;
    FLEXBUS_Init(FB, &flexbusConfig);
   endcode
 *
 * param base FlexBus peripheral address.
 * param config Pointer to the configuration structure
*/
void FLEXBUS_Init(FB_Type *base, const flexbus_config_t *config)
{
    assert(config != NULL);
    assert(config->chip < FB_CSAR_COUNT);
    assert(config->waitStates <= 0x3FU);
    assert(config->secondaryWaitStates <= 0x3FU);

    uint32_t chip      = config->chip;
    uint32_t reg_value = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate clock for FLEXBUS */
    CLOCK_EnableClock(s_flexbusClocks[FLEXBUS_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the associated register to default state */
    /* Set CSMR register, all chips not valid (disabled) */
    base->CS[chip].CSMR = 0x0000U;
    /* Set default base address */
    base->CS[chip].CSAR &= (~FB_CSAR_BA_MASK);
    /* Reset FB_CSCRx register */
    base->CS[chip].CSCR = 0x0000U;

    /* Set FB_CSPMCR register */
    /* FlexBus signal group 1 multiplex control */
    reg_value |= (uint32_t)kFLEXBUS_MultiplexGroup1_FB_ALE << FB_CSPMCR_GROUP1_SHIFT;
    /* FlexBus signal group 2 multiplex control */
    reg_value |= (uint32_t)kFLEXBUS_MultiplexGroup2_FB_CS4 << FB_CSPMCR_GROUP2_SHIFT;
    /* FlexBus signal group 3 multiplex control */
    reg_value |= (uint32_t)kFLEXBUS_MultiplexGroup3_FB_CS5 << FB_CSPMCR_GROUP3_SHIFT;
    /* FlexBus signal group 4 multiplex control */
    reg_value |= (uint32_t)kFLEXBUS_MultiplexGroup4_FB_TBST << FB_CSPMCR_GROUP4_SHIFT;
    /* FlexBus signal group 5 multiplex control */
    reg_value |= (uint32_t)kFLEXBUS_MultiplexGroup5_FB_TA << FB_CSPMCR_GROUP5_SHIFT;
    /* Write to CSPMCR register */
    base->CSPMCR = reg_value;

    /* Base address */
    reg_value = config->chipBaseAddress;
    /* Write to CSAR register */
    base->CS[chip].CSAR = reg_value;

    /* Chip-select validation */
    reg_value = 0x1U << FB_CSMR_V_SHIFT;
    /* Write protect */
    reg_value |= ((uint32_t)config->writeProtect) << FB_CSMR_WP_SHIFT;
    /* Base address mask */
    reg_value |= config->chipBaseAddressMask << FB_CSMR_BAM_SHIFT;
    /* Write to CSMR register */
    base->CS[chip].CSMR = reg_value;

    /* Burst write */
    reg_value = ((uint32_t)config->burstWrite) << FB_CSCR_BSTW_SHIFT;
    /* Burst read */
    reg_value |= ((uint32_t)config->burstRead) << FB_CSCR_BSTR_SHIFT;
    /* Byte-enable mode */
    reg_value |= ((uint32_t)config->byteEnableMode) << FB_CSCR_BEM_SHIFT;
    /* Port size */
    reg_value |= (uint32_t)config->portSize << FB_CSCR_PS_SHIFT;
    /* The internal transfer acknowledge for accesses */
    reg_value |= ((uint32_t)config->autoAcknowledge) << FB_CSCR_AA_SHIFT;
    /* Byte-Lane shift */
    reg_value |= (uint32_t)config->byteLaneShift << FB_CSCR_BLS_SHIFT;
    /* The number of wait states */
    reg_value |= (uint32_t)config->waitStates << FB_CSCR_WS_SHIFT;
    /* Write address hold or deselect */
    reg_value |= (uint32_t)config->writeAddressHold << FB_CSCR_WRAH_SHIFT;
    /* Read address hold or deselect */
    reg_value |= (uint32_t)config->readAddressHold << FB_CSCR_RDAH_SHIFT;
    /* Address setup */
    reg_value |= (uint32_t)config->addressSetup << FB_CSCR_ASET_SHIFT;
    /* Extended transfer start/extended address latch */
    reg_value |= ((uint32_t)config->extendTransferAddress) << FB_CSCR_EXTS_SHIFT;
    /* Secondary wait state */
    if (config->secondaryWaitStatesEnable)
    {
        reg_value |= FB_CSCR_SWSEN_MASK;
        reg_value |= (uint32_t)(config->secondaryWaitStates) << FB_CSCR_SWS_SHIFT;
    }
    /* Write to CSCR register */
    base->CS[chip].CSCR = reg_value;

    /* FlexBus signal group 1 multiplex control */
    reg_value = (uint32_t)config->group1MultiplexControl << FB_CSPMCR_GROUP1_SHIFT;
    /* FlexBus signal group 2 multiplex control */
    reg_value |= (uint32_t)config->group2MultiplexControl << FB_CSPMCR_GROUP2_SHIFT;
    /* FlexBus signal group 3 multiplex control */
    reg_value |= (uint32_t)config->group3MultiplexControl << FB_CSPMCR_GROUP3_SHIFT;
    /* FlexBus signal group 4 multiplex control */
    reg_value |= (uint32_t)config->group4MultiplexControl << FB_CSPMCR_GROUP4_SHIFT;
    /* FlexBus signal group 5 multiplex control */
    reg_value |= (uint32_t)config->group5MultiplexControl << FB_CSPMCR_GROUP5_SHIFT;
    /* Write to CSPMCR register */
    base->CSPMCR = reg_value;

    /* Enable CSPMCR0[V] to make all chip select registers take effect. */
    if (chip != 0UL)
    {
        base->CS[0].CSMR |= FB_CSMR_V_MASK;
    }
}

/*!
 * brief De-initializes a FlexBus instance.
 *
 * This function disables the clock gate of the FlexBus module clock.
 *
 * param base FlexBus peripheral address.
 */
void FLEXBUS_Deinit(FB_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate clock for FLEXBUS */
    CLOCK_DisableClock(s_flexbusClocks[FLEXBUS_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Initializes the FlexBus configuration structure.
 *
 * This function initializes the FlexBus configuration structure to default value. The default
 * values are.
   code
   fbConfig->chip                         = 0;
   fbConfig->writeProtect                 = false;
   fbConfig->burstWrite                   = false;
   fbConfig->burstRead                    = false;
   fbConfig->byteEnableMode               = false;
   fbConfig->autoAcknowledge              = true;
   fbConfig->extendTransferAddress        = false;
   fbConfig->secondaryWaitStatesEnable    = false;
   fbConfig->byteLaneShift                = kFLEXBUS_NotShifted;
   fbConfig->writeAddressHold             = kFLEXBUS_Hold1Cycle;
   fbConfig->readAddressHold              = kFLEXBUS_Hold1Or0Cycles;
   fbConfig->addressSetup                 = kFLEXBUS_FirstRisingEdge;
   fbConfig->portSize                     = kFLEXBUS_1Byte;
   fbConfig->group1MultiplexControl       = kFLEXBUS_MultiplexGroup1_FB_ALE;
   fbConfig->group2MultiplexControl       = kFLEXBUS_MultiplexGroup2_FB_CS4 ;
   fbConfig->group3MultiplexControl       = kFLEXBUS_MultiplexGroup3_FB_CS5;
   fbConfig->group4MultiplexControl       = kFLEXBUS_MultiplexGroup4_FB_TBST;
   fbConfig->group5MultiplexControl       = kFLEXBUS_MultiplexGroup5_FB_TA;
   endcode
 * param config Pointer to the initialization structure.
 * see FLEXBUS_Init
 */
void FLEXBUS_GetDefaultConfig(flexbus_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->chip                      = 0;                   /* Chip 0 FlexBus for validation */
    config->writeProtect              = false;               /* Write accesses are allowed */
    config->burstWrite                = false;               /* Burst-Write disable */
    config->burstRead                 = false;               /* Burst-Read disable */
    config->byteEnableMode            = false;               /* Byte-Enable mode is asserted for data write only */
    config->autoAcknowledge           = true;                /* Auto-Acknowledge enable */
    config->extendTransferAddress     = false;               /* Extend transfer start/extend address latch disable */
    config->secondaryWaitStatesEnable = false;               /* Secondary wait state disable */
    config->byteLaneShift             = kFLEXBUS_NotShifted; /* Byte-Lane shift disable */
    config->writeAddressHold          = kFLEXBUS_Hold1Cycle; /* Write address hold 1 cycles */
    config->readAddressHold           = kFLEXBUS_Hold1Or0Cycles; /* Read address hold 0 cycles */
    config->addressSetup =
        kFLEXBUS_FirstRisingEdge; /* Assert ~FB_CSn on the first rising clock edge after the address is asserted */
    config->portSize               = kFLEXBUS_1Byte;                   /* 1 byte port size of transfer */
    config->group1MultiplexControl = kFLEXBUS_MultiplexGroup1_FB_ALE;  /* FB_ALE */
    config->group2MultiplexControl = kFLEXBUS_MultiplexGroup2_FB_CS4;  /* FB_CS4 */
    config->group3MultiplexControl = kFLEXBUS_MultiplexGroup3_FB_CS5;  /* FB_CS5 */
    config->group4MultiplexControl = kFLEXBUS_MultiplexGroup4_FB_TBST; /* FB_TBST */
    config->group5MultiplexControl = kFLEXBUS_MultiplexGroup5_FB_TA;   /* FB_TA */
}
