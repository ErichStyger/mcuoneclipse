/*
 * AD5151.h
 *
 *  Created on: 12.02.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_AD5141_H_
#define SOURCES_AD5141_H_

#include "Platform.h"
#include "CLS1.h"

uint8_t AD5141_ReadEEMEMReg(uint8_t *val);
uint8_t AD5141_ReadRDACReg(uint8_t *val);

uint8_t AD5141_WriteEEMEMReg(uint8_t val);
uint8_t AD5141_WriteRDACReg(uint8_t val);

uint8_t AD5141_HardwareReset(void);

uint8_t AD5141_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);

void AD5141_Init(void);

#endif /* SOURCES_AD5141_H_ */
