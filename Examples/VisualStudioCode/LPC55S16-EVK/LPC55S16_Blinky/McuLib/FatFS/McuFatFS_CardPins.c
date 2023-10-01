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
#if McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN
static McuGPIO_Handle_t McuFatFS_WriteProtectPin;
#endif

bool McuFatFS_CardPinDiskPresent(uint8_t *drvStr) {
#if McuFatFS_CONFIG_HAS_CARD_DETECT_PIN
#if McuFatFS_CONFIG_CARD_DETECT_IS_HIGH_ACTIVE
  return McuGPIO_IsHigh(McuFatFS_CardDetectPin); /* Pin is high if card is inserted */
#else
  return McuGPIO_IsLow(McuFatFS_CardDetectPin); /* Pin is low if card is inserted */
#endif
#else
  return true;
#endif
}

bool McuFatFS_CardPinWriteProtected(uint8_t *drvStr) {
#if McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN
#if McuFatFS_CONFIG_WRITE_PROTECT_IS_HIGH_ACTIVE
  return McuGPIO_IsHigh(McuFatFS_WriteProtectPin); /* Pin is high if card is write protected */
#else
  return McuGPIO_IsLow(McuFatFS_WriteProtectPin); /* Pin is low if card is write protected */
#endif
#else
  return false;
#endif
}

void McuFatFS_CardPinInit(void) {
#if McuFatFS_CONFIG_HAS_CARD_DETECT_PIN || McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = true;
#endif
  /* card detect pin: */
#if McuFatFS_CONFIG_HAS_CARD_DETECT_PIN
  config.hw.gpio = McuFatFS_CONFIG_CARD_DETECT_GPIO;
  config.hw.port = McuFatFS_CONFIG_CARD_DETECT_PORT;
  config.hw.pin = McuFatFS_CONFIG_CARD_DETECT_PIN;
#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
  config.hw.iocon = McuFatFS_CONFIG_CARD_DETECT_IOCON;
#endif
  McuFatFS_CardDetectPin = McuGPIO_InitGPIO(&config);
  if (McuFatFS_CONFIG_CARD_DETECT_PULL!=McuGPIO_PULL_DISABLE) {
    McuGPIO_SetPullResistor(McuFatFS_CardDetectPin, McuFatFS_CONFIG_CARD_DETECT_PULL);
  }
#endif
  /* write protect pin: */
#if McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN
  config.hw.gpio = McuFatFS_CONFIG_WRITE_PROTECT_GPIO;
  config.hw.port = McuFatFS_CONFIG_WRITE_PROTECT_PORT;
  config.hw.pin = McuFatFS_CONFIG_WRITE_PROTECT_PIN;
#if McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0
  config.hw.iocon = McuFatFS_CONFIG_WRITE_PROTECT_IOCON;
#endif
  McuFatFS_WriteProtectPin = McuGPIO_InitGPIO(&config);
  if (McuFatFS_CONFIG_WRITE_PROTECT_PULL!=McuGPIO_PULL_DISABLE) {
    McuGPIO_SetPullResistor(McuFatFS_WriteProtectPin, McuFatFS_CONFIG_WRITE_PROTECT_PULL);
  }
#endif
}


