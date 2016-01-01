/*
 * AdaBLE.h
 *
 *  Created on: 30.12.2015
 *      Author: Erich Styger
 */

#ifndef SOURCES_ADABLE_H_
#define SOURCES_ADABLE_H_

#include <stdint.h>
#include <stdbool.h>
#include "sdep.h"
#include "CLS1.h"

bool ABLE_sendPacket(uint16_t command, const uint8_t *buf, uint8_t count, uint8_t more_data);

bool ABLE_getResponse(void);

uint8_t ABLE_ParseCommand(const uint8_t *cmd, bool *handled, CLS1_ConstStdIOType *io);

void ABLE_Init(void);

#endif /* SOURCES_ADABLE_H_ */
