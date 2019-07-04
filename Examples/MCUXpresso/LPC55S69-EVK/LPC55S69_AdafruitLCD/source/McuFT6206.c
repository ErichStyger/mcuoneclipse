/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuFT6206config.h"
#include "McuFT6206.h"
#include "McuGenericI2C.h"

#define MCUFT62XX_I2C_ADDR          0x38
#define MCUFT62XX_G_FT5201ID        0xA8
#define MCUFT62XX_REG_NUMTOUCHES    0x02

#define MCUFT62XX_NUM_X             0x33
#define MCUFT62XX_NUM_Y             0x34

#define MCUFT62XX_REG_DATA_START    0x00
#define MCUFT62XX_REG_MODE          0x00
#define MCUFT62XX_REG_CALIBRATE     0x02
#define MCUFT62XX_REG_WORKMODE      0x00
#define MCUFT62XX_REG_FACTORYMODE   0x40
#define MCUFT62XX_REG_THRESHHOLD    0x80
#define MCUFT62XX_REG_POINTRATE     0x88
#define MCUFT62XX_REG_FIRMVERS      0xA6
#define MCUFT62XX_REG_CHIPID        0xA3
#define MCUFT62XX_REG_VENDID        0xA8


/* calibrated for Adafruit 2.8" capacitive touch screen */
#define MCUFT62XX_DEFAULT_THRESHOLD 128

uint8_t McuFT6206_ReadVendorID(uint8_t *id) {
  return McuGenericI2C_ReadByteAddress8(MCUFT62XX_I2C_ADDR, MCUFT62XX_REG_VENDID, id);
}

uint8_t McuFT6206_ReadChipID(uint8_t *id) {
  return McuGenericI2C_ReadByteAddress8(MCUFT62XX_I2C_ADDR, MCUFT62XX_REG_CHIPID, id);
}

uint8_t McuFT6206_ReadFirmwareVersion(uint8_t *version) {
  return McuGenericI2C_ReadByteAddress8(MCUFT62XX_I2C_ADDR, MCUFT62XX_REG_FIRMVERS, version);
}

uint8_t McuFT6206_ReadPointRateHz(uint8_t *rate) {
  return McuGenericI2C_ReadByteAddress8(MCUFT62XX_I2C_ADDR, MCUFT62XX_REG_POINTRATE, rate);
}

uint8_t McuFT6206_ReadThreshold(uint8_t *threshold) {
  return McuGenericI2C_ReadByteAddress8(MCUFT62XX_I2C_ADDR, MCUFT62XX_REG_THRESHHOLD, threshold);
}

uint8_t McuFT6206_WriteThreshold(uint8_t threshold) {
  return McuGenericI2C_WriteByteAddress8(MCUFT62XX_I2C_ADDR, MCUFT62XX_REG_THRESHHOLD, threshold);
}

uint8_t McuFT6206_ReadNofTouches(uint8_t *nof) {
  /* return number of touches, can be 0, 1 or 2 */
  uint8_t res;

  res = McuGenericI2C_ReadByteAddress8(MCUFT62XX_I2C_ADDR, MCUFT62XX_REG_NUMTOUCHES, nof);
  if (res!=ERR_OK) {
    *nof = 0;
    return 0;
  }
  if (*nof>2) { /* error? */
    *nof = 0;
  }
  return ERR_OK;
}

static struct {
  uint8_t touches;
  uint16_t touchX[2], touchY[2], touchID[2];
} McuFT6206_Data;

uint8_t McuFT6206_ReadPoint(uint8_t n, McuFT6206_TouchPoint *point) {
  uint8_t data[16];
  uint8_t addr = MCUFT62XX_REG_DATA_START;
  uint8_t i, res;

  res = McuGenericI2C_ReadAddress(MCUFT62XX_I2C_ADDR, &addr, sizeof(addr), data, sizeof(data));
  if (res!=ERR_OK) {
    return res;
  }
  McuFT6206_Data.touches = data[2];
  if (McuFT6206_Data.touches>2) { /* error case */
    McuFT6206_Data.touches = 0;
  }

  for (i=0; i<2; i++) {
    McuFT6206_Data.touchX[i] = data[0x03 + i*6]&0x0F;
    McuFT6206_Data.touchX[i] <<= 8;
    McuFT6206_Data.touchX[i] |= data[0x04 + i*6];
    McuFT6206_Data.touchY[i] = data[0x05 + i*6]&0x0F;
    McuFT6206_Data.touchY[i] <<= 8;
    McuFT6206_Data.touchY[i] |= data[0x06 + i*6];
    McuFT6206_Data.touchID[i] = data[0x05 + i*6]>>4;
  }

  if (McuFT6206_Data.touches==0 || McuFT6206_Data.touches>1) {
    point->x = 0;
    point->y = 0;
    point->z = 0;
  } else {
    point->x = McuFT6206_Data.touchX[n];
    point->y = McuFT6206_Data.touchY[n];
    point->z = 1;
  }
  return ERR_OK;
}

void McuFT6206_Deinit(void) {
}

void McuFT6206_Init(void) {
  uint8_t res;
#if 0
  uint8_t val = 0;
  McuFT6206_TouchPoint point;

  res = McuFT6206_ReadVendorID(&val); /* expect MCUFT62XX_VENDID */
  res = McuFT6206_ReadChipID(&val);  /* expect MCUFT6206_CHIPID */
  res = McuFT6206_ReadFirmwareVersion(&val);
  res = McuFT6206_ReadPointRateHz(&val);
  res = McuFT6206_ReadThreshold(&val);
#endif
  res = McuFT6206_WriteThreshold(MCUFT62XX_DEFAULT_THRESHOLD);

#if 0
  do {
    res = McuFT6206_ReadNofTouches(&val);
    if (val>0) {
      res = McuFT6206_ReadPoint(0, &point);
      if (point.z>0) {
        val = 0;
      }
    }
  } while(1);
#endif
}


