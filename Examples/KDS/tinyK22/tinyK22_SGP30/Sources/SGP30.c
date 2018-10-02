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

static uint8_t serialNumber[3];

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

uint8_t SGP30_InitDevice(void) {
  uint8_t cmd[2];
  uint8_t res;

  cmd[0] = 0x36;
  cmd[1] = 0x82;

  res = GI2C1_ReadAddress(SGP30_I2C_ADDRESS, cmd, sizeof(cmd), serialNumber, sizeof(serialNumber));
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t SGP30_Init(void) {
  return SGP30_InitDevice();
}


#endif /* PL_CONFIG_HAS_SGP30 */
