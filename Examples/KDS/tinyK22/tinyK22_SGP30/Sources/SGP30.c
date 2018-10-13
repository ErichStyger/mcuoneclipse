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
  uint16_t reply[2];

  cmd[0] = 0x20;
  cmd[1] = 0x08;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 12, (uint8_t*)reply, sizeof(reply));
  *pCO2 = reply[0];
  *pTVOC = reply[1];
  return res;
}

/* Request baseline calibration values for both CO2 and TVOC IAQ calculations. */
uint8_t SGP30_GetIAQBaseline(uint16_t *pTVOCbase, uint16_t *pCO2base) {
  uint8_t res;
  uint8_t cmd[2];
  uint16_t reply[2];

  cmd[0] = 0x20;
  cmd[1] = 0x15;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, (uint8_t*)reply, sizeof(reply));
  *pTVOCbase = reply[0];
  *pCO2base = reply[1];
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
  cmd[7] = SGP30_GenerateCRC(cmd+5, 2);;
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
  return GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, NULL, 0);
}

/* Commands the sensor to begin the IAQ algorithm. Must be called after startup. */
static uint8_t SGP30_IAQinit(void) {
  uint8_t cmd[2];

  cmd[0] = 0x20;
  cmd[1] = 0x03;
  return GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, NULL, 0);
 }

static uint8_t SGP30_InitDevice(void) {
  uint16_t featureSet;
  uint8_t cmd[2];
  uint8_t res;

  cmd[0] = 0x36;
  cmd[1] = 0x82;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, (uint8_t*)serialNumber, sizeof(serialNumber));
  if (res!=ERR_OK) {
    return res;
  }
  cmd[0] = 0x20;
  cmd[1] = 0x2F;
  res = GI2C1_ReadAddressWait(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), 10, (uint8_t*)&featureSet, sizeof(featureSet));
  if (res!=ERR_OK) {
    return res;
  }
  if (featureSet!=SGP30_FEATURESET) {
    return ERR_FAILED;
  }
  return SGP30_IAQinit();
}

#if SGP30_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint16_t TVOC, CO2;
  uint8_t buf[32];

  CLS1_SendStatusStr((unsigned char*)"SGP30", (unsigned char*)"\r\n", io->stdOut);

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
