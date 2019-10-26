/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef UPS_H_
#define UPS_H_

#include <stdbool.h>

int UPS_GetVoltage(float *voltage);
int UPS_GetCharge(float *charge);

void UPS_SetIsCharging(bool charging);
bool UPS_IsCharging(void);

void UPS_Deinit(void);
void UPS_Init(void);

#endif /* UPS_H_ */
