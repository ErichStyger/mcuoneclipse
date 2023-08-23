/*
 * Copyright (c) 2019, 2022 Erich Styger
 * All rights reserved.
 *
 * Driver for the Sensirion SHT40 Temperature/Humidity sensor
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_MCUSHT40_H_
#define SOURCES_MCUSHT40_H_

#include "McuSHT40config.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if MCUSHT40_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
  uint8_t McuSHT40_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*!
 * \brief Perform a soft reset
 * \return Error code, ERR_OK for no error
 */
uint8_t McuSHT40_Reset(void);

/*!
 * \brief Read temperature and relative humidity
 * \param temperature Pointer to where to store the value
 * \param humidity Pointer to where to store the value
 * \return Error code, ERR_OK for no error
 */
uint8_t McuSHT40_ReadTempHum(float *temperature, float *humidity);

/*!
 * \brief Module de-initialization
 */
void McuSHT40_Deinit(void);

/*!
 * \brief Module initialization
 */
void McuSHT40_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_MCUSHT40_H_ */
