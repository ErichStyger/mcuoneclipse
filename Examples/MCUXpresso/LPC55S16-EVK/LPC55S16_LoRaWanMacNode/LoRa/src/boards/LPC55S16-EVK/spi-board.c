/*!
 * \file      spi-board.c
 *
 * \brief     Target board SPI driver implementation
 * 
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "board.h"
#include "board-config.h"
#include "spi-board.h"
#include "fsl_spi.h"
#include "utilities.h"

/* Having a TRANSFER_SIZE of one byte is on purpose, since the communication of multiple
 * bytes is handled in the upper layer */
#define TRANSFER_SIZE 							1

typedef struct {
	SpiId_t id;
	SPI_Type *type;
	uint32_t srcClk;
	spi_master_config_t masterConfig;
	spi_transfer_t xfr;
	uint8_t masterRxData[TRANSFER_SIZE];
	uint8_t masterTxData[TRANSFER_SIZE];
} lpcSpiHandle_t;

/**
  * Local SPI Handles
  * DO NOT CHANGE => If you need to change SPI settings, change it in board-config.h
  */
#if(LPC_NUMBER_OF_SPI > 0)
static lpcSpiHandle_t spiHandle0 = {
	.id = SPI_1,
	.type = LPC_SPI1_TYPE,
};
#endif
#if(LPC_NUMBER_OF_SPI > 1)
static lpcSpiHandle_t spiHandle1 = {
	.id = SPI_2,
	.type = LPC_SPI2_TYPE,
};
#endif

static void MapSpiIdToHandle(SpiId_t spiId, lpcSpiHandle_t **handle);

/**
  * CAUTION:
  * The pin configuration (muxing, clock, etc.) is made with the pin_mux.* of the board.
  * You can also use the pin configuration tool of NXP.
  * This init function doesn't care about the handovered pins
  */
void SpiInit(Spi_t *obj, SpiId_t spiId, PinNames mosi, PinNames miso,
	PinNames sclk, PinNames nss) {

	lpcSpiHandle_t *handle;
	MapSpiIdToHandle(spiId, &handle);

#if(LPC_NUMBER_OF_SPI > 0)
	if(handle == &spiHandle0){
		handle->srcClk = LPC_SPI1_CLK_FRQ;
		SPI_MasterGetDefaultConfig(&(handle->masterConfig));
		handle->masterConfig.polarity = LPC_SPI1_CONFIG_POLARITY;
		handle->masterConfig.phase = LPC_SPI1_CONFIG_PHASE;
		handle->masterConfig.direction = LPC_SPI1_CONFIG_DIRECTION;
		handle->masterConfig.baudRate_Bps = LPC_SPI1_CONFIG_BAUDRATE;
		handle->masterConfig.dataWidth = LPC_SPI1_CONFIG_DATAWIDTH;
		handle->masterConfig.sselNum = LPC_SPI1_CONFIG_SS;
		handle->masterConfig.sselPol = LPC_SPI1_CONFIG_SPOL;
	}
#endif
#if(LPC_NUMBER_OF_SPI > 1)
	if(handle == &spiHandle1){
		handle->srcClk = LPC_SPI2_CLK_FRQ;
		SPI_MasterGetDefaultConfig(&(handle->masterConfig));
		handle->masterConfig.polarity = LPC_SPI2_CONFIG_POLARITY;
		handle->masterConfig.phase = LPC_SPI2_CONFIG_PHASE;
		handle->masterConfig.direction = LPC_SPI2_CONFIG_DIRECTION;
		handle->masterConfig.baudRate_Bps = LPC_SPI2_CONFIG_BAUDRATE;
		handle->masterConfig.dataWidth = LPC_SPI2_CONFIG_DATAWIDTH;
		handle->masterConfig.sselNum = LPC_SPI2_CONFIG_SS;
		handle->masterConfig.sselPol = LPC_SPI2_CONFIG_SPOL;
	}
#endif

	SPI_MasterInit(handle->type, &(handle->masterConfig), handle->srcClk);
}

void SpiDeInit(Spi_t *obj) {
	lpcSpiHandle_t *handle;
	MapSpiIdToHandle(obj->SpiId, &handle);
	SPI_Deinit(handle->type);
}

uint16_t SpiInOut(Spi_t *obj, uint16_t outData) {

	lpcSpiHandle_t *handle;
	MapSpiIdToHandle(obj->SpiId, &handle);

	handle->masterRxData[0] = 0x00;
	handle->masterTxData[0] = (uint8_t) (outData);

	CRITICAL_SECTION_BEGIN();

	/* Start master transfer, send data to slave */
	handle->xfr.txData = handle->masterTxData;
	handle->xfr.rxData = handle->masterRxData;
	handle->xfr.dataSize = TRANSFER_SIZE;
	handle->xfr.configFlags = kSPI_FrameAssert;
	if (kStatus_Success != SPI_MasterTransferBlocking(handle->type, &(handle->xfr))) {
		CRITICAL_SECTION_END();
		/* Error occured */
	}

	CRITICAL_SECTION_END();
	return handle->masterRxData[0];
}

/**
  * Since the LoRaMac-node stack's SPI enum (SpiId_t) goes from SPI_1 to SPI_2,
  * but the LPC series offers several SPIs on different pin settings, a short mapping
  * is required. This method sets the pointer "handle" to the corresponding handle of the given
  * spiId defined above.
  */
static void MapSpiIdToHandle(SpiId_t spiId, lpcSpiHandle_t **handle) {

#if(LPC_NUMBER_OF_SPI > 0)
	if(spiHandle0.id == spiId){
		*handle = &spiHandle0;
	}
#endif
#if(LPC_NUMBER_OF_SPI > 1)
	if(spiHandle1.id == spiId){
		*handle = &spiHandle1;
	}
#endif
}
