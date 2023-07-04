/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 * Description:
 * In this Module is the Statemachine which makes the Project work.
 *
 */

#include "McuRTOS.h"
#include "States.h"

static void MainTask(void * pv){

	for(;;) {
		/*FSM*/
		switch(GetState()){
			case Initialisation:
				State_Initialisation();
				break;
			case LampIsON:
				State_LampIsON();
				break;
			case LampIsOFF:
				State_LampIsOFF();
				break;
			case TurnLampOFF:
				State_TurnLampOFF();
				break;
			case TurnAppOFF:
				State_TurnAppOFF();
				break;
			case TurnLampON:
				State_TurnLampON();
				break;
			case TurnAppON:
				State_TurnAppON();
				break;
			default:
				//Code should never get here
				break;
		}
	vTaskDelay(pdMS_TO_TICKS(50));
	}
}

void MainTask_Init(void){
	BaseType_t res;

	res = xTaskCreate(	MainTask,  		//function
						"mainTask" ,		//Kernel awareness name
						500/sizeof(StackType_t), //stack
						(void*)NULL,	// Task Parameter
						tskIDLE_PRIORITY+3,	//Priority
						(TaskHandle_t*)NULL); //Task Handle

	if(res!=pdPASS){/*error*/
		for(;;){ __asm volatile ("nop");}
	}
}

void MainTask_Deinit(void){
	//Not used yet!
}
// file end
//=================================================================================
