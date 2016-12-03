/*
 * VL6180X.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "VL6180X.h"
#include "GI2C1.h"
#include "WAIT1.h"
#if VL_MULTIPLE_DEVICES>=1
  #include "TofCE1.h" /* CE of ToF 1, low active */
#endif
#if VL_MULTIPLE_DEVICES>=2
  #include "TofCE2.h" /* CE of ToF 2, low active */
#endif
#if VL_MULTIPLE_DEVICES>=3
  #include "TofCE3.h" /* CE of ToF 3, low active */
#endif
#if VL_MULTIPLE_DEVICES>=4
  #include "TofCE4.h" /* CE of ToF 4, low active */
#endif

static void VL_OnError(VL_Enum_Error error) {
  /* generic error hook */
}

uint8_t VL_WriteReg8(uint8_t i2cDeviceAddress, uint16_t reg, uint8_t val) {
  uint8_t r[2];
  uint8_t res;

  r[0] = reg>>8;
  r[1] = reg&0xff;
  res = GI2C1_WriteAddress(i2cDeviceAddress, &r[0], sizeof(r), &val, sizeof(val));
  return res;
}

uint8_t VL_WriteReg16(uint8_t i2cDeviceAddress, uint16_t reg, uint16_t val) {
  uint8_t r[2], v[2];
  uint8_t res;

  r[0] = reg>>8;
  r[1] = reg&0xff;
  v[0] = val>>8;
  v[1] = val&0xff;
  res = GI2C1_WriteAddress(i2cDeviceAddress, &r[0], sizeof(r), &v[0], sizeof(v));
  return res;
}

uint8_t VL_ReadReg8(uint8_t i2cDeviceAddress, uint16_t reg, uint8_t *valP) {
  uint8_t tmp[2];
  uint8_t res;

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  res = GI2C1_ReadAddress(i2cDeviceAddress, &tmp[0], sizeof(tmp), valP, 1);
  return res;
}

uint8_t VL_ReadReg16(uint8_t i2cDeviceAddress, uint16_t reg, uint16_t *valP) {
  uint8_t tmp[2];
  uint8_t res;

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  res = GI2C1_ReadAddress(i2cDeviceAddress, &tmp[0], sizeof(tmp), (uint8_t*)valP, 2);
  return res;
}

static uint8_t readRangeContinuous(uint8_t i2cDeviceAddress, uint8_t *valP) {
  uint8_t range;
  uint8_t res, val;
  uint16_t timeoutMs = 100;

  *valP = 0; /* init */
  do { /* breaks */
   res = VL_ReadReg8(i2cDeviceAddress, RESULT__INTERRUPT_STATUS_GPIO, &val);
   if (res!=ERR_OK) {
     break;
   }
   if ((val&0x4)!=0) {
     break; /* 4: New Sample Ready threshold event */
   }
   if (timeoutMs==0) { /* timeout */
     break;
   }
   WAIT1_WaitOSms(1);
   timeoutMs--;
  } while(1);
  if (timeoutMs==0) {
    return ERR_NOTAVAIL; /* timeout */
  }

  res = VL_ReadReg8(i2cDeviceAddress, RESULT__RANGE_VAL, &range); /* read range in millimeters */
  if (res!=ERR_OK) {
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, SYSTEM__INTERRUPT_CLEAR, 0x01); /* clear interrupt flag */
  if (res!=ERR_OK) {
    return res;
  }
  *valP = range;
  return ERR_OK;
}

static uint8_t readAmbientContinuous(uint8_t i2cDeviceAddress, uint16_t *valP) {
  uint16_t ambient;
  uint8_t res, val;
  uint16_t timeoutMs = 100;

  *valP = 0; /* init */
  do {
   res = VL_ReadReg8(i2cDeviceAddress, RESULT__INTERRUPT_STATUS_GPIO, &val);
   if (res!=ERR_OK) {
     break;
   }
   if ((val&0x20)!=0) {
     break; /* new value available */
   }
   if (timeoutMs==0) { /* timeout */
     break;
   }
   WAIT1_WaitOSms(1);
   timeoutMs--;
  } while(1);
  if (timeoutMs==0) {
    return ERR_NOTAVAIL; /* timeout */
  }

  res = VL_ReadReg16(i2cDeviceAddress, RESULT__ALS_VAL, &ambient); /* read ambient value */
  if (res!=ERR_OK) {
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, SYSTEM__INTERRUPT_CLEAR, 0x02); /* clear interrupt flag */
  if (res!=ERR_OK) {
    return res;
  }

  *valP = ambient;
  return ERR_OK;
}

uint8_t VL_ReadRangeSingle(uint8_t i2cDeviceAddress, int16_t *rangeP) {
  uint8_t res;
  uint8_t val;

  VL_WriteReg8(i2cDeviceAddress, SYSRANGE__START, 0x01);
  res = readRangeContinuous(i2cDeviceAddress, &val);
  if (res!=ERR_OK) {
    *rangeP = -1;
    return res; /* error */
  }
  if (val>=0 && val<=255) {
    *rangeP = val; /* store value */
    return ERR_OK;
  }
  *rangeP = -2; /* error */
  return ERR_FAILED;
}

uint8_t VL_ReadAmbientSingle(uint8_t i2cDeviceAddress, uint16_t *ambientP) {
  VL_WriteReg8(i2cDeviceAddress, SYSALS__START, 0x01);
  return readAmbientContinuous(i2cDeviceAddress, ambientP);
}

// Configure some settings for the sensor's default behavior from AN4545 -
// "Recommended : Public registers" and "Optional: Public registers"
uint8_t VL_ConfigureDefault(uint8_t i2cDeviceAddress) {
  // "Recommended : Public registers"

  // readout__averaging_sample_period = 48
  VL_WriteReg8(i2cDeviceAddress, READOUT__AVERAGING_SAMPLE_PERIOD, 0x30);

  // sysals__analogue_gain_light = 6 (ALS gain = 1 nominal, actually 1.01 according to Table 14 in datasheet)
  VL_WriteReg8(i2cDeviceAddress, SYSALS__ANALOGUE_GAIN, 0x46);

  // sysrange__vhv_repeat_rate = 255 (auto Very High Voltage temperature recalibration after every 255 range measurements)
  VL_WriteReg8(i2cDeviceAddress, SYSRANGE__VHV_REPEAT_RATE, 0xFF);

  // sysals__integration_period = 99 (100 ms)
  // AN4545 incorrectly recommends writing to register 0x040; 0x63 should go in the lower byte, which is register 0x041.
  VL_WriteReg16(i2cDeviceAddress, SYSALS__INTEGRATION_PERIOD, 0x0063);

  // sysrange__vhv_recalibrate = 1 (manually trigger a VHV recalibration)
  VL_WriteReg8(i2cDeviceAddress, SYSRANGE__VHV_RECALIBRATE, 0x01);

  // "Optional: Public registers"

  // sysrange__intermeasurement_period = 9 (100 ms)
  VL_WriteReg8(i2cDeviceAddress, SYSRANGE__INTERMEASUREMENT_PERIOD, 0x09);

  // sysals__intermeasurement_period = 49 (500 ms)
  VL_WriteReg8(i2cDeviceAddress, SYSALS__INTERMEASUREMENT_PERIOD, 0x31);

  // als_int_mode = 4 (ALS new sample ready interrupt); range_int_mode = 4 (range new sample ready interrupt)
  VL_WriteReg8(i2cDeviceAddress, SYSTEM__INTERRUPT_CONFIG_GPIO, 0x24);
}

/* Initialize sensor with settings from ST application note AN4545, section 9 -
   "Mandatory : private registers" */
uint8_t VL_InitDevice(uint8_t i2cDeviceAddress) {
  uint8_t res;

  res = VL_WriteReg8(i2cDeviceAddress, 0x207, 0x01);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x208, 0x01);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x096, 0x00);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x097, 0xFD);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0E3, 0x00);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0E4, 0x04);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0E5, 0x02);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0E6, 0x01);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0E7, 0x03);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0F5, 0x02);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0D9, 0x05);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0DB, 0xCE);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0DC, 0x03);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0DD, 0xF8);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x09F, 0x00);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0A3, 0x3C);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0B7, 0x00);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0BB, 0x3C);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0B2, 0x09);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0CA, 0x09);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x198, 0x01);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x1B0, 0x17);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x1AD, 0x00);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x0FF, 0x05);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x100, 0x05);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x199, 0x05);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x1A6, 0x1B);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x1AC, 0x3E);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x1A7, 0x1F);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, 0x030, 0x00);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_INIT_DEVICE);
    return res;
  }
  return ERR_OK;
}

uint8_t VL_InitAndConfigureDevice(uint8_t i2cDeviceAddress) {
  uint8_t res;

  res = VL_InitDevice(i2cDeviceAddress);
  if (res!=ERR_OK) {
    return res;
  }
  res = VL_ConfigureDefault(i2cDeviceAddress);
  if (res!=ERR_OK) {
    return res;
  }
  return res;
}

uint8_t VL_ChipEnable(uint8_t deviceNo, bool on) {
#if VL_MULTIPLE_DEVICES>0
#if VL_MULTIPLE_DEVICES>=1
  if (deviceNo==0) {
    if (on) {
      TofCE1_SetInput(); /* let it pull high by the pull-up on the board */
    } else { /* pull it down */
      TofCE1_ClrVal();
      TofCE1_SetOutput();
    }
#endif
#if VL_MULTIPLE_DEVICES>=2
  } else if (deviceNo==1) {
      if (on) {
        TofCE2_SetInput(); /* let it pull high by the pull-up on the board */
      } else { /* pull it down */
        TofCE2_ClrVal();
        TofCE2_SetOutput();
      }
#endif
#if VL_MULTIPLE_DEVICES>=3
  } else if (deviceNo==2) {
      if (on) {
        TofCE3_SetInput(); /* let it pull high by the pull-up on the board */
      } else { /* pull it down */
        TofCE3_ClrVal();
        TofCE3_SetOutput();
      }
#endif
#if VL_MULTIPLE_DEVICES>=4
  } else if (deviceNo==3) {
      if (on) {
        TofCE4_SetInput(); /* let it pull high by the pull-up on the board */
      } else { /* pull it down */
        TofCE4_ClrVal();
        TofCE4_SetOutput();
      }
#endif
  } else {
    VL_OnError(VL_ON_ERROR_WRONG_DEVICE);
    return ERR_FAILED; /* wrong device number */
  }
#endif
  return ERR_OK;
}

uint8_t VL_SetI2CDeviceAddress(uint8_t deviceNo, uint8_t i2cDeviceAddress) {
  uint8_t res;
  uint8_t val;
  int i;

  if (deviceNo>=VL_MULTIPLE_DEVICES) {
    VL_OnError(VL_ON_ERROR_WRONG_DEVICE);
    return ERR_FAILED;
  }
  i2cDeviceAddress &= 0x7F; /* make sure it is 7bits only */
  /* test: check if the device is already configured */
  res = VL_ReadReg8(i2cDeviceAddress, I2C_SLAVE__DEVICE_ADDRESS, &val);
  if (res==ERR_OK || val == i2cDeviceAddress) {
    /* already configured :-) */
    return ERR_OK;
  }
  /* device just has been powered on: it shall be accessible using the default address */
  res = VL_WriteReg8(VL6180X_DEFAULT_I2C_ADDRESS, I2C_SLAVE__DEVICE_ADDRESS, i2cDeviceAddress);
  if (res!=ERR_OK) {
    VL_OnError(VL_ON_ERROR_SET_I2C_ADDRESS);
    return ERR_FAILED;
  }
  /* test: read back with new address */
  res = VL_ReadReg8(i2cDeviceAddress, I2C_SLAVE__DEVICE_ADDRESS, &val);
  if (res!=ERR_OK || val != i2cDeviceAddress) {
    VL_OnError(VL_ON_ERROR_SET_I2C_ADDRESS);
    return ERR_FAILED;
  }
  /* device is accessible with the new address now */
  return ERR_OK;
}

uint8_t VL_Init(void) {
  /* use VL_InitDevice() from a task with interrupts enabled */
}
