/*
 * Si7021.c
 *
 *  Created on: 27.11.2018
 *      Author: Erich Styger
 */

#include <stdint.h>
#include "Si7021.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "UTIL1.h"

#define SI7021_DEFAULT_ADDRESS  0x40

#define SI7021_MEASRH_HOLD_CMD           0xE5 // Measure Relative Humidity, Hold Master Mode
#define SI7021_MEASRH_NOHOLD_CMD         0xF5 // Measure Relative Humidity, No Hold Master Mode
#define SI7021_MEASTEMP_HOLD_CMD         0xE3 // Measure Temperature, Hold Master Mode
#define SI7021_MEASTEMP_NOHOLD_CMD       0xF3 // Measure Temperature, No Hold Master Mode
#define SI7021_READPREVTEMP_CMD          0xE0 // Read Temperature Value from Previous RH Measurement
#define SI7021_RESET_CMD                 0xFE
#define SI7021_WRITERHT_REG_CMD          0xE6 // Write RH/T User Register 1
#define SI7021_READRHT_REG_CMD           0xE7 // Read RH/T User Register 1
#define SI7021_WRITEHEATER_REG_CMD       0x51 // Write Heater Control Register
#define SI7021_READHEATER_REG_CMD        0x11 // Read Heater Control Register
#define SI7021_ID1_CMD                   0xFA0F // Read Electronic ID 1st Byte
#define SI7021_ID2_CMD                   0xFCC9 // Read Electronic ID 2nd Byte
#define SI7021_FIRMVERS_CMD              0x84B8 // Read Firmware Revision

#define SI7021_REV_1          0xff
#define SI7021_REV_2          0x20


uint8_t SI7021_ReadTemperatureHold(float *temperature) {
  uint8_t res;
  uint8_t cmd = SI7021_MEASTEMP_HOLD_CMD;
  uint8_t data[3];
  float t;

  /* using hold mode with clock stretching */
  res = GI2C1_ReadAddress(SI7021_DEFAULT_ADDRESS, &cmd, sizeof(cmd), data, sizeof(data));
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  t = (float)((data[0]<<8)+data[1]);
  t *= 175.72;
  t /= 65536;
  t -= 46.85;
  *temperature = t;
  return ERR_OK;
}

uint8_t SI7021_ReadHumidityHold(float *humidity) {
  uint8_t res;
  uint8_t cmd = SI7021_MEASRH_HOLD_CMD;
  uint8_t data[3];
  float h;

  /* using hold mode with clock stretching */
  res = GI2C1_ReadAddress(SI7021_DEFAULT_ADDRESS, &cmd, sizeof(cmd), data, sizeof(data));
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  h = (float)((data[0]<<8)+data[1]);
  h *= 125;
  h /= 65536;
  h -= 6;
  *humidity = h;
  return ERR_OK;
}

uint8_t SI7021_GetSerialBytes(uint32_t *sna, uint32_t *snb) {
  static const uint8_t Serial1Read[] = {0xFA, 0x0F};
  static const uint8_t Serial2Read[] = {0xFC, 0xC9};
  uint8_t res;
  uint8_t read1[8];
  uint8_t read2[6];
  uint32_t serial;

  /* 1st access:
   * send 0xFF 0x0F, response are 8 bytes: SNA_3, CRC, SNA_2, CRC, SNA_1, CRC, SNA_0, CRC */
  res = GI2C1_ReadAddress(SI7021_DEFAULT_ADDRESS, (uint8_t*)&Serial1Read[0], sizeof(Serial1Read), &read1[0], sizeof(read1));
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  if (sna!=NULL) {
    *sna = (read1[0]<<24)|(read1[2]<<16)|(read1[4]<<8)|(read1[6]);
  }
  /* 2nd access:
   * send 0xFC 0xC9, response are 6 bytes: SNB_3, SNB_2, CRC, SNB_1, SNB_0, CRC */
  res = GI2C1_ReadAddress(SI7021_DEFAULT_ADDRESS, (uint8_t*)&Serial2Read[0], sizeof(Serial2Read), &read2[0], sizeof(read2));
  /* read2[0]:
   * 0x00 or 0xFF engineering samples
   * 0x0D=13=Si7013
   * 0x14=20=Si7020
   * 0x15=21=Si7021
   */
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  if (snb!=NULL) {
    *snb = (read2[0]<<24)|(read2[1]<<16)|(read2[3]<<8)|(read2[4]);
  }
  return ERR_OK;
}

uint8_t SI7021_GetDeviceID(SI7021_DeviceID *id) {
  uint8_t res;
  uint32_t snb;

  res = SI7021_GetSerialBytes(NULL, &snb);
  if (res!=ERR_OK) {
    return res;
  }
  switch((snb>>24)&0xff) {
    case 0x0D:
      *id = SI7021_DEVICE_IDE_SI7013;
      break;
    case 0x14:
      *id = SI7021_DEVICE_IDE_SI7020;
      break;
    case 0x15:
      *id = SI7021_DEVICE_IDE_SI7021;
      break;
    default:
    case 0x00:
    case 0xFF:
      *id = SI7021_DEVICE_ID_ENGINEERING_SAMPLE;
      break;
  } /* switch */
  return ERR_OK;
}

uint8_t SI7021_GetFirmware(uint8_t *fw) {
  static const uint8_t FwRead[] = {0x84, 0xB8};
  uint8_t res;
  uint8_t fwrev;

  res = GI2C1_ReadAddress(SI7021_DEFAULT_ADDRESS, (uint8_t*)&FwRead[0], sizeof(FwRead), &fwrev, sizeof(fwrev));
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  *fw = fwrev; /* 0xFF: Firmware version 1.0, 0x20: Firmware version 2.0 */
  return ERR_OK;
}

uint8_t SI7021_Reset(void) {
  uint8_t res;

  res = GI2C1_WriteByte(SI7021_DEFAULT_ADDRESS, SI7021_RESET_CMD);
  WAIT1_WaitOSms(50);
  return ERR_OK;
}

static uint8_t SI7021_PrintStatus(CLS1_ConstStdIOType *io) {
  uint8_t res, fw, buf[48];
  uint32_t sna, snb;
  SI7021_DeviceID id;
  float f, h;

  CLS1_SendStatusStr((const unsigned char*)"SI7021", (const unsigned char*)"\r\n", io->stdOut);
  res = SI7021_GetSerialBytes(&sna, &snb);
  if (res==ERR_OK) {
    buf[0] = '\0';
    UTIL1_strcatNum32Hex(buf, sizeof(buf), sna);
    UTIL1_strcatNum32Hex(buf, sizeof(buf), snb);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  S/N", buf, io->stdOut);

  res = SI7021_GetFirmware(&fw);
  if (res==ERR_OK) {
    buf[0] = '\0';
    if (fw==0xff) {
      UTIL1_strcat(buf, sizeof(buf), "V1.0\r\n");
    } else if (fw==0x20) {
      UTIL1_strcat(buf, sizeof(buf), "V2.0\r\n");
    } else {
      UTIL1_strcat(buf, sizeof(buf), "????\r\n");
   }
   } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  Firmware", buf, io->stdOut);

  res = SI7021_GetDeviceID(&id);
  if (res==ERR_OK) {
    buf[0] = '\0';
    switch(id) {
      case SI7021_DEVICE_IDE_SI7013:
        UTIL1_strcat(buf, sizeof(buf), "SI7013\r\n");
        break;
      case SI7021_DEVICE_IDE_SI7020:
        UTIL1_strcat(buf, sizeof(buf), "SI7020\r\n");
        break;
      case SI7021_DEVICE_IDE_SI7021:
        UTIL1_strcat(buf, sizeof(buf), "SI7021\r\n");
       break;
      case SI7021_DEVICE_ID_ENGINEERING_SAMPLE:
        UTIL1_strcat(buf, sizeof(buf), "Engineering Sample\r\n");
        break;
      default:
        break;
    }
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  Device ID", buf, io->stdOut);

  res = SI7021_ReadTemperatureHold(&f);
  if (res==ERR_OK) {
    buf[0] = '\0';
    UTIL1_strcatNumFloat(buf, sizeof(buf), f, 2);
    UTIL1_strcat(buf, sizeof(buf), "°C\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  Temperature", buf, io->stdOut);

  res = SI7021_ReadHumidityHold(&f);
  if (res==ERR_OK) {
    buf[0] = '\0';
    UTIL1_strcatNumFloat(buf, sizeof(buf), f, 2);
    UTIL1_strcat(buf, sizeof(buf), "%\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr((const unsigned char*)"  Humidity", buf, io->stdOut);
  return ERR_OK;
}

uint8_t SI7021_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "SI7021 help")==0) {
    CLS1_SendHelpStr((unsigned char*)"SI7021", (const unsigned char*)"Group of CLS1 commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "SI7021 status")==0) {
    *handled = TRUE;
    return SI7021_PrintStatus(io);
  }
  return ERR_OK;
}

void SI7021_Init(void) {
}
