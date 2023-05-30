/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SWO_H_
#define SWO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuSWOconfig.h"
#include "McuShell.h"

extern uint8_t McuSWO_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

extern McuShell_ConstStdIOType McuSWO_stdio; /* default standard I/O */

/*!
 * \brief Return the SWO stdio handle
 * \return Standard I/O handle
 */
McuShell_ConstStdIOTypePtr McuSWO_GetStdio(void);

/*!
 * \brief Sending a character to the SWO/ITM console
 * \param ch Character to send
 */
void McuSWO_StdIOSendChar(uint8_t ch);

/*!
 * \brief Reads a character from the standard input
 * \param ch Pointer where to store the character, stores '\0' if no character was received
 */
void McuSWO_StdIOReadChar(uint8_t *ch);

/*!
 * \brief Checks if there is input from SWO/ITM console
 * \return true if there is input, false otherwise
 */
bool McuSWO_StdIOKeyPressed(void);

/*!
 * \brief Parser for the SWO module shell commands
 * \param cmd Pointer to the command string
 * \param handled Set to true if command is known
 * \param io Standard I/O channel to be used
 * \return ERR_OK if everything is fine, error code otherwise.
 */
uint8_t McuSWO_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io);

/*!
 * \brief Reads a line from the SWO ITM channel, including the newline.
 * Note that this function blocks until a '\n' is encountered.
 * \param buf Buffer where to store the data
 * \param bufSize Size of the buffer in bytes
 */
void McuSWO_ReadLineBlocking(unsigned char *buf, size_t bufSize);

/*!
 * \brief Non-blocking version of reading a line. It appends characters to a buffer.
 * \param buf Pointer to where to store the characters. Note that the buffer has to be initialized with a '\0' by the caller.
 * \param bufSize Size of buffer in bytes
 * \return ERR_OK if '\n' has added, ERR_BUSY otherwise.
 */
uint8_t McuSWO_ReadAppendLine(unsigned char *buf, size_t bufSize);

/*!
 * \brief Send a string through SWO ITM Port 0 (0x1)
 * \param str String to send
 */
void McuSWO_SendStr(const unsigned char *str);

/*!
 * \brief Writing SWO output using printf style
 * \param fmt Format string
 */
unsigned McuSWO_printf(const char *fmt, ...);

/*!
 * \brief Test routine for various stdio redirection.
 */
void McuSWO_TestStdio(void);

/*! The TraceClock is used to configure the SWO speed. Use this method if the clock has been changed */
void McuSWO_ChangeTraceClock(uint32_t traceClock);

/*! used to change speed to the desired value */
void McuSWO_ChangeSpeed(uint32_t baud);

/*! called to initialize the module. */
void McuSWO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* SWO_H_ */
