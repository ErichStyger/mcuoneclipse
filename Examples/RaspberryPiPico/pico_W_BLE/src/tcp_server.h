/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TCP_SERVER_PORT            (1235)

#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"

  /*!
   * \brief Command line and shell handler
   * \param cmd The command to be parsed
   * \param handled If command has been recognized and handled
   * \param io I/O handler to be used
   * \return error code, otherwise ERR_OK
   */
  uint8_t TcpServer_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

void TcpServer_Suspend(void);

void TcpServer_Resume(void);

void TcpServer_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* TCP_SERVER_H_ */
