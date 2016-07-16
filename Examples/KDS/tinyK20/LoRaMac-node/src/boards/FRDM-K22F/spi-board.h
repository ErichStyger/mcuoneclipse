/**
 * \file spi-board.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 15.09.2015
 * \brief Target board SPI driver implementation
 *
 */

#ifndef __SPI_MCU_H__
#define __SPI_MCU_H__

#include "fsl_dspi_master_driver.h"
#include "fsl_dspi_slave_driver.h"

/*!
 * LoRaMac SPI typedef
 */
typedef SPI_Type SPI_TypeDef;

/*!
 * SPI driver structure definition
 */
struct Spi_s {
    uint32_t instance;
    SPI_TypeDef *Spi;
    bool isSlave;
    Gpio_t Mosi;
    Gpio_t Miso;
    Gpio_t Sclk;
    Gpio_t Nss;
};

#endif  // __SPI_MCU_H__
