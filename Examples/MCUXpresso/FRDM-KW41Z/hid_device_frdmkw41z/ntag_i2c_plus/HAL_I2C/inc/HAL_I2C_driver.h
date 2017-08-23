/*
 * Copyright (c) 2016, NXP Semiconductor
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef _HAL_I2C_DRIVER_H_
#define _HAL_I2C_DRIVER_H_

/** @file HAL_I2C_driver.h
 * \brief Public interface to access the I2C hardware.
 *
 * This is a documentation of the API the other modules expect to see,
 * the actual implementation is platform dependent. Please also consult
 * the porting guide for further information regarding the functions in
 * this module.
 */

#include "global_types.h"
/***********************************************************************/
/* API DESCRIPTION                                                     */
/***********************************************************************/
#ifdef API_DESCRIPTION
/*
 * PLEASE MODIFY HAL_I2C_HANDLE_T, STATUS_T AND STATUS_OK TO SUIT YOUR NEED
 * IMPLEMENT HAL_I2C_InitDevice() / HAL_I2C_CloseDevice()
 *           HAL_I2C_RecvBytes() / HAL_I2C_SendBytes() AS SPECIFIED
 *
 * IF NECESSARY SPECIFY THE NUMBER OF BYTES NEEDED INTERNALLY BY
 * YOUR I2C IMPLEMENTATION IN THE HAL_I2C_XX_RESERVED_BYTES FIELDS
 * ALL BUFFERS WILL BE INCREASED BY THAT AMOUNT.
 *
 * e.g. HAL_I2C_TX_RESERVED_BYTES == 2, tx len = 5
 *      bytes[0-1] are reserved for i2c driver
 *      bytes[2-7] contain to be transmitted bytes
 */
#define HAL_I2C_HANDLE_T < e.g. void*>
#define HAL_I2C_INIT_PARAM_T < e.g. uint32_t bitrate >
#define HAL_I2C_INIT_DEFAULT < e.g. 400000 >
#define HAL_I2C_INVALID_HANDLE < e.g. NULL >
#define HAL_I2C_STATUS_T < e.g. bool >
#define HAL_I2C_OK < e.g. false>
#define HAL_I2C_RX_RESERVED_BYTES < e.g. 0 >
#define HAL_I2C_TX_RESERVED_BYTES < e.g. 1 >

/**
 * \brief initialize the I2C hardware and return a handle
 *
 *	This functions initializes the I2C hardware as specified by the
 *	HAL_I2C_INIT_PARAM_T parameter and returns a handle to be used
 *	for further operations.
 *
 * \param 	params 	structure holding all information necessary for
 * 					initializing the device
 *
 * \return 		 	HAL_I2C_INVALID_HANDLE on failure
 */
HAL_I2C_HANDLE_T HAL_I2C_InitDevice(HAL_I2C_INIT_PARAM_T params);

/**
 * \brief close handle and shutdown the I2C hardware
 *
 *	This functions puts the I2C hardware specified by handle into a
 *	save state and closes the handle
 *
 * \param 	handle 	handle to identify the i2c-bus instance
 *
 * \return 		 	HAL_I2C_INVALID_HANDLE on failure
 */
void HAL_I2C_CloseDevice(HAL_I2C_HANDLE_T handle);

/**
 * \brief receive len number of bytes on the specified I2C bus
 *
 *	This functions sends a start condition and then the i2c-address of the
 *	destination device. Afterwards it reads len number of bytes from the
 *	device followed by a stop condition.
 *
 *	| +START | +ADDR |-A| -D0 |+A| ... | -DN |+A| +STOP |
 *	+ send / - receive / A Ack-bit
 *
 * \param 	i2cbus 	handle to identify the i2c-bus instance
 * \param 	bytes  	array of bytes to be received.
 * \param   address 7-bit device address
 * \param 	len    	length of the bytes array
 *
 * \return 		 	HAL_I2C_OK on success
 */
HAL_I2C_STATUS_T HAL_I2C_RecvBytes(HAL_I2C_HANDLE_T i2cbus, uint8_t address, uint8_t *bytes, uint8_t len);

/**
 * \brief receive len number of bytes on the specified I2C bus
 *
 *	This functions sends a start condition followed by len number of bytes and
 *	a stop condition.
 *
 *	| +START | +ADDR |-A| +D0 |-A| ... | +DN |-A| +STOP |
 *	+ send / - receive / A Ack-bit
 *
 * \param 	i2cbus 	handle to identify the i2c-bus instance
 * \param 	bytes  	array of bytes to be send.
 * \param   address 7-bit device address
 * \param 	len    	length of the bytes array
 *
 * \return 			HAL_I2C_OK on success
 */
HAL_I2C_STATUS_T HAL_I2C_SendBytes(HAL_I2C_HANDLE_T i2cbus, uint8_t address, const uint8_t *bytes, uint8_t len);

#endif /* used for doxygen */

/***********************************************************************/
/* INTERFACING FOR FSL I2C DRIVERS - MACRO BASED EXAMPLE                      */
/***********************************************************************/

#ifdef I2C_FSL

#include "HAL_I2C_kinetis_fsl.h"

#define HAL_I2C_HANDLE_T I2C_Type *
#define HAL_I2C_INIT_PARAM_T uint32_t
#define HAL_I2C_INIT_DEFAULT 100000 /*278500 */
#define HAL_I2C_INVALID_HANDLE NULL
#define HAL_I2C_STATUS_T uint16_t
#define HAL_I2C_OK 0
#define HAL_I2C_InitDevice(bitrate, input_clock, instance) I2C_InitDevice(bitrate, input_clock, instance)
#define HAL_I2C_SendBytes(handle, address, bytes, len) TransmitPoll(handle, address, bytes, len)
#define HAL_I2C_RecvBytes(handle, address, bytes, len) ReceivePoll(handle, address, bytes, len)
#define HAL_I2C_CloseDevice(handle) /* not necessary */
#define HAL_I2C_RX_RESERVED_BYTES 0
#define HAL_I2C_TX_RESERVED_BYTES 0

#endif

/***********************************************************************/
/* INTERFACING FOR FRDM CMSIS DRIVERS - MACRO BASED EXAMPLE                      */
/***********************************************************************/

#ifdef I2C_CMSIS

#include "HAL_I2C_kinetis_cmsis.h"

#define HAL_I2C_HANDLE_T ARM_DRIVER_I2C *
#define HAL_I2C_INIT_PARAM_T uint32_t
#define HAL_I2C_INIT_DEFAULT 100000
#define HAL_I2C_INVALID_HANDLE NULL
#define HAL_I2C_STATUS_T uint16_t
#define HAL_I2C_OK 0
#define HAL_I2C_InitDevice(bitrate, input_clock, instance) CMSIS_I2C_InitDevice(instance)
#define HAL_I2C_SendBytes(handle, address, bytes, len) CMSIS_TransmitPoll(handle, address, bytes, len)
#define HAL_I2C_RecvBytes(handle, address, bytes, len) CMSIS_ReceivePoll(handle, address, bytes, len)
#define HAL_I2C_CloseDevice(handle) /* not necessary */
#define HAL_I2C_RX_RESERVED_BYTES 0
#define HAL_I2C_TX_RESERVED_BYTES 0

#endif

/***********************************************************************/
/* INTERFACING FOR LPC11U68 - MACRO BASED EXAMPLE                      */
/***********************************************************************/

#ifdef __LPC11U37H__

//#include "../../HAL_I2C/inc/HAL_I2C_lpc11u37h.h"

#define HAL_I2C_HANDLE_T void *
#define HAL_I2C_FAKE_HANDLE (void *)0xDEADBEEF
#define HAL_I2C_INIT_PARAM_T uint32_t
#define HAL_I2C_INIT_DEFAULT 100000 /*278500 */
#define HAL_I2C_INVALID_HANDLE NULL
#define HAL_I2C_STATUS_T uint16_t
#define HAL_I2C_OK 0
#define HAL_I2C_SendBytes(handle, address, bytes, len) \
    TransmitPoll((bytes[0] = (address << 1) | 0x00) ? bytes : bytes, len + 1)
#define HAL_I2C_RecvBytes(handle, address, bytes, len) \
    ReceivePoll((bytes[0] = (address << 1) | 0x01) ? bytes : bytes, len + 1)
#define HAL_I2C_InitDevice \
    HAL_I2C_FAKE_HANDLE;   \
    I2CMasterInit
#define HAL_I2C_CloseDevice(handle) /* not necessary */
#define HAL_I2C_RX_RESERVED_BYTES 1
#define HAL_I2C_TX_RESERVED_BYTES 1

#endif

#endif /* _HAL_I2C_DRIVER_H_ */
