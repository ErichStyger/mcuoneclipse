/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SHELL_H_
#define SHELL_H_

#include "McuShell.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Send a string to all supported I/Os
 * \param str String to send
 */
void SHELL_SendString(const unsigned char *str);

/*!
 * \brief Send a string to a given IO. It tries to accelerate it by sending a buffer instead char by char.
 * \param str String to be sent.
 * \param io I/O to be used.
 */
void SHELL_SendStringToIO(const unsigned char *str, McuShell_ConstStdIOType *io);

/*!
 * \brief Send a character to all supported I/Os
 * \param ch Character to send
 */
void SHELL_SendChar(unsigned char ch);

/*!
 * \brief Parses a command with a given standard I/O channel
 * \param command Command to be parsed
 * \param io I/O to be used. If NULL, the standard default I/O will be used
 * \param silent If parsing shall be silent or not
 * \return Error code, ERR_OK for no error
 */
uint8_t SHELL_ParseCommandIO(const unsigned char *command, McuShell_ConstStdIOType *io, bool silent);

/*!
 * \brief Send a string to the ESP shell get a response back
 * \param send Message to send
 * \param response Where to store the response
 * \param responseSize Size of the response buffer
 */
void SHELL_SendToESPAndGetResponse(const unsigned char *send, unsigned char *response, size_t responseSize);

/*!
 * \brief Send a string to the robot get a response back
 * \param send Message to send
 * \param response Where to store the response
 * \param responseSize Size of the response buffer
 */
void SHELL_SendToRobotAndGetResponse(const unsigned char *send, unsigned char *response, size_t responseSize);

/*!
 * \brief Module de-initialization
 */
void SHELL_Deinit(void);

/*!
 * \brief Module Initialization
 */
void SHELL_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SHELL_H_ */
