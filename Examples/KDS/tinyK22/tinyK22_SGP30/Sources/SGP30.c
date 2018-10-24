/*
 * SGP30.c
 *
 *  Created on: 01.10.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_SGP30
#include "SGP30.h"
#include "GI2C1.h"
#include <math.h> /* for exp() */
#include "UTIL1.h"

/* Code based on Adafruit's implementation on https://github.com/adafruit/Adafruit_SGP30 */

static uint16_t serialNumber[3];

uint8_t SGP30_GenerateCRC(uint8_t *data, size_t datalen) {
  /* calculates 8-Bit checksum with given polynomial */
  uint8_t crc = SGP30_CRC8_INIT;
  uint8_t b;
  size_t i;

  for (i=0; i<datalen; i++) {
    crc ^= data[i];
    for (b=0; b<8; b++) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ SGP30_CRC8_POLYNOMIAL;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = (1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

/* Commands the sensor to take a single eCO2/VOC measurement. */
uint8_t SGP30_IAQmeasure(uint16_t *pTVOC, uint16_t *pCO2) {
  uint8_t res;
  uint8_t cmd[2];
  uint8_t reply[2*(2+1)]; /* two 16bit values with 1 byte CRC each */

  /* measure_air_quality */
  cmd[0] = 0x20;
  cmd[1] = 0x08;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 12, (uint8_t*)reply, sizeof(reply));
  if (res!=ERR_OK) {
    return res;
  }
  if (SGP30_GenerateCRC(reply, 2)!=reply[2]) {
    return ERR_CRC; /* wrong CRC? */
  }
  if (SGP30_GenerateCRC(reply+3, 2)!=reply[5]) {
    return ERR_CRC; /* wrong CRC? */
  }
  *pCO2 = (reply[0]<<8)|reply[1];
  *pTVOC = (reply[3]<<8)|reply[4];
  return res;
}

/* Request baseline calibration values for both CO2 and TVOC IAQ calculations. */
uint8_t SGP30_GetIAQBaseline(uint16_t *pTVOCbase, uint16_t *pCO2base) {
  uint8_t res;
  uint8_t cmd[2];
  uint8_t reply[2*(2+1)]; /* two 16bit values with 1 byte CRC each */

  /* Get_baseline */
  cmd[0] = 0x20;
  cmd[1] = 0x15;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, (uint8_t*)reply, sizeof(reply));
  if (res!=ERR_OK) {
    return res;
  }
  if (SGP30_GenerateCRC(reply, 2)!=reply[2]) {
    return ERR_CRC; /* wrong CRC? */
  }
  if (SGP30_GenerateCRC(reply+3, 2)!=reply[5]) {
    return ERR_CRC; /* wrong CRC? */
  }
  *pCO2base  = (reply[0]<<8)|reply[1];
  *pTVOCbase = (reply[3]<<8)|reply[4];
  return res;
}

/* Assign baseline calibration values for both CO2 and TVOC IAQ calculations. */
uint8_t SGP30_SetIAQBaseline(uint16_t TVOCbase, uint16_t CO2base) {
  uint8_t cmd[8];

  cmd[0] = 0x20;
  cmd[1] = 0x1e;
  cmd[2] = TVOCbase>>8;
  cmd[3] = TVOCbase&0xFF;
  cmd[4] = SGP30_GenerateCRC(cmd+2, 2);
  cmd[5] = CO2base>>8;
  cmd[6] = CO2base&0xff;
  cmd[7] = SGP30_GenerateCRC(cmd+5, 2);
  return GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 0, NULL, 0);
}

uint8_t SGP30_SetHumidity(uint32_t abs_humidity) {
  uint8_t cmd[5];
  uint16_t ah_scaled;

  if (abs_humidity > 256000) {
    return ERR_FAILED;
  }
  ah_scaled = (uint16_t)(((uint64_t)abs_humidity * 256 * 16777) >> 24);
  cmd[0] = 0x20;
  cmd[1] = 0x61;
  cmd[2] = ah_scaled>>8;
  cmd[3] = ah_scaled&0xff;
  cmd[4] = SGP30_GenerateCRC(cmd+2, 2);
  /* \todo Wrong data sheet? Do not have to wait???? */
  return GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, NULL, 0);
}

/* Commands the sensor to begin the IAQ algorithm. Must be called after startup. */
static uint8_t SGP30_IAQinit(void) {
  uint8_t cmd[2];

  cmd[0] = 0x20;
  cmd[1] = 0x03;
  return GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, NULL, 0);
 }

uint8_t SGP30_ReadFeatureSet(uint16_t *featureSet) {
  uint8_t buf[3]; /* 2 bytes for data plus 1 for CRC */
  uint8_t cmd[2];
  uint8_t res;

  cmd[0] = 0x20;
  cmd[1] = 0x2F;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, buf, sizeof(buf));
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  if (SGP30_GenerateCRC(buf, 2)!=buf[2]) {
    return ERR_CRC; /* wrong CRC? */
  }
  *featureSet = (buf[0]<<8)|buf[1]; /* build 16bit feature set value */
  return res;
}

uint8_t SGP30_ReadSerialNumber(uint8_t serial[6]) {
  uint8_t buf[3*(2+1)]; /* 3 words with 2 bytes of data and 1 byte for CRC */
  uint8_t cmd[2];
  uint8_t res;

  cmd[0] = 0x20;
  cmd[1] = 0x2F;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, buf, sizeof(buf));
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  if (   SGP30_GenerateCRC(buf, 2)!=buf[2] /* CRC for first word */
      || SGP30_GenerateCRC(buf+3, 2)!=buf[5] /* CRC for second word */
      || SGP30_GenerateCRC(buf+6, 2)!=buf[8] /* CRC for third word */
     )
  {
    return ERR_CRC; /* wrong CRC? */
  }
  /* build serial number */
  serial[0] = buf[0];
  serial[1] = buf[1];
  serial[2] = buf[3];
  serial[3] = buf[4];
  serial[4] = buf[6];
  serial[5] = buf[7];
  return res;
}

static uint8_t SGP30_InitDevice(void) {
  uint16_t featureSet;
  uint8_t res;

  res = SGP30_ReadFeatureSet(&featureSet);
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  if (featureSet!=SGP30_FEATURESET) {
    return ERR_FAILED; /* wrong device? */
  }
  return SGP30_IAQinit();
}

#if SGP30_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint16_t featureSet;
  uint8_t serial[6];
  uint16_t TVOC, CO2;
  uint8_t buf[32];
  uint8_t res;

  CLS1_SendStatusStr((unsigned char*)"SGP30", (unsigned char*)"\r\n", io->stdOut);
  res = SGP30_ReadFeatureSet(&featureSet);
  if (res==ERR_OK) {
    buf[0] = '\0';
    UTIL1_strcatNum16Hex(buf, sizeof(buf), featureSet);
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr("  featureset", buf, io->stdOut);

  res = SGP30_ReadSerialNumber(serial);
  if (res==ERR_OK) {
    int i;
    buf[0] = '\0';
    for(i=0; i<sizeof(serial); i++) {
      UTIL1_strcatNum8Hex(buf, sizeof(buf), serial[i]);
    }
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\r\n");
  }
  CLS1_SendStatusStr("  serial", buf, io->stdOut);

  if(SGP30_IAQmeasure(&TVOC, &CO2)==ERR_OK) {
    UTIL1_Num16uToStrFormatted(buf, sizeof(buf), TVOC, ' ', 5);
    UTIL1_strcat(buf, sizeof(buf), " ppb\r\n");
    CLS1_SendStatusStr((unsigned char*)"  TVOC", buf, io->stdOut);

    UTIL1_Num16uToStrFormatted(buf, sizeof(buf), CO2, ' ', 5);
    UTIL1_strcat(buf, sizeof(buf), " ppm\r\n");
    CLS1_SendStatusStr((unsigned char*)"  eCO2", buf, io->stdOut);
  } else {
    CLS1_SendStatusStr("  ERROR:", (unsigned char*)"  *** ERROR reading sensor values\r\n", io->stdOut);
  }

  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"SGP30", (unsigned char*)"Group of SGP30 commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}
#endif /* SGP30_CONFIG_PARSE_COMMAND_ENABLED */


#if SGP30_CONFIG_PARSE_COMMAND_ENABLED
uint8_t SGP30_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
    || UTIL1_strcmp((char*)cmd, "SGP30 help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0)
             || (UTIL1_strcmp((char*)cmd, "SGP30 status")==0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  }
  return res;
}
#endif /* SGP30_CONFIG_PARSE_COMMAND_ENABLED */


uint8_t SGP30_Init(void) {
  uint8_t res;

  res = SGP30_InitDevice();
  if (res!=ERR_OK) {
    return res;
  }
  // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
  //SGP30_SetIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!

  // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
  //float temperature = 22.1; // [°C]
  //float humidity = 45.2; // [%RH]
  //SGP30_SetHumidity(getAbsoluteHumidity(temperature, humidity));
  return res;
}

#endif /* PL_CONFIG_HAS_SGP30 */
