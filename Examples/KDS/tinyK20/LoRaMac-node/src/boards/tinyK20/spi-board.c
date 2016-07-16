/**
 * \file spi-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board SPI driver implementation
 *
 */

#include "board.h"
#include "spi-board.h"
#include <stdlib.h>

#define LOG_LEVEL_TRACE
#include "debug.h"

/*----------------------- Local Definitions ------------------------------*/
/*!
 * MCU SPI peripherals enumeration
 */
typedef enum {
    SPI_0 = (uint32_t) SPI0_BASE_PTR
} SPIName;

void SpiInit(Spi_t *obj, PinNames mosi, PinNames miso, PinNames sclk, PinNames nss)
{
    /* Check if a proper channel was selected */
    if (obj == NULL) return;

    GpioInit(&obj->Mosi, mosi, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Miso, miso, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Sclk, sclk, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    if (nss != NC) GpioInit(&obj->Nss, nss, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 1);

    /* Choose SPI interface according to the given pins */
    obj->Spi = (SPI_TypeDef) SPI0_BASE_PTR;
    /* Enable clock gating */
    SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_SPI0_MASK;

    /*!
     * Initialize DSPI module
     */
    /* first, make sure the module is enabled to allow writes to certain registers*/
    obj->Spi->MCR &= ~SPI_MCR_MDIS_MASK;

    /* Halt all transfers*/
    obj->Spi->MCR |= SPI_MCR_HALT_MASK;

    /* set the registers to their default states */
    /* clear the status bits (write-1-to-clear) */
    obj->Spi->SR |= (SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK
            | SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK);

    obj->Spi->TCR = 0;
    obj->Spi->CTAR[0] = 0x78000000; /* CTAR0 */
    obj->Spi->CTAR[1] = 0x78000000; /* CTAR1 */
    obj->Spi->RSER = 0;

    /* Clear out PUSHR register. Since DSPI is halted, nothing should be transmitted. Be
     * sure the flush the FIFOs afterwards */
    obj->Spi->PUSHR &= ~(SPI_PUSHR_TXDATA_MASK);

    /* flush the fifos*/
    obj->Spi->MCR |= (SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK);

    /* Disable FIFO operation. */
    obj->Spi->MCR |= (SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK);

    if (!(obj->isSlave)) {
        // 8 bits, CPOL = 0, CPHA = 0, MASTER
        SpiFormat(obj, 8, 0, 0, 0);
    } else {
        // 8 bits, CPOL = 0, CPHA = 0, SLAVE
        SpiFormat(obj, 8, 0, 0, 1);
    }
    SpiFrequency(obj, 10000000);

    /* Enable DSPI module */
    obj->Spi->MCR &= ~(SPI_MCR_MDIS_MASK);
}

void SpiDeInit(Spi_t *obj)
{
    GpioInit(&obj->Mosi, obj->Mosi.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&obj->Miso, obj->Miso.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Sclk, obj->Sclk.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&obj->Nss, obj->Nss.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
}

void SpiFormat(Spi_t *obj, int8_t bits, int8_t cpol, int8_t cpha, int8_t slave)
{
    /* Configure for continuous SCK operation */
    obj->Spi->MCR &= ~(SPI_MCR_CONT_SCKE_MASK);
    /* Configure for peripheral chip select polarity */
    obj->Spi->MCR = (((obj->Spi->MCR) & ~(SPI_MCR_PCSIS_MASK)) | SPI_MCR_PCSIS(1));

    if (slave == 0) {
        /* Set to master mode */
        obj->Spi->MCR |= SPI_MCR_MSTR_MASK;
        /* Initialize the configurable delays: PCS-to-SCK, prescaler = 0, scaler = 1 */
        obj->Spi->CTAR[0] = (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_PCSSCK_MASK)) | SPI_CTAR_PCSSCK(0));
        obj->Spi->CTAR[0] = (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_CSSCK_MASK)) | SPI_CTAR_CSSCK(1));
        /* Set frame size */
        obj->Spi->CTAR[0] =
                (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_FMSZ_MASK)) | SPI_CTAR_FMSZ(bits - 1));
        /* Set clock polarity */
        obj->Spi->CTAR[0] = (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_CPOL_MASK))
                | (((uint32_t)(((uint32_t)(cpol)) << SPI_CTAR_CPOL_SHIFT)) & SPI_CTAR_CPOL_MASK));
        /* Set clock phase */
        obj->Spi->CTAR[0] = (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_CPHA_MASK))
                | (((uint32_t)(((uint32_t)(cpha)) << SPI_CTAR_CPHA_SHIFT)) & SPI_CTAR_CPHA_MASK));
        /* Set MSB first */
        obj->Spi->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
    } else {
        /* Set to slave mode */
        obj->Spi->MCR &= ~(SPI_MCR_MSTR_MASK);
        /* Set frame size */
        obj->Spi->CTAR_SLAVE[0] = (((obj->Spi->CTAR_SLAVE[0]) & ~(SPI_CTAR_SLAVE_FMSZ_MASK))
                | SPI_CTAR_SLAVE_FMSZ(bits - 1));
        /* Set clock polarity */
        obj->Spi->CTAR_SLAVE[0] = (((obj->Spi->CTAR_SLAVE[0]) & ~(SPI_CTAR_SLAVE_CPOL_MASK))
                | (((uint32_t)(((uint32_t)(cpol)) << SPI_CTAR_SLAVE_CPOL_SHIFT))
                        & SPI_CTAR_SLAVE_CPOL_MASK));
        /* Set clock phase */
        obj->Spi->CTAR_SLAVE[0] = (((obj->Spi->CTAR_SLAVE[0]) & ~(SPI_CTAR_SLAVE_CPHA_MASK))
                | (((uint32_t)(((uint32_t)(cpha)) << SPI_CTAR_SLAVE_CPHA_SHIFT))
                        & SPI_CTAR_SLAVE_CPHA_MASK));
    }
}

void SpiFrequency(Spi_t *obj, uint32_t hz)
{
    /* for master mode configuration, if slave mode detected, return 0*/
    if ((obj->Spi->MCR & SPI_MCR_MSTR_MASK) == 0) {
        return;
    }

    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t dbr, bestDbr;
    uint32_t realBaudrate, bestBaudrate;
    uint32_t diff, min_diff;
    uint32_t baudrate = hz;

    /* find combination of prescaler and scaler resulting in baudrate closest to the
     * requested value
     */
    min_diff = 0xFFFFFFFFU;
    bestPrescaler = 0;
    bestScaler = 0;
    bestDbr = 1;
    bestBaudrate = 0; /* required to avoid compilation warning */

    /* In all for loops, if min_diff = 0, the exit for loop*/
    for (prescaler = 0; (prescaler < 4) && min_diff; prescaler++) {
        for (scaler = 0; (scaler < 16) && min_diff; scaler++) {
            for (dbr = 1; (dbr < 3) && min_diff; dbr++) {
                realBaudrate = ((CPU_BUS_CLK_HZ * dbr)
                        / (s_baudratePrescaler[prescaler] * (s_baudrateScaler[scaler])));

                /* calculate the baud rate difference based on the conditional statement
                 * that states that the calculated baud rate must not exceed the desired baud rate */
                if (baudrate >= realBaudrate) {
                    diff = baudrate - realBaudrate;
                    if (min_diff > diff) {
                        /* a better match found */
                        min_diff = diff;
                        bestPrescaler = prescaler;
                        bestScaler = scaler;
                        bestBaudrate = realBaudrate;
                        bestDbr = dbr;
                    }
                }
            }
        }
    }

    LOG_TRACE("Transfer at baudrate %lu \r\n", bestBaudrate);

    /* write the best dbr, prescalar, and baud rate scalar to the CTAR */
    obj->Spi->CTAR[0] = (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_DBR_MASK))
            | (((uint32_t)(((uint32_t)(bestDbr - 1)) << SPI_CTAR_DBR_SHIFT)) & SPI_CTAR_DBR_MASK));
    obj->Spi->CTAR[0] =
            (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_PBR_MASK)) | SPI_CTAR_PBR(bestPrescaler));
    obj->Spi->CTAR[0] = (((obj->Spi->CTAR[0]) & ~(SPI_CTAR_BR_MASK)) | SPI_CTAR_BR(bestScaler));
}

uint16_t SpiInOut(Spi_t *obj, uint16_t outData)
{
    uint32_t cmd = 0x00;
    uint16_t data = 0x00;

    if ((obj == NULL) || (obj->Spi) == NULL) {
        LOG_ERROR("Spi object has not been initialized.");
        while (1)
            ;
    }

    /*!
     * Prepare DSPI command to attach to data
     *
     * isChipSelectContinuous = false,
     * whichCtar = Ctar0,
     * whichPcs = Pcs0,
     * clearTransferCount = true,
     * isEndOfQueue = false
     */
    cmd = ((uint32_t)(0) << SPI_PUSHR_CONT_SHIFT) | ((uint32_t)(0) << SPI_PUSHR_CTAS_SHIFT)
            | (SPI_PUSHR_PCS(1)) | ((uint32_t)(0) << SPI_PUSHR_EOQ_SHIFT)
            | ((uint32_t)(1) << SPI_PUSHR_CTCNT_SHIFT);

    /* Restart the transfer by stop then start again, this will clear out the shift register */
    obj->Spi->MCR |= SPI_MCR_HALT_MASK;
    /* flush the fifos*/
    obj->Spi->MCR |= (SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK);
    /* Clear status flags that may have been set from previous transfers */
    obj->Spi->SR |= (SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK
            | SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK);
    /* Clear the transfer count */
    obj->Spi->TCR = 0u;
    /* Start the transfer process in the hardware */
    obj->Spi->MCR &= ~(SPI_MCR_HALT_MASK);

    if (!(obj->isSlave)) {
        if (outData != 0x00) {
            /*! Write data to PUSHR */
            cmd |= ((uint32_t)(outData & SPI_PUSHR_TXDATA_MASK));
            obj->Spi->PUSHR = cmd;
        } else {
            /*! Read data */
            /* Write command to PUSHR */
            obj->Spi->PUSHR = cmd;
            /* Check RFDR flag */
            while ((((obj->Spi->SR) & SPI_SR_RFDF_MASK) >> SPI_SR_RFDF_SHIFT) == false) {
            }
            /* Read data from POPR */
            data = (uint16_t)(obj->Spi->POPR & 0xFFFF);
            /* Clear RFDR flag */
            obj->Spi->SR |= SPI_SR_RFDF_MASK;
        }
    } else {
        LOG_ERROR("Slave transfer has not yet been implemented.");
    }

    return data;
}

