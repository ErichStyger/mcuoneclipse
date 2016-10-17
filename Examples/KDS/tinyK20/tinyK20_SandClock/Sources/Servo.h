/*
 * Servo.h
 *
 *  Created on: 14.10.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_SERVO_H_
#define SOURCES_SERVO_H_

#include <stdint.h>

#define SERVO_MIN_TICKS 225
#define SERVO_MAX_TICKS 645

uint8_t SERVO_InitHardware(uint8_t i2cAddr);

uint8_t SERVO_WriteDutyMicroSeconds(uint8_t i2cAddr, uint8_t channel, uint16_t microSeconds, uint16_t minTicks, uint16_t maxTicks);

void SERVO_Deinit(void);
void SERVO_Init(void);

#endif /* SOURCES_SERVO_H_ */
