/**
 * \file spi-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board SPI driver implementation
 *
 */

#include "board.h"
#include "spi-board.h"
#include "fsl_clock_manager.h"
#include "fsl_dspi_master_driver.h"
#include "fsl_dspi_slave_driver.h"
#include "fsl_interrupt_manager.h"
#include <stdlib.h>

/*----------------------- Local Definitions ------------------------------*/
/*!
 * MCU SPI peripherals enumeration
 */
typedef enum {
    SPI_0 = (uint32_t) SPI0_BASE, SPI_1 = (uint32_t) SPI1_BASE,
} SPIName;

/*! Number of bytes to be transmitted per transaction */
#define TRANSFER_SIZE   2

void SpiInit(Spi_t *obj, PinNames mosi, PinNames miso, PinNames sclk, PinNames nss)
{
    /* Check if a proper channel was selected */
    if (g_dspiBase[obj->instance] == NULL) return;

    obj->Spi = g_dspiBase[obj->instance];

    GpioInit(&obj->Mosi, mosi, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Miso, miso, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Sclk, sclk, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    if (nss != NC) GpioInit(&obj->Nss, nss, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_UP, 1);

    if (!obj->isSlave) {
        // Enable DSPI clock.
        CLOCK_SYS_EnableSpiClock(obj->instance);
        // Initialize the DSPI module registers to default value, which disables the module
        DSPI_HAL_Init(obj->Spi);
        // Set to master mode.
        DSPI_HAL_SetMasterSlaveMode(obj->Spi, kDspiMaster);
        // Configure for continuous SCK operation
        DSPI_HAL_SetContinuousSckCmd(obj->Spi, false);
        // Configure for peripheral chip select polarity
        DSPI_HAL_SetPcsPolarityMode(obj->Spi, kDspiPcs0, kDspiPcs_ActiveLow);
        // Disable FIFO operation.
        DSPI_HAL_SetFifoCmd(obj->Spi, false, false);
        // Initialize the configurable delays: PCS-to-SCK, prescaler = 0, scaler = 1
        DSPI_HAL_SetDelay(obj->Spi, kDspiCtar0, 0, 1, kDspiPcsToSck);
        // DSPI system enable
        DSPI_HAL_Enable(obj->Spi);

        // 8 bits, CPOL = 0, CPHA = 0, MASTER
        SpiFormat(obj, 8, 0, 0, 0);
    } else {
        // 8 bits, CPOL = 0, CPHA = 0, SLAVE
        SpiFormat(obj, 8, 0, 0, 1);
    }
    SpiFrequency(obj, 10000000);
}

void SpiDeInit(Spi_t *obj)
{
    /* First stop transfers */
    DSPI_HAL_StopTransfer(obj->Spi);

    /* Restore the module to defaults then power it down. This also disables the DSPI module.*/
    DSPI_HAL_Init(obj->Spi);

    /* disable the interrupt*/
    INT_SYS_DisableIRQ (g_dspiIrqId[obj->instance]);

    /* Gate the clock for DSPI.*/
    CLOCK_SYS_DisableSpiClock(obj->instance);

    GpioInit(&obj->Mosi, obj->Mosi.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&obj->Miso, obj->Miso.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Sclk, obj->Sclk.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&obj->Nss, obj->Nss.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
}

void SpiFormat(Spi_t *obj, int8_t bits, int8_t cpol, int8_t cpha, int8_t slave)
{
    dspi_data_format_config_t dataConfig;

    dataConfig.clkPhase = ((cpha != 1) ? kDspiClockPhase_FirstEdge : kDspiClockPhase_SecondEdge);
    dataConfig.clkPolarity = (
            (cpol != 1) ? kDspiClockPolarity_ActiveHigh : kDspiClockPolarity_ActiveLow);
    dataConfig.direction = kDspiMsbFirst;
    dataConfig.bitsPerFrame = bits;

    if (obj->isSlave) {

    } else {
        DSPI_HAL_SetDataFormat(obj->Spi, kDspiCtar0, &dataConfig);
    }
}

void SpiFrequency(Spi_t *obj, uint32_t hz)
{
    uint32_t dspiSourceClock;
    uint32_t calculatedBaudRate;

    if (!(obj->isSlave)) {
        // Get DSPI source clock.
        dspiSourceClock = CLOCK_SYS_GetSpiFreq(obj->instance);
        calculatedBaudRate = DSPI_HAL_SetBaudRate(obj->Spi, kDspiCtar0, hz, dspiSourceClock);
        PRINTF("Transfer at baudrate %lu \r\n", calculatedBaudRate);
    }
}

uint16_t SpiInOut(Spi_t *obj, uint16_t outData)
{
    uint16_t data = 0x00;

    if ((obj == NULL) || (obj->Spi) == NULL) {
        while (1)
            ;
    }

    if (obj->isSlave) {

    } else {
        dspi_command_config_t
        commandConfig =
        {
            .isChipSelectContinuous = false,
            .whichCtar = kDspiCtar0,
            .whichPcs = kDspiPcs0,
            .clearTransferCount = true,
            .isEndOfQueue = false
        };
        if (outData != 0x00) {
            // Restart the transfer by stop then start again, this will clear out the shift register
            DSPI_HAL_StopTransfer(obj->Spi);
            // Flush the FIFOs
            DSPI_HAL_SetFlushFifoCmd(obj->Spi, true, true);
            // Clear status flags that may have been set from previous transfers.
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiTxComplete);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiEndOfQueue);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiTxFifoUnderflow);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiTxFifoFillRequest);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiRxFifoOverflow);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiRxFifoDrainRequest);
            // Clear the transfer count.
            DSPI_HAL_PresetTransferCount(obj->Spi, 0);
            // Start the transfer process in the hardware
            DSPI_HAL_StartTransfer(obj->Spi);
            // Send the data to slave.
            // Write data to PUSHR
            DSPI_HAL_WriteDataMastermode(obj->Spi, &commandConfig, outData);
        } else {
            // Restart the transfer by stop then start again, this will clear out the shift register
            DSPI_HAL_StopTransfer(obj->Spi);
            // Flush the FIFOs
            DSPI_HAL_SetFlushFifoCmd(obj->Spi, true, true);
            //Clear status flags that may have been set from previous transfers.
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiTxComplete);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiEndOfQueue);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiTxFifoUnderflow);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiTxFifoFillRequest);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiRxFifoOverflow);
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiRxFifoDrainRequest);
            // Clear the transfer count.
            DSPI_HAL_PresetTransferCount(obj->Spi, 0);
            // Start the transfer process in the hardware
            DSPI_HAL_StartTransfer(obj->Spi);
            // Write command to PUSHR.
            DSPI_HAL_WriteDataMastermode(obj->Spi, &commandConfig, 0);
            // Check RFDR flag
            while (DSPI_HAL_GetStatusFlag(obj->Spi, kDspiRxFifoDrainRequest) == false) {
            }
            // Read data from POPR
            data = DSPI_HAL_ReadData(obj->Spi);
            // Clear RFDR flag
            DSPI_HAL_ClearStatusFlag(obj->Spi, kDspiRxFifoDrainRequest);
        }
    }
    return data;
}

