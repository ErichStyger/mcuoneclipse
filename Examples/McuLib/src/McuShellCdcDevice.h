/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef McuShellCdcDevice_H_
#define McuShellCdcDevice_H_

#include "McuShellCdcDeviceconfig.h"
#include "McuShell.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! Default McuShell buffer */
extern uint8_t McuShellCdcDevice_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

/*! Standard I/O for input/output */
extern McuShell_ConstStdIOType McuShellCdcDevice_stdio;

McuShell_ConstStdIOTypePtr McuShellCdcDevice_GetStdio(void);

void McuShellCdcDevice_Flush(void);
void McuShellCdcDevice_WriteAndFlush(const char *buf, size_t count);
void McuShellCdcDevice_WriteStr(const char *str);

void McuShellCdcDevice_WriteChar(char ch);
void McuShellCdcDevice_ReadChar(char *ch);
bool McuShellCdcDevice_IsDataPresent(void);
void McuShellCdcDevice_QueueChar(char ch);

/*!
 * \brief Return a received byte.
 * \return The byte, or EOF
 */
int McuShellCdcDevice_ReadByte(void);

bool McuShellCdcDevice_IsReady(void); /* device is ready to transfer */
bool McuShellCdcDevice_IsConnected(void); /* note: connection status might not be accurate */

/*!
 * \brief Set the callback for a character is received from the USB CDC channel.
 * \param buffer_rx_char_cb Callback to be used to store the character. Can be NULL.
 */
void McuShellCdcDevice_SetBufferRxCharCallback(void (*buffer_rx_char_cb)(char ch));

uint8_t McuShellCdcDevice_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Module de-initialization
 */
void McuShellCdcDevice_Deinit(void);

/*!
 * \brief Module initialization
 */
void McuShellCdcDevice_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* McuShellCdcDevice_H_ */