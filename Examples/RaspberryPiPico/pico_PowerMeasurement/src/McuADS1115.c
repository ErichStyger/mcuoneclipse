/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuADS1115.h"
#include "McuADS1115_config.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"
#include "McuUtility.h"
#include "McuGenericI2C.h"
#include "McuLog.h"

/* TI ADS1115 device register map: */
typedef enum McuADS1115_Reg_e { /* values are the hardware register addresses */
  McuADS1115_ADDR_CONVERSION_REGISTER      = 0x00,  /**< Conversion result register */
  McuADS1115_ADDR_CONFIGURATION_REGISTER   = 0x01,  /**< Configuration and settings register */
  McuADS1115_ADDR_LOW_THRES_REGISTER       = 0x02,  /**< Low Threshold register */
  McuADS1115_ADDR_HIGH_TRHES_REGISTER      = 0x03,  /**< High Threshold register */
} McuADS1115_Reg_e;

typedef enum McuADS1115_Range_e { /* values are the ones in the configuration register */
  McuADS1115_RANGE_6P144V = 0b00,  /**< 6.144V range */
  McuADS1115_RANGE_4P096V = 0b01,  /**< 4.096V range */
  McuADS1115_RANGE_2P048V = 0b10,  /**< 2.048V range */
  McuADS1115_RANGE_1P024V = 0b11,  /**< 1.024V range */
  McuADS1115_RANGE_0P512V,  /**< 0.512V range */
  McuADS1115_RANGE_0P256V,  /**< 0.256V range */
} McuADS1115_Range_e;

typedef enum McuADS1115_Mux_e { /* values correspond to the config register MUX bits */
  McuADS1115_MUX_AIN0_AIN1 = 0b000, /**< AIN0 and AIN1 pins */
  McuADS1115_MUX_AIN0_AIN3 = 0b001, /**< AIN0 and AIN3 pins */
  McuADS1115_MUX_AIN1_AIN3 = 0b010, /**< AIN1 and AIN3 pins */
  McuADS1115_MUX_AIN2_AIN3 = 0b011, /**< AIN2 and AIN3 pins */
  McuADS1115_MUX_AIN0_GND  = 0b100, /**< AIN0 and GND pins */
  McuADS1115_MUX_AIN1_GND  = 0b101, /**< AIN1 and GND pins */
  McuADS1115_MUX_AIN2_GND  = 0b110, /**< AIN2 and GND pins */
  McuADS1115_MUX_AIN3_GND  = 0b111, /**< AIN3 and GND pins */
} McuADS1115_Mux_e;

#define SWAP_BYTES(u16)  (((u16)<<8)|((u16)>>8))

uint8_t McuADS1115_ReadRegisterWord(McuADS1115_Reg_e reg, uint16_t *value) {
  uint8_t res;
  uint16_t data;

  res = McuGenericI2C_ReadWordAddress8(McuADS1115_CONFIG_I2C_ADDRESS, reg, &data);
  if (res!=ERR_OK) {
    return res;
  }
  *value = SWAP_BYTES(data);
  return ERR_OK;
}

uint8_t McuADS1115_WriteRegisterWord(McuADS1115_Reg_e reg, uint16_t value) {
  uint8_t res;
  uint16_t data;

  data = SWAP_BYTES(value);
  res = McuGenericI2C_WriteWordAddress8(McuADS1115_CONFIG_I2C_ADDRESS, reg, data);
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t McuADS1115_ReadConversionRaw(uint16_t *value) {
  return McuADS1115_ReadRegisterWord(McuADS1115_ADDR_CONVERSION_REGISTER, value);
}

uint8_t McuADS1115_ReadConversionAndScale(uint16_t *value, McuADS1115_Range_e range, float *f) {
  uint8_t res;
  uint16_t raw;

  *value = 0;
  res = McuADS1115_ReadRegisterWord(McuADS1115_ADDR_CONVERSION_REGISTER, &raw);
  if (res!=ERR_OK) {
    return res;
  }
  switch(range) {
    case McuADS1115_RANGE_6P144V: *f = (float)(raw) * 6.144f / 32768.0f; break;
    case McuADS1115_RANGE_4P096V: *f = (float)(raw) * 4.096f / 32768.0f; break;
    case McuADS1115_RANGE_2P048V: *f = (float)(raw) * 2.048f / 32768.0f; break;
    case McuADS1115_RANGE_1P024V: *f = (float)(raw) * 1.024f / 32768.0f; break;
    case McuADS1115_RANGE_0P512V: *f = (float)(raw) * 0.512f / 32768.0f; break;
    case McuADS1115_RANGE_0P256V: *f = (float)(raw) * 0.256f / 32768.0f; break;
    default:
        return ERR_FAILED;
        break;
  }
  return ERR_OK;
}

uint8_t McuADS1115_ReadLowThreshold(uint16_t *value) {
  return McuADS1115_ReadRegisterWord(McuADS1115_ADDR_LOW_THRES_REGISTER, value);
}

uint8_t McuADS1115_ReadHighThreshold(uint16_t *value) {
  return McuADS1115_ReadRegisterWord(McuADS1115_ADDR_HIGH_TRHES_REGISTER, value);
}

uint8_t McuADS1115_ReadConfig(uint16_t *value) {
  return McuADS1115_ReadRegisterWord(McuADS1115_ADDR_CONFIGURATION_REGISTER, value);
}

uint8_t McuADS1115_WriteConfig(uint16_t value) {
  return McuADS1115_WriteRegisterWord(McuADS1115_ADDR_CONFIGURATION_REGISTER, value);
}

uint8_t McuADS1115_SetConversionModeSingle(bool isSingleShotMode) {
  uint16_t config;
  uint8_t res;

  res = McuADS1115_ReadConfig(&config);
  if (res!=ERR_OK) {
    return res;
  }
  /* bit8: 0: continuous conversion mode; 1: single-shot mode */
  if (isSingleShotMode) {
    config |= (1<<8); /* set bit */
  } else {
    config &= ~(1<<8); /* clear bit */
  }
  return McuADS1115_WriteConfig(config);
}

uint8_t McuADS1115_SingleShot(void) {
  uint16_t config;
  uint8_t res;

  res = McuADS1115_ReadConfig(&config);
  if (res!=ERR_OK) {
    return res;
  }
  /* write bit15: 1: Begin a single-shot conversion */
  config |= (1<<15); /* set bit */
  return McuADS1115_WriteConfig(config);
}


uint8_t McuADS1115_WriteMux(McuADS1115_Mux_e mux) {
  uint16_t config;
  uint8_t res;

  res = McuADS1115_ReadConfig(&config);
  if (res!=ERR_OK) {
    return res;
  }
  /* write bit14..bit12: 3bits for muxing */
  config &= ~(0b111<<12); /* clear muxing bits */
  config |= mux<<12; /* set new bits */
  return McuADS1115_WriteConfig(config);
}

uint8_t McuADS1115_Test(void) {
  uint16_t val;
  if (McuADS1115_SingleShot()!=ERR_OK) {
    return ERR_FAILED;
  }
  //if (McuADS1115_ReadConversionAndScale(&val)!=ERR_OK) {
  //  return ERR_FAILED;
  //}
  return ERR_OK;
}

uint8_t McuADS1115_PrintConfig(const McuShell_StdIOType *io) {
  uint16_t config;
  uint8_t res;
  const char *txt;

  res = McuADS1115_ReadConfig(&config);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  /*
    Bit [15] OS: Operational status/single-shot conversion start
    This bit determines the operational status of the device.
    This bit can only be written when in power-down mode.
    For a write status:
    0 : No effect
    1 : Begin a single conversion (when in power-down mode)
    For a read status:
    0 : Device is currently performing a conversion
    1 : Device is not currently performing a conversion
  */
  if (config&(1<<15)) {
    txt = "OS 1        : Device is not currently performing a conversion\r\n";
  } else {
    txt = "OS 0        : Device is currently performing a conversion\r\n";
  }
  McuShell_printfIO(io, txt);
/*
    Bits [14:12] MUX[2:0]: Input multiplexer configuration (ADS1115 only)
    These bits configure the input multiplexer. They serve no function on the ADS1113/4.
    000 : AINP = AIN0 and AINN = AIN1 (default) 100 : AINP = AIN0 and AINN = GND
    001 : AINP = AIN0 and AINN = AIN3           101 : AINP = AIN1 and AINN = GND
    010 : AINP = AIN1 and AINN = AIN3           110 : AINP = AIN2 and AINN = GND
    011 : AINP = AIN2 and AINN = AIN3           111 : AINP = AIN3 and AINN = GND
*/
  switch((config>>12)&0b111) {
    case McuADS1115_MUX_AIN0_AIN1: txt = "MUX 000     : AINP = AIN0 and AINN = AIN1 (default)\r\n"; break;
    case McuADS1115_MUX_AIN0_AIN3: txt = "MUX 001     : AINP = AIN0 and AINN = AIN3\r\n"; break;
    case McuADS1115_MUX_AIN1_AIN3: txt = "MUX 010     : AINP = AIN1 and AINN = AIN3\r\n"; break;
    case McuADS1115_MUX_AIN2_AIN3: txt = "MUX 011     : AINP = AIN2 and AINN = AIN3\r\n"; break;
    case McuADS1115_MUX_AIN0_GND:  txt = "MUX 100     : AINP = AIN0 and AINN = GND\r\n"; break;
    case McuADS1115_MUX_AIN1_GND:  txt = "MUX 101     : AINP = AIN1 and AINN = GND\r\n"; break;
    case McuADS1115_MUX_AIN2_GND:  txt = "MUX 110     : AINP = AIN2 and AINN = GND\r\n"; break;
    case McuADS1115_MUX_AIN3_GND:  txt = "MUX 111     : AINP = AIN3 and AINN = GND\r\n"; break;
    default: txt = "MUX error\r\n"; break;
  }
  McuShell_printfIO(io, txt);
/*
    Bits [11:9] PGA[2:0]: Programmable gain amplifier configuration (ADS1114 and ADS1115 only)
    These bits configure the programmable gain amplifier. They serve no function on the ADS1113.
    000 : FS = ±6.144V(1)           100 : FS = ±0.512V
    001 : FS = ±4.096V(1)           101 : FS = ±0.256V
    010 : FS = ±2.048V (default)    110 : FS = ±0.256V
    011 : FS = ±1.024V              111 : FS = ±0.256V
*/
  switch((config>>9)&0b111) {
    case 0b000: txt = "PGA 000     : FS= +/-6.144V\r\n"; break;
    case 0b001: txt = "PGA 001     : FS= +/-4.096V\r\n"; break;
    case 0b010: txt = "PGA 010     : FS= +/-2.048V (default)\r\n"; break;
    case 0b011: txt = "PGA 011     : FS= +/-1.024V\r\n"; break;
    case 0b100: txt = "PGA 100     : FS= +/-0.512V\r\n"; break;
    case 0b101: txt = "PGA 101     : FS= +/-0.256V\r\n"; break;
    case 0b110: txt = "PGA 110     : FS= +/-0.256V\r\n"; break;
    case 0b111: txt = "PGA 111     : FS= +/-0.256V\r\n"; break;
    default: txt = "PGA error\r\n"; break;
  }
  McuShell_printfIO(io, txt);
/*
    Bit [8] MODE: Device operating mode
    This bit controls the current operational mode of the ADS1113/4/5.
    0 : Continuous conversion mode
    1 : Power-down single-shot mode (default)
*/
  if (config&(1<<8)) {
    txt = "MODE 1      : Power-down single-shot mode (default)\r\n";
  } else {
    txt = "MODE 0      : Continuous conversion mode\r\n";
  }
  McuShell_printfIO(io, txt);
/*
    Bits [7:5] DR[2:0]: Data rate
    These bits control the data rate setting.
    000 : 8SPS      100 : 128SPS (default)
    001 : 16SPS     101 : 250SPS
    010 : 32SPS     110 : 475SPS
    011 : 64SPS     111 : 860SPS
*/
  switch((config>>5)&0b11) {
    case 0b000: txt = "DR 000      : 8SPS\r\n"; break;
    case 0b001: txt = "DR 001      : 16SPS\r\n"; break;
    case 0b010: txt = "DR 010      : 32SPS\r\n"; break;
    case 0b011: txt = "DR 011      : 64SPS\r\n"; break;
    case 0b100: txt = "DR 100      : 128SPS (default)\r\n"; break;
    case 0b101: txt = "DR 101      : 250SPS\r\n"; break;
    case 0b110: txt = "DR 110      : 475SPS\r\n"; break;
    case 0b111: txt = "DR 111      : 860SPS\r\n"; break;
    default: txt = "DR error\r\n"; break;
  }
  McuShell_printfIO(io, txt);
/*
    Bit [4] COMP_MODE: Comparator mode (ADS1114 and ADS1115 only)
    This bit controls the comparator mode of operation. It changes whether the comparator is implemented as a
    traditional comparator (COMP_MODE = '0') or as a window comparator (COMP_MODE = '1'). It serves no
    function on the ADS1113.
    0 : Traditional comparator with hysteresis (default)
    1 : Window comparator
*/
  if (config&(1<<4)) {
    txt = "COMP_MODE 1 : Window comparator\r\n";
  } else {
    txt = "COMP_MODE 0 : Traditional comparator with hysteresis (default)\r\n";
  }
  McuShell_printfIO(io, txt);
/*
    Bit [3] COMP_POL: Comparator polarity (ADS1114 and ADS1115 only)
    This bit controls the polarity of the ALERT/RDY pin. When COMP_POL = '0' the comparator output is active
    low. When COMP_POL='1' the ALERT/RDY pin is active high. It serves no function on the ADS1113.
    0 : Active low (default)
    1 : Active high
*/
  if (config&(1<<3)) {
    txt = "COMP_POL 1  : Active high\r\n";
  } else {
    txt = "COMP_POL 0  : Active low (default)\r\n";
  }
  McuShell_printfIO(io, txt);
/*
    Bit [2] COMP_LAT: Latching comparator (ADS1114 and ADS1115 only)
    This bit controls whether the ALERT/RDY pin latches once asserted or clears once conversions are within the
    margin of the upper and lower threshold values. When COMP_LAT = '0', the ALERT/RDY pin does not latch
    when asserted. When COMP_LAT = '1', the asserted ALERT/RDY pin remains latched until conversion data
    are read by the master or an appropriate SMBus alert response is sent by the master, the device responds with
    its address, and it is the lowest address currently asserting the ALERT/RDY bus line. This bit serves no
    function on the ADS1113.
    0 : Non-latching comparator (default)
    1 : Latching comparator
*/
  if (config&(1<<3)) {
    txt = "COMP_LAT 1  : Latching comparator\r\n";
  } else {
    txt = "COMP_LAT 0  : Non-latching comparator (default)\r\n";
  }
  McuShell_printfIO(io, txt);
/*
    Bits [1:0] COMP_QUE: Comparator queue and disable (ADS1114 and ADS1115 only)
    These bits perform two functions. When set to '11', they disable the comparator function and put the
    ALERT/RDY pin into a high state. When set to any other value, they control the number of successive
    conversions exceeding the upper or lower thresholds required before asserting the ALERT/RDY pin. They
    serve no function on the ADS1113.
    00 : Assert after one conversion
    01 : Assert after two conversions
    10 : Assert after four conversions
    11 : Disable comparator (default)
*/
  switch(config&0b11) {
    case 0b00: txt = "COMP_QUE 00 : Assert after one conversion\r\n"; break;
    case 0b01: txt = "COMP_QUE 01 : Assert after two conversions\r\n"; break;
    case 0b10: txt = "COMP_QUE 10 : Assert after four conversions\r\n"; break;
    case 0b11: txt = "COMP_QUE 11 : Disable comparator (default)\r\n"; break;
    default: txt = "COMP_QUE error\r\n"; break;
  }
  McuShell_printfIO(io, txt);
  return ERR_OK;
}

#if McuADS1115_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint16_t value;
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"McuADS1115", (unsigned char*)"ADS1115 sensor status\r\n", io->stdOut);
  if (McuADS1115_ReadConfig(&value)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "failed\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  config", buf, io->stdOut);

  if (McuADS1115_ReadLowThreshold(&value)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "failed\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Lo_thres", buf, io->stdOut);

  if (McuADS1115_ReadHighThreshold(&value)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "failed\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Hi_thres", buf, io->stdOut);

  if (McuADS1115_ReadConversionRaw(&value)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "failed\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Conversion", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuADS1115", (unsigned char*)"Group of ADS1115 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  printconfig", (unsigned char*)"Print configuration register status\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  mode single|cont", (unsigned char*)"Set single-shot or continuous conversion mode\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  singleshot", (unsigned char*)"Perform a single shot conversion\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  mux <val>", (unsigned char*)"Write the 3 MUX bits into the config register\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  test", (unsigned char*)"test\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuADS1115_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  int32_t val;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "McuADS1115 help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "McuADS1115 status")==0)
            )
  {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuADS1115 printconfig")==0) {
    *handled = true;
    return McuADS1115_PrintConfig(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuADS1115 mode single")==0) {
    *handled = true;
    return McuADS1115_SetConversionModeSingle(true);
  } else if (McuUtility_strcmp((char*)cmd, "McuADS1115 mode cont")==0) {
    *handled = true;
    return McuADS1115_SetConversionModeSingle(false);
  } else if (McuUtility_strcmp((char*)cmd, "McuADS1115 singleshot")==0) {
    *handled = true;
    return McuADS1115_SingleShot();
  } else if (McuUtility_strncmp((char*)cmd, "McuADS1115 mux ", sizeof("McuADS1115 mux ")-1)==0) {
    *handled = true;
    p += sizeof("McuADS1115 mux ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (val<0 || val>0b111) {
      return ERR_RANGE;
    }
    return McuADS1115_WriteMux(val);
  } else if (McuUtility_strcmp((char*)cmd, "McuADS1115 test")==0) {
    *handled = true;
    return McuADS1115_Test();
  }
  return ERR_OK;
}
#endif /* McuADS1115_CONFIG_PARSE_COMMAND_ENABLED */


void McuADS1115_Init(void) {}

void McuADS1115_Deinit(void) {}
