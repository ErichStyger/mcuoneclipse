/*
 * leds.c
 *
 *  Created on: 28.03.2019
 *      Author: Erich Styger
 */

#include "leds.h"
#include "SuperDuperLedDriverOfTheWorld.h"

SDLED_Handle_t tinyLED, hatRedLED, hatBlueLED, hatGreenLED, hatYellowLED;

void LEDS_Deinit(void) {
  /* nothing to do */
}

void LEDS_Init(void) {
  SDLED_Config_t config;

  SDLED_Init(); /* initialize LED module */

  /* initialize LEDs */
  SDLED_GetDefaultConfig(&config);

  config.isLowActive = true;
  config.pinNr = PINS_LEDBLUE_PIN;
  config.port = PINS_LEDBLUE_PORT;
  config.gpio = PINS_LEDBLUE_GPIO;
  tinyLED = SDLED_InitLed(&config);

  /* hat LEDs are high active */
  config.isLowActive = false;

  config.pinNr = PINS_HATLEDBLUE_PIN;
  config.port = PINS_HATLEDBLUE_PORT;
  config.gpio = PINS_HATLEDBLUE_GPIO;
  hatBlueLED = SDLED_InitLed(&config);

  config.pinNr = PINS_HATLEDGREEN_PIN;
  config.port = PINS_HATLEDGREEN_PORT;
  config.gpio = PINS_HATLEDGREEN_GPIO;
  hatGreenLED = SDLED_InitLed(&config);

  config.pinNr = PINS_HATLEDRED_PIN;
  config.port = PINS_HATLEDRED_PORT;
  config.gpio = PINS_HATLEDRED_GPIO;
  hatRedLED = SDLED_InitLed(&config);

  config.pinNr = PINS_HATLEDYELLOW_PIN;
  config.port = PINS_HATLEDYELLOW_PORT;
  config.gpio = PINS_HATLEDYELLOW_GPIO;
  hatYellowLED = SDLED_InitLed(&config);
}
