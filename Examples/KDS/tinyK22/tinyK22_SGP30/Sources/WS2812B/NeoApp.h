/*
 * Neo.h
 *
 *  Created on: 10.10.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_WS2812B_NEO_APP_C_
#define SOURCES_WS2812B_NEO_APP_C_

#include "Platform.h"
#include <stdbool.h>
#include <stdint.h>

#define NEOA_CONFIG_PARSE_COMMAND_ENABLED  (1)

#if NEOA_CONFIG_PARSE_COMMAND_ENABLED
  #include "CLS1.h"
  uint8_t NEOA_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);
#endif

void NEOA_SetFixedBrightness(uint8_t level);
uint8_t NEOA_GetFixedBrightness(void);

uint8_t NEOA_GetBrightness(void);

bool NEOA_GetIsAutoBrightness(void);
bool NEOA_SetIsAutoBrightness(bool on);

void NEOA_SetUseGammaCorrection(bool on);
bool NEOA_GetUseGammaCorrection(void);


uint32_t NEOA_GammaBrightnessColor(uint32_t color);

void NEOA_RequestDisplayUpdate(void);

void NEOA_RequestNeoMutex(void);
void NEOA_ReleaseNeoMutex(void);

typedef enum { /* order of items *MUST* match order in LittlevGL! */
#if PL_CONFIG_HAS_NEO_CLOCK
  NEOA_APP_CLOCK, /* show clock */
#endif
#if PL_CONFIG_HAS_NEO_SAND_CLOCK
  NEOA_APP_SAND_CLOCK, /* show a sand clock */
#endif
#if PL_CONFIG_HAS_NEO_SHADOW_BOX
  NEOA_APP_SHADOW_BOX,
#endif
  NEOA_APP_COUNTDOWN, /* show countdown counter */
  NEOA_APP_NONE,  /* default, dummy value */
} NEOA_AppMode;

void NEOA_SetAppMode(NEOA_AppMode mode);
NEOA_AppMode NEOA_GetAppMode(void);

void NEOA_Init(void);

#endif /* SOURCES_WS2812B_NEO_APP_C_ */
