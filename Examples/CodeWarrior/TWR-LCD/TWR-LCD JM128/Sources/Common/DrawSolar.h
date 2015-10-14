/** ###################################################################
**     Filename  : DrawSolar.h
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

#ifndef __DRAWSOLAR_H
#define __DRAWSOLAR_H

#include "platform.h"
#if PL_HAS_SOLAR
#include "Solar.h"
#include "UI1.h"


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
void getTemp(word *temp);


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
char calcTemp(int16_t temp, int8_t i, char *tempBuf);


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
void getEnergy(char *energyBuf, byte i, int energy);


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
void updateText(SOLAR_WindowDesc *ui);


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
void initTimeDate(SOLAR_WindowDesc *ui);

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
void setTimeDate(SOLAR_WindowDesc *ui);


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
void control1(void);


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
void control2(void);

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
void control3(void);


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
void drawSens(UI1_PixelDim xPos,UI1_PixelDim yPos);


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
void drawSensHor(UI1_PixelDim xPos,UI1_PixelDim yPos);


/*
** ===================================================================
**     Method      :  drawPump(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**
**     Description :
**         draw a pump
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**         xPos       			- x coordinate center of circle
**         yPos       			- y coordinate center of circle
**     Returns     : Nothing
** ===================================================================
*/
void drawPump(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0);


/*
** ===================================================================
**     Method      :  drawValve(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0)
**
**     Description :
**         draw a valve
**     Parameters  :
**         NAME            		- DESCRIPTION
**         ui					- pointer of actual window
**         xPos       			- x coordinate center of valve
**         yPos       			- y coordinate center of valve
**     Returns     : Nothing
** ===================================================================
*/
void drawValve(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0);


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
void drawEnergyMeter(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0);


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
void drawPanel(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0, bool typ);


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
void drawTank(SOLAR_WindowDesc *ui,UI1_PixelDim x0,UI1_PixelDim y0);


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
void drawController1(SOLAR_WindowDesc *ui);

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
void drawController2(SOLAR_WindowDesc *ui);


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
void drawController3(SOLAR_WindowDesc *ui);

#endif /* PL_HAS_SOLAR */
#endif /* __DRAWSOLAR_H */