/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_POWER
#if PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h"
  #include "PicoWiFi.h"
#endif
#include "power.h"
#include "McuUtility.h"
#include "McuGPIO.h"
#include "McuLog.h"

static struct power_s {
  #if POWER_CONFIG_USE_EN_VCC2
    struct vcc2 {
      bool isOn;
      McuGPIO_Handle_t pin; /* Low active */
    } vcc2;
  #endif
  #if POWER_CONFIG_USE_EN_PWR
    struct en_pwr {
      bool isOn;
      McuGPIO_Handle_t pin; /* high active */
    } en_pwr;
  #endif
  #if POWER_CONFIG_USE_PS
    struct ps {
      bool isOn;
    #if !PL_CONFIG_USE_PICO_W
      McuGPIO_Handle_t pin; /* low active */
    #endif
    } ps;
  #endif
  #if POWER_CONFIG_SENSE_USB && !PL_CONFIG_USE_PICO_W
    struct usb_sense {
      McuGPIO_Handle_t pin; /* low active. */
    } usb_sense;
  #endif
} power;

#if POWER_CONFIG_SENSE_USB
bool Power_GetUsbPowerIsOn(void) {
#if PL_CONFIG_USE_PICO_W
  if (!PicoWiFi_ArchIsInit()) {
    McuLog_error("Wifi Arch is not initialized");
    return false;
  }
  return cyw43_arch_gpio_get(POWER_CONFIG_SENSE_USB_PIN)!=0;
#else
  return McuGPIO_IsHigh(power.usb_sense.pin);
#endif
}
#endif

#if POWER_CONFIG_USE_EN_VCC2
void Power_SetVcc2IsOn(bool on) {
  if (on) {
    McuGPIO_SetLow(power.vcc2.pin);
  } else {
    McuGPIO_SetHigh(power.vcc2.pin);
  }
  power.vcc2.isOn = on;
}
#endif

#if POWER_CONFIG_USE_EN_VCC2
bool Power_GetVcc2IsOn(void) {
  return power.vcc2.isOn;
}
#endif

#if POWER_CONFIG_USE_EN_PWR
void Power_SetEnPwrIsOn(bool on) {
  if (on) {
    McuGPIO_SetHigh(power.en_pwr.pin);
  } else {
    McuGPIO_SetLow(power.en_pwr.pin);
  }
  power.en_pwr.isOn = on;
}
#endif

#if POWER_CONFIG_USE_PS
bool Power_GetPsIsOn(void) {
  return power.ps.isOn;
}
#endif

#if POWER_CONFIG_USE_PS
void Power_SetPsIsOn(bool on) {
#if PL_CONFIG_USE_PICO_W
  if (!PicoWiFi_ArchIsInit()) {
    McuLog_error("Wifi Arch is not initialized");
    return;
  }
  cyw43_arch_gpio_put(POWER_CONFIG_PS_PIN, on?0:1);
#else
  if (on) {
    McuGPIO_SetLow(power.ps.pin);
  } else {
    McuGPIO_SetHigh(power.ps.pin);
  }
#endif
  power.ps.isOn = on;
}
#endif

#if POWER_CONFIG_USE_EN_VCC2
bool Power_GetEnPwrIsOn(void) {
  return power.en_pwr.isOn;
}
#endif

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"power", (const unsigned char*)"Status of power\r\n", io->stdOut);
#if POWER_CONFIG_USE_EN_VCC2
  McuGPIO_GetPinStatusString(power.vcc2.pin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), Power_GetVcc2IsOn()?(unsigned char*)", on\r\n":(unsigned char*)", off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  vcc2 pin", buf, io->stdOut);
#endif
#if POWER_CONFIG_USE_EN_PWR
  McuGPIO_GetPinStatusString(power.en_pwr.pin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), Power_GetEnPwrIsOn()?(unsigned char*)", on\r\n":(unsigned char*)", off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  en_pwr pin", buf, io->stdOut);
#endif
#if POWER_CONFIG_USE_PS
  #if PL_CONFIG_USE_PICO_W
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"WL_GPIO");
    McuUtility_strcatNum8u(buf, sizeof(buf), POWER_CONFIG_PS_PIN);
  #else
    McuGPIO_GetPinStatusString(power.ps.pin, buf, sizeof(buf));
  #endif
  McuUtility_strcat(buf, sizeof(buf), Power_GetPsIsOn()?(unsigned char*)", on\r\n":(unsigned char*)", off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  ps pin", buf, io->stdOut);
#endif
#if POWER_CONFIG_SENSE_USB
  #if PL_CONFIG_USE_PICO_W
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"WL_GPIO");
    McuUtility_strcatNum8u(buf, sizeof(buf), POWER_CONFIG_SENSE_USB_PIN);
  #else
    McuGPIO_GetPinStatusString(power.usb_sense.pin, buf, sizeof(buf));
  #endif
  McuUtility_strcat(buf, sizeof(buf), Power_GetUsbPowerIsOn()?(unsigned char*)", on\r\n":(unsigned char*)", off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  usb sense", buf, io->stdOut);
#endif
  return ERR_OK;
}

uint8_t Power_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint32_t value;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "power help")==0) {
    McuShell_SendHelpStr((unsigned char*)"power", (const unsigned char*)"Group of application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
#if POWER_CONFIG_USE_EN_VCC2
    McuShell_SendHelpStr((unsigned char*)"  vcc2 on|off", (const unsigned char*)"Turn VCC2 on or off\r\n", io->stdOut);
#endif
#if POWER_CONFIG_USE_EN_PWR
    McuShell_SendHelpStr((unsigned char*)"  pwr on|off", (const unsigned char*)"Turn En_Pwr on or off\r\n", io->stdOut);
#endif
    *handled = true;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "power status")==0)) {
    *handled = true;
    return PrintStatus(io);
#if POWER_CONFIG_USE_EN_VCC2
  } else if (McuUtility_strcmp((char*)cmd, "power vcc2 on")==0) {
    *handled = TRUE;
    Power_SetVcc2IsOn(true);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "power vcc2 off")==0) {
    *handled = TRUE;
    Power_SetVcc2IsOn(false);
    return ERR_OK;
#endif
#if POWER_CONFIG_USE_EN_PWR
  } else if (McuUtility_strcmp((char*)cmd, "power pwr on")==0) {
    *handled = TRUE;
    Power_SetEnPwrIsOn(true);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "power pwr off")==0) {
    *handled = TRUE;
    Power_SetEnPwrIsOn(false);
    return ERR_OK;
#endif
  }
  return ERR_OK;
}

void Power_Init(void) {
#if POWER_CONFIG_USE_EN_VCC2
  {
    McuGPIO_Config_t config;

    McuGPIO_GetDefaultConfig(&config);
    config.hw.pull = McuGPIO_PULL_DISABLE;
    config.isInput = false; /* output */
    config.isHighOnInit = true; /* VCC2 PMOSFET pin is low active */
    config.hw.pin = POWER_CONFIG_VCC2_PIN;
    power.vcc2.pin = McuGPIO_InitGPIO(&config);
    power.vcc2.isOn = true;
  }
#endif

#if POWER_CONFIG_USE_EN_PWR
  {
    McuGPIO_Config_t config;

    McuGPIO_GetDefaultConfig(&config);
    config.hw.pull = McuGPIO_PULL_DISABLE;
    config.isInput = false; /* output */
    config.isHighOnInit = true; /* high active, keep power on */
    config.hw.pin = POWER_CONFIG_EN_PWR_PIN;
    power.en_pwr.pin = McuGPIO_InitGPIO(&config);
    power.en_pwr.isOn = true;
  }
#endif

#if POWER_CONFIG_USE_PS
  {
  #if !PL_CONFIG_USE_PICO_W
    McuGPIO_Config_t config;

    McuGPIO_GetDefaultConfig(&config);
    config.hw.pull = McuGPIO_PULL_DISABLE;
    config.isInput = false; /* output */
    config.isHighOnInit = false; /* by default in PS mode (low active) */
    config.hw.pin = POWER_CONFIG_PS_PIN;
    power.ps.pin = McuGPIO_InitGPIO(&config);
  #endif
    power.ps.isOn = true;
  }
#endif

#if POWER_CONFIG_SENSE_USB && !PL_CONFIG_USE_PICO_W
  {
    McuGPIO_Config_t config;

    McuGPIO_GetDefaultConfig(&config);
  #if POWER_CONFIG_SENSE_USB_PIN_PULL_DOWN
    config.hw.pull = McuGPIO_PULL_DOWN;
  #else
    config.hw.pull = McuGPIO_PULL_DISABLE;
  #endif
    config.isInput = true; /* input */
    config.hw.pin = POWER_CONFIG_SENSE_USB_PIN;
    power.usb_sense.pin = McuGPIO_InitGPIO(&config);
  }
#endif
}

#endif /* PL_CONFIG_USE_POWER */
