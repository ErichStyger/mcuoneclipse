/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader_config.h"
#include "bootloader/bl_irq_common.h"
#include "fsl_device_registers.h"
#include "fsl_dspi.h"
#include "bootloader_common.h"
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
static const IRQn_Type dspi_irq_ids[FSL_FEATURE_SOC_DSPI_COUNT] = {
#if defined(SPI0)
    SPI0_IRQn,
#else
    SPI_IRQn,
#endif
#if (FSL_FEATURE_SOC_DSPI_COUNT > 1)
    SPI1_IRQn,
#endif
#if (FSL_FEATURE_SOC_DSPI_COUNT > 2)
    SPI2_IRQn,
#endif
};

void DSPI_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set)
{
    switch (instance)
    {
        case 0:
#if (FSL_FEATURE_SOC_DSPI_COUNT > 1)
        case 1:
#endif // #if (LPI2C_INSTANCE_COUNT > 1)
#if (FSL_FEATURE_SOC_DSPI_COUNT > 2)
        case 2:
#endif // #if (LPI2C_INSTANCE_COUNT > 2)
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(dspi_irq_ids[instance]);
            }
            else
            {
                NVIC_DisableIRQ(dspi_irq_ids[instance]);
            }
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
