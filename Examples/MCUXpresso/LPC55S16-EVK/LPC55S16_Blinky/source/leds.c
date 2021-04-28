/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds_config.h"
#include "leds.h"
#include "McuLED.h"

static McuLED_Handle_t ledRed, ledGreen, ledBlue;

void LEDS_On(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_RED:        McuLED_On(ledRed); break;
    case LEDS_GREEN:      McuLED_On(ledGreen); break;
    case LEDS_BLUE:       McuLED_On(ledBlue); break;
    default:
      break; /* error */
  }
}

void LEDS_Off(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_RED:        McuLED_Off(ledRed); break;
    case LEDS_GREEN:      McuLED_Off(ledGreen); break;
    case LEDS_BLUE:       McuLED_Off(ledBlue); break;
    default:
      break; /* error */
  }
}

void LEDS_Neg(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_RED:        McuLED_Toggle(ledRed); break;
    case LEDS_GREEN:      McuLED_Toggle(ledGreen); break;
    case LEDS_BLUE:       McuLED_Toggle(ledBlue); break;
    default:
      break; /* error */
  }
}

#include "fsl_iocon.h"
#include "pin_mux.h"

void LEDS_Init(void) {
#define IOCON_PIO_DIGITAL_EN 0x0100u  /*!<@brief Enables digital function */
#define IOCON_PIO_FUNC0 0x00u         /*!<@brief Selects pin function 0 */
#define IOCON_PIO_INV_DI 0x00u        /*!<@brief Input function is not inverted */
#define IOCON_PIO_MODE_PULLUP 0x20u   /*!<@brief Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI 0x00u  /*!<@brief Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD 0x00u /*!<@brief Standard mode, output slew rate control is enabled */

  const uint32_t port1_pin4_config = (/* Pin is configured as PIO1_4 */
                                      IOCON_PIO_FUNC0 |
                                      /* Selects pull-up function */
                                      IOCON_PIO_MODE_PULLUP |
                                      /* Standard mode, output slew rate control is enabled */
                                      IOCON_PIO_SLEW_STANDARD |
                                      /* Input function is not inverted */
                                      IOCON_PIO_INV_DI |
                                      /* Enables digital function */
                                      IOCON_PIO_DIGITAL_EN |
                                      /* Open drain is disabled */
                                      IOCON_PIO_OPENDRAIN_DI);
  /* PORT1 PIN4 (coords: 1) is configured as PIO1_4 */
  IOCON_PinMuxSet(IOCON, LEDS_LED_RED_PORT, LEDS_LED_RED_PIN, port1_pin4_config);
  IOCON_PinMuxSet(IOCON, LEDS_LED_GREEN_PORT, LEDS_LED_GREEN_PIN, port1_pin4_config);
  IOCON_PinMuxSet(IOCON, LEDS_LED_BLUE_PORT, LEDS_LED_BLUE_PIN, port1_pin4_config);


  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isOnInit = false;
  config.isLowActive = false;
  config.hw.gpio = LEDS_LED_RED_GPIO;
  config.hw.port = LEDS_LED_RED_PORT;
  config.hw.pin = LEDS_LED_RED_PIN;
//  config.hw.iocon = LEDS_LED_RED_IOCON;
  ledRed = McuLED_InitLed(&config);
  if (ledRed==NULL) {
    for(;;) {}
  }

  config.isOnInit = false;
  config.isLowActive = false;
  config.hw.gpio = LEDS_LED_GREEN_GPIO;
  config.hw.port = LEDS_LED_GREEN_PORT;
  config.hw.pin = LEDS_LED_GREEN_PIN;
//  config.hw.iocon = LEDS_LED_GREEN_IOCON;
  ledGreen = McuLED_InitLed(&config);
  if (ledGreen==NULL) {
    for(;;) {}
  }

  config.isOnInit = false;
  config.isLowActive = false;
  config.hw.gpio = LEDS_LED_BLUE_GPIO;
  config.hw.port = LEDS_LED_BLUE_PORT;
  config.hw.pin = LEDS_LED_BLUE_PIN;
//  config.hw.iocon = LEDS_LED_BLUE_IOCON;
  ledBlue = McuLED_InitLed(&config);
  if (ledBlue==NULL) {
    for(;;) {}
  }
}

void LED_Deinit(void) {
  ledRed = McuLED_DeinitLed(ledRed);
  ledGreen = McuLED_DeinitLed(ledGreen);
  ledBlue = McuLED_DeinitLed(ledBlue);
}
