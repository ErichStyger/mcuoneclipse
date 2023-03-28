/*
 * Copyright (c) 2019-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RS485_H_
#define RS485_H_

#include <stdbool.h>
#include <stdint.h>
#include "McuShell.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! special pre-defined node addresses */
#define RS485_BROADCAST_ADDRESS (0x00)
  /*!< special broadcast address */
#define RS485_ILLEGAL_ADDRESS   (0xff)
  /*!< illegal/initialization value */

/*!
 * \brief Send a shell command to the RS-485 bus
 * \param dstAddr Destination node address
 * \param cmd The shell command string
 * \param timeoutMs timeout in milliseconds to wait for a response
 * \param nofRetry Number of retries
 * \param shellIO I/O handler of the calling shell, used for writing output of the command
 * \param rsIO I/O handler for the RS-485 bus, used to read incoming characters
 * \return Error code, or ERR_OK
 */
uint8_t RS485_SendCommand(uint8_t dstAddr, const unsigned char *cmd, int32_t timeoutMs, uint32_t nofRetry, McuShell_ConstStdIOType *shellIO, McuShell_ConstStdIOType *rsIO);

/*!
 * \brief Getter for RS-485 node address
 * \return address of node
 */
uint8_t RS485_GetAddress(void);

/*!
 * \brief Shell command line parser
 * \param cmd command to be parsed
 * \param handled if command was recognized
 * \param io I/O handler
 * \return Error code, or ERR_OK
 */
uint8_t RS485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*! \brief Module de-initialization */
void RS485_Deinit(void);

/*! \brief Module initialization */
void RS485_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* RS485_H_ */
