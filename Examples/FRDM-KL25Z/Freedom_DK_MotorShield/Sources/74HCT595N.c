/*
 * 74HCT595N.c
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#include "Platform.h"

/*!
 * D12, DIR_LATCH, pin 12: STCP, Storage register clock input
 * D11, PWM2A, IC1 PWM
 * D10, PWM1B, Servo1
 * D09, PWM1A, Servo2
 * D08, DIR_SER, pin 14: DS, Serial Data Input
 * D07, DIR_EN, pin 13: OE, Output Enable, low Active
 * D06, PWM0A, IC2 PWM
 * D05, PWM0B, IC2 PWM
 * D04, DIR_CLK, pin 11: SHCP, Shift register clock input
 * D03, PWM2B, IC1 PWM
 */

uint8_t HCT_WriteByte(uint8_t val);


