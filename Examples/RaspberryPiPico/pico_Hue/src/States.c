/*
 * Hue Apple IR Remote
 * Author: 	Joshua Wyss
 * Date: 	24.11.2022
 *
 *This module defines all the states of the statemachines
 */

#include <stdbool.h>
#include "pico/stdlib.h"
#include "McuRTOS.h"
#include "HUEInterface.h"
#include "IR.h"
#include "LED.h"
#include "mybutton.h"
#include "SPI.h"
#include "States.h"
#include "LED.h"

typedef enum{/* Used to dim the Lamp */
	DimmStep1,
	DimmStep2,
	DimmStep3,
}DimmStep_e;

static DimmStep_e actual_DimmStep;
static DimmStep_e old_Dimmstep = DimmStep1;
static State_e actual_State = Initialisation; //define the startup state
static bool ENTRY = true; 	//This Variable makes sure that the entry condition is done only once
static uint8_t IRRetryCounter = 0; //Counter Variable for IR Retrys

//Settings
static const int IRRetrys = 2;
static const int TimeToWaitAfterLampToggleCommand = 1000; //Lamp needs this time to turn on/off
static const int TimeToWaitAfterAppToggleCommand = 1000;  //App needs this time to turn on/off
static const float DutyCycleThreshold1 = 25;
static const float DutyCycleThreshold2 = 98;

//this Function returns the actual State of the FSM
State_e GetState(void){
	return actual_State;
}

void State_Initialisation(void){
	//ENTRY
	//==============================================================
	if(ENTRY){
		ENTRY = false; 			//only do the entry statement once
		RGB_Controll(1, 1, 1);
		vTaskDelay(pdMS_TO_TICKS(1000)); //Wait 1 Second to properly boot
	}

	//DO
	//==============================================================

	//EXIT
	//==============================================================
	if( (Get_App_State()) && (Get_Lamp_State()) ){
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = LampIsON;
	}
	if( (!Get_App_State()) && (!Get_Lamp_State()) ){
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = LampIsOFF;
	}
	if( !(Get_App_State()) && (Get_Lamp_State()) ){
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = TurnAppON;
	}
	if( (Get_App_State()) && (!Get_Lamp_State()) ){
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = TurnAppOFF;
	}
}

void State_LampIsON(void){
	//ENTRY
	//==============================================================
	if(ENTRY){
		ENTRY = false; //only do the entry statement once
		//nothing to be done at entry
		RGB_Controll(0,1,0);

		old_Dimmstep = actual_DimmStep;
	}

	//DO
	//==============================================================
	if(GetButtonState()){//turn lamp off on button press
		IR_PowerOnOff_tx();
	}

	if(actual_DimmStep!= old_Dimmstep){
		switch(actual_DimmStep){
			case DimmStep1:
				IR_Up_tx(3);
				IR_Down_tx(2);
				break;
			case DimmStep2:
				IR_Up_tx(3);
				IR_Down_tx(1);
				break;
			case DimmStep3:
				IR_Up_tx(3);
				break;
			default:

				break;
		}
		old_Dimmstep = actual_DimmStep;
	}

	if(Get_App_DutyCycle() < DutyCycleThreshold1){
		actual_DimmStep = DimmStep1;
	}else if(Get_App_DutyCycle() < DutyCycleThreshold2){
		actual_DimmStep = DimmStep2;
	}else{
		actual_DimmStep = DimmStep3;
	}

   vTaskDelay(pdMS_TO_TICKS(50));


	//EXIT
	//==============================================================
	if(!Get_App_State()){	//App was turned OFF, Lamp needs also to be turned OFF
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = TurnLampOFF;
	}
	if(!Get_Lamp_State()){	//Lamp was turned OFF, App needs also to be turned OFF
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = TurnAppOFF;
	}
}

void State_LampIsOFF(void){
	//ENTRY
	//==============================================================
	if(ENTRY){
		ENTRY = false; //only do the entry statement once
		RGB_Controll(1,0,0); //turn the red part of the RGB LED on
	}
	//DO
	//==============================================================
	if(GetButtonState()){//turn lamp on, if the button was pressed
		IR_PowerOnOff_tx();
	}
	//EXIT
	//==============================================================
	if(Get_App_State()){	//app was turned ON, lamp needs also to be turned ON
		ENTRY = true; 		//do the entry statement in the next state
		actual_State = TurnLampON;
	}
	if(Get_Lamp_State()){	//lamp was turned ON, the app needs also to be turned ON
		ENTRY = true; 		//do the entry statement in the next state
		actual_State = TurnAppON;
	}
}

void State_TurnLampOFF(void){
	//ENTRY -> this part of the code will only run once
	//==============================================================
	if(ENTRY){
		ENTRY = false; 			//only do the entry statement once
		RGB_Controll(0,0,1);	//turn the blue part of the RGB LED on, the other parts off
	}

	//DO -> this part of the code is running continuous until an exit statement becomes true
	//==============================================================
	Toggle_Lamp_State(); 		//Lamp needs to be turned OFF
	IRRetryCounter++;
	vTaskDelay(pdMS_TO_TICKS(TimeToWaitAfterLampToggleCommand)); //wait to let the lamp turn off

	//EXIT -> if one of these Statements becomes true, the state will be changed
	//==============================================================
	if(!Get_Lamp_State()){			//Lamp was turned off
		ENTRY = true; 				//do the entry statement in the next State
		IRRetryCounter = 0;			//reset the retry counter
		actual_State = LampIsOFF;	//set the next state
	}

	if(IRRetryCounter>=IRRetrys){	//Lamp couldn't be turned off
		ENTRY = true; 				//do the entry statement in the next State
		IRRetryCounter = 0;			//reset the retry counter
		actual_State = TurnAppON;	//set the next state
	}
}

void State_TurnAppOFF(void){
	//ENTRY
	//==============================================================
	if(ENTRY){
		ENTRY = false; 			//only do the entry statement once
		RGB_Controll(0,0,1);
	}
	//DO
	//==============================================================
	Toggle_App_State(); 	//App needs to be turned OFF
	vTaskDelay(pdMS_TO_TICKS(TimeToWaitAfterAppToggleCommand));
	//while(!Get_App_State()); //wait until App is off
	//EXIT
	//==============================================================
	if(!Get_App_State()){	//App is turned OFF
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = LampIsOFF;
	}
}

void State_TurnLampON(void){
	//ENTRY
	//==============================================================
	if(ENTRY){
		ENTRY = false; 			//only do the entry statement once
		IRRetryCounter = 0;	//Reset the Retry Counter
		RGB_Controll(0,0,1);
	}
	//DO
	//==============================================================
	Toggle_Lamp_State(); 	//Lamp needs to be turned ON
	IRRetryCounter++;
	vTaskDelay(pdMS_TO_TICKS(TimeToWaitAfterLampToggleCommand));
	//EXIT
	//==============================================================
	if(Get_Lamp_State()){	//Lamp was turned ON
		ENTRY = true; 		//do the entry statement in the next State
		IRRetryCounter = 0;	//Reset the Retry Counter
		actual_State = LampIsON;
	}
	if(IRRetryCounter>=IRRetrys){	//Lamp couldn't be turned on
		ENTRY = true; 				//do the entry statement in the next State
		IRRetryCounter = 0;			//Reset the Retry Counter
		actual_State = TurnAppOFF;
	}
}

void State_TurnAppON(void){
	//ENTRY
	//==============================================================
	if(ENTRY){
		ENTRY = false; 			//only do the entry statement once
		RGB_Controll(0,0,1);
	}
	//DO
	//==============================================================
	Toggle_App_State(); 	//App needs to be turned ON
	vTaskDelay(pdMS_TO_TICKS(TimeToWaitAfterAppToggleCommand));
	//EXIT
	//==============================================================
	if(Get_App_State()){	//App is turned ON
		ENTRY = true; 		//do the entry statement in the next State
		actual_State = LampIsON;
	}
}

// file end
//=================================================================================
