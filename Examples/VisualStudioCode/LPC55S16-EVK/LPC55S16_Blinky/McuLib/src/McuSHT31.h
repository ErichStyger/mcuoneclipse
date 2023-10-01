/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Driver for the Sensirion SHT31 Temperature/Humidity sensor
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_MCUSHT31_H_
#define SOURCES_MCUSHT31_H_

#include "McuSHT31config.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
  uint8_t McuSHT31_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

  /*!
   * \brief Perform a soft reset
   * \return Error code, ERR_OK for no error
   */
uint8_t McuSHT31_Reset(void);

/*!
 * \brief Turn the heater on or off
 * \param on If heater has to be turned on or off
 * \return Error code, ERR_OK for no error
 */
uint8_t McuSHT31_Heater(bool on);

/*!
 * \brief Reads the device status register
 * \param status Where to store the status
 * \return Error code, ERR_OK for no error
 */
uint8_t SHT31_ReadStatus(uint16_t *status);

/*!
 * \brief Read temperature and relative humidity
 * \param temperature Pointer to where to store the value
 * \param humidity Pointer to where to store the value
 * \return Error code, ERR_OK for no error
 */
uint8_t McuSHT31_ReadTempHum(float *temperature, float *humidity);

/*!
 * \brief Module de-initialization
 */
void McuSHT31_Deinit(void);

/*!
 * \brief Module initialization
 */
void McuSHT31_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_MCUSHT31_H_ */
