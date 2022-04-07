/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef MCUW28Q128CONFIG_H_
#define MCUW28Q128CONFIG_H_


#include "fsl_dspi.h"

//#define W25Q_NSS_GPIO       GPIO
//#define W25Q_NSS_PORT       0
//#define W25Q_NSS_PIN        4

/*******************************************************************************
 * Definitions of SPI Interface to W25Q
 ******************************************************************************/
#define W25Q_SPI_MASTER            SPI3
#define W25Q_SPI_MASTER_IRQ        FLEXCOMM3_IRQn
#define W25Q_SPI_MASTER_CLK_SRC    kCLOCK_Flexcomm3
#define W25Q_SPI_MASTER_CLK_FREQ   CLOCK_GetFlexCommClkFreq(3U)
#define W25Q_SPI_SSEL              0
#define W25Q_DMA                   DMA0
#define W25Q_SPI_MASTER_RX_CHANNEL 8
#define W25Q_SPI_MASTER_TX_CHANNEL 9
#define W25Q_MASTER_SPI_SPOL       kSPI_SpolActiveAllLow


#endif /* MCUW28Q128CONFIG_H_ */
