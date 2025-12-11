/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuShell.h"
/*!
 * \brief Shell command line parser
 * \param cmd Pointer to the command string
 * \param handled If command has been recognized and handled
 * \param io I/O hander used for output
 * \return Error code, ERR_OK if everything is fine
 */
uint8_t Calibration_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void Calibration_Deinit(void);
void Calibration_Init(void);
void Calibration_Start(void);
int32_t Calib_Offset_Result(int32_t);

#ifdef __cplusplus
}  /* extern "C" */ 
#endif

#endif /* CALIBRATION_H_ */