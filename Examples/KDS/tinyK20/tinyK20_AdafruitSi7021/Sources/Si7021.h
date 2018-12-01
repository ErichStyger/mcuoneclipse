/*
 * Si7021.h
 *
 *  Created on: 27.11.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_SI7021_H_
#define SOURCES_SI7021_H_

#include <stdint.h>
#include "CLS1.h"

uint8_t SI7021_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);


uint8_t SI7021_ReadTemperatureHold(float *temperature);

uint8_t SI7021_ReadHumidityHold(float *humidity);

typedef enum {
   /* 0x00 or 0xFF engineering samples
   * 0x0D=13=Si7013
   * 0x14=20=Si7020
   * 0x15=21=Si7021
   */
  SI7021_DEVICE_ID_ENGINEERING_SAMPLE,
  SI7021_DEVICE_IDE_SI7013,
  SI7021_DEVICE_IDE_SI7020,
  SI7021_DEVICE_IDE_SI7021
} SI7021_DeviceID;

uint8_t SI7021_GetDeviceID(SI7021_DeviceID *id);

uint8_t SI7021_GetSerialBytes(uint32_t *sna, uint32_t *snb);

uint8_t SI7021_GetFirmware(uint8_t *fw);

uint8_t SI7021_Reset(void);

void SI7021_Init(void);


#endif /* SOURCES_SI7021_H_ */
