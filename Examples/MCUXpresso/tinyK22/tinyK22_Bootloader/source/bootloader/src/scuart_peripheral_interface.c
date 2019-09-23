/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader/bl_context.h"
#include "bootloader/bl_irq_common.h"
#include "bootloader_common.h"
#include "autobaud/autobaud.h"
#include "packet/serial_packet.h"
#include "fsl_device_registers.h"
#include "fsl_uart.h"
#include "utilities/fsl_assert.h"

#if BL_CONFIG_SCUART

//! @addtogroup scuart_peripheral
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static bool scuart_poll_for_activity(const peripheral_descriptor_t *self);
static status_t scuart_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function);
static void scuart_full_shutdown(const peripheral_descriptor_t *self);

static status_t scuart_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

const peripheral_control_interface_t g_scuartControlInterface = {
    .pollForActivity = scuart_poll_for_activity, .init = scuart_full_init, .shutdown = scuart_full_shutdown, .pump = 0
};

const peripheral_byte_inteface_t g_scuartByteInterface = {.init = NULL, .write = scuart_write };

static serial_byte_receive_func_t s_scuart_byte_receive_callback;
static bool g_uartInitDone = false;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
static UART_Type *get_uart_baseAddr(uint32_t instance)
{
    switch (instance)
    {
        default:
        case 0:
            return UART0;
        case 1:
            return UART1;
#if (FSL_FEATURE_SOC_UART_COUNT > 2U)
        case 2:
            return UART2;
#if (FSL_FEATURE_SOC_UART_COUNT > 3U)
        case 3:
            return UART3;
#if (FSL_FEATURE_SOC_UART_COUNT > 4U)
        case 4:
            return UART4;
#if (FSL_FEATURE_SOC_UART_COUNT > 5U)
        case 5:
            return UART5;
#endif // (FSL_FEATURE_SOC_UART_COUNT > 5U)
#endif // (FSL_FEATURE_SOC_UART_COUNT > 4U)
#endif // (FSL_FEATURE_SOC_UART_COUNT > 3U)
#endif // (FSL_FEATURE_SOC_UART_COUNT > 2U)
    }
}

bool scuart_poll_for_activity(const peripheral_descriptor_t *self)
{
    uint32_t baud;
    status_t autoBaudCompleted = autobaud_get_rate(self->instance, &baud);

    if (autoBaudCompleted == kStatus_Success)
    {
        uart_config_t userConfig;
        UART_Type *base = get_uart_baseAddr(self->instance);
        UART_GetDefaultConfig(&userConfig);

        userConfig.baudRate_Bps = baud;
        userConfig.enableTx = true;
        userConfig.enableRx = true;

        if (UART_Init(base, &userConfig, get_uart_clock(self->instance)) == kStatus_Success)
        {
            UART_SetSystemIRQ(self->instance, kPeripheralEnableIRQ);
            UART_EnableInterrupts(base, kUART_RxDataRegFullInterruptEnable);
            // Configure selected pin as uart peripheral interface
            self->pinmuxConfig(self->instance, kPinmuxType_Peripheral);

            // This was the byte pattern identified in autobaud detection, inform the command layer
            s_scuart_byte_receive_callback(kFramingPacketStartByte);
            s_scuart_byte_receive_callback(kFramingPacketType_Ping);

            g_uartInitDone = true;

            return true;
        }
        else
        {
            autobaud_init(self->instance);
        }
    }

    return false;
}

status_t scuart_full_init(const peripheral_descriptor_t *self, serial_byte_receive_func_t function)
{
    s_scuart_byte_receive_callback = function;

    // Since we are using autobaud once the detection is completed
    // it will call the UART initialization and remux the pins when it completes
    self->pinmuxConfig(self->instance, kPinmuxType_PollForActivity);

    // Init autobaud detector.
    autobaud_init(self->instance);

    return kStatus_Success;
}

void scuart_full_shutdown(const peripheral_descriptor_t *self)
{
    if (g_uartInitDone)
    {
        UART_SetSystemIRQ(self->instance, kPeripheralDisableIRQ);
        UART_Deinit(get_uart_baseAddr(self->instance));
    }

//! Note: if not deinit autobaud(IRQ method), user app may encounters hardfault
//! if it doesn't provide related pin interrupt service routine.
#if BL_FEATURE_UART_AUTOBAUD_IRQ
    // De-init autobaud detector.
    autobaud_deinit(self->instance);
#endif

#if BL_FEATURE_6PINS_PERIPHERAL
    // When the active peripheral is not UART, we should only restore
    //   those pin which we used to poll for activity.
    if (g_bootloaderContext.activePeripheral == NULL)
    {
        self->pinmuxConfig(self->instance, kPinmuxType_RestoreForActivity);
    }
    // When the active peripheral is UART, we should restore all
    //  the UART peripheral pin.
    else
#endif
    {
        // Restore selected pin to default state to reduce IDD.
        self->pinmuxConfig(self->instance, kPinmuxType_Default);
    }
}

status_t scuart_write(const peripheral_descriptor_t *self, const uint8_t *buffer, uint32_t byteCount)
{
    UART_WriteBlocking(get_uart_baseAddr(self->instance), buffer, byteCount);
    return kStatus_Success;
}

/********************************************************************/
/*
 * UART0 IRQ Handler
 *
 */

void UART0_RX_TX_IRQHandler(void)
{
    if (UART0->S1 & UART_S1_RDRF_MASK)
    {
        s_scuart_byte_receive_callback(UART0->D);
    }
}

/********************************************************************/
/*
 * UART1 IRQ Handler
 *
 */

void UART1_RX_TX_IRQHandler(void)
{
    uint8_t s1 = UART1->S1;
    uint8_t d;

    if (s1 & UART_S1_FE_MASK)
    {
        d = UART1->D;
    }
    else if (s1 & UART_S1_RDRF_MASK)
    {
        d = UART1->D;
        s_scuart_byte_receive_callback(d);
    }
}

#if (FSL_FEATURE_SOC_UART_COUNT > 2U)
/********************************************************************/
/*
 * UART2 IRQ Handler
 *
 */

void UART2_RX_TX_IRQHandler(void)
{
    if (UART2->S1 & UART_S1_RDRF_MASK)
    {
        s_scuart_byte_receive_callback(UART2->D);
    }
}

#if (FSL_FEATURE_SOC_UART_COUNT > 3U)

/********************************************************************/
/*
 * UART3 IRQ Handler
 *
 */

void UART3_RX_TX_IRQHandler(void)
{
    if (UART3->S1 & UART_S1_RDRF_MASK)
    {
        s_scuart_byte_receive_callback(UART3->D);
    }
}

/********************************************************************/
/*
 * UART4 IRQ Handler
 *
 */

void UART4_RX_TX_IRQHandler(void)
{
    if (UART4->S1 & UART_S1_RDRF_MASK)
    {
        s_scuart_byte_receive_callback(UART4->D);
    }
}

#if (FSL_FEATURE_SOC_UART_COUNT > 5U)
/********************************************************************/
/*
 * UART5 IRQ Handler
 *
 */

void UART5_RX_TX_IRQHandler(void)
{
    if (UART5->S1 & UART_S1_RDRF_MASK)
    {
        s_scuart_byte_receive_callback(UART5->D);
    }
}

#endif // (FSL_FEATURE_SOC_UART_COUNT > 5U)
#endif // (FSL_FEATURE_SOC_UART_COUNT > 3U)
#endif // (FSL_FEATURE_SOC_UART_COUNT > 2U)

//! @}

#endif // BL_CONFIG_SCUART

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
