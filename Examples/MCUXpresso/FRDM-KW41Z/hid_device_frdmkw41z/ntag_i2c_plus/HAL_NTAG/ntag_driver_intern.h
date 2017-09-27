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
#ifndef _NTAG_DRIVER_INTERN_H_
#define _NTAG_DRIVER_INTERN_H_

/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include "HAL_I2C_driver.h"
#include "ntag_driver.h"
#ifdef HAVE_NTAG_INTERRUPT
#include "HAL_ISR_driver.h"
#endif
/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/
#define TX_START HAL_I2C_TX_RESERVED_BYTES
#define RX_START HAL_I2C_RX_RESERVED_BYTES
#define NTAG_ADDRESS_SIZE 1
/***********************************************************************/
/* TYPES                                                               */
/***********************************************************************/
struct NTAG_DEVICE
{
    NTAG_STATUS_T status;
    HAL_I2C_HANDLE_T i2cbus;
    uint8_t address;
#ifdef HAVE_NTAG_INTERRUPT
    ISR_SOURCE_T isr;
#endif
    uint8_t tx_buffer[TX_START + NTAG_I2C_BLOCK_SIZE + NTAG_ADDRESS_SIZE];
    uint8_t rx_buffer[RX_START + NTAG_I2C_BLOCK_SIZE];
};

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
extern struct NTAG_DEVICE ntag_device_list[];

/***********************************************************************/
/* GLOBAL FUNCTION PROTOTYPES                                          */
/***********************************************************************/
/**
 * \brief read the specified block from the selected NTAG device
 *
 *	This functions reads the specified 16-byte sized block from the selected
 *	NTAG device. Reading an invalid block will result in a failed read.
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	bytes	array of bytes to store read data
 * \param	block	block number to read
 * \param	len 	number of bytes to be read
 *
 * \return			TRUE on failure
 */
BOOL NTAG_ReadBlock(NTAG_HANDLE_T ntag, uint8_t block, uint8_t *bytes, uint8_t len);

/**
 * \brief write the specified block to the selected NTAG device
 *
 *	This functions writes the specified 16-byte sized block to selected NTAG device.
 *	Writing to an invalid block is undefined. Writing less than a full block will write
 *	0 to the rest of the block.
 *
 *	When directly using this function care has to be taken when writing the first byte
 *	of the first block( block = 0 ) because it will modify the I2C address of the device
 *	whereas on read the first byte will contain part of the serial number.
 *
 * \param	ntag	handle to identify the NTAG device instance
 * \param	bytes	array of bytes to be written
 * \param	block	block number to write
 * \param	len 	number of bytes to be written
 *
 * \return			TRUE on failure
 */
BOOL NTAG_WriteBlock(NTAG_HANDLE_T ntag, uint8_t block, const uint8_t *bytes, uint8_t len);

#endif /* _NTAG_DRIVER_INTERN_H_ */
