/*
 * NMEA.h
 *
 *  Created on: 20.05.2014
 *      Author: tastyger
 */

#ifndef NMEA_H_
#define NMEA_H_

#include "Platform.h"

#include "CLS1.h"

uint8_t NMEA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#define NMEA_PARSE_COMMAND_ENABLED    (1 && PL_HAS_GPS)


uint8_t NMEA_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second, uint16_t* mSecond);
uint8_t NMEA_GetDate(uint8_t *day, uint8_t *month, uint16_t *year);


void NMEA_Init(void);


#endif /* NMEA_H_ */
