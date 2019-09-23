/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader/bl_context.h"
#include "bootloader_common.h"
#include "bootloader_config.h"
#include "bootloader/bl_irq_common.h"
#include "autobaud/autobaud.h"
#include "packet/serial_packet.h"
#include "fsl_device_registers.h"
#include "fsl_i2c.h"
#include "utilities/fsl_assert.h"

#if BL_CONFIG_I2C
static const IRQn_Type i2c_irq_ids[FSL_FEATURE_SOC_I2C_COUNT] = { I2C0_IRQn,
#if (FSL_FEATURE_SOC_I2C_COUNT > 1)
                                                                  I2C1_IRQn,
#endif // #if (FSL_FEATURE_SOC_I2C_COUNT > 1)
#if (FSL_FEATURE_SOC_I2C_COUNT > 2)
                                                                  I2C2_IRQn
#endif // #if (FSL_FEATURE_SOC_I2C_COUNT > 2)
};

void I2C_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set)
{
    switch (instance)
    {
        case 0:
#if (FSL_FEATURE_SOC_I2C_COUNT > 1)
        case 1:
#endif // #if (FSL_FEATURE_SOC_I2C_COUNT > 1)
#if (FSL_FEATURE_SOC_I2C_COUNT > 2)
        case 2:
#endif // #if (FSL_FEATURE_SOC_I2C_COUNT > 2)
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(i2c_irq_ids[instance]);
            }
            else
            {
                NVIC_DisableIRQ(i2c_irq_ids[instance]);
            }
            break;
    }
}

#endif // BL_CONFIG_I2C

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
