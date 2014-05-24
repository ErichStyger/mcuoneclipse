/*
 * NMEA.h
 *
 *  Created on: 20.05.2014
 *      Author: tastyger
 */

#ifndef NMEA_H_
#define NMEA_H_

#include "CLS1.h"

uint8_t NMEA_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#define NMEA_PARSE_COMMAND_ENABLED    1

void NMEA_Init(void);


#endif /* NMEA_H_ */
