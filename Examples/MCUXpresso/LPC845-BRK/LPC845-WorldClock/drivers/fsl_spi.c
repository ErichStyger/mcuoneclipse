/*
 * Copyright 2017-2020,2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_minispi"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS) && (FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS)
/*! @brief SPI internal handle pointer array */
static spi_master_handle_t *s_spiHandle[FSL_FEATURE_SOC_SPI_COUNT];

/*! @brief IRQ name array */
static const IRQn_Type s_spiIRQ[] = SPI_IRQS;

/*! @brief Typedef for spi master interrupt handler. spi master and slave handle is the same. */
typedef void (*spi_isr_t)(SPI_Type *base, spi_master_handle_t *spiHandle);

/*! @brief Pointer to master IRQ handler for each instance. */
static spi_isr_t s_spiMasterIsr;
static spi_isr_t s_spiSlaveIsr;
#endif /* FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS */

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* @brief Array to map SPI instance number to CLOCK names */
static const clock_ip_name_t s_spiClock[] = SPI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
/* @brief Array to map SPI reset. */
static const SYSCON_RSTn_t s_spiReset[] = SPI_RSTS_N;
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

/*! @brief Array to map SPI instance number to base address. */
static const uint32_t s_spiBaseAddrs[FSL_FEATURE_SOC_SPI_COUNT] = SPI_BASE_ADDRS;

/* @brief Dummy data for each instance. This data is used when user's tx buffer is NULL*/
volatile uint16_t s_dummyData[FSL_FEATURE_SOC_SPI_COUNT] = {0};

/*******************************************************************************
 * Code
 ******************************************************************************/

#if defined(FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS) && (FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS)
/*!
 * @brief Send a piece of data for SPI.
 *
 * This function will check if TXDAT register ready, and write the data into it.
 * At the same time, this function updates the values in master handle structure.
 *
 * @param base SPI base pointer
 * @param handle Pointer to SPI master handle structure.
 */
static void SPI_SendTransfer(SPI_Type *base, spi_master_handle_t *handle)
{
    uint32_t tmp32    = 0U;
    uint32_t instance = SPI_GetInstance(base);

    /* If transmit is ready, write data to TXDAT register. */
    if (((uint32_t)kSPI_TxReadyFlag & SPI_GetStatusFlags(base)) != 0U)
    {
        if ((handle->txData) != NULL)
        {
            tmp32 = *(handle->txData++);
            handle->txRemainingBytes--;
            if (handle->dataWidth > (uint8_t)kSPI_Data8Bits)
            {
                tmp32 |= ((uint32_t)(*(handle->txData++)) << 8U);
                handle->txRemainingBytes--;
            }
        }
        else
        {
            tmp32 = (uint32_t)s_dummyData[instance];
            handle->txRemainingBytes--;
            if (handle->dataWidth > (uint8_t)kSPI_Data8Bits)
            {
                handle->txRemainingBytes--;
            }
        }
        /* If this transmit is the last to send, Set the control bits. */
        if (handle->txRemainingBytes == 0U)
        {
            base->TXCTL = handle->lastCommand;
        }

        base->TXDAT = tmp32;
    }
}

/*!
 * @brief Receive a piece of data for SPI.
 *
 * This function will check if RX register is ready, and write the data to destination address.
 * At the same time, this function updates the values in master handle structure.
 *
 * @param base SPI base pointer
 * @param handle Pointer to SPI master handle structure.
 */
static void SPI_ReceiveTransfer(SPI_Type *base, spi_master_handle_t *handle)
{
    uint32_t tmp32 = 0U;

    /* If receive is ready, read data from RXDAT register. */
    if (((uint32_t)kSPI_RxReadyFlag & SPI_GetStatusFlags(base)) != 0U)
    {
        tmp32 = SPI_ReadData(base);
        /* Check If receive buffer is NULL. */
        if ((handle->rxData) != NULL)
        {
            *(handle->rxData++) = (uint8_t)tmp32;
            handle->rxRemainingBytes--;
            if (handle->dataWidth > (uint8_t)kSPI_Data8Bits)
            {
                *(handle->rxData++) = (uint8_t)(tmp32 >> 8U);
                handle->rxRemainingBytes--;
            }
        }
    }
}
#endif /* FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS */

/*!
 * @brief Get the instance for SPI module.
 *
 * @param base SPI base address
 */
/*! brief Returns instance number for SPI peripheral base address. */
uint32_t SPI_GetInstance(SPI_Type *base)
{
    assert(NULL != base);

    uint32_t i = 0U;

    for (i = 0; i < (uint32_t)FSL_FEATURE_SOC_SPI_COUNT; i++)
    {
        if ((uint32_t)base == s_spiBaseAddrs[i])
        {
            break;
        }
    }

    assert(i < (uint32_t)FSL_FEATURE_SOC_SPI_COUNT);
    return i;
}

/*!
 * brief Set up the dummy data. This API can change the default data to be transferred
 *        when users set the tx buffer to NULL.
 *
 * param base SPI peripheral address.
 * param dummyData Data to be transferred when tx buffer is NULL.
 */
void SPI_SetDummyData(SPI_Type *base, uint16_t dummyData)
{
    uint32_t instance     = SPI_GetInstance(base);
    s_dummyData[instance] = dummyData;
}

/* Set delay time for SPI transfer. */
/*!
 * brief Set delay time for transfer.
 *        the delay uint is SPI clock time, maximum value is 0xF.
 * param base SPI base pointer
 * param config configuration for delay option ref spi_delay_config_t.
 */
void SPI_SetTransferDelay(SPI_Type *base, const spi_delay_config_t *config)
{
    assert(NULL != config);
    /* Set the delay configuration. */
    base->DLY = (SPI_DLY_PRE_DELAY(config->preDelay) | SPI_DLY_POST_DELAY(config->postDelay) |
                 SPI_DLY_FRAME_DELAY(config->frameDelay) | SPI_DLY_TRANSFER_DELAY(config->transferDelay));
}

/*!
 * brief  Sets the SPI master configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in SPI_MasterInit().
 * User may use the initialized structure unchanged in SPI_MasterInit(), or modify
 * some fields of the structure before calling SPI_MasterInit(). After calling this API,
 * the master is ready to transfer.
 * Example:
   code
   spi_master_config_t config;
   SPI_MasterGetDefaultConfig(&config);
   endcode
 *
 * param config pointer to master config structure
 */
void SPI_MasterGetDefaultConfig(spi_master_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableLoopback            = false;
    config->enableMaster              = true;
    config->clockPolarity             = kSPI_ClockPolarityActiveHigh;
    config->clockPhase                = kSPI_ClockPhaseFirstEdge;
    config->direction                 = kSPI_MsbFirst;
    config->baudRate_Bps              = 500000U;
    config->dataWidth                 = (uint8_t)kSPI_Data8Bits;
    config->sselNumber                = kSPI_Ssel0Assert;
    config->sselPolarity              = kSPI_SpolActiveAllLow;
    config->delayConfig.frameDelay    = 0U;
    config->delayConfig.postDelay     = 0U;
    config->delayConfig.preDelay      = 0U;
    config->delayConfig.transferDelay = 0U;
}

/*!
 * brief Initializes the SPI with master configuration.
 *
 * The configuration structure can be filled by user from scratch, or be set with default
 * values by SPI_MasterGetDefaultConfig(). After calling this API, the slave is ready to transfer.
 * Example
   code
   spi_master_config_t config = {
   .baudRate_Bps = 500000,
   ...
   };
   SPI_MasterInit(SPI0, &config);
   endcode
 *
 * param base SPI base pointer
 * param config pointer to master configuration structure
 * param srcClock_Hz Source clock frequency.
 */
status_t SPI_MasterInit(SPI_Type *base, const spi_master_config_t *config, uint32_t srcClock_Hz)
{
    uint32_t instance = 0U;
    status_t result   = 0;
    uint32_t tmp      = 0U;

    /* assert params */
    assert(!((NULL == base) || (NULL == config) || (0U == srcClock_Hz)));

    /* Get instance number */
    instance = SPI_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_spiClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(s_spiReset[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

    /* set divider */
    result = SPI_MasterSetBaudRate(base, config->baudRate_Bps, srcClock_Hz);
    if (kStatus_Success != result)
    {
        return result;
    }
    /* Set CFG register to configure phase/polarity/direction/master mode/loopback/ssel pin select. */
    tmp |= (SPI_CFG_CPHA(config->clockPhase) | SPI_CFG_CPOL(config->clockPolarity) | SPI_CFG_LSBF(config->direction) |
            SPI_CFG_MASTER(1) | SPI_CFG_LOOP(config->enableLoopback) |
            ((uint32_t)config->sselPolarity & (uint32_t)kSPI_SpolActiveAllHigh));
    base->CFG = tmp;

    /* Set delay configuration. */
    SPI_SetTransferDelay(base, &(config->delayConfig));

    /* Set dummy data. */
    SPI_SetDummyData(base, (uint8_t)SPI_DUMMYDATA);

    /* Set TXCTL register. */
    base->TXCTL |= (SPI_TXCTL_LEN(config->dataWidth) | ((uint32_t)config->sselNumber & (uint32_t)kSPI_SselDeAssertAll));

    /* Enable the SPI module. */
    SPI_Enable(base, config->enableMaster);

    return kStatus_Success;
}

/*!
 * brief  Sets the SPI slave configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in SPI_SlaveInit().
 * Modify some fields of the structure before calling SPI_SlaveInit().
 * Example:
   code
   spi_slave_config_t config;
   SPI_SlaveGetDefaultConfig(&config);
   endcode
 *
 * param config pointer to slave configuration structure
 */
void SPI_SlaveGetDefaultConfig(spi_slave_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->enableSlave   = true;
    config->clockPolarity = kSPI_ClockPolarityActiveHigh;
    config->clockPhase    = kSPI_ClockPhaseFirstEdge;
    config->direction     = kSPI_MsbFirst;
    config->dataWidth     = (uint8_t)kSPI_Data8Bits;
    config->sselPolarity  = kSPI_SpolActiveAllLow;
}

/*!
 * brief Initializes the SPI with slave configuration.
 *
 * The configuration structure can be filled by user from scratch or be set with
 * default values by SPI_SlaveGetDefaultConfig().
 * After calling this API, the slave is ready to transfer.
 * Example
   code
    spi_slave_config_t config = {
    .polarity = kSPI_ClockPolarityActiveHigh;
    .phase = kSPI_ClockPhaseFirstEdge;
    .direction = kSPI_MsbFirst;
    ...
    };
    SPI_SlaveInit(SPI0, &config);
   endcode
 *
 * param base SPI base pointer
 * param config pointer to slave configuration structure
 */
status_t SPI_SlaveInit(SPI_Type *base, const spi_slave_config_t *config)
{
    uint32_t instance = 0U;
    uint32_t tmp      = 0U;

    /* assert params */
    assert(!((NULL == base) || (NULL == config)));
    /* Get the instance of SPI. */
    instance = SPI_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_spiClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(s_spiReset[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

    /* Set confiuration for phase/polarity/direction/active level for SSEL pins. */
    tmp |= SPI_CFG_CPHA(config->clockPhase) | SPI_CFG_CPOL(config->clockPolarity) | SPI_CFG_LSBF(config->direction) |
           ((uint32_t)config->sselPolarity & (uint32_t)kSPI_SpolActiveAllHigh);
    base->CFG = tmp;

    /* Set dummy data. */
    SPI_SetDummyData(base, (uint8_t)SPI_DUMMYDATA);

    /* Set TXCTL register. */
    base->TXCTL |= SPI_TXCTL_LEN(config->dataWidth);

    /* Enable the SPI module. */
    SPI_Enable(base, config->enableSlave);

    return kStatus_Success;
}

/*!
 * brief De-initializes the SPI.
 *
 * Calling this API resets the SPI module, gates the SPI clock.
 * Disable the fifo if enabled.
 * The SPI module can't work unless calling the SPI_MasterInit/SPI_SlaveInit to initialize module.
 *
 * param base SPI base pointer
 */
void SPI_Deinit(SPI_Type *base)
{
    /* Assert arguments */
    assert(NULL != base);
    uint32_t instance = SPI_GetInstance(base);
    /* Disable SPI module before shutting down the clock. */
    SPI_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_spiClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Sets the baud rate for SPI transfer. This is only used in master.
 *
 * param base SPI base pointer
 * param baudrate_Bps baud rate needed in Hz.
 * param srcClock_Hz SPI source clock frequency in Hz.
 */
status_t SPI_MasterSetBaudRate(SPI_Type *base, uint32_t baudrate_Bps, uint32_t srcClock_Hz)
{
    uint32_t tmp;

    /* assert params */
    assert(!((NULL == base) || (0U == baudrate_Bps) || (0U == srcClock_Hz)));

    /* calculate baudrate */
    tmp = (srcClock_Hz / baudrate_Bps) - 1U;
    if (tmp > 0xFFFFU)
    {
        return kStatus_SPI_BaudrateNotSupport;
    }
    base->DIV &= ~SPI_DIV_DIVVAL_MASK;
    base->DIV |= SPI_DIV_DIVVAL(tmp);
    return kStatus_Success;
}

/*!
 * brief Writes a data control info and data into the SPI TX register directly.
 *
 * param base SPI base pointer
 * param value needs to be write.
 */
void SPI_WriteDataWithConfigFlags(SPI_Type *base, uint16_t data, uint32_t configFlags)
{
    uint32_t control = 0;
    /* check params */
    assert(NULL != base);
    /* Read origin command from TXCTL register. */
    control = base->TXCTL & (~(SPI_TXDATCTL_EOT_MASK | SPI_TXDATCTL_EOF_MASK | SPI_TXDATCTL_RXIGNORE_MASK));
    /* Mask configFlags */
    control |= (configFlags & (SPI_TXDATCTL_EOT_MASK | SPI_TXDATCTL_EOF_MASK | SPI_TXDATCTL_RXIGNORE_MASK));
    /* Write data and command to register. */
    base->TXDATCTL = (data | control);
}

/*!
 * brief Transfers a block of data using a polling method.
 *
 * param base SPI base pointer
 * param xfer pointer to spi_xfer_config_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_SPI_Timeout The transfer timed out and was aborted.
 */
status_t SPI_MasterTransferBlocking(SPI_Type *base, spi_transfer_t *xfer)
{
    uint32_t tx_ctrl = 0, last_ctrl = 0;
    uint32_t tmp32, remainingBytes, dataWidth;
    uint32_t instance = SPI_GetInstance(base);
#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif
    /* Check params */
    assert(!((NULL == base) || (NULL == xfer) || ((NULL == xfer->txData) && (NULL == xfer->rxData))));

    remainingBytes = xfer->dataSize;
    /* Read datawidth and ssel info from TXCTL. */
    tx_ctrl   = base->TXCTL & (SPI_TXCTL_LEN_MASK | (uint32_t)kSPI_SselDeAssertAll);
    dataWidth = ((tx_ctrl & SPI_TXCTL_LEN_MASK) >> SPI_TXCTL_LEN_SHIFT);

    /* Set end of frame configuration. */
    tx_ctrl |= ((xfer->configFlags & (uint32_t)kSPI_EndOfFrame) != 0U) ? (uint32_t)kSPI_EndOfFrame : 0U;
    /* Set ignore configuration. */
    tx_ctrl |= (xfer->configFlags & (uint32_t)kSPI_ReceiveIgnore);

    /* If rxData is NULL, ignore the receive. */
    if (NULL == xfer->rxData)
    {
        tx_ctrl |= (uint32_t)kSPI_ReceiveIgnore;
    }

    /* Setup last command for transfer. */
    last_ctrl = tx_ctrl;
    /* Set end of transfer configuration for last command. */
    last_ctrl |= ((xfer->configFlags & (uint32_t)kSPI_EndOfTransfer) != 0U) ? (uint32_t)kSPI_EndOfTransfer : 0U;

    /* If only on frame to be sent, set the command to last command. */
    if (((remainingBytes == 1U) && (dataWidth < (uint32_t)kSPI_Data9Bits)) ||
        ((remainingBytes == 2U) && (dataWidth >= (uint32_t)kSPI_Data9Bits)))
    {
        SPI_WriteConfigFlags(base, last_ctrl);
    }
    else
    {
        SPI_WriteConfigFlags(base, tx_ctrl);
    }

    /* Index of loop */
    while (remainingBytes != 0U)
    {
        tmp32 = 0U;
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while (((base->STAT & SPI_STAT_TXRDY_MASK) == 0U) && (--waitTimes != 0U))
#else
        while ((base->STAT & SPI_STAT_TXRDY_MASK) == 0U)
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_SPI_Timeout;
        }
#endif

        /* If txdata is not NULL. */
        if (xfer->txData != NULL)
        {
            tmp32 = *(xfer->txData++);
            if (dataWidth > (uint32_t)kSPI_Data8Bits)
            {
                tmp32 |= ((uint32_t)(*(xfer->txData++))) << 8U;
            }
        }
        else
        {
            tmp32 = (uint32_t)s_dummyData[instance];
        }
        if ((dataWidth > (uint32_t)kSPI_Data8Bits) ? (remainingBytes == 2U) : (remainingBytes == 1U))
        {
            base->TXDATCTL = (tmp32 | last_ctrl);
        }
        else
        {
            /* Write data to the Transmit register. */
            base->TXDAT = tmp32;
        }
        /* If the RX ignore bits is not set. */
        if ((xfer->configFlags & (uint32_t)kSPI_ReceiveIgnore) == 0U)
        {
            /* Read data from the receive register. */
#if SPI_RETRY_TIMES
            waitTimes = SPI_RETRY_TIMES;
            while (((base->STAT & SPI_STAT_RXRDY_MASK) == 0U) && (--waitTimes != 0U))
#else
            while ((base->STAT & SPI_STAT_RXRDY_MASK) == 0U)
#endif
            {
            }
#if SPI_RETRY_TIMES
            if (waitTimes == 0U)
            {
                return kStatus_SPI_Timeout;
            }
#endif
            tmp32 = base->RXDAT;

            /* If receive buffer is not NULL. */
            if (xfer->rxData != NULL)
            {
                *(xfer->rxData++) = (uint8_t)tmp32;
                if (dataWidth > (uint32_t)kSPI_Data8Bits)
                {
                    *(xfer->rxData++) = (uint8_t)(tmp32 >> 8U);
                }
            }
        }
        remainingBytes--;
        if (dataWidth > (uint32_t)kSPI_Data8Bits)
        {
            remainingBytes--;
        }
    }

    /* Note that: the MSTIDLE status is related to the EOT bit, if the EOT is not set, the MSTIDLE bit will never be set
     * even though there is no data in the FIFO and no data will be shifted by the bus line. so, please don't check the
     * MSTIDLE status if the EOT bit is not set.
     */
    if ((xfer->configFlags & (uint32_t)kSPI_EndOfTransfer) != 0U)
    {
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while (((base->STAT & SPI_STAT_MSTIDLE_MASK) == 0U) && (--waitTimes != 0U))
#else
        while ((base->STAT & SPI_STAT_MSTIDLE_MASK) == 0U)
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_SPI_Timeout;
        }
#endif
    }
    return kStatus_Success;
}

#if defined(FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS) && (FSL_SDK_ENABLE_SPI_DRIVER_TRANSACTIONAL_APIS)
/*!
 * brief Initializes the SPI master handle.
 *
 * This function initializes the SPI master handle which can be used for other SPI master transactional APIs. Usually,
 * for a specified SPI instance, call this API once to get the initialized handle.
 *
 * param base SPI peripheral base address.
 * param handle SPI handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
status_t SPI_MasterTransferCreateHandle(SPI_Type *base,
                                        spi_master_handle_t *handle,
                                        spi_master_callback_t callback,
                                        void *userData)
{
    /* check 'base' and 'handle'. */
    assert((NULL != base) || (NULL != handle));

    /* Get SPI instance by 'base' param */
    uint32_t instance = SPI_GetInstance(base);

    (void)memset(handle, 0, sizeof(*handle));
    handle->dataWidth     = (uint8_t)((base->TXCTL & SPI_TXCTL_LEN_MASK) >> SPI_TXCTL_LEN_SHIFT);
    handle->callback      = callback;
    handle->userData      = userData;
    s_spiHandle[instance] = handle;
    s_spiMasterIsr        = SPI_MasterTransferHandleIRQ;
    /* Enable SPI NVIC */
    (void)EnableIRQ(s_spiIRQ[instance]);

    return kStatus_Success;
}

/*!
 * brief Initializes the SPI slave handle.
 *
 * This function initializes the SPI slave handle which can be used for other SPI slave transactional APIs. Usually,
 * for a specified SPI instance, call this API once to get the initialized handle.
 *
 * param base SPI peripheral base address.
 * param handle SPI handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
status_t SPI_SlaveTransferCreateHandle(SPI_Type *base,
                                       spi_slave_handle_t *handle,
                                       spi_slave_callback_t callback,
                                       void *userData)
{
    (void)SPI_MasterTransferCreateHandle(base, handle, callback, userData);
    s_spiSlaveIsr = SPI_SlaveTransferHandleIRQ;
    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SPI interrupt transfer.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_master_handle_t structure which stores the transfer state
 * param xfer pointer to spi_xfer_config_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t SPI_MasterTransferNonBlocking(SPI_Type *base, spi_master_handle_t *handle, spi_transfer_t *xfer)
{
    /* check params */
    assert(
        !((NULL == base) || (NULL == handle) || (NULL == xfer) || ((NULL == xfer->txData) && (NULL == xfer->rxData))));
    uint16_t temp = 0U;
    uint32_t instance;

    /* dataSize (in bytes) is not aligned to 16bit (2B) transfer */
    if ((handle->dataWidth > (uint8_t)kSPI_Data8Bits) && ((xfer->dataSize & 0x1U) != 0U))
    {
        return kStatus_InvalidArgument;
    }

    /* Check if SPI is busy */
    if (handle->state == (uint32_t)kStatus_SPI_Busy)
    {
        return kStatus_SPI_Busy;
    }

    /* Set the handle information */
    handle->txData = xfer->txData;
    handle->rxData = xfer->rxData;
    /* Set count */
    handle->txRemainingBytes = (NULL == xfer->txData) ? 0U : xfer->dataSize;
    handle->rxRemainingBytes = (NULL == xfer->rxData) ? 0U : xfer->dataSize;
    handle->totalByteCount   = xfer->dataSize;
    /* If the rxData is NULL, ignore the receive. */
    if (NULL == xfer->rxData)
    {
        xfer->configFlags |= (uint32_t)kSPI_ReceiveIgnore;
    }

    /* If only on frame to be sent, set the command to last command. */
    if (((xfer->dataSize == 1U) && (handle->dataWidth < (uint8_t)kSPI_Data9Bits)) ||
        ((xfer->dataSize == 2U) && (handle->dataWidth >= (uint8_t)kSPI_Data9Bits)))
    {
        SPI_WriteConfigFlags(base, xfer->configFlags);
    }
    else
    {
        SPI_WriteConfigFlags(base, (xfer->configFlags & (~SPI_TXDATCTL_EOT_MASK)));
    }

    /* Set the last command. */
    handle->lastCommand = base->TXCTL & (SPI_TXCTL_LEN_MASK | SPI_TXCTL_RXIGNORE_MASK | SPI_TXCTL_EOF_MASK |
                                         SPI_TXCTL_EOT_MASK | (uint32_t)kSPI_SselDeAssertAll);
    if ((xfer->configFlags & (uint32_t)kSPI_EndOfTransfer) != 0U)
    {
        handle->lastCommand |= SPI_TXDATCTL_EOT_MASK;
    }
    /* Set the SPI state to busy */
    handle->state = (uint32_t)kStatus_SPI_Busy;

    /* Write data to TXDAT register to trigger a SPI receive. */
    if (NULL == handle->txData)
    {
        instance = SPI_GetInstance(base);
        temp     = s_dummyData[instance];
    }
    else
    {
        temp = *handle->txData++;
        handle->txRemainingBytes--;
        if (handle->dataWidth > (uint8_t)kSPI_Data8Bits)
        {
            temp |= (uint16_t)(*handle->txData++) << 8U;
            handle->txRemainingBytes--;
        }
    }

    SPI_WriteData(base, temp);

    /* Enable generating IRQ.
     * If RX ignore bit was set, only enable TX ready interrupt, otherwise,
     * enable RX ready interrupt.
     */
    if (((uint32_t)kSPI_ReceiveIgnore & xfer->configFlags) != 0U)
    {
        SPI_EnableInterrupts(base, (uint32_t)kSPI_TxReadyInterruptEnable);
    }
    else
    {
        SPI_EnableInterrupts(base, (uint32_t)kSPI_RxReadyInterruptEnable);
    }

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SPI slave interrupt transfer.
 *
 * note The API returns immediately after the transfer initialization is finished.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_master_handle_t structure which stores the transfer state
 * param xfer pointer to spi_xfer_config_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t SPI_SlaveTransferNonBlocking(SPI_Type *base, spi_slave_handle_t *handle, spi_transfer_t *xfer)
{
    status_t status = kStatus_Success;

    s_spiSlaveIsr = SPI_SlaveTransferHandleIRQ;
    status        = SPI_MasterTransferNonBlocking(base, handle, xfer);

    return status;
}

/*!
 * brief Gets the master transfer count.
 *
 * This function gets the master transfer count.
 *
 * param base SPI peripheral base address.
 * param handle Pointer to the spi_master_handle_t structure which stores the transfer state.
 * param count The number of bytes transferred by using the non-blocking transaction.
 * return status of status_t.
 */
status_t SPI_MasterTransferGetCount(SPI_Type *base, spi_master_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    if (count == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state != (uint32_t)kStatus_SPI_Busy)
    {
        *count = 0U;
        return kStatus_NoTransferInProgress;
    }

    *count = handle->totalByteCount - handle->rxRemainingBytes;
    return kStatus_Success;
}

/*!
 * brief SPI master aborts a transfer using an interrupt.
 *
 * This function aborts a transfer using an interrupt.
 *
 * param base SPI peripheral base address.
 * param handle Pointer to the spi_master_handle_t structure which stores the transfer state.
 */
void SPI_MasterTransferAbort(SPI_Type *base, spi_master_handle_t *handle)
{
    assert(NULL != handle);

    SPI_DisableInterrupts(base, (uint32_t)kSPI_TxReadyInterruptEnable | (uint32_t)kSPI_RxReadyInterruptEnable);

    handle->state            = (uint32_t)kStatus_SPI_Idle;
    handle->txRemainingBytes = 0U;
    handle->rxRemainingBytes = 0U;
}

/*!
 * brief Interrupts the handler for the SPI.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_master_handle_t structure which stores the transfer state.
 */
void SPI_MasterTransferHandleIRQ(SPI_Type *base, spi_master_handle_t *handle)
{
    assert((NULL != base) && (NULL != handle));

    /* IRQ behaviour:
     * - First interrupt is triggered by receive ready interrupt. The transfer function then
     *   tries read data and transmit data interleaved that results to strategy to process
     *   as many items as possible.
     * - In last interrupt, the last state is known by empty rxBuffer and txBuffer. If there
     *   is nothing to receive or send - both operations have been finished and interrupts can be disabled.
     *   If the callback function is not NULL, trigger it.
     */

    /* Data to send or read or expected to receive */
    if ((handle->rxRemainingBytes) != 0U)
    {
        SPI_ReceiveTransfer(base, handle);
    }
    if ((handle->txRemainingBytes) != 0U)
    {
        SPI_SendTransfer(base, handle);
    }
    if ((0U == handle->txRemainingBytes) && (0U == handle->rxRemainingBytes))
    {
        /* Only finalize the transfer when kSPI_TxReadyFlag is set which means
           the tx register is empty and all data is sent out to bus */
        if ((SPI_GetStatusFlags(base) & (uint32_t)kSPI_TxReadyFlag) != 0U)
        {
            /* Disable TX and RX interrupt. */
            SPI_DisableInterrupts(base, (uint32_t)kSPI_RxReadyInterruptEnable | (uint32_t)kSPI_TxReadyInterruptEnable);

            /* Set transfer state to idle. */
            handle->state = (uint32_t)kStatus_SPI_Idle;
            /* If callback is not NULL, call this function. */
            if (handle->callback != NULL)
            {
                (handle->callback)(base, handle, handle->state, handle->userData);
            }
        }
    }
}

/*!
 * brief Interrupts a handler for the SPI slave.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_slave_handle_t structure which stores the transfer state
 */
void SPI_SlaveTransferHandleIRQ(SPI_Type *base, spi_slave_handle_t *handle)
{
    assert((NULL != base) && (NULL != handle));

    /* IRQ behaviour:
     * - First interrupt is triggered by receive ready interrupt. The transfer function then
     *   tries read data and transmit data interleaved that results to strategy to process
     *   as many items as possible.
     * - In the last interrupt, the last state is known by empty rxBuffer. If there is nothing
     *   to receive or send - both operations have been finished and interrupt can be disabled.
     *   If the callback function is not NULL, call it.
     */

    /* Sending data to TXDAT first in case of data missing. */
    if (handle->txRemainingBytes != 0U)
    {
        SPI_SendTransfer(base, handle);
    }

    /* Read data from RXDAT. */
    if (handle->rxRemainingBytes != 0U)
    {
        SPI_ReceiveTransfer(base, handle);
    }

    if ((0U == handle->txRemainingBytes) && (0U == handle->rxRemainingBytes))
    {
        /* Only finalize the transfer when kSPI_TxReadyFlag is set which means
           the tx register is empty and all data is sent out to bus */
        if ((SPI_GetStatusFlags(base) & (uint32_t)kSPI_TxReadyFlag) != 0U)
        {
            /* Disable RX interrupt. */
            SPI_DisableInterrupts(base, (uint32_t)kSPI_RxReadyInterruptEnable | (uint32_t)kSPI_TxReadyInterruptEnable);
            /* Set transfer state to idle. */
            handle->state = (uint32_t)kStatus_SPI_Idle;
            /* If callback is not NULL, call this function. */
            if (handle->callback != NULL)
            {
                (handle->callback)(base, handle, handle->state, handle->userData);
            }
        }
    }
}

static void SPI_CommonIRQHandler(SPI_Type *base, void *param)
{
    if (SPI_IsMaster(base))
    {
        s_spiMasterIsr(base, (spi_master_handle_t *)param);
    }
    else
    {
        s_spiSlaveIsr(base, (spi_slave_handle_t *)param);
    }
}

#if defined(SPI0)
void SPI0_DriverIRQHandler(void);
void SPI0_DriverIRQHandler(void)
{
    assert(s_spiHandle[0] != NULL);
    SPI_CommonIRQHandler(SPI0, s_spiHandle[0]);
}
#endif

#if defined(SPI1)
void SPI1_DriverIRQHandler(void);
void SPI1_DriverIRQHandler(void)
{
    assert(s_spiHandle[1] != NULL);
    SPI_CommonIRQHandler(SPI1, s_spiHandle[1]);
}
#endif
#endif /* FSL_SDK_ENABLE_SPI_TRANSACTIONAL_API */
