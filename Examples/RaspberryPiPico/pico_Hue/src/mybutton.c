/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 * Description:
 * This Module does the button debouncing.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "hardware/gpio.h"
#include "pico/time.h"
#include "McuRTOS.h"

#define BUTTON_PIN 			(18)

struct repeating_timer timer;
static uint16_t DebounceState;
static bool BUTTON_PRESSED_FLAG = false;

bool GetButtonState(void){
	if(BUTTON_PRESSED_FLAG){
		BUTTON_PRESSED_FLAG = false;
		return true;
	}else{
		return false;
	}
}

//debouncing on rising edge for button 1
static bool Debounce_Button1(struct repeating_timer *t){
	DebounceState = (DebounceState<<1);
	DebounceState = DebounceState | gpio_get(BUTTON_PIN);
	DebounceState = DebounceState | 0xe000;
	if(DebounceState == 0xf000){
		BUTTON_PRESSED_FLAG = true;
		DebounceState = 0;
	}
	return true;
}

void MyButton_Init(void){
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_up(BUTTON_PIN);
	add_repeating_timer_ms(10, Debounce_Button1, NULL, &timer);
}

void MyButton_Deinit(void){
	//Not used yet!
}
// file end
//=================================================================================
