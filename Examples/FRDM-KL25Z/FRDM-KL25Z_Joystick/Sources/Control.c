/*
 * Control.c
 *
 *  Created on: Jul 2, 2014
 *      Author: tastyger
 */


#include "Control.h"
#include "KEY1.h"
#include "EVNT1.h"

void CTRL_OnKeyPressed(uint8_t keys) {
  if (keys&(1<<0)) {
    EVNT1_SetEvent(EVNT1_A_PRESSED);
  }
  if (keys&(1<<1)) {
    EVNT1_SetEvent(EVNT1_B_PRESSED);
  }
  if (keys&(1<<2)) {
    EVNT1_SetEvent(EVNT1_C_PRESSED);
  }
  if (keys&(1<<3)) {
    EVNT1_SetEvent(EVNT1_D_PRESSED);
  }
  if (keys&(1<<4)) {
    EVNT1_SetEvent(EVNT1_E_PRESSED);
  }
  if (keys&(1<<5)) {
    EVNT1_SetEvent(EVNT1_F_PRESSED);
  }
  if (keys&(1<<6)) {
    EVNT1_SetEvent(EVNT1_KEY_PRESSED);
  }
}

void CTRL_OnKeyReleasedLong(uint8_t keys) {
}

void CTRL_OnKeyReleased(uint8_t keys) {
}

void CTRL_ScanKeys(void) {
  KEY1_ScanKeys();
}

void CTRL_Init(void) {
}
