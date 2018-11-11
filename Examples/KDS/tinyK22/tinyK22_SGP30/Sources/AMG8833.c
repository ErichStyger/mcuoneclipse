/*
 * AMG833.c
 *
 *  Created on: 09.11.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_AMG8833
#include "AMG8833.h"
#include "GI2C1.h"
#include "UTIL1.h"
#include "WAIT1.h"


/* I2C Address */
#define AMG88xx_I2C_ADDRESS (0x69)

 enum {
    AMG88xx_PCTL = 0x00,
    AMG88xx_RST = 0x01,
    AMG88xx_FPSC = 0x02,
    AMG88xx_INTC = 0x03,
    AMG88xx_STAT = 0x04,
    AMG88xx_SCLR = 0x05,
    //0x06 reserved
    AMG88xx_AVE = 0x07,
    AMG88xx_INTHL = 0x08,
    AMG88xx_INTHH = 0x09,
    AMG88xx_INTLL = 0x0A,
    AMG88xx_INTLH = 0x0B,
    AMG88xx_IHYSL = 0x0C,
    AMG88xx_IHYSH = 0x0D,
    AMG88xx_TTHL = 0x0E,
    AMG88xx_TTHH = 0x0F,
    AMG88xx_INT_OFFSET = 0x010,
    AMG88xx_PIXEL_OFFSET = 0x80
    };

  enum power_modes{
    AMG88xx_NORMAL_MODE = 0x00,
    AMG88xx_SLEEP_MODE = 0x01,
    AMG88xx_STAND_BY_60 = 0x20,
    AMG88xx_STAND_BY_10 = 0x21
  };

  enum sw_resets {
    AMG88xx_FLAG_RESET = 0x30,
    AMG88xx_INITIAL_RESET = 0x3F
  };

  enum frame_rates {
    AMG88xx_FPS_10 = 0x00,
    AMG88xx_FPS_1 = 0x01
  };

  enum int_enables{
    AMG88xx_INT_DISABLED = 0x00,
    AMG88xx_INT_ENABLED = 0x01
};

  enum int_modes {
    AMG88xx_DIFFERENCE = 0x00,
    AMG88xx_ABSOLUTE_VALUE = 0x01
  };

/*=========================================================================*/

#define AMG88xx_PIXEL_TEMP_CONVERSION    .25
#define AMG88xx_THERMISTOR_CONVERSION    .0625


//interrupt control register
static struct {
    // 0 = INT output reactive (Hi-Z)
    // 1 = INT output active
    uint8_t INTEN : 1;
    // 0 = Difference interrupt mode
    // 1 = absolute value interrupt mode
    uint8_t INTMOD : 1;
} intc;

static uint8_t intc_get(void) {
   return (intc.INTMOD << 1 | intc.INTEN) & 0x03;
}


//reset register
static struct {
  //0x30 = flag reset (all clear status reg 0x04, interrupt flag and interrupt table)
  //0x3F = initial reset (brings flag reset and returns to initial setting)
  uint8_t RST : 8;
} rst;

static uint8_t rst_get(void) {
  return rst.RST;
}

//interrupt level registers
//for setting upper / lower limit hysteresis on interrupt level

//interrupt level upper limit setting. Interrupt output
// and interrupt pixel table are set when value exceeds set value
static struct  {
  uint8_t INT_LVL_H : 8;
} inthl;

static uint8_t inthl_get(void) {
  return inthl.INT_LVL_H;
}

static struct  {
  uint8_t INT_LVL_H : 4;
} inthh;

static uint8_t inthh_get(void) {
  return inthh.INT_LVL_H;
}

//interrupt level lower limit. Interrupt output
//and interrupt pixel table are set when value is lower than set value
static struct  {
  uint8_t INT_LVL_L : 8;
} intll;

static uint8_t intll_get(void) {
   return intll.INT_LVL_L;
}

static struct  {
  uint8_t INT_LVL_L : 4;
} intlh;

static uint8_t intlh_get(void) {
  return (intlh.INT_LVL_L & 0xF);
}

//setting of interrupt hysteresis level when interrupt is generated.
//should not be higher than interrupt level
static struct  {
  uint8_t INT_HYS : 8;

} ihysl;

static uint8_t ihysl_get(void) {
  return ihysl.INT_HYS;
}

static struct {
  uint8_t INT_HYS : 4;
} ihysh;

static uint8_t ihysh_get(void) {
   return (ihysh.INT_HYS & 0xF);
}

//average register
//for setting moving average output mode
static struct {
  uint8_t unused : 5;
  //1 = twice moving average mode
  uint8_t MAMOD : 1;
} ave;

static uint8_t ave_get(){
  return (ave.MAMOD << 5);
}

//frame rate register
static struct {
  //0 = 10FPS
  //1 = 1FPS
  uint8_t FPS : 1;
} fpsc;

static uint8_t fpsc_get(void) {
  return fpsc.FPS & 0x01;
}

static struct {
// 0x00 = Normal Mode
// 0x01 = Sleep Mode
// 0x20 = Stand-by mode (60 sec intermittence)
// 0x21 = Stand-by mode (10 sec intermittence)
      uint8_t PCTL : 8;
} pctl;

static uint8_t pctl_get(void) {
    return pctl.PCTL;
}
/*=========================================================================*/

static uint8_t AMG88xx_write(uint8_t reg, uint8_t *buf, uint8_t bufSize) {
  return GI2C1_WriteAddress(AMG88xx_I2C_ADDRESS, &reg, 1, buf, bufSize);
}

/**************************************************************************/
/*!
    @brief  write one byte of data to the specified register
    @param  reg the register to write to
    @param  value the value to write
*/
/**************************************************************************/
static uint8_t AMG88xx_write8(uint8_t reg, uint8_t value) {
  return GI2C1_WriteByteAddress8(AMG88xx_I2C_ADDRESS, reg, value);
}

/**************************************************************************/
/*!
    @brief  read one byte of data from the specified register
    @param  reg the register to read
    @returns one byte of register data
*/
/**************************************************************************/
static uint8_t AMG88xx_read8(uint8_t reg, uint8_t *value) {
  return GI2C1_ReadByteAddress8(AMG88xx_I2C_ADDRESS, reg, value);
}

static uint8_t AMG88xx_read(uint8_t reg, uint8_t *buf, uint8_t num) {
  return GI2C1_ReadAddress(AMG88xx_I2C_ADDRESS, &reg, sizeof(reg), buf, num);
}

/**************************************************************************/
/*!
    @brief  convert a 12-bit signed magnitude value to a floating point number
    @param  val the 12-bit signed magnitude value to be converted
    @returns the converted floating point value
*/
/**************************************************************************/
static float AMG88xx_signedMag12ToFloat(uint16_t val) {
  //take first 11 bits as absolute val
  uint16_t absVal = (val & 0x7FF);

  return (val & 0x8000) ? 0 - (float)absVal : (float)absVal ;
}


/**************************************************************************/
/*!
    @brief  Set the interrupt levels
    @param  high the value above which an interrupt will be triggered
    @param  low the value below which an interrupt will be triggered
    @param hysteresis the hysteresis value for interrupt detection
*/
/**************************************************************************/
uint8_t AMG88xx_SetInterruptLevels(float high, float low, float hysteresis) {
  int highConv = high / AMG88xx_PIXEL_TEMP_CONVERSION;
  uint8_t res;

  highConv = UTIL1_constrain(highConv, -4095, 4095);
  inthl.INT_LVL_H = highConv & 0xFF;
  inthh.INT_LVL_H = (highConv & 0xF) >> 4;
  res = AMG88xx_write8(AMG88xx_INTHL, inthl_get());
  if (res!=ERR_OK) {
    return res;
  }
  res = AMG88xx_write8(AMG88xx_INTHH, inthh_get());
  if (res!=ERR_OK) {
    return res;
  }

  int lowConv = low / AMG88xx_PIXEL_TEMP_CONVERSION;
  lowConv = UTIL1_constrain(lowConv, -4095, 4095);
  intll.INT_LVL_L = lowConv & 0xFF;
  intlh.INT_LVL_L = (lowConv & 0xF) >> 4;
  res = AMG88xx_write8(AMG88xx_INTLL, intll_get());
  if (res!=ERR_OK) {
    return res;
  }
  res = AMG88xx_write8(AMG88xx_INTLH, intlh_get());
  if (res!=ERR_OK) {
    return res;
  }

  int hysConv = hysteresis / AMG88xx_PIXEL_TEMP_CONVERSION;
  hysConv = UTIL1_constrain(hysConv, -4095, 4095);
  ihysl.INT_HYS = hysConv & 0xFF;
  ihysh.INT_HYS = (hysConv & 0xF) >> 4;
  res = AMG88xx_write8(AMG88xx_IHYSL, ihysl_get());
  if (res!=ERR_OK) {
    return res;
  }
  res = AMG88xx_write8(AMG88xx_IHYSH, ihysh_get());
  return res;
}

/**************************************************************************/
/*!
    @brief  Set the moving average mode.
    @param  mode if True is passed, output will be twice the moving average
*/
/**************************************************************************/
uint8_t AMG88xx_SetMovingAverageMode(bool mode) {
  ave.MAMOD = mode;
  return AMG88xx_write8(AMG88xx_AVE, ave_get());
}

/**************************************************************************/
/*!
    @brief  Set the interrupt levels. The hysteresis value defaults to .95 * high
    @param  high the value above which an interrupt will be triggered
    @param  low the value below which an interrupt will be triggered
*/
/**************************************************************************/
uint8_t AMG88xx_SetInterruptLevelsHighLow(float high, float low) {
  return AMG88xx_SetInterruptLevels(high, low, high * .95);
}


/**************************************************************************/
/*!
    @brief  enable the interrupt pin on the device.
*/
/**************************************************************************/
uint8_t AMG88xx_EnableInterrupt(void) {
  intc.INTEN = 1;
  return AMG88xx_write8(AMG88xx_INTC, intc_get());
}

/**************************************************************************/
/*!
    @brief  disable the interrupt pin on the device
*/
/**************************************************************************/
uint8_t AMG88xx_DisableInterrupt(void) {
  intc.INTEN = 0;
  return AMG88xx_write8(AMG88xx_INTC, intc_get());
}

/**************************************************************************/
/*!
    @brief  Set the interrupt to either absolute value or difference mode
    @param  mode passing AMG88xx_DIFFERENCE sets the device to difference mode, AMG88xx_ABSOLUTE_VALUE sets to absolute value mode.
*/
/**************************************************************************/
uint8_t AMG88xx_SetInterruptMode(uint8_t mode) {
  intc.INTMOD = mode;
  return AMG88xx_write8(AMG88xx_INTC, intc_get());
}

/**************************************************************************/
/*!
    @brief  Read the state of the triggered interrupts on the device. The full interrupt register is 8 bytes in length.
    @param  buf the pointer to where the returned data will be stored
    @param  size Number of bytes to read. Must be 8 bytes.
    @returns 8 bytes of data in buf
*/
/**************************************************************************/
uint8_t AMG88xx_getInterrupt(uint8_t *buf, uint8_t size) {
  if (size!=8) {
    return ERR_FAULT; /* buffer size must be 8! */
  }
  return AMG88xx_read(AMG88xx_INT_OFFSET, buf, size);
}

/**************************************************************************/
/*!
    @brief  Clear any triggered interrupts
*/
/**************************************************************************/
uint8_t AMG88xx_clearInterrupt(void) {
  rst.RST = AMG88xx_FLAG_RESET;
  return AMG88xx_write8(AMG88xx_RST, rst_get());
}

/**************************************************************************/
/*!
    @brief  read the onboard thermistor
    @returns a the floating point temperature in degrees Celsius
*/
/**************************************************************************/
uint8_t AMG88xx_readThermistor(float *value) {
  uint8_t raw[2];
  uint8_t res;


  res = AMG88xx_read(AMG88xx_TTHL, raw, 2);
  if (res!=ERR_OK) {
    return res;
  }
  uint16_t recast = ((uint16_t)raw[1] << 8) | ((uint16_t)raw[0]);
  *value = AMG88xx_signedMag12ToFloat(recast) * AMG88xx_THERMISTOR_CONVERSION;
  return res;
}

void AMG88xx_FlipHorizontal(float buf[AMG88xx_PIXEL_ROWS][AMG88xx_PIXEL_COLS]) {
  int x, y;
  float tmp;

  for(y=0;y<AMG88xx_PIXEL_ROWS;y++) {
    for(x=0;x<AMG88xx_PIXEL_COLS/2;x++) {
      tmp = buf[y][x];
      buf[y][x] = buf[y][AMG88xx_PIXEL_COLS-1-x];
      buf[y][AMG88xx_PIXEL_COLS-1-x] = tmp;
    }
  }
}

/**************************************************************************/
/*!
    @brief  Read Infrared sensor values
    @param  buf the array to place the pixels in
    @param  size number of bytes to read (up to 64). Default is 64 bytes.
    @return has to be 64 bytes of pixel data in buf
*/
/**************************************************************************/
uint8_t AMG88xx_readPixels(float *buf, uint8_t nofPixels) {
  uint16_t recast;
  float converted;
  uint8_t res;
  static uint8_t rawArray[AMG88xx_PIXEL_ARRAY_SIZE << 1]; /* to save stack space, makes it non-reentrant! */

  if (nofPixels!=AMG88xx_PIXEL_ARRAY_SIZE) {
    return ERR_OVERFLOW;
  }
  res = AMG88xx_read(AMG88xx_PIXEL_OFFSET, rawArray, sizeof(rawArray));
  if (res!=ERR_OK) {
    return res;
  }
  for(int i=0; i<nofPixels; i++){
    uint8_t pos = i << 1;
    recast = ((uint16_t)rawArray[pos + 1] << 8) | ((uint16_t)rawArray[pos]);
    converted = AMG88xx_signedMag12ToFloat(recast) * AMG88xx_PIXEL_TEMP_CONVERSION;
    buf[i] = converted;
  }
  return ERR_OK;
}

uint8_t AMG_Init(void) {
  uint8_t res;

  //enter normal mode
  pctl.PCTL = AMG88xx_NORMAL_MODE;
  res = AMG88xx_write8(AMG88xx_PCTL, pctl_get());
  if (res!=ERR_OK) {
    return res;
  }

  //software reset
  rst.RST = AMG88xx_INITIAL_RESET;
  res = AMG88xx_write8(AMG88xx_RST, rst_get());
  if (res!=ERR_OK) {
    return res;
  }

  //set to 10 FPS
  fpsc.FPS = AMG88xx_FPS_10;
  res = AMG88xx_write8(AMG88xx_FPSC, fpsc_get());
  if (res!=ERR_OK) {
    return res;
  }

  WAIT1_WaitOSms(100);
  return ERR_OK;
}

#endif /* PL_CONFIG_HAS_AMG8833 */
