/*
 * Zork.h
 *
 *  Created on: 14.11.2018
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_INTRO_COMMON_ZORK_H_
#define SOURCES_INTRO_COMMON_ZORK_H_

#include "FRTOS1.h"
#include "CLS1.h"

extern TaskHandle_t ZorkTaskHandle;

uint8_t ZORK_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void ZORK_Deinit(void);

void ZORK_Init(void);


#endif /* SOURCES_INTRO_COMMON_ZORK_H_ */
