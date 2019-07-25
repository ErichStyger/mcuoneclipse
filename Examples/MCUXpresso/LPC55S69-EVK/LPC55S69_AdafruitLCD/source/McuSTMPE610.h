/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSTMPE610_H_
#define MCUSTMPE610_H_

#include <stdint.h>
#include <stdbool.h>

/* see https://github.com/adafruit/Adafruit_STMPE610 for register definition */
#define MCUSTMPE610_CHIP_ID_REG       0x00
  #define MCUSTMPE610_CHIP_ID_DEFAULT   0x03 /* default factory ID */

#define MCUSTMPE610_ID_VER_REG        0x02
  #define MCUSTMPE610_ID_VER_DEFAULT    0x0811 /* default factory version */

/* Reset Control */
#define MCUSTMPE610_SYS_CTRL1_REG     0x03
  #define MCUSTMPE610_SYS_CTRL1_RESET   0x02

/* Clock Control */
#define MCUSTMPE610_SYS_CTRL2_REG     0x04

/* Interrupt status */
#define MCUSTMPE610_INT_STA_REG       0x0B
  #define MCUSTMPE610_INT_STA_TOUCHDET 0x01

/* Interrupt control */
#define MCUSTMPE610_INT_CTRL_REG  0x09
  #define MCUSTMPE610_INT_CTRL_POL_HIGH 0x04
  #define MCUSTMPE610_INT_CTRL_POL_LOW  0x00
  #define MCUSTMPE610_INT_CTRL_EDGE     0x02
  #define MCUSTMPE610_INT_CTRL_LEVEL    0x00
  #define MCUSTMPE610_INT_CTRL_ENABLE   0x01
  #define MCUSTMPE610_INT_CTRL_DISABLE  0x00

/* Interrupt enable */
#define MCUSTMPE610_INT_EN_REG    0x0A
  #define MCUSTMPE610_INT_EN_TOUCHDET   0x01
  #define MCUSTMPE610_INT_EN_FIFOTH     0x02
  #define MCUSTMPE610_INT_EN_FIFOOF     0x04
  #define MCUSTMPE610_INT_EN_FIFOFULL   0x08
  #define MCUSTMPE610_INT_EN_FIFOEMPTY  0x10
  #define MCUSTMPE610_INT_EN_ADC        0x40
  #define MCUSTMPE610_INT_EN_GPIO       0x80

/* GPIO */
#define MCUSTMPE610_GPIO_SET_PIN_REG    0x10
#define MCUSTMPE610_GPIO_CLR_PIN_REG    0x11
#define MCUSTMPE610_GPIO_DIR_REG        0x13
#define MCUSTMPE610_GPIO_ALT_FUNCT_REG  0x17

/* ADC control */
#define MCUSTMPE610_ADC_CTRL1_REG   0x20
  #define MCUSTMPE610_ADC_CTRL1_12BIT 0x08
  #define MCUSTMPE610_ADC_CTRL1_10BIT 0x00

/* ADC control */
#define MCUSTMPE610_ADC_CTRL2_REG       0x21
  #define MCUSTMPE610_ADC_CTRL2_1_625MHZ  0x00
  #define MCUSTMPE610_ADC_CTRL2_3_25MHZ   0x01
  #define MCUSTMPE610_ADC_CTRL2_6_5MHZ    0x02

/* Touch-screen controller setup */
#define MCUSTMPE610_TSC_CTRL_REG        0x40
  #define MCUSTMPE610_TSC_CTRL_EN         0x01
  #define MCUSTMPE610_TSC_CTRL_XYZ        0x00
  #define MCUSTMPE610_TSC_CTRL_XY         0x02
  #define MCUSTMPE610_TSC_CTRL_STA        0x80 /* bit set to one if touched */

/* Touchscreen controller configuration */
#define MCUSTMPE610_TSC_CFG_REG         0x41
  #define MCUSTMPE610_TSC_CFG_1SAMPLE     0x00
  #define MCUSTMPE610_TSC_CFG_2SAMPLE     0x40
  #define MCUSTMPE610_TSC_CFG_4SAMPLE     0x80
  #define MCUSTMPE610_TSC_CFG_8SAMPLE     0xC0
  #define MCUSTMPE610_TSC_CFG_DELAY_10US  0x00
  #define MCUSTMPE610_TSC_CFG_DELAY_50US  0x08
  #define MCUSTMPE610_TSC_CFG_DELAY_100US 0x10
  #define MCUSTMPE610_TSC_CFG_DELAY_500US 0x18
  #define MCUSTMPE610_TSC_CFG_DELAY_1MS   0x20
  #define MCUSTMPE610_TSC_CFG_DELAY_5MS   0x28
  #define MCUSTMPE610_TSC_CFG_DELAY_10MS  0x30
  #define MCUSTMPE610_TSC_CFG_DELAY_50MS  0x38
  #define MCUSTMPE610_TSC_CFG_SETTLE_10US 0x00
  #define MCUSTMPE610_TSC_CFG_SETTLE_100US 0x01
  #define MCUSTMPE610_TSC_CFG_SETTLE_500US 0x02
  #define MCUSTMPE610_TSC_CFG_SETTLE_1MS  0x03
  #define MCUSTMPE610_TSC_CFG_SETTLE_5MS  0x04
  #define MCUSTMPE610_TSC_CFG_SETTLE_10MS 0x05
  #define MCUSTMPE610_TSC_CFG_SETTLE_50MS 0x06
  #define MCUSTMPE610_TSC_CFG_SETTLE_100MS 0x07

/* FIFO level to generate interrupt */
#define MCUSTMPE610_FIFO_TH_REG         0x4A

/* Current status of FIFO */
#define MCUSTMPE610_FIFO_STA_REG        0x4B
  #define MCUSTMPE610_FIFO_STA_RESET    0x01
  #define MCUSTMPE610_FIFO_STA_OFLOW    0x80
  #define MCUSTMPE610_FIFO_STA_FULL     0x40
  #define MCUSTMPE610_FIFO_STA_EMPTY    0x20
  #define MCUSTMPE610_FIFO_STA_THTRIG   0x10

/* Current filled level of FIFO */
#define MCUSTMPE610_FIFO_SIZE_REG       0x4C

/* Data port for TSC data address */
#define MCUSTMPE610_TSC_DATA_X_REG      0x4D
#define MCUSTMPE610_TSC_DATA_Y_REG      0x4F
#define MCUSTMPE610_TSC_FRACTION_Z_REG  0x56

#define MCUSTMPE610_TSC_DATA_XYZ_REG    0x52


/* Touchscreen controller drive I */
#define MCUSTMPE610_TSC_I_DRIVE_REG     0x58
  #define MCUSTMPE610_TSC_I_DRIVE_20MA 0x00
  #define MCUSTMPE610_TSC_I_DRIVE_50MA 0x01


uint8_t McuSTMPE610_ReadReg8(uint8_t addr, uint8_t *val);
uint8_t McuSTMPE610_ReadReg16(uint8_t addr, uint16_t *val);
uint8_t McuSTMPE610_GetVersion(uint16_t *version);
uint8_t McuSTMPE610_GetID(uint8_t *id);
uint8_t McuSTMPE610_FIFOisEmpty(bool *isEmpty);
uint8_t McuSTMPE610_FIFOBufSize(uint8_t *size);
uint8_t McuSTMPE610_IsTouched(bool *touched);
uint8_t McuSTMPE610_ReadTouchData(uint16_t *x, uint16_t *y, uint8_t *z);
uint8_t McuSTMPE610_GetPoint(uint16_t *x, uint16_t *y, uint8_t *z);
uint8_t McuSTMPE610_GetLastPoint(uint16_t *x, uint16_t *y, uint8_t *z);
uint8_t McuSTMPE610_GetCalibratedCoordinates(uint16_t *x, uint16_t *y, uint8_t *z);
uint8_t McuSTMPE610_GetRawCoordinates(uint16_t *x, uint16_t *y, uint8_t *z);
uint8_t McuSTMPE610_CheckAndSwitchSPIMode(void);
uint8_t McuSTMPE610_InitController(void);

void McuSTMPE610_Deinit(void);
void McuSTMPE610_Init(void);

#endif /* MCUSTMPE610_H_ */
