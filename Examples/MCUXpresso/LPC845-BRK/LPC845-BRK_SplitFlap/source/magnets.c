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

#if MAG_CONFIG_NOF_MAGNETS>=1
/* sensor for motor 0 */
#define MAG_MOTOR0_GPIO       GPIO
#define MAG_MOTOR0_PORT       0U
#define MAG_MOTOR0_PIN        19U
#define MAG_MOTOR0_IOCON      IOCON_INDEX_PIO0_19
#endif

#if MAG_CONFIG_NOF_MAGNETS>=2
/* sensor for motor 1 */
#define MAG_MOTOR1_GPIO       GPIO
#define MAG_MOTOR1_PORT       0U
#define MAG_MOTOR1_PIN        11U
#define MAG_MOTOR1_IOCON      IOCON_INDEX_PIO0_11
#endif

#if MAG_CONFIG_NOF_MAGNETS>=3
/* sensor for motor 2 */
#define MAG_MOTOR2_GPIO       GPIO
#define MAG_MOTOR2_PORT       0U
#define MAG_MOTOR2_PIN        10U
#define MAG_MOTOR2_IOCON      IOCON_INDEX_PIO0_10
#endif

#if MAG_CONFIG_NOF_MAGNETS>=4
/* sensor for motor 3 */
#define MAG_MOTOR3_GPIO       GPIO
#define MAG_MOTOR3_PORT       0U
#define MAG_MOTOR3_PIN        4U
#define MAG_MOTOR3_IOCON      IOCON_INDEX_PIO0_4
#endif

static McuGPIO_Handle_t MAG_MagnetPins[MAG_CONFIG_NOF_MAGNETS];

bool MAG_Triggered(uint8_t magnetIdx) {
  return McuGPIO_IsLow(MAG_MagnetPins[magnetIdx]);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];
  unsigned char statusBuf[16];

  McuShell_SendStatusStr((unsigned char*)"mag", (unsigned char*)"\r\n", io->stdOut);

  for(int i=0; i<MAG_CONFIG_NOF_MAGNETS; i++) {
    McuGPIO_GetPinStatusString(MAG_MagnetPins[i], buf, sizeof(buf));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuUtility_strcpy(statusBuf, sizeof(statusBuf), (unsigned char*)"  mag ");
    McuUtility_strcatNum8u(statusBuf, sizeof(statusBuf), i);
    McuShell_SendStatusStr(statusBuf, buf, io->stdOut);
  }
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
  for(int i=0; i<MAG_CONFIG_NOF_MAGNETS; i++) {
    MAG_MagnetPins[i] = McuGPIO_DeinitGPIO(MAG_MagnetPins[i]);
  }
}

void MAG_Init(void) {
  McuGPIO_Config_t gpioConfig;

  McuGPIO_GetDefaultConfig(&gpioConfig);
#if MAG_CONFIG_NOF_MAGNETS>=1
  gpioConfig.hw.gpio = MAG_MOTOR0_GPIO;
  gpioConfig.hw.port = MAG_MOTOR0_PORT;
  gpioConfig.hw.pin = MAG_MOTOR0_PIN;
  gpioConfig.hw.iocon = MAG_MOTOR0_IOCON;
  gpioConfig.isInput = true;
  MAG_MagnetPins[0] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagnetPins[0], McuGPIO_PULL_UP);
#endif

#if MAG_CONFIG_NOF_MAGNETS>=2
  gpioConfig.hw.gpio = MAG_MOTOR1_GPIO;
  gpioConfig.hw.port = MAG_MOTOR1_PORT;
  gpioConfig.hw.pin = MAG_MOTOR1_PIN;
  gpioConfig.hw.iocon = MAG_MOTOR1_IOCON;
  gpioConfig.isInput = true;
  MAG_MagnetPins[1] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagnetPins[1], McuGPIO_PULL_UP);
#endif

#if MAG_CONFIG_NOF_MAGNETS>=3
  gpioConfig.hw.gpio = MAG_MOTOR2_GPIO;
  gpioConfig.hw.port = MAG_MOTOR2_PORT;
  gpioConfig.hw.pin = MAG_MOTOR2_PIN;
  gpioConfig.hw.iocon = MAG_MOTOR2_IOCON;
  gpioConfig.isInput = true;
  MAG_MagnetPins[2] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagnetPins[2], McuGPIO_PULL_UP);
#endif

#if MAG_CONFIG_NOF_MAGNETS>=4
  gpioConfig.hw.gpio = MAG_MOTOR3_GPIO;
  gpioConfig.hw.port = MAG_MOTOR3_PORT;
  gpioConfig.hw.pin = MAG_MOTOR3_PIN;
  gpioConfig.hw.iocon = MAG_MOTOR3_IOCON;
  gpioConfig.isInput = true;
  MAG_MagnetPins[3] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagnetPins[3], McuGPIO_PULL_UP);
#endif
}

#endif /* PL_CONFIG_USE_HALL_SENSOR */
