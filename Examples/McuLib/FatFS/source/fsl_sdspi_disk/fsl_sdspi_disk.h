/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SDSPI_DISK_H_
#define _FSL_SDSPI_DISK_H_

#include <stdint.h>
#include "ff.h"
#include "diskio.h"
#include "fsl_common.h"
#include "board.h"

/*!
 * @addtogroup SD Disk over SPI
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
/* DSPI clock source */
#if (BOARD_SDSPI_SPI_BASE == SPI0_BASE)
#define DSPI_MASTER_CLK_SRC (DSPI0_CLK_SRC)
#elif(BOARD_SDSPI_SPI_BASE == SPI1_BASE)
#define DSPI_MASTER_CLK_SRC (DSPI0_CLK_SRC)
#elif(BOARD_SDSPI_SPI_BASE == SPI2_BASE)
#define DSPI_MASTER_CLK_SRC (DSPI2_CLK_SRC)
#elif(BOARD_SDSPI_SPI_BASE == SPI3_BASE)
#define DSPI_MASTER_CLK_SRC (DSPI3_CLK_SRC)
#elif(BOARD_SDSPI_SPI_BASE == SPI4_BASE)
#define DSPI_MASTER_CLK_SRC (DSPI4_CLK_SRC)
#else
#error Should define the DSPI_MASTER_CLK_SRC!
#endif

/* Which PCS used to select the slave */
#if (BOARD_SDSPI_SPI_PCS_NUMBER == 0U)
#define DSPI_MASTER_PCS_CONFIG kDSPI_Pcs0
#define DSPI_MASTER_PCS_TRANSFER kDSPI_MasterPcs0
#elif(BOARD_SDSPI_SPI_PCS_NUMBER == 1U)
#define DSPI_MASTER_PCS_CONFIG kDSPI_Pcs1
#define DSPI_MASTER_PCS_TRANSFER kDSPI_MasterPcs1
#elif(BOARD_SDSPI_SPI_PCS_NUMBER == 2U)
#define DSPI_MASTER_PCS_CONFIG kDSPI_Pcs2
#define DSPI_MASTER_PCS_TRANSFER kDSPI_MasterPcs2
#elif(BOARD_SDSPI_SPI_PCS_NUMBER == 3U)
#define DSPI_MASTER_PCS_CONFIG kDSPI_Pcs3
#define DSPI_MASTER_PCS_TRANSFER kDSPI_MasterPcs3
#elif(BOARD_SDSPI_SPI_PCS_NUMBER == 4U)
#define DSPI_MASTER_PCS_CONFIG kDSPI_Pcs4
#define DSPI_MASTER_PCS_TRANSFER kDSPI_MasterPcs4
#elif(BOARD_SDSPI_SPI_PCS_NUMBER == 5U)
#define DSPI_MASTER_PCS_CONFIG kDSPI_Pcs5
#define DSPI_MASTER_PCS_TRANSFER kDSPI_MasterPcs5
#endif

#define DSPI_MASTER_CTAR (kDSPI_Ctar0) /* The CTAR to describe the transfer attribute */

#elif McuLib_CONFIG_CPU_VARIANT==McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16

#define SDSPI_SPI_MASTER          SPI8
#define SDSPI_SPI_MASTER_IRQ      FLEXCOMM8_IRQn
#define SDSPI_SPI_MASTER_CLK_SRC  kCLOCK_Flexcomm8
#define SDSPI_SPI_MASTER_CLK_FREQ CLOCK_GetFlexCommClkFreq(8U)
#define SDSPI_SPI_SSEL            1
#define SDSPI_SPI_SPOL            kSPI_SpolActiveAllLow
#else
  #error "unknown device"
#endif /* McuLib_CONFIG_CPU_VARIANT */

#define DSPI_BUS_BAUDRATE (500000U)    /* Transfer baudrate - 500k */

/*************************************************************************************************
 * API - SD disk interface
 ************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SD over SPI Disk Function
 * @{
 */

/*!
 * @brief Initializes SD disk over SPI.
 *
 * @param physicalDrive Physical drive number.
 * @retval STA_NOINIT Failed.
 * @retval RES_OK Success.
 */
DSTATUS sdspi_disk_initialize(uint8_t physicalDrive);

/*!
 * Gets SD over SPI disk status
 *
 * @param physicalDrive Physical drive number.
 * @retval STA_NOINIT Failed.
 * @retval RES_OK Success.
 */
DSTATUS sdspi_disk_status(uint8_t physicalDrive);

/*!
 * @brief Reads SD disk over SPI.
 *
 * @param physicalDrive Physical drive number.
 * @param buffer The data buffer pointer to store read content.
 * @param sector The start sector number to be read.
 * @param count The sector count to be read.
 * @retval RES_PARERR Failed.
 * @retval RES_OK Success.
 */
DRESULT sdspi_disk_read(uint8_t physicalDrive, uint8_t *buffer, uint32_t sector, uint8_t count);

/*!
 * @brief Writes to SD disk over SPI.
 *
 * @param physicalDrive Physical drive number.
 * @param buffer The data buffer pointer to store write content.
 * @param sector The start sector number to be written.
 * @param count The sector count to be written.
 * @retval RES_PARERR Failed.
 * @retval RES_OK Success.
 */
DRESULT sdspi_disk_write(uint8_t physicalDrive, const uint8_t *buffer, uint32_t sector, uint8_t count);

/*!
 * @brief SD over SPI disk IO operation.
 *
 * @param physicalDrive Physical drive number.
 * @param command The command to be set.
 * @param buffer The buffer to store command result.
 * @retval RES_PARERR Failed.
 * @retval RES_OK Success.
 */
DRESULT sdspi_disk_ioctl(uint8_t physicalDrive, uint8_t command, void *buffer);

/*************************************************************************************************
 * API - SPI interface
 ************************************************************************************************/
/*!
 * @brief Initializes the SPI.
 */
void spi_init(void);

/*!
 * @brief Sets the SPI bus frequency.
 *
 * @param frequency The frequency to set.
 * @retval kStatus_Success Success.
 * @retval kStatus_Fail Failed.
 */
status_t spi_set_frequency(uint32_t frequency);

/*!
 * @brief Transfers data over SPI bus in full-duplex way.
 *
 * @param in The buffer to save the data to be sent.
 * @param out The buffer to save the data to be read.
 * @param size The transfer data size.
 * @return The status of the function DSPI_MasterTransferPolling().
 */
status_t spi_exchange(uint8_t *in, uint8_t *out, uint32_t size);

/*!
 * @brief Initializes the timer to generator 1ms interrupt used to get current time in milliseconds.
 */
void timer_init(void);

/*!
 * @brief Gets current time in milliseconds.
 *
 * @return Current time in milliseconds.
 */
uint32_t timer_get_current_milliseconds(void);

/*!
 * @brief Initializes the host descriptor.
 */
void sdspi_host_init(void);

/* @} */
#if defined(__cplusplus)
}
#endif

#endif /* _FSL_SDSPI_DISK_H_ */
