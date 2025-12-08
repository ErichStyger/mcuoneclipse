/**
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * \brief Driver for the TI INA229 SPI current/voltage sensor.
 */

#include "McuINA229.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuSPI.h"
#include "McuGPIO.h"
#include <stdint.h>
#include <math.h>

typedef enum {
  McuINA229_REG_CONFIG            = 0x00,
  McuINA229_REG_ADC_CONFIG        = 0x01,
  McuINA229_REG_SHUNT_CAL         = 0x02,
  McuINA229_REG_SHUNT_TEMPCO      = 0x03,
  McuINA229_REG_VSHUNT            = 0x04,
  McuINA229_REG_VBUS              = 0x05,
  McuINA229_REG_DIETEMP           = 0x06,
  McuINA229_REG_CURRENT           = 0x07,
  McuINA229_REG_POWER             = 0x08,
  McuINA229_REG_ENERGY            = 0x09,
  McuINA229_REG_CHARGE            = 0x0A,
  McuINA229_REG_DIAG_ALRT         = 0x0B,
  McuINA229_REG_SOVL              = 0x0C,
  McuINA229_REG_SUVL              = 0x0D,
  McuINA229_REG_BOVL              = 0x0E,
  McuINA229_REG_BUVL              = 0x0F,
  McuINA229_REG_TEMP_LIMIT        = 0x10,
  McuINA229_REG_PWRE_LIMIT        = 0x11,
  McuINA229_REG_MANUFACTURER_ID   = 0x3E,
  McuINA229_REG_DEVICE_ID         = 0x3F,
} McuINA229_REG_e;

typedef enum McuINA229_ADC_RANGE_e {
  /* ADCRANGE (1bit) in McuINA229_REG_CONFIG */
  McuINA229_ADC_RANGE_163dot84_mv = 0,
  McuINA229_ADC_RANGE_40dot96_mv = 1,
} McuINA229_ADC_RANGE_e;

static struct { /* The INA229 uses SPI MODE 1 (CPOL = 0, CPHA = 1) */
#if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
  McuGPIO_Handle_t cs; /* chip select (output) pin, LOW active */
#endif
#if McuINA229_CONFIG_ALERT_PIN_NUMBER!=-1
  McuGPIO_Handle_t alert; /* alert (innput) pin, default state is active LOW */
#endif
  float shuntResistance; /* resistance value of the shunt resistor */
  float maxCurrent; /* maximum expeted current */
  float currentLSB; /* LSB of current, based on maxCurrent and 19 bit resolution */
} device;

static void SPI_Select(void) {
  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_SetLow(device.cs);
  #endif
}

static void SPI_Unselect(void) {
  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_SetHigh(device.cs);
  #endif
}

static uint8_t SPI_CmdReadBytes2(uint8_t reg, uint16_t *data) {
  uint8_t tx[3], rx[3], res;

  tx[0] = (reg<<2) | 1; /* command: 6bit register address, a zero bit plus 1 bit with one for reading */
  tx[1] = 0;
  tx[2] = 0;
  rx[0] = 0;
  rx[1] = 0;
  rx[2] = 0;
  res = McuSPI_SendReceiveBlock(tx, rx, sizeof(tx)); /* send command and receive data */
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  *data = (rx[1]<<8) | rx[2]; /* return 16bit value we have read */
  return ERR_OK;
}

static uint8_t SPI_CmdReadBytes3(uint8_t reg, uint32_t *data) {
  uint8_t tx[4], rx[4], res;

  tx[0] = (reg<<2) | 1; /* command: 6bit register address, a zero bit plus 1 bit with one for reading */
  tx[1] = 0;
  tx[2] = 0;
  tx[3] = 0;
  rx[0] = 0;
  rx[1] = 0;
  rx[2] = 0;
  rx[3] = 0;
  res = McuSPI_SendReceiveBlock(tx, rx, sizeof(tx)); /* send command and receive data */
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  *data = (rx[1]<<16) | (rx[2]<<8) | rx[3]; /* return 24it value we have read */
  return ERR_OK;
}

static uint8_t SPI_CmdReadBytes5(uint8_t reg, uint64_t *data) {
  uint8_t tx[6], rx[6], res;

  tx[0] = (reg<<2) | 1; /* command: 6bit register address, a zero bit plus 1 bit with one for reading */
  tx[1] = 0;
  tx[2] = 0;
  tx[3] = 0;
  tx[4] = 0;
  tx[5] = 0;
  rx[0] = 0;
  rx[1] = 0;
  rx[2] = 0;
  rx[3] = 0;
  rx[4] = 0;
  rx[5] = 0;
  res = McuSPI_SendReceiveBlock(tx, rx, sizeof(tx)); /* send command and receive data */
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  *data = (((uint64_t)rx[1])<<32) | (rx[2]<<24) | (rx[3]<<16) | (rx[4]<<8) | rx[5]; /* return 40it value we have read */
  return ERR_OK;
}

static uint8_t SPI_CmdWriteBytes2(uint8_t reg, uint16_t data) {
  uint8_t tx[3], rx[3], res;

  tx[0] = (reg<<2); /* command: 6bit register address, a zero byte plus 1 bit with zero for writing */
  tx[1] = data<<8;  /* data high byte */
  tx[2] = data;     /* data low byte */
  res = McuSPI_SendReceiveBlock(tx, rx, sizeof(tx)); /* send command and receive data */
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  return ERR_OK;
}

static uint8_t McuINA229_WriteConfig(uint16_t data) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdWriteBytes2(McuINA229_REG_CONFIG, data);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_WriteADCConfig(uint16_t data) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdWriteBytes2(McuINA229_REG_ADC_CONFIG, data);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_WriteShuntCal(uint16_t data) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdWriteBytes2(McuINA229_REG_SHUNT_CAL, data);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_WriteShuntTempCoefficient(uint16_t data) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdWriteBytes2(McuINA229_REG_SHUNT_TEMPCO, data);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadManufacturerID(uint16_t *id) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_MANUFACTURER_ID, id);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadDeviceID(uint16_t *id) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_DEVICE_ID, id);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadConfig(uint16_t *config) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_CONFIG, config);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadAdcRange(McuINA229_ADC_RANGE_e *range) {
  uint8_t res;
  uint16_t config;

  res = McuINA229_ReadConfig(&config);
  if (res!=ERR_OK) {
    return res;
  }
  if (config&(1<<4)) {
    *range = McuINA229_ADC_RANGE_163dot84_mv; /* bit 1: +/- 40.96 mV */
  } else {
    *range = McuINA229_ADC_RANGE_40dot96_mv; /* bit 0: +/- 163.84 mV */
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadCurrent(float *current_mA) {
  uint8_t res;
  int32_t val;
  float current;

  SPI_Select();
  res = SPI_CmdReadBytes3(McuINA229_REG_CURRENT, &val);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  val >>= 4; /* lowest 4 bits are reserved and always zero */
  /* handle negative value */
  if (val&0x80000) {
    val |= 0xFFF00000;
  }
  current = val*device.currentLSB;
  *current_mA = current*1000.0f;
  return ERR_OK;
}

static uint8_t McuINA229_ReadPower(float *power_mW) {
  uint8_t res;
  uint32_t val;
  float power;

  SPI_Select();
  res = SPI_CmdReadBytes3(McuINA229_REG_POWER, &val);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  power = val*3.2f*device.currentLSB;
  *power_mW = power*1000.0f;
  return ERR_OK;
}

static uint8_t McuINA229_ReadEnergy(double *value_mWh) {
  uint8_t res;
  uint64_t val;
  double energy;

  SPI_Select();
  res = SPI_CmdReadBytes5(McuINA229_REG_ENERGY, &val);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  energy = val * (16.0*3.2) * device.currentLSB;
  *value_mWh = energy;
  return ERR_OK;
}

static uint8_t McuINA229_ReadCharge(int16_t *value) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_CHARGE, value);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadAdcConfig(int16_t *value) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_ADC_CONFIG, value);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadShuntCal(int16_t *value) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_SHUNT_CAL, value);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadShuntTempCoefficient(int16_t *value) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_SHUNT_TEMPCO, value);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadVShunt(int32_t *value_nV) {
  uint8_t res;
  int32_t val;

  SPI_Select();
  res = SPI_CmdReadBytes3(McuINA229_REG_VSHUNT, &val);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  /* handle negative value */
  if (val&0x80000) {
    val |= 0xFFF00000;
  }

  McuINA229_ADC_RANGE_e range;
  res = McuINA229_ReadAdcRange(&range);
  if (res!=ERR_OK) {
    return res;
  }
  int32_t nV;
  if (range==McuINA229_ADC_RANGE_163dot84_mv) { /* ADCRANGE=0 */
    nV = val * 312.5f; /* 312.5 nV/LSB */
  } else {
    nV = val * 78.125f; /* 78.125 nV/LSB */
  }
  *value_nV = nV;
  return ERR_OK;
}

static uint8_t McuINA229_ReadVBus(int32_t *value_uV) {
  uint8_t res;
  uint32_t val;

  SPI_Select();
  res = SPI_CmdReadBytes3(McuINA229_REG_VBUS, &val);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  val >>= 4; /* lowest 4 bits are reserved and always zero */
  int32_t uV = val * 195.3125f; /* 195.3125 uV/LSB */
  *value_uV = uV;
  return ERR_OK;
}

static uint8_t McuINA229_ReadDieTemp(int32_t *val_mC) {
  uint8_t res;
  uint16_t val;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_DIETEMP, &val);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  int32_t mC = val * 7.815f; /* 7.8125 mCelsius/LSB */
  *val_mC = mC;
  return ERR_OK;
}

static uint8_t McuINA229_ReadDiagAlert(int16_t *value) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_DIAG_ALRT, value);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

#if McuINA229_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint16_t val16u;
  int16_t val16s;
  int32_t val32s;
  unsigned char buf[64];
  float f;

  McuUtility_NumFloatToStr(buf, sizeof(buf), McuINA229_CONFIG_SHUNT_RESISTOR_R, 3);
  McuUtility_strcat(buf, sizeof(buf), " R, max ");
  McuUtility_strcatNumFloat(buf, sizeof(buf), McuINA229_CONFIG_MAX_CURRENT_A, 2);
  McuUtility_strcat(buf, sizeof(buf), " A\r\n");
  McuShell_SendStatusStr((unsigned char*)"  shunt", buf, io->stdOut);

  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_GetPinStatusString(device.cs, buf, sizeof(buf));
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
    McuShell_SendStatusStr((unsigned char*)"  CS", buf, io->stdOut);
  #endif

  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_GetPinStatusString(device.alert, buf, sizeof(buf));
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
    McuShell_SendStatusStr((unsigned char*)"  ALERT", buf, io->stdOut);
  #endif

  if (McuINA229_ReadConfig(&val16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), val16u);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  config", buf, io->stdOut);

  if (McuINA229_ReadAdcConfig(&val16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), val16u);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  ADC config", buf, io->stdOut);

  if (McuINA229_ReadShuntCal(&val16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), val16u);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Shunt Cal", buf, io->stdOut);

  if (McuINA229_ReadShuntTempCoefficient(&val16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "");
    McuUtility_strcatNum16u(buf, sizeof(buf), val16u);
    McuUtility_strcat(buf, sizeof(buf), " ppm/C\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Shunt Temp", buf, io->stdOut);

  if (McuINA229_ReadVShunt(&val32s)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "");
    McuUtility_strcatNum32sDotValue1000(buf, sizeof(buf), val32s);
    McuUtility_strcat(buf, sizeof(buf), " mV\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  V Shunt", buf, io->stdOut);

  if (McuINA229_ReadVBus(&val32s)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "");
    McuUtility_strcatNum32sDotValue1000(buf, sizeof(buf), val32s);
    McuUtility_strcat(buf, sizeof(buf), " mV\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  V Bus", buf, io->stdOut);

  if (McuINA229_ReadDieTemp(&val32s)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "");
    McuUtility_strcatNum32sDotValue1000(buf, sizeof(buf), val16s);
    McuUtility_strcat(buf, sizeof(buf), " C\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Die Temp", buf, io->stdOut);

  if (McuINA229_ReadCurrent(&f)==ERR_OK) {
    McuUtility_NumFloatToStr(buf, sizeof(buf), f, 3);
    McuUtility_strcat(buf, sizeof(buf), " mA\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  current", buf, io->stdOut);

  if (McuINA229_ReadPower(&f)==ERR_OK) {
    McuUtility_NumFloatToStr(buf, sizeof(buf), f, 3);
    McuUtility_strcat(buf, sizeof(buf), " mW\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  power", buf, io->stdOut);

  double d;
  if (McuINA229_ReadEnergy(&d)==ERR_OK) {
    McuUtility_NumFloatToStr(buf, sizeof(buf), d, 3); /* \todo use double function */
    McuUtility_strcat(buf, sizeof(buf), " mWh\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  energy", buf, io->stdOut);

  if (McuINA229_ReadCharge(&val16s)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "");
    McuUtility_strcatNum16s(buf, sizeof(buf), val16s);
    McuUtility_strcat(buf, sizeof(buf), " C\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  charge", buf, io->stdOut);
  
  if (McuINA229_ReadDiagAlert(&val16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16s(buf, sizeof(buf), val16u);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  diag/alert", buf, io->stdOut);

  if (McuINA229_ReadManufacturerID(&val16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), val16u);
    McuUtility_chcat(buf, sizeof(buf), ' ');
    McuUtility_chcat(buf, sizeof(buf), (char)(val16u>>8));
    McuUtility_chcat(buf, sizeof(buf), (char)(val16u));
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  manuf.-ID", buf, io->stdOut);

  if (McuINA229_ReadDeviceID(&val16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), val16u);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  device ID", buf, io->stdOut);
  
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuINA229", (unsigned char*)"Group of INA229 sensor commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  config <val>", (unsigned char*)"Write value into config register\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  ADC config <val>", (unsigned char*)"Write value into ADC config register\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  shunt cal <val>", (unsigned char*)"Write value into shunt calibration register\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  shunt tempco <val>", (unsigned char*)"Write value into shunt temperature coefficient register\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuINA229_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;
  int32_t val;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "McuINA229 help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "McuINA229 status")==0)
            )
  {
    *handled = true;
    res = PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "McuINA229 config ", sizeof("McuINA229 config ")-1)==0) {
    *handled = true;
    p += sizeof("McuINA229 config ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuINA229_WriteConfig(val);
  } else if (McuUtility_strncmp((char*)cmd, "McuINA229 ADC config ", sizeof("McuINA229 ADC config ")-1)==0) {
    *handled = true;
    p += sizeof("McuINA229 ADC config ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuINA229_WriteADCConfig(val);
  } else if (McuUtility_strncmp((char*)cmd, "McuINA229 shunt cal ", sizeof("McuINA229 shunt cal ")-1)==0) {
    *handled = true;
    p += sizeof("McuINA229 shunt cal ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuINA229_WriteShuntCal(val);
  } else if (McuUtility_strncmp((char*)cmd, "McuINA229 shunt tempco ", sizeof("McuINA229 shunt tempco ")-1)==0) {
    *handled = true;
    p += sizeof("McuINA229 shunt tempco ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuINA229_WriteShuntTempCoefficient(val);
  }
  return res;
}
#endif /* McuINA229_CONFIG_PARSE_COMMAND_ENABLED */

void McuINA229_Deinit(void) {
  /* nothing needed */
}

void McuINA229_Init(void) {
  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_Config_t config_cs;

    McuGPIO_GetDefaultConfig(&config_cs);
    config_cs.isInput = false;
    config_cs.isHighOnInit = true; /* CS is active LOW */
    config_cs.hw.pin = McuINA229_CONFIG_CS_PIN_NUMBER;
    device.cs = McuGPIO_InitGPIO(&config_cs);
    if (device.cs==NULL) {
      McuLog_fatal("failed initializing CS pin");
      for(;;){}
    }
  #endif
  #if McuINA229_CONFIG_ALERT_PIN_NUMBER!=-1
    McuGPIO_Config_t config_alert;

    McuGPIO_GetDefaultConfig(&config_alert);
    config_alert.isInput = true;
    config_alert.hw.pin = McuINA229_CONFIG_ALERT_PIN_NUMBER;
    config_alert.hw.pull = McuGPIO_PULL_DISABLE;
    device.alert = McuGPIO_InitGPIO(&config_alert);
    if (device.alert==NULL) {
      McuLog_fatal("failed initializing ALERT pin");
      for(;;){}
    }
  #endif
  device.shuntResistance = McuINA229_CONFIG_SHUNT_RESISTOR_R;
  device.maxCurrent = McuINA229_CONFIG_MAX_CURRENT_A;
  device.currentLSB = McuINA229_CONFIG_MAX_CURRENT_A * pow(2, -19); /* 19 because we have a 20bit ADC */
}
