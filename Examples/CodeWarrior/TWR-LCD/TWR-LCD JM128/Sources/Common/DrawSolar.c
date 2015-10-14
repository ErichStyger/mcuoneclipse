/** ###################################################################
**     Filename  : DrawSolar.c
**     Project   : SolarControl
**     Processor : MCF52259CAG80
**     Component : GDisplay
**     Version   : Component 01.186, Driver 01.00, CPU db: 3.00.000
**     Compiler  : CodeWarrior ColdFireV2 C Compiler
**     Date/Time : 2011-12-14, 08:49
**
**     Contents  :
**          get temperatur 				- void getTemp(word *temp)
**			calculate temperatur		- char calcTemp(int16_t temp, int8_t i, char *tempBuf)
**			get Energy					- void getEnergy(char *energyBuf, byte i, int energy)
**			update Text on Display		- void updateText(SOLAR_WindowDesc *ui)
**			init. Time and Date			- void initTimeDate(SOLAR_WindowDesc *ui)
**			set Time and Date			- void setTimeDate(SOLAR_WindowDesc *ui)
**			control controller 1		- void control1(void)
**			control controller 2		- void control2(void)
**			control controller 3		- void control3(void)
**			draw horizontally Sensor	- void drawSens(UI1_PixelDim xPos,UI1_PixelDim yPos)
**			draw vertical sensor		- void drawSensHor(UI1_PixelDim xPos,UI1_PixelDim yPos)
**			draw pump					- void drawPump(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**			draw valve					- void drawValve(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**			draw enery meter			- void drawEnergyMeter(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**			draw panel 					- void drawPanel(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0, bool typ)
**			draw tank					- void drawTank(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**			draw controller 1			- void drawController1(SOLAR_WindowDesc *ui)
**			draw controller 2			- void drawController2(SOLAR_WindowDesc *ui)
**			draw controller 3			- void drawController3(SOLAR_WindowDesc *ui)	   
**		   
**     (c) Copyright Barmettler Marc, 2010
**     http      : www.hslu.ch
**     mail      : barmettler.marc@stud.hslu.ch
** ###################################################################*/

/* MODULE DrawSolar */

#include "Platform.h"
#if PL_HAS_SOLAR
#include <string.h> 
#include "DrawSolar.h"
#include "UTIL1.h"
#include "Helv08n.h"
#include "Helv10n.h"
#include "Helv12n.h"
#include "UTI1.h"
#include "UTI2.h"
#include "RTC1.h"
#include "PtConv1.h"

#if PL_USE_SINGLE_FONT /* use only one font */
  #define FONT   PL_FONT()
#else
  #define FONT		Helv12n_GetFont()
  #define FONT_12   Helv12n_GetFont()
  #define FONT_10   Helv10n_GetFont()
  #define FONT_08   Helv08n_GetFont()
#endif

static bool statePump1 = FALSE;

/* build absolute value */
#define 	abs(x)   ((x) >= 0 ? (x) : -(x))

/*
** ===================================================================
**     Method      :  getTemp(word *temp)
**
**     Description :
**         return array pointer of temperatur
**     Parameters  :
**         NAME            - DESCRIPTION
**         temp            - array pointer of temperatures
**     Returns     : Nothing
** ===================================================================
*/
void getTemp(word *temp){
	byte i;
	word value1[6]; /* 6 Temperatursensoren */
	
	if (UTI1_getUTIresults(value1) == ERR_OK){
		for(i = 0; i < 3 ; i++){
			temp[i] = value1[i];
		}
	}
	if (UTI2_getUTIresults(value1) == ERR_OK){
		for(i = 0; i < 3 ; i++){
			temp[i+3] = value1[i];
		}	
	}
}

/*
** ===================================================================
**     Method      :  calcTemp(int16_t temp, int8_t i, char *tempBuf)
**
**     Description :
**         save the actual temperatur in a char of array
**     Parameters  :
**         NAME            - DESCRIPTION
**         temp            - actual temperatures
**         i			   - designator of temp.
**         tempBuf		   - array pointer of temperatures
**     Returns     : 
		   char		       - return array of calculated temp.
** ===================================================================
*/
char calcTemp(int16_t temp, int8_t i, char *tempBuf){
	tempBuf[0] = 'T';
	tempBuf[1] = (char)('0' + i);
	tempBuf[2] = ':';
	tempBuf[3] = ' ';
	i = 0;
	if(temp == 1000){
		tempBuf[4] = '1';
		tempBuf[5] = '0';
		tempBuf[6] = '0';
		tempBuf[7] = '°';
		tempBuf[8] = 'C';
		tempBuf[9] = ' ';
		tempBuf[10] = ' ';
		tempBuf[11] = ' ';
		tempBuf[12] = '\0';
	}
	else if(temp >= 0){
		tempBuf[4] = (char)('0' + ((temp / 1000) % 10));
		/* If first digit is zero, delete this digit */
		if(tempBuf[4] == '0') i++;
		tempBuf[5-i] = (char)('0' + ((temp / 100) % 10));
		/* If second digit is zero, delete this digit */
		if(tempBuf[5-i] == '0') i++;
		tempBuf[6-i] = (char)('0' + ((temp / 10) % 10));
		tempBuf[7-i] = '.';
		tempBuf[8-i] = (char)('0' + (temp % 10));
		tempBuf[9-i] = '°';
		tempBuf[10-i] = 'C';
		/* removes the empty spaces */
		if(i == 1){
			tempBuf[10] = ' ';
		}
		if(i == 2){
			tempBuf[9] = ' ';
			tempBuf[10] = ' ';
		}
		tempBuf[11] = ' ';	
		tempBuf[12] = '\0';	
}
	else{
		tempBuf[0] = 'T';
		tempBuf[1] = (char)('0' + i);
		tempBuf[2] = ':';
		tempBuf[3] = ' ';
		i = 0;
		temp = abs(temp);
		tempBuf[4] = '-';
		tempBuf[5] = (char)('0' + ((temp / 1000) % 10));
		/* If first digit is zero, delete this digit */
		if(tempBuf[5] == '0') i++;
		tempBuf[6-i] = (char)('0' + ((temp / 100) % 10));
		/* If second digit is zero, delete this digit */
		if(tempBuf[6-i] == '0') i++;
		tempBuf[7-i] = (char)('0' + ((temp / 10) % 10));
		tempBuf[8-i] = '.';
		tempBuf[9-i] = (char)('0' + (temp % 10));
		tempBuf[10-i] = '°';
		tempBuf[11-i] = 'C';
		/* removes the empty spaces */
		if(i == 1){
			tempBuf[11] = ' ';
		}
		if(i == 2){
			tempBuf[10] = ' ';
			tempBuf[11] = ' ';
		}
		tempBuf[12] = '\0';	
	}
	
}

/*
** ===================================================================
**     Method      :  getEnergy(char *energyBuf, byte i, int energy)
**
**     Description :
**         save the actual energy in a char of array
**     Parameters  :
**         NAME            		- DESCRIPTION
**         energyBuf       		- pointer on actual energy to save
**         energy			   	- actual energy
**     Returns     : Nothing
** ===================================================================
*/
void getEnergy(char *energyBuf, byte i, int energy){
	energyBuf[0] = 'I';
	energyBuf[1] = (char)('0' + i);
	energyBuf[2] = ':';
	energyBuf[3] = ' ';
	energyBuf[4] = (char)('0' + ((energy / 1000) % 10));
	i = 0;
	/* If first digit is zero, delete this digit */
	if(energyBuf[4] == '0') i++;
	energyBuf[5-i] = (char)('0' + ((energy / 100) % 10));
	/* If second digit is zero, delete this digit */
	if(energyBuf[5-i] == '0') i++;
	energyBuf[6-i] = (char)('0' + ((energy / 10) % 10));
	energyBuf[7-i] = '.';
	energyBuf[8-i] = (char)('0' + (energy % 10));
	energyBuf[9-i] = 'W';
	energyBuf[10-i] = 'm';
	energyBuf[11-i] = 'i';
	energyBuf[12-i] = 'n';
	/* removes the empty spaces */
	if(i == 1){
		energyBuf[12] = ' ';
	}
	if(i == 2){
		energyBuf[11] = ' ';
		energyBuf[12] = ' ';
	}
	energyBuf[13] = '\0';		
}


/*
** ===================================================================
**     Method      :  updateText(SOLAR_WindowDesc *ui)
**
**     Description :
**         update all values (temperatures, state of pump, state of valve)
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui       			- pointer on actual window
**     Returns     : Nothing
** ===================================================================
*/
void updateText(SOLAR_WindowDesc *ui){
	unsigned char buf[sizeof("Date: 07:07:07")];
	word temp[6];
	char tempVal[13];
	
	getTemp(temp);
	
	calcTemp(PtConv1_PtRtoTemperatur(temp[0]),1, (char*)tempVal);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtT1, sizeof(ui->txtBufT1), (unsigned char*)tempVal);
	
	calcTemp(PtConv1_PtRtoTemperatur(temp[1]),2, (char*)tempVal);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtT2, sizeof(ui->txtBufT2), (unsigned char*)tempVal);
		
	calcTemp(PtConv1_PtRtoTemperatur(temp[2]),3, (char*)tempVal);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtT3, sizeof(ui->txtBufT3), (unsigned char*)tempVal);
			
	calcTemp(PtConv1_PtRtoTemperatur(temp[3]),4, (char*)tempVal);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtT4, sizeof(ui->txtBufT4), (unsigned char*)tempVal);
				
	calcTemp(PtConv1_PtRtoTemperatur(temp[4]),5, (char*)tempVal);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtT5, sizeof(ui->txtBufT5), (unsigned char*)tempVal);
					
	calcTemp(PtConv1_PtRtoTemperatur(temp[5]),6, (char*)tempVal);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtT6, sizeof(ui->txtBufT6), (unsigned char*)tempVal);

	/* Pump 1 */
	UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"P1: ");  
	if(P_IsEnabled(1)) UTIL1_strcat(buf,sizeof(buf),(unsigned char*)"On");
	else UTIL1_strcat(buf,sizeof(buf),(unsigned char*)"Off");
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtP1, sizeof(ui->txtBufP1), (unsigned char*)buf);
	
	/* Pump 2 */
	UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"P2: ");  
	if(P_IsEnabled(2)) UTIL1_strcat(buf,sizeof(buf),(unsigned char*)"On");
	else UTIL1_strcat(buf,sizeof(buf),(unsigned char*)"Off");
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtP2, sizeof(ui->txtBufP2), (unsigned char*)buf);
	
	/* Valve 1 */
	UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"V1: ");  
	if(V_IsEnabled(1)) UTIL1_strcat(buf,sizeof(buf),(unsigned char*)"S1 On");
	else if(V_IsEnabled(2)) UTIL1_strcat(buf,sizeof(buf),(unsigned char*)"S2 On");
	else UTIL1_strcat(buf,sizeof(buf),(unsigned char*)"Off");
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtV1, sizeof(ui->txtBufV1), (unsigned char*)buf);
}

/*
** ===================================================================
**     Method      :  initTimeDate(SOLAR_WindowDesc *ui)
**
**     Description :
**         set text of time and date on default coordinates
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui       			- pointer on actual window
**     Returns     : Nothing
** ===================================================================
*/
void initTimeDate(SOLAR_WindowDesc *ui){  
	/* Date*/
	UTIL1_strcpy(ui->txtBufDate, sizeof(ui->txtBufDate), (unsigned char*)"init");
	(void)UI1_CreateText(&ui->window, &ui->txtDate, 245,20, 0, 0, ui->txtBufDate, FONT_08);
	/* Time */
	UTIL1_strcpy(ui->txtBufTime, sizeof(ui->txtBufTime), (unsigned char*)"init");
	(void)UI1_CreateText(&ui->window, &ui->txtTime, 245,30, 0, 0, ui->txtBufTime, FONT_08);
}


/*
** ===================================================================
**     Method      :  setTimeDate(SOLAR_WindowDesc *ui)
**
**     Description :
**         set actual time and date
**         update window with new time and date
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui       			- pointer on actual window
**     Returns     : Nothing
** ===================================================================
*/
void setTimeDate(SOLAR_WindowDesc *ui){
	TTIME time;
	TDATE date;
	unsigned char buf[sizeof("Date: 07:07:07")];
	unsigned char ucBuf[9];
	RTC1_GetTimeDate(&time, &date);

	/* save Date */
	ucBuf[0] = (char)(date.day / 10 + '0');                      
	ucBuf[1] = (char)(date.day % 10 + '0');
	ucBuf[2] = '.';
	ucBuf[3] = (char)(date.month / 10 + '0');
	ucBuf[4] = (char)(date.month % 10 + '0');
	ucBuf[5] = '.';
	ucBuf[6] = (char)(date.year / 10 + '0');
	ucBuf[7] = (char)(date.year % 10 + '0');
	ucBuf[8] = '\0';
	
	/* Set Date */
	UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Date: ");  
	UTIL1_strcat(buf,sizeof(buf),ucBuf);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtDate, sizeof(ui->txtBufDate), buf);
     
	/* save Time */
	ucBuf[0] = (char)(time.hour / 10 + '0');
	ucBuf[1] = (char)(time.hour % 10 + '0');
	ucBuf[2] = ':';
	ucBuf[3] = (char)(time.min / 10 + '0');
	ucBuf[4] = (char)(time.min % 10 + '0');
	// If seconds is displayed -> commented out implementation
	ucBuf[5] = ' '; 	// ':';
	ucBuf[6] = ' '; 	// (char)(time.sec / 10 + '0');
	ucBuf[7] = ' ';		// (char)(time.sec % 10 + '0');   
	ucBuf[8] = '\0';
	
	/* Set Time */
	UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Time: ");  
	UTIL1_strcat(buf,sizeof(buf),ucBuf);
	(void)UI1_ChangeText(&ui->window, (UI1_Element *)&ui->txtTime, sizeof(ui->txtBufTime), buf);
}


/*
** ===================================================================
**     Method      :  control1(void)
**
**     Description :
**         control Controller 1
**     Parameters  :
**         NAME      Nothing
**     Returns     : Nothing
** ===================================================================
*/
void control1(void){
	word temp[6];
	bool Pump1 = FALSE;
	/* temperatures in dezidegree!!! */
	int8_t einschaltDeltaT = 30;
	int8_t ausschaltDeltaT = 50;
	int16_t maxTempTank = 900;
	TTIME time;
	
	/* read Temperatures */
	getTemp(temp);
	/* read Time */
	RTC1_GetTime(&time);
	

	
    /* Pump is turned on every half hour so that the heat is distributed in the liquid */
    //if(time.min >= 30 && time.min <= 35) setAktuator(0);
    //else clearAktuator(0);
    
	/* maximum temperature reached in the tank */
	if(PtConv1_PtRtoTemperatur(temp[3]) >= maxTempTank) {
		clearAktuator(0);
		statePump1 = FALSE;
	}
	/* temperatur is under the maximum */
	else {
		/* Once the temperature at the collector is higher than in tank, the pump is switched on
		 * on and off is implemented with hysterese
		 */
		if(statePump1 == FALSE){
			if(PtConv1_PtRtoTemperatur(temp[0]) >= PtConv1_PtRtoTemperatur(temp[3]) + einschaltDeltaT){
				setAktuator(0);
				statePump1 = TRUE;
			}
		}
		else if(statePump1 == TRUE){
			if(PtConv1_PtRtoTemperatur(temp[0]) + ausschaltDeltaT <= PtConv1_PtRtoTemperatur(temp[3])){
				clearAktuator(0);
				statePump1 = FALSE;
			}
		}
	}
}


/*
** ===================================================================
**     Method      :  control2(void)
**
**     Description :
**         control Controller 2
**     Parameters  :
**         NAME      Nothing
**     Returns     : Nothing
** ===================================================================
*/
void control2(void){
	
	
	
/*
** ===================================================================
**     Method      :  control3(void)
**
**     Description :
**         control Controller 3
**     Parameters  :
**         NAME      Nothing
**     Returns     : Nothing
** ===================================================================
*/
}
void control3(void){
	
}

/*
** ===================================================================
**     Method      :  drawSens(UI1_PixelDim xPos,UI1_PixelDim yPos)
**
**     Description :
**         draw a vertical sensor
**     Parameters  :
**         NAME            		- DESCRIPTION
**         xPos       			- x coordinate of sensor
**         yPos       			- y coordinate of sensor
**     Returns     : Nothing
** ===================================================================
*/
void drawSens(UI1_PixelDim xPos,UI1_PixelDim yPos){
	GDisp1_DrawFilledBox(xPos,yPos-5,2,5,UI1_COLOR_BLACK);
	GDisp1_DrawFilledCircle(xPos+1,yPos-9,3,UI1_COLOR_ORANGE);
}


/*
** ===================================================================
**     Method      :  drawSensHor(UI1_PixelDim xPos,UI1_PixelDim yPos)
**
**     Description :
**         draw a horizontally sensor
**     Parameters  :
**         NAME            		- DESCRIPTION
**         xPos       			- x coordinate of sensor
**         yPos       			- y coordinate of sensor
**     Returns     : Nothing
** ===================================================================
*/
void drawSensHor(UI1_PixelDim xPos,UI1_PixelDim yPos){
	GDisp1_DrawFilledBox(xPos,yPos,5,2,UI1_COLOR_BLACK);
	GDisp1_DrawFilledCircle(xPos+8,yPos,3,UI1_COLOR_ORANGE);
}


/*
** ===================================================================
**     Method      :  drawPump(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**
**     Description :
**         draw a pump
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**         x0       			- x coordinate center of circle
**         y0       			- y coordinate center of circle
**     Returns     : Nothing
** ===================================================================
*/
void drawPump(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0){
	GDisp1_DrawCircle(x0+12,y0,12,GDisp1_COLOR_BLACK);
	GDisp1_DrawCircle(x0+12,y0,11,GDisp1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0,y0,x0+18,y0-10,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+1,y0,x0+17,y0-9,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+18,y0-10,x0+18,y0+10,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+17,y0-9,x0+17,y0+9,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+18,y0+10,x0,y0,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+17,y0+9,x0+1,y0,UI1_COLOR_BLACK);
}


/*
** ===================================================================
**     Method      :  drawValve(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**
**     Description :
**         draw a valve
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**         x0       			- x coordinate center of valve
**         y0       			- y coordinate center of valve
**     Returns     : Nothing
** ===================================================================
*/
void drawValve(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0){
	GDisp1_DrawFilledCircle(x0,y0,3,GDisp1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+3,y0+1,x0+10,y0+6,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+10,y0-6,x0+10,y0+6,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+3,y0-1,x0+10,y0-6,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0-3,y0+1,x0-10,y0+6,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0-10,y0-6,x0-10,y0+6,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0-3,y0-1,x0-10,y0-6,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0-1,y0+3,x0-6,y0+10,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0-6,y0+10,x0+6,y0+10,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+1,y0+3,x0+6,y0+10,UI1_COLOR_BLACK);
}



/*
** ===================================================================
**     Method      :  drawEnergyMeter(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**
**     Description :
**         draw a energy-meter
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**         x0       			- x coordinate center of circle
**         y0       			- y coordinate center of circle
**     Returns     : Nothing
** ===================================================================
*/
void drawEnergyMeter(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0){
	GDisp1_DrawCircle(x0,y0,12,GDisp1_COLOR_BLACK);
	GDisp1_DrawCircle(x0,y0,11,GDisp1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+4,y0-4,x0,y0+4,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+5,y0-4,x0+1,y0+4,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0-4,y0-4,x0,y0+4,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0-5,y0-4,x0-1,y0+4,UI1_COLOR_BLACK);
}



/*
** ===================================================================
**     Method      :  drawPanel(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0, bool type)
**
**     Description :
**         draw a panal (increasing or falling)
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**         x0       			- x coordinate of panel
**         y0       			- y coordinate of panel
**         type					- type of panel (increasing or falling)
**     Returns     : Nothing
** ===================================================================
*/
void drawPanel(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0, bool type){
	if(type == TRUE){
		UI1_DrawLine(&ui->window,x0+82,y0-63,x0-3,y0-3,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+83,y0-62,x0-2,y0-2,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+84,y0-61,x0-1,y0-1,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0-3,y0-3,x0+1,y0+1,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0-2,y0-2,x0+2,y0+2,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0-1,y0-1,x0+3,y0+3,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+1,y0+1,x0+86,y0-59,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+2,y0+2,x0+87,y0-58,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+3,y0+3,x0+88,y0-57,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+86,y0-59,x0+82,y0-63,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+87,y0-58,x0+83,y0-62,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+88,y0-57,x0+84,y0-61,UI1_COLOR_BLACK);
	}
	else {
		UI1_DrawLine(&ui->window,x0+1,y0-1,x0+86,y0+59,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+2,y0-2,x0+87,y0+58,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+3,y0-3,x0+88,y0+57,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+82,y0+63,x0-3,y0+3,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+83,y0+62,x0-2,y0+2,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+84,y0+61,x0-1,y0+1,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0-3,y0+3,x0+1,y0-1,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0-2,y0+2,x0+2,y0-2,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0-1,y0+1,x0+3,y0-3,UI1_COLOR_BLACK);
		
		UI1_DrawLine(&ui->window,x0+86,y0-59,x0+82,y0-63,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+87,y0-58,x0+83,y0-62,UI1_COLOR_BLACK);
		UI1_DrawLine(&ui->window,x0+88,y0-57,x0+84,y0-61,UI1_COLOR_BLACK);
	}
}

/*
** ===================================================================
**     Method      :  drawTank(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**
**     Description :
**         draw a tank
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**         x0       			- x coordinates of the upper left
**         y0       			- y coordinates of the upper left
**     Returns     : Nothing
** ===================================================================
*/
void drawTank(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0){
	/* Heizstäbe */ 
	UI1_DrawLine(&ui->window,x0,y0+60,x0+50,y0+60,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0,y0+61,x0+50,y0+61,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+50,y0+60,x0+20,y0+67,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+50,y0+61,x0+20,y0+68,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+20,y0+67,x0+50,y0+75,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+20,y0+68,x0+50,y0+76,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+50,y0+75,x0+20,y0+82,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+50,y0+76,x0+20,y0+83,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+20,y0+82,x0+50,y0+90,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0+20,y0+83,x0+50,y0+91,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0,y0+90,x0+50,y0+90,UI1_COLOR_BLACK);
	UI1_DrawLine(&ui->window,x0,y0+91,x0+50,y0+91,UI1_COLOR_BLACK);
	/* Speicher */
	UI1_DrawBox(&ui->window,x0,y0,63,100,2,UI1_COLOR_BLACK);
}


/*
** ===================================================================
**     Method      :  drawController1(SOLAR_WindowDesc *ui)
**
**     Description :
**         draw controller 1
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**     Returns     : Nothing
** ===================================================================
*/
void drawController1(SOLAR_WindowDesc *ui){
	/* Rücklauf */
	GDisp1_DrawFilledBox(85,205,125,3,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(30,205,30,3,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(30,105,3,100,UI1_COLOR_BLUE);
	/* Vorlauf */ 
	GDisp1_DrawFilledBox(115,175,95,3,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(115,45,3,55,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(115,124,3,51,UI1_COLOR_RED);
	/* Kollektor */
	drawPanel(ui,30,105, TRUE);
	/* Pumpe */
	drawPump(ui,60,206);
	/* Wärmemengenzähler */
	drawEnergyMeter(ui,116,112);
	/* Speicher */
	drawTank(ui, 210,115);
	/* Sensoren */ 
	/* Kollektor */
	drawSensHor(118,45);
	/* Vorlauf */
	drawSens(150,175);
	/* Rücklauf */
	drawSens(150,205);
	/* Speicher */
	drawSens(215,115);
	/* Temperaturwerte */
	UTIL1_strcpy(ui->txtBufT1, sizeof(ui->txtBufT1), (unsigned char*)"temp1");
	(void)UI1_CreateText(&ui->window, &ui->txtT1, 132,41, 0, 0, ui->txtBufT1, FONT_08);
	UTIL1_strcpy(ui->txtBufT2, sizeof(ui->txtBufT2), (unsigned char*)"temp2");
	(void)UI1_CreateText(&ui->window, &ui->txtT2, 156,163, 0, 0, ui->txtBufT2, FONT_08);
	UTIL1_strcpy(ui->txtBufT3, sizeof(ui->txtBufT3), (unsigned char*)"temp3");
	(void)UI1_CreateText(&ui->window, &ui->txtT3, 156,193, 0, 0, ui->txtBufT3, FONT_08);
	UTIL1_strcpy(ui->txtBufT4, sizeof(ui->txtBufT4), (unsigned char*)"temp4");
	(void)UI1_CreateText(&ui->window, &ui->txtT4, 221,103, 0, 0, ui->txtBufT4, FONT_08);
	/* Pumpe */
	UTIL1_strcpy(ui->txtBufP1, sizeof(ui->txtBufP1), (unsigned char*)"pump1");
	(void)UI1_CreateText(&ui->window, &ui->txtP1, 56,181, 0, 0, ui->txtBufP1, FONT_08);
	/* Wärmemengenzähler */
	UTIL1_strcpy(ui->txtBufI1, sizeof(ui->txtBufI1), (unsigned char*)"energy");
	(void)UI1_CreateText(&ui->window, &ui->txtI1, 132,109, 0, 0, ui->txtBufI1, FONT_08);
}


/*
** ===================================================================
**     Method      :  drawController2(SOLAR_WindowDesc *ui)
**
**     Description :
**         draw controller 2
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**     Returns     : Nothing
** ===================================================================
*/
void drawController2(SOLAR_WindowDesc *ui){
	/* Rücklauf */
	GDisp1_DrawFilledBox(20,95,3,80,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(20,175,20,3,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(65,175,25,3,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(109,175,71,3,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(98,187,3,33,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(98,220,152,3,UI1_COLOR_BLUE);
	/* Vorlauf */ 
	GDisp1_DrawFilledBox(105,35,3,110,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(105,145,75,3,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(140,145,3,45,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(140,190,110,3,UI1_COLOR_RED);
	/* Kollektor */
	drawPanel(ui,20,95,TRUE);
	/* Pumpe */
	drawPump(ui,40,176);
	/* Speicher */
	drawTank(ui, 180,85);
	drawTank(ui, 250,130);
	/* Ventil */
	drawValve(ui,99,176);
	/* Sensoren */ 
	/* Kollektor */
	drawSensHor(108,35);
	/* Vorlauf */
	drawSens(185,145);
	drawSens(255,190);
	/* Rücklauf */
	drawSensHor(23,125);
	/* Speicher */
	drawSens(185,85);
	drawSens(255,130);
	/* Temperaturwerte */
	UTIL1_strcpy(ui->txtBufT1, sizeof(ui->txtBufT1), (unsigned char*)"temp1");
	(void)UI1_CreateText(&ui->window, &ui->txtT1, 125,31, 0, 0, ui->txtBufT1, FONT_08);
	UTIL1_strcpy(ui->txtBufT2, sizeof(ui->txtBufT2), (unsigned char*)"temp2");
	(void)UI1_CreateText(&ui->window, &ui->txtT2, 190,72, 0, 0, ui->txtBufT2, FONT_08);
	UTIL1_strcpy(ui->txtBufT3, sizeof(ui->txtBufT3), (unsigned char*)"temp3");
	(void)UI1_CreateText(&ui->window, &ui->txtT3, 260,117, 0, 0, ui->txtBufT3, FONT_08);
	UTIL1_strcpy(ui->txtBufT4, sizeof(ui->txtBufT4), (unsigned char*)"temp4");
	(void)UI1_CreateText(&ui->window, &ui->txtT4, 190,132, 0, 0, ui->txtBufT4, FONT_08);
	UTIL1_strcpy(ui->txtBufT5, sizeof(ui->txtBufT5), (unsigned char*)"temp5");
	(void)UI1_CreateText(&ui->window, &ui->txtT5, 260,177, 0, 0, ui->txtBufT5, FONT_08);
	UTIL1_strcpy(ui->txtBufT6, sizeof(ui->txtBufT6), (unsigned char*)"temp6");
	(void)UI1_CreateText(&ui->window, &ui->txtT6, 35,121, 0, 0, ui->txtBufT6, FONT_08);
	/* Pumpe */
	UTIL1_strcpy(ui->txtBufP1, sizeof(ui->txtBufP1), (unsigned char*)"pump1");
	(void)UI1_CreateText(&ui->window, &ui->txtP1, 35,150, 0, 0, ui->txtBufP1, FONT_08);
	/* Ventil */
	UTIL1_strcpy(ui->txtBufV1, sizeof(ui->txtBufV1), (unsigned char*)"valve1");
	(void)UI1_CreateText(&ui->window, &ui->txtV1, 83,158, 0, 0, ui->txtBufV1, FONT_08);
}


/*
** ===================================================================
**     Method      :  drawController3(SOLAR_WindowDesc *ui)
**
**     Description :
**         draw controller 3
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**     Returns     : Nothing
** ===================================================================
*/
void drawController3(SOLAR_WindowDesc *ui){
	
	/* Speicher */
	drawTank(ui, 240,115);
	/* Pumpe */
	drawPump(ui,4,135);
	drawPump(ui,183,135);
	/* Wärmemengenzähler */
	drawEnergyMeter(ui,106,112);
	/* Sensoren */ 
	/* Kollektor */
	drawSens(100,45);
	drawSens(110,45);
	/* Vorlauf */
	drawSens(185,175);
	/* Rücklauf */
	drawSens(185,205);
	/* Speicher */
	drawSens(245,115);
	/* Rücklauf */
	GDisp1_DrawFilledBox(15,105,3,18,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(15,148,3,57,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(15,205,225,3,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(194,105,3,18,UI1_COLOR_BLUE);
	GDisp1_DrawFilledBox(194,148,3,57,UI1_COLOR_BLUE);
	
	/* Vorlauf */ 
	GDisp1_DrawFilledBox(100,45,13,3,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(105,175,135,3,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(105,45,3,55,UI1_COLOR_RED);
	GDisp1_DrawFilledBox(105,125,3,52,UI1_COLOR_RED);
	/* Kollektor */
	drawPanel(ui, 15,105,TRUE);
	drawPanel(ui, 110,45,FALSE);
	/* Temperaturwerte */
	UTIL1_strcpy(ui->txtBufT1, sizeof(ui->txtBufT1), (unsigned char*)"temp1");
	(void)UI1_CreateText(&ui->window, &ui->txtT1, 40,32, 0, 0, ui->txtBufT1, FONT_08);
	UTIL1_strcpy(ui->txtBufT2, sizeof(ui->txtBufT2), (unsigned char*)"temp2");
	(void)UI1_CreateText(&ui->window, &ui->txtT2, 115,32, 0, 0, ui->txtBufT2, FONT_08);
	UTIL1_strcpy(ui->txtBufT3, sizeof(ui->txtBufT3), (unsigned char*)"temp3");
	(void)UI1_CreateText(&ui->window, &ui->txtT3, 250,102, 0, 0, ui->txtBufT3, FONT_08);
	UTIL1_strcpy(ui->txtBufT4, sizeof(ui->txtBufT4), (unsigned char*)"temp4");
	(void)UI1_CreateText(&ui->window, &ui->txtT4, 125,162, 0, 0, ui->txtBufT4, FONT_08);
	UTIL1_strcpy(ui->txtBufT5, sizeof(ui->txtBufT5), (unsigned char*)"temp5");
	(void)UI1_CreateText(&ui->window, &ui->txtT5, 125,192, 0, 0, ui->txtBufT5, FONT_08);
	/* Pumpe */ 
	UTIL1_strcpy(ui->txtBufP1, sizeof(ui->txtBufP1), (unsigned char*)"pump1");
	(void)UI1_CreateText(&ui->window, &ui->txtP1, 35,131, 0, 0, ui->txtBufP1, FONT_08);
	UTIL1_strcpy(ui->txtBufP2, sizeof(ui->txtBufP2), (unsigned char*)"pump2");
	(void)UI1_CreateText(&ui->window, &ui->txtP2, 143,131, 0, 0, ui->txtBufP2, FONT_08);
	/* Wärmemengenzähler */
	UTIL1_strcpy(ui->txtBufI1, sizeof(ui->txtBufI1), (unsigned char*)"energy");
	(void)UI1_CreateText(&ui->window, &ui->txtI1, 122,108, 0, 0, ui->txtBufI1, FONT_08);
}

#endif /* PL_HAS_SOLAR */
