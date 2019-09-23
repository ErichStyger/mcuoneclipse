/*
 * Copyright (c) 2014 Freescale Semiconductor, Inc.
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
#include "fsl_uart.h"
#include "utilities/fsl_assert.h"

static const IRQn_Type uart_irqs[] = UART_RX_TX_IRQS;

void UART_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set)
{
    switch (instance)
    {
        case 0:
#if (FSL_FEATURE_SOC_UART_COUNT > 1)
        case 1:
#endif // #if (FSL_FEATURE_SOC_UART_COUNT > 1)
#if (FSL_FEATURE_SOC_UART_COUNT > 2)
        case 2:
#endif // #if (FSL_FEATURE_SOC_UART_COUNT > 2)
#if (FSL_FEATURE_SOC_UART_COUNT > 3)
        case 3:
#endif // #if (FSL_FEATURE_SOC_UART_COUNT > 3)
#if (FSL_FEATURE_SOC_UART_COUNT > 4)
        case 4:
#endif // #if (FSL_FEATURE_SOC_UART_COUNT > 4)
            if (set == kPeripheralEnableIRQ)
            {
                NVIC_EnableIRQ(uart_irqs[instance]);
            }
            else
            {
                NVIC_DisableIRQ(uart_irqs[instance]);
            }
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
