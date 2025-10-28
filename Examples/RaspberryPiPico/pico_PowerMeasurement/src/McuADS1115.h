/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __ADS1115_H__
#define __ADS1115_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "McuADS1115_config.h"

#if McuADS1115_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
  uint8_t McuADS1115_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif /* McuADS1115 */

/*!
 * \brief Module initialization, call it to initialize the driver
 */
void McuADS1115_Init(void);

/*!
 * \brief Module de-initialization, call it to de-initialize the driver
 */
void McuADS1115_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __ADS1115_H__ */