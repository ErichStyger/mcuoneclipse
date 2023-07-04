/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 * Description:
 * This Module allows to send and receive IR NEC Signals.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "McuRTOS.h"
#include "nec_transmit.h"
#include "nec_receive.h"
#include "McuRTT.h"

static PIO pio = pio1;      // choose which PIO block to use (RP2040 has two: pio0 and pio1)
static int tx_sm;
static int rx_sm;
static uint8_t time_ms_repeated_buttons = 200; //time to wait between IR tx Signals

//list of all the transmit frames from the apple ir remote
static const uint32_t apple_IR_power1_tx = 	0x265C87EE;
static const uint32_t apple_IR_power2_tx = 	0x260587EE;
static const uint32_t apple_IR_left_tx = 	0x260987EE;
static const uint32_t apple_IR_right_tx = 	0x260687EE;
static const uint32_t apple_IR_up_tx = 		0x260A87EE;
static const uint32_t apple_IR_down_tx = 	0x260C87EE;
static const uint32_t apple_IR_menu_tx = 	0x260387EE;
static const uint32_t apple_IR_sync1_tx = 	0x265F87EE;
static const uint32_t apple_IR_sync2_tx = 	0x260587EE;
static const uint32_t apple_IR_couple_tx = 	0x260287E0;
static const uint32_t apple_IR_decouple_tx = 0x260487E0;

/*send the power on/off IR command to toggle the lamp state*/
void IR_PowerOnOff_tx(void){
	pio_sm_put(pio, tx_sm, apple_IR_power1_tx);
	vTaskDelay(pdMS_TO_TICKS(100));
	pio_sm_put(pio, tx_sm, apple_IR_power2_tx);
	vTaskDelay(pdMS_TO_TICKS(100));
}

void Toggle_Lamp_State(void){
	IR_PowerOnOff_tx();
}

void IR_Up_tx(uint8_t count){
	for(uint8_t i = 0;i<count;i++){
		pio_sm_put(pio, tx_sm, apple_IR_up_tx);
		vTaskDelay(pdMS_TO_TICKS(time_ms_repeated_buttons));
	}
}

void IR_Down_tx(uint8_t count){
	for(uint8_t i = 0;i<count;i++){
		pio_sm_put(pio, tx_sm, apple_IR_down_tx);
		vTaskDelay(pdMS_TO_TICKS(time_ms_repeated_buttons));
	}
}

void IR_Left_tx(uint8_t count){
	for(uint8_t i = 0;i<count;i++){
		pio_sm_put(pio, tx_sm, apple_IR_left_tx);
		vTaskDelay(pdMS_TO_TICKS(time_ms_repeated_buttons));
	}
}

void IR_Right_tx(uint8_t count){
	for(uint8_t i = 0;i<count;i++){
		pio_sm_put(pio, tx_sm, apple_IR_right_tx);
		vTaskDelay(pdMS_TO_TICKS(time_ms_repeated_buttons));
	}
}

void IR_Menu_tx(void){
		pio_sm_put(pio, tx_sm, apple_IR_menu_tx);
		vTaskDelay(pdMS_TO_TICKS(100));
}

void IR_Sync_tx(void){
		pio_sm_put(pio, tx_sm, apple_IR_sync1_tx);
		vTaskDelay(pdMS_TO_TICKS(100));
		pio_sm_put(pio, tx_sm, apple_IR_sync2_tx);
		vTaskDelay(pdMS_TO_TICKS(100));
}

//this Task allows to react to received IR signals
static void IRReceiveTask(void * pv){

	static uint32_t rx_frame; //received frames are stored in this variable

	for(;;) {

			while (!pio_sm_is_rx_fifo_empty(pio, rx_sm)) {

				rx_frame = pio_sm_get(pio, rx_sm);

				if(rx_frame == apple_IR_up_tx){
				//Action to do if button up was pressed
				}
				if(rx_frame == apple_IR_left_tx){
				//Action to do if button left was pressed
				}
				if(rx_frame == apple_IR_right_tx){
				//Action to do if button right was pressed
				}
				if(rx_frame == apple_IR_down_tx){
				//Action to do if button down was pressed
				}
			}
	vTaskDelay(pdMS_TO_TICKS(20));
	}
}

void IR_Init(void){

	static int tx_gpio = 14;   // choose which GPIO pin is connected to the IR LED
	static int rx_gpio = 15;	// choose which GPIO pin is connected to the IR detector

	// configure and enable the state machine to send ir Signals
	tx_sm = nec_tx_init(pio, tx_gpio);  // uses two state machines, 16 instructions and one IRQ

	if (tx_sm == -1 ) {//ERROR: could not configure PIO
			for(;;){ __asm volatile ("nop");}
	}

	// configure and enable the state machine to receive IR Signals
	rx_sm = nec_rx_init(pio, rx_gpio);   // uses one state machine and 9 instructions

	if (rx_sm == -1) {//ERROR: could not configure PIO
			for(;;){ __asm volatile ("nop");}
	}
	// Set up the IR Tasks
	BaseType_t res;

	// Set up the IR Receive Task
	res = xTaskCreate(	IRReceiveTask,  			//function
						"IRreceivetask" ,			//Kernel awareness name
						500/sizeof(StackType_t), 	//stack
						(void*)NULL,				// Task Parameter
						tskIDLE_PRIORITY+1,			//Priority
						(TaskHandle_t*)NULL); 		//Task Handle

						if(res!=pdPASS){/*error*/
							for(;;){__asm volatile ("nop");}
						}
}

void IR_Deinit(void){
	//Not used yet!
}

// file end
//=================================================================================
