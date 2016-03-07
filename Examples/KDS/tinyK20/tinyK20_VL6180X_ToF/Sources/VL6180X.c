/*
 * VL6180X.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "VL6180X.h"
#include "GI2C1.h"
#include "WAIT1.h"

#define VL6180X_I2C_ADDRESS 0x29 /* 0101001b (shifted on the bus it is 0101001x */
static const uint8_t deviceI2CAddress = VL6180X_I2C_ADDRESS;

void VL_OnError(VL_Enum_Error error) {
}

uint8_t VL_WriteReg8(uint16_t reg, uint8_t val) {
  uint8_t r[2];
  uint8_t res;

  r[0] = reg>>8;
  r[1] = reg&0xff;
  res = GI2C1_WriteAddress(deviceI2CAddress, &r[0], sizeof(r), &val, sizeof(val));
  return res;
}

uint8_t VL_WriteReg16(uint16_t reg, uint16_t val) {
  uint8_t r[2], v[2];
  uint8_t res;

  r[0] = reg>>8;
  r[1] = reg&0xff;
  v[0] = val>>8;
  v[1] = val&0xff;
  res = GI2C1_WriteAddress(deviceI2CAddress, &r[0], sizeof(r), &v[0], sizeof(v));
  return res;
}

uint8_t VL_ReadReg8(uint16_t reg, uint8_t *valP) {
  uint8_t tmp[2];
  uint8_t res;

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  res = GI2C1_ReadAddress(deviceI2CAddress, &tmp[0], sizeof(tmp), valP, 1);
  return res;
}

uint8_t VL_ReadReg16(uint16_t reg, uint16_t *valP) {
  uint8_t tmp[2];
  uint8_t res;

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  res = GI2C1_ReadAddress(deviceI2CAddress, &tmp[0], sizeof(tmp), (uint8_t*)valP, 2);
  return res;
}

static uint8_t readRangeContinuous(uint8_t *valP) {
  uint8_t range;
  uint8_t res, val;
  uint16_t timeoutMs = 100;

  *valP = 0; /* init */
  do { /* breaks */
   res = VL_ReadReg8(RESULT__INTERRUPT_STATUS_GPIO, &val);
   if (res!=ERR_OK) {
     break;
   }
   if ((val&0x4)!=0) {
     break; /* 4: New Sample Ready threshold event */
   }
   if (timeoutMs==0) { /* timeout */
     break;
   }
   WAIT1_Waitms(1);
   timeoutMs--;
  } while(1);
  if (timeoutMs==0) {
    return ERR_NOTAVAIL; /* timeout */
  }

  res = VL_ReadReg8(RESULT__RANGE_VAL, &range); /* read range in millimeters */
  if (res!=ERR_OK) {
    return res;
  }
  res = VL_WriteReg8(SYSTEM__INTERRUPT_CLEAR, 0x01); /* clear interrupt flag */
  if (res!=ERR_OK) {
    return res;
  }

  *valP = range;
  return ERR_OK;
}

static uint8_t readAmbientContinuous(uint16_t *valP) {
  uint16_t ambient;
  uint8_t res, val;
  uint16_t timeoutMs = 100;

  *valP = 0; /* init */
  do {
   res = VL_ReadReg8(RESULT__INTERRUPT_STATUS_GPIO, &val);
   if (res!=ERR_OK) {
     break;
   }
   if ((val&0x20)!=0) {
     break; /* 4: New Sample Ready threshold event */
   }
   if (timeoutMs==0) { /* timeout */
     break;
   }
   WAIT1_Waitms(1);
   timeoutMs--;
  } while(1);
  if (timeoutMs==0) {
    return ERR_NOTAVAIL; /* timeout */
  }

  res = VL_ReadReg16(RESULT__ALS_VAL, &ambient); /* read ambient value */
  if (res!=ERR_OK) {
    return res;
  }
  res = VL_WriteReg8(SYSTEM__INTERRUPT_CLEAR, 0x02); /* clear interrupt flag */
  if (res!=ERR_OK) {
    return res;
  }

  *valP = ambient;
  return ERR_OK;
}


uint8_t VL_ReadRangeSingle(uint8_t *rangeP) {
  VL_WriteReg8(SYSRANGE__START, 0x01);
  return readRangeContinuous(rangeP);
}

uint8_t VL_ReadAmbientSingle(uint16_t *ambientP) {
  VL_WriteReg8(SYSALS__START, 0x01);
  return readAmbientContinuous(ambientP);
}

// Configure some settings for the sensor's default behavior from AN4545 -
// "Recommended : Public registers" and "Optional: Public registers"
uint8_t VL_ConfigureDefault(void) {
  // "Recommended : Public registers"

  // readout__averaging_sample_period = 48
  VL_WriteReg8(READOUT__AVERAGING_SAMPLE_PERIOD, 0x30);

  // sysals__analogue_gain_light = 6 (ALS gain = 1 nominal, actually 1.01 according to Table 14 in datasheet)
  VL_WriteReg8(SYSALS__ANALOGUE_GAIN, 0x46);

  // sysrange__vhv_repeat_rate = 255 (auto Very High Voltage temperature recalibration after every 255 range measurements)
  VL_WriteReg8(SYSRANGE__VHV_REPEAT_RATE, 0xFF);

  // sysals__integration_period = 99 (100 ms)
  // AN4545 incorrectly recommends writing to register 0x040; 0x63 should go in the lower byte, which is register 0x041.
  VL_WriteReg16(SYSALS__INTEGRATION_PERIOD, 0x0063);

  // sysrange__vhv_recalibrate = 1 (manually trigger a VHV recalibration)
  VL_WriteReg8(SYSRANGE__VHV_RECALIBRATE, 0x01);

  // "Optional: Public registers"

  // sysrange__intermeasurement_period = 9 (100 ms)
  VL_WriteReg8(SYSRANGE__INTERMEASUREMENT_PERIOD, 0x09);

  // sysals__intermeasurement_period = 49 (500 ms)
  VL_WriteReg8(SYSALS__INTERMEASUREMENT_PERIOD, 0x31);

  // als_int_mode = 4 (ALS new sample ready interrupt); range_int_mode = 4 (range new sample ready interrupt)
  VL_WriteReg8(SYSTEM__INTERRUPT_CONFIG_GPIO, 0x24);
}

/* Initialize sensor with settings from ST application note AN4545, section 9 -
   "Mandatory : private registers" */
uint8_t VL_InitDevice(void) {
  (void)VL_WriteReg8(0x207, 0x01);
  (void)VL_WriteReg8(0x208, 0x01);
  (void)VL_WriteReg8(0x096, 0x00);
  (void)VL_WriteReg8(0x097, 0xFD);
  (void)VL_WriteReg8(0x0E3, 0x00);
  (void)VL_WriteReg8(0x0E4, 0x04);
  (void)VL_WriteReg8(0x0E5, 0x02);
  (void)VL_WriteReg8(0x0E6, 0x01);
  (void)VL_WriteReg8(0x0E7, 0x03);
  (void)VL_WriteReg8(0x0F5, 0x02);
  (void)VL_WriteReg8(0x0D9, 0x05);
  (void)VL_WriteReg8(0x0DB, 0xCE);
  (void)VL_WriteReg8(0x0DC, 0x03);
  (void)VL_WriteReg8(0x0DD, 0xF8);
  (void)VL_WriteReg8(0x09F, 0x00);
  (void)VL_WriteReg8(0x0A3, 0x3C);
  (void)VL_WriteReg8(0x0B7, 0x00);
  (void)VL_WriteReg8(0x0BB, 0x3C);
  (void)VL_WriteReg8(0x0B2, 0x09);
  (void)VL_WriteReg8(0x0CA, 0x09);
  (void)VL_WriteReg8(0x198, 0x01);
  (void)VL_WriteReg8(0x1B0, 0x17);
  (void)VL_WriteReg8(0x1AD, 0x00);
  (void)VL_WriteReg8(0x0FF, 0x05);
  (void)VL_WriteReg8(0x100, 0x05);
  (void)VL_WriteReg8(0x199, 0x05);
  (void)VL_WriteReg8(0x1A6, 0x1B);
  (void)VL_WriteReg8(0x1AC, 0x3E);
  (void)VL_WriteReg8(0x1A7, 0x1F);
  (void)VL_WriteReg8(0x030, 0x00);
  return ERR_OK;
}

uint8_t VL_Init(void) {
  uint8_t res;

  res = VL_InitDevice();
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT);
    return res;
  }
  res = VL_ConfigureDefault();
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_CONFIGURE_DEFAULT);
    return res;
  }
  return res;
}

