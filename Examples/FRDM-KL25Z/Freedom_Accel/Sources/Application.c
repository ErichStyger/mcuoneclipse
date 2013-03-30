/*
 * Application.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Erich Styger
 */

#include "Application.h"
#include "MMA8451.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"

void APP_Run(void) {
  uint8_t res=ERR_OK;
  uint8_t xyz[3];
  
  LED1_On();
  LED2_On();
  LED3_On();
  res = MMA8451_Init();
  while (res==ERR_OK) {
    res = MMA8451_GetRawXYZ(&xyz[0]);
    LED1_Put(xyz[0]>50);
    LED2_Put(xyz[1]>50);
    LED3_Put(xyz[2]>50);
  }
  LED1_Off();
  LED2_Off();
  LED3_Off();
}
