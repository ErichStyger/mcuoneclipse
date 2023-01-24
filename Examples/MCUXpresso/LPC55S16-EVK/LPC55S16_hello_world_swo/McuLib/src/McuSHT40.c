/*
 * Copyright (c) 2019, 2022 Erich Styger
 * All rights reserved.
 *
 * Driver for the Sensirion SHT40 Temperature/Humidity sensor
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSHT40config.h"
#include "McuSHT40.h"
#include "McuGenericI2C.h"
#include "McuUtility.h"
#include <stddef.h> /* for NULL */

#define SHT40_MEAS_HIGHREP         0xFD
#define SHT40_MEAS_MEDREP          0xF6
#define SHT40_MEAS_LOWREP          0xE0

#define SHT40_READSERIALNUM        0x89

#define SHT40_SOFTRESET            0x94

#define SHT40_HEATER_200MW_1000MS_PRECISION_HIGH    0x39 /* activate heater with 200mW for 1s, including a high precision measurement just before deactivation */
#define SHT40_HEATER_200MW_100MS_PRECISION_HIGH     0x32 /* activate heater with 200mW for 0.1s, including a high precision measurement just before deactivation */
#define SHT40_HEATER_110MW_1000MS_PRECISION_HIGH    0x2F /* activate heater with 110mW for 1s, including a high precision measurement just before deactivation */
#define SHT40_HEATER_110MW_100MS_PRECISION_HIGH     0x24 /* activate heater with 110mW for 0.1s, including a high precision measurement just before deactivation */
#define SHT40_HEATER_20MW_1000MS_PRECISION_HIGH     0x1E /* activate heater with 20mW for 1s, including a high precision measurement just before deactivation */
#define SHT40_HEATER_20MW_100MS_PRECISION_HIGH      0x15 /* activate heater with 20mW for 0.1s, including a high precision measurement just before deactivation */


/* status bits of the Status register (0xF32D) */
#define SHT40_STATUS_ALERT_PENDING      (1<<15) /* 0: no pending alert, 1: at least one pending alert */
#define SHT40_STATUS_HEATER_ON          (1<<13) /* 0: heater OFF, 1: heater ON */
#define SHT40_STATUS_RH_TRACKING_ALERT  (1<<11) /* 0: no RH tracking alert, 1: alert */
#define SHT40_STATUS_T_TRACKING_ALERT   (1<<10) /* 0: no T tracking alert, 1: alert */
#define SHT40_STATUS_SYSTEM_RESET       (1<<4)  /* 0: no reset detected since last clear status register command, 1: reset detected (hard reset, soft reset or supply fail */
#define SHT40_STATUS_CMD_STATUS         (1<<1)  /* 0: last command executed successfully; 1: last command not processed, it was either invalid, failed the internal command checksum */
#define SHT40_STATUS_WRITE_CRC_STATUS   (1<<0)  /* 0: checksum of last write transfer was correct, 1: checksum of last write transfer failed */

#define SHT40_CRC8_POLYNOMIAL  0x31    /* Seed for CRC polynomial */
#define SHT40_CRC8_INIT        0xFF    /* Init value for CRC */

static uint8_t SHT40_GenerateCRC(uint8_t *data, uint8_t datalen) {
  /* calculates 8-Bit checksum with given polynomial */
  uint8_t crc = SHT40_CRC8_INIT;
  uint8_t b;
  uint8_t i;

  for (i=0; i<datalen; i++) {
    crc ^= data[i];
    for (b=0; b<8; b++) {
      if (crc & 0x80) {
        crc = (crc<<1)^SHT40_CRC8_POLYNOMIAL;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}

static uint8_t SHT40_WriteCommand(uint16_t cmd) {
  uint8_t buf[2];

  buf[0] = cmd>>8;
  buf[1] = cmd&0xff;
  return McuGenericI2C_WriteAddress(McuSHT40_CONFIG_I2C_ADDR, buf, sizeof(buf), NULL, 0);
}

uint8_t SHT40_ReadSerialNumber(uint32_t *serial) {
  uint8_t res;
  uint8_t cmd[1];
  uint8_t readbuffer[6];

  cmd[0] = SHT40_READSERIALNUM;
  res = McuGenericI2C_ReadAddressWait(McuSHT40_CONFIG_I2C_ADDR, cmd, sizeof(cmd), 20, readbuffer, sizeof(readbuffer));
  if (res!=ERR_OK) {
    *serial = 0;
    return res;
  }
  *serial = (readbuffer[0]<<24)|(readbuffer[1]<<16);
  if (readbuffer[2] != SHT40_GenerateCRC(readbuffer, 2)) {
    return ERR_CRC;
  }

  *serial |= (readbuffer[3]<<8)|readbuffer[4];
  if (readbuffer[5] != SHT40_GenerateCRC(readbuffer+3, 2)) {
    return ERR_CRC;
  }
  return res;
}

uint8_t McuSHT40_Reset(void) {
  return SHT40_WriteCommand(SHT40_SOFTRESET);
}

uint8_t McuSHT40_ReadTempHum(float *temperature, float *humidity) {
  float stemp, shum;
  uint16_t ST, SRH;
  uint8_t readbuffer[6];
  uint8_t res;
  uint8_t cmd[1];

  cmd[0] = SHT40_MEAS_HIGHREP;
  res = McuGenericI2C_ReadAddressWait(McuSHT40_CONFIG_I2C_ADDR, cmd, sizeof(cmd), 20, readbuffer, sizeof(readbuffer));
  if (res!=ERR_OK) {
    return res;
  }
  ST = (readbuffer[0]<<8)|readbuffer[1];
  if (readbuffer[2] != SHT40_GenerateCRC(readbuffer, 2)) {
    return ERR_CRC;
  }

  SRH = (readbuffer[3]<<8)|readbuffer[4];
  if (readbuffer[5] != SHT40_GenerateCRC(readbuffer+3, 2)) {
    return ERR_CRC;
  }

  stemp = ST;
  stemp *= 175;
  stemp /= 0xffff;
  stemp = -45 + stemp;
  *temperature = stemp;

  shum = SRH;
  shum *= 125;
  shum /= 0xFFFF;
  shum = -6 + shum;
  if (shum>100.0f) {
    shum = 100.0f;
  } else if (shum<0.0f) {
    shum = 0.0f;
  }
  *humidity = shum;

  return ERR_OK;
}

#if MCUSHT40_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];
  uint32_t serial;
  float temperature, humidity;
  uint8_t res;

  McuShell_SendStatusStr((unsigned char*)"SHT40", (unsigned char*)"Sensirion SHT40 sensor status\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), McuSHT40_CONFIG_I2C_ADDR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  addr", buf, io->stdOut);

  res = SHT40_ReadSerialNumber(&serial);
  if (res==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum32Hex(buf, sizeof(buf), serial);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  serial", buf, io->stdOut);

  if(McuSHT40_ReadTempHum(&temperature, &humidity)==ERR_OK) {
    McuUtility_NumFloatToStr(buf, sizeof(buf), temperature, 2);
    McuUtility_chcat(buf, sizeof(buf), '\xB0'); /* add '°' (ASCII 0xB0) it as single char, as with UTF-8 it might end up in two bytes inside a string */
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"C\r\n");
    McuShell_SendStatusStr((unsigned char*)"  temp", buf, io->stdOut);

    McuUtility_NumFloatToStr(buf, sizeof(buf), humidity, 2);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" RH\r\n");
    McuShell_SendStatusStr((unsigned char*)"  humidity", buf, io->stdOut);
  } else {
    McuShell_SendStatusStr((unsigned char*)"  ERROR:", (unsigned char*)"  *** ERROR reading sensor values\r\n", io->stdOut);
  }
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"SHT40", (unsigned char*)"Group of SHT40 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}
#endif /* MCUSHT40_CONFIG_PARSE_COMMAND_ENABLED */

#if MCUSHT40_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuSHT40_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "SHT40 help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "SHT40 status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  }
  return res;
}
#endif /* SHT40_CONFIG_PARSE_COMMAND_ENABLED */

void McuSHT40_Init(void) {
  /* noting to do */
}

void McuSHT40_Deinit(void) {
  /* nothing to do */
}
