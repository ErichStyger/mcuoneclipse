/**
 * \file
 * \brief Interface to the STMicroelectronics VL6180X ToF (Time-of-Flight) sensor.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a driver for the VL6180X sensor.
 * Sensor tested: https://www.pololu.com/product/2489
 */

#ifndef SOURCES_VL6180X_H_
#define SOURCES_VL6180X_H_

#include "PE_Types.h" /* bool, uint8_t, ... */

/* configuration */
#define VL6180X_CONFIG_MULTIPLE_DEVICES   1  /* 1: Multiple devices on the same bus; 0: single device on the bus */
#define VL6180X_CONFIG_SUPPORT_SCALING    1  /* 1: Support range scaling (20, 40 and 60 cm); 0: no range scaling */

/* scaling values */
#define VL6180X_SCALING_FACTOR_1      1 /* 0-20 cm */
#define VL6180X_SCALING_FACTOR_2      2 /* 0-40 cm */
#define VL6180X_SCALING_FACTOR_3      3 /* 0-60 cm */
#define VL6180X_SCALING_DEFAULT       VL6180X_SCALING_FACTOR_1

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

  RANGE_SCALER = 0x096, // 16-bit - see STSW-IMG003 core/inc/vl6180x_def.h

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
  VL6180X_ON_ERROR_INIT,
  VL6180X_ON_ERROR_CONFIGURE_DEFAULT,
  VL6180X_ON_ERROR_ENABLE_FAULT,
  VL6180X_ON_ERROR_INIT_DEVICE,
  VL6180X_ON_ERROR_ENABLE_DEVICE,
  VL6180X_ON_ERROR_SET_I2C_ADDRESS,
} VL6180X_Enum_Error;

typedef enum {
  VL6180X_PIN_ACTION_SET_INPUT, /* configure pin as input pin */
  VL6180X_PIN_ACTION_SET_OUTPUT, /* configure pin as output pin */
  VL6180X_PIN_ACTION_SET_LOW, /* drive output pin low */
  VL6180X_PIN_ACTION_SET_HIGH /* drive output pin high */
} VL6180X_PIN_ACTION;

typedef struct {
  uint8_t deviceAddr; /* device address, default would be VL6180X_DEFAULT_I2C_ADDRESS */
#if VL6180X_CONFIG_SUPPORT_SCALING
  uint8_t scale; /* scaling factor: 1, 2 or 3 */
  uint8_t ptp_offset; /* SYSRANGE__PART_TO_PART_RANGE_OFFSET */
#endif
#if VL6180X_CONFIG_MULTIPLE_DEVICES
  void (*pinAction)(VL6180X_PIN_ACTION action); /* callback to perform pin actions */
#endif
} VL6180X_Device;

#if VL6180X_CONFIG_SUPPORT_SCALING
  uint8_t VL6180X_setScaling(VL6180X_Device *device, uint8_t new_scaling);
#endif

extern const VL6180X_Device VL6180X_DefaultDevice; /* default device with default address */

uint8_t VL6180X_WriteReg8(VL6180X_Device *device, uint16_t reg, uint8_t val);

uint8_t VL6180X_WriteReg16(VL6180X_Device *device, uint16_t reg, uint16_t val);

uint8_t VL6180X_ReadReg8(VL6180X_Device *device, uint16_t reg, uint8_t *valP);

uint8_t VL6180X_ReadReg16(VL6180X_Device *device, uint16_t reg, uint16_t *valP);

uint8_t VL6180X_readLux(VL6180X_Device *device, VL6180X_ALS_GAIN gain, float *pLux);

uint8_t VL6180X_ReadRangeSingle(VL6180X_Device *device, int16_t *rangeP);
uint8_t VL6180X_ReadRangeSingleMultiple(VL6180X_Device *device, int16_t *rangeP, uint32_t nofDevices);
uint8_t VL6180X_ReadAmbientSingle(VL6180X_Device *device, uint16_t *ambientP);

uint8_t VL6180X_ChipEnable(VL6180X_Device *device, bool on);

/*!
 * \brief Configures the device I2C address
 * \param device Pointer to device to be configured.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t VL6180X_SetI2CDeviceAddress(VL6180X_Device *device);

/*!
 * \brief Initializes the device and configures the registers according to the STM application note.
 * \param device Pointer to device to be configured.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t VL6180X_InitAndConfigureDevice(VL6180X_Device *device);

/*!
 * \brief Driver de-initalization
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t VL6180X_Deinit(void);

/*!
 * \brief Driver initalization
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t VL6180X_Init(void);

#endif /* SOURCES_VL6180X_H_ */
