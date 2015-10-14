/*
 * Application.c
 *
 *  Created on: Jul 1, 2013
 *      Author: Erich Styger
 */

#include "Application.h"
#include "SW2.h"
#include "LED1.h"
#include "LED2.h"
#include "WAIT1.h"
#include "HIDM1.h"

void APP_Run(void) {
  int cnt=0; /* counter to slow down LED blinking */

  for(;;) {
    WAIT1_Waitms(10);
    cnt++;
    if (HIDM1_App_Task()==ERR_BUSOFF) {
      if ((cnt%128)==0) { /* just slow down blinking */
        LED1_Off();
        LED2_Neg();
      }
    } else {
      if ((cnt%128)==0) { /* just slow down blinking */
        LED2_Off();
        LED1_Neg();
      }
      if (SW2_GetVal()==0) { /* button pressed */
        WAIT1_Waitms(100); /* wait for debouncing */
        if (SW2_GetVal()==0) { /* still pressed */
          //(void)HIDM1_Send(0, 8, 8); /* raw move message */
          
          //(void)HIDM1_Send(HIDM1_MOUSE_LEFT, 0, 0); /* send left mouse button */
          //(void)HIDM1_Send(0, 0, 0); /* send release button message */
          
          //(void)HIDM1_Move(-8, 0); /* moving the cursor up */
          
          //HIDM1_Click(HIDM1_MOUSE_LEFT); /* left mouse click */
          
          HIDM1_Click(HIDM1_MOUSE_RIGHT); /* right mouse click */
        }
        while(SW2_GetVal()==0) {} /* wait until button is released */
      }
    }
  }
}
