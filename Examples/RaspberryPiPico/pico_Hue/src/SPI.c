/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 * Description:
 * This Module reads the current from the Lamp.
 * It provides a bool if the Lamp is on or off.
 *
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "McuRTOS.h"
#include "SEGGER_RTT.h"

#define SPI_SCLK 	10			//SCLK PIN
#define SPI_MOSI	11			//MOSI PIN
#define SPI_MISO 	12			//MISO PIN
#define SPI_CS		13			//CS PIN
#define SPI_PORT	spi1		//use SPI1 from the RP2040
#define READ_BIT	0b01
#define WRITE_BIT 	0xFE
#define ADC_CONFIG_ADDR 0x01
#define SHUNT_CAL_ADDR 	0x02
#define CURRENT_ADDR 	0x07
#define DEVICE_ID_ADDR 	0x3F

static bool LampState; //true = Lamp is ON , false = Lamp is OFF

//Set CS Low to start SPI communication.
static void CS_select(void){
    gpio_put(SPI_CS, 0);
}

//Set CS High to end SPI communication.
static void CS_deselect(void){
    gpio_put(SPI_CS, 1);
}

//this function allows to read 8 bit registers via SPI
static void spi_read_register(uint8_t reg, uint8_t *buf, size_t len){
	reg = (reg<<2);
	reg = reg|READ_BIT;
	CS_select();
	spi_write_blocking(SPI_PORT, &reg , 1);
	spi_read_blocking(SPI_PORT, 0, buf, len);
	CS_deselect();
}

//this function allows to write 16 bits of data into an register via SPI
static void spi_write_register(uint8_t reg, uint16_t data){
    reg = (reg<<2);
    reg = reg&WRITE_BIT;
    uint8_t buf[2]; //buffer for data to be written
    //trim data
    buf[0] = (uint8_t)((data>>8)&0x00FF);
    buf[1] = (uint8_t)((data)&0x00FF);
    CS_select();
    spi_write_blocking(SPI_PORT, &reg, sizeof(reg));
    spi_write_blocking(SPI_PORT, buf, sizeof(buf));
    CS_deselect();
}

//this function reads the raw current from the INA239 and converts it, to return the current in [A]
static float spi_get_currentA(void){
	const float current_lsb = (float)5/(float)(1<<15); //this variable is used to convert the raw current reading to a value in [A]
	uint8_t current_raw[2];
	float current_in_A;
	spi_read_register(CURRENT_ADDR , current_raw , sizeof(current_raw));
	uint16_t current_raw_read = ((current_raw[0])<<8)|(current_raw[1]);
	current_in_A = current_raw_read * current_lsb;
	return current_in_A;
}

//this function returns the Lamp state
bool Get_Lamp_State(void){
	return LampState;
}

//this task reads the lamp current every 20 ms and provides the LampState
static void SPITask(void * pv){

	/* storage for the actual current in A */
	float current;

	/* read the current every 20 ms */
	int CurrentReadFrequencyInMS = 20;

	/* if the current is greater than this value the lamp is on */
	const float current_threshold = 0.014;

	/* hysterese to avoid flickering in LampState while lamp turns on or off */
	const float hysterese = 0.003;

	for(;;) {

		current = spi_get_currentA();

		if(current>(current_threshold+hysterese)){
			LampState = true;
		}else if(current<(current_threshold-hysterese)){
			LampState = false;
		}

	vTaskDelay(pdMS_TO_TICKS(CurrentReadFrequencyInMS));
	}
}

// initialisations and deinitialisations
//=================================================================================
void SPI_Init(void){
	// Use the SPI1 at 50 kHz
	spi_init(SPI_PORT, 50 * 1000);
	//Set the SPI clock Phase
	spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST);
	stdio_init_all();
	//Set the SPI Pins
	gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
	gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
	gpio_set_function(SPI_SCLK, GPIO_FUNC_SPI);
	// Chip select is active-low, so we'll initialise it to a driven-high state
	gpio_init(SPI_CS);
	gpio_set_dir(SPI_CS, GPIO_OUT);
	gpio_put(SPI_CS, 1);
	// Calibrate INA239
	// Rshunt = 0.03 Ohms
	// SHUNT_CAL = 819.2x1,0^6xCURRENT_LSBxRshunt=3750=0xEA6
	spi_write_register(SHUNT_CAL_ADDR, 0xEA6);
	//measure only shunt voltage (->current), calc meanvalue of 16 samples (takes ca 18ms)
	spi_write_register(ADC_CONFIG_ADDR, 0xAB6A);

	// read device id to test the SPI connection
	uint8_t id[2]; //storage for the read device Id
	spi_read_register(DEVICE_ID_ADDR , id , sizeof(id));
	uint16_t id_read = ((id[0])<<8)|(id[1]);
	if(id_read!=0x2391){
			__asm volatile ("nop");
			}

	//Create the SPI Task
	BaseType_t res;
	res = xTaskCreate(	SPITask,  				//function
						"SPItask" ,				//Kernel awareness name
						1024/sizeof(StackType_t), //stack
						(void*)NULL,			//Task Parameter
						tskIDLE_PRIORITY+1,		//Priority
						(TaskHandle_t*)NULL); 	//Task Handle

	if(res!=pdPASS){/*error*/
					for(;;){__asm volatile ("nop");}
	}
}

void SPI_Deinit(void){
	// Not used yet!
}

// file end
//=================================================================================
