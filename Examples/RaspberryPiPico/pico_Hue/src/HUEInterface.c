/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 * Description:
 * This Module allows to communicate with the Hue System
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
//#include "hardware/adc.h"
#include "McuRTOS.h"

#define MEASURE_PWM_PIN   	(27)	//This Pin is conected to the direct 3.3V PWM Signal from the LED Dimmer
#define HUE_Button_PIN		(22) 	//This Pin is connectet to the Button of the LED Dimmer

static float DutyCycle = 0; //this variable stores the actual DutyCycle from the LED Dimmer
static bool AppState = false; //this Variable stores the current state of the App
static uint8_t DutyCycleInPercent = 0;

//this function returns false if the App State is off or true if the appstate is on
bool Get_App_State(void){
	return AppState;
}

//this function returns the DutyCycle measured from the LED Dimmer in percent
uint8_t Get_App_DutyCycle(void){
	return DutyCycleInPercent;
}

//this function returns the measured dutycycle from the app
//Source: https://github.com/raspberrypi/pico-examples/blob/master/pwm/measure_duty_cycle/measure_duty_cycle.c
static float measure_duty_cycle(int PIN) {
    // Only the PWM B pins can be used as inputs.
    assert(pwm_gpio_to_channel(PIN) == PWM_CHAN_B);
    uint slice_num = pwm_gpio_to_slice_num(PIN);
    // Count once for every 100 cycles the PWM B input is high
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(PIN, GPIO_FUNC_PWM);
    pwm_set_enabled(slice_num, true);
    vTaskDelay(pdMS_TO_TICKS(10));
    pwm_set_enabled(slice_num, false);
    float counting_rate = clock_get_hz(clk_sys) / 100;
    float max_possible_count = counting_rate * 0.01;
    return pwm_get_counter(slice_num) / max_possible_count;
}

//this function allows to toggle the state of the Hue App
void Toggle_App_State(void){
	gpio_put(HUE_Button_PIN, 1);
	vTaskDelay(pdMS_TO_TICKS(20));
	gpio_put(HUE_Button_PIN, 0);
	vTaskDelay(pdMS_TO_TICKS(20));
}

//this task reads the dutycycle from the LED Dimmer every 10 Ms and provides the AppState
static void HUEInterfaceTask(void * pv){

	//if the dutycycle is greater than this value the AppState is on
	const static float threshold24V = 0.12;

	//Read the AppDutyCycle every 10 MS
	const static int DutyCycleReadFrequencyInMS = 10;

	for(;;) {

			//measure the dutycycle and invert it
			DutyCycle = 1-(measure_duty_cycle(MEASURE_PWM_PIN));

			//convert the dutycycle to an number in percent
			DutyCycleInPercent = (uint8_t)(DutyCycle*100);

			if((DutyCycle < threshold24V)){
				AppState = false;
				}else{
				AppState = true;
				}

	vTaskDelay(pdMS_TO_TICKS(DutyCycleReadFrequencyInMS));
	}
}

void HUEInterface_Init(void){
	//Init the Hue Button Pin
    gpio_init(HUE_Button_PIN);
    gpio_set_dir(HUE_Button_PIN, GPIO_OUT);
	gpio_put(HUE_Button_PIN, 0);

    //Init the PWM Measure Pin
    gpio_init(MEASURE_PWM_PIN);
    gpio_set_dir(MEASURE_PWM_PIN, GPIO_IN);

	// Set up the HUEInterface Task
	BaseType_t res;
	res = xTaskCreate(	HUEInterfaceTask,  			//function
						"HUEInterface" ,			//Kernel awareness name
						512/sizeof(StackType_t), 	//stack
						(void*)NULL,				//Task Parameter
						tskIDLE_PRIORITY+1,			//Priority
						(TaskHandle_t*)NULL); 		//Task Handle

	if(res!=pdPASS){/*error*/
					for(;;){ __asm volatile ("nop");}
	}
}

void HUEInterface_Denit(void){
	//Not used yet!
}

// file end
//=================================================================================


