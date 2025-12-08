/**
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * \brief Driver for the TI INA229 SPI current/voltage sensor.
 */

#ifndef McuINA229_H_
#define McuINA229_H_

#include "McuINA229config.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if McuINA229_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
  uint8_t McuINA229_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*! \brief Module de-initialization */
void McuINA229_Deinit(void);

/*! \brief Module initialization */
void McuINA229_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* McuINA229_H_ */