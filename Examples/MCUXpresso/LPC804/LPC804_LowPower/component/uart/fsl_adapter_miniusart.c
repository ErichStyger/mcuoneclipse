/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_usart.h"

#include "fsl_adapter_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef NDEBUG
#if (defined(DEBUG_CONSOLE_ASSERT_DISABLE) && (DEBUG_CONSOLE_ASSERT_DISABLE > 0U))
#undef assert
#define assert(n)
#endif
#endif

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))
/*! @brief uart RX state structure. */
typedef struct _hal_uart_receive_state
{
    volatile uint8_t *buffer;
    volatile uint32_t bufferLength;
    volatile uint32_t bufferSofar;
} hal_uart_receive_state_t;

/*! @brief uart TX state structure. */
typedef struct _hal_uart_send_state
{
    volatile uint8_t *buffer;
    volatile uint32_t bufferLength;
    volatile uint32_t bufferSofar;
} hal_uart_send_state_t;
#endif
/*! @brief uart state structure. */
typedef struct _hal_uart_state
{
#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))
    hal_uart_transfer_callback_t callback;
    void *callbackParam;
#if (defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
    usart_handle_t hardwareHandle;
#endif
    hal_uart_receive_state_t rx;
    hal_uart_send_state_t tx;
#endif
    uint8_t instance;
} hal_uart_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static USART_Type *const s_UsartAdapterBase[] = USART_BASE_PTRS;

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))

#if !(defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
/* Array of USART IRQ number. */
static const IRQn_Type s_UsartIRQ[] = USART_IRQS;

static hal_uart_state_t *s_UartState[sizeof(s_UsartAdapterBase) / sizeof(USART_Type *)];
#endif

#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

#if (defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
static hal_uart_status_t HAL_UartGetStatus(status_t status)
{
    hal_uart_status_t uartStatus = kStatus_HAL_UartError;
    switch (status)
    {
        case kStatus_Success:
            uartStatus = kStatus_HAL_UartSuccess;
            break;
        case kStatus_USART_TxBusy:
            uartStatus = kStatus_HAL_UartTxBusy;
            break;
        case kStatus_USART_RxBusy:
            uartStatus = kStatus_HAL_UartRxBusy;
            break;
        case kStatus_USART_TxIdle:
            uartStatus = kStatus_HAL_UartTxIdle;
            break;
        case kStatus_USART_RxIdle:
            uartStatus = kStatus_HAL_UartRxIdle;
            break;
        case kStatus_USART_BaudrateNotSupport:
            uartStatus = kStatus_HAL_UartBaudrateNotSupport;
            break;
        case kStatus_USART_NoiseError:
        case kStatus_USART_FramingError:
        case kStatus_USART_ParityError:
            uartStatus = kStatus_HAL_UartProtocolError;
            break;
        default:
            /* This comments for MISRA C-2012 Rule 16.4 */
            break;
    }
    return uartStatus;
}
#else
static hal_uart_status_t HAL_UartGetStatus(status_t status)
{
    if (kStatus_Success == status)
    {
        return kStatus_HAL_UartSuccess;
    }
    else
    {
        return kStatus_HAL_UartError;
    }
}
#endif

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))

#if (defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
static void HAL_UartCallback(USART_Type *base, usart_handle_t *handle, status_t status, void *callbackParam)
{
    hal_uart_state_t *uartHandle;
    hal_uart_status_t uartStatus = HAL_UartGetStatus(status);
    assert(callbackParam);

    uartHandle = (hal_uart_state_t *)callbackParam;

    if (kStatus_HAL_UartProtocolError == uartStatus)
    {
        if (uartHandle->hardwareHandle.rxDataSize)
        {
            uartStatus = kStatus_HAL_UartError;
        }
    }

    if (uartHandle->callback)
    {
        uartHandle->callback(uartHandle, uartStatus, uartHandle->callbackParam);
    }
}

#else

static void HAL_UartInterruptHandle(uint8_t instance)
{
    hal_uart_state_t *uartHandle = s_UartState[instance];
    uint32_t status;

    if (NULL == uartHandle)
    {
        return;
    }

    status = USART_GetStatusFlags(s_UsartAdapterBase[instance]);

    /* Receive data register full */
    if ((USART_STAT_RXRDY_MASK & status) &&
        (USART_GetEnabledInterrupts(s_UsartAdapterBase[instance]) & kUSART_RxReadyInterruptEnable))
    {
        if (uartHandle->rx.buffer)
        {
            uartHandle->rx.buffer[uartHandle->rx.bufferSofar++] = USART_ReadByte(s_UsartAdapterBase[instance]);
            if (uartHandle->rx.bufferSofar >= uartHandle->rx.bufferLength)
            {
                USART_DisableInterrupts(s_UsartAdapterBase[instance],
                                        kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable);
                uartHandle->rx.buffer = NULL;
                if (uartHandle->callback)
                {
                    uartHandle->callback(uartHandle, kStatus_HAL_UartRxIdle, uartHandle->callbackParam);
                }
            }
        }
    }

    /* Send data register empty and the interrupt is enabled. */
    if ((USART_STAT_TXRDY_MASK & status) &&
        (USART_GetEnabledInterrupts(s_UsartAdapterBase[instance]) & kUSART_TxReadyInterruptEnable))
    {
        if (uartHandle->tx.buffer)
        {
            USART_WriteByte(s_UsartAdapterBase[instance], uartHandle->tx.buffer[uartHandle->tx.bufferSofar++]);
            if (uartHandle->tx.bufferSofar >= uartHandle->tx.bufferLength)
            {
                USART_DisableInterrupts(s_UsartAdapterBase[uartHandle->instance], kUSART_TxReadyInterruptEnable);
                uartHandle->tx.buffer = NULL;
                if (uartHandle->callback)
                {
                    uartHandle->callback(uartHandle, kStatus_HAL_UartTxIdle, uartHandle->callbackParam);
                }
            }
        }
    }

#if 1
    USART_ClearStatusFlags(s_UsartAdapterBase[instance], status);
#endif
}
#endif

#endif

hal_uart_status_t HAL_UartInit(hal_uart_handle_t handle, const hal_uart_config_t *uart_config)
{
    hal_uart_state_t *uartHandle;
    usart_config_t usartConfig;
    status_t status;
    assert(handle);
    assert(uart_config);
    assert(uart_config->instance < (sizeof(s_UsartAdapterBase) / sizeof(USART_Type *)));
    assert(s_UsartAdapterBase[uart_config->instance]);

    assert(HAL_UART_HANDLE_SIZE >= sizeof(hal_uart_state_t));

    USART_GetDefaultConfig(&usartConfig);
    usartConfig.baudRate_Bps = uart_config->baudRate_Bps;

    if (kHAL_UartParityEven == uart_config->parityMode)
    {
        usartConfig.parityMode = kUSART_ParityEven;
    }
    else if (kHAL_UartParityOdd == uart_config->parityMode)
    {
        usartConfig.parityMode = kUSART_ParityOdd;
    }
    else
    {
        usartConfig.parityMode = kUSART_ParityDisabled;
    }

    if (kHAL_UartTwoStopBit == uart_config->stopBitCount)
    {
        usartConfig.stopBitCount = kUSART_TwoStopBit;
    }
    else
    {
        usartConfig.stopBitCount = kUSART_OneStopBit;
    }
    usartConfig.enableRx = (bool)uart_config->enableRx;
    usartConfig.enableTx = (bool)uart_config->enableTx;

    status = USART_Init(s_UsartAdapterBase[uart_config->instance], &usartConfig, uart_config->srcClock_Hz);

    if (kStatus_Success != status)
    {
        return HAL_UartGetStatus(status);
    }

    uartHandle           = (hal_uart_state_t *)handle;
    uartHandle->instance = uart_config->instance;

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))

#if (defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
    USART_TransferCreateHandle(s_UsartAdapterBase[uart_config->instance], &uartHandle->hardwareHandle,
                               (usart_transfer_callback_t)HAL_UartCallback, handle);
#else
    s_UartState[uartHandle->instance] = uartHandle;
    /* Enable interrupt in NVIC. */
    NVIC_SetPriority((IRQn_Type)s_UsartIRQ[uart_config->instance], HAL_UART_ISR_PRIORITY);
    EnableIRQ(s_UsartIRQ[uart_config->instance]);
#endif

#endif

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartDeinit(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;

    assert(handle);

    uartHandle = (hal_uart_state_t *)handle;

    USART_Deinit(s_UsartAdapterBase[uartHandle->instance]);

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))

#if !(defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
    s_UartState[uartHandle->instance] = NULL;
#endif

#endif

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartReceiveBlocking(hal_uart_handle_t handle, uint8_t *data, size_t length)
{
    hal_uart_state_t *uartHandle;
    status_t status;
    assert(handle);
    assert(data);
    assert(length);

    uartHandle = (hal_uart_state_t *)handle;

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))
    if (uartHandle->rx.buffer)
    {
        return kStatus_HAL_UartRxBusy;
    }
#endif

    status = USART_ReadBlocking(s_UsartAdapterBase[uartHandle->instance], data, length);

    return HAL_UartGetStatus(status);
}

hal_uart_status_t HAL_UartSendBlocking(hal_uart_handle_t handle, const uint8_t *data, size_t length)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(data);
    assert(length);

    uartHandle = (hal_uart_state_t *)handle;

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))
    if (uartHandle->tx.buffer)
    {
        return kStatus_HAL_UartTxBusy;
    }
#endif

    (void)USART_WriteBlocking(s_UsartAdapterBase[uartHandle->instance], data, length);

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartEnterLowpower(hal_uart_handle_t handle)
{
    assert(handle);

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartExitLowpower(hal_uart_handle_t handle)
{
    assert(handle);

    return kStatus_HAL_UartSuccess;
}

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))

#if (defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))

hal_uart_status_t HAL_UartTransferInstallCallback(hal_uart_handle_t handle,
                                                  hal_uart_transfer_callback_t callback,
                                                  void *callbackParam)
{
    hal_uart_state_t *uartHandle;

    assert(handle);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    uartHandle->callbackParam = callbackParam;
    uartHandle->callback      = callback;

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartTransferReceiveNonBlocking(hal_uart_handle_t handle, hal_uart_transfer_t *transfer)
{
    hal_uart_state_t *uartHandle;
    status_t status;
    assert(handle);
    assert(transfer);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    status = USART_TransferReceiveNonBlocking(s_UsartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle,
                                              (usart_transfer_t *)transfer, NULL);

    return HAL_UartGetStatus(status);
}

hal_uart_status_t HAL_UartTransferSendNonBlocking(hal_uart_handle_t handle, hal_uart_transfer_t *transfer)
{
    hal_uart_state_t *uartHandle;
    status_t status;
    assert(handle);
    assert(transfer);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    status = USART_TransferSendNonBlocking(s_UsartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle,
                                           (usart_transfer_t *)transfer);

    return HAL_UartGetStatus(status);
}

hal_uart_status_t HAL_UartTransferGetReceiveCount(hal_uart_handle_t handle, uint32_t *count)
{
    hal_uart_state_t *uartHandle;
    status_t status;
    assert(handle);
    assert(count);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    status =
        USART_TransferGetReceiveCount(s_UsartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle, count);

    return HAL_UartGetStatus(status);
}

hal_uart_status_t HAL_UartTransferGetSendCount(hal_uart_handle_t handle, uint32_t *count)
{
    hal_uart_state_t *uartHandle;
    status_t status;
    assert(handle);
    assert(count);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    status = USART_TransferGetSendCount(s_UsartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle, count);

    return HAL_UartGetStatus(status);
}

hal_uart_status_t HAL_UartTransferAbortReceive(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    USART_TransferAbortReceive(s_UsartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle);

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartTransferAbortSend(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    USART_TransferAbortSend(s_UsartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle);

    return kStatus_HAL_UartSuccess;
}

#else

/* None transactional API with non-blocking mode. */
hal_uart_status_t HAL_UartInstallCallback(hal_uart_handle_t handle,
                                          hal_uart_transfer_callback_t callback,
                                          void *callbackParam)
{
    hal_uart_state_t *uartHandle;

    assert(handle);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    uartHandle->callbackParam = callbackParam;
    uartHandle->callback      = callback;

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartReceiveNonBlocking(hal_uart_handle_t handle, uint8_t *data, size_t length)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(data);
    assert(length);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (uartHandle->rx.buffer)
    {
        return kStatus_HAL_UartRxBusy;
    }

    uartHandle->rx.bufferLength = length;
    uartHandle->rx.bufferSofar  = 0;
    uartHandle->rx.buffer       = data;
    USART_EnableInterrupts(s_UsartAdapterBase[uartHandle->instance],
                           kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable);
    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartSendNonBlocking(hal_uart_handle_t handle, uint8_t *data, size_t length)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(data);
    assert(length);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (uartHandle->tx.buffer)
    {
        return kStatus_HAL_UartTxBusy;
    }
    uartHandle->tx.bufferLength = length;
    uartHandle->tx.bufferSofar  = 0;
    uartHandle->tx.buffer       = (volatile uint8_t *)data;
    USART_EnableInterrupts(s_UsartAdapterBase[uartHandle->instance], kUSART_TxReadyInterruptEnable);
    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartGetReceiveCount(hal_uart_handle_t handle, uint32_t *reCount)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(reCount);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (uartHandle->rx.buffer)
    {
        *reCount = uartHandle->rx.bufferSofar;
        return kStatus_HAL_UartSuccess;
    }
    return kStatus_HAL_UartError;
}

hal_uart_status_t HAL_UartGetSendCount(hal_uart_handle_t handle, uint32_t *seCount)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(seCount);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (uartHandle->tx.buffer)
    {
        *seCount = uartHandle->tx.bufferSofar;
        return kStatus_HAL_UartSuccess;
    }
    return kStatus_HAL_UartError;
}

hal_uart_status_t HAL_UartAbortReceive(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (uartHandle->rx.buffer)
    {
        USART_DisableInterrupts(s_UsartAdapterBase[uartHandle->instance],
                                kUSART_RxReadyInterruptEnable | kUSART_HardwareOverRunInterruptEnable);
        uartHandle->rx.buffer = NULL;
    }

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartAbortSend(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (uartHandle->tx.buffer)
    {
        USART_DisableInterrupts(s_UsartAdapterBase[uartHandle->instance], kUSART_TxReadyInterruptEnable);
        uartHandle->tx.buffer = NULL;
    }

    return kStatus_HAL_UartSuccess;
}

#endif

#if (defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))

void HAL_UartIsrFunction(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

#if 0
    DisableIRQ(s_UsartIRQ[uartHandle->instance]);
#endif
    USART_TransferHandleIRQ(s_UsartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle);
#if 0
    NVIC_SetPriority((IRQn_Type)s_UsartIRQ[uartHandle->instance], HAL_UART_ISR_PRIORITY);
    EnableIRQ(s_UsartIRQ[uartHandle->instance]);
#endif
}

#else

void HAL_UartIsrFunction(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(!HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

#if 0
    DisableIRQ(s_UsartIRQ[uartHandle->instance]);
#endif
    HAL_UartInterruptHandle(uartHandle->instance);
#if 0
    NVIC_SetPriority((IRQn_Type)s_UsartIRQ[uartHandle->instance], HAL_UART_ISR_PRIORITY);
    EnableIRQ(s_UsartIRQ[uartHandle->instance]);
#endif
}

#if defined(USART0)
void USART0_IRQHandler(void)
{
    HAL_UartInterruptHandle(0);
}
#endif

#if defined(USART1)
void USART1_IRQHandler(void)
{
    HAL_UartInterruptHandle(1);
}
#endif

#if defined(USART2)
void USART2_IRQHandler(void)
{
    HAL_UartInterruptHandle(2);
}
#endif

#if defined(USART3)
void PIN_INT6_USART3_IRQHandler(void)
{
    HAL_UartInterruptHandle(3);
}
#endif

#if defined(USART4)
void PIN_INT7_USART4_IRQHandler(void)
{
    HAL_UartInterruptHandle(4);
}
#endif
#endif

#endif
