/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSEMIHOST_H_
#define MCUSEMIHOST_H_

#include "McuSemihost_config.h"

#include <stdbool.h>
#include <stdint.h>
#include "McuShell.h"

extern uint8_t McuSWO_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

extern McuShell_ConstStdIOType McuSWO_stdio; /* default standard I/O */

/*!
 * \brief Return the SWO stdio handle
 * \return Standard I/O handle
 */
McuShell_ConstStdIOTypePtr McuSemiHost_GetStdio(void);

/*!
 * \brief Sending a character to the SWO/ITM console
 * \param ch Character to send
 */
void McuSemiHost_StdIOSendChar(uint8_t ch);

/*!
 * \brief Reads a character from the standard input
 * \param ch Pointer where to store the character, stores '\0' if no character was received
 */
void McuSemiHost_StdIOReadChar(uint8_t *ch);

/*!
 * \brief Checks if there is input from SWO/ITM console
 * \return true if there is input, false otherwise
 */
bool McuSemiHost_StdIOKeyPressed(void);

/*!
 * \brief Testing the semihost functionality and API
 */
void McuSemiHost_Test(void);

/*!
 * \brief Module de-initialization
 */
void McuSemiHost_Deinit(void);

/*!
 * \brief Module initialization
 */
void McuSemiHost_Init(void);

#endif /* MCUSEMIHOST_H_ */
