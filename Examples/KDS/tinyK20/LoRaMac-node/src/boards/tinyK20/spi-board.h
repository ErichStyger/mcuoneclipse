/**
 * \file spi-board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board SPI driver implementation
 *
 */

#ifndef __SPI_MCU_H__
#define __SPI_MCU_H__

/* Defines constant value arrays for the baud rate pre-scalar and scalar divider values.*/
static const uint32_t s_baudratePrescaler[] = { 2, 3, 5, 7 };
static const uint32_t s_baudrateScaler[] = { 2, 4, 6, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
        4096, 8192, 16384, 32768 };

/*!
 * LoRaMac SPI typedef
 */
typedef SPI_MemMapPtr SPI_TypeDef;

/*!
 * SPI driver structure definition
 */
struct Spi_s {
    SPI_TypeDef Spi;
    bool isSlave;
    Gpio_t Mosi;
    Gpio_t Miso;
    Gpio_t Sclk;
    Gpio_t Nss;
};

#endif  // __SPI_MCU_H__
