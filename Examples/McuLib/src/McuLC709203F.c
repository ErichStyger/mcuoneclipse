/*
 * Copyright (c) 2019, Erich Styger, Sarah Gander
 * All rights reserved.
 *
 * Driver for GPIO pins
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#if McuLib_CONFIG_CPU_IS_STM
  #include "libIIC.h"
#endif
#include "McuLC709203Fconfig.h"
#include "McuLC709203F.h"
#include "McuGenericI2C.h"
#include "McuUtility.h"
#include "McuWait.h"

#define LC709203F_I2C_SLAVE_ADDR  0x0B

#define LC709203F_REG_SET_BEFORE_RSOC   0x04  /* Before RSCOC */
#define LC709203F_REG_SET_THERMB        0x06  /* Thermistor B */
#define LC709203F_REG_INIT_RSOC         0x07  /* Initial RSOC */
#define LC709203F_REG_CELL_TEMP         0x08  /* Cell temperature */
#define LC709203F_REG_VOLTAGE           0x09  /* Cell voltage */
#define LC709203F_REG_CURRENT_DIRECTION 0x0A  /* Current direction */
#define LC709203F_REG_ADJ_APPLI         0x0B  /* APA, Adjustment Pack Application, sets Parasitic impedance */
#define LC709203F_REG_APT               0x0C  /* APT, Adjustment Pack Thermistor, adjust temperature measurement delay timing */
#define LC709203F_REG_RSOC              0x0D  /* RSOC, value based 0-100 scale */
#define LC709203F_REG_ITE               0x0F  /* ITE, Indicator to Empty */
#define LC709203F_REG_IC_VER            0x11  /* IC version */
#define LC709203F_REG_CHG_PARAM         0x12  /* change of parameter */
#define LC709203F_REG_RSOC_ALM          0x13  /* Alarm low RSOC */
#define LC709203F_REG_LOW_CELL_VOL_ALM  0x14  /* Alarm Low Cell Voltage */
#define lC709203F_REG_PW_MODE           0x15  /* IC Power Mode */
#define LC709203F_REG_EN_NTC            0x16  /* Status Bit, enable Thermistor mode */
#define LC709203F_REG_NUM_PARAMS        0x1A  /* Number of the parameter, display batter profile code */

#define MCULC_TEMP_ZERO_CELSIUS    0x0AAC /* From the data sheet command table: 0x0AAC is 0 degree Celsius */

static uint8_t i2cReadCmdData(uint8_t i2cAddr, uint8_t cmd, uint8_t *data, size_t length) {
	return McuGenericI2C_ReadAddress(i2cAddr, &cmd, sizeof(cmd), data, length);
}

static uint8_t i2cWriteCmdData(uint8_t i2cAddr, uint8_t cmd, uint8_t *data, size_t length) {
	return McuGenericI2C_WriteAddress(i2cAddr, &cmd, sizeof(cmd), data, length);
}

static uint8_t calcCrc8Atm(uint8_t a, uint8_t b) {
  /* the sensor uses a CRC-8-ATM,
   * Polynomial: x8 + x2 + x + 1
   * Corresponds to: 100000111
   */
  #define POLY_8  0x8380
  uint8_t i = 0;
  uint16_t val = 0;

  val = (uint16_t)(a^b);
  val <<= 8;
  for(i=0; i<8; i++) {
    if (val&0x8000 ){
      val ^= POLY_8;
    }
    val <<= 1;
  }
  return (uint8_t)(val >> 8);
}

static uint8_t calcCRC_WriteAccess16(uint8_t i2cSlaveAddr, uint8_t cmd, uint8_t low, uint8_t high) {
  uint8_t crc;

  crc = calcCrc8Atm(0x00, i2cSlaveAddr<<1); /* I2C slave address */
  crc = calcCrc8Atm(crc, cmd);              /* command */
  crc = calcCrc8Atm(crc, low);              /* data byte */
  return calcCrc8Atm(crc, high);            /* data byte */
}

static uint8_t calcCRC_ReadAccess16(uint8_t i2cSlaveAddr, uint8_t cmd, uint8_t low, uint8_t high) {
  uint8_t crc;

  crc = calcCrc8Atm(0x00, i2cSlaveAddr<<1);     /* I2C slave address */
  crc = calcCrc8Atm(crc, cmd);                  /* command */
  crc = calcCrc8Atm(crc, (i2cSlaveAddr<<1)|1);  /* I2C address with R bit set */
  crc = calcCrc8Atm(crc, low);                  /* data byte */
  return calcCrc8Atm(crc, high);                /* data byte */
}

static uint8_t CheckCrc(uint8_t i2cSlaveAddr, uint8_t cmd, uint8_t low, uint8_t high, uint8_t crc) {
  uint8_t val;

  val = calcCRC_ReadAccess16(i2cSlaveAddr, cmd, low, high);
  if (val != crc) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

static uint8_t CheckI2CErr(uint8_t res) {
  if (res==ERR_OK) {
    return ERR_OK; /* ok */
  }
#if MCULC_CONFIG_BLOCK_ON_I2C_ERROR
  for(;;) { /* I2C Error? wait for the watchdog to kick in... */
    McuWait_WaitOSms(50);
  }
#endif
  return ERR_FAILED;
}

static uint8_t WriteCmdWordChecked(uint8_t i2cSlaveAddr, uint8_t cmd, uint8_t low, uint8_t high) {
  uint8_t data[3];

  data[0] = low;
  data[1] = high;
  data[2] = calcCRC_WriteAccess16(i2cSlaveAddr, cmd, data[0], data[1]);
  return CheckI2CErr(i2cWriteCmdData(i2cSlaveAddr, cmd, data, sizeof(data)));
}

void McuLC_Wakeup(void) {
  /* Generates wake up signal on SDA, according to the data sheet.
   * This has to happen before any other I2C communication on the bus:
   * Pull down SDA for 0.6us, then high again,
   * wait for 400 us
   *  */
#if McuLib_CONFIG_CPU_IS_STM
	/* set SDA pin of I2C to GPIO Output mode. */
	HAL_I2C_MspDeInit(&hi2c3);
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port, I2C_SDA_Pin, GPIO_PIN_RESET);
  McuWait_Waitus(1);		/* SDA min 0.6us low */
	HAL_GPIO_WritePin(I2C_SDA_GPIO_Port, I2C_SDA_Pin, GPIO_PIN_SET);
	McuWait_Waitus(400);  	/* wait 400us */
	/* set SDA pin of I2C to GPIO Ouput mode. */
	HAL_I2C_MspInit(&hi2c3);
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_PROCESSOR_EXPERT
  PORT_PDD_SetPinMuxControl(PORTB_BASE_PTR, 3, PORT_PDD_MUX_CONTROL_ALT1); /* MUX SDA/PTB3 as GPIO */
  PORT_PDD_SetPinOpenDrain(PORTB_BASE_PTR, 3, PORT_PDD_OPEN_DRAIN_ENABLE);
  GPIO_PDD_SetPortOutputDirectionMask(PTB_BASE_PTR, (1<<3)); /* SDA/PTB3 as output */
  GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR, 1<<3); /* SDA/PB3 low */
  McuWait_Waitus(1);                                        /* SDA min 0.6us low */
  GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR, 1<<3);   /* SDA/PB3 high */
  McuWait_Waitus(400);                                      /* wait 400us */
  /* mux back to normal I2C mode with interrupts enabled */
  PORTB_PCR3 = (uint32_t)((PORTB_PCR3 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  PORT_PDD_SetPinOpenDrain(PORTB_BASE_PTR, 0x03u, PORT_PDD_OPEN_DRAIN_ENABLE); /* Set SDA pin as open drain */
#else
  /* NYI for NXP SDK yet */
#endif
}

static uint8_t ReadCmdWordChecked(uint8_t i2cSlaveAddr, uint8_t cmd, uint16_t *val) {
  uint8_t data[3];
  uint8_t res;

  res = CheckI2CErr(i2cReadCmdData(i2cSlaveAddr, cmd, data, sizeof(data)));
  if (res!=ERR_OK) {
    return res;
  }
  res = CheckI2CErr(CheckCrc(i2cSlaveAddr, cmd, data[0], data[1], data[2]));
  if (res!=ERR_OK) {
    return res;
  }
  *val = (data[1]<<8) | data[0];
  return ERR_OK;
}

/* returns cell voltage in mV */
uint8_t McuLC_GetVoltage(uint16_t *pVoltage) {
  return ReadCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_VOLTAGE, pVoltage);
}

/* returns cell temperature (10 = 1 degree C) */
uint8_t McuLC_GetTemperature(int16_t *pTemperature) {
  /* cell temperature is in 0.1C units, from 0x09E4 (-20C) up to 0x0D04 (60C) */
  uint8_t res;

  res = ReadCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_CELL_TEMP, (uint16_t*)pTemperature);
  if (res!=ERR_OK) {
     return res;
   }
  *pTemperature -= MCULC_TEMP_ZERO_CELSIUS; /* From the data sheet command table: 0x0AAC is 0 degree Celsius */
  return ERR_OK;
}

uint8_t McuLC_SetTemperature(int16_t temperature) {
  /* cell temperature is in 0.1C units, from 0x09E4 (-20C) up to 0x0D04 (60C) */
  temperature = ((uint16_t)temperature)+MCULC_TEMP_ZERO_CELSIUS; /* From the data sheet command table: 0x0AAC is 0 degree Celsius */
  return WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_CELL_TEMP, ((uint16_t)temperature)&0xff, (((uint16_t)temperature)>>8)&0xff);
}

/* returns battery Relative State of Charge in percent */
uint8_t McuLC_GetRSOC(uint16_t *pRsoc) {
  return ReadCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_RSOC, pRsoc);
}

/* Indicator to empty, returns battery charge in thousandth */
uint8_t McuLC_GetITE(uint16_t *pIte) {
  return ReadCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_ITE, pIte);
}

/* Indicator to empty, returns battery charge in thousandth */
uint8_t McuLC_GetICversion(uint16_t *pVersion) {
  return ReadCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_IC_VER, pVersion);
}

#if MCULC709203F_CONFIG_PARSE_COMMAND_ENABLED
static const unsigned char *McuLC_CurrentDirectionToString(McuLC_CurrentDirection dir) {
  switch(dir) {
    case McuLC_CURRENT_DIR_AUTO:       return (const unsigned char*)"auto";
    case McuLC_CURRENT_DIR_CHARGING:   return (const unsigned char*)"charging";
    case McuLC_CURRENT_DIR_DISCHARING: return (const unsigned char*)"discharging";
    case McuLC_CURRENT_DIR_ERROR:
    default:                           return (const unsigned char*)"ERROR";
  }
}
#endif

uint8_t McuLC_GetCurrentDirection(McuLC_CurrentDirection *pDir) {
  uint16_t val;
  uint8_t res;

  res = ReadCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_CURRENT_DIRECTION, &val);
  if (res!=ERR_OK) {
    return res;
  }
  switch(val) {
    case 0:         *pDir = McuLC_CURRENT_DIR_AUTO; break;
    case 1:         return McuLC_CURRENT_DIR_CHARGING; break;
    case 0xffff:    return McuLC_CURRENT_DIR_DISCHARING; break;
    default:        return McuLC_CURRENT_DIR_ERROR; break;
  }
  return ERR_OK;
}

uint8_t McuLC_SetCurrentDirection(McuLC_CurrentDirection direction) {
  uint8_t low, high;

  switch(direction) {
    case McuLC_CURRENT_DIR_AUTO:        low = 0x00; high = 0x00; break;
    case McuLC_CURRENT_DIR_CHARGING:    low = 0x01; high = 0x00; break;
    case McuLC_CURRENT_DIR_DISCHARING:  low = 0xff; high = 0xff; break;
    default:
      CheckI2CErr(ERR_FAILED);
      return ERR_FAILED;
  }
  return WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_CURRENT_DIRECTION, low, high);
}

#if MCULC709203F_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[32], res;

  McuShell_SendStatusStr((unsigned char*)"LC", (const unsigned char*)"\r\n", io->stdOut);
  {
    uint16_t version;

    res = McuLC_GetICversion(&version); /* battery charge in thousandth */
    if (res==ERR_OK) {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
      McuUtility_strcatNum16Hex(buf, sizeof(buf), version);
      McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
    } else {
    	McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
    }
    McuShell_SendStatusStr((unsigned char*)"  IC version", buf, io->stdOut);
  }
  {
    uint16_t rsoc;

    res = McuLC_GetRSOC(&rsoc); /* battery charge in percent */
    if (res==ERR_OK) {
      McuUtility_Num16uToStr(buf, sizeof(buf), rsoc);
      McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)"\% (0..100)\r\n");
    } else {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
    }
    McuShell_SendStatusStr((unsigned char*)"  RSOC", buf, io->stdOut);
  }
  {
    uint16_t ite;

    res = McuLC_GetITE(&ite); /* battery charge in thousandth */
    if (res==ERR_OK) {
      McuUtility_Num16uToStr(buf, sizeof(buf), ite);
      McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (0..1000)\r\n");
    } else {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
    }
    McuShell_SendStatusStr((unsigned char*)"  ITE", buf, io->stdOut);
  }
  {
    int16_t temperature;
    bool isI2Cmode;

    res = McuLC_GetTemperature(&temperature); /* cell temperature in 1/10-degree C */
    if (res==ERR_OK) {
      McuUtility_Num16sToStr(buf, sizeof(buf), temperature/10);
      McuUtility_chcat(buf, sizeof(buf), '.');
      if (temperature<0) { /* make it positive */
        temperature = -temperature;
      }
      McuUtility_strcatNum16s(buf, sizeof(buf), temperature%10);
      McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" C");
    } else {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR");
    }
    if (McuLC_GetTemperatureMeasurementMode(&isI2Cmode)==ERR_OK) {
      if (isI2Cmode) {
        McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (I2C mode)");
      } else {
        McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (Thermistor mode)");
      }
    } else {
      McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" (ERROR!)");
    }
    McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
    McuShell_SendStatusStr((unsigned char*)"  Temperature", buf, io->stdOut);
  }
  {
    uint16_t mVolt;

    res = McuLC_GetVoltage(&mVolt); /* cell voltage in milli-volts */
    if (res==ERR_OK) {
      McuUtility_Num16uToStr(buf, sizeof(buf), mVolt);
      McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" mV\r\n");
    } else {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
    }
    McuShell_SendStatusStr((unsigned char*)"  Voltage", buf, io->stdOut);
  }
  {
    McuLC_CurrentDirection direction;

    res = McuLC_GetCurrentDirection(&direction);
    if (res==ERR_OK) {
      McuUtility_strcpy(buf, sizeof(buf), McuLC_CurrentDirectionToString(direction));
      McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
    } else {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
    }
    McuShell_SendStatusStr((unsigned char*)"  Current dir", buf, io->stdOut);
  }
  return ERR_OK;
}
#endif /* MCULC709203F_CONFIG_PARSE_COMMAND_ENABLED */

#if MCULC709203F_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuLC_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;
  const uint8_t *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "LC help")==0) {
    McuShell_SendHelpStr((unsigned char*)"LC", (const unsigned char*)"Group of LC709203F commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  settemp <temp>", (const unsigned char*)"In I2C temperature mode, set the temperature in deci-Celsius\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "LC status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, (char*)"LC settemp ", sizeof("LC settemp ")-1)==0) {
    int16_t val;

    *handled = TRUE;
    p = cmd+sizeof("LC settemp ")-1;
    if (McuUtility_ScanDecimal16sNumber(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuLC_SetTemperature(val);
  }
  return res;
}
#endif /* MCULC709203F_CONFIG_PARSE_COMMAND_ENABLED */

uint8_t McuLC_GetTemperatureMeasurementMode(bool *isI2Cmode) {
  uint16_t val=0;
  uint8_t res;

  res = ReadCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_EN_NTC, &val);
  if (res!=ERR_OK) {
    return res;
  }
  *isI2Cmode = val==0; /* 0: i2c, 1: thermistor mode */
  return ERR_OK;
}

uint8_t McuLC_SetTemperatureMeasurementMode(bool i2cMode) {
  return WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_EN_NTC, i2cMode?0x00:0x01, 0x0);
}

uint8_t McuLC_SetPowerMode(bool sleepMode) {
  return WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, lC709203F_REG_PW_MODE, sleepMode?0x02:0x01, 0x00);
}

uint8_t McuLC_Init(void) {
  /* initializes LC709203F for Renata ICP543759PMT battery */
  uint8_t res;

  /* operational mode (1: operational, 2: sleep), 0x0001 = operational mode */
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, lC709203F_REG_PW_MODE, 0x01, 0x00);
  if (res!=ERR_OK) { return ERR_FAILED; }

  /* APA, set parasitic impedance (table 7 in data sheet): 0x000C, value for 280mA */
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_ADJ_APPLI, 0x0C, 0x00);
  if (res!=ERR_OK) { return ERR_FAILED; }

  /* Battery Profile (table 8 in data sheet): 0x0001 = Type 1 */
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_CHG_PARAM, 0x01, 0x00);
  if (res!=ERR_OK) { return ERR_FAILED; }

  /* write 0xAA55 to initialize RSOC */
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_INIT_RSOC, 0x55, 0xAA);
  if (res!=ERR_OK) { return ERR_FAILED; }

  /* Set battery measurement mode: 0x0001: thermistor mode. 0x0000: I2C mode */
#if MCULC709203F_CONFIG_USE_THERMISTOR
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_EN_NTC, 0x01, 0x00);
  if (res!=ERR_OK) { return ERR_FAILED; }
#else
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_EN_NTC, 0x00, 0x00);
  if (res!=ERR_OK) { return ERR_FAILED; }
#endif
  /* set the B-constant of the thermistor to be measured */
#if MCULC709203F_CONFIG_USE_THERMISTOR
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_SET_THERMB, 0x6B, 0x0D); /* Thermistor B-Constant: 0x0D6B = B=3435 */
  if (res!=ERR_OK) { return ERR_FAILED; }
#endif

  /* Low voltage alarm setting: 0x0C1C = 3100mV = 3.1V, low byte first */
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_LOW_CELL_VOL_ALM, 0x1C, 0x0C);
  if (res!=ERR_OK) { return ERR_FAILED; }

  /* 0x0000 = alarm disable, low byte first */
  res = WriteCmdWordChecked(LC709203F_I2C_SLAVE_ADDR, LC709203F_REG_RSOC_ALM, 0x00, 0x00);
  if (res!=ERR_OK) { return ERR_FAILED; }

  return ERR_OK;
}

void McuLC_Deinit(void) {
  /* nothing to do */
}

