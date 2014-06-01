/**
 * \file
 * \brief NMEA Parser and GPS handling interface
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the NMEA parser plus a task handling the serial connection to the GPS module.
 */

#ifndef NMEA_H_
#define NMEA_H_

#include "Platform.h"

#if PL_HAS_SHELL
#include "CLS1.h"

#define NMEA_PARSE_COMMAND_ENABLED    (1 && PL_HAS_GPS)
/*!< Set to 1 if parser is present or enabled */

uint8_t NMEA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

#endif /* PL_HAS_SHELL */

/*!
 * \brief Returns the current GPS time, adjusted for the current GMT time zone difference.
 * \param hour number of hours.
 * \param minute number of minutes.
 * \param second number of seconds.
 * \param mSecond number of milliseconds.
 * \return ERR_OK if everything is fine, error code otherwise.
 */
uint8_t NMEA_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second, uint16_t* mSecond);

/*!
 * Returns the current GPS date.
 * \param day day of the month.
 * \param month mont in mm format.
 * \param year Year in yyyy format.
 * \return ERR_OK if everything is fine, error code otherwise.
 */
uint8_t NMEA_GetDate(uint8_t *day, uint8_t *month, uint16_t *year);

/*!
 * \brief return the current GPS position as a string.
 * \param buf Pointer to buffer where to store the position.
 * \param bufSize Size of buffer in bytes.
 * \param isLatitude If TRUE, return latitude, otherwise longitude.
 * \return ERR_OK for no failure, error code otherwise.
 */
uint8_t NMEA_GetPosString(uint8_t *buf, size_t bufSize, bool isLatitude);

/*!
 * \brief Event hook to be called from the PPS (Pulse-Per-Second) interrupt to count the PPS.
 */
void NMEA_OnPPS(void);

/*!
 * Driver initialization routine.
 */
void NMEA_Init(void);

#endif /* NMEA_H_ */
