/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_MAG_SENSOR
#include "magnets.h"
#include "McuGPIO.h"
#include "McuUtility.h"

/* Hall_M0: PIO1_1 */
#define MAG0_GPIO       GPIO
#define MAG0_PORT       1U
#define MAG0_PIN        1U
#define MAG0_IOCON      IOCON_INDEX_PIO1_1

#if PL_CONFIG_BOARD_VERSION==1
/* Hall_M1: PIO0_10 */
#define MAG1_GPIO       GPIO
#define MAG1_PORT       0U
#define MAG1_PIN        10U
#define MAG1_IOCON      IOCON_INDEX_PIO0_10
#elif PL_CONFIG_BOARD_VERSION==10
#define MAG1_GPIO       GPIO
#define MAG1_PORT       0U
#define MAG1_PIN        31U
#define MAG1_IOCON      IOCON_INDEX_PIO0_31
#endif

/* Hall_M2: PIO0_17 */
#define MAG2_GPIO       GPIO
#define MAG2_PORT       0U
#define MAG2_PIN        17U
#define MAG2_IOCON      IOCON_INDEX_PIO0_17

/* Hall_M3: PIO0_18 */
#define MAG3_GPIO       GPIO
#define MAG3_PORT       0U
#define MAG3_PIN        18U
#define MAG3_IOCON      IOCON_INDEX_PIO0_18

/* Hall_M4: PIO0_23 */
#define MAG4_GPIO       GPIO
#define MAG4_PORT       0U
#define MAG4_PIN        23U
#define MAG4_IOCON      IOCON_INDEX_PIO0_23

/* Hall_M5: PIO0_29 */
#define MAG5_GPIO       GPIO
#define MAG5_PORT       0U
#define MAG5_PIN        29U
#define MAG5_IOCON      IOCON_INDEX_PIO0_29

/* Hall_M6: PIO1_2 */
#define MAG6_GPIO       GPIO
#define MAG6_PORT       1U
#define MAG6_PIN        2U
#define MAG6_IOCON      IOCON_INDEX_PIO1_2

/* Hall_M7: PIO0_16 */
#define MAG7_GPIO       GPIO
#define MAG7_PORT       0U
#define MAG7_PIN        16U
#define MAG7_IOCON      IOCON_INDEX_PIO0_16

static McuGPIO_Handle_t MAG_MagSensor[MAG_NOF_MAG];

bool MAG_IsTriggered(MAG_MagSensor_e sensor) {
  return McuGPIO_IsLow(MAG_MagSensor[sensor]);
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];
  unsigned char status[16];

  McuShell_SendStatusStr((unsigned char*)"mag", (unsigned char*)"Magnetic hall sensor settings\r\n", io->stdOut);

  for(int i=MAG_MAG0; i<MAG_NOF_MAG; i++) {
    McuGPIO_GetPinStatusString(MAG_MagSensor[i], buf, sizeof(buf));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    McuUtility_strcpy(status, sizeof(status), (unsigned char*)"  Mag[");
    McuUtility_strcatNum32u(status, sizeof(status), i);
    McuUtility_chcat(status, sizeof(status), ']');
    McuShell_SendStatusStr(status, buf, io->stdOut);
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
  for(int i=0; i<MAG_NOF_MAG; i++) {
    MAG_MagSensor[i] = McuGPIO_DeinitGPIO(MAG_MagSensor[i]);
  }
}

#include <stdio.h>
void MAG_Init(void) {
  McuGPIO_Config_t gpioConfig;

  McuGPIO_GetDefaultConfig(&gpioConfig);
  /* internal pull-ups are enabled in Pins Tool! (or use HW pull-ups!) */

  gpioConfig.hw.gpio = MAG0_GPIO;
  gpioConfig.hw.port = MAG0_PORT;
  gpioConfig.hw.pin = MAG0_PIN;
  gpioConfig.hw.iocon = MAG0_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG0] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG0], McuGPIO_PULL_UP);

  gpioConfig.hw.gpio = MAG1_GPIO;
  gpioConfig.hw.port = MAG1_PORT;
  gpioConfig.hw.pin = MAG1_PIN;
  gpioConfig.hw.iocon = MAG1_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG1] = McuGPIO_InitGPIO(&gpioConfig);
#if PL_CONFIG_BOARD_VERSION==10 /* Pin used on V0.1 has no internal pull-up capability */
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG1], McuGPIO_PULL_UP);
#endif

  gpioConfig.hw.gpio = MAG2_GPIO;
  gpioConfig.hw.port = MAG2_PORT;
  gpioConfig.hw.pin = MAG2_PIN;
  gpioConfig.hw.iocon = MAG2_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG2] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG2], McuGPIO_PULL_UP);

  gpioConfig.hw.gpio = MAG3_GPIO;
  gpioConfig.hw.port = MAG3_PORT;
  gpioConfig.hw.pin = MAG3_PIN;
  gpioConfig.hw.iocon = MAG3_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG3] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG3], McuGPIO_PULL_UP);

  gpioConfig.hw.gpio = MAG4_GPIO;
  gpioConfig.hw.port = MAG4_PORT;
  gpioConfig.hw.pin = MAG4_PIN;
  gpioConfig.hw.iocon = MAG4_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG4] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG4], McuGPIO_PULL_UP);

  gpioConfig.hw.gpio = MAG5_GPIO;
  gpioConfig.hw.port = MAG5_PORT;
  gpioConfig.hw.pin = MAG5_PIN;
  gpioConfig.hw.iocon = MAG5_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG5] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG5], McuGPIO_PULL_UP);

  gpioConfig.hw.gpio = MAG6_GPIO;
  gpioConfig.hw.port = MAG6_PORT;
  gpioConfig.hw.pin = MAG6_PIN;
  gpioConfig.hw.iocon = MAG6_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG6] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG6], McuGPIO_PULL_UP);

  gpioConfig.hw.gpio = MAG7_GPIO;
  gpioConfig.hw.port = MAG7_PORT;
  gpioConfig.hw.pin = MAG7_PIN;
  gpioConfig.hw.iocon = MAG7_IOCON;
  gpioConfig.isInput = true;
  MAG_MagSensor[MAG_MAG7] = McuGPIO_InitGPIO(&gpioConfig);
  McuGPIO_SetPullResistor(MAG_MagSensor[MAG_MAG7], McuGPIO_PULL_UP);
}

#endif /* PL_CONFIG_USE_MAG_SENSOR */
