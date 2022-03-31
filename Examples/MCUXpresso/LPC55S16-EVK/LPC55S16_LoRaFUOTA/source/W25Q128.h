/*
 * W25Q128.h
 *
 *  Created on: 05.01.2019
 *      Author: Erich Styger
 */

#ifndef SOURCES_W25Q128_H_
#define SOURCES_W25Q128_H_

#include <stdint.h>
#include <stddef.h>
#include "McuShell.h"
#include "spi.h"
#include "spi-board.h"
#include "fsl_spi.h"
#include "fsl_spi_dma.h"
#include "fsl_dma.h"
#include "platform.h"


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


uint8_t W25_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

#define W25_SERIAL_BUF_SIZE  (8)
uint8_t W25_ReadSerialNumber(uint8_t *buf, size_t bufSize);

#define W25_ID_BUF_SIZE  (3)
uint8_t W25_ReadID(uint8_t *buf, size_t bufSize);

uint8_t W25_ReadStatus1(uint8_t *status);

bool W25_isBusy(void);

void W25_WaitIfBusy(void);

uint8_t W25_Read(uint32_t address, uint8_t *buf, size_t bufSize);

uint8_t W25_EraseAll(void);

uint8_t W25_EraseSector4K(uint32_t address);

uint8_t W25_EraseBlock32K(uint32_t address);

uint8_t W25_EraseBlock64K(uint32_t address);

/*!
 * Program a page with data
 * \param address, should be aligned on page (256 bytes) if programming 256 bytes
 * \param data pointer to data
 * \param dataSize size of data in bytes, max 256
 * \return error code, ERR_OK for no error
 */
uint8_t W25_ProgramPage(uint32_t address, const uint8_t *data, size_t dataSize);

uint8_t W25_GetCapacity(const uint8_t *id, uint32_t *capacity);

uint8_t W25_Init(void);

uint16_t W25_SpiInOut( Spi_t *obj, uint16_t outData );

#endif /* SOURCES_W25Q128_H_ */
