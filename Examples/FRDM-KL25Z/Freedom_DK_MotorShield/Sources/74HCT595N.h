/*
 * 74HCT595N.h
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#ifndef _74HCT595N_H_
#define _74HCT595N_H_

void HCT_Latch(void);

void HCT_Enable(void);
void HCT_Disable(void);

uint8_t HCT_ShiftByte(uint8_t val);

void HCT_Init(void);

#endif /* 74HCT595N_H_ */
