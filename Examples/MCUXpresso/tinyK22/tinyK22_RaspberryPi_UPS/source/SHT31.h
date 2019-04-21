/*

 * SHT31.h
 *
 *  Created on: 08.10.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_SHT31_H_
#define SOURCES_SHT31_H_

#include "platform.h"

#define SHT31_CONFIG_PARSE_COMMAND_ENABLED  (1 && PL_CONFIG_USE_SHELL)

#if SHT31_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"
  uint8_t SHT31_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

#include <stdint.h>

uint8_t SHT31_ReadTempHum(float *temperature, float *humidity);

void SHT31_Deinit(void);
void SHT31_Init(void);

#endif /* SOURCES_SHT31_H_ */
