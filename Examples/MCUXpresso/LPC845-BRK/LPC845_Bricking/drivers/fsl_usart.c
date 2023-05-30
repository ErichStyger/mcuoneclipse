/*
 * Copyright 2017-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_usart.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpc_miniusart"
#endif

enum _usart_transfer_states
{
    kUSART_TxIdle, /* TX idle. */
    kUSART_TxBusy, /* TX busy. */
    kUSART_RxIdle, /* RX idle. */
    kUSART_RxBusy  /* RX busy. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if defined(FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS) && (FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS)
/* Array of USART handle. */
static usart_handle_t *s_usartHandle[FSL_FEATURE_SOC_USART_COUNT];

/*! @brief IRQ name array */
static const IRQn_Type s_usartIRQ[] = USART_IRQS;

/* Typedef for interrupt handler. */
typedef void (*usart_isr_t)(USART_Type *base, usart_handle_t *handle);

/* USART ISR for transactional APIs. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
static usart_isr_t s_usartIsr = (usart_isr_t)DefaultISR;
#else
static usart_isr_t s_usartIsr;
#endif
#endif /* FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS */

/*! @brief Array to map USART instance number to base address. */
static const uint32_t s_usartBaseAddrs[FSL_FEATURE_SOC_USART_COUNT] = USART_BASE_ADDRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* @brief Array to map USART instance number to CLOCK names */
static const clock_ip_name_t s_usartClock[] = USART_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
/* @brief Array to map USART instance number to RESET names */
static const SYSCON_RSTn_t s_usartRest[] = UART_RSTS_N;
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Get the index corresponding to the USART */
/*! brief Returns instance number for USART peripheral base address. */
uint32_t USART_GetInstance(USART_Type *base)
{
    uint32_t i;

    for (i = 0U; i < (uint32_t)FSL_FEATURE_SOC_USART_COUNT; i++)
    {
        if ((uint32_t)base == s_usartBaseAddrs[i])
        {
            break;
        }
    }

    assert(i < (uint32_t)FSL_FEATURE_SOC_USART_COUNT);
    return i;
}

#if defined(FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS) && (FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS)
/*!
 * brief Get the length of received data in RX ring buffer.
 *
 * param handle USART handle pointer.
 * return Length of received data in RX ring buffer.
 */
size_t USART_TransferGetRxRingBufferLength(usart_handle_t *handle)
{
    size_t size = 0U;

    /* Check arguments */
    assert(NULL != handle);
    uint16_t tmprxRingBufferTail = handle->rxRingBufferTail;
    uint16_t tmprxRingBufferHead = handle->rxRingBufferHead;

    if (tmprxRingBufferTail > tmprxRingBufferHead)
    {
        size = (size_t)tmprxRingBufferHead + (handle->rxRingBufferSize) - (size_t)tmprxRingBufferTail;
    }
    else
    {
        size = (size_t)tmprxRingBufferHead - (size_t)tmprxRingBufferTail;
    }
    return size;
}

static bool USART_TransferIsRxRingBufferFull(usart_handle_t *handle)
{
    bool full = false;

    /* Check arguments */
    assert(NULL != handle);

    if (USART_TransferGetRxRingBufferLength(handle) == (handle->rxRingBufferSize - 1U))
    {
        full = true;
    }
    else
    {
        full = false;
    }
    return full;
}

/*!
 * brief Sets up the RX ring buffer.
 *
 * This function sets up the RX ring buffer to a specific USART handle.
 *
 * When the RX ring buffer is used, data received are stored into the ring buffer even when the
 * user doesn't call the USART_TransferReceiveNonBlocking() API. If there is already data received
 * in the ring buffer, the user can get the received data from the ring buffer directly.
 *
 * note When using the RX ring buffer, one byte is reserved for internal use. In other
 * words, if ringBufferSize is 32, then only 31 bytes are used for saving data.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param ringBuffer Start address of the ring buffer for background receiving. Pass NULL to disable the ring buffer.
 * param ringBufferSize size of the ring buffer.
 */
void USART_TransferStartRingBuffer(USART_Type *base, usart_handle_t *handle, uint8_t *ringBuffer, size_t ringBufferSize)
{
    /* Check arguments */
    assert(NULL != base);
    assert(NULL != handle);
    assert(NULL != ringBuffer);

    /* Setup the ringbuffer address */
    handle->rxRingBuffer     = ringBuffer;
    handle->rxRingBufferSize = ringBufferSize;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;

    /* Start receive data read interrupt and reveive overrun interrupt. */
    USART_EnableInterrupts(base,
                           (uint32_t)kUSART_RxReadyInterruptEnable | (uint32_t)kUSART_HardwareOverRunInterruptEnable);
}

/*!
 * brief Aborts the background transfer and uninstalls the ring buffer.
 *
 * This function aborts the background transfer and uninstalls the ring buffer.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 */
void USART_TransferStopRingBuffer(USART_Type *base, usart_handle_t *handle)
{
    /* Check arguments */
    assert(NULL != base);
    assert(NULL != handle);

    /* If USART is in idle state, dsiable the interrupts for ring buffer. */
    if (handle->rxState == (uint8_t)kUSART_RxIdle)
    {
        USART_DisableInterrupts(
            base, (uint32_t)kUSART_RxReadyInterruptEnable | (uint32_t)kUSART_HardwareOverRunInterruptEnable);
    }
    handle->rxRingBuffer     = NULL;
    handle->rxRingBufferSize = 0U;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;
}
#endif /* FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS */

/*!
 * brief Initializes a USART instance with user configuration structure and peripheral clock.
 *
 * This function configures the USART module with the user-defined settings. The user can configure the configuration
 * structure and also get the default configuration by using the USART_GetDefaultConfig() function.
 * Example below shows how to use this API to configure USART.
 * code
 *  usart_config_t usartConfig;
 *  usartConfig.baudRate_Bps = 115200U;
 *  usartConfig.parityMode = kUSART_ParityDisabled;
 *  usartConfig.stopBitCount = kUSART_OneStopBit;
 *  USART_Init(USART1, &usartConfig, 20000000U);
 * endcode
 *
 * param base USART peripheral base address.
 * param config Pointer to user-defined configuration structure.
 * param srcClock_Hz USART clock source frequency in HZ.
 * retval kStatus_USART_BaudrateNotSupport Baudrate is not support in current clock source.
 * retval kStatus_InvalidArgument USART base address is not valid
 * retval kStatus_Success Status USART initialize succeed
 */
status_t USART_Init(USART_Type *base, const usart_config_t *config, uint32_t srcClock_Hz)
{
    /* Check arguments */
    assert(!((NULL == base) || (NULL == config) || (0U == srcClock_Hz)));
#if defined(FSL_FEATURE_USART_HAS_RXIDLETO_CHECK) && FSL_FEATURE_USART_HAS_RXIDLETO_CHECK
    assert(8U > config->rxIdleTimeout);
#endif

    status_t status = kStatus_Success;

    uint32_t instance = USART_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    CLOCK_EnableClock(s_usartClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(s_usartRest[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

    /* Setup configuration and enable USART to configure other register. */
    base->CFG = USART_CFG_PARITYSEL(config->parityMode) | USART_CFG_STOPLEN(config->stopBitCount) |
                USART_CFG_SYNCEN((uint32_t)config->syncMode >> 1) |
                USART_CFG_DATALEN((uint8_t)config->bitCountPerChar) | USART_CFG_LOOP(config->loopback) |
                USART_CFG_SYNCMST(config->syncMode) | USART_CFG_CLKPOL(config->clockPolarity) |
                USART_CFG_CTSEN(config->enableHardwareFlowControl) | USART_CFG_ENABLE_MASK;
#if defined(FSL_FEATURE_USART_HAS_RXIDLETO_CHECK) && FSL_FEATURE_USART_HAS_RXIDLETO_CHECK
    base->CTL |= USART_CTL_RXIDLETOCFG(config->rxIdleTimeout);
#endif
#if defined(FSL_SDK_USART_DRIVER_ENABLE_BAUDRATE_AUTO_GENERATE) && (FSL_SDK_USART_DRIVER_ENABLE_BAUDRATE_AUTO_GENERATE)
    if (0U != config->baudRate_Bps)
    {
        /* Setup baudrate */
        if (kStatus_Success != USART_SetBaudRate(base, config->baudRate_Bps, srcClock_Hz))
        {
            status = kStatus_USART_BaudrateNotSupport;
        }
    }
#else
    base->BRG       = FSL_SDK_USART_BRG_VALUE;
#if defined(FSL_FEATURE_USART_HAS_OSR_REGISTER) && (FSL_FEATURE_USART_HAS_OSR_REGISTER)
    base->OSR       = FSL_SDK_USART_BRG_VALUE;
#endif /* FSL_FEATURE_USART_HAS_OSR_REGISTER */
#endif /* FSL_SDK_USART_DRIVER_ENABLE_BAUDRATE_AUTO_GENERATE */

    if (status == kStatus_Success)
    {
        USART_EnableContinuousSCLK(base, config->enableContinuousSCLK);

        /* Setup the USART transmit and receive. */
        USART_EnableTx(base, config->enableTx);
        USART_EnableRx(base, config->enableRx);
    }

    return status;
}

/*!
 * brief Deinitializes a USART instance.
 *
 * This function waits for TX complete, disables the USART clock.
 *
 * param base USART peripheral base address.
 */
void USART_Deinit(USART_Type *base)
{
    /* Check arguments */
    assert(NULL != base);
    /* Wait for data transmit complete. */
    while (0U == (base->STAT & USART_STAT_TXIDLE_MASK))
    {
    }
    /* Disable the USART module. */
    base->CFG &= ~(USART_CFG_ENABLE_MASK);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    CLOCK_DisableClock(s_usartClock[USART_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the default configuration structure.
 *
 * This function initializes the USART configuration structure to a default value. The default
 * values are:
 *   usartConfig->baudRate_Bps = 9600U;
 *   usartConfig->parityMode = kUSART_ParityDisabled;
 *   usartConfig->stopBitCount = kUSART_OneStopBit;
 *   usartConfig->bitCountPerChar = kUSART_8BitsPerChar;
 *   usartConfig->loopback = false;
 *   usartConfig->enableTx = false;
 *   usartConfig->enableRx = false;
 *   usartConfig->enableHardwareFlowControl = false;
 *   ...
 * param config Pointer to configuration structure.
 */
void USART_GetDefaultConfig(usart_config_t *config)
{
    /* Check arguments */
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    /* Set always all members ! */
    config->baudRate_Bps              = 9600U;
    config->parityMode                = kUSART_ParityDisabled;
    config->stopBitCount              = kUSART_OneStopBit;
    config->bitCountPerChar           = kUSART_8BitsPerChar;
    config->loopback                  = false;
    config->enableRx                  = false;
    config->enableTx                  = false;
    config->syncMode                  = kUSART_SyncModeDisabled;
    config->enableContinuousSCLK      = false;
    config->clockPolarity             = kUSART_RxSampleOnFallingEdge;
    config->enableHardwareFlowControl = false;
#if defined(FSL_FEATURE_USART_HAS_RXIDLETO_CHECK) && FSL_FEATURE_USART_HAS_RXIDLETO_CHECK
    config->rxIdleTimeout = 0U;
#endif
}

/*!
 * brief Sets the USART instance baud rate.
 *
 * This function configures the USART module baud rate. This function is used to update
 * the USART module baud rate after the USART module is initialized by the USART_Init.
 * code
 *  USART_SetBaudRate(USART1, 115200U, 20000000U);
 * endcode
 *
 * param base USART peripheral base address.
 * param baudrate_Bps USART baudrate to be set.
 * param srcClock_Hz USART clock source frequency in HZ.
 * retval kStatus_USART_BaudrateNotSupport Baudrate is not support in current clock source.
 * retval kStatus_Success Set baudrate succeed.
 * retval kStatus_InvalidArgument One or more arguments are invalid.
 */
status_t USART_SetBaudRate(USART_Type *base, uint32_t baudrate_Bps, uint32_t srcClock_Hz)
{
    /* check arguments */
    assert(!((NULL == base) || (0U == baudrate_Bps) || (0U == srcClock_Hz)));

#if defined(FSL_FEATURE_USART_HAS_OSR_REGISTER) && (FSL_FEATURE_USART_HAS_OSR_REGISTER)
    uint32_t best_diff = (uint32_t)-1, best_osrval = 0xf, best_brgval = (uint32_t)-1;
    uint32_t diff = 0U, brgval = 0U, osrval = 0U, baudrate = 0U;

    /* If synchronous is enable, only BRG register is useful. */
    if (0U != (base->CFG & USART_CFG_SYNCEN_MASK))
    {
        brgval    = srcClock_Hz / baudrate_Bps;
        base->BRG = brgval - 1U;
    }
    else
    {
        for (osrval = best_osrval; osrval >= 8U; osrval--)
        {
            brgval = (((srcClock_Hz * 10U) / ((osrval + 1U) * baudrate_Bps)) - 5U) / 10U;
            if (brgval > 0xFFFFU)
            {
                continue;
            }
            baudrate = srcClock_Hz / ((osrval + 1U) * (brgval + 1U));
            diff     = baudrate_Bps < baudrate ? baudrate - baudrate_Bps : baudrate_Bps - baudrate;
            if (diff < best_diff)
            {
                best_diff   = diff;
                best_osrval = osrval;
                best_brgval = brgval;
            }
        }

        /* value over range */
        if (best_brgval > 0xFFFFU)
        {
            return kStatus_USART_BaudrateNotSupport;
        }

        /* If the baud rate caculated is not very precise, please select the FRG clock as
         * the USART's source clock, and set the FRG frequency to a more suitable value.
         */
        assert(best_diff < ((baudrate_Bps / 100U) * 3U));

        base->OSR = best_osrval;
        base->BRG = best_brgval;
    }
#else
    uint32_t brgval = 0U;
    /* If synchronous is enable. */
    if (0U != (base->CFG & USART_CFG_SYNCEN_MASK))
    {
        brgval    = srcClock_Hz / baudrate_Bps;
        base->BRG = brgval - 1U;
    }
    else
    {
        /* In asynchronous mode, The baud rate divider divides the common USART
         * peripheral clock by a factor of 16 multiplied by the baud rate value
         * to provide the baud rate.
         */
        brgval = (srcClock_Hz >> 4U) / baudrate_Bps;

        /* If the baud rate caculated is not very precise, Please set the FRG register for
         * getting a more precise suitable frequency.
         */
        assert((((srcClock_Hz >> 4U) / brgval) - baudrate_Bps) < ((baudrate_Bps / 100U) * 3U));
        base->BRG = brgval - 1U;
    }
#endif /* FSL_FEATURE_USART_HAS_OSR_REGISTER */

    return kStatus_Success;
}

/*!
 * brief Writes to the TX register using a blocking method.
 *
 * This function polls the TX register, waits for the TX register to be empty.
 *
 * param base USART peripheral base address.
 * param data Start address of the data to write.
 * param length Size of the data to write.
 * retval kStatus_USART_Timeout Transmission timed out and was aborted.
 * retval kStatus_Success Successfully wrote all data.
 */
status_t USART_WriteBlocking(USART_Type *base, const uint8_t *data, size_t length)
{
    /* Check arguments */
    assert(!((NULL == base) || (NULL == data)));
#if UART_RETRY_TIMES
    uint32_t waitTimes;
#endif

    for (; length > 0U; length--)
    {
        /* Wait for TX is ready to transmit new data. */
#if UART_RETRY_TIMES
        waitTimes = UART_RETRY_TIMES;
        while ((0U == (base->STAT & USART_STAT_TXRDY_MASK)) && (0U != --waitTimes))
#else
        while (0U == (base->STAT & USART_STAT_TXRDY_MASK))
#endif
        {
        }
#if UART_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_USART_Timeout;
        }
#endif
        base->TXDAT = *data;
        data++;
    }
    /* Wait to finish transfer */
#if UART_RETRY_TIMES
    waitTimes = UART_RETRY_TIMES;
    while ((0U == (base->STAT & USART_STAT_TXIDLE_MASK)) && (0U != --waitTimes))
#else
    while (0U == (base->STAT & USART_STAT_TXIDLE_MASK))
#endif
    {
    }
#if UART_RETRY_TIMES
    if (waitTimes == 0U)
    {
        return kStatus_USART_Timeout;
    }
#endif
    return kStatus_Success;
}

/*!
 * brief Read RX data register using a blocking method.
 *
 * This function polls the RX register, waits for the RX register to be full.
 *
 * param base USART peripheral base address.
 * param data Start address of the buffer to store the received data.
 * param length Size of the buffer.
 * retval kStatus_USART_FramingError Receiver overrun happened while receiving data.
 * retval kStatus_USART_ParityError Noise error happened while receiving data.
 * retval kStatus_USART_NoiseError Framing error happened while receiving data.
 * retval kStatus_USART_RxError Overflow or underflow happened.
 * retval kStatus_USART_Timeout Transmission timed out and was aborted.
 * retval kStatus_Success Successfully received all data.
 */
status_t USART_ReadBlocking(USART_Type *base, uint8_t *data, size_t length)
{
    uint32_t statusFlag;
    status_t status = kStatus_Success;

    /* Check arguments */
    assert(!((NULL == base) || (NULL == data)));

#if UART_RETRY_TIMES
    uint32_t waitTimes;
#endif

    for (; length > 0U; length--)
    {
        /* loop until receive is ready to read */
#if UART_RETRY_TIMES
        waitTimes = UART_RETRY_TIMES;
        while (((base->STAT & USART_STAT_RXRDY_MASK) == 0U) && (--waitTimes != 0U))
#else
        while ((base->STAT & USART_STAT_RXRDY_MASK) == 0U)
#endif
        {
        }
#if UART_RETRY_TIMES
        if (waitTimes == 0U)
        {
            status = kStatus_USART_Timeout;
            break;
        }
#endif
        /* Check receive statusFlag */
        statusFlag = base->STAT;
        base->STAT |= statusFlag;
        if ((statusFlag & USART_STAT_OVERRUNINT_MASK) != 0U)
        {
            status = kStatus_USART_HardwareOverrun;
            break;
        }
        if ((statusFlag & USART_STAT_PARITYERRINT_MASK) != 0U)
        {
            status = kStatus_USART_ParityError;
        }
        if ((statusFlag & USART_STAT_FRAMERRINT_MASK) != 0U)
        {
            status = kStatus_USART_FramingError;
        }
        if ((statusFlag & USART_STAT_RXNOISEINT_MASK) != 0U)
        {
            status = kStatus_USART_NoiseError;
        }
        if (kStatus_Success == status)
        {
            *data = (uint8_t)base->RXDAT;
            data++;
        }
        else
        {
            break;
        }
    }
    return status;
}

#if defined(FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS) && (FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS)
/*!
 * brief Initializes the USART handle.
 *
 * This function initializes the USART handle which can be used for other USART
 * transactional APIs. Usually, for a specified USART instance,
 * call this API once to get the initialized handle.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 */
status_t USART_TransferCreateHandle(USART_Type *base,
                                    usart_handle_t *handle,
                                    usart_transfer_callback_t callback,
                                    void *userData)
{
    uint32_t instance = 0;

    /* Check 'base' */
    assert(!((NULL == base) || (NULL == handle)));

    instance = USART_GetInstance(base);

    (void)memset(handle, 0, sizeof(*handle));
    /* Set the TX/RX state. */
    handle->rxState = (uint8_t)kUSART_RxIdle;
    handle->txState = (uint8_t)kUSART_TxIdle;
    /* Set the callback and user data. */
    handle->callback = callback;
    handle->userData = userData;
    /* Store the handle data to global variables. */
    s_usartHandle[instance] = handle;
    /* Mapping the interrupt function. */
    s_usartIsr = USART_TransferHandleIRQ;
    /* Enable interrupt in NVIC. */
    (void)EnableIRQ(s_usartIRQ[instance]);

    return kStatus_Success;
}

/*!
 * brief Transmits a buffer of data using the interrupt method.
 *
 * This function sends data using an interrupt method. This is a non-blocking function, which
 * returns directly without waiting for all data to be written to the TX register. When
 * all data is written to the TX register in the IRQ handler, the USART driver calls the callback
 * function and passes the ref kStatus_USART_TxIdle as status parameter.
 *
 * note The kStatus_USART_TxIdle is passed to the upper layer when all data is written
 * to the TX register. However it does not ensure that all data are sent out. Before disabling the TX,
 * check the kUSART_TransmissionCompleteFlag to ensure that the TX is finished.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param xfer USART transfer structure. See  #usart_transfer_t.
 * retval kStatus_Success Successfully start the data transmission.
 * retval kStatus_USART_TxBusy Previous transmission still not finished, data not all written to TX register yet.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t USART_TransferSendNonBlocking(USART_Type *base, usart_handle_t *handle, usart_transfer_t *xfer)
{
    /* Check arguments */
    assert(!((NULL == base) || (NULL == handle) || (NULL == xfer)));
    /* Check xfer members */
    assert(!((0U == xfer->dataSize) || (NULL == xfer->txData)));

    /* Return error if current TX busy. */
    if ((uint8_t)kUSART_TxBusy == handle->txState)
    {
        return kStatus_USART_TxBusy;
    }
    else
    {
        handle->txData        = xfer->txData;
        handle->txDataSize    = xfer->dataSize;
        handle->txDataSizeAll = xfer->dataSize;
        handle->txState       = (uint8_t)kUSART_TxBusy;

        USART_EnableInterrupts(base, (uint32_t)kUSART_TxReadyInterruptEnable);
        /* Clear transmit disable bit. */
        base->CTL &= ~USART_CTL_TXDIS_MASK;
    }
    return kStatus_Success;
}

/*!
 * brief Aborts the interrupt-driven data transmit.
 *
 * This function aborts the interrupt driven data sending. The user can get the remainBtyes to find out
 * how many bytes are still not sent out.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 */
void USART_TransferAbortSend(USART_Type *base, usart_handle_t *handle)
{
    assert(NULL != handle);

    USART_DisableInterrupts(base, (uint32_t)kUSART_TxReadyInterruptEnable);
    /* Disable transmit after data being transmitted. */
    USART_EnableTx(base, false);
    handle->txDataSize = 0;
    handle->txState    = (uint8_t)kUSART_TxIdle;
}

/*!
 * brief Get the number of bytes that have been written to USART TX register.
 *
 * This function gets the number of bytes that have been written to USART TX
 * register by interrupt method.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param count Send bytes count.
 * retval kStatus_NoTransferInProgress No send in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t USART_TransferGetSendCount(USART_Type *base, usart_handle_t *handle, uint32_t *count)
{
    assert(NULL != handle);
    assert(NULL != count);

    status_t status;

    if ((uint8_t)kUSART_TxIdle == handle->txState)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->txDataSizeAll - handle->txDataSize;
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Receives a buffer of data using an interrupt method.
 *
 * This function receives data using an interrupt method. This is a non-blocking function, which
 *  returns without waiting for all data to be received.
 * If the RX ring buffer is used and not empty, the data in the ring buffer is copied and
 * the parameter p receivedBytes shows how many bytes are copied from the ring buffer.
 * After copying, if the data in the ring buffer is not enough to read, the receive
 * request is saved by the USART driver. When the new data arrives, the receive request
 * is serviced first. When all data is received, the USART driver notifies the upper layer
 * through a callback function and passes the status parameter ref kStatus_USART_RxIdle.
 * For example, the upper layer needs 10 bytes but there are only 5 bytes in the ring buffer.
 * The 5 bytes are copied to the xfer->data and this function returns with the
 * parameter p receivedBytes set to 5. For the left 5 bytes, newly arrived data is
 * saved from the xfer->data[5]. When 5 bytes are received, the USART driver notifies the upper layer.
 * If the RX ring buffer is not enabled, this function enables the RX and RX interrupt
 * to receive data to the xfer->data. When all data is received, the upper layer is notified.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param xfer USART transfer structure, see #usart_transfer_t.
 * param receivedBytes Bytes received from the ring buffer directly.
 * retval kStatus_Success Successfully queue the transfer into transmit queue.
 * retval kStatus_USART_RxBusy Previous receive request is not finished.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t USART_TransferReceiveNonBlocking(USART_Type *base,
                                          usart_handle_t *handle,
                                          usart_transfer_t *xfer,
                                          size_t *receivedBytes)
{
    status_t status = kStatus_Success;
    uint32_t i;
    /* How many bytes to copy from ring buffer to user memory. */
    size_t bytesToCopy = 0U;
    /* How many bytes to receive. */
    size_t bytesToReceive;
    /* How many bytes currently have received. */
    size_t bytesCurrentReceived;

    /* Check arguments */
    assert(!((NULL == base) || (NULL == handle) || (NULL == xfer)));
    /* Check xfer members */
    assert(!((0U == xfer->dataSize) || (NULL == xfer->rxData)));

    /* How to get data:
       1. If RX ring buffer is not enabled, then save xfer->data and xfer->dataSize
          to uart handle, enable interrupt to store received data to xfer->data. When
          all data received, trigger callback.
       2. If RX ring buffer is enabled and not empty, get data from ring buffer first.
          If there are enough data in ring buffer, copy them to xfer->data and return.
          If there are not enough data in ring buffer, copy all of them to xfer->data,
          save the xfer->data remained empty space to uart handle, receive data
          to this empty space and trigger callback when finished. */
    if ((uint8_t)kUSART_RxBusy == handle->rxState)
    {
        status = kStatus_USART_RxBusy;
    }
    else
    {
        bytesToReceive       = xfer->dataSize;
        bytesCurrentReceived = 0U;
        /* If RX ring buffer is used. */
        if (handle->rxRingBuffer != NULL)
        {
            USART_DisableInterrupts(base, (uint32_t)kUSART_RxReadyInterruptEnable);
            /* How many bytes in RX ring buffer currently. */
            bytesToCopy = USART_TransferGetRxRingBufferLength(handle);
            if (bytesToCopy != 0U)
            {
                bytesToCopy = MIN(bytesToReceive, bytesToCopy);
                bytesToReceive -= bytesToCopy;
                /* Copy data from ring buffer to user memory. */
                for (i = 0U; i < bytesToCopy; i++)
                {
                    xfer->rxData[bytesCurrentReceived++] = handle->rxRingBuffer[handle->rxRingBufferTail];
                    /* Wrap to 0. Not use modulo (%) because it might be large and slow. */
                    if ((size_t)handle->rxRingBufferTail + 1U == handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }
            }
            /* If ring buffer does not have enough data, still need to read more data. */
            if (bytesToReceive != 0U)
            {
                /* No data in ring buffer, save the request to UART handle. */
                handle->rxData        = xfer->rxData + bytesCurrentReceived;
                handle->rxDataSize    = bytesToReceive;
                handle->rxDataSizeAll = xfer->dataSize;
                handle->rxState       = (uint8_t)kUSART_RxBusy;
            }

            USART_EnableInterrupts(base, (uint32_t)kUSART_RxReadyInterruptEnable);
            /* Call user callback since all data are received. */
            if (0U == bytesToReceive)
            {
                if (handle->callback != NULL)
                {
                    handle->callback(base, handle, kStatus_USART_RxIdle, handle->userData);
                }
            }
        }
        /* Ring buffer not used. */
        else
        {
            handle->rxData        = xfer->rxData + bytesCurrentReceived;
            handle->rxDataSize    = bytesToReceive;
            handle->rxDataSizeAll = bytesToReceive;
            handle->rxState       = (uint8_t)kUSART_RxBusy;

            USART_EnableInterrupts(
                base, (uint32_t)kUSART_RxReadyInterruptEnable | (uint32_t)kUSART_HardwareOverRunInterruptEnable);
        }
        /* Return the how many bytes have read. */
        if (receivedBytes != NULL)
        {
            *receivedBytes = bytesCurrentReceived;
        }
    }
    return status;
}

/*!
 * brief Aborts the interrupt-driven data receiving.
 *
 * This function aborts the interrupt-driven data receiving. The user can get the remainBytes to find out
 * how many bytes not received yet.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 */
void USART_TransferAbortReceive(USART_Type *base, usart_handle_t *handle)
{
    assert(NULL != handle);

    /* Only abort the receive to handle->rxData, the RX ring buffer is still working. */
    if (handle->rxRingBuffer == NULL)
    {
        USART_DisableInterrupts(
            base, (uint32_t)kUSART_RxReadyInterruptEnable | (uint32_t)kUSART_HardwareOverRunInterruptEnable);
    }

    handle->rxDataSize = 0U;
    handle->rxState    = (uint8_t)kUSART_RxIdle;
}

/*!
 * brief Get the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 * param count Receive bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t USART_TransferGetReceiveCount(USART_Type *base, usart_handle_t *handle, uint32_t *count)
{
    assert(NULL != handle);
    assert(NULL != count);
    status_t status = kStatus_Success;

    if ((uint8_t)kUSART_RxIdle == handle->rxState)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->rxDataSizeAll - handle->rxDataSize;
    }

    return status;
}

/*!
 * brief USART IRQ handle function.
 *
 * This function handles the USART transmit and receive IRQ request.
 *
 * param base USART peripheral base address.
 * param handle USART handle pointer.
 */
void USART_TransferHandleIRQ(USART_Type *base, usart_handle_t *handle)
{
    /* Check arguments */
    assert((NULL != base) && (NULL != handle));

    bool receiveEnabled = (handle->rxDataSize != 0U) || (handle->rxRingBuffer != NULL);
    bool sendEnabled    = (handle->txDataSize != 0U);
    uint32_t status     = USART_GetStatusFlags(base);
    uint8_t tmpdata     = (uint8_t)base->RXDAT;

    /* If RX overrun. */
    if (((uint32_t)kUSART_HardwareOverrunFlag & status) != 0U)
    {
        /* Clear rx error state. */
        base->STAT |= USART_STAT_OVERRUNINT_MASK;
        /* Trigger callback. */
        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kStatus_USART_RxError, handle->userData);
        }
    }
#if defined(FSL_FEATURE_USART_HAS_RXIDLETO_CHECK) && FSL_FEATURE_USART_HAS_RXIDLETO_CHECK
    /* If RX idle time out */
    if (((uint32_t)kUSART_RxIdleTimeoutFlag & status) != 0U)
    {
        /* Clear rx error state. */
        base->STAT |= USART_STAT_RXIDLETO_MASK;
        /* Trigger callback. */
        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kStatus_USART_RxIdleTimeout, handle->userData);
        }
    }
#endif
    /* Receive data */
    if ((receiveEnabled) && (((uint32_t)kUSART_RxReady & status) != 0U))
    {
        /* Receive to app bufffer if app buffer is present */
        if (handle->rxDataSize != 0U)
        {
            *handle->rxData = tmpdata;
            handle->rxDataSize--;
            handle->rxData++;

            if (handle->rxDataSize == 0U)
            {
                if (handle->rxRingBuffer == NULL)
                {
                    USART_DisableInterrupts(base, (uint32_t)kUSART_RxReadyInterruptEnable |
                                                      (uint32_t)kUSART_HardwareOverRunInterruptEnable);
                }
                handle->rxState = (uint8_t)kUSART_RxIdle;
                if (handle->callback != NULL)
                {
                    handle->callback(base, handle, kStatus_USART_RxIdle, handle->userData);
                }
            }
        }
        /* Otherwise receive to ring buffer if ring buffer is present */
        else
        {
            if (handle->rxRingBuffer != NULL)
            {
                if (USART_TransferIsRxRingBufferFull(handle))
                {
                    if (handle->callback != NULL)
                    {
                        handle->callback(base, handle, kStatus_USART_RxRingBufferOverrun, handle->userData);
                    }
                }
                /* If ring buffer is still full after callback function, the oldest data is overridden. */
                if (USART_TransferIsRxRingBufferFull(handle))
                {
                    /* Increase handle->rxRingBufferTail to make room for new data. */
                    if ((size_t)handle->rxRingBufferTail + 1U == handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }

                handle->rxRingBuffer[handle->rxRingBufferHead] = tmpdata;

                /* Increase handle->rxRingBufferHead. */
                if ((size_t)handle->rxRingBufferHead + 1U == handle->rxRingBufferSize)
                {
                    handle->rxRingBufferHead = 0U;
                }
                else
                {
                    handle->rxRingBufferHead++;
                }
            }
        }
    }
    /* Send data */
    if (sendEnabled && (((uint32_t)kUSART_TxReady & status) != 0U))
    {
        base->TXDAT = *handle->txData;
        handle->txDataSize--;
        handle->txData++;

        if (0U == handle->txDataSize)
        {
            USART_DisableInterrupts(base, (uint32_t)kUSART_TxReadyInterruptEnable);
            handle->txState = (uint8_t)kUSART_TxIdle;
            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kStatus_USART_TxIdle, handle->userData);
            }
        }
    }
}

#if defined(USART0)
void USART0_DriverIRQHandler(void);
void USART0_DriverIRQHandler(void)
{
    s_usartIsr(USART0, s_usartHandle[0]);
}
#endif

#if defined(USART1)
void USART1_DriverIRQHandler(void);
void USART1_DriverIRQHandler(void)
{
    s_usartIsr(USART1, s_usartHandle[1]);
}
#endif

#if defined(USART2)
void USART2_DriverIRQHandler(void);
void USART2_DriverIRQHandler(void)
{
    s_usartIsr(USART2, s_usartHandle[2]);
}
#endif

#if defined(USART3)
void PIN_INT6_USART3_DriverIRQHandler(void);
void PIN_INT6_USART3_DriverIRQHandler(void)
{
    s_usartIsr(USART3, s_usartHandle[3]);
}
#endif

#if defined(USART4)
void PIN_INT7_USART4_DriverIRQHandler(void);
void PIN_INT7_USART4_DriverIRQHandler(void)
{
    s_usartIsr(USART4, s_usartHandle[4]);
}
#endif
#endif /* FSL_SDK_ENABLE_USART_DRIVER_TRANSACTIONAL_APIS */
