/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "McuSTMPE610config.h"
#include "McuSTMPE610.h"
#include "McuGPIO.h"
#include "McuSPI.h"
#include "McuUtility.h"
#include "McuShell.h"
#include "TouchCalibrate.h"

static McuSPI_Config configSPI = -1;

#define SELECT_CONTROLLER()    McuGPIO_SetLow(McuSTMPE610_CSPin)
#define DESELECT_CONTROLLER()  McuGPIO_SetHigh(McuSTMPE610_CSPin);

static McuGPIO_Handle_t McuSTMPE610_CSPin;

uint8_t McuSTMPE610_WriteReg8(uint8_t reg, uint8_t val) {
  SELECT_CONTROLLER();
  McuSPI_WriteByte(configSPI, reg);
  McuSPI_WriteByte(configSPI, val);
  DESELECT_CONTROLLER();
  return ERR_OK;
}

uint8_t McuSTMPE610_ReadReg8(uint8_t addr, uint8_t *val) {
  SELECT_CONTROLLER();
  McuSPI_WriteByte(configSPI, 0x80|addr); /* MSB to denote read operation */
  McuSPI_ReadByte(configSPI, val); /* read value */
  DESELECT_CONTROLLER();
  return ERR_OK;
}

uint8_t McuSTMPE610_ReadReg16(uint8_t addr, uint16_t *val) {
  uint8_t high, low;

  SELECT_CONTROLLER();
  McuSPI_WriteByte(configSPI, 0x80|addr); /* MSB to denote read operation */
  McuSPI_WriteReadByte(configSPI, 0x80|(addr+1), &high); /* read value */
  McuSPI_ReadByte(configSPI, &low); /* read value */
  DESELECT_CONTROLLER();
  *val = (high<<8)|low;
  return ERR_OK;
}

uint8_t McuSTMPE610_FIFOisEmpty(bool *isEmpty) {
  uint8_t val, res;

  res = McuSTMPE610_ReadReg8(MCUSTMPE610_FIFO_STA_REG, &val);
  if (res!=ERR_OK) {
    return res;
  }
  *isEmpty = val & MCUSTMPE610_FIFO_STA_EMPTY;
  return ERR_OK;
}

uint8_t McuSTMPE610_FIFOBufSize(uint8_t *size) {
  return McuSTMPE610_ReadReg8(MCUSTMPE610_FIFO_SIZE_REG, size);
}

uint8_t McuSTMPE610_IsTouched(bool *touched) {
  uint8_t val, res;

  res = McuSTMPE610_ReadReg8(MCUSTMPE610_TSC_CTRL_REG, &val);
  if (res!=ERR_OK) {
    return res;
  }
  *touched = val&MCUSTMPE610_TSC_CTRL_STA; /* bit set if touched */
  return ERR_OK;
}

uint8_t McuSTMPE610_ReadTouchData(uint16_t *x, uint16_t *y, uint8_t *z) {
  uint8_t data[4], res;
  bool empty;

  for (uint8_t i = 0; i < 4; i++) {
    res = McuSTMPE610_ReadReg8(MCUSTMPE610_TSC_DATA_XYZ_REG+i, &data[i]);
    if (res!=ERR_OK) {
      return res;
    }
  }
  *x = data[0];
  *x <<= 4;
  *x |= (data[1]>>4);
  *y = data[1]&0x0F;
  *y <<= 8;
  *y |= data[2];
  *z = data[3];
  res = McuSTMPE610_FIFOisEmpty(&empty);
  if (res==ERR_OK && empty) {
    res = McuSTMPE610_WriteReg8(MCUSTMPE610_INT_STA_REG, 0xff); /* reset all interrupts */
    if (res!=ERR_OK) {
      return res;
    }
  }
  return ERR_OK;
}

uint8_t McuSTMPE610_GetPoint(uint16_t *x, uint16_t *y, uint8_t *z) {
  uint16_t xp, yp;
  uint8_t zp;
  uint8_t res;

  res = McuSTMPE610_ReadTouchData(&xp, &yp, &zp);
  if (res!=ERR_OK) {
    return res;
  }
  *x = xp;
  *y = yp;
  *z = zp;
  return ERR_OK;
}

uint8_t McuSTMPE610_GetLastPoint(uint16_t *x, uint16_t *y, uint8_t *z) {
  uint16_t xp, yp;
  uint8_t zp, res = ERR_OK;
  bool empty;

  do {
    res = McuSTMPE610_GetPoint(&xp, &yp, &zp);
    if (res!=ERR_OK) {
      break;
    }
    res = McuSTMPE610_FIFOisEmpty(&empty);
    if (res!=ERR_OK) {
      break;
    }
  } while(!empty);
  *x = xp;
  *y = yp;
  *z = zp;
  McuShell_printf("touch last raw: x:%d, y:%d z:%d\r\n", xp, yp, zp);
  return res;
}

uint8_t McuSTMPE610_GetCalibratedCoordinates(uint16_t *x, uint16_t *y, uint8_t *z) {
  uint8_t res;
  uint16_t xd, yd;
  uint8_t zd;

  res = McuSTMPE610_GetLastPoint(&xd, &yd, &zd);
  if (res==ERR_OK) {
    TouchCalib_Calibrate(&xd, &yd);
    McuShell_printf("touch calib: x:%d, y:%d z:%d\r\n", xd, yd, zd);
    *x = xd;
    *y = yd;
    *z = zd;
    return ERR_OK;
  }
  return res;
}

uint8_t McuSTMPE610_GetRawCoordinates(uint16_t *x, uint16_t *y, uint8_t *z) {
  return McuSTMPE610_GetLastPoint(x, y, z);
}

uint8_t McuSTMPE610_CheckAndSwitchSPIMode(void) {
  /* see https://github.com/adafruit/Adafruit_CircuitPython_STMPE610/issues/3
   * The problem is that the device might use SPI Mode0 or Mode1, depending on power-up
   * The correct mode is detected by reading the ID register
   */
  uint8_t id;

  McuSTMPE610_ReadReg8(MCUSTMPE610_ID_VER_REG, &id);
  if (id!=MCUSTMPE610_CHIP_ID_DEFAULT) { /* current SPI mode does not work? switch to different mode1 */
    configSPI = McuSPI_ConfigTouch2; /* try alternate configuration */
    McuSTMPE610_ReadReg8(MCUSTMPE610_ID_VER_REG, &id);
    if (id!=MCUSTMPE610_CHIP_ID_DEFAULT) {
      return ERR_FAILED;
    }
  }
  return ERR_OK;
}

uint8_t McuSTMPE610_GetID(uint8_t *id) {
  /* should return MCUSTMPE610_CHIP_ID_DEFAULT as ID */
  return McuSTMPE610_ReadReg8(MCUSTMPE610_ID_VER_REG, id);
}

uint8_t McuSTMPE610_GetVersion(uint16_t *version) {
  /* should return 0x0811 as version */
  return McuSTMPE610_ReadReg16(MCUSTMPE610_CHIP_ID_REG, version);
}

uint8_t McuSTMPE610_InitController(void) {
  uint16_t version;

  if (McuSTMPE610_CheckAndSwitchSPIMode()!=ERR_OK) { /* device might be in SPI mode0 or mode1 */
    return ERR_FAILED;
  }
  if (McuSTMPE610_GetVersion(&version)!=ERR_OK || version!=MCUSTMPE610_ID_VER_DEFAULT) {
    return ERR_FAILED;
  }
  McuSTMPE610_WriteReg8(MCUSTMPE610_SYS_CTRL1_REG, MCUSTMPE610_SYS_CTRL1_RESET); /* reset */
  McuSTMPE610_WriteReg8(MCUSTMPE610_SYS_CTRL2_REG, 0x0); /* turn on clocks */
  McuSTMPE610_WriteReg8(MCUSTMPE610_TSC_CTRL_REG, MCUSTMPE610_TSC_CTRL_XYZ | MCUSTMPE610_TSC_CTRL_EN); /* XYZ enable */
  McuSTMPE610_WriteReg8(MCUSTMPE610_INT_EN_REG, MCUSTMPE610_INT_EN_TOUCHDET);
  McuSTMPE610_WriteReg8(MCUSTMPE610_ADC_CTRL1_REG, MCUSTMPE610_ADC_CTRL1_10BIT | (0x6 << 4)); /* 96 clocks per conversion */
  McuSTMPE610_WriteReg8(MCUSTMPE610_ADC_CTRL2_REG, MCUSTMPE610_ADC_CTRL2_6_5MHZ);
  McuSTMPE610_WriteReg8(MCUSTMPE610_TSC_CFG_REG, MCUSTMPE610_TSC_CFG_4SAMPLE | MCUSTMPE610_TSC_CFG_DELAY_1MS | MCUSTMPE610_TSC_CFG_SETTLE_5MS);
  McuSTMPE610_WriteReg8(MCUSTMPE610_TSC_FRACTION_Z_REG, 0x6);
  McuSTMPE610_WriteReg8(MCUSTMPE610_FIFO_TH_REG, 1);
  McuSTMPE610_WriteReg8(MCUSTMPE610_FIFO_STA_REG, MCUSTMPE610_FIFO_STA_RESET);
  McuSTMPE610_WriteReg8(MCUSTMPE610_FIFO_STA_REG, 0); /* unreset */
  McuSTMPE610_WriteReg8(MCUSTMPE610_TSC_I_DRIVE_REG, MCUSTMPE610_TSC_I_DRIVE_50MA);
  McuSTMPE610_WriteReg8(MCUSTMPE610_INT_STA_REG, 0xFF); /* reset all ints */
  McuSTMPE610_WriteReg8(MCUSTMPE610_INT_CTRL_REG, MCUSTMPE610_INT_CTRL_POL_HIGH | MCUSTMPE610_INT_CTRL_ENABLE);
  return ERR_OK;
}

void McuSTMPE610_Deinit(void) {
  McuSTMPE610_CSPin = McuGPIO_DeinitGPIO(McuSTMPE610_CSPin);
  configSPI = -1;
}

void McuSTMPE610_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isHighOnInit = true;

  /* initialize STEMPE610 CS (is LOW active) */
  config.hw.pin = MCUSTMPE610_CS_PIN;
  config.hw.port = MCUSTMPE610_CS_PORT;
  config.hw.gpio = MCUSTMPE610_CS_GPIO;
  McuSTMPE610_CSPin = McuGPIO_InitGPIO(&config);

  configSPI = McuSPI_ConfigTouch1; /* default configuration */
}
