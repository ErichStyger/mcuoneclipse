/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BLINKY_H_
#define BLINKY_H_

#include "platform.h"
#if PL_CONFIG_USE_BLINKY
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void Blinky_SetOnTime(uint32_t ms);
void Blinky_Suspend(void);
void Blinky_Resume(void);
void Blinky_GetStatus(unsigned char *buf, size_t bufSize);

#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"

  /*!
   * \brief Command line and shell handler
   * \param cmd The command to be parsed
   * \param handled If command has been recognized and handled
   * \param io I/O handler to be used
   * \return error code, otherwise ERR_OK
   */
  uint8_t Blinky_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*! \brief Module initialization */
void Blinky_Init(void);

/*! \brief Module de-initialization */
void Blinky_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* PL_CONFIG_USE_BLINKY */

#endif /* BLINKY_H_ */
