/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_TCP_CLIENT_H_
#define SRC_TCP_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "platform.h"

#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"

  /*!
   * \brief Command line and shell handler
   * \param cmd The command to be parsed
   * \param handled If command has been recognized and handled
   * \param io I/O handler to be used
   * \return error code, otherwise ERR_OK
   */
  uint8_t TcpClient_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*! \brief Module initialization */
void TcpClient_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SRC_TCP_CLIENT_H_ */
