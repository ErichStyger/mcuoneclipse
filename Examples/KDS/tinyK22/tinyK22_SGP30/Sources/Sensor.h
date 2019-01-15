/*
 * Sensor.h
 *
 *  Created on: 14.10.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_SENSOR_H_
#define SOURCES_SENSOR_H_

#include <stdint.h>

float SENSOR_GetTemperature(void);
float SENSOR_GetHumidity(void);

uint8_t SENSOR_GetAccel(int16_t *xmg, int16_t *ymg, int16_t *zmg);
uint8_t SENSOR_GetLux(uint32_t *lux);

void SENSOR_Init(void);


#endif /* SOURCES_SENSOR_H_ */
