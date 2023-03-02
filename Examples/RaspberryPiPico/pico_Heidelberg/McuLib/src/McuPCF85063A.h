/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUPCF85063A_H_
#define MCUPCF85063A_H_

#include "McuPCF85063A_config.h"
#include "McuShell.h"
#include "McuTimeDate.h"

uint8_t McuPCF85063A_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

uint8_t McuPCF85063A_GetTime(TIMEREC *time);
uint8_t McuPCF85063A_GetDate(DATEREC *date);
uint8_t McuPCF85063A_SetTime(TIMEREC *time);
uint8_t McuPCF85063A_SetDate(DATEREC *date);
uint8_t McuPCF85063A_GetTimeDate(TIMEREC *time, DATEREC *date);

uint8_t McuPCF85063A_SetTimeInfo(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100);
uint8_t McuPCF85063A_SetDateInfo(uint16_t Year, uint8_t Month, uint8_t Day);

typedef enum McuPCF85063A_COF_Frequency_e {
  McuPCF85063A_COF_FREQ_32768 = 0,
  McuPCF85063A_COF_FREQ_16384 = 1,
  McuPCF85063A_COF_FREQ_8192  = 2,
  McuPCF85063A_COF_FREQ_4096  = 3,
  McuPCF85063A_COF_FREQ_2048  = 4,
  McuPCF85063A_COF_FREQ_1024  = 5,
  McuPCF85063A_COF_FREQ_1     = 6,
  McuPCF85063A_COF_FREQ_OFF   = 7
} McuPCF85063A_COF_Frequency_e;

uint8_t McuPCF85063A_WriteClockOutputFrequency(McuPCF85063A_COF_Frequency_e frequency);

void McuPCF85063A_Deinit(void);

void McuPCF85063A_Init(void);

#endif /* MCUPCF85063A_H_ */
