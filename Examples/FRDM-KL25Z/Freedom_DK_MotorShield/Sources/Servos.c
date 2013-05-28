/*
 * Servos.c
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#if 0
#include "Servos.h"
#include "Servo1.h"
#include "Servo2.h"

/* Servos are using 50 Hz (20 ms) Frequency, with a duty cycle from 1-2 ms */

uint8_t SERVO_SetPos(SERVO_Servo servo, uint16_t pos) {
  uint16_t val;
  
  /* pos left: 1 ms high, 19 ms low
   * pos right: 2 ms high, 18 ms low
   */
  val = 0xFFFF/20; /* 1 ms base, 0x7ff */
  val += pos*(0xFFFF/20)/0xFFFF; /* (val*(0xFFFF/20))/0xFFFF */
  val = 0xffff-val; /* invert polarity */
  if (servo==SERVO1) {
    Servo1_SetRatio16(val);
  } else if (servo==SERVO2) {
    Servo2_SetRatio16(val);
  } else {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t SERVO_SetPosPercent(SERVO_Servo servo, uint8_t percent) {
  if (percent>100) {
    return ERR_FAILED;
  }
  SERVO_SetPos(servo, (0xffff)/100*percent);
  return ERR_OK;
}

#endif
