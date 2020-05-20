/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "fatfs_sdcard.h"
#include "McuGPIO.h"

#if PL_CONFIG_USE_SD_CARD

#define CARD_DETECT_GPIO        GPIOB
#define CARD_DETECT_PORT        PORTB
#define CARD_DETECT_PIN         16U

static McuGPIO_Handle_t FatFS_CardDetectPin;

bool McuFatFS_IsDiskPresent(uint8_t drv) {
  return McuGPIO_IsHigh(FatFS_CardDetectPin); /* pin has internal pull-down. Pin is high if card is inserted */
}

bool McuFatFS_IsWriteProtected(uint8_t drv) {
  return false; /* there is no way to detect write detection on the micro SD card */
}

void FatFS_SdCardInit(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = true;

  config.hw.gpio = CARD_DETECT_GPIO;
  config.hw.port = CARD_DETECT_PORT;
  config.hw.pin = CARD_DETECT_PIN;
  FatFS_CardDetectPin = McuGPIO_InitGPIO(&config);
  McuGPIO_SetPullResistor(FatFS_CardDetectPin, McuGPIO_PULL_DOWN);
}

#endif /* PL_CONFIG_USE_SD_CARD */

