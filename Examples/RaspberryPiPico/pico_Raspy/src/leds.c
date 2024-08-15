/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_LEDS
#if PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h"
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
  /* note: if cyw43_arch_init() is called too early, it might hang! Best to wait during startup around 50 ms */
  if (cyw43_arch_init_with_country(CYW43_COUNTRY_SWITZERLAND)!=0) {
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
