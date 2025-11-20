/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * 2-Channel I2C DAC module with a voltage of 0-10V
 */

#ifndef __GP8403_H__
#define __GP8403_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "McuGP8403_config.h"

#if McuGP8403_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
  uint8_t McuGP8403_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif /* McuGP8403 */

/*!
 * \brief Module initialization, call it to initialize the driver
 */
void McuGP8403_Init(void);

/*!
 * \brief Module de-initialization, call it to de-initialize the driver
 */
void McuGP8403_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __GP8403_H__ */