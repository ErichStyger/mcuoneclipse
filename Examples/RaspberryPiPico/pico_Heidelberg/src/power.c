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
#if PL_CONFIG_USE_ADC
  #include "analog.h"
#endif
#include "power.h"
#include "lights.h"
#include "McuUtility.h"
#include "McuGPIO.h"
#include "McuLog.h"
#include "McuWait.h"
#include "McuArmTools.h"

static struct power_s {
  #if POWER_CONFIG_USE_EN_VCC2
    struct vcc2 {
      McuGPIO_Handle_t pin; /* Low active: low means VCC2 power is ON */
    } vcc2;
  #endif
  #if POWER_CONFIG_USE_EN_PWR
    struct en_pwr {
      McuGPIO_Handle_t pin; /* high active */
    } en_pwr;
  #endif
  #if POWER_CONFIG_USE_PS && !PL_CONFIG_USE_PICO_W /* on Pico-W, this pin is not directly connected to the RP2040, but through the Cypress chip and WL_GPIO1 */
    struct ps {
      McuGPIO_Handle_t pin; /* low active */
    } ps;
  #endif
  #if POWER_CONFIG_SENSE_USB && !PL_CONFIG_USE_PICO_W /* Pico-W uses WL_GPIO2 */
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
    McuGPIO_SetLow(power.vcc2.pin); /* LOW: turn it on */
  } else {
    McuGPIO_SetHigh(power.vcc2.pin); /* HIGH: turn it off */
  }
}
#endif

#if POWER_CONFIG_USE_EN_VCC2
bool Power_GetVcc2IsOn(void) {
  return !McuGPIO_GetValue(power.vcc2.pin); /* false/LOW: on, true/HIGH: off */
}
#endif

#if POWER_CONFIG_USE_EN_PWR
void Power_SetEnPwrIsOn(bool on) {
  if (on) {
    McuGPIO_SetHigh(power.en_pwr.pin); /* HIGH: on */
  } else {
    McuGPIO_SetLow(power.en_pwr.pin); /* LOW: off */
  }
}
#endif

#if POWER_CONFIG_USE_EN_PWR
bool Power_GetEnPwrIsOn(void) {
  return McuGPIO_GetValue(power.en_pwr.pin); /* false/LOW: on, true/HIGH: off */
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
    McuGPIO_SetLow(power.ps.pin); /* on: LOW */
  } else {
    McuGPIO_SetHigh(power.ps.pin); /* off: HIGH */
  }
#endif
}
#endif

#if POWER_CONFIG_USE_PS
bool Power_GetPsIsOn(void) {
#if PL_CONFIG_USE_PICO_W
  if (!PicoWiFi_ArchIsInit()) {
    McuLog_error("Wifi Arch is not initialized");
    return false;
  }
  return cyw43_arch_gpio_get(POWER_CONFIG_PS_PIN)!=0;
#else
  return !McuGPIO_GetValue(power.ps.pin); /* false/LOW: on, true/HIGH: off */
#endif
}
#endif

uint8_t Power_GetBatteryChargeLevel(void) {
#if PL_CONFIG_USE_ADC && ANALOG_CONFIG_HAS_ADC_BAT
  static uint8_t avgArr[3]; /* build average */
  static uint8_t avgIdx= 0;
  avgArr[avgIdx++] = Analog_GetBatteryChargeLevel();
  if (avgIdx>=sizeof(avgArr)/sizeof(avgArr[0])) {
    avgIdx = 0;
  }
  int avg = 0;
  for(int i=0;i<sizeof(avgArr)/sizeof(avgArr[0]); i++) {
    avg += avgArr[i];
  }
  avg = avg/(sizeof(avgArr)/sizeof(avgArr[0]));
  return avg;
#else
  return 100; /* assume full battery */
#endif
}

void Power_WaitForSufficientBatteryChargeAtStartup(void) {
#if PL_CONFIG_USE_ADC && ANALOG_CONFIG_HAS_ADC_BAT
  McuWait_Waitms(5); /* C20 startup charging: 1 nF*1.5MOhm ==> ~1.5ms */
  if (Power_GetBatteryChargeLevel()<POWER_BATTERY_LEVEL_TURN_OFF) {
    Lights_SetLed(0x050000); /* turn led to red to indicate problem */
    McuWait_Waitms(5);
    Lights_SetLed(0); /* off again */
  #if POWER_CONFIG_USE_EN_VCC2
    Power_SetVcc2IsOn(false); /* turn OFF power VCC2 for OLED and SHT sensor */
  #endif
  #if POWER_CONFIG_USE_PS
    Power_SetPsIsOn(false); /* turn main power off */
  #endif
  }
  /* note: if user keeps center button pressed, we still get here: try to reduce power */
  while (Power_GetBatteryChargeLevel()<POWER_BATTERY_LEVEL_STARTUP) { /* use a power hysteresis */
    Lights_SetLed(0x020200); /* turn led to orange to indicate waiting for charge level */
    McuWait_Waitms(5);
    Lights_SetLed(0); /* off again */
  #if POWER_CONFIG_USE_EN_VCC2
    Power_SetVcc2IsOn(false); /* turn OFF power VCC2 for OLED and SHT sensor */
  #endif
  #if POWER_CONFIG_USE_PS
    Power_SetPsIsOn(false); /* turn main power off */
  #endif
    McuArmTools_SoftwareReset();
    __asm("nop"); /* \todo: enter low power mode if running RTOS */
  }
#endif
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[64];

  McuShell_SendStatusStr((unsigned char*)"power", (const unsigned char*)"Status of power\r\n", io->stdOut);
#if PL_CONFIG_USE_ADC && ANALOG_CONFIG_HAS_ADC_BAT
  McuUtility_strcpy(buf, sizeof(buf),(unsigned char*)"Turn off at ");
  McuUtility_strcatNum8u(buf, sizeof(buf), POWER_BATTERY_LEVEL_TURN_OFF);
  McuUtility_strcat(buf, sizeof(buf),(unsigned char*)"%, startup at ");
  McuUtility_strcatNum8u(buf, sizeof(buf), POWER_BATTERY_LEVEL_STARTUP);
  McuUtility_strcat(buf, sizeof(buf),(unsigned char*)"%\r\n");
  McuShell_SendStatusStr((unsigned char*)"  levels", buf, io->stdOut);
#endif
#if POWER_CONFIG_USE_EN_VCC2
  McuGPIO_GetPinStatusString(power.vcc2.pin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), Power_GetVcc2IsOn()?(unsigned char*)", power on\r\n":(unsigned char*)", power off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  vcc2 pin", buf, io->stdOut);
#endif
#if POWER_CONFIG_USE_EN_PWR
  McuGPIO_GetPinStatusString(power.en_pwr.pin, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), Power_GetEnPwrIsOn()?(unsigned char*)", power on\r\n":(unsigned char*)", power off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  en_pwr pin", buf, io->stdOut);
#endif
#if POWER_CONFIG_USE_PS
  #if PL_CONFIG_USE_PICO_W
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"WL_GPIO");
    McuUtility_strcatNum8u(buf, sizeof(buf), POWER_CONFIG_PS_PIN);
  #else
    McuGPIO_GetPinStatusString(power.ps.pin, buf, sizeof(buf));
  #endif
  McuUtility_strcat(buf, sizeof(buf), Power_GetPsIsOn()?(unsigned char*)", power save on, worse ADC\r\n":(unsigned char*)", power save off, better ADC\r\n");
  McuShell_SendStatusStr((unsigned char*)"  ps pin", buf, io->stdOut);
#endif
#if POWER_CONFIG_SENSE_USB
  #if PL_CONFIG_USE_PICO_W
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"WL_GPIO");
    McuUtility_strcatNum8u(buf, sizeof(buf), POWER_CONFIG_SENSE_USB_PIN);
  #else
    McuGPIO_GetPinStatusString(power.usb_sense.pin, buf, sizeof(buf));
  #endif
  McuUtility_strcat(buf, sizeof(buf), Power_GetUsbPowerIsOn()?(unsigned char*)", USB on\r\n":(unsigned char*)", USB off\r\n");
  McuShell_SendStatusStr((unsigned char*)"  usb sense", buf, io->stdOut);
#endif
  return ERR_OK;
}

uint8_t Power_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint32_t value;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "power help")==0) {
    *handled = true;
    McuShell_SendHelpStr((unsigned char*)"power", (const unsigned char*)"Group of power commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
#if POWER_CONFIG_USE_EN_PWR
    McuShell_SendHelpStr((unsigned char*)"  on|off", (const unsigned char*)"Turn En_Pwr on or off\r\n", io->stdOut);
#endif
#if POWER_CONFIG_USE_PS
    McuShell_SendHelpStr((unsigned char*)"  ps on|off", (const unsigned char*)"Turn DC converter power saving on or off\r\n", io->stdOut);
#endif
#if POWER_CONFIG_USE_EN_VCC2
    McuShell_SendHelpStr((unsigned char*)"  vcc2 on|off", (const unsigned char*)"Turn VCC2 on or off\r\n", io->stdOut);
#endif
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "power status")==0)) {
    *handled = true;
    return PrintStatus(io);
#if POWER_CONFIG_USE_PS
  } else if (McuUtility_strcmp((char*)cmd, "power ps on")==0) {
    *handled = TRUE;
    Power_SetPsIsOn(true);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "power ps off")==0) {
    *handled = TRUE;
    Power_SetPsIsOn(false);
    return ERR_OK;
#endif
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
  } else if (McuUtility_strcmp((char*)cmd, "power on")==0) {
    *handled = TRUE;
    Power_SetEnPwrIsOn(true);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "power off")==0) {
    *handled = TRUE;
    if (Power_GetUsbPowerIsOn()) {
      McuShell_SendStr("USB is connected, cannot turn power off\n", io->stdErr);
      return ERR_FAILED;
    }
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
    config.isHighOnInit = true; /* VCC2 PMOSFET pin is low active: turn off power at startup */
    config.hw.pin = POWER_CONFIG_VCC2_PIN;
    power.vcc2.pin = McuGPIO_InitGPIO(&config);
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
