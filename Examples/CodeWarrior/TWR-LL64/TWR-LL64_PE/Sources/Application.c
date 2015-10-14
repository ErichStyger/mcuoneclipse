/*
 * Application.c
 *
 *  Created on: 03.05.2010
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "EVNT1.h"
#include "WAIT1.h"
#include "TRG1.h"
#include "LCD.h"
#include "PT1000.h"
#include "RTOS.h"

void APP_ShowTemperature(void) {
  short temperature;
  #define SCALE  10  /* 10 degree is 100 */ 
  
  temperature = PT_GetTemperatureCelsiusD();
  
  if (temperature<0) {
    LCD_PrintAlphaNum(0, '-');
    temperature = -temperature;
  }
  if (temperature >= 100*SCALE) { /* we only can show -99.0 - 99.0 */
    temperature = 99*SCALE;
  }
  
  LCD_PrintAlphaNum(1, '0'+temperature/(10*SCALE));
  temperature -= (temperature/(10*SCALE))*(10*SCALE);
  
  LCD_PrintAlphaNum(2, '0'+temperature/(1*SCALE));
  temperature -= (temperature/(1*SCALE))*(1*SCALE);
  
  LCD_PrintAlphaNum(3, '0'+temperature%(1*SCALE));
  
  LCD_PrintAlphaNum(4, ' ');
}

void APP_HandleEvent(byte event) {
  switch(event) {
    case EVNT1_INIT:
      LED1_On(); WAIT1_Waitms(200); 
      LED2_On(); WAIT1_Waitms(200); 
      LED3_On(); WAIT1_Waitms(200); 
      LED4_On(); WAIT1_Waitms(200);
      LED1_Off(); LED2_Off(); LED3_Off(); LED4_Off();
      break;
    case EVNT1_SW1_PRESSED:
      LED1_On(); WAIT1_Waitms(200); LED1_Off();
      break;
    case EVNT1_SW2_PRESSED:
      LED2_On(); WAIT1_Waitms(200); LED2_Off();
      break;
    case EVNT1_SW3_PRESSED:
      LED3_On(); WAIT1_Waitms(200); LED3_Off();
      break;
    case EVNT1_SW4_PRESSED:
      LED4_On(); WAIT1_Waitms(200); LED4_Off();
      break;
    case EVNT1_SW1_LONG_PRESSED:
      LED1_On(); WAIT1_Waitms(500); LED1_Off();
      break;
    case EVNT1_SW2_LONG_PRESSED:
      LED2_On(); WAIT1_Waitms(500); LED2_Off();
      break;
    case EVNT1_SW3_LONG_PRESSED:
      LED3_On(); WAIT1_Waitms(500); LED3_Off();
      break;
    case EVNT1_SW4_LONG_PRESSED:
      LED4_On(); WAIT1_Waitms(500); LED4_Off();
      break;
  } /* switch */
}

static void APP_LedBlink(void) {
  LED4_Neg();
  TRG1_AddTrigger(TRG1_LED_BLINK, 100, APP_LedBlink);
}

void APP_Run(void) {
  LCD_Test();
  EVNT1_SetEvent(EVNT1_INIT);
  TRG1_AddTrigger(TRG1_LED_BLINK, 100, APP_LedBlink);
  RTOS_Start();
}
