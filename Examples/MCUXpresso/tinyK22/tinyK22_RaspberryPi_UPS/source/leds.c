/*
 * leds.c
 *
 *  Created on: 28.03.2019
 *      Author: Erich Styger
 */

#include "leds.h"
#include "McuLED.h"

McuLED_Handle_t tinyLED, hatRedLED, hatBlueLED, hatGreenLED, hatYellowLED;

void LEDS_Deinit(void) {
  tinyLED = McuLED_DeinitLed(tinyLED);
  hatBlueLED = McuLED_DeinitLed(hatBlueLED);
  hatRedLED = McuLED_DeinitLed(hatRedLED);
  hatGreenLED = McuLED_DeinitLed(hatGreenLED);
  hatYellowLED = McuLED_DeinitLed(hatYellowLED);

  McuLED_Deinit(); /* de-initialize LED module */
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_Init(); /* initialize LED module */

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);

  config.isLowActive = true;
  config.pin = PINS_LEDBLUE_PIN;
  config.port = PINS_LEDBLUE_PORT;
  config.gpio = PINS_LEDBLUE_GPIO;
  tinyLED = McuLED_InitLed(&config);

  /* hat LEDs are high active */
  config.isLowActive = false;

  config.pin = PINS_HATLEDBLUE_PIN;
  config.port = PINS_HATLEDBLUE_PORT;
  config.gpio = PINS_HATLEDBLUE_GPIO;
  hatBlueLED = McuLED_InitLed(&config);

  config.pin = PINS_HATLEDGREEN_PIN;
  config.port = PINS_HATLEDGREEN_PORT;
  config.gpio = PINS_HATLEDGREEN_GPIO;
  hatGreenLED = McuLED_InitLed(&config);

  config.pin = PINS_HATLEDRED_PIN;
  config.port = PINS_HATLEDRED_PORT;
  config.gpio = PINS_HATLEDRED_GPIO;
  hatRedLED = McuLED_InitLed(&config);

  config.pin = PINS_HATLEDYELLOW_PIN;
  config.port = PINS_HATLEDYELLOW_PORT;
  config.gpio = PINS_HATLEDYELLOW_GPIO;
  hatYellowLED = McuLED_InitLed(&config);
}