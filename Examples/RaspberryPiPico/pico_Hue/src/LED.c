/*
 * Hue Apple IR Remote
 * Autor: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 * Description:
 * This Module allows to control the RGB LED
 *
 */

#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "McuRTOS.h"

#define RGB_G   (21)	//RGB Green PIN
#define RGB_B   (19)	//RGB Blue PIN
#define RGB_R   (20)	//RGB Red PIN
#define ONBOARD_LED (25) //ONBOARD LED PIN

//this function turns the RGB LED ON
void RGB_ON(void){
	gpio_put(RGB_R, 0);
	gpio_put(RGB_G, 0);
	gpio_put(RGB_B, 0);
}

//this function turns the RGB LED ON
void RGB_OFF(void){
	gpio_put(RGB_R, 1);
	gpio_put(RGB_G, 1);
	gpio_put(RGB_B, 1);
}

//this function allows to turn the red part from the RGB LED on or off
void LED_RED(bool onORoff){
	gpio_put(RGB_R, !onORoff);
}

//this function allows to turn the green part from the RGB LED on or off
void LED_GREEN(bool onORoff){
	gpio_put(RGB_G, !onORoff);
}

//this function allows to turn the blue part from the RGB LED on or off
void LED_BLUE(bool onORoff){
	gpio_put(RGB_B, !onORoff);
}

//this function allows to control the RGB LED
void RGB_Controll(bool R, bool G, bool B){
	gpio_put(RGB_R, !R);
	gpio_put(RGB_G, !G);
	gpio_put(RGB_B, !B);
}

void LED_Init(void){
	// Initialize LED Pins that they can be used
    gpio_init(RGB_R);
    gpio_init(RGB_G);
    gpio_init(RGB_B);
    gpio_init(ONBOARD_LED);
   // Set LED Pins as Output
	gpio_set_dir(RGB_R, GPIO_OUT);
	gpio_set_dir(RGB_G, GPIO_OUT);
	gpio_set_dir(RGB_B, GPIO_OUT);
	gpio_set_dir(ONBOARD_LED, GPIO_OUT);
	//turn off the rgb  led
	gpio_put(RGB_R, 1);
	gpio_put(RGB_G, 1);
	gpio_put(RGB_B, 1);
	//Turn the onboard led OFF
	gpio_put(ONBOARD_LED, 0);
}

void LED_Deinit(void){
	//Not used yet!
}
// file end
//=================================================================================
