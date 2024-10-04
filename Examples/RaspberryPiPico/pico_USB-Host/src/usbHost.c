/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "USBHost.h"
#include "McuLib.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuGPIO.h"

#define USB_HOST_POWER_ENABLE_PIN  18 /* GPIO18 on Adafruit USB Host board to the TPS61023 EN pin (high active)*/

static McuGPIO_Handle_t powerEnablePin;

bool UsbHost_PowerIsEnabled(void) {
  return McuGPIO_IsHigh(powerEnablePin);
}

void UsbHost_PowerEnable(bool enable) {
  if (enable) {
    McuGPIO_SetHigh(powerEnablePin); /* EN High: turn on */
  } else {
    McuGPIO_SetLow(powerEnablePin); /* EN Low: turn off*/
  }
}

static uint8_t PrintHelp(McuShell_ConstStdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"UsbHost", (const unsigned char*)"Group of UsbHost commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  power on|off", (const unsigned char*)"Turn host 5V power on or off\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  McuShell_SendStatusStr((const unsigned char*)"UsbHost", (const unsigned char*)"UsbHost module status\r\n", io->stdOut);
  McuShell_SendStatusStr((const unsigned char*)"  power", UsbHost_PowerIsEnabled()?(unsigned char*)"on\r\n":(unsigned char*)"off\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t UsbHost_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io) {
if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "UsbHost help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "UsbHost status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if ((McuUtility_strcmp((char*)cmd, "UsbHost power on")==0)) {
    UsbHost_PowerEnable(true);
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, "UsbHost power off")==0)) {
    UsbHost_PowerEnable(false);
    return ERR_OK;
  }
  return ERR_OK;
}

void UsbHost_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.isInput = false;
  config.isHighOnInit = false; /* low by default: 5V power off */
  config.hw.pin = USB_HOST_POWER_ENABLE_PIN;
  config.hw.pull = McuGPIO_PULL_UP;
 
  powerEnablePin = McuGPIO_InitGPIO(&config);
  if (powerEnablePin==NULL) {
    for(;;) { /* error */ }
  }
}