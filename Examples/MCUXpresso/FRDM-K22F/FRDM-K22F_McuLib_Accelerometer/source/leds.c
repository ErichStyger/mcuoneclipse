/*
 * leds.c
 *
 *  Created on: 28.03.2019
 *      Author: Erich Styger
 */

#include "leds.h"
#include "McuLED.h"

/* red: PTA1 */
#define PINS_LEDRED_PIN     1
#define PINS_LEDRED_PORT    PORTA
#define PINS_LEDRED_GPIO    GPIOA

/* green: PTA2 */
#define PINS_LEDGREEN_PIN   2
#define PINS_LEDGREEN_PORT  PORTA
#define PINS_LEDGREEN_GPIO  GPIOA

/* blue: PTD5 */
#define PINS_LEDBLUE_PIN    5
#define PINS_LEDBLUE_PORT   PORTD
#define PINS_LEDBLUE_GPIO   GPIOD

McuLED_Handle_t LED_red, LED_green, LED_blue;

void LEDS_Deinit(void) {
  LED_red = McuLED_DeinitLed(LED_red);
  LED_green = McuLED_DeinitLed(LED_green);
  LED_blue = McuLED_DeinitLed(LED_blue);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_Init(); /* initialize LED module */

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDRED_PIN;
  config.hw.port = PINS_LEDRED_PORT;
  config.hw.gpio = PINS_LEDRED_GPIO;
  LED_red = McuLED_InitLed(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDGREEN_PIN;
  config.hw.port = PINS_LEDGREEN_PORT;
  config.hw.gpio = PINS_LEDGREEN_GPIO;
  LED_green = McuLED_InitLed(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  LED_blue = McuLED_InitLed(&config);

}
