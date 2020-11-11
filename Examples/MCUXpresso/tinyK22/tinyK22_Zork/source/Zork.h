/*
 * Zork.h
 *
 *  Created on: 14.11.2018
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_INTRO_COMMON_ZORK_H_
#define SOURCES_INTRO_COMMON_ZORK_H_

#include "McuRTOS.h"
#include "McuShell.h"

extern TaskHandle_t ZorkTaskHandle;

uint8_t ZORK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void ZORK_Deinit(void);

void ZORK_Init(void);


#endif /* SOURCES_INTRO_COMMON_ZORK_H_ */
