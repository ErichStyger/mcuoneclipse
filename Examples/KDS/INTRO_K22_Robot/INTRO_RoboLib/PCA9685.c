/*
 * PCA9685.c
 *  Driver for the NXP PCA9685: 16 Channel PWM/Servo driver over I2C
 *  Created on: 20.09.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#if PL_CONFIG_HAS_PCA9685
#include "PCA9685.h"
#include "GI2C1.h"
#include "PE_Error.h"
#include <math.h> /* for floor() function */

/*!
 * \brief Reads one or multiple registers with address auto-increment
 * \param i2cAddr I2C device address
 * \param memAddr Memory address in the device
 * \param data Pointer to the data
 * \param dataSize Number of data bytes to read
 * \return Error code
 */
uint8_t PCA9685_ReadRegister(uint8_t i2cAddr, uint8_t memAddr, uint8_t *data, uint16_t dataSize) {
  return GI2C1_ReadAddress(i2cAddr, &memAddr, sizeof(memAddr), data, dataSize);
}

/*!
 * \brief Writes one or multiple registers with address auto-increment
 * \param i2cAddr I2C device address
 * \param memAddr Memory address in the device
 * \param data Pointer to the data
 * \param dataSize Number of data bytes
 * \return Error code
 */
uint8_t PCA9685_WriteRegister(uint8_t i2cAddr, uint8_t memAddr, uint8_t *data, uint16_t dataSize) {
  return GI2C1_WriteAddress(i2cAddr, &memAddr, sizeof(memAddr), data, dataSize);
}

uint8_t PCA9685_SetChannelPWM(uint8_t deviceI2CAddr, uint8_t channel, uint16_t pwm) {
  uint8_t buf[4];
  uint16_t on, off; /* values for on/off cycles */
  uint8_t addr; /* device memory address */

  if (channel>15) { /* only channel 0..15 per device */
    return ERR_FAILED;
  }
  addr = PCA9685_REG_LED0_ON_L+(channel*4); /* output register value array starts with address 6, each channel has 4 bytes of values */
  if(pwm==0) { /* full off */
    on = 0x1000;
    off = 0;
  } else if (pwm>=0xfff) { /* full on */
    on = 0;
    off = 0x1000;
  } else {
    off = 0;
    on = pwm;
  }
  buf[0] = (uint8_t)on;
  buf[1] = (uint8_t)(on>>8);
  buf[2] = (uint8_t)off;
  buf[3] = (uint8_t)(off>>8);
  return PCA9685_WriteRegister(deviceI2CAddr, addr, buf, sizeof(buf));
}

/*!
 * \brief Configures the PWM bases frequency of the device
 * \param deviceI2CAddr I2C device address
 * \param freqHz Frequency in Hz, typically 24 to 1526 Hz
 * \return Error code
 */
uint8_t PCA9685_SetPWMFrequency(uint8_t deviceI2CAddr, float freqHz) {
  float prescaleval = 25000000;
  uint8_t prescale, oldmode, newmode;

  prescaleval /= 4096;
  prescaleval /= freqHz;
  prescaleval -= 1;

  prescale = floor(prescaleval + 0.5);
  GI2C1_ReadByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, &oldmode);
  newmode = (oldmode & 0x7F) | 0x10;            // sleep
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, newmode);
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_PRESCALE, prescale); /* set the prescaler */
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, oldmode);     /* wake up again */
  vTaskDelay(pdMS_TO_TICKS(5)); /* delay */
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, oldmode | 0xa1);  /* turn on auto increment */
  return ERR_OK;
}

uint8_t PCA9685_SetChannelDuty12Bit(uint8_t deviceI2CAddr, uint8_t channel, uint16_t value) {
  if (channel>15) { /* only channel 0..15 per device */
    return ERR_FAILED;
  }
  if (value>4095) {
    value = 4096;
  }
  PCA9685_SetChannelPWM(deviceI2CAddr, channel, value);
  return ERR_OK;
}

uint8_t PCA9685_Reset(uint8_t deviceI2CAddr) {
  return GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, 0); /* reset the PCA9685 and disable all PWM outputs */
}

void PCA9685_Deinit(void) {
}

void PCA9685_Init(void) {
}
#endif /* PL_CONFIG_HAS_PCA9685 */
