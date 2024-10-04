/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _USB_HOST_H_
#define _USB_HOST_H_

#include <stdbool.h>
#include <stdint.h>
#include "McuShell.h"

/*!
* \brief Command line handler
* \param cmd String to command to be parsed
* \param handled Returns if command has been handled
* \param io I/O channel
* \return Error code, ERR_OK if everything is ok
*/
uint8_t UsbHost_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io);

void UsbHost_PowerEnable(bool enable);

void UsbHost_Init(void);

#endif /* _USB_HOST_H_ */