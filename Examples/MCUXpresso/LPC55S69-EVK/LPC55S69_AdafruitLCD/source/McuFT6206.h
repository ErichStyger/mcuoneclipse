/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUFT6206_H_
#define MCUFT6206_H_

void McuFT6206_Deinit(void);
void McuFT6206_Init(void);

#endif /* MCUFT6206_H_ */


#if 0

Skip to content
Pull requests
Issues
Marketplace
Explore
@ErichStyger

31
19

    16

adafruit/Adafruit_FT6206_Library
Code
Issues 1
Pull requests 1
Projects 0
Security
Insights
Adafruit_FT6206_Library/Adafruit_FT6206.h
@ladyada ladyada commit working travis with testing & doxy 1b093b1 on 15 Jan 2018
@ladyada
@driverblock
92 lines (70 sloc) 2.6 KB
/***************************************************
  This is a library for the Adafruit Capacitive Touch Screens
  ----> http://www.adafruit.com/products/1947

  Check out the links above for our tutorials and wiring diagrams
  This chipset uses I2C to communicate
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef ADAFRUIT_FT6206_LIBRARY
#define ADAFRUIT_FT6206_LIBRARY

#include "Arduino.h"
#include <Wire.h>

#define FT62XX_ADDR           0x38
#define FT62XX_G_FT5201ID     0xA8
#define FT62XX_REG_NUMTOUCHES 0x02

#define FT62XX_NUM_X             0x33
#define FT62XX_NUM_Y             0x34

#define FT62XX_REG_MODE 0x00
#define FT62XX_REG_CALIBRATE 0x02
#define FT62XX_REG_WORKMODE 0x00
#define FT62XX_REG_FACTORYMODE 0x40
#define FT62XX_REG_THRESHHOLD 0x80
#define FT62XX_REG_POINTRATE 0x88
#define FT62XX_REG_FIRMVERS 0xA6
#define FT62XX_REG_CHIPID 0xA3
#define FT62XX_REG_VENDID 0xA8

#define FT62XX_VENDID 0x11
#define FT6206_CHIPID 0x06
#define FT6236_CHIPID 0x36
#define FT6236U_CHIPID 0x64 // mystery!

// calibrated for Adafruit 2.8" ctp screen
#define FT62XX_DEFAULT_THRESHOLD 128

/**************************************************************************/
/*!
    @brief  Helper class that stores a TouchScreen Point with x, y, and z coordinates, for easy math/comparison
*/
/**************************************************************************/
class TS_Point {
 public:
  TS_Point(void);
  TS_Point(int16_t x, int16_t y, int16_t z);

  bool operator==(TS_Point);
  bool operator!=(TS_Point);

  int16_t x; /*!< X coordinate */
  int16_t y; /*!< Y coordinate */
  int16_t z; /*!< Z coordinate (often used for pressure) */
};

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with FT6206 capacitive touch chips
*/
/**************************************************************************/
class Adafruit_FT6206 {
 public:

  Adafruit_FT6206(void);
  boolean begin(uint8_t thresh = FT62XX_DEFAULT_THRESHOLD);
  uint8_t touched(void);
  TS_Point getPoint(uint8_t n = 0);

  //void autoCalibrate(void);

 private:
  void writeRegister8(uint8_t reg, uint8_t val);
  uint8_t readRegister8(uint8_t reg);

  void readData(void);
  uint8_t touches;
  uint16_t touchX[2], touchY[2], touchID[2];

};

#endif //ADAFRUIT_FT6206_LIBRARY

#endif
