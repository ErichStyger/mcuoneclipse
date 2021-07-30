/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_HALL_SENSOR
#include "magnets.h"
#include "McuGPIO.h"
#include "McuUtility.h"

/* sensor for hour */
#define MAG_HH_GPIO       GPIO
#define MAG_HH_PORT       0U
#define MAG_HH_PIN        16U

/* sensor for minute */
#define MAG_MM_GPIO       GPIO
#define MAG_MM_PORT       0U
#define MAG_MM_PIN        17U

static McuGPIO_Handle_t MAG_HHpin, MAG_MMpin;

bool MAG_TriggeredHH(void) {
  return McuGPIO_IsLow(MAG_HHpin);
}

bool MAG_TriggeredMM(void) {
  return McuGPIO_IsLow(MAG_MMpin);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];

  McuShell_SendStatusStr((unsigned char*)"mag", (unsigned char*)"\r\n", io->stdOut);

  McuGPIO_GetPinStatusString(MAG_HHpin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  HH", buf, io->stdOut);

  McuGPIO_GetPinStatusString(MAG_MMpin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  MM", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"mag", (unsigned char*)"Group of magnet/hall sensor commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t MAG_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "mag help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "mag status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}

void MAG_Deinit(void) {
  MAG_HHpin = McuGPIO_DeinitGPIO(MAG_HHpin);
  MAG_MMpin = McuGPIO_DeinitGPIO(MAG_MMpin);
}

void MAG_Init(void) {
  McuGPIO_Config_t gpioConfig;

  McuGPIO_GetDefaultConfig(&gpioConfig);

  gpioConfig.hw.gpio = MAG_HH_GPIO;
  gpioConfig.hw.port = MAG_HH_PORT;
  gpioConfig.hw.pin = MAG_HH_PIN;
  gpioConfig.isInput = true;
  MAG_HHpin = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_HHpin, McuGPIO_PULL_UP);

  gpioConfig.hw.gpio = MAG_MM_GPIO;
  gpioConfig.hw.port = MAG_MM_PORT;
  gpioConfig.hw.pin = MAG_MM_PIN;
  gpioConfig.isInput = true;
  MAG_MMpin = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MMpin, McuGPIO_PULL_UP);
}

#endif /* PL_CONFIG_USE_HALL_SENSOR */
