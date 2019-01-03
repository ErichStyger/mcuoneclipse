/*
 * VL53L0X.h
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#ifndef SOURCES_VL53L0X_H_
#define SOURCES_VL53L0X_H_

#include "PE_Types.h"

#define VL_MULTIPLE_DEVICES  0  /* set to greater zero with the number of devices */

#define VL6180X_DEFAULT_I2C_ADDRESS 0x29 /* default address 0101001b (shifted on the bus it is 0101001x */

enum regAddr {
  IDENTIFICATION__MODEL_ID              = 0x000,
  IDENTIFICATION__MODEL_REV_MAJOR       = 0x001,
  IDENTIFICATION__MODEL_REV_MINOR       = 0x002,
  IDENTIFICATION__MODULE_REV_MAJOR      = 0x003,
  IDENTIFICATION__MODULE_REV_MINOR      = 0x004,
  IDENTIFICATION__DATE_HI               = 0x006,
  IDENTIFICATION__DATE_LO               = 0x007,
  IDENTIFICATION__TIME                  = 0x008, // 16-bit

  SYSTEM__MODE_GPIO0                    = 0x010,
  SYSTEM__MODE_GPIO1                    = 0x011,
  SYSTEM__HISTORY_CTRL                  = 0x012,
  SYSTEM__INTERRUPT_CONFIG_GPIO         = 0x014,
  SYSTEM__INTERRUPT_CLEAR               = 0x015,
  SYSTEM__FRESH_OUT_OF_RESET            = 0x016,
  SYSTEM__GROUPED_PARAMETER_HOLD        = 0x017,

  SYSRANGE__START                       = 0x018,
  SYSRANGE__THRESH_HIGH                 = 0x019,
  SYSRANGE__THRESH_LOW                  = 0x01A,
  SYSRANGE__INTERMEASUREMENT_PERIOD     = 0x01B,
  SYSRANGE__MAX_CONVERGENCE_TIME        = 0x01C,
  SYSRANGE__CROSSTALK_COMPENSATION_RATE = 0x01E, // 16-bit
  SYSRANGE__CROSSTALK_VALID_HEIGHT      = 0x021,
  SYSRANGE__EARLY_CONVERGENCE_ESTIMATE  = 0x022, // 16-bit
  SYSRANGE__PART_TO_PART_RANGE_OFFSET   = 0x024,
  SYSRANGE__RANGE_IGNORE_VALID_HEIGHT   = 0x025,
  SYSRANGE__RANGE_IGNORE_THRESHOLD      = 0x026, // 16-bit
  SYSRANGE__MAX_AMBIENT_LEVEL_MULT      = 0x02C,
  SYSRANGE__RANGE_CHECK_ENABLES         = 0x02D,
  SYSRANGE__VHV_RECALIBRATE             = 0x02E,
  SYSRANGE__VHV_REPEAT_RATE             = 0x031,

  SYSALS__START                         = 0x038,
  SYSALS__THRESH_HIGH                   = 0x03A,
  SYSALS__THRESH_LOW                    = 0x03C,
  SYSALS__INTERMEASUREMENT_PERIOD       = 0x03E,
  SYSALS__ANALOGUE_GAIN                 = 0x03F,
  SYSALS__INTEGRATION_PERIOD            = 0x040,

  RESULT__RANGE_STATUS                  = 0x04D,
  RESULT__ALS_STATUS                    = 0x04E,
  RESULT__INTERRUPT_STATUS_GPIO         = 0x04F,
  RESULT__ALS_VAL                       = 0x050, // 16-bit
  RESULT__HISTORY_BUFFER_0              = 0x052, // 16-bit
  RESULT__HISTORY_BUFFER_1              = 0x054, // 16-bit
  RESULT__HISTORY_BUFFER_2              = 0x056, // 16-bit
  RESULT__HISTORY_BUFFER_3              = 0x058, // 16-bit
  RESULT__HISTORY_BUFFER_4              = 0x05A, // 16-bit
  RESULT__HISTORY_BUFFER_5              = 0x05C, // 16-bit
  RESULT__HISTORY_BUFFER_6              = 0x05E, // 16-bit
  RESULT__HISTORY_BUFFER_7              = 0x060, // 16-bit
  RESULT__RANGE_VAL                     = 0x062,
  RESULT__RANGE_RAW                     = 0x064,
  RESULT__RANGE_RETURN_RATE             = 0x066, // 16-bit
  RESULT__RANGE_REFERENCE_RATE          = 0x068, // 16-bit
  RESULT__RANGE_RETURN_SIGNAL_COUNT     = 0x06C, // 32-bit
  RESULT__RANGE_REFERENCE_SIGNAL_COUNT  = 0x070, // 32-bit
  RESULT__RANGE_RETURN_AMB_COUNT        = 0x074, // 32-bit
  RESULT__RANGE_REFERENCE_AMB_COUNT     = 0x078, // 32-bit
  RESULT__RANGE_RETURN_CONV_TIME        = 0x07C, // 32-bit
  RESULT__RANGE_REFERENCE_CONV_TIME     = 0x080, // 32-bit

  READOUT__AVERAGING_SAMPLE_PERIOD      = 0x10A,
  FIRMWARE__BOOTUP                      = 0x119,
  FIRMWARE__RESULT_SCALER               = 0x120,
  I2C_SLAVE__DEVICE_ADDRESS             = 0x212,
  INTERLEAVED_MODE__ENABLE              = 0x2A3,
};

#define VL6180X_REG_IDENTIFICATION_MODEL_ID       0x000
#define VL6180X_REG_SYSTEM_INTERRUPT_CONFIG       0x014
#define VL6180X_REG_SYSTEM_INTERRUPT_CLEAR        0x015
#define VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET     0x016
#define VL6180X_REG_SYSRANGE_START                0x018
#define VL6180X_REG_SYSALS_START                  0x038
#define VL6180X_REG_SYSALS_ANALOGUE_GAIN          0x03F
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_HI  0x040
#define VL6180X_REG_SYSALS_INTEGRATION_PERIOD_LO  0x041
#define VL6180X_REG_RESULT_ALS_VAL                0x050
#define VL6180X_REG_RESULT_RANGE_VAL              0x062
#define VL6180X_REG_RESULT_RANGE_STATUS           0x04d
#define VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO  0x04f


/* ALS gain constants */
typedef enum {
  VL6180X_ALS_GAIN_1 =        0x06,
  VL6180X_ALS_GAIN_1_25 =     0x05,
  VL6180X_ALS_GAIN_1_67 =     0x04,
  VL6180X_ALS_GAIN_2_5  =     0x03,
  VL6180X_ALS_GAIN_5    =     0x02,
  VL6180X_ALS_GAIN_10   =     0x01,
  VL6180X_ALS_GAIN_20   =     0x00,
  VL6180X_ALS_GAIN_40   =     0x07,
} VL6180X_ALS_GAIN;

typedef enum {
  VL_ON_ERROR_INIT,
  VL_ON_ERROR_WRONG_DEVICE,
  VL_ON_ERROR_CONFIGURE_DEFAULT,
  VL_ON_ERROR_ENABLE_FAULT,
  VL_ON_ERROR_INIT_DEVICE,
  VL_ON_ERROR_ENABLE_DEVICE,
  VL_ON_ERROR_SET_I2C_ADDRESS,
} VL_Enum_Error;

uint8_t VL_WriteReg8(uint8_t i2cDeviceAddress, uint16_t reg, uint8_t val);

uint8_t VL_WriteReg16(uint8_t i2cDeviceAddress, uint16_t reg, uint16_t val);

uint8_t VL_ReadReg8(uint8_t i2cDeviceAddress, uint16_t reg, uint8_t *valP);

uint8_t VL_ReadReg16(uint8_t i2cDeviceAddress, uint16_t reg, uint16_t *valP);

uint8_t VL6180X_readLux(uint8_t i2cDeviceAddress, VL6180X_ALS_GAIN gain, float *pLux);

uint8_t VL_ReadRangeSingle(uint8_t i2cDeviceAddress, int16_t *rangeP);
uint8_t VL_ReadAmbientSingle(uint8_t i2cDeviceAddress, uint16_t *ambientP);

uint8_t VL_ChipEnable(uint8_t deviceNo, bool on);
uint8_t VL_SetI2CDeviceAddress(uint8_t deviceNo, uint8_t i2cDeviceAddress);

uint8_t VL_InitDevice(uint8_t i2cDeviceAddress);
uint8_t VL_ConfigureDefault(uint8_t i2cDeviceAddress);

uint8_t VL_InitAndConfigureDevice(uint8_t i2cDeviceAddress);
uint8_t VL_Init(void);

#endif /* SOURCES_VL53L0X_H_ */
