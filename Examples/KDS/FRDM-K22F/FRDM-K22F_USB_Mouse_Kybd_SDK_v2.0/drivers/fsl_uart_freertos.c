/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

static void UART_RTOS_Callback(UART_Type *base, uart_handle_t *state, status_t status, void *param)
{
    uart_rtos_handle_t *handle = (uart_rtos_handle_t *)param;
    BaseType_t xHigherPriorityTaskWoken, xResult;

    xHigherPriorityTaskWoken = pdFALSE;
    xResult = pdFAIL;

    if (status == kStatus_UART_RxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->rx_event, RTOS_UART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_UART_TxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->tx_event, RTOS_UART_COMPLETE, &xHigherPriorityTaskWoken);
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
int UART_RTOS_Init(uart_rtos_handle_t *handle, uart_handle_t *t_handle, const struct rtos_uart_config *cfg)
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

    handle->tx_sem = xSemaphoreCreateMutex();
    if (NULL == handle->tx_sem)
    {
        return kStatus_Fail;
    }
    handle->rx_sem = xSemaphoreCreateMutex();
    if (NULL == handle->rx_sem)
    {
        vSemaphoreDelete(handle->tx_sem);
        return kStatus_Fail;
    }
    handle->tx_event = xEventGroupCreate();
    if (NULL == handle->tx_event)
    {
        vSemaphoreDelete(handle->rx_sem);
        vSemaphoreDelete(handle->tx_sem);
        return kStatus_Fail;
    }
    handle->rx_event = xEventGroupCreate();
    if (NULL == handle->rx_event)
    {
        vEventGroupDelete(handle->rx_event);
        vSemaphoreDelete(handle->rx_sem);
        vSemaphoreDelete(handle->tx_sem);
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

    vEventGroupDelete(handle->tx_event);
    vEventGroupDelete(handle->rx_event);

    /* Give the semaphore. This is for functional safety */
    xSemaphoreGive(handle->tx_sem);
    xSemaphoreGive(handle->rx_sem);

    vSemaphoreDelete(handle->tx_sem);
    vSemaphoreDelete(handle->rx_sem);

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

    if (pdFALSE == xSemaphoreTake(handle->tx_sem, 0))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->tx_xfer.data = (uint8_t *)buffer;
    handle->tx_xfer.dataSize = (uint32_t)length;

    xEventGroupClearBits(handle->tx_event, RTOS_UART_COMPLETE);

    /* Non-blocking call */
    UART_TransferSendNonBlocking(handle->base, handle->t_state, &handle->tx_xfer);

    ev = xEventGroupWaitBits(handle->tx_event, RTOS_UART_COMPLETE, pdTRUE, pdFALSE, portMAX_DELAY);
    if (!(ev & RTOS_UART_COMPLETE))
    {
        retval = kStatus_Fail;
    }

    if (pdFALSE == xSemaphoreGive(handle->tx_sem))
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
    int retval = kStatus_Success;

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

    if (pdFALSE == xSemaphoreTake(handle->rx_sem, portMAX_DELAY))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->rx_xfer.data = buffer;
    handle->rx_xfer.dataSize = (uint32_t)length;

    xEventGroupClearBits(handle->rx_event, RTOS_UART_COMPLETE);

    /* Non-blocking call */
    UART_TransferReceiveNonBlocking(handle->base, handle->t_state, &handle->rx_xfer, &n);

    if (n < length)
    {
        ev = xEventGroupWaitBits(handle->rx_event, RTOS_UART_COMPLETE, pdTRUE, pdFALSE, portMAX_DELAY);
        if (ev & RTOS_UART_COMPLETE)
        {
            n = length;
        }
        else
        {
            retval = kStatus_Fail;
        }
    }

    if (pdFALSE == xSemaphoreGive(handle->rx_sem))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }

    if (received != NULL)
    {
        *received = n;
    }

    return retval;
}
