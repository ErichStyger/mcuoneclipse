/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Driver for the SHT31 Temperature/Humidity sensor
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuSHT31config.h"
#include "McuSHT31.h"
#include "McuGenericI2C.h"
#include "McuUtility.h"
#include <stddef.h> /* for NULL */

#define SHT31_MEAS_HIGHREP_STRETCH 0x2C06
#define SHT31_MEAS_MEDREP_STRETCH  0x2C0D
#define SHT31_MEAS_LOWREP_STRETCH  0x2C10
#define SHT31_MEAS_HIGHREP         0x2400
#define SHT31_MEAS_MEDREP          0x240B
#define SHT31_MEAS_LOWREP          0x2416
#define SHT31_READSTATUS           0xF32D
#define SHT31_CLEARSTATUS          0x3041
#define SHT31_SOFTRESET            0x30A2
#define SHT31_HEATEREN             0x306D
#define SHT31_HEATERDIS            0x3066

/* status bits of the Status register (0xF32D) */
#define SHT31_STATUS_ALERT_PENDING      (1<<15) /* 0: no pending alert, 1: at least one pending alert */
#define SHT31_STATUS_HEATER_ON          (1<<13) /* 0: heater OFF, 1: heater ON */
#define SHT31_STATUS_RH_TRACKING_ALERT  (1<<11) /* 0: no RH tracking alert, 1: alert */
#define SHT31_STATUS_T_TRACKING_ALERT   (1<<10) /* 0: no T tracking alert, 1: alert */
#define SHT31_STATUS_SYSTEM_RESET       (1<<4)  /* 0: no reset detected since last clear status register command, 1: reset detected (hard reset, soft reset or supply fail */
#define SHT31_STATUS_CMD_STATUS         (1<<1)  /* 0: last command executed successfully; 1: last command not processed, it was either invalid, failed the internal command checksum */
#define SHT31_STATUS_WRITE_CRC_STATUS   (1<<0)  /* 0: checksum of last write transfer was correct, 1: checksum of last write transfer failed */

#define SHT31_CRC8_POLYNOMIAL  0x31    /* Seed for CRC polynomial */
#define SHT31_CRC8_INIT        0xFF    /* Init value for CRC */

static uint8_t SHT31_GenerateCRC(uint8_t *data, uint8_t datalen) {
  /* calculates 8-Bit checksum with given polynomial */
  uint8_t crc = SHT31_CRC8_INIT;
  uint8_t b;
  uint8_t i;

  for (i=0; i<datalen; i++) {
    crc ^= data[i];
    for (b=0; b<8; b++) {
      if (crc & 0x80) {
        crc = (crc<<1)^SHT31_CRC8_POLYNOMIAL;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}

static uint8_t SHT31_WriteCommand(uint16_t cmd) {
  uint8_t buf[2];

  buf[0] = cmd>>8;
  buf[1] = cmd&0xff;
  return McuGenericI2C_WriteAddress(McuSHT31_CONFIG_I2C_ADDR, buf, sizeof(buf), NULL, 0);
}

uint8_t SHT31_ReadStatus(uint16_t *status) {
  uint8_t res;
  uint8_t cmd[2];
  uint8_t stat[3];
  uint8_t crc;

  cmd[0] = SHT31_READSTATUS>>8;
  cmd[1] = SHT31_READSTATUS&0xff;
  res = McuGenericI2C_ReadAddress(McuSHT31_CONFIG_I2C_ADDR, cmd, sizeof(cmd), stat, sizeof(stat));
  if (res!=ERR_OK) {
    *status = 0;
    return res;
  }
  crc = SHT31_GenerateCRC(stat, 2);
  if (crc!=stat[2]) {
    return ERR_CRC; /* wrong CRC */
  }
  *status = (stat[0]<<8)+stat[1]; /* ignore CRC */
  return res;
}

uint8_t McuSHT31_Heater(bool on) {
  return SHT31_WriteCommand(on?SHT31_HEATEREN:SHT31_HEATERDIS);
}

uint8_t McuSHT31_Reset(void) {
  return SHT31_WriteCommand(SHT31_SOFTRESET);
}

uint8_t McuSHT31_ReadTempHum(float *temperature, float *humidity) {
  uint16_t ST, SRH;
  uint8_t readbuffer[6];
  uint8_t res;
  uint8_t cmd[2];

  cmd[0] = SHT31_MEAS_HIGHREP>>8;
  cmd[1] = SHT31_MEAS_HIGHREP&0xff;
  res = McuGenericI2C_ReadAddressWait(McuSHT31_CONFIG_I2C_ADDR, cmd, sizeof(cmd), 20, readbuffer, sizeof(readbuffer));
  if (res!=ERR_OK) {
    return res;
  }
  ST = (readbuffer[0]<<8)|readbuffer[1];
  if (readbuffer[2] != SHT31_GenerateCRC(readbuffer, 2)) {
    return ERR_CRC;
  }

  SRH = (readbuffer[3]<<8)|readbuffer[4];
  if (readbuffer[5] != SHT31_GenerateCRC(readbuffer+3, 2)) {
    return ERR_CRC;
  }
  /* source: https://github.com/adafruit/Adafruit_SHT31/blob/master/Adafruit_SHT31.cpp */
  int32_t stemp = (int32)ST;
  /* simplified (65536 instead of 65535) integer version of:
   * temp = (stemp * 175.0f) / 65535.0f - 45.0f;
   */
  stemp = ((4375 * stemp) >> 14) - 4500;
  *temperature = (float)stemp / 100.0f;

  /* source: https://github.com/adafruit/Adafruit_SHT31/blob/master/Adafruit_SHT31.cpp */
  uint32_t shum = (uint32_t)SRH;
  /* simplified (65536 instead of 65535) integer version of:
   * humidity = (shum * 100.0f) / 65535.0f;
   */
  shum = (625 * shum) >> 12;
  *humidity = (float)shum / 100.0f;
  return ERR_OK;
}

#if MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];
  float temperature, humidity;

  McuShell_SendStatusStr((unsigned char*)"SHT31", (unsigned char*)"Sensirion SHT31 sensor status\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), McuSHT31_CONFIG_I2C_ADDR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  addr", buf, io->stdOut);

  if(McuSHT31_ReadTempHum(&temperature, &humidity)==ERR_OK) {
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
  McuShell_SendHelpStr((unsigned char*)"SHT31", (unsigned char*)"Group of SHT31 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}
#endif /* MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED */

#if MCUSHT31_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuSHT31_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "SHT31 help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "SHT31 status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  }
  return res;
}
#endif /* SHT31_CONFIG_PARSE_COMMAND_ENABLED */

void McuSHT31_Init(void) {
  /* noting to do */
}

void McuSHT31_Deinit(void) {
  /* nothing to do */
}
