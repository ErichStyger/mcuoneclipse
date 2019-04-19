/*
 * ups.h
 *
 *  Created on: 16.04.2019
 *      Author: Erich Styger
 */

#ifndef UPS_H_
#define UPS_H_

int UPS_GetVoltage(float *voltage);
int UPS_GetCharge(float *charge);

void UPS_Deinit(void);
void UPS_Init(void);

#endif /* UPS_H_ */
