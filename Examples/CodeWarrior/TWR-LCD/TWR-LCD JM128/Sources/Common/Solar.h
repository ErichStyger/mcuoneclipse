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

#ifndef __SOLAR_H
#define __SOLAR_H

#include "platform.h"
#if PL_HAS_SOLAR
#include "UI1.h"

// InterruptFlag 
extern unsigned char SOLAR_EnergyMeterInterruptHappend;

/* descriptor for our window */
typedef struct {
  UI1_Screen screen;
  UI1_Window window; /* graph window */
  UI1_Header header;
  UI1_Text txtT1,txtT2,txtT3,txtT4,txtT5,txtT6;
  UI1_Text txtP1,txtP2,txtV1,txtI1,txtI2,txtTime,txtDate;
  word value1[3];
  unsigned char txtBufT1[sizeof("T1: -000.0°C")];
  unsigned char txtBufT2[sizeof("T2: -000.0°C")];
  unsigned char txtBufT3[sizeof("T3: -000.0°C")];
  unsigned char txtBufT4[sizeof("T4: -000.0°C")];
  unsigned char txtBufT5[sizeof("T5: -000.0°C")];
  unsigned char txtBufT6[sizeof("T6: -000.0°C")];
  unsigned char txtBufP1[sizeof("P1: Init...")];
  unsigned char txtBufP2[sizeof("P1: Init...")];
  unsigned char txtBufV1[sizeof("V1: Init...")];
  unsigned char txtBufI1[sizeof("I1: 400.0Wmin")];
  unsigned char txtBufI2[sizeof("I1: 400.0Wmin")];
  unsigned char txtBufTime[sizeof("Time: 00:00")];
  unsigned char txtBufDate[sizeof("Date: 00:00:00")];
  UI1_Icon iconClose;
} SOLAR_WindowDesc;

typedef enum {
  CONTROLLER1 = 100,
  CONTROLLER2 = 200,
  CONTROLLER3 = 300
} Selection_R;

typedef enum {
  PUMP1ON = 101,
  PUMP1OFF = 102,
  PUMP2ON = 201,
  PUMP2OFF = 202
} Selection_P;

typedef enum {
  VALVE1OFF = 111,
  VALVE1ON1 = 112,
  VALVE1ON2 = 113
} Selection_V;


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
void R_Enable(byte i);


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
bool R_IsEnabled(byte i);


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
void P1_Enable(byte i);


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
void P2_Enable(byte i);


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
bool P_IsEnabled(byte i);


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
void V1_Enable(byte i);


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
bool V_IsEnabled(byte i);


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
void setAktuator(byte i);


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
void clearAktuator(byte i);


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
void set_IOExpander(void);


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
void InitImpuls(void);


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
void SOLAR_StartTask(SOLAR_WindowDesc *desc);


#endif /* PL_HAS_SOLAR */
#endif /* __SOLAR_H */

