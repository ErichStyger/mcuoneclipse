/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Interface for for the LC709203 battery gauge I2C sensor
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_MCULC709203F_H_
#define SOURCES_MCULC709203F_H_

#ifdef __cplusplus
extern "C" {
#endif

#if MCULC709203F_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"
#endif

/*!
 * \brief Returns the current battery voltage
 * \param pVoltage Pointer where to store the value (in mV)
 * \return Error code, ERR_OK for no error
 */
uint8_t McuLC_GetVoltage(uint16_t *pVoltage);

typedef enum {
  McuLC_CURRENT_DIR_AUTO,         /*!< automatic mode (default) */
  McuLC_CURRENT_DIR_CHARGING,     /*!< charging mode */
  McuLC_CURRENT_DIR_DISCHARING,   /*!< discharging mode */
  McuLC_CURRENT_DIR_ERROR         /*!< error case */
} McuLC_CurrentDirection;
/*!< Current direction used for McuLC_GetCurrentDirection() and McuLC_SetCurrentDirection() */

uint8_t McuLC_GetVoltage(uint16_t *pVoltage);
uint8_t McuLC_GetTemperature(int16_t *pTemperature);
uint8_t McuLC_GetRSOC(uint16_t *pRsoc);
uint8_t McuLC_GetITE(uint16_t *pIte);
uint8_t McuLC_GetICversion(uint16_t *pVersion);

uint8_t McuLC_SetTemperatureMeasurementMode(bool i2cMode);

/*!
 * \brief Get the current temperature measurement mode
 * \param pDir Pointer where to store the mode
 * \return Error code, ERR_OK if everything is ok
 */
uint8_t McuLC_GetTemperatureMeasurementMode(bool *isI2Cmode);


/*!
 * \brief Get the current direction mode
 * \param pDir Pointer where to store the mode
 * \return Error code, ERR_OK if everything is ok
 */
uint8_t McuLC_GetCurrentDirection(McuLC_CurrentDirection *pDir);

/*!
 * \brief Set the current direction mode
 * \param dir Mode to set
 * \return Error code, ERR_OK if everything is ok
 */
uint8_t McuLC_SetCurrentDirection(McuLC_CurrentDirection dir);

/*!
 * \brief Sets the device power mode (normal or sleep mode)
 * \param sleepMode true to put device into sleep mode, false for normal operational mode
 * \return Error code, ERR_OK if everything is ok
 */
uint8_t McuLC_SetPowerMode(bool sleepMode);

/*!
 * \brief Wake up the device from sleep mode. Uses bit-banging. If other devices are on the bus, this method has to be called before anything else!
 */
void McuLC_Wakeup(void); /* must be done before any other I2C communication on the bus! */

#if MCULC709203F_CONFIG_PARSE_COMMAND_ENABLED
/*!
 * \brief Module command line parser
 * \param cmd Pointer to string to be parsed
 * \param handled set to true if command was recognized
 * \param io standard I/O handler
 * \return Error code, ERR_OK if everything is ok
 */
uint8_t McuLC_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*!
 * \brief Driver initialization. I2C bus must be operational for this.
 * \return Error code, ERR_OK if everything is ok
 */
uint8_t McuLC_Init(void);

/*!
 * \brief Driver de-initialisation
 */
void McuLC_Deinit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_MCULC709203F_H_ */
