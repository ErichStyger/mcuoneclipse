/*
 * LED.c
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#include "LED.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

void LED_On(void) {
    GPIO_PinWrite(BOARD_INITPINS_LED_GPIO, BOARD_INITPINS_LED_GPIO_PIN, 0U);
}

void LED_Off(void) {
    GPIO_PinWrite(BOARD_INITPINS_LED_GPIO, BOARD_INITPINS_LED_GPIO_PIN, 1U);
}

void LED_Toggle(void) {
	GPIO_PortToggle(BOARD_INITPINS_LED_GPIO, 1<<BOARD_INITPINS_LED_GPIO_PIN); /* toggle LED */
}

bool LED_IsOn(void) {
	return GPIO_PinRead(BOARD_INITPINS_LED_GPIO, BOARD_INITPINS_LED_GPIO_PIN)==0;
}

void LED_Init(void) {
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 1, kGPIO_NoIntmode};
    GPIO_PinInit(BOARD_INITPINS_LED_GPIO, BOARD_INITPINS_LED_GPIO_PIN, &led_config);
}
