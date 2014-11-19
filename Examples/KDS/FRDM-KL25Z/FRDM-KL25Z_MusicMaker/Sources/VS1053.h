/*
 * VS1053.h
 *
 *  Created on: 18.11.2014
 *      Author: tastyger
 */

#ifndef VS1053_H_
#define VS1053_H_

/* VS1053 Registers */
#define VS_MODE         0x00
#define VS_STATUS       0x01
#define VS_BASS         0x02
#define VS_CLOCKF       0x03
#define VS_DECODE_TIME  0x04
#define VS_AUDATA       0x05
#define VS_WRAM         0x06
#define VS_WRAMADDR     0x07
#define VS_HDAT0        0x08
#define VS_HDAT1        0x09
#define VS_AIADDR       0x0A
#define VS_VOL          0x0B
#define VS_AICTRL0      0x0C
#define VS_AICTRL1      0x0D
#define VS_AICTRL2      0x0E
#define VS_AICTRL3      0x0F

#include "CLS1.h"
uint8_t VS_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void VS_OnBlockReceived(void);

uint8_t VS_PlaySong(const uint8_t *fileName, const CLS1_StdIOType *io);

uint8_t VS_ReadRegister(uint8_t reg, uint16_t *value);

/*!
 * \brief Driver initialization.
 */
void VS_Init(void);

/*!
 * \brief Driver deinitalization
 */
void VS_Deinit(void);

#endif /* VS1053_H_ */
