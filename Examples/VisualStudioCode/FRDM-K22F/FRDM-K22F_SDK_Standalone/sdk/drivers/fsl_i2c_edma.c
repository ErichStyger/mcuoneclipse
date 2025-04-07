/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i2c_edma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.i2c_edma"
#endif

/*<! @breif Structure definition for i2c_master_edma_private_handle_t. The structure is private. */
typedef struct _i2c_master_edma_private_handle
{
    I2C_Type *base;
    i2c_master_edma_handle_t *handle;
} i2c_master_edma_private_handle_t;

/*! @brief i2c master DMA transfer state. */
enum _i2c_master_dma_transfer_states
{
    kIdleState         = 0x0U, /*!< I2C bus idle. */
    kTransferDataState = 0x1U, /*!< 7-bit address check state. */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief EDMA callback for I2C master EDMA driver.
 *
 * @param handle EDMA handler for I2C master EDMA driver
 * @param userData user param passed to the callback function
 */
static void I2C_MasterTransferCallbackEDMA(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds);

/*!
 * @brief Check and clear status operation.
 *
 * @param base I2C peripheral base address.
 * @param status current i2c hardware status.
 * @retval kStatus_Success No error found.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStatus_I2C_Nak Received Nak error.
 */
static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status);

/*!
 * @brief EDMA config for I2C master driver.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_edma_handle_t structure which stores the transfer state
 */
static void I2C_MasterTransferEDMAConfig(I2C_Type *base, i2c_master_edma_handle_t *handle);

/*!
 * @brief Set up master transfer, send slave address and sub address(if any), wait until the
 * wait until address sent status return.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_edma_handle_t structure which stores the transfer state
 * @param xfer pointer to i2c_master_transfer_t structure
 */
static status_t I2C_InitTransferStateMachineEDMA(I2C_Type *base,
                                                 i2c_master_edma_handle_t *handle,
                                                 i2c_master_transfer_t *xfer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*<! Private handle only used for internally. */
static i2c_master_edma_private_handle_t s_i2cEdmaPrivateHandle[FSL_FEATURE_SOC_I2C_COUNT];

/*******************************************************************************
 * Codes
 ******************************************************************************/

static void I2C_MasterTransferCallbackEDMA(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
    i2c_master_edma_private_handle_t *i2cPrivateHandle = (i2c_master_edma_private_handle_t *)userData;
    status_t result                                    = kStatus_Success;
    uint8_t tmpReg;
    size_t tmpdataSize;

    /* Disable DMA. */
    I2C_EnableDMA(i2cPrivateHandle->base, false);

    /* Send stop if kI2C_TransferNoStop flag is not asserted. */
    if (0U == (i2cPrivateHandle->handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag))
    {
        if (i2cPrivateHandle->handle->transfer.direction == kI2C_Read)
        {
            /* Change to send NAK at the last byte. */
            i2cPrivateHandle->base->C1 |= I2C_C1_TXAK_MASK;

            /* Wait the last data to be received. */
            while (0U == (i2cPrivateHandle->base->S & (uint8_t)kI2C_TransferCompleteFlag))
            {
            }

            /* Send stop signal. */
            result = I2C_MasterStop(i2cPrivateHandle->base);

            /* Read the last data byte. */
            tmpReg                                                        = i2cPrivateHandle->base->D;
            tmpdataSize                                                   = i2cPrivateHandle->handle->transfer.dataSize;
            *(i2cPrivateHandle->handle->transfer.data + tmpdataSize - 1U) = tmpReg;
        }
        else
        {
            /* Wait the last data to be sent. */
            while (0U == (i2cPrivateHandle->base->S & (uint8_t)kI2C_TransferCompleteFlag))
            {
            }

            /* Send stop signal. */
            result = I2C_MasterStop(i2cPrivateHandle->base);
        }
    }
    else
    {
        if (i2cPrivateHandle->handle->transfer.direction == kI2C_Read)
        {
            /* Change to send NAK at the last byte. */
            i2cPrivateHandle->base->C1 |= I2C_C1_TXAK_MASK;

            /* Wait the last data to be received. */
            while (0U == (i2cPrivateHandle->base->S & (uint8_t)kI2C_TransferCompleteFlag))
            {
            }

            /* Change direction to send. */
            i2cPrivateHandle->base->C1 |= I2C_C1_TX_MASK;

            /* Read the last data byte. */
            tmpReg                                                        = i2cPrivateHandle->base->D;
            tmpdataSize                                                   = i2cPrivateHandle->handle->transfer.dataSize;
            *(i2cPrivateHandle->handle->transfer.data + tmpdataSize - 1U) = tmpReg;
        }
    }

    i2cPrivateHandle->handle->state = (uint8_t)kIdleState;

    if (NULL != i2cPrivateHandle->handle->completionCallback)
    {
        i2cPrivateHandle->handle->completionCallback(i2cPrivateHandle->base, i2cPrivateHandle->handle, result,
                                                     i2cPrivateHandle->handle->userData);
    }
}

static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check arbitration lost. */
    if (0U != (status & (uint32_t)kI2C_ArbitrationLostFlag))
    {
        /* Clear arbitration lost flag. */
        base->S = (uint8_t)kI2C_ArbitrationLostFlag;
        result  = kStatus_I2C_ArbitrationLost;
    }
    /* Check NAK */
    else if (0U != (status & (uint32_t)kI2C_ReceiveNakFlag))
    {
        result = kStatus_I2C_Nak;
    }
    else
    {
        /* Add this to fix MISRA C2012 rule15.7 issue: Empty else without comment. */
    }

    return result;
}

static status_t I2C_InitTransferStateMachineEDMA(I2C_Type *base,
                                                 i2c_master_edma_handle_t *handle,
                                                 i2c_master_transfer_t *xfer)
{
    assert(NULL != handle);
    assert(NULL != xfer);

    status_t result = kStatus_Success;

    if (handle->state != (uint8_t)kIdleState)
    {
        return kStatus_I2C_Busy;
    }
    else
    {
        i2c_direction_t direction = xfer->direction;

        /* Init the handle member. */
        handle->transfer = *xfer;

        /* Save total transfer size. */
        handle->transferSize = xfer->dataSize;

        handle->state = (uint8_t)kTransferDataState;

        /* Clear all status before transfer. */
        I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

        /* Change to send write address when it's a read operation with command. */
        if ((xfer->subaddressSize > 0U) && (0U != (uint8_t)(xfer->direction == kI2C_Read)))
        {
            direction = kI2C_Write;
        }

        /* If repeated start is requested, send repeated start. */
        if (0U != (handle->transfer.flags & (uint32_t)kI2C_TransferRepeatedStartFlag))
        {
            result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, direction);
        }
        else /* For normal transfer, send start. */
        {
            result = I2C_MasterStart(base, handle->transfer.slaveAddress, direction);
        }

        if (kStatus_Success != result)
        {
            return result;
        }

#if I2C_RETRY_TIMES != 0U
        uint32_t waitTimes = I2C_RETRY_TIMES;
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (waitTimes == 0U)
        {
            return kStatus_I2C_Timeout;
        }
#else
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif

        /* Check if there's transfer error. */
        result = I2C_CheckAndClearError(base, base->S);

        /* Return if error. */
        if (kStatus_Success != result)
        {
            if (result == kStatus_I2C_Nak)
            {
                result = kStatus_I2C_Addr_Nak;

                if (I2C_MasterStop(base) != kStatus_Success)
                {
                    result = kStatus_I2C_Timeout;
                }

                if (NULL != handle->completionCallback)
                {
                    (handle->completionCallback)(base, handle, result, handle->userData);
                }
            }

            return result;
        }

        /* Send subaddress. */
        if (0U != handle->transfer.subaddressSize)
        {
            do
            {
                /* Clear interrupt pending flag. */
                base->S = (uint8_t)kI2C_IntPendingFlag;

                handle->transfer.subaddressSize--;
                base->D = (uint8_t)((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize));

                /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES != 0U
                waitTimes = I2C_RETRY_TIMES;
                while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
                {
                    waitTimes--;
                }
                if (waitTimes == 0U)
                {
                    return kStatus_I2C_Timeout;
                }
#else
                while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
                {
                }
#endif

                /* Check if there's transfer error. */
                result = I2C_CheckAndClearError(base, base->S);

                if (0 != result)
                {
                    return result;
                }

            } while (handle->transfer.subaddressSize > 0U);

            if (handle->transfer.direction == kI2C_Read)
            {
                /* Clear pending flag. */
                base->S = (uint8_t)kI2C_IntPendingFlag;

                /* Send repeated start and slave address. */
                result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, kI2C_Read);

                if (0 != result)
                {
                    return result;
                }

                /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES != 0U
                waitTimes = I2C_RETRY_TIMES;
                while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
                {
                    waitTimes--;
                }
                if (waitTimes == 0U)
                {
                    return kStatus_I2C_Timeout;
                }
#else
                while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
                {
                }
#endif

                /* Check if there's transfer error. */
                result = I2C_CheckAndClearError(base, base->S);

                if (0 != result)
                {
                    return result;
                }
            }
        }

        /* Clear pending flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;
    }

    return result;
}

static void I2C_MasterTransferEDMAConfig(I2C_Type *base, i2c_master_edma_handle_t *handle)
{
    edma_transfer_config_t transfer_config = {0};

    if (handle->transfer.direction == kI2C_Read)
    {
        transfer_config.srcAddr          = (uint32_t)I2C_GetDataRegAddr(base);
        transfer_config.destAddr         = (uint32_t)(handle->transfer.data);
        transfer_config.majorLoopCounts  = (handle->transfer.dataSize - 1U);
        transfer_config.srcTransferSize  = kEDMA_TransferSize1Bytes;
        transfer_config.srcOffset        = 0;
        transfer_config.destTransferSize = kEDMA_TransferSize1Bytes;
        transfer_config.destOffset       = 1;
        transfer_config.minorLoopBytes   = 1;
    }
    else
    {
        transfer_config.srcAddr          = ((uint32_t)handle->transfer.data + 1U);
        transfer_config.destAddr         = (uint32_t)I2C_GetDataRegAddr(base);
        transfer_config.majorLoopCounts  = (handle->transfer.dataSize - 1U);
        transfer_config.srcTransferSize  = kEDMA_TransferSize1Bytes;
        transfer_config.srcOffset        = 1;
        transfer_config.destTransferSize = kEDMA_TransferSize1Bytes;
        transfer_config.destOffset       = 0;
        transfer_config.minorLoopBytes   = 1;
    }

    /* Store the initially configured eDMA minor byte transfer count into the I2C handle */
    handle->nbytes = (uint8_t)(transfer_config.minorLoopBytes);

    (void)EDMA_SubmitTransfer(handle->dmaHandle, (const edma_transfer_config_t *)(uint32_t)&transfer_config);

    EDMA_StartTransfer(handle->dmaHandle);
}

/*!
 * brief Initializes the I2C handle which is used in transactional functions.
 *
 * param base I2C peripheral base address.
 * param handle A pointer to the i2c_master_edma_handle_t structure.
 * param callback A pointer to the user callback function.
 * param userData A user parameter passed to the callback function.
 * param edmaHandle eDMA handle pointer.
 */
void I2C_MasterCreateEDMAHandle(I2C_Type *base,
                                i2c_master_edma_handle_t *handle,
                                i2c_master_edma_transfer_callback_t callback,
                                void *userData,
                                edma_handle_t *edmaHandle)
{
    assert(NULL != handle);
    assert(NULL != edmaHandle);

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set the user callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Set the handle for EDMA. */
    handle->dmaHandle = edmaHandle;

    s_i2cEdmaPrivateHandle[instance].base   = base;
    s_i2cEdmaPrivateHandle[instance].handle = handle;

    EDMA_SetCallback(edmaHandle, (edma_callback)I2C_MasterTransferCallbackEDMA, &s_i2cEdmaPrivateHandle[instance]);
}

/*!
 * brief Performs a master eDMA non-blocking transfer on the I2C bus.
 *
 * param base I2C peripheral base address.
 * param handle A pointer to the i2c_master_edma_handle_t structure.
 * param xfer A pointer to the transfer structure of i2c_master_transfer_t.
 * retval kStatus_Success Successfully completed the data transmission.
 * retval kStatus_I2C_Busy A previous transmission is still not finished.
 * retval kStatus_I2C_Timeout Transfer error, waits for a signal timeout.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_MasterTransferEDMA(I2C_Type *base, i2c_master_edma_handle_t *handle, i2c_master_transfer_t *xfer)
{
    assert(NULL != handle);
    assert(NULL != xfer);

    status_t result;
    uint8_t tmpReg;

    /* Disable dma xfer. */
    I2C_EnableDMA(base, false);

    /* Send address and command buffer(if there is), until senddata phase or receive data phase. */
    result = I2C_InitTransferStateMachineEDMA(base, handle, xfer);

    if (0 != result)
    {
        /* Send stop if received Nak. */
        if (result == kStatus_I2C_Nak)
        {
            if (I2C_MasterStop(base) != kStatus_Success)
            {
                result = kStatus_I2C_Timeout;
            }
        }

        /* Reset the state to idle state. */
        handle->state = (uint8_t)kIdleState;

        return result;
    }

    /* Configure dma transfer. */
    /* For i2c send, need to send 1 byte first to trigger the dma, for i2c read,
    need to send stop before reading the last byte, so the dma transfer size should
    be (xSize - 1). */
    if (handle->transfer.dataSize > 1U)
    {
        I2C_MasterTransferEDMAConfig(base, handle);
        if (handle->transfer.direction == kI2C_Read)
        {
            /* Change direction for receive. */
            base->C1 &= ~(uint8_t)(I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

            /* Read dummy to release the bus. */
            (void)base->D;

            /* Enabe dma transfer. */
            I2C_EnableDMA(base, true);
        }
        else
        {
            /* Enabe dma transfer. */
            I2C_EnableDMA(base, true);

            /* Send the first data. */
            base->D = *handle->transfer.data;
        }
    }
    else /* If transfer size is 1, use polling method. */
    {
        if (handle->transfer.direction == kI2C_Read)
        {
            tmpReg = base->C1;

            /* Change direction to Rx. */
            tmpReg &= ~(uint8_t)I2C_C1_TX_MASK;

            /* Configure send NAK */
            tmpReg |= I2C_C1_TXAK_MASK;

            base->C1 = tmpReg;

            /* Read dummy to release the bus. */
            (void)base->D;
        }
        else
        {
            base->D = *handle->transfer.data;
        }

        /* Wait until data transfer complete. */
#if I2C_RETRY_TIMES != 0U
        uint32_t waitTimes = I2C_RETRY_TIMES;
        while ((0U == (base->S & (uint8_t)kI2C_IntPendingFlag)) && (0U != waitTimes))
        {
            waitTimes--;
        }
        if (waitTimes == 0U)
        {
            return kStatus_I2C_Timeout;
        }
#else
        while (0U == (base->S & (uint8_t)kI2C_IntPendingFlag))
        {
        }
#endif

        /* Clear pending flag. */
        base->S = (uint8_t)kI2C_IntPendingFlag;

        /* Send stop if kI2C_TransferNoStop flag is not asserted. */
        if (0U == (handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag))
        {
            result = I2C_MasterStop(base);
        }
        else
        {
            /* Change direction to send. */
            base->C1 |= I2C_C1_TX_MASK;
        }

        /* Read the last byte of data. */
        if (handle->transfer.direction == kI2C_Read)
        {
            tmpReg                 = base->D;
            *handle->transfer.data = tmpReg;
        }

        /* Reset the state to idle. */
        handle->state = (uint8_t)kIdleState;
    }

    return result;
}

/*!
 * brief Gets a master transfer status during the eDMA non-blocking transfer.
 *
 * param base I2C peripheral base address.
 * param handle A pointer to the i2c_master_edma_handle_t structure.
 * param count A number of bytes transferred by the non-blocking transaction.
 */
status_t I2C_MasterTransferGetCountEDMA(I2C_Type *base, i2c_master_edma_handle_t *handle, size_t *count)
{
    assert(NULL != handle->dmaHandle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    if ((uint8_t)kIdleState != handle->state)
    {
        *count = (handle->transferSize -
                  (uint32_t)handle->nbytes *
                      EDMA_GetRemainingMajorLoopCount(handle->dmaHandle->base, handle->dmaHandle->channel));
    }
    else
    {
        *count = handle->transferSize;
    }

    return kStatus_Success;
}

/*!
 * brief Aborts a master eDMA non-blocking transfer early.
 *
 * param base I2C peripheral base address.
 * param handle A pointer to the i2c_master_edma_handle_t structure.
 */
void I2C_MasterTransferAbortEDMA(I2C_Type *base, i2c_master_edma_handle_t *handle)
{
    EDMA_AbortTransfer(handle->dmaHandle);

    /* Disable dma transfer. */
    I2C_EnableDMA(base, false);

    /* Reset the state to idle. */
    handle->state = (uint8_t)kIdleState;
}
