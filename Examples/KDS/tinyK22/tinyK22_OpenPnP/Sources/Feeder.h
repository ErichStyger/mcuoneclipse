/*
 * Feeder.h
 *
 *  Created on: 19.04.2018
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_FEEDER_H_
#define SOURCES_FEEDER_H_

#include "CLS1.h"

uint8_t FEED_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);

void FEED_Init(void);


#endif /* SOURCES_FEEDER_H_ */
