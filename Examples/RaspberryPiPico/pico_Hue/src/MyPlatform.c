/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 * Description:
 * This Module initializes all used Modules
 *
 */

// includes
//=================================================================================
#include "mybutton.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "SPI.c"
#include "LED.h"
#include "IR.h"
#include "HUEInterface.h"
#include "MainTask.h"

/* \Todo need to have it globally defined, as not present anywhere else */
uint32_t SystemCoreClock = 120000000;

// initializations and deinitializations
//=================================================================================
void MyPL_Init(void){
	LED_Init();
	HUEInterface_Init();
	IR_Init();
	MainTask_Init();
	MyButton_Init();
	McuRTT_Init();
	SPI_Init();
	stdio_init_all();
	//McuSystemView_Init();
}

void MyPL_DeInit(void){
	LED_Deinit();
	HUEInterface_Deinit();
	IR_Deinit();
	MainTask_Deinit();
	MyButton_Deinit();
	SPI_Deinit();
}
// file end
//=================================================================================
