/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_NTP_CLIENT_H_
#define SRC_NTP_CLIENT_H_

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
  uint8_t NtpClient_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*!
 * \brief Decide if NTP client shall start by default.
 * \return true if it shall be started, false otherwise. 
 */
bool NtpClient_GetDefaultStart(void);

/*!
 * \brief Suspend the NTP client task
 */
void NtpClient_TaskSuspend(void);

/*!
 * \brief Resume the NTP client task
 */
void NtpClient_TaskResume(void);

/*!
 * \brief Module initialization
 */
void NtpClient_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SRC_NTP_CLIENT_H_ */
