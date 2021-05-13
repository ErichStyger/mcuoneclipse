/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuFatFS_CardPins.h"
#include "McuGPIO.h"

#if McuFatFS_CONFIG_HAS_CARD_DETECT_PIN
static McuGPIO_Handle_t McuFatFS_CardDetectPin;
#endif

bool McuFatFS_CardPinDiskPresent(uint8_t *drvStr) {
#if McuFatFS_CONFIG_HAS_CARD_DETECT_PIN
#if FatFS_CardDetect_HighActive
  return McuGPIO_IsHigh(McuFatFS_CardDetectPin); /* Pin is high if card is inserted */
#else
  return McuGPIO_IsLow(McuFatFS_CardDetectPin); /* Pin is low if card is inserted */
#endif
#else
  return true;
#endif
}

bool McuFatFS_CardPinWriteProtected(uint8_t *drvStr) {
  return false; /* there is no way to detect write detection on the micro SD card */
}

void McuFatFS_CardPinInit(void) {
#if McuFatFS_CONFIG_HAS_CARD_DETECT_PIN
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = true;
  config.hw.gpio = McuFatFS_CONFIG_CARD_DETECT_GPIO;
  config.hw.port = McuFatFS_CONFIG_CARD_DETECT_PORT;
  config.hw.pin = McuFatFS_CONFIG_CARD_DETECT_PIN;
#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
  config.hw.iocon = McuFatFS_CONFIG_CARD_DETECT_IOCON;
#endif
  McuFatFS_CardDetectPin = McuGPIO_InitGPIO(&config);
  if (McuFatFS_CONFIG_CARD_DETECT_PULL!=McuGPIO_PULL_DISABLE) {
    McuGPIO_SetPullResistor(McuFatFS_CardDetectPin, FatFS_CardDetect_Pull);
  }
#endif
}


