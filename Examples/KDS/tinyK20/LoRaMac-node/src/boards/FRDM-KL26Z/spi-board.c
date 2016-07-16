/**
 * \file spi-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board SPI driver implementation
 *
 */

#include "board.h"
#include "spi-board.h"
#include "fsl_spi_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

/*----------------------- Local Definitions ------------------------------*/
/*!
 * MCU SPI peripherals enumeration
 */
typedef enum {
    SPI_0 = (uint32_t) SPI0_BASE, SPI_1 = (uint32_t) SPI1_BASE,
} SPIName;

/*------------------------ Local Variables -------------------------------*/
// Table of SPI FIFO sizes per instance.
extern const uint32_t g_spiFifoSize[SPI_INSTANCE_COUNT];
//Table of base pointers for SPI instances.
extern SPI_Type * const g_spiBase[SPI_INSTANCE_COUNT];

void SpiInit(Spi_t *obj, PinNames mosi, PinNames miso, PinNames sclk, PinNames nss)
{
    /* Check if a proper channel was selected */
    if (g_spiBase[obj->instance] == NULL) return;

    obj->Spi = g_spiBase[obj->instance];

    GpioInit(&obj->Mosi, mosi, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Miso, miso, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Sclk, sclk, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    if (nss != NC) GpioInit(&obj->Nss, nss, PIN_ALTERNATE_FCT, PIN_PUSH_PULL, PIN_PULL_DOWN, 1);

    /* Enable clock for SPI.*/
    CLOCK_SYS_EnableSpiClock(obj->instance);

    // Initialize the SPI module registers to default value, which disables the module
    SPI_HAL_Init(obj->Spi);

    // Set the SPI pin mode to normal mode
    SPI_HAL_SetPinMode(obj->Spi, kSpiPinMode_Normal);

#if FSL_FEATURE_SPI_FIFO_SIZE
    if (g_spiFifoSize[obj->instance] != 0)
    {
        // If SPI module contains a FIFO, disable it and set watermarks to half full/empty
        SPI_HAL_SetFifoMode(obj->Spi, false, kSpiTxFifoOneHalfEmpty, kSpiRxFifoOneHalfFull);
    }
#endif

    if (!obj->isSlave) {
        // 8 bits, CPOL = 0, CPHA = 0, MASTER
        SpiFormat(obj, 8, 0, 0, 0);
    } else {
        // 8 bits, CPOL = 0, CPHA = 0, SLAVE
        SpiFormat(obj, 8, 0, 0, 1);
    }
    SpiFrequency(obj, 10000000);

    /* Enable Spi module */
    SPI_HAL_Enable(obj->Spi);
}

void SpiDeInit(Spi_t *obj)
{
    /* Disable Spi module */
    SPI_HAL_Disable(obj->Spi);

    /* Disable clock for SPI.*/
    CLOCK_SYS_DisableSpiClock(obj->instance);

    GpioInit(&obj->Mosi, obj->Mosi.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&obj->Miso, obj->Miso.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_PULL_DOWN, 0);
    GpioInit(&obj->Sclk, obj->Sclk.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&obj->Nss, obj->Nss.pin, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
}

void SpiFormat(Spi_t *obj, int8_t bits, int8_t cpol, int8_t cpha, int8_t slave)
{
    spi_clock_polarity_t clockPolarity;
    spi_clock_phase_t clockPhase;
    spi_data_bitcount_mode_t bitCount;

    /* Disable Spi module */
    SPI_HAL_Disable(obj->Spi);

    clockPolarity = ((cpol != 1) ? kSpiClockPolarity_ActiveHigh : kSpiClockPolarity_ActiveLow);
    clockPhase = ((cpha != 1) ? kSpiClockPhase_FirstEdge : kSpiClockPhase_SecondEdge);
    bitCount = ((bits != 8) ? kSpi16BitMode : kSpi8BitMode);

    if (obj->isSlave) {
        /* Set SPI to master mode */
        SPI_HAL_SetMasterSlave(obj->Spi, kSpiSlave);
    } else {
        /* Set SPI to master mode */
        SPI_HAL_SetMasterSlave(obj->Spi, kSpiMaster);
        // Set slave select to automatic output mode
        SPI_HAL_SetSlaveSelectOutputMode(obj->Spi, kSpiSlaveSelect_AutomaticOutput);
    }

    SPI_HAL_SetDataFormat(obj->Spi, clockPolarity, clockPhase, kSpiMsbFirst);
    SPI_HAL_Set8or16BitMode(obj->Spi, bitCount);

    /* Enable Spi module */
    SPI_HAL_Enable(obj->Spi);
}

void SpiFrequency(Spi_t *obj, uint32_t hz)
{
    uint32_t spiSourceClock;

    spiSourceClock = CLOCK_SYS_GetSpiFreq(obj->instance);

    /* Disable Spi module */
    SPI_HAL_Disable(obj->Spi);

    SPI_HAL_SetBaud(obj->Spi, hz, spiSourceClock);

    /* Enable Spi module */
    SPI_HAL_Enable(obj->Spi);
}

uint16_t SpiInOut(Spi_t *obj, uint16_t outData)
{
    uint16_t data;

    if ((obj == NULL) || (obj->Spi) == NULL) {
        while (1) {
        }
    }

    // Disable module to clear the shift register
    SPI_HAL_Disable(obj->Spi);
    SPI_HAL_Enable(obj->Spi);

    SPI_HAL_WriteDataBlocking(obj->Spi, kSpi8BitMode, 0, (uint8_t)(outData & 0xFF));

    // Wait for slave send data back
    while (SPI_HAL_IsReadBuffFullPending(obj->Spi) == 0) {
    }
    data = SPI_HAL_ReadDataLow(obj->Spi);

    return data;
}

