/*
 * AD5151.h
 *
 *  Created on: 12.02.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_AD5252_H_
#define SOURCES_AD5252_H_

#include "Platform.h"
#include "CLS1.h"

typedef enum {
  AD5252_RESERVED0 = 0,
  AD5252_EEMEM1 = 1,
  AD5252_RESERVED2 = 2,
  AD5252_EEMEM3 = 3,
  AD5252_EEMEM4 = 4,
  AD5252_EEMEM5 = 5,
  AD5252_EEMEM6 = 6,
  AD5252_EEMEM7 = 7,
  AD5252_EEMEM8 = 8,
  AD5252_EEMEM9 = 9,
  AD5252_EEMEM10 = 10,
  AD5252_EEMEM11 = 11,
  AD5252_EEMEM12 = 12,
  AD5252_EEMEM13 = 13,
  AD5252_EEMEM14 = 14,
  AD5252_EEMEM15 = 15
} AD5252_EEMEM_REG;

typedef enum {
  AD5252_RDAC1 = 1,
  AD5252_RDAC3 = 3,
} AD5252_RDAC_REG;


uint8_t AD5252_ReadEEMEMReg(AD5252_EEMEM_REG reg, uint8_t *val);
uint8_t AD5252_ReadRDACReg(AD5252_RDAC_REG reg, uint8_t *val);

uint8_t AD5252_WriteEEMEMReg(AD5252_EEMEM_REG reg, uint8_t val);
uint8_t AD5252_WriteRDACReg(AD5252_RDAC_REG reg, uint8_t val);


uint8_t AD5252_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);

void AD5252_Init(void);

#endif /* SOURCES_AD5252_H_ */
