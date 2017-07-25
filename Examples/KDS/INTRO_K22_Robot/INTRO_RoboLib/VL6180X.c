/**
 * \file
 * \brief Implementation of a driver for the STMicroelectronics VL6180X ToF (Time-of-Flight) sensor.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a driver for the VL6180X sensor.
 */

#include "Platform.h"
#if PL_HAS_TOF_SENSOR
#include "VL6180X.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "TofPwr.h" /* FET on PTB18, LOW active */

#if VL6180X_CONFIG_SUPPORT_SCALING
  // RANGE_SCALER values for 1x, 2x, 3x scaling - see STSW-IMG003 core/src/vl6180x_api.c (ScalerLookUP[])
  static uint16_t const ScalerValues[] = {0, 253, 127, 84};
#endif

static uint8_t scaling = 1; /* default scaling */

const VL6180X_Device VL6180X_DefaultDevice = { /* default device with default address */
  .deviceAddr = VL6180X_DEFAULT_I2C_ADDRESS,
#if VL6180X_CONFIG_MULTIPLE_DEVICES
  .pinAction = NULL,
#endif
#if VL6180X_CONFIG_SUPPORT_SCALING
  .scale = VL6180X_SCALING_FACTOR_1,
  .ptp_offset = 0,
#endif
};

static void VL6180X_OnError(VL6180X_Enum_Error error) {
  /* generic error hook */
  (void)error;
}

uint8_t VL6180X_WriteReg8(VL6180X_Device *device, uint16_t reg, uint8_t val) {
  uint8_t r[2];

  r[0] = reg>>8;
  r[1] = reg&0xff;
  return GI2C1_WriteAddress(device->deviceAddr, &r[0], sizeof(r), &val, sizeof(val));
}

uint8_t VL6180X_WriteReg16(VL6180X_Device *device, uint16_t reg, uint16_t val) {
  uint8_t r[2], v[2];

  r[0] = reg>>8;
  r[1] = reg&0xff;
  v[0] = val>>8;
  v[1] = val&0xff;
  return GI2C1_WriteAddress(device->deviceAddr, &r[0], sizeof(r), &v[0], sizeof(v));
}

uint8_t VL6180X_ReadReg8(VL6180X_Device *device, uint16_t reg, uint8_t *valP) {
  uint8_t tmp[2];

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  return GI2C1_ReadAddress(device->deviceAddr, &tmp[0], sizeof(tmp), valP, 1);
}

uint8_t VL6180X_ReadReg16(VL6180X_Device *device, uint16_t reg, uint16_t *valP) {
  uint8_t tmp[2];

  tmp[0] = reg>>8;
  tmp[1] = reg&0xff;
  return GI2C1_ReadAddress(device->deviceAddr, &tmp[0], sizeof(tmp), (uint8_t*)valP, 2);
}

static uint8_t readRangeContinuous(VL6180X_Device *device, int16_t *valP) {
  uint8_t range;
  uint8_t res, val;
  uint16_t timeoutMs = 100;

  *valP = 0; /* init */
  do { /* breaks */
    res = VL6180X_ReadReg8(device, RESULT__INTERRUPT_STATUS_GPIO, &val);
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
  res = VL6180X_ReadReg8(device, RESULT__RANGE_VAL, &range); /* read range in millimeters */
  if (res!=ERR_OK) {
    return res;
  }
  res = VL6180X_WriteReg8(device, SYSTEM__INTERRUPT_CLEAR, 0x01); /* clear interrupt flag */
  if (res!=ERR_OK) {
    return res;
  }
  *valP = range;
  return ERR_OK;
}

static uint8_t readRangeContinuousMultiple(VL6180X_Device *device, int16_t *valP, uint32_t nofDevices) {
  uint8_t range;
  uint8_t res, val;
  uint16_t timeoutMs = 100;
  uint32_t i, cntr;

  for(i=0;i<nofDevices;i++) {
    valP[i] = 0; /* init */
  }
  do { /* breaks */
    for(i=0,cntr=0;i<nofDevices;i++) {
      res = VL6180X_ReadReg8(&device[i], RESULT__INTERRUPT_STATUS_GPIO, &val);
      if (res!=ERR_OK) {
        break;
      }
      if ((val&0x4)!=0) {
        cntr++; /* 4: New Sample Ready threshold event */
      }
    }
    if (res!=ERR_OK) {
      break;
    }
    if (cntr==nofDevices) {
      break; /* break loop, all devices are ready to read the range info */
    }
    if (timeoutMs==0) { /* timeout */
      break;
    }
    WAIT1_WaitOSms(5);
    timeoutMs--;
  } while(1);
  /* check timout */
  if (timeoutMs==0) {
    return ERR_NOTAVAIL; /* timeout */
  }
  /* read range */
  for(i=0;i<nofDevices;i++) {
    res = VL6180X_ReadReg8(&device[i], RESULT__RANGE_VAL, &range); /* read range in millimeters */
    if (res!=ERR_OK) {
      return res;
    }
    res = VL6180X_WriteReg8(&device[i], SYSTEM__INTERRUPT_CLEAR, 0x01); /* clear interrupt flag */
    if (res!=ERR_OK) {
      return res;
    }
    valP[i] = range;
  }
  return ERR_OK;
}


static uint8_t readAmbientContinuous(VL6180X_Device *device, uint16_t *valP) {
  uint16_t ambient;
  uint8_t res, val;
  uint16_t timeoutMs = 100;

  *valP = 0; /* init */
  do {
   res = VL6180X_ReadReg8(device, RESULT__INTERRUPT_STATUS_GPIO, &val);
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

  res = VL6180X_ReadReg16(device, RESULT__ALS_VAL, &ambient); /* read ambient value */
  if (res!=ERR_OK) {
    return res;
  }
  res = VL6180X_WriteReg8(device, SYSTEM__INTERRUPT_CLEAR, 0x02); /* clear interrupt flag */
  if (res!=ERR_OK) {
    return res;
  }

  *valP = ambient;
  return ERR_OK;
}

uint8_t VL6180X_ReadRangeSingle(VL6180X_Device *device, int16_t *rangeP) {
  uint8_t res;
  int16_t val;

  res = VL6180X_WriteReg8(device, SYSRANGE__START, 0x01);
  if (res!=ERR_OK) {
    *rangeP = -1;
    return res; /* error */
  }
  res = readRangeContinuous(device, &val);
  if (res!=ERR_OK) {
    *rangeP = -1;
    return res; /* error */
  }
  if (val==255) { /* no object measured? */
    *rangeP = -1;
    return ERR_OK;
  } else if (val>=0 && val<255) {
    *rangeP = val*device->scale; /* store value */
    return ERR_OK;
  }
  *rangeP = -2; /* error */
  return ERR_FAILED;
}

uint8_t VL6180X_ReadRangeSingleMultiple(VL6180X_Device *device, int16_t *rangeP, uint32_t nofDevices) {
  uint8_t res;
  uint32_t i;
  bool failed;
  int16_t val;

  /* start measurement */
  for(i=0;i<nofDevices;i++) {
    res = VL6180X_WriteReg8(&device[i], SYSRANGE__START, 0x01);
    if (res!=ERR_OK) {
      for(i=0;i<nofDevices;i++) {
        rangeP[i] = -1; /* error */
      }
      return res; /* error */
    }
  }
  /* wait and get result */
  res = readRangeContinuousMultiple(device, rangeP, nofDevices);
  if (res!=ERR_OK) {
    for(i=0;i<nofDevices;i++) {
      rangeP[i] = -1; /* error */
    }
    return res; /* error */
  }
  failed = FALSE;
  for(i=0;i<nofDevices;i++) {
    val = rangeP[i];
    if (val==255) { /* no object measured? */
      rangeP[i] = -1; /* error */
    } else if (val>=0 && val<255) {
      rangeP[i] = val*device->scale; /* store value */
    } else {
      rangeP[i] = -2; /* error */
      failed = TRUE;
    }
  }
  if (failed) {
    return ERR_FAILED;
  }
  return ERR_OK;
}


uint8_t VL6180X_ReadAmbientSingle(VL6180X_Device *device, uint16_t *ambientP) {
  uint8_t res;

  res = VL6180X_WriteReg8(device, SYSALS__START, 0x01);
  if (res!=ERR_OK) {
    return res;
  }
  return readAmbientContinuous(device, ambientP);
}

uint8_t VL6180X_readLux(VL6180X_Device *device, VL6180X_ALS_GAIN gain, float *pLux) {
  uint8_t reg;
  uint16_t reg16;
  uint8_t res;
  float lux;

  *pLux = 0.0; /* init */
  res = VL6180X_ReadReg8(device, VL6180X_REG_SYSTEM_INTERRUPT_CONFIG, &reg);
  if (res!=ERR_OK) {
    return res;
  }
  reg &= ~0x38;
  reg |= (0x4 << 3); /* IRQ on ALS ready */
  res = VL6180X_WriteReg8(device, VL6180X_REG_SYSTEM_INTERRUPT_CONFIG, reg);
  if (res!=ERR_OK) {
    return res;
  }

  /* 100 ms integration period */
  res = VL6180X_WriteReg8(device, VL6180X_REG_SYSALS_INTEGRATION_PERIOD_HI, 0);
  if (res!=ERR_OK) {
    return res;
  }
  res = VL6180X_WriteReg8(device, VL6180X_REG_SYSALS_INTEGRATION_PERIOD_LO, 100);
  if (res!=ERR_OK) {
    return res;
  }

  /* analog gain */
  if (gain > VL6180X_ALS_GAIN_40) {
    gain = VL6180X_ALS_GAIN_40;
  }
  res = VL6180X_WriteReg8(device, VL6180X_REG_SYSALS_ANALOGUE_GAIN, 0x40 | gain);
  if (res!=ERR_OK) {
    return res;
  }

  /* start ALS */
  res = VL6180X_WriteReg8(device, VL6180X_REG_SYSALS_START, 0x1);
  if (res!=ERR_OK) {
    return res;
  }

  /* Poll until "New Sample Ready threshold event" is set */
  do {
    res = VL6180X_ReadReg8(device, VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO, &reg);
    if (((reg>>3)&0x7)==4) {
      break; /* new result ready */
    }
    /* \todo add proper timeout handling */
  } while(1);

  /* read lux */
  res = VL6180X_ReadReg16(device, VL6180X_REG_RESULT_ALS_VAL, &reg16);
  if (res!=ERR_OK) {
    return res;
  }
  lux = reg16;

  /* clear interrupt */
  res = VL6180X_WriteReg8(device, VL6180X_REG_SYSTEM_INTERRUPT_CLEAR, 0x07);

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

#if VL6180X_CONFIG_SUPPORT_SCALING
/* Set range scaling factor. The sensor uses 1x scaling by default, giving range
 * measurements in units of mm. Increasing the scaling to 2x or 3x makes it give
 * raw values in units of 2 mm or 3 mm instead. In other words, a bigger scaling
 * factor increases the sensor's potential maximum range but reduces its
 * resolution.
*/
/* Implemented using ST's VL6180X API as a reference (STSW-IMG003); see
 * VL6180x_UpscaleSetScaling() in vl6180x_api.c.
 * https://github.com/pololu/vl6180x-arduino/blob/master/VL6180X.cpp
 */
uint8_t VL6180X_setScaling(VL6180X_Device *device, uint8_t new_scaling) {
  uint8_t const DefaultCrosstalkValidHeight = 20; /* default value of SYSRANGE__CROSSTALK_VALID_HEIGHT */
  uint8_t rce, res;

  /* do nothing if scaling value is invalid */
  if (new_scaling < VL6180X_SCALING_FACTOR_1 || new_scaling > VL6180X_SCALING_FACTOR_3) {
    return ERR_RANGE;
  }

  scaling = new_scaling;
  res = VL6180X_WriteReg16(device, RANGE_SCALER, ScalerValues[scaling]);
  if (res!=ERR_OK) {
    return res;
  }

  /* apply scaling on part-to-part offset */
  res = VL6180X_WriteReg8(device, SYSRANGE__PART_TO_PART_RANGE_OFFSET, device->ptp_offset / scaling);
  if (res!=ERR_OK) {
    return res;
  }

  /* apply scaling on CrossTalkValidHeight */
  res = VL6180X_WriteReg8(device, SYSRANGE__CROSSTALK_VALID_HEIGHT, DefaultCrosstalkValidHeight / scaling);
  if (res!=ERR_OK) {
    return res;
  }

  /* This function does not apply scaling to RANGE_IGNORE_VALID_HEIGHT. */

  /* enable early convergence estimate only at 1x scaling */
  res = VL6180X_ReadReg8(device, SYSRANGE__RANGE_CHECK_ENABLES, &rce);
  if (res!=ERR_OK) {
    return res;
  }
  res = VL6180X_WriteReg8(device, SYSRANGE__RANGE_CHECK_ENABLES, (rce&0xFE) | (scaling==VL6180X_SCALING_FACTOR_1));
  if (res!=ERR_OK) {
    return res;
  }
  device->scale = scaling;
  return ERR_OK;
}
#endif


/* Configure some settings for the sensor's default behavior from AN4545 -
 * "Recommended : Public registers" and "Optional: Public registers"
 */
static uint8_t VL6180X_ConfigureDefaults(VL6180X_Device *device) {
  uint8_t res;

  /* "Recommended : Public registers" */
  /* Set the averaging sample period (compromise between lower noise and increased execution time) */
  res = VL6180X_WriteReg8(device, READOUT__AVERAGING_SAMPLE_PERIOD, 0x30);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  /* sysals__analogue_gain_light = 6 (ALS gain = 1 nominal, actually 1.01 according to Table 14 in datasheet)
   * Sets the light and dark gain (upper nibble). Dark gain should not be changed.  */
  res = VL6180X_WriteReg8(device, SYSALS__ANALOGUE_GAIN, 0x46);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  // sysrange__vhv_repeat_rate = 255 (auto Very High Voltage temperature recalibration after every 255 range measurements)
  /* sets the # of range measurements after which auto calibration of system is which auto calibration of system is performed */
  res = VL6180X_WriteReg8(device, SYSRANGE__VHV_REPEAT_RATE, 0xFF);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  /* sysals__integration_period = 99 (100 ms) */
  /* AN4545 incorrectly recommends writing to register 0x040; 0x63 should go in the lower byte, which is register 0x041. */
  /* Set ALS integration time to 100ms */
  res = VL6180X_WriteReg16(device, SYSALS__INTEGRATION_PERIOD, 0x0063);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  /* sysrange__vhv_recalibrate = 1 (manually trigger a VHV recalibration) */
  /* perform a single temperature calibration of the ranging sensor */
  res = VL6180X_WriteReg8(device, SYSRANGE__VHV_RECALIBRATE, 0x01);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  /* Optional: Public registers, see data sheet for more detail */
  /* Set default ranging inter-measurement period to 100ms */
  res = VL6180X_WriteReg8(device, SYSRANGE__INTERMEASUREMENT_PERIOD, 0x09);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  /* Set default ALS inter-measurement period to 500ms */
  res = VL6180X_WriteReg8(device, SYSALS__INTERMEASUREMENT_PERIOD, 0x31);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  /* Configures interrupt on 'New Sample Ready threshold event' */
  res = VL6180X_WriteReg8(device, SYSTEM__INTERRUPT_CONFIG_GPIO, 0x24);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }

  scaling = 1;
  return ERR_OK;
}

/* Initialize sensor with settings from ST application note AN4545, section 9 -
   "Mandatory : private registers" */
static uint8_t VL6180X_InitDevice(VL6180X_Device *device) {
  uint8_t res, val;

#if VL6180X_CONFIG_SUPPORT_SCALING
  res = VL6180X_ReadReg8(device, SYSRANGE__PART_TO_PART_RANGE_OFFSET, &device->ptp_offset);
  if (res!=ERR_OK) {
    device->ptp_offset = 0; /* reset value to default in error case */
  }
#endif

  res = VL6180X_ReadReg8(device, SYSTEM__FRESH_OUT_OF_RESET, &val);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
    return res;
  }
  if (val==1)  {
    scaling = 1;

    res = VL6180X_WriteReg8(device, 0x207, 0x01);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x208, 0x01);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x096, 0x00);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x097, 0xFD); /* RANGE_SCALER = 253 */
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0E3, 0x00);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0E4, 0x04);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0E5, 0x02);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0E6, 0x01);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0E7, 0x03);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0F5, 0x02);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0D9, 0x05);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0DB, 0xCE);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0DC, 0x03);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0DD, 0xF8);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x09F, 0x00);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0A3, 0x3C);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0B7, 0x00);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0BB, 0x3C);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0B2, 0x09);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0CA, 0x09);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x198, 0x01);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x1B0, 0x17);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x1AD, 0x00);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x0FF, 0x05);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x100, 0x05);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x199, 0x05);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x1A6, 0x1B);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x1AC, 0x3E);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x1A7, 0x1F);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
    res = VL6180X_WriteReg8(device, 0x030, 0x00);
    if (res!=ERR_OK) {
      VL6180X_OnError(VL6180X_ON_ERROR_INIT_DEVICE);
      return res;
    }
  } else {
    // Sensor has already been initialized, so try to get scaling settings by
    // reading registers.
    uint16_t s;

    res = VL6180X_ReadReg16(device, RANGE_SCALER, &s);

    if      (s == ScalerValues[3]) { scaling = 3; }
    else if (s == ScalerValues[2]) { scaling = 2; }
    else                           { scaling = 1; }

    // Adjust the part-to-part range offset value read earlier to account for
    // existing scaling. If the sensor was already in 2x or 3x scaling mode,
    // precision will be lost calculating the original (1x) offset, but this can
    // be resolved by resetting the sensor and Arduino again.
    device->ptp_offset *= scaling;
  }
  return ERR_OK;
}

uint8_t VL6180X_InitAndConfigureDevice(VL6180X_Device *device) {
  uint8_t res;

  res = VL6180X_InitDevice(device);
  if (res!=ERR_OK) {
    return res;
  }
  res = VL6180X_ConfigureDefaults(device);
  if (res!=ERR_OK) {
    return res;
  }
#if VL6180X_CONFIG_SUPPORT_SCALING
  res = VL6180X_setScaling(device, VL6180X_SCALING_FACTOR_3);
  if (res!=ERR_OK) {
    return res;
  }
#endif
  return res;
}

uint8_t VL6180X_ChipEnable(VL6180X_Device *device, bool on) {
  if (device==NULL || device->pinAction==NULL) {
    return ERR_FAILED;
  }
  if (on) {
    device->pinAction(VL6180X_PIN_ACTION_SET_INPUT); /* let it pull high by the pull-up on the board */
  } else {
    device->pinAction(VL6180X_PIN_ACTION_SET_LOW); /* pull it down */
    device->pinAction(VL6180X_PIN_ACTION_SET_OUTPUT);
  }
  return ERR_OK;
}

uint8_t VL6180X_SetI2CDeviceAddress(VL6180X_Device *device) {
  uint8_t res;
  uint8_t val;

  /* device just has been powered on: it shall be accessible using the default address */
  res = VL6180X_WriteReg8((VL6180X_Device*)&VL6180X_DefaultDevice, I2C_SLAVE__DEVICE_ADDRESS, device->deviceAddr);
  if (res!=ERR_OK) {
    VL6180X_OnError(VL6180X_ON_ERROR_SET_I2C_ADDRESS);
    return ERR_FAILED;
  }
  /* test: read back with new address */
  res = VL6180X_ReadReg8(device, I2C_SLAVE__DEVICE_ADDRESS, &val);
  if (res!=ERR_OK || val != device->deviceAddr) {
    VL6180X_OnError(VL6180X_ON_ERROR_SET_I2C_ADDRESS);
    return ERR_FAILED;
  }
  /* device is accessible with the new address now */
  return ERR_OK;
}

uint8_t VL6180X_Deinit(void) {
  return ERR_OK;
}

uint8_t VL6180X_Init(void) {
  /* use VL6180X_InitDevice() from a task with interrupts enabled */
  TofPwr_ClrVal(); /* turn on power for sensors */
  return ERR_OK;
}
#endif /* PL_HAS_TOF_SENSOR */
