/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef UDP_SERVER_SHELL_H_
#define UDP_SERVER_SHELL_H_

#include "platform.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"

  /*!
   * \brief Command line and shell handler
   * \param cmd The command to be parsed
   * \param handled If command has been recognized and handled
   * \param io I/O handler to be used
   * \return error code, otherwise ERR_OK
   */
  uint8_t UdpServer_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif /* PL_CONFIG_USE_SHELL */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* UDP_SERVER_SHELL_H_ */
