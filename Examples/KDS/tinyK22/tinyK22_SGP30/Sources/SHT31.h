/*
 * SHT31.h
 *
 *  Created on: 08.10.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_SHT31_H_
#define SOURCES_SHT31_H_

#define SHT31_CONFIG_PARSE_COMMAND_ENABLED  (1)

#if SHT31_CONFIG_PARSE_COMMAND_ENABLED
  #include "CLS1.h"
  uint8_t SHT31_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);
#endif

uint8_t SHT31_ReadTempHum(float *temperature, float *humidity);

void SHT31_Init(void);


#endif /* SOURCES_SHT31_H_ */
