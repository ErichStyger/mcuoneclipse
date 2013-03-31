/*
 * Application.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Erich Styger
 */

#include "Application.h"
#if 0
#include "MMA8451.h"
#else
#include "MMA1.h"
#endif
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"

void APP_Run(void) {
  uint8_t res=ERR_OK;
  uint8_t xyz[3];
  
  LED1_On();
  LED2_On();
  LED3_On();
#if 0
  res = MMA8451_Init();
#else
  res = MMA1_Init();
#endif
  while (res==ERR_OK) {
#if 0
	res = MMA8451_GetRaw8XYZ(&xyz[0]);
#else
	res = MMA1_GetRaw8XYZ(&xyz[0]);
#endif
    LED1_Put(xyz[0]>50);
    LED2_Put(xyz[1]>50);
    LED3_Put(xyz[2]>50);
  }
  LED1_Off();
  LED2_Off();
  LED3_Off();
}
