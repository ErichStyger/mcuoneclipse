/*
 * leds.c
 *
 *  Created on: 28.03.2019
 *      Author: Erich Styger
 */

#include "leds.h"
#include "McuLED.h"

/* Blue: P1_4 */
#define LED_BLUE_GPIO    GPIO
#define LED_BLUE_PORT    1U
#define LED_BLUE_PIN     4U
/* Red: P1_6 */
#define LED_RED_GPIO     GPIO
#define LED_RED_PORT     1U
#define LED_RED_PIN      6U
/* Green: P1_7 */
#define LED_GREEN_GPIO   GPIO
#define LED_GREEN_PORT   1U
#define LED_GREEN_PIN    7U

McuLED_Handle_t LED_Red, LED_Blue, LED_Green;

void LEDS_Deinit(void) {
  LED_Red = McuLED_DeinitLed(LED_Red);
  LED_Green = McuLED_DeinitLed(LED_Green);
  LED_Blue = McuLED_DeinitLed(LED_Blue);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;

  config.hw.pin = LED_RED_PIN;
  config.hw.port = LED_RED_PORT;
  config.hw.gpio = LED_RED_GPIO;
  LED_Red = McuLED_InitLed(&config);

  config.hw.pin = LED_GREEN_PIN;
  config.hw.port = LED_GREEN_PORT;
  config.hw.gpio = LED_GREEN_GPIO;
  LED_Green = McuLED_InitLed(&config);

  config.hw.pin = LED_BLUE_PIN;
  config.hw.port = LED_BLUE_PORT;
  config.hw.gpio = LED_BLUE_GPIO;
  LED_Blue = McuLED_InitLed(&config);
}
