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

void APP_Run(void) {
  int cnt=0; /* counter to slow down LED blinking */

  for(;;) {
    WAIT1_Waitms(10);
    cnt++;
    if (HIDK2_App_Task()==ERR_BUSOFF) {
      if ((cnt%128)==0) {
        LEDG_Off();
        LEDR_Neg();
      }
    } else {
      if ((cnt%128)==0) {
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
