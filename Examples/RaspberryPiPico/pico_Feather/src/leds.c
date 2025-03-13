/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "McuLED.h"
#include "McuUtility.h"
#include "McuShell.h"
#include "leds_config.h"
#include "leds.h"

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
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  static McuLED_Handle_t ledTiny;
#endif
#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  static McuLED_Handle_t ledPicoGreen;
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
  #if LEDS_CONFIG_HAS_BLUE_TINY_LED
    case LEDS_TINY_BLUE:  McuLED_On(ledTiny); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_PICO_LED
    case LEDS_PICO_GREEN: McuLED_On(ledPicoGreen); break;
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
  #if LEDS_CONFIG_HAS_BLUE_TINY_LED
    case LEDS_TINY_BLUE:  McuLED_Off(ledTiny); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_PICO_LED
    case LEDS_PICO_GREEN: McuLED_Off(ledPicoGreen); break;
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
  #if LEDS_CONFIG_HAS_BLUE_TINY_LED
    case LEDS_TINY_BLUE:  McuLED_Toggle(ledTiny); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_PICO_LED
    case LEDS_PICO_GREEN: McuLED_Toggle(ledPicoGreen); break;
  #endif
    default:
      break; /* error */
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  uint8_t buf[64];

#if LEDS_CONFIG_HAS_RED_LED
  McuShell_SendStatusStr((const unsigned char*)"led", (const unsigned char*)"LED module status\r\n", io->stdOut);
  McuLED_GetLedStatusString(ledRed, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  red", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
McuLED_GetLedStatusString(ledGreen, buf, sizeof(buf));
McuUtility_strcat(buf, sizeof(buf), "\r\n");

  McuShell_SendStatusStr((const unsigned char*)"  green", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
McuLED_GetLedStatusString(ledBlue, buf, sizeof(buf));
McuUtility_strcat(buf, sizeof(buf), "\r\n");

  McuShell_SendStatusStr((const unsigned char*)"  blue", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
McuLED_GetLedStatusString(ledOrange, buf, sizeof(buf));
McuUtility_strcat(buf, sizeof(buf), "\r\n");

  McuShell_SendStatusStr((const unsigned char*)"  orange", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  McuLED_GetLedStatusString(ledPicoGreen, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");

  McuShell_SendStatusStr((const unsigned char*)"  picogreen", (const unsigned char*)buf, io->stdOut);
#endif
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  McuLED_GetLedStatusString(ledTiny, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), "\r\n");

  McuShell_SendStatusStr((const unsigned char*)"  tinyblue", (const unsigned char*)buf, io->stdOut);
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
#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  McuShell_SendHelpStr((unsigned char*)"  picogreen on|off|neg", (const unsigned char*)"Control pico green LED\r\n", io->stdOut);
#endif
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  McuShell_SendHelpStr((unsigned char*)"  tinyblue on|off|neg", (const unsigned char*)"Control tiny blue LED\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t Leds_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "led help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "led status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
#if LEDS_CONFIG_HAS_RED_LED
  } else if (McuUtility_strcmp((char*)cmd, "led red on")==0) {
    *handled = TRUE;
    Leds_On(LEDS_RED);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "led red off")==0) {
    *handled = TRUE;
    Leds_Off(LEDS_RED);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "led red neg")==0) {
    *handled = TRUE;
    Leds_Neg(LEDS_RED);
    return ERR_OK;
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  } else if (McuUtility_strncmp((char*)cmd, "led green ", sizeof("led green ")-1)==0) {
    const uint8_t *p;

    p = cmd+sizeof("led green ")-1;
    if (McuUtility_strcmp((char*)p, "on")==0) {
      *handled = TRUE;
      Leds_On(LEDS_GREEN);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "off")==0) {
      *handled = TRUE;
      Leds_Off(LEDS_GREEN);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "neg")==0) {
      *handled = TRUE;
      Leds_Neg(LEDS_GREEN);
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  } else if (McuUtility_strncmp((char*)cmd, "led blue ", sizeof("led blue ")-1)==0) {
    const uint8_t *p;

    p = cmd+sizeof("led blue ")-1;
    if (McuUtility_strcmp((char*)p, "on")==0) {
      *handled = TRUE;
      Leds_On(LEDS_BLUE);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "off")==0) {
      *handled = TRUE;
      Leds_Off(LEDS_BLUE);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "neg")==0) {
      *handled = TRUE;
      Leds_Neg(LEDS_BLUE);
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  } else if (McuUtility_strncmp((char*)cmd, "led orange ", sizeof("led orange ")-1)==0) {
    const uint8_t *p;

    p = cmd+sizeof("led orange ")-1;
    if (McuUtility_strcmp((char*)p, "on")==0) {
      *handled = TRUE;
      Leds_On(LEDS_ORANGE);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "off")==0) {
      *handled = TRUE;
      Leds_Off(LEDS_ORANGE);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "neg")==0) {
      *handled = TRUE;
      Leds_Neg(LEDS_ORANGE);
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  } else if (McuUtility_strncmp((char*)cmd, "led picogreen ", sizeof("led picogreen ")-1)==0) {
    const uint8_t *p;

    p = cmd+sizeof("led picogreen ")-1;
    if (McuUtility_strcmp((char*)p, "on")==0) {
      *handled = TRUE;
      Leds_On(LEDS_PICO_GREEN);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "off")==0) {
      *handled = TRUE;
      Leds_Off(LEDS_PICO_GREEN);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "neg")==0) {
      *handled = TRUE;
      Leds_Neg(LEDS_PICO_GREEN);
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  } else if (McuUtility_strncmp((char*)cmd, "led tinyblue ", sizeof("led tinyblue ")-1)==0) {
    const uint8_t *p;

    p = cmd+sizeof("led tinyblue ")-1;
    if (McuUtility_strcmp((char*)p, "on")==0) {
      *handled = TRUE;
      Leds_On(LEDS_TINY_BLUE);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "off")==0) {
      *handled = TRUE;
      Leds_Off(LEDS_TINY_BLUE);
      return ERR_OK;
    } else if (McuUtility_strcmp((char*)p, "neg")==0) {
      *handled = TRUE;
      Leds_Neg(LEDS_TINY_BLUE);
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
  }
  return ERR_OK; /* no error */
}

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

#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  config.isLowActive = true;
    #if McuLib_CONFIG_CPU_IS_LPC || McuLib_CONFIG_CPU_IS_KINETIS
  config.hw.gpio = LEDS_CONFIG_BLUE_TINY_GPIO;
  config.hw.port = LEDS_CONFIG_BLUE_TINY_PORT;
  #endif
  config.hw.pin = LEDS_CONFIG_BLUE_TINY_PIN;
  config.isLowActive = LEDS_CONFIG_BLUE_TINY_LOW_ACTIVE;
  ledTiny = McuLED_InitLed(&config);
  if (ledTiny==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  config.hw.pin = LEDS_CONFIG_PICO_GREEN_PIN;
  config.isLowActive = LEDS_CONFIG_PICO_GREEN_LOW_ACTIVE;
  ledPicoGreen = McuLED_InitLed(&config);
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
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  ledTiny = McuLED_DeinitLed(ledTiny);
#endif
#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  ledPicoGreen = McuLED_DeinitLed(ledPicoGreen);
#endif
}
