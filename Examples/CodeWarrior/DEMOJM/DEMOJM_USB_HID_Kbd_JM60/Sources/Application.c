/*
 * Application.c
 *
 *  Created on: Jul 1, 2013
 *      Author: Erich Styger
 */

#include "Application.h"
#include "SW1.h"
#include "LED1.h"
#include "LED2.h"
#include "WAIT1.h"
#include "HIDK1.h"

void APP_Run(void) {
  int cnt=0; /* counter to slow down LED blinking */

  for(;;) {
    WAIT1_Waitms(10);
    cnt++;
    if (SW1_GetVal()==0) { /* button pressed */
      WAIT1_Waitms(100); /* wait for debouncing */
      if (SW1_GetVal()==0) { /* still pressed */
#if 0 /* send a string */
        (void)HIDK1_SendStr((unsigned char*)"SW1 press "); /* send a string */
#endif
#if 1 /* send print screen */
        (void)HIDK1_Send(MODIFERKEYS_NONE, KEY_PRINTSCREEN);
        (void)HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release key */
#endif
#if 0 /* send CTRL+ALT+DELETE */
        HIDK1_Send(MODIFERKEYS_LEFT_CTRL|MODIFERKEYS_RIGHT_ALT, KEY_DELETE);
        HIDK1_Send(MODIFERKEYS_NONE, KEY_NONE); /* release key */
#endif
      }
      while(SW1_GetVal()==0) {} /* wait until button is released */
    }
    if (HIDK1_App_Task()==ERR_OK) { /* run the USB application task: this will send the buffer */
      if ((cnt%100)==0) {
        LED1_Off(); /* orange LED off */
        LED2_Neg(); /* blink yellow LED if connected */
      }
    } else {
      if ((cnt%200)==0) {
        LED2_Off(); /* yellow LED off */
        LED1_Neg(); /* blink orange LED if not connected */
      }
    }
  }
}
