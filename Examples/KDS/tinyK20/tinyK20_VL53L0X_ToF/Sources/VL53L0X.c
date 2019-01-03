/*
 * VL53L0X.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "VL53L0X.h"
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

// RANGE_SCALER values for 1x, 2x, 3x scaling - see STSW-IMG003 core/src/vl6180x_api.c (ScalerLookUP[])
static uint16_t const ScalerValues[] = {0, 253, 127, 84};
static uint8_t scaling = 1;


static void VL_OnError(VL_Enum_Error error) {
  /* generic error hook */
}

uint8_t VL_WriteReg8(uint8_t i2cDeviceAddress, uint16_t reg, uint8_t val) {
  uint8_t r[2];

  r[0] = reg>>8;
  r[1] = reg&0xff;
  return GI2C1_WriteAddress(i2cDeviceAddress, &r[0], sizeof(r), &val, sizeof(val));
}

uint8_t VL_WriteReg16(uint8_t i2cDeviceAddress, uint16_t reg, uint16_t val) {
  uint8_t r[2], v[2];

  r[0] = reg>>8;
  r[1] = reg&0xff;
  v[0] = val>>8;
  v[1] = val&0xff;
  return GI2C1_WriteAddress(i2cDeviceAddress, &r[0], sizeof(r), &v[0], sizeof(v));
}

uint8_t VL_ReadReg8(uint8_t i2cDeviceAddress, uint16_t reg, uint8_t *valP) {
  uint8_t tmp[2];

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  return GI2C1_ReadAddress(i2cDeviceAddress, &tmp[0], sizeof(tmp), valP, 1);
}

uint8_t VL_ReadReg16(uint8_t i2cDeviceAddress, uint16_t reg, uint16_t *valP) {
  uint8_t tmp[2];

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  return GI2C1_ReadAddress(i2cDeviceAddress, &tmp[0], sizeof(tmp), (uint8_t*)valP, 2);
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
  //WAIT1_WaitOSms(8); /* logic analyzer shows it takes around 9 ms until the data is ready */
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

uint8_t VL6180X_readLux(uint8_t i2cDeviceAddress, VL6180X_ALS_GAIN gain, float *pLux) {
  uint8_t reg;
  uint16_t reg16;
  uint8_t res;
  float lux;

  *pLux = 0.0; /* init */
  res = VL_ReadReg8(i2cDeviceAddress, VL6180X_REG_SYSTEM_INTERRUPT_CONFIG, &reg);
  if (res!=ERR_OK) {
    return res;
  }
  reg &= ~0x38;
  reg |= (0x4 << 3); /* IRQ on ALS ready */
  res = VL_WriteReg8(i2cDeviceAddress, VL6180X_REG_SYSTEM_INTERRUPT_CONFIG, reg);
  if (res!=ERR_OK) {
    return res;
  }

  /* 100 ms integration period */
  res = VL_WriteReg8(i2cDeviceAddress, VL6180X_REG_SYSALS_INTEGRATION_PERIOD_HI, 0);
  if (res!=ERR_OK) {
    return res;
  }
  res = VL_WriteReg8(i2cDeviceAddress, VL6180X_REG_SYSALS_INTEGRATION_PERIOD_LO, 100);
  if (res!=ERR_OK) {
    return res;
  }

  /* analog gain */
  if (gain > VL6180X_ALS_GAIN_40) {
    gain = VL6180X_ALS_GAIN_40;
  }
  res = VL_WriteReg8(i2cDeviceAddress, VL6180X_REG_SYSALS_ANALOGUE_GAIN, 0x40 | gain);
  if (res!=ERR_OK) {
    return res;
  }

  /* start ALS */
  res = VL_WriteReg8(i2cDeviceAddress, VL6180X_REG_SYSALS_START, 0x1);
  if (res!=ERR_OK) {
    return res;
  }

  /* Poll until "New Sample Ready threshold event" is set */
  do {
    res = VL_ReadReg8(i2cDeviceAddress, VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO, &reg);
    if (((reg>>3)&0x7)==4) {
      break; /* new result ready */
    }
    /* \todo add proper timeout handling */
  } while(1);

  /* read lux */
  res = VL_ReadReg16(i2cDeviceAddress, VL6180X_REG_RESULT_ALS_VAL, &reg16);
  if (res!=ERR_OK) {
    return res;
  }
  lux = reg16;

  /* clear interrupt */
  res = VL_WriteReg8(i2cDeviceAddress, VL6180X_REG_SYSTEM_INTERRUPT_CLEAR, 0x07);

  lux *= 0.32; // calibrated count/lux
  switch(gain) {
    case VL6180X_ALS_GAIN_1:
      break;
    case VL6180X_ALS_GAIN_1_25:
      lux /= 1.25;
      break;
    case VL6180X_ALS_GAIN_1_67:
      lux /= 1.76;
      break;
    case VL6180X_ALS_GAIN_2_5:
      lux /= 2.5;
      break;
    case VL6180X_ALS_GAIN_5:
      lux /= 5;
      break;
    case VL6180X_ALS_GAIN_10:
      lux /= 10;
      break;
    case VL6180X_ALS_GAIN_20:
      lux /= 20;
      break;
    case VL6180X_ALS_GAIN_40:
      lux /= 20;
      break;
    default:
      break;
  }
  lux *= 100;
  lux /= 100; // integration time in ms
  *pLux = lux;
  return ERR_OK;
}

#if 0
// Set range scaling factor. The sensor uses 1x scaling by default, giving range
// measurements in units of mm. Increasing the scaling to 2x or 3x makes it give
// raw values in units of 2 mm or 3 mm instead. In other words, a bigger scaling
// factor increases the sensor's potential maximum range but reduces its
// resolution.

// Implemented using ST's VL6180X API as a reference (STSW-IMG003); see
// VL6180x_UpscaleSetScaling() in vl6180x_api.c.
void VL6180X::setScaling(uint8_t new_scaling)
{
  uint8_t const DefaultCrosstalkValidHeight = 20; // default value of SYSRANGE__CROSSTALK_VALID_HEIGHT

  // do nothing if scaling value is invalid
  if (new_scaling < 1 || new_scaling > 3) { return; }

  scaling = new_scaling;
  writeReg16Bit(RANGE_SCALER, ScalerValues[scaling]);

  // apply scaling on part-to-part offset
  writeReg(VL6180X::SYSRANGE__PART_TO_PART_RANGE_OFFSET, ptp_offset / scaling);

  // apply scaling on CrossTalkValidHeight
  writeReg(VL6180X::SYSRANGE__CROSSTALK_VALID_HEIGHT, DefaultCrosstalkValidHeight / scaling);

  // This function does not apply scaling to RANGE_IGNORE_VALID_HEIGHT.

  // enable early convergence estimate only at 1x scaling
  uint8_t rce = readReg(VL6180X::SYSRANGE__RANGE_CHECK_ENABLES);
  writeReg(VL6180X::SYSRANGE__RANGE_CHECK_ENABLES, (rce & 0xFE) | (scaling == 1));
}
#endif


// Configure some settings for the sensor's default behavior from AN4545 -
// "Recommended : Public registers" and "Optional: Public registers"
uint8_t VL_ConfigureDefault(uint8_t i2cDeviceAddress) {
  // "Recommended : Public registers"

  /* Set the averaging sample period (compromise between lower noise and increased execution time) */
  VL_WriteReg8(i2cDeviceAddress, READOUT__AVERAGING_SAMPLE_PERIOD, 0x30);

  /* sysals__analogue_gain_light = 6 (ALS gain = 1 nominal, actually 1.01 according to Table 14 in datasheet)
   * Sets the light and dark gain (upper nibble). Dark gain should not be changed.  */
  VL_WriteReg8(i2cDeviceAddress, SYSALS__ANALOGUE_GAIN, 0x46);

  // sysrange__vhv_repeat_rate = 255 (auto Very High Voltage temperature recalibration after every 255 range measurements)
  /* sets the # of range measurements after which auto calibration of system is which auto calibration of system is performed */
  VL_WriteReg8(i2cDeviceAddress, SYSRANGE__VHV_REPEAT_RATE, 0xFF);

  /* sysals__integration_period = 99 (100 ms) */
  /* AN4545 incorrectly recommends writing to register 0x040; 0x63 should go in the lower byte, which is register 0x041. */
  /* Set ALS integration time to 100ms */
  VL_WriteReg16(i2cDeviceAddress, SYSALS__INTEGRATION_PERIOD, 0x0063);

  /* sysrange__vhv_recalibrate = 1 (manually trigger a VHV recalibration) */
  /* perform a single temperature calibration of the ranging sensor */
  VL_WriteReg8(i2cDeviceAddress, SYSRANGE__VHV_RECALIBRATE, 0x01);

  /* Optional: Public registers, see data sheet for more detail */
  /* Set default ranging inter-measurement period to 100ms */
  VL_WriteReg8(i2cDeviceAddress, SYSRANGE__INTERMEASUREMENT_PERIOD, 0x09);

  /* Set default ALS inter-measurement period to 500ms */
  VL_WriteReg8(i2cDeviceAddress, SYSALS__INTERMEASUREMENT_PERIOD, 0x31);

  /* Configures interrupt on 'New Sample Ready threshold event' */
  VL_WriteReg8(i2cDeviceAddress, SYSTEM__INTERRUPT_CONFIG_GPIO, 0x24);

  scaling = 1;
  return ERR_OK;
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
  res = VL_WriteReg8(i2cDeviceAddress, 0x097, 0xFD); /* RANGE_SCALER = 253 */
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
