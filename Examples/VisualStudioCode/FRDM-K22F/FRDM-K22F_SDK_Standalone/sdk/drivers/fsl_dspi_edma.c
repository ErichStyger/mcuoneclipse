/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dspi_edma.h"

/***********************************************************************************************************************
 * Definitions
 ***********************************************************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.dspi_edma"
#endif

/*!
 * @brief Structure definition for dspi_master_edma_private_handle_t. The structure is private.
 */
typedef struct _dspi_master_edma_private_handle
{
    SPI_Type *base;                    /*!< DSPI peripheral base address. */
    dspi_master_edma_handle_t *handle; /*!< dspi_master_edma_handle_t handle */
} dspi_master_edma_private_handle_t;

/*!
 * @brief Structure definition for dspi_slave_edma_private_handle_t. The structure is private.
 */
typedef struct _dspi_slave_edma_private_handle
{
    SPI_Type *base;                   /*!< DSPI peripheral base address. */
    dspi_slave_edma_handle_t *handle; /*!< dspi_master_edma_handle_t handle */
} dspi_slave_edma_private_handle_t;

/***********************************************************************************************************************
 * Prototypes
 ***********************************************************************************************************************/
/*!
 * @brief EDMA_DspiMasterCallback after the DSPI master transfer completed by using EDMA.
 * This is not a public API.
 */
static void EDMA_DspiMasterCallback(edma_handle_t *edmaHandle,
                                    void *g_dspiEdmaPrivateHandle,
                                    bool transferDone,
                                    uint32_t tcds);

/*!
 * @brief EDMA_DspiSlaveCallback after the DSPI slave transfer completed by using EDMA.
 * This is not a public API.
 */
static void EDMA_DspiSlaveCallback(edma_handle_t *edmaHandle,
                                   void *g_dspiEdmaPrivateHandle,
                                   bool transferDone,
                                   uint32_t tcds);

/***********************************************************************************************************************
 * Variables
 ***********************************************************************************************************************/

/*! @brief Pointers to dspi edma handles for each instance. */
static dspi_master_edma_private_handle_t s_dspiMasterEdmaPrivateHandle[FSL_FEATURE_SOC_DSPI_COUNT];
static dspi_slave_edma_private_handle_t s_dspiSlaveEdmaPrivateHandle[FSL_FEATURE_SOC_DSPI_COUNT];

/***********************************************************************************************************************
 * Code
 ***********************************************************************************************************************/

/*!
 * brief Initializes the DSPI master eDMA handle.
 *
 * This function initializes the DSPI eDMA handle which can be used for other DSPI transactional APIs.  Usually, for a
 * specified DSPI instance, call this API once to get the initialized handle.
 *
 * Note that DSPI eDMA has separated (RX and TX as two sources) or shared (RX  and TX are the same source) DMA request
 * source.
 * (1) For the separated DMA request source, enable and set the RX DMAMUX source for edmaRxRegToRxDataHandle and
 * TX DMAMUX source for edmaIntermediaryToTxRegHandle.
 * (2) For the shared DMA request source, enable and set the RX/RX DMAMUX source for the edmaRxRegToRxDataHandle.
 *
 * param base DSPI peripheral base address.
 * param handle DSPI handle pointer to dspi_master_edma_handle_t.
 * param callback DSPI callback.
 * param userData A callback function parameter.
 * param edmaRxRegToRxDataHandle edmaRxRegToRxDataHandle pointer to edma_handle_t.
 * param edmaTxDataToIntermediaryHandle edmaTxDataToIntermediaryHandle pointer to edma_handle_t.
 * param edmaIntermediaryToTxRegHandle edmaIntermediaryToTxRegHandle pointer to edma_handle_t.
 */
void DSPI_MasterTransferCreateHandleEDMA(SPI_Type *base,
                                         dspi_master_edma_handle_t *handle,
                                         dspi_master_edma_transfer_callback_t callback,
                                         void *userData,
                                         edma_handle_t *edmaRxRegToRxDataHandle,
                                         edma_handle_t *edmaTxDataToIntermediaryHandle,
                                         edma_handle_t *edmaIntermediaryToTxRegHandle)
{
    assert(NULL != handle);
    assert(NULL != edmaRxRegToRxDataHandle);
#if (!(defined(FSL_FEATURE_DSPI_HAS_GASKET) && FSL_FEATURE_DSPI_HAS_GASKET))
    assert(NULL != edmaTxDataToIntermediaryHandle);
#endif
    assert(NULL != edmaIntermediaryToTxRegHandle);

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    uint32_t instance = DSPI_GetInstance(base);

    s_dspiMasterEdmaPrivateHandle[instance].base   = base;
    s_dspiMasterEdmaPrivateHandle[instance].handle = handle;

    handle->callback = callback;
    handle->userData = userData;

    handle->edmaRxRegToRxDataHandle        = edmaRxRegToRxDataHandle;
    handle->edmaTxDataToIntermediaryHandle = edmaTxDataToIntermediaryHandle;
    handle->edmaIntermediaryToTxRegHandle  = edmaIntermediaryToTxRegHandle;
}

/*!
 * brief DSPI master transfer data using eDMA.
 *
 * This function transfers data using eDMA. This is a non-blocking function, which returns right away. When all data
 * is transferred, the callback function is called.
 *
 * note The max transfer size of each transfer depends on whether the instance's Tx/Rx shares the same DMA request. If
 * FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(x) is true, then the max transfer size is 32767 datawidth of data,
 * otherwise is 511.
 *
 * param base DSPI peripheral base address.
 * param handle A pointer to the dspi_master_edma_handle_t structure which stores the transfer state.
 * param transfer A pointer to the dspi_transfer_t structure.
 * return status of status_t.
 */
status_t DSPI_MasterTransferEDMA(SPI_Type *base, dspi_master_edma_handle_t *handle, dspi_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);

    /* If the transfer count is zero, then return immediately.*/
    if (transfer->dataSize == 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* If both send buffer and receive buffer is null */
    if ((NULL == (transfer->txData)) && (NULL == (transfer->rxData)))
    {
        return kStatus_InvalidArgument;
    }

    /* Check that we're not busy.*/
    if (handle->state == (uint8_t)kDSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }

    handle->state = (uint8_t)kDSPI_Busy;

    uint32_t instance                = DSPI_GetInstance(base);
    uint16_t wordToSend              = 0;
    uint8_t dummyData                = DSPI_GetDummyDataInstance(base);
    uint8_t dataAlreadyFed           = 0;
    uint8_t dataFedMax               = 2;
    uint32_t tmpMCR                  = 0;
    size_t tmpRemainingSendByteCount = 0;

    uint32_t rxAddr = DSPI_GetRxRegisterAddress(base);
    uint32_t txAddr = DSPI_MasterGetTxRegisterAddress(base);

    edma_tcd_t *softwareTCD = (edma_tcd_t *)((uint32_t)(&handle->dspiSoftwareTCD[1]) & (~0x1FU));

    edma_transfer_config_t transferConfigA = {0};
    edma_transfer_config_t transferConfigB = {0};

    handle->txBuffIfNull = ((uint32_t)dummyData << 8U) | dummyData;

    dspi_command_data_config_t commandStruct;
    DSPI_StopTransfer(base);
    DSPI_FlushFifo(base, true, true);
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_AllStatusFlag);

    commandStruct.whichPcs =
        (uint8_t)((uint32_t)1U << ((transfer->configFlags & DSPI_MASTER_PCS_MASK) >> DSPI_MASTER_PCS_SHIFT));
    commandStruct.isEndOfQueue       = false;
    commandStruct.clearTransferCount = false;
    commandStruct.whichCtar = (uint8_t)((transfer->configFlags & DSPI_MASTER_CTAR_MASK) >> DSPI_MASTER_CTAR_SHIFT);
    commandStruct.isPcsContinuous =
        (0U != (transfer->configFlags & (uint32_t)kDSPI_MasterPcsContinuous)) ? true : false;
    handle->command = DSPI_MasterGetFormattedCommand(&(commandStruct));

    commandStruct.isEndOfQueue = true;
    commandStruct.isPcsContinuous =
        (0U != (transfer->configFlags & (uint32_t)kDSPI_MasterActiveAfterTransfer)) ? true : false;
    handle->lastCommand = DSPI_MasterGetFormattedCommand(&(commandStruct));

    handle->bitsPerFrame = ((base->CTAR[commandStruct.whichCtar] & SPI_CTAR_FMSZ_MASK) >> SPI_CTAR_FMSZ_SHIFT) + 1U;

    tmpMCR = base->MCR;
    if ((0U != (tmpMCR & SPI_MCR_DIS_RXF_MASK)) || (0U != (tmpMCR & SPI_MCR_DIS_TXF_MASK)))
    {
        handle->fifoSize = 1U;
    }
    else
    {
        handle->fifoSize = (uint8_t)FSL_FEATURE_DSPI_FIFO_SIZEn(base);
    }
    handle->txData                    = transfer->txData;
    handle->rxData                    = transfer->rxData;
    handle->remainingSendByteCount    = transfer->dataSize;
    handle->remainingReceiveByteCount = transfer->dataSize;
    handle->totalByteCount            = transfer->dataSize;

    /* If using a shared RX/TX DMA request, then this limits the amount of data we can transfer
     * due to the linked channel. The max bytes is 511 if 8-bit/frame or 1022 if 16-bit/frame
     */
    if (transfer->dataSize > DSPI_EDMA_MAX_TRANSFER_SIZE(base, (handle->bitsPerFrame)))
    {
        handle->state = (uint8_t)kDSPI_Idle;
        return kStatus_DSPI_OutOfRange;
    }

    /*The data size should be even if the bitsPerFrame is greater than 8 (that is 2 bytes per frame in dspi) */
    if ((0U != (transfer->dataSize & 0x1U)) && (handle->bitsPerFrame > 8U))
    {
        handle->state = (uint8_t)kDSPI_Idle;
        return kStatus_InvalidArgument;
    }

    DSPI_DisableDMA(base, (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);

    EDMA_SetCallback(handle->edmaRxRegToRxDataHandle, EDMA_DspiMasterCallback,
                     &s_dspiMasterEdmaPrivateHandle[instance]);

    /*
    (1)For DSPI instances with shared RX/TX DMA requests: Rx DMA request -> channel_A -> channel_B-> channel_C.
    channel_A minor link to channel_B , channel_B minor link to channel_C.

    Already pushed 1 or 2 data in SPI_PUSHR , then start the DMA tansfer.
    channel_A:SPI_POPR to rxData,
    channel_B:next txData to handle->command (low 16 bits),
    channel_C:handle->command (32 bits) to SPI_PUSHR, and use the scatter/gather to transfer the last data
    (handle->lastCommand to SPI_PUSHR).

    (2)For DSPI instances with separate RX and TX DMA requests:
    Rx DMA request -> channel_A
    Tx DMA request -> channel_C -> channel_B .
    channel_C major link to channel_B.
    So need prepare the first data in "intermediary"  before the DMA
    transfer and then channel_B is used to prepare the next data to "intermediary"

    channel_A:SPI_POPR to rxData,
    channel_C: handle->command (32 bits) to SPI_PUSHR,
    channel_B: next txData to handle->command (low 16 bits), and use the scatter/gather to prepare the last data
    (handle->lastCommand to handle->Command).
    */

    /*If dspi has separate dma request , prepare the first data in "intermediary" .
    else (dspi has shared dma request) , send first 2 data if there is fifo or send first 1 data if there is no fifo*/
    if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        /* For DSPI instances with separate RX/TX DMA requests, we'll use the TX DMA request to
         * trigger the TX DMA channel and RX DMA request to trigger the RX DMA channel
         */

        /*Prepare the firt data*/
        if (handle->bitsPerFrame > 8U)
        {
            /* If it's the last word */
            if (handle->remainingSendByteCount <= 2U)
            {
                if (NULL != handle->txData)
                {
                    wordToSend = *(handle->txData);
                    ++handle->txData; /* increment to next data byte */
                    wordToSend |= (uint16_t)(*(handle->txData)) << 8U;
                }
                else
                {
                    wordToSend = (((uint16_t)dummyData << 8U) | (uint16_t)dummyData);
                }
                handle->lastCommand = (handle->lastCommand & 0xffff0000U) | wordToSend;
                handle->command     = handle->lastCommand;
            }
            else /* For all words except the last word , frame > 8bits */
            {
                if (NULL != handle->txData)
                {
                    wordToSend = *(handle->txData);
                    ++handle->txData; /* increment to next data byte */
                    wordToSend |= (uint16_t)(*(handle->txData)) << 8U;
                    ++handle->txData; /* increment to next data byte */
                }
                else
                {
                    wordToSend = (((uint16_t)dummyData << 8U) | (uint16_t)dummyData);
                }
                handle->command = (handle->command & 0xffff0000U) | wordToSend;
            }
        }
        else /* Optimized for bits/frame less than or equal to one byte. */
        {
            if (NULL != handle->txData)
            {
                wordToSend = *(handle->txData);
                ++handle->txData; /* increment to next data word*/
            }
            else
            {
                wordToSend = dummyData;
            }

            if (handle->remainingSendByteCount == 1U)
            {
                handle->lastCommand = (handle->lastCommand & 0xffff0000U) | wordToSend;
                handle->command     = handle->lastCommand;
            }
            else
            {
                handle->command = (handle->command & 0xffff0000U) | wordToSend;
            }
        }
    }

    else /*dspi has shared dma request*/
    {
        /* For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
         * trigger ongoing transfers and will link to the TX DMA channel from the RX DMA channel.
         */

        /* If bits/frame is greater than one byte */
        if (handle->bitsPerFrame > 8U)
        {
            while ((uint32_t)kDSPI_TxFifoFillRequestFlag ==
                   (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
            {
                if (handle->remainingSendByteCount <= 2U)
                {
                    if (NULL != handle->txData)
                    {
                        wordToSend = *(handle->txData);
                        ++handle->txData;
                        wordToSend |= (uint16_t)(*(handle->txData)) << 8U;
                    }
                    else
                    {
                        wordToSend = (((uint16_t)dummyData << 8U) | (uint16_t)dummyData);
                    }
                    handle->remainingSendByteCount = 0;
                    base->PUSHR                    = (handle->lastCommand & 0xffff0000U) | wordToSend;
                }
                /* For all words except the last word */
                else
                {
                    if (NULL != handle->txData)
                    {
                        wordToSend = *(handle->txData);
                        ++handle->txData;
                        wordToSend |= (uint16_t)(*(handle->txData)) << 8U;
                        ++handle->txData;
                    }
                    else
                    {
                        wordToSend = (((uint16_t)dummyData << 8U) | (uint16_t)dummyData);
                    }
                    handle->remainingSendByteCount -= 2U;
                    base->PUSHR = (handle->command & 0xffff0000U) | wordToSend;
                }

                /* Try to clear the TFFF; if the TX FIFO is full this will clear */
                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

                dataAlreadyFed += 2U;

                /* exit loop if send count is zero, else update local variables for next loop */
                if ((handle->remainingSendByteCount == 0U) || (dataAlreadyFed == (dataFedMax * 2U)))
                {
                    break;
                }
            } /* End of TX FIFO fill while loop */
        }
        else /* Optimized for bits/frame less than or equal to one byte. */
        {
            while ((uint32_t)kDSPI_TxFifoFillRequestFlag ==
                   (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
            {
                if (NULL != handle->txData)
                {
                    wordToSend = *(handle->txData);
                    ++handle->txData;
                }
                else
                {
                    wordToSend = dummyData;
                }

                if (handle->remainingSendByteCount == 1U)
                {
                    base->PUSHR = (handle->lastCommand & 0xffff0000U) | wordToSend;
                }
                else
                {
                    base->PUSHR = (handle->command & 0xffff0000U) | wordToSend;
                }

                /* Try to clear the TFFF; if the TX FIFO is full this will clear */
                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

                --handle->remainingSendByteCount;

                dataAlreadyFed++;

                /* exit loop if send count is zero, else update local variables for next loop */
                if ((handle->remainingSendByteCount == 0U) || (dataAlreadyFed == dataFedMax))
                {
                    break;
                }
            } /* End of TX FIFO fill while loop */
        }
    }

    /***channel_A *** used for carry the data from Rx_Data_Register(POPR) to User_Receive_Buffer(rxData)*/
    EDMA_ResetChannel(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel);

    transferConfigA.srcAddr   = (uint32_t)rxAddr;
    transferConfigA.srcOffset = 0;

    if (NULL != handle->rxData)
    {
        transferConfigA.destAddr   = (uint32_t) & (handle->rxData[0]);
        transferConfigA.destOffset = 1;
    }
    else
    {
        transferConfigA.destAddr   = (uint32_t) & (handle->rxBuffIfNull);
        transferConfigA.destOffset = 0;
    }

    transferConfigA.destTransferSize = kEDMA_TransferSize1Bytes;

    if (handle->bitsPerFrame <= 8U)
    {
        transferConfigA.srcTransferSize = kEDMA_TransferSize1Bytes;
        transferConfigA.minorLoopBytes  = 1;
        transferConfigA.majorLoopCounts = handle->remainingReceiveByteCount;
    }
    else
    {
        transferConfigA.srcTransferSize = kEDMA_TransferSize2Bytes;
        transferConfigA.minorLoopBytes  = 2;
        transferConfigA.majorLoopCounts = handle->remainingReceiveByteCount / 2U;
    }

    /* Store the initially configured eDMA minor byte transfer count into the DSPI handle */
    handle->nbytes = (uint8_t)(transferConfigA.minorLoopBytes);

    EDMA_SetTransferConfig(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                           (const edma_transfer_config_t *)(uint32_t)&transferConfigA, NULL);
    EDMA_EnableChannelInterrupts(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                 (uint32_t)kEDMA_MajorInterruptEnable);

    if (handle->remainingSendByteCount == 0U)
    {
        EDMA_StartTransfer(handle->edmaRxRegToRxDataHandle);
        DSPI_EnableDMA(base, (uint32_t)kDSPI_RxDmaEnable);
        DSPI_StartTransfer(base);
        return kStatus_Success;
    }

    tmpRemainingSendByteCount = handle->remainingSendByteCount;
    /*Calculate the last data : handle->lastCommand*/
    if (((tmpRemainingSendByteCount > 0U) && (1U != (uint8_t)FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))) ||
        ((((tmpRemainingSendByteCount > 1U) && (handle->bitsPerFrame <= 8U)) ||
          ((tmpRemainingSendByteCount > 2U) && (handle->bitsPerFrame > 8U))) &&
         (1U == (uint8_t)FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))))
    {
        if (NULL != handle->txData)
        {
            uint32_t bufferIndex = 0;

            if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
            {
                if (handle->bitsPerFrame <= 8U)
                {
                    bufferIndex = handle->remainingSendByteCount - 1U;
                }
                else
                {
                    bufferIndex = handle->remainingSendByteCount - 2U;
                }
            }
            else
            {
                bufferIndex = handle->remainingSendByteCount;
            }

            uint32_t tmpLastCommand = handle->lastCommand;
            uint8_t *tmpTxData      = handle->txData;

            if (handle->bitsPerFrame <= 8U)
            {
                tmpLastCommand = (tmpLastCommand & 0xffff0000U) | tmpTxData[bufferIndex - 1U];
            }
            else
            {
                tmpLastCommand = (tmpLastCommand & 0xffff0000U) | ((uint32_t)tmpTxData[bufferIndex - 1U] << 8U) |
                                 tmpTxData[bufferIndex - 2U];
            }

            handle->lastCommand = tmpLastCommand;
        }
        else
        {
            if (handle->bitsPerFrame <= 8U)
            {
                wordToSend = dummyData;
            }
            else
            {
                wordToSend = (((uint16_t)dummyData << 8U) | (uint16_t)dummyData);
            }
            handle->lastCommand = (handle->lastCommand & 0xffff0000U) | wordToSend;
        }
    }

/* The feature of GASKET is that the SPI supports 8-bit or 16-bit writes to the PUSH TX FIFO,
 * allowing a single write to the command word followed by multiple writes to the transmit word.
 * The TX FIFO will save the last command word written, and convert a 8-bit/16-bit write to the
 * transmit word into a 32-bit write that pushes both the command word and transmit word into
 * the TX FIFO (PUSH TX FIFO Register In Master Mode)
 * So, if this feature is supported, we can use use one channel to carry the receive data from
 * receive regsiter to user data buffer, use the other channel to carry the data from user data buffer
 * to transmit register,and use the scatter/gather function to prepare the last data.
 * That is to say, if GASKET feature is supported, we can use only two channels for tansferring data.
 */
#if defined(FSL_FEATURE_DSPI_HAS_GASKET) && FSL_FEATURE_DSPI_HAS_GASKET
    /*  For DSPI instances with separate RX and TX DMA requests: use the scatter/gather to prepare the last data
     * (handle->lastCommand) to PUSHR register.
     */

    EDMA_ResetChannel(handle->edmaIntermediaryToTxRegHandle->base, handle->edmaIntermediaryToTxRegHandle->channel);

    if ((1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base)) ||
        ((handle->remainingSendByteCount > 0) && (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))))
    {
        transferConfigB.srcAddr          = (uint32_t) & (handle->lastCommand);
        transferConfigB.destAddr         = (uint32_t)txAddr;
        transferConfigB.srcTransferSize  = kEDMA_TransferSize4Bytes;
        transferConfigB.destTransferSize = kEDMA_TransferSize4Bytes;
        transferConfigB.srcOffset        = 0;
        transferConfigB.destOffset       = 0;
        transferConfigB.minorLoopBytes   = 4;
        transferConfigB.majorLoopCounts  = 1;

        EDMA_TcdReset(softwareTCD);
        EDMA_TcdSetTransferConfig(softwareTCD, &transferConfigB, NULL);
    }

    /*User_Send_Buffer(txData) to PUSHR register. */
    if (((handle->remainingSendByteCount > 2U) && (handle->bitsPerFrame <= 8U)) ||
        ((handle->remainingSendByteCount > 4U) && (handle->bitsPerFrame > 8U)))
    {
        if (handle->txData)
        {
            if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
            {
                /* For DSPI with separate RX and TX DMA requests, one frame data has been carry
                 * to handle->command, so need to reduce the pointer of txData.
                 */
                transferConfigB.srcAddr =
                    (uint32_t)((uint8_t *)(handle->txData) - ((handle->bitsPerFrame <= 8U) ? (1U) : (2U)));
                transferConfigB.srcOffset = 1;
            }
            else
            {
                /* For DSPI with shared RX and TX DMA requests, one or two frame data have been carry
                 * to PUSHR register, so no need to change the pointer of txData.
                 */
                transferConfigB.srcAddr   = (uint32_t)((uint8_t *)(handle->txData));
                transferConfigB.srcOffset = 1;
            }
        }
        else
        {
            transferConfigB.srcAddr   = (uint32_t)(&handle->txBuffIfNull);
            transferConfigB.srcOffset = 0;
        }

        transferConfigB.destAddr   = (uint32_t)txAddr;
        transferConfigB.destOffset = 0;

        transferConfigB.srcTransferSize = kEDMA_TransferSize1Bytes;

        if (handle->bitsPerFrame <= 8U)
        {
            transferConfigB.destTransferSize = kEDMA_TransferSize1Bytes;
            transferConfigB.minorLoopBytes   = 1;

            transferConfigB.majorLoopCounts = handle->remainingSendByteCount - 1U;
        }
        else
        {
            transferConfigB.destTransferSize = kEDMA_TransferSize2Bytes;
            transferConfigB.minorLoopBytes   = 2;
            transferConfigB.majorLoopCounts  = (handle->remainingSendByteCount / 2U) - 1U;
        }

        EDMA_SetTransferConfig(handle->edmaIntermediaryToTxRegHandle->base,
                               handle->edmaIntermediaryToTxRegHandle->channel, &transferConfigB, softwareTCD);
    }
    /* If only one word to transmit, only carry the lastcommand. */
    else
    {
        EDMA_SetTransferConfig(handle->edmaIntermediaryToTxRegHandle->base,
                               handle->edmaIntermediaryToTxRegHandle->channel, &transferConfigB, NULL);
    }

    /*Start the EDMA channel_A , channel_C. */
    EDMA_StartTransfer(handle->edmaRxRegToRxDataHandle);
    EDMA_StartTransfer(handle->edmaIntermediaryToTxRegHandle);

    /* Set the channel link.
     * For DSPI instances with shared TX and RX DMA requests, setup channel minor link, first receive data from the
     * receive register, and then carry transmit data to PUSHER register.
     * For DSPI instance with separate TX and RX DMA requests, there is no need to set up channel link.
     */
    if (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        /*Set channel priority*/
        uint8_t channelPriorityLow  = handle->edmaRxRegToRxDataHandle->channel;
        uint8_t channelPriorityHigh = handle->edmaIntermediaryToTxRegHandle->channel;
        uint8_t t                   = 0;

        if (channelPriorityLow > channelPriorityHigh)
        {
            t                   = channelPriorityLow;
            channelPriorityLow  = channelPriorityHigh;
            channelPriorityHigh = t;
        }

        edma_channel_Preemption_config_t preemption_config_t;
        preemption_config_t.enableChannelPreemption = true;
        preemption_config_t.enablePreemptAbility    = true;
        preemption_config_t.channelPriority         = channelPriorityLow;

        EDMA_SetChannelPreemptionConfig(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                        &preemption_config_t);

        preemption_config_t.channelPriority = channelPriorityHigh;
        EDMA_SetChannelPreemptionConfig(handle->edmaIntermediaryToTxRegHandle->base,
                                        handle->edmaIntermediaryToTxRegHandle->channel, &preemption_config_t);
        /*if there is Rx DMA request , carry the 32bits data (handle->command) to user data first , then link to
          channelC to carry the next data to PUSHER register.(txData to PUSHER) */
        if (handle->remainingSendByteCount > 0U)
        {
            EDMA_SetChannelLink(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                kEDMA_MinorLink, handle->edmaIntermediaryToTxRegHandle->channel);
        }
    }

    DSPI_EnableDMA(base, kDSPI_RxDmaEnable | kDSPI_TxDmaEnable);

    /* Setup control info to PUSHER register. */
    *((uint16_t *)&(base->PUSHR) + 1) = (handle->command >> 16U);
#else

    /***channel_B *** used for carry the data from User_Send_Buffer to "intermediary" because the SPIx_PUSHR should
    write the 32bits at once time . Then use channel_C to carry the "intermediary" to SPIx_PUSHR. Note that the
    SPIx_PUSHR upper 16 bits are the "command" and the low 16bits are data */

    EDMA_ResetChannel(handle->edmaTxDataToIntermediaryHandle->base, handle->edmaTxDataToIntermediaryHandle->channel);

    /*For DSPI instances with separate RX and TX DMA requests: use the scatter/gather to prepare the last data
     * (handle->lastCommand) to handle->Command*/
    if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        transferConfigB.srcAddr          = (uint32_t) & (handle->lastCommand);
        transferConfigB.destAddr         = (uint32_t) & (handle->command);
        transferConfigB.srcTransferSize  = kEDMA_TransferSize4Bytes;
        transferConfigB.destTransferSize = kEDMA_TransferSize4Bytes;
        transferConfigB.srcOffset        = 0;
        transferConfigB.destOffset       = 0;
        transferConfigB.minorLoopBytes   = 4;
        transferConfigB.majorLoopCounts  = 1;

        EDMA_TcdReset(softwareTCD);
        EDMA_TcdSetTransferConfig(softwareTCD, (const edma_transfer_config_t *)(uint32_t)&transferConfigB, NULL);
    }

    tmpRemainingSendByteCount = handle->remainingSendByteCount;
    /*User_Send_Buffer(txData) to intermediary(handle->command)*/
    if (((((tmpRemainingSendByteCount > 2U) && (handle->bitsPerFrame <= 8U)) ||
          ((tmpRemainingSendByteCount > 4U) && (handle->bitsPerFrame > 8U))) &&
         (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))) ||
        (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base)))
    {
        if (NULL != handle->txData)
        {
            transferConfigB.srcAddr   = (uint32_t)(handle->txData);
            transferConfigB.srcOffset = 1;
        }
        else
        {
            transferConfigB.srcAddr   = (uint32_t)(&handle->txBuffIfNull);
            transferConfigB.srcOffset = 0;
        }

        transferConfigB.destAddr   = (uint32_t)(&handle->command);
        transferConfigB.destOffset = 0;

        transferConfigB.srcTransferSize = kEDMA_TransferSize1Bytes;

        if (handle->bitsPerFrame <= 8U)
        {
            transferConfigB.destTransferSize = kEDMA_TransferSize1Bytes;
            transferConfigB.minorLoopBytes   = 1;

            if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
            {
                transferConfigB.majorLoopCounts = handle->remainingSendByteCount - 2U;
            }
            else
            {
                /*Only enable channel_B minorlink to channel_C , so need to add one count due to the last time is
                majorlink , the majorlink would not trigger the channel_C*/
                transferConfigB.majorLoopCounts = handle->remainingSendByteCount + 1U;
            }
        }
        else
        {
            transferConfigB.destTransferSize = kEDMA_TransferSize2Bytes;
            transferConfigB.minorLoopBytes   = 2;
            if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
            {
                transferConfigB.majorLoopCounts = handle->remainingSendByteCount / 2U - 2U;
            }
            else
            {
                /*Only enable channel_B minorlink to channel_C , so need to add one count due to the last time is
                 * majorlink*/
                transferConfigB.majorLoopCounts = handle->remainingSendByteCount / 2U + 1U;
            }
        }

        if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
        {
            EDMA_SetTransferConfig(handle->edmaTxDataToIntermediaryHandle->base,
                                   handle->edmaTxDataToIntermediaryHandle->channel,
                                   (const edma_transfer_config_t *)(uint32_t)&transferConfigB, softwareTCD);
            EDMA_EnableAutoStopRequest(handle->edmaIntermediaryToTxRegHandle->base,
                                       handle->edmaIntermediaryToTxRegHandle->channel, false);
        }
        else
        {
            EDMA_SetTransferConfig(handle->edmaTxDataToIntermediaryHandle->base,
                                   handle->edmaTxDataToIntermediaryHandle->channel,
                                   (const edma_transfer_config_t *)(uint32_t)&transferConfigB, NULL);
        }
    }
    else
    {
        EDMA_SetTransferConfig(handle->edmaTxDataToIntermediaryHandle->base,
                               handle->edmaTxDataToIntermediaryHandle->channel,
                               (const edma_transfer_config_t *)(uint32_t)&transferConfigB, NULL);
    }

    /***channel_C ***carry the "intermediary" to SPIx_PUSHR. used the edma Scatter Gather function on channel_C to
    handle the last data */

    edma_transfer_config_t transferConfigC = {0};

    EDMA_ResetChannel(handle->edmaIntermediaryToTxRegHandle->base, handle->edmaIntermediaryToTxRegHandle->channel);

    tmpRemainingSendByteCount = handle->remainingSendByteCount;
    /*For DSPI instances with shared RX/TX DMA requests: use the scatter/gather to prepare the last data
     * (handle->lastCommand) to SPI_PUSHR*/
    if (((1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base)) && (tmpRemainingSendByteCount > 0U)))
    {
        transferConfigC.srcAddr          = (uint32_t) & (handle->lastCommand);
        transferConfigC.destAddr         = (uint32_t)txAddr;
        transferConfigC.srcTransferSize  = kEDMA_TransferSize4Bytes;
        transferConfigC.destTransferSize = kEDMA_TransferSize4Bytes;
        transferConfigC.srcOffset        = 0;
        transferConfigC.destOffset       = 0;
        transferConfigC.minorLoopBytes   = 4;
        transferConfigC.majorLoopCounts  = 1;

        EDMA_TcdReset(softwareTCD);
        EDMA_TcdSetTransferConfig(softwareTCD, (const edma_transfer_config_t *)(uint32_t)&transferConfigC, NULL);
    }

    tmpRemainingSendByteCount = handle->remainingSendByteCount;
    if (((tmpRemainingSendByteCount > 1U) && (handle->bitsPerFrame <= 8U)) ||
        ((tmpRemainingSendByteCount > 2U) && (handle->bitsPerFrame > 8U)) ||
        (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base)))
    {
        transferConfigC.srcAddr  = (uint32_t)(&(handle->command));
        transferConfigC.destAddr = (uint32_t)txAddr;

        transferConfigC.srcTransferSize  = kEDMA_TransferSize4Bytes;
        transferConfigC.destTransferSize = kEDMA_TransferSize4Bytes;
        transferConfigC.srcOffset        = 0;
        transferConfigC.destOffset       = 0;
        transferConfigC.minorLoopBytes   = 4;
        if (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
        {
            if (handle->bitsPerFrame <= 8U)
            {
                transferConfigC.majorLoopCounts = handle->remainingSendByteCount - 1U;
            }
            else
            {
                transferConfigC.majorLoopCounts = (handle->remainingSendByteCount / 2U) - 1U;
            }

            EDMA_SetTransferConfig(handle->edmaIntermediaryToTxRegHandle->base,
                                   handle->edmaIntermediaryToTxRegHandle->channel,
                                   (const edma_transfer_config_t *)(uint32_t)&transferConfigC, softwareTCD);
        }
        else
        {
            transferConfigC.majorLoopCounts = 1;

            EDMA_SetTransferConfig(handle->edmaIntermediaryToTxRegHandle->base,
                                   handle->edmaIntermediaryToTxRegHandle->channel,
                                   (const edma_transfer_config_t *)(uint32_t)&transferConfigC, NULL);
        }

        EDMA_EnableAutoStopRequest(handle->edmaIntermediaryToTxRegHandle->base,
                                   handle->edmaIntermediaryToTxRegHandle->channel, false);
    }
    else
    {
        EDMA_SetTransferConfig(handle->edmaIntermediaryToTxRegHandle->base,
                               handle->edmaIntermediaryToTxRegHandle->channel,
                               (const edma_transfer_config_t *)(uint32_t)&transferConfigC, NULL);
    }

    /*Start the EDMA channel_A , channel_B , channel_C transfer*/
    EDMA_StartTransfer(handle->edmaRxRegToRxDataHandle);
    EDMA_StartTransfer(handle->edmaTxDataToIntermediaryHandle);
    EDMA_StartTransfer(handle->edmaIntermediaryToTxRegHandle);

    /*Set channel priority*/
    uint8_t channelPriorityLow  = handle->edmaRxRegToRxDataHandle->channel;
    uint8_t channelPriorityMid  = handle->edmaTxDataToIntermediaryHandle->channel;
    uint8_t channelPriorityHigh = handle->edmaIntermediaryToTxRegHandle->channel;
    uint8_t t                   = 0;
    if (channelPriorityLow > channelPriorityMid)
    {
        t                  = channelPriorityLow;
        channelPriorityLow = channelPriorityMid;
        channelPriorityMid = t;
    }

    if (channelPriorityLow > channelPriorityHigh)
    {
        t                   = channelPriorityLow;
        channelPriorityLow  = channelPriorityHigh;
        channelPriorityHigh = t;
    }

    if (channelPriorityMid > channelPriorityHigh)
    {
        t                   = channelPriorityMid;
        channelPriorityMid  = channelPriorityHigh;
        channelPriorityHigh = t;
    }
    edma_channel_Preemption_config_t preemption_config_t;
    preemption_config_t.enableChannelPreemption = true;
    preemption_config_t.enablePreemptAbility    = true;
    preemption_config_t.channelPriority         = channelPriorityLow;

    if (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        EDMA_SetChannelPreemptionConfig(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);

        preemption_config_t.channelPriority = channelPriorityMid;
        EDMA_SetChannelPreemptionConfig(handle->edmaTxDataToIntermediaryHandle->base,
                                        handle->edmaTxDataToIntermediaryHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);

        preemption_config_t.channelPriority = channelPriorityHigh;
        EDMA_SetChannelPreemptionConfig(handle->edmaIntermediaryToTxRegHandle->base,
                                        handle->edmaIntermediaryToTxRegHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);
    }
    else
    {
        EDMA_SetChannelPreemptionConfig(handle->edmaIntermediaryToTxRegHandle->base,
                                        handle->edmaIntermediaryToTxRegHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);

        preemption_config_t.channelPriority = channelPriorityMid;
        EDMA_SetChannelPreemptionConfig(handle->edmaTxDataToIntermediaryHandle->base,
                                        handle->edmaTxDataToIntermediaryHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);

        preemption_config_t.channelPriority = channelPriorityHigh;
        EDMA_SetChannelPreemptionConfig(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);
    }

    /*Set the channel link.*/
    if (1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        /*if there is Tx DMA request , carry the 32bits data (handle->command) to PUSHR first , then link to channelB
        to prepare the next 32bits data (txData to handle->command) */
        if (handle->remainingSendByteCount > 1U)
        {
            EDMA_SetChannelLink(handle->edmaIntermediaryToTxRegHandle->base,
                                handle->edmaIntermediaryToTxRegHandle->channel, kEDMA_MajorLink,
                                handle->edmaTxDataToIntermediaryHandle->channel);
        }

        DSPI_EnableDMA(base, (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);
    }
    else
    {
        if (handle->remainingSendByteCount > 0U)
        {
            EDMA_SetChannelLink(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                kEDMA_MinorLink, handle->edmaTxDataToIntermediaryHandle->channel);

            EDMA_SetChannelLink(handle->edmaTxDataToIntermediaryHandle->base,
                                handle->edmaTxDataToIntermediaryHandle->channel, kEDMA_MinorLink,
                                handle->edmaIntermediaryToTxRegHandle->channel);
        }

        DSPI_EnableDMA(base, (uint32_t)kDSPI_RxDmaEnable);
    }
#endif
    DSPI_StartTransfer(base);

    return kStatus_Success;
}

/*!
 * brief Transfers a block of data using a eDMA method.
 *
 * This function transfers data using eDNA, the transfer mechanism is half-duplex. This is a non-blocking function,
 * which returns right away. When all data is transferred, the callback function is called.
 *
 * param base DSPI base pointer
 * param handle A pointer to the dspi_master_edma_handle_t structure which stores the transfer state.
 * param transfer A pointer to the dspi_half_duplex_transfer_t structure.
 * return status of status_t.
 */
status_t DSPI_MasterHalfDuplexTransferEDMA(SPI_Type *base,
                                           dspi_master_edma_handle_t *handle,
                                           dspi_half_duplex_transfer_t *xfer)
{
    assert(NULL != xfer);
    assert(NULL != handle);
    dspi_transfer_t tempXfer = {0};
    status_t status;

    if (true == xfer->isTransmitFirst)
    {
        tempXfer.txData   = xfer->txData;
        tempXfer.rxData   = NULL;
        tempXfer.dataSize = xfer->txDataSize;
    }
    else
    {
        tempXfer.txData   = NULL;
        tempXfer.rxData   = xfer->rxData;
        tempXfer.dataSize = xfer->rxDataSize;
    }
    /* If the pcs pin keep assert between transmit and receive. */
    if (true == xfer->isPcsAssertInTransfer)
    {
        tempXfer.configFlags = (xfer->configFlags) | (uint32_t)kDSPI_MasterActiveAfterTransfer;
    }
    else
    {
        tempXfer.configFlags = (xfer->configFlags) & (~(uint32_t)kDSPI_MasterActiveAfterTransfer);
    }

    status = DSPI_MasterTransferBlocking(base, &tempXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    if (true == xfer->isTransmitFirst)
    {
        tempXfer.txData   = NULL;
        tempXfer.rxData   = xfer->rxData;
        tempXfer.dataSize = xfer->rxDataSize;
    }
    else
    {
        tempXfer.txData   = xfer->txData;
        tempXfer.rxData   = NULL;
        tempXfer.dataSize = xfer->txDataSize;
    }
    tempXfer.configFlags = xfer->configFlags;

    status = DSPI_MasterTransferEDMA(base, handle, &tempXfer);

    return status;
}
static void EDMA_DspiMasterCallback(edma_handle_t *edmaHandle,
                                    void *g_dspiEdmaPrivateHandle,
                                    bool transferDone,
                                    uint32_t tcds)
{
    assert(NULL != edmaHandle);
    assert(NULL != g_dspiEdmaPrivateHandle);

    dspi_master_edma_private_handle_t *dspiEdmaPrivateHandle;

    dspiEdmaPrivateHandle = (dspi_master_edma_private_handle_t *)g_dspiEdmaPrivateHandle;

    DSPI_DisableDMA((dspiEdmaPrivateHandle->base), (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);

    dspiEdmaPrivateHandle->handle->state = (uint8_t)kDSPI_Idle;

    if (NULL != dspiEdmaPrivateHandle->handle->callback)
    {
        dspiEdmaPrivateHandle->handle->callback(dspiEdmaPrivateHandle->base, dspiEdmaPrivateHandle->handle,
                                                kStatus_Success, dspiEdmaPrivateHandle->handle->userData);
    }
}

/*!
 * brief DSPI master aborts a transfer which is using eDMA.
 *
 * This function aborts a transfer which is using eDMA.
 *
 * param base DSPI peripheral base address.
 * param handle A pointer to the dspi_master_edma_handle_t structure which stores the transfer state.
 */
void DSPI_MasterTransferAbortEDMA(SPI_Type *base, dspi_master_edma_handle_t *handle)
{
    assert(NULL != handle);

    DSPI_StopTransfer(base);

    DSPI_DisableDMA(base, (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);

    EDMA_AbortTransfer(handle->edmaRxRegToRxDataHandle);
    EDMA_AbortTransfer(handle->edmaTxDataToIntermediaryHandle);
    EDMA_AbortTransfer(handle->edmaIntermediaryToTxRegHandle);

    handle->state = (uint8_t)kDSPI_Idle;
}

/*!
 * brief Gets the master eDMA transfer count.
 *
 * This function gets the master eDMA transfer count.
 *
 * param base DSPI peripheral base address.
 * param handle A pointer to the dspi_master_edma_handle_t structure which stores the transfer state.
 * param count A number of bytes transferred by the non-blocking transaction.
 * return status of status_t.
 */
status_t DSPI_MasterTransferGetCountEDMA(SPI_Type *base, dspi_master_edma_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state != (uint8_t)kDSPI_Busy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    size_t bytes;

    bytes = (uint32_t)handle->nbytes * EDMA_GetRemainingMajorLoopCount(handle->edmaRxRegToRxDataHandle->base,
                                                                       handle->edmaRxRegToRxDataHandle->channel);

    *count = handle->totalByteCount - bytes;

    return kStatus_Success;
}

/*!
 * brief Initializes the DSPI slave eDMA handle.
 *
 * This function initializes the DSPI eDMA handle which can be used for other DSPI transactional APIs.  Usually, for a
 * specified DSPI instance, call this API once to get the initialized handle.
 *
 * Note that DSPI eDMA has separated (RN and TX in 2 sources) or shared (RX  and TX are the same source) DMA request
 * source.
 * (1)For the separated DMA request source, enable and set the RX DMAMUX source for edmaRxRegToRxDataHandle and
 * TX DMAMUX source for edmaTxDataToTxRegHandle.
 * (2)For the shared DMA request source,  enable and set the RX/RX DMAMUX source for the edmaRxRegToRxDataHandle.
 *
 * param base DSPI peripheral base address.
 * param handle DSPI handle pointer to dspi_slave_edma_handle_t.
 * param callback DSPI callback.
 * param userData A callback function parameter.
 * param edmaRxRegToRxDataHandle edmaRxRegToRxDataHandle pointer to edma_handle_t.
 * param edmaTxDataToTxRegHandle edmaTxDataToTxRegHandle pointer to edma_handle_t.
 */
void DSPI_SlaveTransferCreateHandleEDMA(SPI_Type *base,
                                        dspi_slave_edma_handle_t *handle,
                                        dspi_slave_edma_transfer_callback_t callback,
                                        void *userData,
                                        edma_handle_t *edmaRxRegToRxDataHandle,
                                        edma_handle_t *edmaTxDataToTxRegHandle)
{
    assert(NULL != handle);
    assert(NULL != edmaRxRegToRxDataHandle);
    assert(NULL != edmaTxDataToTxRegHandle);

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    uint32_t instance = DSPI_GetInstance(base);

    s_dspiSlaveEdmaPrivateHandle[instance].base   = base;
    s_dspiSlaveEdmaPrivateHandle[instance].handle = handle;

    handle->callback = callback;
    handle->userData = userData;

    handle->edmaRxRegToRxDataHandle = edmaRxRegToRxDataHandle;
    handle->edmaTxDataToTxRegHandle = edmaTxDataToTxRegHandle;
}

/*!
 * brief DSPI slave transfer data using eDMA.
 *
 * This function transfers data using eDMA. This is a non-blocking function, which returns right away. When all data
 * is transferred, the callback function is called.
 * Note that the slave eDMA transfer doesn't support transfer_size is 1 when the bitsPerFrame is greater
 * than eight.
 *
 * note The max transfer size of each transfer depends on whether the instance's Tx/Rx shares the same DMA request. If
 * FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(x) is true, then the max transfer size is 32767 datawidth of data,
 * otherwise is 511.
 *
 * param base DSPI peripheral base address.
 * param handle A pointer to the dspi_slave_edma_handle_t structure which stores the transfer state.
 * param transfer A pointer to the dspi_transfer_t structure.
 * return status of status_t.
 */
status_t DSPI_SlaveTransferEDMA(SPI_Type *base, dspi_slave_edma_handle_t *handle, dspi_transfer_t *transfer)
{
    assert(NULL != handle);
    assert(NULL != transfer);

    /* If send/receive length is zero */
    if (transfer->dataSize == 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* If both send buffer and receive buffer is null */
    if ((NULL == (transfer->txData)) && (NULL == (transfer->rxData)))
    {
        return kStatus_InvalidArgument;
    }

    /* Check that we're not busy.*/
    if (handle->state == (uint8_t)kDSPI_Busy)
    {
        return kStatus_DSPI_Busy;
    }

    handle->state = (uint8_t)kDSPI_Busy;

    uint32_t instance = DSPI_GetInstance(base);
    uint8_t whichCtar = (uint8_t)((transfer->configFlags & DSPI_SLAVE_CTAR_MASK) >> DSPI_SLAVE_CTAR_SHIFT);
    handle->bitsPerFrame =
        (((base->CTAR_SLAVE[whichCtar]) & SPI_CTAR_SLAVE_FMSZ_MASK) >> SPI_CTAR_SLAVE_FMSZ_SHIFT) + 1U;

    /* If using a shared RX/TX DMA request, then this limits the amount of data we can transfer
     * due to the linked channel. The max bytes is 511 if 8-bit/frame or 1022 if 16-bit/frame
     */
    if (transfer->dataSize > DSPI_EDMA_MAX_TRANSFER_SIZE(base, (handle->bitsPerFrame)))
    {
        handle->state = (uint8_t)kDSPI_Idle;
        return kStatus_DSPI_OutOfRange;
    }

    /*The data size should be even if the bitsPerFrame is greater than 8 (that is 2 bytes per frame in dspi) */
    if ((0U != (transfer->dataSize & 0x1U)) && (handle->bitsPerFrame > 8U))
    {
        handle->state = (uint8_t)kDSPI_Idle;
        return kStatus_InvalidArgument;
    }

    EDMA_SetCallback(handle->edmaRxRegToRxDataHandle, EDMA_DspiSlaveCallback, &s_dspiSlaveEdmaPrivateHandle[instance]);

    /* Store transfer information */
    handle->txData                    = transfer->txData;
    handle->rxData                    = transfer->rxData;
    handle->remainingSendByteCount    = transfer->dataSize;
    handle->remainingReceiveByteCount = transfer->dataSize;
    handle->totalByteCount            = transfer->dataSize;

    uint32_t wordToSend    = 0;
    uint8_t dummyData      = DSPI_GetDummyDataInstance(base);
    uint8_t dataAlreadyFed = 0;
    uint8_t dataFedMax     = 2;

    uint32_t rxAddr = DSPI_GetRxRegisterAddress(base);
    uint32_t txAddr = DSPI_SlaveGetTxRegisterAddress(base);

    edma_transfer_config_t transferConfigA = {0};
    edma_transfer_config_t transferConfigC = {0};

    DSPI_StopTransfer(base);

    DSPI_FlushFifo(base, true, true);
    DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_AllStatusFlag);

    DSPI_DisableDMA(base, (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);

    DSPI_StartTransfer(base);

    /*if dspi has separate dma request , need not prepare data first .
    else (dspi has shared dma request) , send first 2 data into fifo if there is fifo or send first 1 data to
    slaveGetTxRegister if there is no fifo*/
    if (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        /* For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
         * trigger ongoing transfers and will link to the TX DMA channel from the RX DMA channel.
         */
        /* If bits/frame is greater than one byte */
        if (handle->bitsPerFrame > 8U)
        {
            while ((uint32_t)kDSPI_TxFifoFillRequestFlag ==
                   (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
            {
                if (NULL != handle->txData)
                {
                    wordToSend = *(handle->txData);
                    ++handle->txData; /* Increment to next data byte */

                    wordToSend |= (unsigned)(*(handle->txData)) << 8U;
                    ++handle->txData; /* Increment to next data byte */
                }
                else
                {
                    wordToSend = ((uint32_t)dummyData << 8U) | dummyData;
                }
                handle->remainingSendByteCount -= 2U; /* decrement remainingSendByteCount by 2 */
                base->PUSHR_SLAVE = wordToSend;

                /* Try to clear the TFFF; if the TX FIFO is full this will clear */
                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);

                dataAlreadyFed += 2U;

                /* Exit loop if send count is zero, else update local variables for next loop */
                if ((handle->remainingSendByteCount == 0U) || (dataAlreadyFed == (dataFedMax * 2U)))
                {
                    break;
                }
            } /* End of TX FIFO fill while loop */
        }
        else /* Optimized for bits/frame less than or equal to one byte. */
        {
            while ((uint32_t)kDSPI_TxFifoFillRequestFlag ==
                   (DSPI_GetStatusFlags(base) & (uint32_t)kDSPI_TxFifoFillRequestFlag))
            {
                if (NULL != handle->txData)
                {
                    wordToSend = *(handle->txData);
                    /* Increment to next data word*/
                    ++handle->txData;
                }
                else
                {
                    wordToSend = dummyData;
                }

                base->PUSHR_SLAVE = wordToSend;

                /* Try to clear the TFFF; if the TX FIFO is full this will clear */
                DSPI_ClearStatusFlags(base, (uint32_t)kDSPI_TxFifoFillRequestFlag);
                /* Decrement remainingSendByteCount*/
                --handle->remainingSendByteCount;

                dataAlreadyFed++;

                /* Exit loop if send count is zero, else update local variables for next loop */
                if ((handle->remainingSendByteCount == 0U) || (dataAlreadyFed == dataFedMax))
                {
                    break;
                }
            } /* End of TX FIFO fill while loop */
        }
    }

    /***channel_A *** used for carry the data from Rx_Data_Register(POPR) to User_Receive_Buffer*/
    if (handle->remainingReceiveByteCount > 0U)
    {
        EDMA_ResetChannel(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel);

        transferConfigA.srcAddr   = (uint32_t)rxAddr;
        transferConfigA.srcOffset = 0;

        if (NULL != handle->rxData)
        {
            transferConfigA.destAddr   = (uint32_t) & (handle->rxData[0]);
            transferConfigA.destOffset = 1;
        }
        else
        {
            transferConfigA.destAddr   = (uint32_t) & (handle->rxBuffIfNull);
            transferConfigA.destOffset = 0;
        }

        transferConfigA.destTransferSize = kEDMA_TransferSize1Bytes;

        if (handle->bitsPerFrame <= 8U)
        {
            transferConfigA.srcTransferSize = kEDMA_TransferSize1Bytes;
            transferConfigA.minorLoopBytes  = 1;
            transferConfigA.majorLoopCounts = handle->remainingReceiveByteCount;
        }
        else
        {
            transferConfigA.srcTransferSize = kEDMA_TransferSize2Bytes;
            transferConfigA.minorLoopBytes  = 2;
            transferConfigA.majorLoopCounts = handle->remainingReceiveByteCount / 2U;
        }

        /* Store the initially configured eDMA minor byte transfer count into the DSPI handle */
        handle->nbytes = (uint8_t)(transferConfigA.minorLoopBytes);

        EDMA_SetTransferConfig(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                               (const edma_transfer_config_t *)(uint32_t)&transferConfigA, NULL);
        EDMA_EnableChannelInterrupts(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                     (uint32_t)kEDMA_MajorInterruptEnable);
    }

    if (handle->remainingSendByteCount > 0U)
    {
        /***channel_C *** used for carry the data from User_Send_Buffer to Tx_Data_Register(PUSHR_SLAVE)*/
        EDMA_ResetChannel(handle->edmaTxDataToTxRegHandle->base, handle->edmaTxDataToTxRegHandle->channel);

        transferConfigC.destAddr   = (uint32_t)txAddr;
        transferConfigC.destOffset = 0;

        if (NULL != handle->txData)
        {
            transferConfigC.srcAddr   = (uint32_t)(&(handle->txData[0]));
            transferConfigC.srcOffset = 1;
        }
        else
        {
            transferConfigC.srcAddr   = (uint32_t)(&handle->txBuffIfNull);
            transferConfigC.srcOffset = 0;
            if (handle->bitsPerFrame <= 8U)
            {
                handle->txBuffIfNull = dummyData;
            }
            else
            {
                handle->txBuffIfNull = ((uint32_t)dummyData << 8U) | dummyData;
            }
        }

        transferConfigC.srcTransferSize = kEDMA_TransferSize1Bytes;

        if (handle->bitsPerFrame <= 8U)
        {
            transferConfigC.destTransferSize = kEDMA_TransferSize1Bytes;
            transferConfigC.minorLoopBytes   = 1;
            transferConfigC.majorLoopCounts  = handle->remainingSendByteCount;
        }
        else
        {
            transferConfigC.destTransferSize = kEDMA_TransferSize2Bytes;
            transferConfigC.minorLoopBytes   = 2;
            transferConfigC.majorLoopCounts  = handle->remainingSendByteCount / 2U;
        }

        EDMA_SetTransferConfig(handle->edmaTxDataToTxRegHandle->base, handle->edmaTxDataToTxRegHandle->channel,
                               (const edma_transfer_config_t *)(uint32_t)&transferConfigC, NULL);

        EDMA_StartTransfer(handle->edmaTxDataToTxRegHandle);
    }

    EDMA_StartTransfer(handle->edmaRxRegToRxDataHandle);

    /*Set channel priority*/
    uint8_t channelPriorityLow  = handle->edmaRxRegToRxDataHandle->channel;
    uint8_t channelPriorityHigh = handle->edmaTxDataToTxRegHandle->channel;
    uint8_t t                   = 0;

    if (channelPriorityLow > channelPriorityHigh)
    {
        t                   = channelPriorityLow;
        channelPriorityLow  = channelPriorityHigh;
        channelPriorityHigh = t;
    }

    edma_channel_Preemption_config_t preemption_config_t;
    preemption_config_t.enableChannelPreemption = true;
    preemption_config_t.enablePreemptAbility    = true;
    preemption_config_t.channelPriority         = channelPriorityLow;

    if (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        EDMA_SetChannelPreemptionConfig(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);

        preemption_config_t.channelPriority = channelPriorityHigh;
        EDMA_SetChannelPreemptionConfig(handle->edmaTxDataToTxRegHandle->base, handle->edmaTxDataToTxRegHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);
    }
    else
    {
        EDMA_SetChannelPreemptionConfig(handle->edmaTxDataToTxRegHandle->base, handle->edmaTxDataToTxRegHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);

        preemption_config_t.channelPriority = channelPriorityHigh;
        EDMA_SetChannelPreemptionConfig(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                        (const edma_channel_Preemption_config_t *)(uint32_t)&preemption_config_t);
    }

    /*Set the channel link.
    For DSPI instances with shared RX/TX DMA requests: Rx DMA request -> channel_A -> channel_C.
    For DSPI instances with separate RX and TX DMA requests:
    Rx DMA request -> channel_A
    Tx DMA request -> channel_C */
    if (1 != FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base))
    {
        if (handle->remainingSendByteCount > 0U)
        {
            EDMA_SetChannelLink(handle->edmaRxRegToRxDataHandle->base, handle->edmaRxRegToRxDataHandle->channel,
                                kEDMA_MinorLink, handle->edmaTxDataToTxRegHandle->channel);
        }
        DSPI_EnableDMA(base, (uint32_t)kDSPI_RxDmaEnable);
    }
    else
    {
        DSPI_EnableDMA(base, (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);
    }

    return kStatus_Success;
}

static void EDMA_DspiSlaveCallback(edma_handle_t *edmaHandle,
                                   void *g_dspiEdmaPrivateHandle,
                                   bool transferDone,
                                   uint32_t tcds)
{
    assert(NULL != edmaHandle);
    assert(NULL != g_dspiEdmaPrivateHandle);

    dspi_slave_edma_private_handle_t *dspiEdmaPrivateHandle;

    dspiEdmaPrivateHandle = (dspi_slave_edma_private_handle_t *)g_dspiEdmaPrivateHandle;

    DSPI_DisableDMA((dspiEdmaPrivateHandle->base), (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);

    dspiEdmaPrivateHandle->handle->state = (uint8_t)kDSPI_Idle;

    if (NULL != dspiEdmaPrivateHandle->handle->callback)
    {
        dspiEdmaPrivateHandle->handle->callback(dspiEdmaPrivateHandle->base, dspiEdmaPrivateHandle->handle,
                                                kStatus_Success, dspiEdmaPrivateHandle->handle->userData);
    }
}

/*!
 * brief DSPI slave aborts a transfer which is using eDMA.
 *
 * This function aborts a transfer which is using eDMA.
 *
 * param base DSPI peripheral base address.
 * param handle A pointer to the dspi_slave_edma_handle_t structure which stores the transfer state.
 */
void DSPI_SlaveTransferAbortEDMA(SPI_Type *base, dspi_slave_edma_handle_t *handle)
{
    assert(NULL != handle);

    DSPI_StopTransfer(base);

    DSPI_DisableDMA(base, (uint32_t)kDSPI_RxDmaEnable | (uint32_t)kDSPI_TxDmaEnable);

    EDMA_AbortTransfer(handle->edmaRxRegToRxDataHandle);
    EDMA_AbortTransfer(handle->edmaTxDataToTxRegHandle);

    handle->state = (uint8_t)kDSPI_Idle;
}

/*!
 * brief Gets the slave eDMA transfer count.
 *
 * This function gets the slave eDMA transfer count.
 *
 * param base DSPI peripheral base address.
 * param handle A pointer to the dspi_slave_edma_handle_t structure which stores the transfer state.
 * param count A number of bytes transferred so far by the non-blocking transaction.
 * return status of status_t.
 */
status_t DSPI_SlaveTransferGetCountEDMA(SPI_Type *base, dspi_slave_edma_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state != (uint8_t)kDSPI_Busy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    size_t bytes;

    bytes = (uint32_t)handle->nbytes * EDMA_GetRemainingMajorLoopCount(handle->edmaRxRegToRxDataHandle->base,
                                                                       handle->edmaRxRegToRxDataHandle->channel);

    *count = handle->totalByteCount - bytes;

    return kStatus_Success;
}
