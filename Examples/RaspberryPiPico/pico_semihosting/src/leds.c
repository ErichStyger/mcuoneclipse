/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_LEDS
#if PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h"
  #include "PicoWiFi.h"
#endif
#include "McuLib.h"
#include "leds_config.h"
#include "leds.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuLog.h"

#if LEDS_CONFIG_HAS_RED_LED
  static McuLED_Handle_t ledRed;
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  static McuLED_Handle_t ledGreen;
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  static McuLED_Handle_t ledBlue;
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  static McuLED_Handle_t ledOrange;
#endif
#if LEDS_CONFIG_HAS_ONBOARD_LED
  #if PL_CONFIG_USE_PICO_W
  static bool onBoardLedIsOn = false;
  #else
  static McuLED_Handle_t ledOnboard;
  #endif
#endif

void Leds_On(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_On(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_On(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_On(ledBlue); break;
  #endif
  #if LEDS_CONFIG_HAS_ORANGE_LED
    case LEDS_ORANGE:     McuLED_On(ledOrange); break;
  #endif
  #if LEDS_CONFIG_HAS_ONBOARD_LED
    case LEDS_ONBOARD:
    #if PL_CONFIG_USE_PICO_W
      onBoardLedIsOn = true;
      cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, onBoardLedIsOn);
    #else
      McuLED_On(ledOnboard);
    #endif
      break;
  #endif
    default:
      break; /* error */
  }
}

void Leds_Off(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_Off(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_Off(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_Off(ledBlue); break;
  #endif
  #if LEDS_CONFIG_HAS_ORANGE_LED
    case LEDS_ORANGE:     McuLED_Off(ledOrange); break;
  #endif
  #if LEDS_CONFIG_HAS_ONBOARD_LED
    case LEDS_ONBOARD:
    #if PL_CONFIG_USE_PICO_W
      onBoardLedIsOn = false;
      cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, onBoardLedIsOn);
    #else
      McuLED_Off(ledOnboard);
    #endif
      break;
  #endif
    default:
      break; /* error */
  }
}

void Leds_Neg(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_Toggle(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_Toggle(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_Toggle(ledBlue); break;
  #endif
  #if LEDS_CONFIG_HAS_ORANGE_LED
    case LEDS_ORANGE:     McuLED_Toggle(ledOrange); break;
  #endif
  #if LEDS_CONFIG_HAS_ONBOARD_LED
    case LEDS_ONBOARD:
    #if PL_CONFIG_USE_PICO_W
      onBoardLedIsOn = !onBoardLedIsOn;
      cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, onBoardLedIsOn);
    #else
      McuLED_Toggle(ledOnboard);
    #endif
      break;
  #endif
    default:
      break; /* error */
  }
}

bool Leds_Get(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        return McuLED_Get(ledRed);
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      return McuLED_Get(ledGreen);
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       return McuLED_Get(ledBlue);
  #endif
  #if LEDS_CONFIG_HAS_ORANGE_LED
    case LEDS_ORANGE:     return McuLED_Get(ledOrange);
  #endif
  #if LEDS_CONFIG_HAS_ONBOARD_LED
    case LEDS_ONBOARD:
    #if PL_CONFIG_USE_PICO_W
      return onBoardLedIsOn;
    #else
      return McuLED_Get(ledOnboard);
    #endif
      break;
  #endif
    default:
      break; /* error */
  }
  return false;
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[16];

  McuShell_SendStatusStr((const unsigned char*)"led", (const unsigned char*)"LED module status\r\n", io->stdOut);
#if LEDS_CONFIG_HAS_RED_LED
  if (Leds_Get(LEDS_RED)) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is ON\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is OFF\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  red", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  if (Leds_Get(LEDS_GREEN)) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is ON\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is OFF\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  green", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  if (Leds_Get(LEDS_BLUE)) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is ON\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is OFF\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  blue", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  if (Leds_Get(LEDS_ORANGE)) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is ON\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is OFF\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  orange", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_ONBOARD_LED
  if (Leds_Get(LEDS_ONBOARD)) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is ON\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"is OFF\r\n");
  }
  McuShell_SendStatusStr((const unsigned char*)"  onboard", (const unsigned char*)buf, io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(McuShell_ConstStdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"led", (const unsigned char*)"Group of LED commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
#if LEDS_CONFIG_HAS_RED_LED
  McuShell_SendHelpStr((unsigned char*)"  red on|off|neg", (const unsigned char*)"Control red LED\r\n", io->stdOut);
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  McuShell_SendHelpStr((unsigned char*)"  green on|off|neg", (const unsigned char*)"Control green LED\r\n", io->stdOut);
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  McuShell_SendHelpStr((unsigned char*)"  blue on|off|neg", (const unsigned char*)"Control blue LED\r\n", io->stdOut);
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  McuShell_SendHelpStr((unsigned char*)"  orange on|off|neg", (const unsigned char*)"Control orange LED\r\n", io->stdOut);
#endif
#if LEDS_CONFIG_HAS_ONBOARD_LED
  McuShell_SendHelpStr((unsigned char*)"  onboard on|off|neg", (const unsigned char*)"Control onboard LED\r\n", io->stdOut);
#endif
  return ERR_OK;
}

static bool ParseLedCommand(const unsigned char *cmd, bool *handled, unsigned char *ledStr, LEDS_Leds_e led) {
  unsigned char ledCmd[16];
  size_t len;

  McuUtility_strcpy(ledCmd, sizeof(ledCmd), (const unsigned char*)"led ");
  McuUtility_strcat(ledCmd, sizeof(ledCmd), ledStr);
  len = McuUtility_strlen((char*)ledCmd);
  if (McuUtility_strncmp((char*)cmd, (char*)ledCmd, len)==0) {
    *handled = true;
    cmd += len;
    if (McuUtility_strcmp((char*)cmd, " on")==0) {
      Leds_On(led);
      return true;
    } else if (McuUtility_strcmp((char*)cmd, " off")==0) {
      Leds_Off(led);
      return true;
    } else if (McuUtility_strcmp((char*)cmd, " neg")==0) {
      Leds_Neg(led);
      return true;
    }
  }
  return false; /* not found */
}

uint8_t Leds_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "led help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "led status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
#if LEDS_CONFIG_HAS_RED_LED
  } else if (ParseLedCommand(cmd, handled, (unsigned char*)"red", LEDS_RED)) {
    return ERR_OK;
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  } else if (ParseLedCommand(cmd, handled, (unsigned char*)"green", LEDS_GREEN)) {
    return ERR_OK;
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  } else if (ParseLedCommand(cmd, handled, (unsigned char*)"blue", LEDS_BLUE)) {
    return ERR_OK;
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  } else if (ParseLedCommand(cmd, handled, (unsigned char*)"orange", LEDS_ORANGE)) {
    return ERR_OK;
#endif
#if LEDS_CONFIG_HAS_ONBOARD_LED
  } else if (ParseLedCommand(cmd, handled, (unsigned char*)"onboard", LEDS_ONBOARD)) {
    return ERR_OK;
#endif
  }
  return ERR_OK; /* no error */
}
#endif /* PL_CONFIG_USE_SHELL */

void Leds_Init(void) {
  McuLED_Config_t config;

  LEDS_CONFIG_ENABLE_CLOCK(); /* enable clocking or initialize GPIO as required by hardware */

  McuLED_GetDefaultConfig(&config);
  config.isOnInit = false;

#if LEDS_CONFIG_HAS_RED_LED
  #if McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_KINETIS
  config.hw.gpio = LEDS_CONFIG_RED_GPIO;
  config.hw.port = LEDS_CONFIG_RED_PORT;
  #endif
  config.hw.pin = LEDS_CONFIG_RED_PIN;
  #if McuLib_CONFIG_CPU_IS_LPC
  config.hw.iocon = LEDS_CONFIG_RED_IOCON;
  #endif
  config.isLowActive = LEDS_CONFIG_RED_LOW_ACTIVE;
  ledRed = McuLED_InitLed(&config);
  if (ledRed==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  config.isLowActive = true;
  #if McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_KINETIS
  config.hw.gpio = LEDS_CONFIG_GREEN_GPIO;
  config.hw.port = LEDS_CONFIG_GREEN_PORT;
  #endif
  config.hw.pin = LEDS_CONFIG_GREEN_PIN;
  #if McuLib_CONFIG_CPU_IS_LPC
  config.hw.iocon = LEDS_CONFIG_GREEN_IOCON;
  #endif
  config.isLowActive = LEDS_CONFIG_GREEN_LOW_ACTIVE;
  ledGreen = McuLED_InitLed(&config);
  if (ledGreen==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  config.isLowActive = true;
  #if McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_KINETIS
  config.hw.gpio = LEDS_CONFIG_BLUE_GPIO;
  config.hw.port = LEDS_CONFIG_BLUE_PORT;
  #endif
  config.hw.pin = LEDS_CONFIG_BLUE_PIN;
  #if McuLib_CONFIG_CPU_IS_LPC
  config.hw.iocon = LEDS_CONFIG_BLUE_IOCON;
  #endif
  config.isLowActive = LEDS_CONFIG_BLUE_LOW_ACTIVE;
  ledBlue = McuLED_InitLed(&config);
  if (ledBlue==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_ORANGE_LED
  config.isLowActive = false;
  #if McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_KINETIS
  config.hw.gpio = LEDS_CONFIG_ORANGE_GPIO;
  config.hw.port = LEDS_CONFIG_ORANGE_PORT;
  #endif
  config.hw.pin = LEDS_CONFIG_ORANGE_PIN;
  ledOrange = McuLED_InitLed(&config);
  config.isLowActive = LEDS_CONFIG_ORANGE_LOW_ACTIVE;
  if (ledOrange==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_ONBOARD_LED
  #if PL_CONFIG_USE_PICO_W
  /* NOTE: you have to call Leds_InitFromTask() from a FreeRTOS task context! */
  #else
    config.isLowActive = true;
    #if McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_KINETIS
    config.hw.gpio = LEDS_CONFIG_ONBOARD_GPIO;
    config.hw.port = LEDS_CONFIG_ONBOARD_PORT;
    #endif
    config.hw.pin = LEDS_CONFIG_ONBOARD_PIN;
    config.isLowActive = LEDS_CONFIG_ONBOARD_LOW_ACTIVE;
    ledOnboard = McuLED_InitLed(&config);
    if (ledOnboard==NULL) {
      for(;;) {}
    }
  #endif
#endif
}

void Leds_InitFromTask(void) {
#if PL_CONFIG_USE_PICO_W
  if (cyw43_arch_init()==0)  { /* need to init for accessing LEDs and other pins */
    PicoWiFi_SetArchIsInitialized(true);
  } else {
    McuLog_fatal("failed initializing CYW43");
    for(;;){}
  }
  onBoardLedIsOn = false;
#endif
}

void Leds_Deinit(void) {
#if LEDS_CONFIG_HAS_RED_LED
  ledRed = McuLED_DeinitLed(ledRed);
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  ledGreen = McuLED_DeinitLed(ledGreen);
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  ledBlue = McuLED_DeinitLed(ledBlue);
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  ledOrange = McuLED_DeinitLed(ledOrange);
#endif
#if LEDS_CONFIG_HAS_ONBOARD_LED &&! PL_CONFIG_USE_PICO_W
  ledOnboard = McuLED_DeinitLed(ledOnboard);
#endif
}

#endif /* PL_CONFIG_USE_LEDS */
