/*
 * LedShadowBox.h
 *
 *  Created on: 14.01.2019
 *      Author: Erich Styger
 */

#ifndef SOURCES_WS2812B_LEDSHADOWBOX_H_
#define SOURCES_WS2812B_LEDSHADOWBOX_H_

#define SHADOWBOX_CONFIG_PARSE_COMMAND_ENABLED  (1)

#if SHADOWBOX_CONFIG_PARSE_COMMAND_ENABLED
  #include "CLS1.h"
  uint8_t LedShadowBox_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);
#endif

void LedShadowBox_StartTask(void);
void LedShadowBox_StopTask(void);

#endif /* SOURCES_WS2812B_LEDSHADOWBOX_H_ */
