/*
 * A3967.h
 *
 *  Created on: 18.01.2019
 *      Author: Erich Styger
 */

#include "Platform.h"

#include "AS7264.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "AS7264_RES.h"

#define AS7264_I2C_ADDR   0x49 /* 7bit address */

void AS7264_Init(void) {
  uint8_t res, data;

  AS7264_RES_ClrVal(); /* low active */
  WAIT1_Waitms(50);
  AS7264_RES_SetVal(); /* getting it out of reset */

  res = GI2C1_ReadByte(AS7264_I2C_ADDR, &data);
}

