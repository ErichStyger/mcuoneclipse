/*
 * MMA8451.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Erich Styger
 */
#include "MMA8451.h"
#include "GI2C1.h"

/* External 3-axis accelerometer control register addresses */
#define MMA8451_CTRL_REG_1 0x2A
/* MMA8451 3-axis accelerometer control register bit masks */
#define MMA8451_ACTIVE_BIT_MASK 0x01
#define MMA8451_F_READ_BIT_MASK 0x02

/* External 3-axis accelerometer data register addresses */
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06

#define MMA8451_I2C_ADDR   (0x1D) /* SA0=1 */
//#define MMA8451_I2C_ADDR   (0x1C) /* SA0=0 */

uint8_t MMA8451_GetRaw8XYZ(uint8_t xyz[3]) {
  static const uint8_t addr = MMA8451_OUT_X_MSB;

  return GI2C1_ReadAddress(MMA8451_I2C_ADDR, (uint8_t*)&addr, sizeof(addr), &xyz[0], sizeof(xyz));
}

uint8_t MMA8451_Deinit(void) {
  /* nothing to do */
  return ERR_OK;
}

uint8_t MMA8451_Init(void) {
  static const uint8_t addr = MMA8451_CTRL_REG_1;
  static const uint8_t data = MMA8451_F_READ_BIT_MASK|MMA8451_ACTIVE_BIT_MASK;
  /* F_READ: Fast read mode, data format limited to single byte (auto increment counter will skip LSB)
   * ACTIVE: Full scale selection
   */
  return GI2C1_WriteAddress(MMA8451_I2C_ADDR, (uint8_t*)&addr, sizeof(addr), (uint8_t*)&data, sizeof(data));
}

