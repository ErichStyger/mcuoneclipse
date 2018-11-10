/*
 * Neo.h
 *
 *  Created on: 10.10.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_WS2812B_NEO_APP_C_
#define SOURCES_WS2812B_NEO_APP_C_

#define NEOA_CONFIG_PARSE_COMMAND_ENABLED  (1)

#if NEOA_CONFIG_PARSE_COMMAND_ENABLED
  #include "CLS1.h"
  uint8_t NEOA_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);
#endif

void NEOA_Init(void);

#endif /* SOURCES_WS2812B_NEO_APP_C_ */
