/** ###################################################################
**     Filename  : Solar.C
**     Project   : SolarControl
**     Processor : MCF52259CAG80
**     Component : GDisplay
**     Version   : Component 01.186, Driver 01.00, CPU db: 3.00.000
**     Compiler  : CodeWarrior ColdFireV2 C Compiler
**     Date/Time : 2011-12-14, 08:49
**
**     Contents  :
**         enable Controller              	- void R_Enable(byte i)
**		   get State of Controller			- bool R_IsEnabled(byte i)
**		   enable pump1 					- void P1_Enable(byte i) 
**		   enable pump2 					- void P2_Enable(byte i) 
**		   get state of pump				- bool P_IsEnabled(byte i)
**		   Enable valve1					- void V1_Enable(byte i) 
**		   get state of valve1				- bool V1_IsEnabled(byte i)
**		   set actuator 					- void setAktuator(byte i)
**		   clear actuator 					- void clearAktuator(byte i)
**		   init IO-Expander					- void set_IOExpander(void)
**		   init. EnergyMeter				- void initImpuls(void)
**		   Solar Task						- void SOLAR_StartTask(SOLAR_WindowDesc *desc) 
**		   
**		   
**     (c) Copyright Barmettler Marc, 2010
**     http      : www.hslu.ch
**     mail      : barmettler.marc@stud.hslu.ch
** ###################################################################*/

/* MODULE Solar */

#include "platform.h"
#if PL_HAS_SOLAR
#include <string.h> 
#include "Solar.h"
#include "DrawSolar.h"
#include "App.h"
#include "UTIL1.h"
#include "UIG1.h"
#include "Helv08n.h"
#include "Helv10n.h"
#include "Helv12n.h"
#include "PCA1.h"
#include "RTC1.h"
#include "EInt3.h"


#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT   PL_FONT()
#else
  #define FONT		Helv12n_GetFont()
  #define FONT_12   Helv12n_GetFont()
  #define FONT_10   Helv10n_GetFont()
  #define FONT_08   Helv08n_GetFont()
#endif

static xTaskHandle xHandleTaskSolar;
static SOLAR_WindowDesc *appWp;
 
static char buf[sizeof("T1: -123.4°C")];

/* Flag EnergyMeter Interrupt 3 */
unsigned char SOLAR_EnergyMeterInterruptHappend = FALSE;

/* valvue of actual state of actuator */
Selection_R controller = CONTROLLER1;
Selection_P pump1 = PUMP1OFF;
Selection_P pump2 = PUMP2OFF;
Selection_V valve1 = VALVE1OFF;

/* build absolute value */
#define 	abs(x)   ((x) >= 0 ? (x) : -(x))

/*
** ===================================================================
**     Method      :  R_Enable(byte i)
**
**     Description :
**         enable selected Controller
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - value of selected controller
**         1			   - controller 1
**         2			   - controller 2
**         3			   - controller 3
**     Returns     : Nothing
** ===================================================================
*/
void R_Enable(byte i) {
	switch(i){
		case 1:	controller = CONTROLLER1;
				break;
		case 2:	controller = CONTROLLER2;
				break;
		case 3:	controller = CONTROLLER3;
				break;
	}
}

/*
** ===================================================================
**     Method      :  R_IsEnabled(byte i)
**
**     Description :
**         return state of selected controller
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - state of selected controller
**     Returns     : 
		   bool			   - state of controller
** ===================================================================
*/
bool R_IsEnabled(byte i){
	switch(i){
		case 1:	if(controller == CONTROLLER1) return TRUE;
				else return FALSE; 
				break;
		case 2:	if(controller == CONTROLLER2) return TRUE;
				else return FALSE;
				break;
		case 3:	if(controller == CONTROLLER3) return TRUE;
				else return FALSE;
				break;
	}
}

/*
** ===================================================================
**     Method      :  P1_Enable(byte i)
**
**     Description :
**         enable / disable selected Pump1
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - value of selected pump1
**         1			   - enable pump1
**         2			   - disable pump1
**     Returns     : Nothing
** ===================================================================
*/
void P1_Enable(byte i) {
	switch(i){
		case 1:	pump1 = PUMP1OFF;
				break;
		case 2:	pump1 = PUMP1ON;
				break;
	}
}

/*
** ===================================================================
**     Method      :  P2_Enable(byte i)
**
**     Description :
**         enable / disable selected Pump2
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - value of selected pump2
**         1			   - enable pump2
**         2			   - disable pump2
**     Returns     : Nothing
** ===================================================================
*/
void P2_Enable(byte i) {
	switch(i){
		case 1:	pump2 = PUMP2OFF;
				break;
		case 2:	pump2 = PUMP2ON;
				break;
	}
}

/*
** ===================================================================
**     Method      :  P_IsEnabled(byte i)
**
**     Description :
**         return state of selected pump
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - state of selected pump
**     Returns     : 
		   bool			   - state of pump
** ===================================================================
*/
bool P_IsEnabled(byte i){
	switch(i){
		case 1:	if(pump1 == PUMP1ON) return TRUE;
				else return FALSE; 
				break;
		case 2:	if(pump2 == PUMP2ON) return TRUE;
				else return FALSE;
				break;
	}
}

/*
** ===================================================================
**     Method      :  V1_Enable(byte i)
**
**     Description :
**         enable / disable selected valve1
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - value of selected valve1
**         1			   - disable valve 1
**         2			   - enable valve1(1)
**         3			   - enable valve1(2)
**     Returns     : Nothing
** ===================================================================
*/
void V1_Enable(byte i) {
	switch(i){
		case 1:	valve1 = VALVE1OFF;
				break;
		case 2:	valve1 = VALVE1ON1;
				break;
		case 3:	valve1 = VALVE1ON2;
				break;
	}
}

/*
** ===================================================================
**     Method      :  V_IsEnabled(byte i)
**
**     Description :
**         return state of selected valve
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - state of selected valve
**     Returns     : 
		   bool			   - state of valve
** ===================================================================
*/
bool V_IsEnabled(byte i){
	switch(i){
		case 1:	if(valve1 == VALVE1ON1) return TRUE;
				else return FALSE;
				break;
		case 2:	if(valve1 == VALVE1ON2) return TRUE;
				else return FALSE;
				break;
	}
}

/*
** ===================================================================
**     Method      :  setAktuator(byte i)
**
**     Description :
**         Set a actuator
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - actuator
**         0			   - pump1
**         1			   - valve1on
**         2			   - valve2on
**         3			   - pump2
**     Returns     : Nothing
** ===================================================================
*/
void setAktuator(byte i){	
	/* set pump1 */
	if(i == 0){
		pump1 = PUMP1ON;
		PCA1_SetOutputBit(0);
		pump2 = PUMP2OFF;
		PCA1_ClearOutputBit(3);
	}
	/* set pump2 */
	else if(i == 3){
		pump2 = PUMP2ON;
		PCA1_SetOutputBit(3);
		pump1 = PUMP1OFF;
		PCA1_ClearOutputBit(0);
	}
	/* set valve1  */
	else if(i == 1) {
		/* set valve1on1  */
		valve1 = VALVE1ON1;
		PCA1_SetOutputBit(1);
		/* clear valve1on2  */
		PCA1_ClearOutputBit(2);
	}
	else if(i == 2) {
		/* set valve1on2  */
		valve1 = VALVE1ON2;
		PCA1_SetOutputBit(1);
		/* clear valve1on2  */
		PCA1_ClearOutputBit(2);
	}
}

/*
** ===================================================================
**     Method      :  clearAktuator(byte i)
**
**     Description :
**         clear a actuator
**     Parameters  :
**         NAME            - DESCRIPTION
**         i               - actuator
**         0			   - pump1
**         1			   - valve1on
**         2			   - valve2on
**         3			   - pump2
**     Returns     : Nothing
** ===================================================================
*/
void clearAktuator(byte i){
	/* Clear Output Bit */ 
	PCA1_ClearOutputBit(i);
	/* turn off pump1 */
	if(i == 0) pump1 = PUMP1OFF;
	/* turn off pump2 */
	else if(i == 3) pump1 = PUMP2OFF;
	/* turn off valve1*/
	else if(i == 1 || i == 2) valve1 = VALVE1OFF;
}

/*
** ===================================================================
**     Method      :  set_IOExpander(void)
**
**     Description :
**         Init. IO-Expander
**         Set Input and Output (1 = Input / 0 = Output)
** 		   1100'0000 = 0xC0 (I0-I5 on output / I6-I7 on input)
** 		   Clear Output
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/
void set_IOExpander(void){
	PCA1_WriteConfig(0xC0);
    /* Clear Output */
    PCA1_WriteOutput(0);
}

/*
** ===================================================================
**     Method      :  InitImpuls(void)
**
**     Description :
**         Init. Energy Meter -> enable Interrupt 3!
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/
void InitImpuls(void){
	EInt3_Enable();
}


static void solarGraphW_WindowCallback(UI1_Window *window, UI1_Element *element, UI1_EventCallbackKind kind, UI1_Pvoid data) {
  (void)data;
  (void)window;
	if (kind==UI1_EVENT_CLICK) {
    if (UI1_EqualElement(element, &appWp->iconClose)) {
      FRTOS1_vTaskDelete(xHandleTaskSolar); 
      APP_SetApplicationMode(APP_MODE_MAIN_MENU);
      return;
    }
  }
}

/*
** ===================================================================
**     Method      :  portTASK_FUNCTION(TaskSolar, pvParameters)
**
**     Description :
**         Solar Main

**     Parameters  :
**         NAME            - DESCRIPTION
**         TaskSolar       - Solar Task
**         pvParameters	   - parametes (Name, Stack, Prio.)
**     Returns     : Nothing
** ===================================================================
*/
static portTASK_FUNCTION(TaskSolar, pvParameters) {
  SOLAR_WindowDesc *ui = (SOLAR_WindowDesc*)pvParameters;
  
  /* Variables for the calculation of the energy*/
  bool energyOn = FALSE;				
  byte inputBit;
  int16_t const spezWaermeKap = 4184;  	// J /(kg•K)  
  int16_t const dichteWasser = 1;		// 0.9982 kg/dm3
  word temp[6];							// Temperaturen 1-6
  int energy1 = 0;
  int energy2 = 0;
  char energyVal1[14];					// angezeigter Wert auf Display 
  char energyVal2[14];					// angezeigter Wert auf Display 
  int16_t tempVorlauf;					// Temperatur im Vorlauf
  int16_t tempRuecklauf;				// Temperatur im Rücklauf
  int16_t deltaT;						// Temperaturdifferenz Rück- & Vorlauf
  int16_t oldTimeInMin;					// Wert für die Zeitmessung 
  int16_t newTimeInMin;					// von einer Minute!!
  TTIME time;
  
  appWp = ui;
  
  UTI1_Init();
  /* Init. Interrupt */
  InitImpuls(); 
  /* clear all output Bits */
  PCA1_WriteOutput(0);
  /* Init. Time & Date */
  initTimeDate(ui);
  /* Init. EnergyMeter Time */
  RTC1_GetTime(&time);
  oldTimeInMin = time.min++;
  /* Reset InterruptFlag */
  SOLAR_EnergyMeterInterruptHappend = FALSE;
  
  /* Draw Controller */
  switch(controller){
  	  case CONTROLLER1:	drawController1(ui);
						/* measure Energy */
						energyOn = TRUE;
						break;
  	  case CONTROLLER2:	drawController2(ui);
						/* don't measure Energy */
						energyOn = FALSE;
						break;
  	  case CONTROLLER3:	drawController3(ui);
						/* measure Energy */
						energyOn = TRUE;
						break;
  }
  
	/* update the screen */
	UI1_UpdateScreen(&ui->screen);	

  for (;;) {
	  /* call the actual selected controller */
	  switch(controller){
	  	case CONTROLLER1: 	updateText(ui);
	  						control1();
	  						break;
	  		  
	  	case CONTROLLER2: 	updateText(ui);
							control2();
							break;
	  					
	  	case CONTROLLER3: 	updateText(ui);
							control3();		
							break;
	  }
	
	// if energymeter is used
	if(energyOn == TRUE){
		// if interrupt is activated
		if (SOLAR_EnergyMeterInterruptHappend) {
			// Clear InterruptFlag
			SOLAR_EnergyMeterInterruptHappend = FALSE;
			// The interrupt is deactivated when the input returns to its 
			// previous state or the Input Port register is read
			inputBit = PCA1_ReadInput();
			// calc deltaT 
			getTemp(temp);
			tempVorlauf = PtConv1_PtRtoTemperatur(temp[1]);
			tempRuecklauf = PtConv1_PtRtoTemperatur(temp[2]);
			// in deziDegree!!
			deltaT = abs(tempVorlauf - tempRuecklauf);
			// I1 is set -> Bit 6
			if(inputBit & (byte)(1<<6)){
				// in deziJoule
				energy1 += (dichteWasser*spezWaermeKap*deltaT);
			}
			// I2 is set -> Bit 7
			if(inputBit & (byte)(1<<7)){
				// in deziJoule
				energy2 += (dichteWasser*spezWaermeKap*deltaT);
			}
		}
		
		// The interrupt is deactivated when the input returns to its 
		// previous state or the Input Port register is read!!!
		inputBit = PCA1_ReadInput();
		
		/* get actual Time */
		RTC1_GetTime(&time);
		newTimeInMin = time.min;
		if(oldTimeInMin == newTimeInMin){		
			/* calculate energy in Wmin */
			/* for change Wh -> energy/3600 + update method getEnergy, change Wmin in Wh*/
			/* energy is in deziJoule -> /10 */
			energy1 = energy1/60/10;
			energy2 = energy2/60/10;
			/* update Energy values on display*/
			getEnergy((char*)energyVal1,1,energy1);
			(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtI1, sizeof(ui->txtBufI1), (unsigned char*)energyVal1);
			getEnergy((char*)energyVal2,2,energy1);
			(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtI2, sizeof(ui->txtBufI2), (unsigned char*)energyVal2);
			/* reset energy */
			energy1 = 0;
			energy2 = 0;
			/* new interrupt Time */
			oldTimeInMin++;
			/* catch Overflow */
			if(oldTimeInMin >= 60){
				oldTimeInMin = 0;
			}
		}
	}
	
	/* update Time and Date */
	setTimeDate(ui);
    FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  } /* for */
}

/*
** ===================================================================
**     Method      :  SOLAR_StartTask(SOLAR_WindowDesc *desc) 
**
**     Description :
**         init. Solar Task
**         start Solar Task
**     Parameters  :
**         NAME            - DESCRIPTION
**         desc            - parameters of window Solar
**     Returns     : Nothing
** ===================================================================
*/
void SOLAR_StartTask(SOLAR_WindowDesc *desc) {
  UI1_PixelDim yPos, h;
  
  UI1_CreateScreen(&desc->screen, UI1_COLOR_WHITE);
  (void)UI1_CreateWindow(&desc->screen, &desc->window, UI1_COLOR_WHITE, 0, 0, UI1_GetWidth(), UI1_GetHeight());
  (void)UI1_CreateHeader(&desc->window, &desc->header, (unsigned char*)"Solar Control", FONT, UI1_COLOR_BLUE);
  UI1_ChangeTextFgColor(&desc->header.element, UI1_COLOR_WHITE);
  UI1_SetWindowEventCallback(&desc->window, solarGraphW_WindowCallback);
  /* Icon: Close */
  h = (UI1_PixelDim)(UI1_GetElementHeight(&desc->header));
  (void)UI1_CreateIcon(&desc->window, &desc->iconClose, 1, 1, (UI1_PixelDim)(h-2), (UI1_PixelDim)(h-2), UI1_ICON_CLOSE);
  desc->iconClose.element.prop.flags |= UI1_FLAGS_ALIGN_RIGHT;
  UI1_OnWindowResize(&desc->window); /* right align element(s) if needed */
  UI1_ChangeElementColor(&desc->iconClose, UI1_COLOR_BLUE);
  UI1_ChangeIconFgColor(&desc->iconClose, UI1_COLOR_WHITE);
  UI1_EnableElementSelection(&desc->iconClose);
  yPos = (UI1_PixelDim)(UI1_GetElementPosY(&desc->window)+UI1_GetElementHeight(&desc->header));

  appWp = desc; /* need to set it, as the update below will call the callback, and we need it there! */
  /* update the screen */
  UI1_UpdateScreen(&desc->screen);

  FRTOS1_xTaskCreate(TaskSolar, (signed portCHAR *)"Solar", configMINIMAL_STACK_SIZE+300, desc, tskIDLE_PRIORITY+3, &xHandleTaskSolar);
}
#endif /* PL_HAS_SOLAR */