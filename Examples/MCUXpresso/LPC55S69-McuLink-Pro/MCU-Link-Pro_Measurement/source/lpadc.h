/*
 * lpadc.h
 *
 *  Created on: 28 Mar 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#ifndef LPADC_H_
#define LPADC_H_

#include "fsl_lpadc.h"

#define LPADC_BASE ADC0
// Change ADC_RESOLUTION_HIGH to 0 to use 12 bit ADC operation
// If ADC_RESOLUTION_HIGH is 1, 16 bit ADC operation is used
#define ADC_RESOLUTION_HIGH (1)
#define ADC_RESOLUTION_STANDARD !ADC_RESOLUTION_HIGH

void init_LPADC0B(void);
uint16_t get_LPADC0B_res(void);
uint16_t get_LPADC0B(void);

void set_CalRes(uint8_t resistors);
void set_CalR1(uint8_t val);
void set_CalR2(uint8_t val);
void set_CalR3(uint8_t val);
void set_CalR4(uint8_t val);
void set_CalDisc(uint8_t val); // 1 is disconnected
void set_LowCurrent(uint8_t val);

#endif /* LPADC_H_ */
