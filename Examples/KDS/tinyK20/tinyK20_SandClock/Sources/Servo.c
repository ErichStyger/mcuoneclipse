/*
 * Servo.c
 *
 *  Created on: 14.10.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#include "Servo.h"
#include "PCA9685.h"
#include "PE_Error.h"

#define SERVO_FREQ_HZ   60
#define SERVO_MIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  600 // this is the 'maximum' pulse length count (out of 4096)


uint8_t SERVO_InitHardware(uint8_t i2cAddr) {
  if (PCA9685_Reset(i2cAddr)!=ERR_OK) { /* reset and disable PWM */
    return ERR_FAILED;
  }
  if (PCA9685_SetPWMFrequency(i2cAddr, SERVO_FREQ_HZ)!=ERR_OK) {  /* set base frequency */
    return ERR_FAILED;
  }
}

uint8_t SERVO_WriteDutyMicroSeconds(uint8_t i2cAddr, uint8_t channel, uint16_t microSeconds, uint16_t minTicks, uint16_t maxTicks) {
  uint32_t val;
  #define SERVO_MIN_MICROSECONDS  1000
  #define SERVO_MAX_MICROSECONDS  2000

  /* microseconds in the range 1000..2000 */
  if (microSeconds<SERVO_MIN_MICROSECONDS) {
    microSeconds =  SERVO_MIN_MICROSECONDS;
  } else if (microSeconds>SERVO_MAX_MICROSECONDS) {
    microSeconds = SERVO_MAX_MICROSECONDS;
  }
  val = minTicks + ((microSeconds-SERVO_MIN_MICROSECONDS)*(maxTicks-minTicks))/(SERVO_MAX_MICROSECONDS-SERVO_MIN_MICROSECONDS);
  /* ticks in the range of minTicks...maxTicks */
  if (val>maxTicks) {
    val = maxTicks;
  } else if (val<minTicks) {
    val = minTicks;
  }
  return PCA9685_SetChannelDuty12Bit(i2cAddr, channel, 4095-val);
}

void SERVO_Deinit(void) {
}

void SERVO_Init(void) {
}
