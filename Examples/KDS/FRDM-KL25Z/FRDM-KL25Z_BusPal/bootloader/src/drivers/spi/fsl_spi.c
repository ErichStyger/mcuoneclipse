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

#include "fsl_spi.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/
/*! @brief SPI transfer state, which is used for SPI transactiaonl APIs' internal state. */
enum _spi_transfer_states_t
{
    kSPI_Idle = 0x0, /*!< SPI is idle state */
    kSPI_Busy        /*!< SPI is busy tranferring data. */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance for SPI module.
 *
 * @param base SPI base address
 */
uint32_t SPI_GetInstance(SPI_Type *base);

/*!
 * @brief Sends a buffer of data bytes in non-blocking way.
 *
 * @param base SPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void SPI_WriteNonBlocking(SPI_Type *base, uint8_t *buffer, size_t size);

/*!
 * @brief Receive a buffer of data bytes in non-blocking way.
 *
 * @param base SPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void SPI_ReadNonBlocking(SPI_Type *base, uint8_t *buffer, size_t size);

/*!
 * @brief Send a piece of data for SPI.
 *
 * This function computes the number of data to be written into D register or Tx FIFO,
 * and write the data into it. At the same time, this function updates the values in
 * master handle structure.
 *
 * @param handle Pointer to SPI master handle structure.
 */
static void SPI_SendTransaction(SPI_Type *base, spi_master_handle_t *handle);

/*!
 * @brief Receive a piece of data for SPI master.
 *
 * This function computes the number of data to receive from D register or Rx FIFO,
 * and write the data to destination address. At the same time, this function updates
 * the values in master handle structure.
 *
 * @param handle Pointer to SPI master handle structure.
 */
static void SPI_ReceiveTransaction(SPI_Type *base, spi_master_handle_t *handle);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* SPI internal handle pointer array */
static spi_master_handle_t *s_spiHandle[FSL_FEATURE_SOC_SPI_COUNT];
/* Base pointer array */
static SPI_Type *const s_spiBases[] = SPI_BASE_PTRS;
/* IRQ name array */
static const IRQn_Type s_spiIRQ[] = SPI_IRQS;
/* Clock array name */
static const clock_ip_name_t s_spiClock[] = SPI_CLOCKS;

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t SPI_GetInstance(SPI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < FSL_FEATURE_SOC_SPI_COUNT; instance++)
    {
        if (s_spiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < FSL_FEATURE_SOC_SPI_COUNT);

    return instance;
}

static void SPI_WriteNonBlocking(SPI_Type *base, uint8_t *buffer, size_t size)
{
    uint32_t i = 0;
    uint8_t bytesPerFrame = 1U;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Check if 16 bits or 8 bits */
    bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#endif

    while (i < size)
    {
        if (buffer != NULL)
        {
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
            /*16 bit mode*/
            if (base->C2 & SPI_C2_SPIMODE_MASK)
            {
                base->DL = *buffer++;
                base->DH = *buffer++;
            }
            /* 8 bit mode */
            else
            {
                base->DL = *buffer++;
            }
#else
            base->D = *buffer++;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
        }
        /* Send dummy data */
        else
        {
            SPI_WriteData(base, SPI_DUMMYDATA);
        }
        i += bytesPerFrame;
    }
}

static void SPI_ReadNonBlocking(SPI_Type *base, uint8_t *buffer, size_t size)
{
    uint32_t i = 0;
    uint8_t bytesPerFrame = 1U;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Check if 16 bits or 8 bits */
    bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#endif

    while (i < size)
    {
        if (buffer != NULL)
        {
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
            /*16 bit mode*/
            if (base->C2 & SPI_C2_SPIMODE_MASK)
            {
                *buffer++ = base->DL;
                *buffer++ = base->DH;
            }
            /* 8 bit mode */
            else
            {
                *buffer++ = base->DL;
            }
#else
            *buffer++ = base->D;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
        }
        else
        {
            SPI_ReadData(base);
        }
        i += bytesPerFrame;
    }
}

static void SPI_SendTransaction(SPI_Type *base, spi_master_handle_t *handle)
{
    uint8_t bytes = MIN((handle->watermark * 2U), handle->txRemainingBytes);
    uint8_t val = 1U;

    /* Read S register and ensure SPTEF is 1, otherwise the write would be ignored. */
    if (handle->watermark == 1U)
    {
        val = (base->S & SPI_S_SPTEF_MASK);
        if (bytes != 0U)
        {
            bytes = handle->bytePerFrame;
        }
    }
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && (FSL_FEATURE_SPI_HAS_FIFO)
    else
    {
        val = (base->S & SPI_S_TNEAREF_MASK);
    }
#endif

    /* Write data */
    if (val)
    {
        SPI_WriteNonBlocking(base, handle->txData, bytes);

        /* Update handle information */
        if (handle->txData)
        {
            handle->txData += bytes;
        }
        handle->txRemainingBytes -= bytes;
    }
}

static void SPI_ReceiveTransaction(SPI_Type *base, spi_master_handle_t *handle)
{
    uint8_t bytes = MIN((handle->watermark * 2U), handle->rxRemainingBytes);
    uint8_t val = 1U;

    /* Read S register and ensure SPRF is 1, otherwise the write would be ignored. */
    if (handle->watermark == 1U)
    {
        val = base->S & SPI_S_SPRF_MASK;
        if (bytes != 0U)
        {
            bytes = handle->bytePerFrame;
        }
    }

    if (val)
    {
        SPI_ReadNonBlocking(base, handle->rxData, bytes);

        /* Update information in handle */
        if (handle->rxData)
        {
            handle->rxData += bytes;
        }
        handle->rxRemainingBytes -= bytes;
    }
}

void SPI_MasterGetDefaultConfig(spi_master_config_t *config)
{
    config->enableMaster = true;
    config->enableStopInWaitMode = false;
    config->polarity = kSPI_ClockPolarityActiveHigh;
    config->phase = kSPI_ClockPhaseFirstEdge;
    config->direction = kSPI_MsbFirst;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    config->dataMode = kSPI_8BitMode;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    config->txWatermark = kSPI_TxFifoOneHalfEmpty;
    config->rxWatermark = kSPI_RxFifoOneHalfFull;
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    config->pinMode = kSPI_PinModeNormal;
    config->outputMode = kSPI_SlaveSelectAutomaticOutput;
    config->baudRate_Bps = 500000U;
}

void SPI_MasterInit(SPI_Type *base, const spi_master_config_t *config, uint32_t srcClock_Hz)
{
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_spiClock[SPI_GetInstance(base)]);

    /* Disable SPI before configuration */
    base->C1 &= ~SPI_C1_SPE_MASK;

    /* Configure clock polarity and phase, set SPI to master */
    base->C1 = SPI_C1_MSTR(1U) | SPI_C1_CPOL(config->polarity) | SPI_C1_CPHA(config->phase) |
               SPI_C1_SSOE(config->outputMode & 1U) | SPI_C1_LSBFE(config->direction);

/* Set data mode, and also pin mode and mode fault settings */
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    base->C2 = SPI_C2_MODFEN(config->outputMode >> 1U) | SPI_C2_BIDIROE(config->pinMode >> 1U) |
               SPI_C2_SPISWAI(config->enableStopInWaitMode) | SPI_C2_SPC0(config->pinMode & 1U) |
               SPI_C2_SPIMODE(config->dataMode);
#else
    base->C2 = SPI_C2_MODFEN(config->outputMode >> 1U) | SPI_C2_BIDIROE(config->pinMode >> 1U) |
               SPI_C2_SPISWAI(config->enableStopInWaitMode) | SPI_C2_SPC0(config->pinMode & 1U);
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

/* Set watermark, FIFO is enabled */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        base->C3 = SPI_C3_TNEAREF_MARK(config->txWatermark) | SPI_C3_RNFULLF_MARK(config->rxWatermark) |
                   SPI_C3_INTCLR(0U) | SPI_C3_FIFOMODE(1U);
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Set baud rate */
    SPI_MasterSetBaudRate(base, config->baudRate_Bps, srcClock_Hz);

    /* Enable SPI */
    if (config->enableMaster)
    {
        base->C1 |= SPI_C1_SPE_MASK;
    }
}

void SPI_SlaveGetDefaultConfig(spi_slave_config_t *config)
{
    config->enableSlave = true;
    config->polarity = kSPI_ClockPolarityActiveHigh;
    config->phase = kSPI_ClockPhaseFirstEdge;
    config->direction = kSPI_MsbFirst;
    config->enableStopInWaitMode = false;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    config->dataMode = kSPI_8BitMode;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    config->txWatermark = kSPI_TxFifoOneHalfEmpty;
    config->rxWatermark = kSPI_RxFifoOneHalfFull;
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
}

void SPI_SlaveInit(SPI_Type *base, const spi_slave_config_t *config)
{
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_spiClock[SPI_GetInstance(base)]);

    /* Disable SPI before configuration */
    base->C1 &= ~SPI_C1_SPE_MASK;

    /* Configure master and clock polarity and phase */
    base->C1 =
        SPI_C1_MSTR(0U) | SPI_C1_CPOL(config->polarity) | SPI_C1_CPHA(config->phase) | SPI_C1_LSBFE(config->direction);

/* Configure data mode if needed */
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    base->C2 = SPI_C2_SPIMODE(config->dataMode) | SPI_C2_SPISWAI(config->enableStopInWaitMode);
#else
    base->C2 = SPI_C2_SPISWAI(config->enableStopInWaitMode);
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

/* Set watermark */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0U)
    {
        base->C3 = SPI_C3_TNEAREF_MARK(config->txWatermark) | SPI_C3_RNFULLF_MARK(config->rxWatermark) |
                   SPI_C3_INTCLR(0U) | SPI_C3_FIFOMODE(1U);
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Enable SPI */
    if (config->enableSlave)
    {
        base->C1 |= SPI_C1_SPE_MASK;
    }
}

void SPI_Deinit(SPI_Type *base)
{
    /* Disable SPI module before shutting down */
    base->C1 &= ~SPI_C1_SPE_MASK;

    /* Gate the clock */
    CLOCK_DisableClock(s_spiClock[SPI_GetInstance(base)]);
}

uint32_t SPI_GetStatusFlags(SPI_Type *base)
{
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        return ((base->S) | (((uint32_t)base->CI) << 8U));
    }
    else
    {
        return (base->S);
    }
#else
    return (base->S);
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
}

void SPI_EnableInterrupts(SPI_Type *base, uint32_t mask)
{
    /* Rx full interrupt */
    if (mask & kSPI_RxFullAndModfInterruptEnable)
    {
        base->C1 |= SPI_C1_SPIE_MASK;
    }

    /* Tx empty interrupt */
    if (mask & kSPI_TxEmptyInterruptEnable)
    {
        base->C1 |= SPI_C1_SPTIE_MASK;
    }

    /* Data match interrupt */
    if (mask & kSPI_MatchInterruptEnable)
    {
        base->C2 |= SPI_C2_SPMIE_MASK;
    }

/* FIFO related interrupts */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        /* Rx FIFO near full interrupt */
        if (mask & kSPI_RxFifoNearFullInterruptEnable)
        {
            base->C3 |= SPI_C3_RNFULLIEN_MASK;
        }

        /* Tx FIFO near empty interrupt */
        if (mask & kSPI_TxFifoNearEmptyInterruptEnable)
        {
            base->C3 |= SPI_C3_TNEARIEN_MASK;
        }
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
}

void SPI_DisableInterrupts(SPI_Type *base, uint32_t mask)
{
    /* Rx full interrupt */
    if (mask & kSPI_RxFullAndModfInterruptEnable)
    {
        base->C1 &= (~SPI_C1_SPIE_MASK);
    }

    /* Tx empty interrupt */
    if (mask & kSPI_TxEmptyInterruptEnable)
    {
        base->C1 &= (~SPI_C1_SPTIE_MASK);
    }

    /* Data match interrupt */
    if (mask & kSPI_MatchInterruptEnable)
    {
        base->C2 &= (~SPI_C2_SPMIE_MASK);
    }

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        /* Rx FIFO near full interrupt */
        if (mask & kSPI_RxFifoNearFullInterruptEnable)
        {
            base->C3 &= ~SPI_C3_RNFULLIEN_MASK;
        }

        /* Tx FIFO near empty interrupt */
        if (mask & kSPI_TxFifoNearEmptyInterruptEnable)
        {
            base->C3 &= ~SPI_C3_TNEARIEN_MASK;
        }
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
}

void SPI_MasterSetBaudRate(SPI_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t prescaler;
    uint32_t bestPrescaler;
    uint32_t rateDivisor;
    uint32_t bestDivisor;
    uint32_t rateDivisorValue;
    uint32_t realBaudrate;
    uint32_t diff;
    uint32_t min_diff;
    uint32_t freq = baudRate_Bps;

    /* Find combination of prescaler and scaler resulting in baudrate closest to the requested value */
    min_diff = 0xFFFFFFFFU;

    /* Set the maximum divisor bit settings for each of the following divisors */
    bestPrescaler = 7U;
    bestDivisor = 8U;

    /* In all for loops, if min_diff = 0, the exit for loop*/
    for (prescaler = 0; (prescaler <= 7) && min_diff; prescaler++)
    {
        /* Initialize to div-by-2 */
        rateDivisorValue = 2U;

        for (rateDivisor = 0; (rateDivisor <= 8U) && min_diff; rateDivisor++)
        {
            /* Calculate actual baud rate, note need to add 1 to prescaler */
            realBaudrate = ((srcClock_Hz) / ((prescaler + 1) * rateDivisorValue));

            /* Calculate the baud rate difference based on the conditional statement ,that states that the
            calculated baud rate must not exceed the desired baud rate */
            if (freq >= realBaudrate)
            {
                diff = freq - realBaudrate;
                if (min_diff > diff)
                {
                    /* A better match found */
                    min_diff = diff;
                    bestPrescaler = prescaler;
                    bestDivisor = rateDivisor;
                }
            }

            /* Multiply by 2 for each iteration, possible divisor values: 2, 4, 8, 16, ... 512 */
            rateDivisorValue *= 2U;
        }
    }

    /* Write the best prescalar and baud rate scalar */
    base->BR = SPI_BR_SPR(bestDivisor) | SPI_BR_SPPR(bestPrescaler);
}

void SPI_WriteBlocking(SPI_Type *base, uint8_t *buffer, size_t size)
{
    uint32_t i = 0;

    while (i < size)
    {
        while ((base->S & SPI_S_SPTEF_MASK) == 0)
        {
        }

        /* Send data */
        SPI_WriteNonBlocking(base, buffer, size);

        /* Wait the data to be sent */
        while ((base->S & SPI_S_SPTEF_MASK) == 0)
        {
        }
        i++;
    }
}

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
void SPI_EnableFIFO(SPI_Type *base, bool enable)
{
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0U)
    {
        if (enable)
        {
            base->C3 |= SPI_C3_FIFOMODE_MASK;
        }
        else
        {
            base->C3 &= ~SPI_C3_FIFOMODE_MASK;
        }
    }
}
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

void SPI_WriteData(SPI_Type *base, uint16_t data)
{
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
    base->DL = data & 0xFFU;
    base->DH = (data >> 8U) & 0xFFU;
#else
    base->D = data & 0xFFU;
#endif
}

uint16_t SPI_ReadData(SPI_Type *base)
{
    uint16_t val = 0;
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
    val = base->DL;
    val |= (uint16_t)((uint16_t)(base->DH) << 8U);
#else
    val = base->D;
#endif
    return val;
}

status_t SPI_MasterTransferBlocking(SPI_Type *base, spi_transfer_t *xfer)
{
    assert(xfer);

    uint8_t bytesPerFrame = 1U;

    /* Check if the argument is legal */
    if ((xfer->txData == NULL) && (xfer->rxData == NULL))
    {
        return kStatus_InvalidArgument;
    }

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Check if 16 bits or 8 bits */
    bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#endif

    /* Disable SPI and then enable it, this is used to clear S register */
    base->C1 &= ~SPI_C1_SPE_MASK;
    base->C1 |= SPI_C1_SPE_MASK;

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO

    /* Disable FIFO, as the FIFO may cause data loss if the data size is not integer
       times of 2bytes. As SPI cannot set watermark to 0, only can set to 1/2 FIFO size or 3/4 FIFO
       size. */
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        base->C3 &= ~SPI_C3_FIFOMODE_MASK;
    }

#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Begin the polling transfer until all data sent */
    while (xfer->dataSize > 0)
    {
        /* Data send */
        while ((base->S & SPI_S_SPTEF_MASK) == 0U)
        {
        }
        SPI_WriteNonBlocking(base, xfer->txData, bytesPerFrame);
        if (xfer->txData)
        {
            xfer->txData += bytesPerFrame;
        }

        while ((base->S & SPI_S_SPRF_MASK) == 0U)
        {
        }
        SPI_ReadNonBlocking(base, xfer->rxData, bytesPerFrame);
        if (xfer->rxData)
        {
            xfer->rxData += bytesPerFrame;
        }

        /* Decrease the number */
        xfer->dataSize -= bytesPerFrame;
    }

    return kStatus_Success;
}

void SPI_MasterTransferCreateHandle(SPI_Type *base,
                                    spi_master_handle_t *handle,
                                    spi_master_callback_t callback,
                                    void *userData)
{
    assert(handle);

    uint8_t instance = SPI_GetInstance(base);

    /* Initialize the handle */
    s_spiHandle[instance] = handle;
    handle->callback = callback;
    handle->userData = userData;

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    uint8_t txSize = 0U;
    /* Get the number to be sent if there is FIFO */
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        txSize = (base->C3 & SPI_C3_TNEAREF_MARK_MASK) >> SPI_C3_TNEAREF_MARK_SHIFT;
        if (txSize == 0U)
        {
            handle->watermark = FSL_FEATURE_SPI_FIFO_SIZEn(base) * 3U / 4U;
        }
        else
        {
            handle->watermark = FSL_FEATURE_SPI_FIFO_SIZEn(base) / 2U;
        }
    }
    /* If no FIFO, just set the watermark to 1 */
    else
    {
        handle->watermark = 1U;
    }
#else
    handle->watermark = 1U;
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

/* Get the bytes per frame */
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
    handle->bytePerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#else
    handle->bytePerFrame = 1U;
#endif

    /* Enable SPI NVIC */
    EnableIRQ(s_spiIRQ[instance]);
}

status_t SPI_MasterTransferNonBlocking(SPI_Type *base, spi_master_handle_t *handle, spi_transfer_t *xfer)
{
    assert(handle && xfer);

    /* Check if SPI is busy */
    if (handle->state == kSPI_Busy)
    {
        return kStatus_SPI_Busy;
    }

    /* Check if the input arguments valid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    /* Set the handle information */
    handle->txData = xfer->txData;
    handle->rxData = xfer->rxData;
    handle->transferSize = xfer->dataSize;
    handle->txRemainingBytes = xfer->dataSize;
    handle->rxRemainingBytes = xfer->dataSize;

    /* Set the SPI state to busy */
    handle->state = kSPI_Busy;

    /* Disable SPI and then enable it, this is used to clear S register*/
    base->C1 &= ~SPI_C1_SPE_MASK;
    base->C1 |= SPI_C1_SPE_MASK;

/* Enable Interrupt, only enable Rx interrupt, use rx interrupt to driver SPI transfer */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (handle->watermark > 1U)
    {
        /* Enable Rx near full interrupt */
        SPI_EnableInterrupts(base, kSPI_RxFifoNearFullInterruptEnable);
    }
    else
    {
        SPI_EnableInterrupts(base, kSPI_RxFullAndModfInterruptEnable);
    }
#else
    SPI_EnableInterrupts(base, kSPI_RxFullAndModfInterruptEnable);
#endif

    /* First send a piece of data to Tx Data or FIFO to start a SPI transfer */
    SPI_SendTransaction(base, handle);

    return kStatus_Success;
}

status_t SPI_MasterTransferGetCount(SPI_Type *base, spi_master_handle_t *handle, size_t *count)
{
    assert(handle);

    status_t status = kStatus_Success;

    if (handle->state != kStatus_SPI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        /* Return remaing bytes in different cases */
        if (handle->rxData)
        {
            *count = handle->transferSize - handle->rxRemainingBytes;
        }
        else
        {
            *count = handle->transferSize - handle->txRemainingBytes;
        }
    }

    return status;
}

void SPI_MasterTransferAbort(SPI_Type *base, spi_master_handle_t *handle)
{
    assert(handle);

/* Stop interrupts */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (handle->watermark > 1U)
    {
        SPI_DisableInterrupts(base, kSPI_RxFifoNearFullInterruptEnable | kSPI_RxFullAndModfInterruptEnable);
    }
    else
    {
        SPI_DisableInterrupts(base, kSPI_RxFullAndModfInterruptEnable);
    }
#else
    SPI_DisableInterrupts(base, kSPI_RxFullAndModfInterruptEnable);
#endif

    /* Transfer finished, set the state to Done*/
    handle->state = kSPI_Idle;

    /* Clear the internal state */
    handle->rxRemainingBytes = 0;
    handle->txRemainingBytes = 0;
}

void SPI_MasterTransferHandleIRQ(SPI_Type *base, spi_master_handle_t *handle)
{
    assert(handle);

    /* If needs to receive data, do a receive */
    if (handle->rxRemainingBytes)
    {
        SPI_ReceiveTransaction(base, handle);
    }

    /* We always need to send a data to make the SPI run */
    if (handle->txRemainingBytes)
    {
        SPI_SendTransaction(base, handle);
    }

    /* All the transfer finished */
    if ((handle->txRemainingBytes == 0) && (handle->rxRemainingBytes == 0))
    {
        /* Complete the transfer */
        SPI_MasterTransferAbort(base, handle);

        if (handle->callback)
        {
            (handle->callback)(base, handle, kStatus_SPI_Idle, handle->userData);
        }
    }
}

static void SPI_CommonIRQHandler(SPI_Type *base, void *handle)
{
    if (base->C1 & SPI_C1_MSTR_MASK)
    {
        SPI_MasterTransferHandleIRQ(base, (spi_master_handle_t *)handle);
    }
    else
    {
        SPI_SlaveTransferHandleIRQ(base, (spi_slave_handle_t *)handle);
    }
}

#if defined(SPI0)
void SPI0_DriverIRQHandler(void)
{
    assert(s_spiHandle[0]);
    SPI_CommonIRQHandler(SPI0, s_spiHandle[0]);
}
#endif

#if defined(SPI1)
void SPI1_DriverIRQHandler(void)
{
    assert(s_spiHandle[1]);
    SPI_CommonIRQHandler(SPI1, s_spiHandle[1]);
}
#endif

#if defined(SPI2)
void SPI2_DriverIRQHandler(void)
{
    assert(s_spiHandle[2]);
    SPI_CommonIRQHandler(SPI0, s_spiHandle[2]);
}
#endif
