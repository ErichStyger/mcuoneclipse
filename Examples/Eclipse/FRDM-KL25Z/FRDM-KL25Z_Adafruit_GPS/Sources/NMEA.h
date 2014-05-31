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

uint8_t NMEA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#define NMEA_PARSE_COMMAND_ENABLED    (1 && PL_HAS_GPS)
#endif /* PL_HAS_SHELL */

uint8_t NMEA_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second, uint16_t* mSecond);
uint8_t NMEA_GetDate(uint8_t *day, uint8_t *month, uint16_t *year);


void NMEA_Init(void);


#endif /* NMEA_H_ */
