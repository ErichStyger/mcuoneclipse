/*!
 * \file      i2c-board.c
 *
 * \brief     Target board I2C driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \author    Diego Bienz
 */

#include "utilities.h"
#include "board-config.h"
#include "i2c-board.h"
#include "i2c.h"
#include "fsl_i2c.h"

typedef struct {
	I2cId_t id;
	I2C_Type *type;
	i2c_master_config_t config;
	uint32_t clockFrq;
	uint32_t baudrate;
	uint8_t i2cInternalAddrSize;
	i2c_master_transfer_t masterXfer;
} lpcI2cHandle_t;

/**
  * Local I2C Handles
  * DO NOT CHANGE => If you need to change I2C settings, change it in board-config.h
  */
#if(LPC_NUMBER_OF_I2C > 0)
static lpcI2cHandle_t i2cHandle0 = {
	.id = I2C_1,
	.type = LPC_I2C1_TYPE,
	.clockFrq = LPC_I2C1_CLK_FRQ,
	.baudrate = LPC_I2C1_BAUDRATE,
	.i2cInternalAddrSize = LPC_I2C1_SLAVE_ADDR_SIZE
};
#endif
#if(LPC_NUMBER_OF_I2C > 1)
static lpcI2cHandle_t i2cHandle1 = { 
	.id = I2C_2,
	.type = LPC_I2C2_TYPE,
	.clockFrq = LPC_I2C2_CLK_FRQ,
	.baudrate = LPC_I2C2_BAUDRATE,
	.i2cInternalAddrSize = LPC_I2C2_SLAVE_ADDR_SIZE
};
#endif

static void MapI2cIdToHandle(I2cId_t i2cId, lpcI2cHandle_t **handle);

/*!
 * CAUTION:
 * The pin configuration (muxing, clock, etc.) is made with the pin_mux.* of the board.
 * You can also use the pin configuration tool of NXP.
 * This init function doesn't care about the defined pins
 */
void I2cMcuInit(I2c_t *obj, I2cId_t i2cId, PinNames scl, PinNames sda) {
	lpcI2cHandle_t *handle;
	obj->I2cId = i2cId;
	MapI2cIdToHandle(i2cId, &handle);

    /*
     * config.debugEnable = false;
     * config.ignoreAck = false;
     * config.pinConfig = kI2C_2PinOpenDrain;
     * config.baudRate_Bps = 100000U;
     * config.busIdleTimeout_ns = 0;
     * config.pinLowTimeout_ns = 0;
     * config.sdaGlitchFilterWidth_ns = 0;
     * config.sclGlitchFilterWidth_ns = 0;
     */
	I2C_MasterGetDefaultConfig(&(handle->config));
	handle->config.baudRate_Bps = handle->baudrate;

	I2C_MasterInit(handle->type, &(handle->config), handle->clockFrq);

	memset(&(handle->masterXfer), 0, sizeof(handle->masterXfer));
}

void I2cMcuFormat(I2c_t *obj, I2cMode mode, I2cDutyCycle dutyCycle,
bool I2cAckEnable, I2cAckAddrMode AckAddrMode, uint32_t I2cFrequency) {
	/*!
	 * This function doesn't do anything!
	 * The pin configuration (muxing, clock, etc.) is made with the pin_mux.* of the board.
	 * You can also use the pin configuration tool of NXP.
	 * This function doesn't care about the defined pins
	 */
}

void I2cMcuDeInit(I2c_t *obj) {
	lpcI2cHandle_t *handle;
	MapI2cIdToHandle(obj->I2cId, &handle);

	I2C_MasterDeinit(handle->type);
}

void I2cSetAddrSize(I2c_t *obj, I2cAddrSize addrSize) {
	lpcI2cHandle_t *handle;
	MapI2cIdToHandle(obj->I2cId, &handle);

	handle->i2cInternalAddrSize = addrSize;
}

LmnStatus_t I2cMcuWriteBuffer( I2c_t *obj, uint8_t deviceAddr, uint8_t *buffer, uint16_t size ) {
//LmnStatus_t I2cMcuWriteBuffer(I2c_t *obj, uint8_t deviceAddr, uint16_t addr,	uint8_t *buffer, uint16_t size) {
  status_t status;
	lpcI2cHandle_t *handle;
	MapI2cIdToHandle(obj->I2cId, &handle);

	handle->masterXfer.slaveAddress = deviceAddr;
	handle->masterXfer.direction = kI2C_Write;
	handle->masterXfer.subaddress = 0;
	handle->masterXfer.subaddressSize = 0;
	handle->masterXfer.data = buffer;
	handle->masterXfer.dataSize = size;
	handle->masterXfer.flags = kI2C_TransferDefaultFlag;

	status = I2C_MasterTransferBlocking(handle->type, &(handle->masterXfer));
  if (status!=kStatus_Success) {
    return LMN_STATUS_ERROR;
  }
  return LMN_STATUS_OK;
}

LmnStatus_t I2cMcuReadBuffer(I2c_t *obj, uint8_t deviceAddr, uint8_t *buffer, uint16_t size) {
  status_t status;
	lpcI2cHandle_t *handle;
	MapI2cIdToHandle(obj->I2cId, &handle);

	handle->masterXfer.slaveAddress = deviceAddr;
	handle->masterXfer.direction = kI2C_Read;
	handle->masterXfer.subaddress = 0;
	handle->masterXfer.subaddressSize = 0;
	handle->masterXfer.data = buffer;
	handle->masterXfer.dataSize = size;
	handle->masterXfer.flags = kI2C_TransferDefaultFlag;

	status = I2C_MasterTransferBlocking(handle->type, &(handle->masterXfer));
	if (status!=kStatus_Success) {
	  return LMN_STATUS_ERROR;
	}
  return LMN_STATUS_OK;
}

LmnStatus_t I2cMcuWaitStandbyState(I2c_t *obj, uint8_t deviceAddr) {
	/* Function not implemented -> Always returns successfully */
	return LMN_STATUS_OK;
}

/*!
 * Since the LoRaMac-node stack's I2C enum (I2cId_t) goes from I2C_1 to I2C_2,
 * but the LPC offers several I2Cs on different pin settings,a short mapping is 
 * required. This method set the pointer "handle" to the corresponding handle 
 * of the given i2cId.
 */
static void MapI2cIdToHandle(I2cId_t i2cId, lpcI2cHandle_t **handle) {

#if(LPC_NUMBER_OF_I2C > 0)
	if(i2cHandle0.id == i2cId){
		*handle = &i2cHandle0;
		return;
	}
#endif
#if(LPC_NUMBER_OF_I2C > 1)
	if(i2cHandle1.id == i2cId){
		*handle = &i2cHandle1;
		return;
	}
#endif
	*handle = NULL;
}
