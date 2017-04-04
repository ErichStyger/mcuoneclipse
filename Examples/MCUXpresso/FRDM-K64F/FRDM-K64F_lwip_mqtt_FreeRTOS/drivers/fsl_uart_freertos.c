/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_uart_freertos.h"
#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

static void UART_RTOS_Callback(UART_Type *base, uart_handle_t *state, status_t status, void *param)
{
    uart_rtos_handle_t *handle = (uart_rtos_handle_t *)param;
    BaseType_t xHigherPriorityTaskWoken, xResult;

    xHigherPriorityTaskWoken = pdFALSE;
    xResult = pdFAIL;

    if (status == kStatus_UART_RxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_UART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_UART_TxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->txEvent, RTOS_UART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_UART_RxRingBufferOverrun)
    {
        xResult = xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_UART_RING_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_UART_RxHardwareOverrun)
    {
        /* Clear Overrun flag (OR) in UART S1 register */
        UART_ClearStatusFlags(base, kUART_RxOverrunFlag);
        xResult =
            xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_UART_HARDWARE_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }

    if (xResult != pdFAIL)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Init
 * Description   : Initializes the UART instance for application
 *
 *END**************************************************************************/
int UART_RTOS_Init(uart_rtos_handle_t *handle, uart_handle_t *t_handle, const uart_rtos_config_t *cfg)
{
    uart_config_t defcfg;

    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == t_handle)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == cfg)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == cfg->base)
    {
        return kStatus_InvalidArgument;
    }
    if (0 == cfg->srcclk)
    {
        return kStatus_InvalidArgument;
    }
    if (0 == cfg->baudrate)
    {
        return kStatus_InvalidArgument;
    }

    handle->base = cfg->base;
    handle->t_state = t_handle;
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->txSemaphore = xSemaphoreCreateMutexStatic(&handle->txSemaphoreBuffer);
#else
    handle->txSemaphore = xSemaphoreCreateMutex();
#endif
    if (NULL == handle->txSemaphore)
    {
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->rxSemaphore = xSemaphoreCreateMutexStatic(&handle->rxSemaphoreBuffer);
#else
    handle->rxSemaphore = xSemaphoreCreateMutex();
#endif
    if (NULL == handle->rxSemaphore)
    {
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->txEvent = xEventGroupCreateStatic(&handle->txEventBuffer);
#else
    handle->txEvent = xEventGroupCreate();
#endif
    if (NULL == handle->txEvent)
    {
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->rxEvent = xEventGroupCreateStatic(&handle->rxEventBuffer);
#else
    handle->rxEvent = xEventGroupCreate();
#endif
    if (NULL == handle->rxEvent)
    {
        vEventGroupDelete(handle->txEvent);
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
    UART_GetDefaultConfig(&defcfg);

    defcfg.baudRate_Bps = cfg->baudrate;
    defcfg.parityMode = cfg->parity;
#if defined(FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    defcfg.stopBitCount = cfg->stopbits;
#endif

    UART_Init(handle->base, &defcfg, cfg->srcclk);
    UART_TransferCreateHandle(handle->base, handle->t_state, UART_RTOS_Callback, handle);
    UART_TransferStartRingBuffer(handle->base, handle->t_state, cfg->buffer, cfg->buffer_size);

    UART_EnableTx(handle->base, true);
    UART_EnableRx(handle->base, true);

    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Deinit
 * Description   : Deinitializes the UART instance and frees resources
 *
 *END**************************************************************************/
int UART_RTOS_Deinit(uart_rtos_handle_t *handle)
{
    UART_Deinit(handle->base);

    vEventGroupDelete(handle->txEvent);
    vEventGroupDelete(handle->rxEvent);

    /* Give the semaphore. This is for functional safety */
    xSemaphoreGive(handle->txSemaphore);
    xSemaphoreGive(handle->rxSemaphore);

    vSemaphoreDelete(handle->txSemaphore);
    vSemaphoreDelete(handle->rxSemaphore);

    /* Invalidate the handle */
    handle->base = NULL;
    handle->t_state = NULL;

    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Send
 * Description   : Initializes the UART instance for application
 *
 *END**************************************************************************/
int UART_RTOS_Send(uart_rtos_handle_t *handle, const uint8_t *buffer, uint32_t length)
{
    EventBits_t ev;
    int retval = kStatus_Success;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0 == length)
    {
        return 0;
    }
    if (NULL == buffer)
    {
        return kStatus_InvalidArgument;
    }

    if (pdFALSE == xSemaphoreTake(handle->txSemaphore, 0))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->txTransfer.data = (uint8_t *)buffer;
    handle->txTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    UART_TransferSendNonBlocking(handle->base, handle->t_state, &handle->txTransfer);

    ev = xEventGroupWaitBits(handle->txEvent, RTOS_UART_COMPLETE, pdTRUE, pdFALSE, portMAX_DELAY);
    if (!(ev & RTOS_UART_COMPLETE))
    {
        retval = kStatus_Fail;
    }

    if (pdFALSE == xSemaphoreGive(handle->txSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }

    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Recv
 * Description   : Receives chars for the application
 *
 *END**************************************************************************/
int UART_RTOS_Receive(uart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length, size_t *received)
{
    EventBits_t ev;
    size_t n = 0;
    int retval = kStatus_Fail;
    size_t local_received = 0;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0 == length)
    {
        if (received != NULL)
        {
            *received = n;
        }
        return 0;
    }
    if (NULL == buffer)
    {
        return kStatus_InvalidArgument;
    }

    /* New transfer can be performed only after current one is finished */
    if (pdFALSE == xSemaphoreTake(handle->rxSemaphore, portMAX_DELAY))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->rxTransfer.data = buffer;
    handle->rxTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    UART_TransferReceiveNonBlocking(handle->base, handle->t_state, &handle->rxTransfer, &n);

    ev = xEventGroupWaitBits(handle->rxEvent,
                             RTOS_UART_COMPLETE | RTOS_UART_RING_BUFFER_OVERRUN | RTOS_UART_HARDWARE_BUFFER_OVERRUN,
                             pdTRUE, pdFALSE, portMAX_DELAY);
    if (ev & RTOS_UART_HARDWARE_BUFFER_OVERRUN)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        UART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of UART_RTOS_Receive.
           RTOS_UART_COMPLETE flag could be set meanwhile overrun is handled */
        xEventGroupClearBits(handle->rxEvent, RTOS_UART_COMPLETE);
        retval = kStatus_UART_RxHardwareOverrun;
        local_received = 0;
    }
    else if (ev & RTOS_UART_RING_BUFFER_OVERRUN)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        UART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of UART_RTOS_Receive.
           RTOS_UART_COMPLETE flag could be set meanwhile overrun is handled */
        xEventGroupClearBits(handle->rxEvent, RTOS_UART_COMPLETE);
        retval = kStatus_UART_RxRingBufferOverrun;
        local_received = 0;
    }
    else if (ev & RTOS_UART_COMPLETE)
    {
        retval = kStatus_Success;
        local_received = length;
    }

    /* Prevent repetitive NULL check */
    if (received != NULL)
    {
        *received = local_received;
    }

    /* Enable next transfer. Current one is finished */
    if (pdFALSE == xSemaphoreGive(handle->rxSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }
    return retval;
}
