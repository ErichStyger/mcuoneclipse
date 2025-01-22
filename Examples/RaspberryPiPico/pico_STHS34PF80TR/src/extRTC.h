/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_EXTRTC_H_
#define SRC_EXTRTC_H_

#include <stdint.h>
#include "McuTimeDate.h"

/* the interfaces below are used by McuTimeDate to for the external RTC */
uint8_t ExtRTC_GetTime(TIMEREC *time);
uint8_t ExtRTC_SetTimeInfo(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100);
uint8_t ExtRTC_GetDate(DATEREC *date);
uint8_t ExtRTC_SetDateInfo(uint16_t Year, uint8_t Month, uint8_t Day);

void ExtRTC_Suspend(void);
void ExtRTC_Resume(void);

void ExtRTC_Deinit(void);
void ExtRTC_Init(void);

#endif /* SRC_EXTRTC_H_ */
