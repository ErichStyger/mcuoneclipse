/*
 * Keys.c
 *
 *  Created on: 30.12.2014
 *      Author: tastyger
 */


#include "EVNT1.h"
#include "Keys.h"

void KEYS_OnKeyPressed(byte keys) {
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BTN_LEFT_PRESSED);
    EVNT1_SetEvent(EVNT1_BTN_RIGHT_PRESSED);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BTN_RIGHT_PRESSED);
  }
}

void KEYS_OnKeyReleased(byte keys) {
  if (keys&1) {
    EVNT1_SetEvent(EVNT1_BTN_LEFT_RELEASED);
    EVNT1_SetEvent(EVNT1_BTN_RIGHT_RELEASED);
  } else if (keys&2) {
    EVNT1_SetEvent(EVNT1_BTN_RIGHT_RELEASED);
  }
}
