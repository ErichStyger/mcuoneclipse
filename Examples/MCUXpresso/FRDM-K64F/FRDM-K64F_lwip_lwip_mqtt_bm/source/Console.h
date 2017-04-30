/*
 * Console.h
 *
 *  Created on: 22.01.2017
 *      Author: Erich Styger Local
 */

#ifndef SOURCE_CONSOLE_H_
#define SOURCE_CONSOLE_H_

#include "CLS1.h"

CLS1_ConstStdIOType *CONSOLE_GetStdio(void);

uint8_t CONSOLE_SendChar(uint8_t ch);

void CONSOLE_Init(void);


#endif /* SOURCE_CONSOLE_H_ */
