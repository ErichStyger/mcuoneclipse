/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_uart.h"

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
    uart_handle_t hardwareHandle;
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
static UART_Type *const s_UartAdapterBase[] = UART_BASE_PTRS;

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))

#if !(defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
/* Array of UART IRQ number. */
static const IRQn_Type s_UartIRQ[] = UART_RX_TX_IRQS;

static hal_uart_state_t *s_UartState[sizeof(s_UartAdapterBase) / sizeof(UART_Type *)];
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
        case kStatus_UART_TxBusy:
            uartStatus = kStatus_HAL_UartTxBusy;
            break;
        case kStatus_UART_RxBusy:
            uartStatus = kStatus_HAL_UartRxBusy;
            break;
        case kStatus_UART_TxIdle:
            uartStatus = kStatus_HAL_UartTxIdle;
            break;
        case kStatus_UART_RxIdle:
            uartStatus = kStatus_HAL_UartRxIdle;
            break;
        case kStatus_UART_BaudrateNotSupport:
            uartStatus = kStatus_HAL_UartBaudrateNotSupport;
            break;
        case kStatus_UART_NoiseError:
        case kStatus_UART_FramingError:
        case kStatus_UART_ParityError:
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
static void HAL_UartCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *callbackParam)
{
    hal_uart_state_t *uartHandle;
    hal_uart_status_t uartStatus = HAL_UartGetStatus(status);
    assert(callbackParam);

    uartHandle = (hal_uart_state_t *)callbackParam;

    if (kStatus_HAL_UartProtocolError == uartStatus)
    {
        if (0U != uartHandle->hardwareHandle.rxDataSize)
        {
            uartStatus = kStatus_HAL_UartError;
        }
    }

    if (NULL != uartHandle->callback)
    {
        uartHandle->callback(uartHandle, uartStatus, uartHandle->callbackParam);
    }
}

#else

static void HAL_UartInterruptHandle(uint8_t instance)
{
    hal_uart_state_t *uartHandle = s_UartState[instance];
    uint32_t status;
    uint32_t clearStatus = 0;

    if (NULL == uartHandle)
    {
        return;
    }

    status = UART_GetStatusFlags(s_UartAdapterBase[instance]);

    /* Receive data register full */
    if ((0U != ((uint32_t)kUART_RxDataRegFullFlag & status)) &&
        (0U != (UART_GetEnabledInterrupts(s_UartAdapterBase[instance]) & (uint32_t)kUART_RxDataRegFullInterruptEnable)))
    {
        clearStatus |= (uint32_t)kUART_RxDataRegFullFlag | (uint32_t)kUART_RxOverrunFlag;
        if (NULL != uartHandle->rx.buffer)
        {
            uartHandle->rx.buffer[uartHandle->rx.bufferSofar++] = UART_ReadByte(s_UartAdapterBase[instance]);
            if (uartHandle->rx.bufferSofar >= uartHandle->rx.bufferLength)
            {
                UART_DisableInterrupts(s_UartAdapterBase[instance], (uint32_t)kUART_RxDataRegFullInterruptEnable |
                                                                        (uint32_t)kUART_RxOverrunInterruptEnable);
                uartHandle->rx.buffer = NULL;
                if (NULL != uartHandle->callback)
                {
                    uartHandle->callback(uartHandle, kStatus_HAL_UartRxIdle, uartHandle->callbackParam);
                }
            }
        }
    }

    /* Send data register empty and the interrupt is enabled. */
    if ((0U != ((uint32_t)kUART_TxDataRegEmptyFlag & status)) &&
        (0U !=
         (UART_GetEnabledInterrupts(s_UartAdapterBase[instance]) & (uint32_t)kUART_TxDataRegEmptyInterruptEnable)))
    {
        clearStatus |= (uint32_t)kUART_TxDataRegEmptyFlag | (uint32_t)kUART_TransmissionCompleteFlag;
        if (NULL != uartHandle->tx.buffer)
        {
            UART_WriteByte(s_UartAdapterBase[instance], uartHandle->tx.buffer[uartHandle->tx.bufferSofar++]);
            if (uartHandle->tx.bufferSofar >= uartHandle->tx.bufferLength)
            {
                UART_DisableInterrupts(s_UartAdapterBase[uartHandle->instance],
                                       (uint32_t)kUART_TxDataRegEmptyInterruptEnable);
                uartHandle->tx.buffer = NULL;
                if (NULL != uartHandle->callback)
                {
                    uartHandle->callback(uartHandle, kStatus_HAL_UartTxIdle, uartHandle->callbackParam);
                }
            }
        }
    }

#if 1
    (void)UART_ClearStatusFlags(s_UartAdapterBase[instance], clearStatus);
#endif
}
#endif

#endif

hal_uart_status_t HAL_UartInit(hal_uart_handle_t handle, const hal_uart_config_t *uart_config)
{
    hal_uart_state_t *uartHandle;
    uart_config_t uartConfig;
    status_t status;
    assert(handle);
    assert(uart_config);
    assert(uart_config->instance < (sizeof(s_UartAdapterBase) / sizeof(UART_Type *)));
    assert(s_UartAdapterBase[uart_config->instance]);

    assert(HAL_UART_HANDLE_SIZE >= sizeof(hal_uart_state_t));

    UART_GetDefaultConfig(&uartConfig);
    uartConfig.baudRate_Bps = uart_config->baudRate_Bps;

    if (kHAL_UartParityEven == uart_config->parityMode)
    {
        uartConfig.parityMode = kUART_ParityEven;
    }
    else if (kHAL_UartParityOdd == uart_config->parityMode)
    {
        uartConfig.parityMode = kUART_ParityOdd;
    }
    else
    {
        uartConfig.parityMode = kUART_ParityDisabled;
    }
#if defined(FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    if (kHAL_UartTwoStopBit == uart_config->stopBitCount)
    {
        uartConfig.stopBitCount = kUART_TwoStopBit;
    }
    else
    {
        uartConfig.stopBitCount = kUART_OneStopBit;
    }
#endif
    uartConfig.enableRx = (bool)uart_config->enableRx;
    uartConfig.enableTx = (bool)uart_config->enableTx;
#if defined(FSL_FEATURE_UART_HAS_MODEM_SUPPORT) && FSL_FEATURE_UART_HAS_MODEM_SUPPORT
    uartConfig.enableRxRTS = (bool)uart_config->enableRxRTS;
    uartConfig.enableTxCTS = (bool)uart_config->enableTxCTS;
#endif
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    uartConfig.txFifoWatermark = 0;
    uartConfig.rxFifoWatermark = 1;
#endif
    status = UART_Init(s_UartAdapterBase[uart_config->instance], &uartConfig, uart_config->srcClock_Hz);

    if (kStatus_Success != status)
    {
        return HAL_UartGetStatus(status);
    }

    uartHandle           = (hal_uart_state_t *)handle;
    uartHandle->instance = uart_config->instance;

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))

#if (defined(HAL_UART_TRANSFER_MODE) && (HAL_UART_TRANSFER_MODE > 0U))
    UART_TransferCreateHandle(s_UartAdapterBase[uart_config->instance], &uartHandle->hardwareHandle,
                              (uart_transfer_callback_t)HAL_UartCallback, handle);
#else
    s_UartState[uartHandle->instance] = uartHandle;
    /* Enable interrupt in NVIC. */
    NVIC_SetPriority((IRQn_Type)s_UartIRQ[uart_config->instance], HAL_UART_ISR_PRIORITY);
    (void)EnableIRQ(s_UartIRQ[uart_config->instance]);
#endif

#endif

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartDeinit(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;

    assert(handle);

    uartHandle = (hal_uart_state_t *)handle;

    UART_Deinit(s_UartAdapterBase[uartHandle->instance]);

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
    if (NULL != uartHandle->rx.buffer)
    {
        return kStatus_HAL_UartRxBusy;
    }
#endif

    status = UART_ReadBlocking(s_UartAdapterBase[uartHandle->instance], data, length);

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
    if (NULL != uartHandle->tx.buffer)
    {
        return kStatus_HAL_UartTxBusy;
    }
#endif

    (void)UART_WriteBlocking(s_UartAdapterBase[uartHandle->instance], data, length);

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

    status = UART_TransferReceiveNonBlocking(s_UartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle,
                                             (uart_transfer_t *)(void *)transfer, NULL);

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

    status = UART_TransferSendNonBlocking(s_UartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle,
                                          (uart_transfer_t *)(void *)transfer);

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

    status = UART_TransferGetReceiveCount(s_UartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle, count);

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

    status = UART_TransferGetSendCount(s_UartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle, count);

    return HAL_UartGetStatus(status);
}

hal_uart_status_t HAL_UartTransferAbortReceive(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    UART_TransferAbortReceive(s_UartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle);

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartTransferAbortSend(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    UART_TransferAbortSend(s_UartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle);

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
    assert(0U == HAL_UART_TRANSFER_MODE);

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
    assert(0U == HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (NULL != uartHandle->rx.buffer)
    {
        return kStatus_HAL_UartRxBusy;
    }

    uartHandle->rx.bufferLength = length;
    uartHandle->rx.bufferSofar  = 0;
    uartHandle->rx.buffer       = data;
    UART_EnableInterrupts(s_UartAdapterBase[uartHandle->instance],
                          (uint32_t)kUART_RxDataRegFullInterruptEnable | (uint32_t)kUART_RxOverrunInterruptEnable);
    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartSendNonBlocking(hal_uart_handle_t handle, uint8_t *data, size_t length)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(data);
    assert(length);
    assert(0U == HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (NULL != uartHandle->tx.buffer)
    {
        return kStatus_HAL_UartTxBusy;
    }
    uartHandle->tx.bufferLength = length;
    uartHandle->tx.bufferSofar  = 0;
    uartHandle->tx.buffer       = (volatile uint8_t *)data;
    UART_EnableInterrupts(s_UartAdapterBase[uartHandle->instance], (uint32_t)kUART_TxDataRegEmptyInterruptEnable);
    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartGetReceiveCount(hal_uart_handle_t handle, uint32_t *reCount)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(reCount);
    assert(0U == HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (NULL != uartHandle->rx.buffer)
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
    assert(0U == HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (NULL != uartHandle->tx.buffer)
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
    assert(0U == HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (NULL != uartHandle->rx.buffer)
    {
        UART_DisableInterrupts(s_UartAdapterBase[uartHandle->instance],
                               (uint32_t)kUART_RxDataRegFullInterruptEnable | (uint32_t)kUART_RxOverrunInterruptEnable);
        uartHandle->rx.buffer = NULL;
    }

    return kStatus_HAL_UartSuccess;
}

hal_uart_status_t HAL_UartAbortSend(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(0U == HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

    if (NULL != uartHandle->tx.buffer)
    {
        UART_DisableInterrupts(s_UartAdapterBase[uartHandle->instance], (uint32_t)kUART_TxDataRegEmptyInterruptEnable);
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
    DisableIRQ(s_UartIRQ[uartHandle->instance]);
#endif
    UART_TransferHandleIRQ(s_UartAdapterBase[uartHandle->instance], &uartHandle->hardwareHandle);
#if 0
    NVIC_SetPriority((IRQn_Type)s_UartIRQ[uartHandle->instance], HAL_UART_ISR_PRIORITY);
    EnableIRQ(s_UartIRQ[uartHandle->instance]);
#endif
}

#else

void HAL_UartIsrFunction(hal_uart_handle_t handle)
{
    hal_uart_state_t *uartHandle;
    assert(handle);
    assert(0U == HAL_UART_TRANSFER_MODE);

    uartHandle = (hal_uart_state_t *)handle;

#if 0
    DisableIRQ(s_UartIRQ[uartHandle->instance]);
#endif
    HAL_UartInterruptHandle(uartHandle->instance);
#if 0
    NVIC_SetPriority((IRQn_Type)s_UartIRQ[uartHandle->instance], HAL_UART_ISR_PRIORITY);
    EnableIRQ(s_UartIRQ[uartHandle->instance]);
#endif
}

#if defined(UART0)
#if ((!(defined(FSL_FEATURE_SOC_LPSCI_COUNT))) || \
     ((defined(FSL_FEATURE_SOC_LPSCI_COUNT)) && (FSL_FEATURE_SOC_LPSCI_COUNT == 0)))
void UART0_IRQHandler(void);
void UART0_IRQHandler(void)
{
    HAL_UartInterruptHandle(0);
    SDK_ISR_EXIT_BARRIER;
}

void UART0_RX_TX_IRQHandler(void);
void UART0_RX_TX_IRQHandler(void)
{
    UART0_IRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif
#endif

#if defined(UART1)
void UART1_IRQHandler(void);
void UART1_IRQHandler(void)
{
    HAL_UartInterruptHandle(1);
    SDK_ISR_EXIT_BARRIER;
}

void UART1_RX_TX_IRQHandler(void);
void UART1_RX_TX_IRQHandler(void)
{
    UART1_IRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART2)
void UART2_IRQHandler(void);
void UART2_IRQHandler(void)
{
    HAL_UartInterruptHandle(2);
    SDK_ISR_EXIT_BARRIER;
}

void UART2_RX_TX_IRQHandler(void);
void UART2_RX_TX_IRQHandler(void)
{
    UART2_IRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART3)
void UART3_IRQHandler(void);
void UART3_IRQHandler(void)
{
    HAL_UartInterruptHandle(3);
    SDK_ISR_EXIT_BARRIER;
}
void UART3_RX_TX_IRQHandler(void);
void UART3_RX_TX_IRQHandler(void)
{
    UART3_IRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART4)
void UART4_IRQHandler(void);
void UART4_IRQHandler(void)
{
    HAL_UartInterruptHandle(4);
    SDK_ISR_EXIT_BARRIER;
}
void UART4_RX_TX_IRQHandler(void);
void UART4_RX_TX_IRQHandler(void)
{
    UART4_IRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART5)
void UART5_IRQHandler(void);
void UART5_IRQHandler(void)
{
    HAL_UartInterruptHandle(5);
    SDK_ISR_EXIT_BARRIER;
}
void UART5_RX_TX_IRQHandler(void);
void UART5_RX_TX_IRQHandler(void)
{
    UART5_IRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1_IRQ2_IRQ3) && FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1_IRQ2_IRQ3
void UART0_UART1_UART2_UART3_IRQHandler(void)
{
    for (uint32_t instance = 0U; instance < 4U; instance++)
    {
        HAL_UartInterruptHandle(instance);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif /* FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1_IRQ2_IRQ3 */

#endif

#endif
