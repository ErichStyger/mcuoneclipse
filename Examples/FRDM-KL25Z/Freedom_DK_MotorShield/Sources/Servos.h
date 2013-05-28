/*
 * Servos.h
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#ifndef SERVOS_H_
#define SERVOS_H_

typedef enum {
  SERVO1,
  SERVO2
} SERVO_Servo;

uint8_t SERVO_SetPos(SERVO_Servo servo, uint16_t pos);
uint8_t SERVO_SetPosPercent(SERVO_Servo servo, uint8_t percent);

#endif /* SERVOS_H_ */
