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
#include "FRTOS1.h"
#include <math.h> /* for floor() function */
#include "UTIL1.h"

static uint8_t PCA9685_I2C_Addr = 0b1000000; /* default address */


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
  newmode = (oldmode & 0x7F) | 0x10;            /* sleep */
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, newmode);
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_PRESCALE, prescale); /* set the prescaler */
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, oldmode);     /* wake up again */
  vTaskDelay(pdMS_TO_TICKS(5)); /* delay */
  GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, oldmode|0xa1);  /* turn on auto increment */
  return ERR_OK;
}

uint8_t PCA9685_SetChannelDuty12Bit(uint8_t deviceI2CAddr, uint8_t channel, uint16_t value) {
  if (channel>15) { /* only channel 0..15 per device */
    return ERR_FAILED;
  }
  if (value>4095) {
    value = 4096;
  }
  return PCA9685_SetChannelPWM(deviceI2CAddr, channel, value);
}

uint8_t PCA9685_Reset(uint8_t deviceI2CAddr) {
  return GI2C1_WriteByteAddress8(deviceI2CAddr, PCA9685_REG_MODE1, 0); /* reset the PCA9685 and disable all PWM outputs */
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t buf[48], channelStr[12], res;
  int32_t val;
  int channel;
  uint8_t addr;

  CLS1_SendStatusStr((unsigned char*)"pca9685", (const unsigned char*)"\r\n", io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), "0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), PCA9685_I2C_Addr);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  CLS1_SendStatusStr((unsigned char*)"  i2c addr", buf, io->stdOut);

  for(channel=0; channel<PCA9685_NOF_CHANNELS; channel++) {
    UTIL1_strcpy(channelStr, sizeof(channelStr), "  ch");
    UTIL1_strcatNum8u(channelStr, sizeof(channelStr), channel);
    addr = PCA9685_REG_LED0_ON_L+(channel*4); /* output register value array starts with address 6, each channel has 4 bytes of values */
    res = PCA9685_ReadRegister(PCA9685_I2C_Addr, addr, (uint8_t*)&val, sizeof(val));
    if (res!=ERR_OK) {
      UTIL1_strcpy(buf, sizeof(buf), " fail\r\n");
    } else {
      UTIL1_strcpy(buf, sizeof(buf), "On: 0x");
      UTIL1_strcatNum16Hex(buf, sizeof(buf), val&0xffff);
      UTIL1_strcat(buf, sizeof(buf), " Off: 0x");
      UTIL1_strcatNum16Hex(buf, sizeof(buf), (val>>16)&0xffff);
      UTIL1_strcat(buf, sizeof(buf), "\r\n");
    }
    CLS1_SendStatusStr(channelStr, buf, io->stdOut);
  }
  return ERR_OK;
}

uint8_t PCA9685_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const uint8_t *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "pca9685 help")==0) {
    CLS1_SendHelpStr((unsigned char*)"pca9685", (const unsigned char*)"Group of pca9685 commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  pwm <channel> <val>", (const unsigned char*)"Set channel pwm with a value (0-0xfff)\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "pca9685 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "pca9685 pwm ", sizeof("pca9685 pwm ")-1)==0) {
    uint16_t channel;
    int32_t pwm;

    p = cmd+sizeof("pca9685 pwm ")-1;
    if (UTIL1_ScanDecimal16uNumber(&p, &channel)==ERR_OK) {
      if (UTIL1_xatoi(&p, &pwm)==ERR_OK) {
        if (pwm<0) {
          pwm = 0;
        } else if (pwm>0xfff) {
          pwm = 0xfff;
        }
        PCA9685_SetChannelPWM(PCA9685_I2C_Addr, channel, pwm);
      }
    }
    *handled = TRUE;
  }
  return ERR_OK;
}


void PCA9685_Deinit(void) {
}

void PCA9685_Init(void) {
}
#endif /* PL_CONFIG_HAS_PCA9685 */
