/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_DSPI_EDMA_H_
#define _FSL_DSPI_EDMA_H_

#include "fsl_dspi.h"
#include "fsl_edma.h"
/*!
 * @addtogroup dspi_edma_driver
 * @{
 */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief DSPI EDMA driver version 2.2.5 */
#define FSL_DSPI_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 2, 5))
/*@}*/

/*! @brief DSPI EDMA max transfer data size calculate
 * @param base DSPI peripheral base address.
 * @param width Transfer width
 */
#define DSPI_EDMA_MAX_TRANSFER_SIZE(base, width)                                                    \
    ((1 == FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(base)) ? ((width > 8U) ? 65534U : 32767U) : \
                                                                 ((width > 8U) ? 1022U : 511U))

/*!
 * @brief Forward declaration of the DSPI eDMA master handle typedefs.
 */
typedef struct _dspi_master_edma_handle dspi_master_edma_handle_t;

/*!
 * @brief Forward declaration of the DSPI eDMA slave handle typedefs.
 */
typedef struct _dspi_slave_edma_handle dspi_slave_edma_handle_t;

/*!
 * @brief Completion callback function pointer type.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the handle for the DSPI master.
 * @param status Success or error code describing whether the transfer completed.
 * @param userData An arbitrary pointer-dataSized value passed from the application.
 */
typedef void (*dspi_master_edma_transfer_callback_t)(SPI_Type *base,
                                                     dspi_master_edma_handle_t *handle,
                                                     status_t status,
                                                     void *userData);
/*!
 * @brief Completion callback function pointer type.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the handle for the DSPI slave.
 * @param status Success or error code describing whether the transfer completed.
 * @param userData An arbitrary pointer-dataSized value passed from the application.
 */
typedef void (*dspi_slave_edma_transfer_callback_t)(SPI_Type *base,
                                                    dspi_slave_edma_handle_t *handle,
                                                    status_t status,
                                                    void *userData);

/*! @brief DSPI master eDMA transfer handle structure used for the transactional API. */
struct _dspi_master_edma_handle
{
    uint32_t bitsPerFrame;         /*!< The desired number of bits per frame. */
    volatile uint32_t command;     /*!< The desired data command. */
    volatile uint32_t lastCommand; /*!< The desired last data command. */

    uint8_t fifoSize; /*!< FIFO dataSize. */

    volatile bool
        isPcsActiveAfterTransfer; /*!< Indicates whether the PCS signal keeps active after the last frame transfer.*/

    uint8_t nbytes;         /*!< eDMA minor byte transfer count initially configured. */
    volatile uint8_t state; /*!< DSPI transfer state, see @ref _dspi_transfer_state.*/

    uint8_t *volatile txData;                  /*!< Send buffer. */
    uint8_t *volatile rxData;                  /*!< Receive buffer. */
    volatile size_t remainingSendByteCount;    /*!< A number of bytes remaining to send.*/
    volatile size_t remainingReceiveByteCount; /*!< A number of bytes remaining to receive.*/
    size_t totalByteCount;                     /*!< A number of transfer bytes*/

    uint32_t rxBuffIfNull; /*!< Used if there is not rxData for DMA purpose.*/
    uint32_t txBuffIfNull; /*!< Used if there is not txData for DMA purpose.*/

    dspi_master_edma_transfer_callback_t callback; /*!< Completion callback. */
    void *userData;                                /*!< Callback user data. */

    edma_handle_t *edmaRxRegToRxDataHandle;        /*!<edma_handle_t handle point used for RxReg to RxData buff*/
    edma_handle_t *edmaTxDataToIntermediaryHandle; /*!<edma_handle_t handle point used for TxData to Intermediary*/
    edma_handle_t *edmaIntermediaryToTxRegHandle;  /*!<edma_handle_t handle point used for Intermediary to TxReg*/

    edma_tcd_t dspiSoftwareTCD[2]; /*!<SoftwareTCD , internal used*/
};

/*! @brief DSPI slave eDMA transfer handle structure used for the transactional API.*/
struct _dspi_slave_edma_handle
{
    uint32_t bitsPerFrame; /*!< The desired number of bits per frame. */

    uint8_t *volatile txData;                  /*!< Send buffer. */
    uint8_t *volatile rxData;                  /*!< Receive buffer. */
    volatile size_t remainingSendByteCount;    /*!< A number of bytes remaining to send.*/
    volatile size_t remainingReceiveByteCount; /*!< A number of bytes remaining to receive.*/
    size_t totalByteCount;                     /*!< A number of transfer bytes*/

    uint32_t rxBuffIfNull; /*!< Used if there is not rxData for DMA purpose.*/
    uint32_t txBuffIfNull; /*!< Used if there is not txData for DMA purpose.*/
    uint32_t txLastData;   /*!< Used if there is an extra byte when 16bits per frame for DMA purpose.*/

    uint8_t nbytes; /*!< eDMA minor byte transfer count initially configured. */

    volatile uint8_t state; /*!< DSPI transfer state.*/

    dspi_slave_edma_transfer_callback_t callback; /*!< Completion callback. */
    void *userData;                               /*!< Callback user data. */

    edma_handle_t *edmaRxRegToRxDataHandle; /*!<edma_handle_t handle point used for RxReg to RxData buff*/
    edma_handle_t *edmaTxDataToTxRegHandle; /*!<edma_handle_t handle point used for TxData to TxReg*/
};

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus*/

/*! @name Transactional APIs
 * @{
 */

/*!
 * @brief Initializes the DSPI master eDMA handle.
 *
 * This function initializes the DSPI eDMA handle which can be used for other DSPI transactional APIs.  Usually, for a
 * specified DSPI instance, call this API once to get the initialized handle.
 *
 * @note DSPI eDMA has separated (RX and TX as two sources) or shared (RX  and TX are the same source) DMA request
 * source.
 * - For the separated DMA request source, enable and set the RX DMAMUX source for edmaRxRegToRxDataHandle and
 *   TX DMAMUX source for edmaIntermediaryToTxRegHandle.
 * - For the shared DMA request source, enable and set the RX/RX DMAMUX source for the edmaRxRegToRxDataHandle.
 *
 * @param base DSPI peripheral base address.
 * @param handle DSPI handle pointer to @ref _dspi_master_edma_handle.
 * @param callback DSPI callback.
 * @param userData A callback function parameter.
 * @param edmaRxRegToRxDataHandle edmaRxRegToRxDataHandle pointer to edma_handle_t.
 * @param edmaTxDataToIntermediaryHandle edmaTxDataToIntermediaryHandle pointer to edma_handle_t.
 * @param edmaIntermediaryToTxRegHandle edmaIntermediaryToTxRegHandle pointer to edma_handle_t.
 */
void DSPI_MasterTransferCreateHandleEDMA(SPI_Type *base,
                                         dspi_master_edma_handle_t *handle,
                                         dspi_master_edma_transfer_callback_t callback,
                                         void *userData,
                                         edma_handle_t *edmaRxRegToRxDataHandle,
                                         edma_handle_t *edmaTxDataToIntermediaryHandle,
                                         edma_handle_t *edmaIntermediaryToTxRegHandle);

/*!
 * @brief DSPI master transfer data using eDMA.
 *
 * This function transfers data using eDMA. This is a non-blocking function, which returns right away. When all data
 * is transferred, the callback function is called.
 *
 * @note The max transfer size of each transfer depends on whether the instance's Tx/Rx shares the same DMA request. If
 * <b>FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(x)</b> is true, then the max transfer size is 32767 datawidth of
 * data, otherwise is 511.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the @ref _dspi_master_edma_handle structure which stores the transfer state.
 * @param transfer A pointer to the @ref dspi_transfer_t structure.
 * @return status of status_t.
 */
status_t DSPI_MasterTransferEDMA(SPI_Type *base, dspi_master_edma_handle_t *handle, dspi_transfer_t *transfer);

/*!
 * @brief Transfers a block of data using a eDMA method.
 *
 * This function transfers data using eDNA, the transfer mechanism is half-duplex. This is a non-blocking function,
 * which returns right away. When all data is transferred, the callback function is called.
 *
 * @param base DSPI base pointer
 * @param handle A pointer to the @ref _dspi_master_edma_handle structure which stores the transfer state.
 * @param xfer A pointer to the @ref dspi_half_duplex_transfer_t structure.
 * @return status of status_t.
 */
status_t DSPI_MasterHalfDuplexTransferEDMA(SPI_Type *base,
                                           dspi_master_edma_handle_t *handle,
                                           dspi_half_duplex_transfer_t *xfer);

/*!
 * @brief DSPI master aborts a transfer which is using eDMA.
 *
 * This function aborts a transfer which is using eDMA.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the @ref _dspi_master_edma_handle structure which stores the transfer state.
 */
void DSPI_MasterTransferAbortEDMA(SPI_Type *base, dspi_master_edma_handle_t *handle);

/*!
 * @brief Gets the master eDMA transfer count.
 *
 * This function gets the master eDMA transfer count.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the @ref _dspi_master_edma_handle structure which stores the transfer state.
 * @param count A number of bytes transferred by the non-blocking transaction.
 * @return status of status_t.
 */
status_t DSPI_MasterTransferGetCountEDMA(SPI_Type *base, dspi_master_edma_handle_t *handle, size_t *count);

/*!
 * @brief Initializes the DSPI slave eDMA handle.
 *
 * This function initializes the DSPI eDMA handle which can be used for other DSPI transactional APIs.  Usually, for a
 * specified DSPI instance, call this API once to get the initialized handle.
 *
 * @note DSPI eDMA has separated (RN and TX in 2 sources) or shared (RX  and TX are the same source) DMA request
 * source.
 * - For the separated DMA request source, enable and set the RX DMAMUX source for edmaRxRegToRxDataHandle and
 *   TX DMAMUX source for edmaTxDataToTxRegHandle.
 * - For the shared DMA request source,  enable and set the RX/RX DMAMUX source for the edmaRxRegToRxDataHandle.
 *
 * @param base DSPI peripheral base address.
 * @param handle DSPI handle pointer to @ref _dspi_slave_edma_handle.
 * @param callback DSPI callback.
 * @param userData A callback function parameter.
 * @param edmaRxRegToRxDataHandle edmaRxRegToRxDataHandle pointer to edma_handle_t.
 * @param edmaTxDataToTxRegHandle edmaTxDataToTxRegHandle pointer to edma_handle_t.
 */
void DSPI_SlaveTransferCreateHandleEDMA(SPI_Type *base,
                                        dspi_slave_edma_handle_t *handle,
                                        dspi_slave_edma_transfer_callback_t callback,
                                        void *userData,
                                        edma_handle_t *edmaRxRegToRxDataHandle,
                                        edma_handle_t *edmaTxDataToTxRegHandle);

/*!
 * @brief DSPI slave transfer data using eDMA.
 *
 * This function transfers data using eDMA. This is a non-blocking function, which returns right away. When all data
 * is transferred, the callback function is called.
 * Note that the slave eDMA transfer doesn't support transfer_size is 1 when the bitsPerFrame is greater
 * than eight.
 *
 * @note The max transfer size of each transfer depends on whether the instance's Tx/Rx shares the same DMA request. If
 * <b>FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(x)</b> is true, then the max transfer size is 32767 datawidth of
 * data, otherwise is 511.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the @ref _dspi_slave_edma_handle structure which stores the transfer state.
 * @param transfer A pointer to the @ref dspi_transfer_t structure.
 * @return status of status_t.
 */
status_t DSPI_SlaveTransferEDMA(SPI_Type *base, dspi_slave_edma_handle_t *handle, dspi_transfer_t *transfer);

/*!
 * @brief DSPI slave aborts a transfer which is using eDMA.
 *
 * This function aborts a transfer which is using eDMA.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the @ref _dspi_slave_edma_handle structure which stores the transfer state.
 */
void DSPI_SlaveTransferAbortEDMA(SPI_Type *base, dspi_slave_edma_handle_t *handle);

/*!
 * @brief Gets the slave eDMA transfer count.
 *
 * This function gets the slave eDMA transfer count.
 *
 * @param base DSPI peripheral base address.
 * @param handle A pointer to the @ref _dspi_slave_edma_handle structure which stores the transfer state.
 * @param count A number of bytes transferred so far by the non-blocking transaction.
 * @return status of status_t.
 */
status_t DSPI_SlaveTransferGetCountEDMA(SPI_Type *base, dspi_slave_edma_handle_t *handle, size_t *count);

/*!@}*/

#if defined(__cplusplus)
}
#endif /*_cplusplus*/
/*!
 *@}
 */

#endif /*_FSL_DSPI_EDMA_H_*/
