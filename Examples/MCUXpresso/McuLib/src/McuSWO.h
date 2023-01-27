/*
 * Copyright (c) 2021, Erich Styger
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
void McuSWO_ReadLine(unsigned char *buf, size_t bufSize);

/*! send a string through SWO ITM Port 0 (0x1) */
void McuSWO_SendStr(const unsigned char *str);

/*!
 * \brief Writing SWO output using printf style
 * \param fmt Format string
 */
unsigned McuSWO_printf(const char *fmt, ...);

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
