/*
 * MPC4728.h
 *
 *  Created on: Jan 30, 2014
 *      Author: tastyger
 */
#ifndef _MPC4728_H__
#define _MPC4728_H__

#include "CLS1.h"

#define MPC4728_MAX_DAC_VAL  0xfff  /* 12bit */

uint8_t MPC4728_SingleWriteDACandEE(uint8_t channel, uint16_t val);

/* Fast Mode Write: updates all 4 channels, but does not affect EEPROM */
uint8_t MPC4728_FastWriteDAC(uint16_t dac[4], size_t dacSize, uint8_t pd[4], size_t pdSize);


byte MPC4728_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void MPC4728_Deinit(void);

void MPC4728_Init(void);


#endif /* _MPC4728_H__ */
