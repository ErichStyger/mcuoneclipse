/*
 * Application.c
 *
 *  Created on: Jul 1, 2013
 *      Author: Erich Styger
 */

#include "Application.h"
#include "SW1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"
#include "WAIT1.h"
#include "HIDK2.h"
#include "MMA1.h"

static void Err(void) {
  for(;;); /* simple implementation: in case of error stop here */
}

#define AIR_THRESHOLD 1024

void APP_Run(void) {
  int cnt=0; /* counter to slow down LED blinking */
  uint8_t res;
  int16_t xyz[3];
  
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
  for(;;) {
    WAIT1_Waitms(10);
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
    cnt++;
    if (HIDK2_App_Task()==ERR_BUSOFF) {
      if ((cnt%128)==0) { /* just slow down blinking */
        LEDG_Off();
        LEDR_Neg();
      }
    } else {
      if ((cnt%128)==0) { /* just slow down blinking */
        LEDR_Off();
        LEDG_Neg();
      }
      if (SW1_GetVal()==0) { /* button pressed */
        WAIT1_Waitms(100); /* wait for debouncing */
        if (SW1_GetVal()==0) { /* still pressed */
          //(void)HIDK2_Send(0, 8, 8); /* raw move message */
          
          //(void)HIDK2_Send(HIDK2_MOUSE_LEFT, 0, 0); /* send left mouse button */
          //(void)HIDK2_Send(0, 0, 0); /* send release button message */
          
          //(void)HIDK2_Move(-8, 0); /* moving the cursor up */
          
          //HIDK2_Click(HIDK2_MOUSE_LEFT); /* left mouse click */
          
          HIDK2_Click(HIDK2_MOUSE_RIGHT); /* right mouse click */
        }
        while(SW1_GetVal()==0) {} /* wait until button is released */
      }
    }
  }
}
