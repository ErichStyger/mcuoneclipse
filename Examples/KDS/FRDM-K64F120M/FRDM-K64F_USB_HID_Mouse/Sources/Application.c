/*
 * Application.c
 *
 *  Created on: Jul 1, 2013
 *      Author: Erich Styger
 */

#include "Application.h"
#include "SW2.h"
#include "SW3.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "HIDM1.h"
//#include "MMA1.h"

static void Err(void) {
  for(;;); /* simple implementation: in case of error stop here */
}

#define AIR_THRESHOLD 1024

void APP_Run(void) {
  int cnt=0; /* counter to slow down LED blinking */
  uint8_t res;
  int16_t xyz[3];
#if 0
  res = MMA1_Init();
  if (res!=ERR_OK) {
    Err();
  }
  res = MMA1_SetFastMode(FALSE);
  if (res!=ERR_OK) {
    Err();
  }
  res = MMA1_Enable(); /* enable accelerometer */
  if (res!=ERR_OK) {
    Err();
  }
#endif
  for(;;) {
    WAIT1_Waitms(10);
#if 0
    /* implement 'air-mouse' movement */
    xyz[0] = MMA1_GetX();
    xyz[1] = MMA1_GetY();
    xyz[3] = MMA1_GetZ();
    /* y axis */
    if (xyz[1]>AIR_THRESHOLD) {
      (void)HIDK2_Move(0, 2); /* moving the cursor left */
    } else if (xyz[1]<-AIR_THRESHOLD) {
      (void)HIDK2_Move(0, -2); /* moving the cursor right */
    }
    /* x axis */
    if (xyz[0]>AIR_THRESHOLD) {
      (void)HIDK2_Move(-2, 0); /* moving the cursor up */
    } else if (xyz[0]<-AIR_THRESHOLD) {
      (void)HIDK2_Move(2, 0); /* moving the cursor down */
    }
#endif
    cnt++;
    if (HIDM1_App_Task()==ERR_BUSOFF) {
      if ((cnt%128)==0) { /* just slow down blinking */
        LED1_Neg(); /* red LED */
        LED2_Off();
      }
    } else {
      if ((cnt%128)==0) { /* just slow down blinking */
        LED1_Off();
        LED2_Neg(); /* green LED */
      }
      if (SW2_GetVal()==0) { /* button pressed */
        WAIT1_Waitms(100); /* wait for debouncing */
        if (SW2_GetVal()==0) { /* still pressed */
          //(void)HIDK2_Send(0, 8, 8); /* raw move message */
          
          //(void)HIDK2_Send(HIDK2_MOUSE_LEFT, 0, 0); /* send left mouse button */
          //(void)HIDK2_Send(0, 0, 0); /* send release button message */
          
          //(void)HIDK2_Move(-8, 0); /* moving the cursor up */
          
          //HIDK2_Click(HIDK2_MOUSE_LEFT); /* left mouse click */
          
          HIDM1_Click(HIDM1_MOUSE_RIGHT); /* right mouse click */
        }
        while(SW2_GetVal()==0) {} /* wait until button is released */
      }
      if (SW3_GetVal()==0) { /* button pressed */
        WAIT1_Waitms(100); /* wait for debouncing */
        if (SW3_GetVal()==0) { /* still pressed */
          HIDM1_Click(HIDM1_MOUSE_LEFT); /* left mouse click */
        }
        while(SW3_GetVal()==0) {} /* wait until button is released */
      }
    }
  }
}
