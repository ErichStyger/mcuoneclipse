/*
 * PCA9685.h
 *  Driver for the NXP PCA8685: 16 Channel PWM/Servo driver over I2C
 *  Created on: 20.09.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_INTRO_ROBOLIB_PCA9685_H_
#define SOURCES_INTRO_ROBOLIB_PCA9685_H_

#include <stdint.h>

/* default I2C Address with all address pins (A0 to A5) on GND */
#define PCA9685_I2C_DEFAULT_ADDR  (0b1000000)

#define PCA9685_NOF_CHANNELS    16  /* channels 0-15 */

/* register addresses */
#define PCA9685_REG_MODE1       0x00  /* MODE1 */
#define PCA9685_REG_MODE2       0x01  /* MODE2 */
#define PCA9685_REG_LED0_ON_L   0x06  /* LED0 output and brightness control byte 0 */
#define PCA9685_REG_PRESCALE    0xFE  /* PRE_SCALE */

/*!
 * \brief Reads one or multiple registers with address auto-increment
 * \param i2cAddr I2C device address
 * \param memAddr Memory address in the device
 * \param data Pointer to the data
 * \param dataSize Number of data bytes to read
 * \return Error code
 */
uint8_t PCA9685_ReadRegister(uint8_t i2cAddr, uint8_t memAddr, uint8_t *data, uint16_t dataSize);

/*!
 * \brief Writes one or multiple registers with address auto-increment
 * \param i2cAddr I2C device address
 * \param memAddr Memory address in the device
 * \param data Pointer to the data
 * \param dataSize Number of data bytes
 * \return Error code
 */
uint8_t PCA9685_WriteRegister(uint8_t i2cAddr, uint8_t memAddr, uint8_t *data, uint16_t dataSize);

/*!
 * \brief Sets the PWM for the given channel
 * \param deviceI2CAddr I2C Address of the PCA9685 to be used
 * \param channel Channel on the device, in the range of 0-15
 * \param pwm PWM value, in the range of 0-0xfff
 * \return Error code, ERR_OK for everything is ok
 */
uint8_t PCA9685_SetChannelPWM(uint8_t deviceI2CAddr, uint8_t channel, uint16_t pwm);

/*!
 * \brief Configures the PWM bases frequency of the device
 * \param deviceI2CAddr I2C device address
 * \param freqHz Frequency in Hz, typically 24 to 1526 Hz
 * \return Error code
 */
uint8_t PCA9685_SetPWMFrequency(uint8_t deviceI2CAddr, float freqHz);

/*!
 * \brief Sets the channel duty for a given device
 * \param deviceI2CAddr I2C address of device
 * \param channel PWM channel on the device, 0-15
 * \param value 12bit Duty value in the range of 0-0xfff
 * \return Error code
 */
uint8_t PCA9685_SetChannelDuty12Bit(uint8_t deviceI2CAddr, uint8_t channel, uint16_t value);

/*!
 * \brief reset the device and disable all PWM outputs
 * @param deviceI2CAddr
 * @return Error code
 */
uint8_t PCA9685_Reset(uint8_t deviceI2CAddr);


/*!
 * \brief Driver de-initialization function
 */
void PCA9685_Deinit(void);

/*!
 * \brief Driver initialization function
 */
void PCA9685_Init(void);

#include "CLS1.h"
uint8_t PCA9685_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);


#endif /* SOURCES_INTRO_ROBOLIB_PCA9685_H_ */
