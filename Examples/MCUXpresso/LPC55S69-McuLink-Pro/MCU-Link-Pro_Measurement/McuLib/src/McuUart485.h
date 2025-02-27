/*
 * Copyright (c) 2020-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUUART485_H_
#define MCUUART485_H_

#include "McuUart485config.h"
#include "McuShell.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! buffers for the RS-485 shell parser */
extern uint8_t McuUart485_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

/*! The shell standard I/O handler to send/receive shell commands over the bus*/
extern McuShell_ConstStdIOType McuUart485_stdio;

/*!
 * \brief Sending a string to the bus
 * \param data string to be sent
 */
void McuUart485_SendString(unsigned char *data);

/*!
 * \brief Send a binary data block to the bus
 * \param data Data to be sent
 * \param dataSize Size of data in bytes
 */
void McuUart485_SendBlock(unsigned char *data, size_t dataSize);

/*!
 * \brief Clear the response queue.
 */
void McuUart485_ClearResponseQueue(void);

/*!
 * \brief Clear the Rx queue.
 */
void McuUart485_ClearRxQueue(void);

/*!
 * \brief Pull (dequeue) a character from the response queue
 * \return Error code, or ERR_OK
 */
uint8_t McuUart485_GetResponseQueueChar(void);

/*!
 * \brief Pull (dequeue) a character from the rx queue
 * \return Error code, or ERR_OK
 */
uint8_t McuUart485_GetRxQueueChar(void);

/*!
 * \brief Shell command line parser
 * \param cmd command to be parsed
 * \param handled if command was recognized
 * \param io I/O handler
 * \return Error code, or ERR_OK
 */
uint8_t McuUart485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*! \brief Module de-initialization */
void McuUart485_Deinit(void);

/*! \brief Module initialization */
void McuUart485_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUUART485_H_ */
