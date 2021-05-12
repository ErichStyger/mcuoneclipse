/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "fatfs_sdcard.h"
#include "McuGPIO.h"

#if PL_CONFIG_USE_SD_CARD

#define CARD_DETECT_GPIO        GPIO
#define CARD_DETECT_PORT        0
#define CARD_DETECT_PIN         16U

//#define FatFS_CardDetect_Pull         McuGPIO_PULL_DOWN /* tinyK22: */
//#define FatFS_CardDetect_HighActive   (1)  /* tinyK22 */
#define FatFS_CardDetect_Pull           McuGPIO_PULL_DISABLE /* https://www.pololu.com/product/2587 */
#define FatFS_CardDetect_HighActive     (1)  /*  https://www.pololu.com/product/2587 */

static McuGPIO_Handle_t FatFS_CardDetectPin;

bool McuFatFS_IsDiskPresent(uint8_t drv) {
#if FatFS_CardDetect_HighActive
  return McuGPIO_IsHigh(FatFS_CardDetectPin); /* Pin is high if card is inserted */
#else
  return McuGPIO_IsLow(FatFS_CardDetectPin); /* Pin is low if card is inserted */
#endif
}

bool McuFatFS_IsWriteProtected(uint8_t drv) {
  return false; /* there is no way to detect write detection on the micro SD card */
}

void FatFS_SdCardInit(void) {
  /* using https://www.pololu.com/product/2587 */
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = true;
  config.hw.gpio = CARD_DETECT_GPIO;
  config.hw.port = CARD_DETECT_PORT;
  config.hw.pin = CARD_DETECT_PIN;
  FatFS_CardDetectPin = McuGPIO_InitGPIO(&config);
  if (FatFS_CardDetect_Pull!=McuGPIO_PULL_DISABLE) {
    McuGPIO_SetPullResistor(FatFS_CardDetectPin, FatFS_CardDetect_Pull);
  }
}

#endif /* PL_CONFIG_USE_SD_CARD */

