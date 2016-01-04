/*
 * bleuart_cmdmode.h
 *
 *  Created on: 03.01.2016
 *      Author: Erich Styger
 */

#ifndef SOURCES_BLEUART_CMDMODE_H_
#define SOURCES_BLEUART_CMDMODE_H_

#include "CLS1.h"

uint8_t BLEUART_CMDMODE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void BLEUART_CMDMODE_Init(void);

#endif /* SOURCES_BLEUART_CMDMODE_H_ */
