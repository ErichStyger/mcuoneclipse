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
#include "HIDJ1.h"
#include "AD1.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "SW4.h"
#include "SW5.h"
#include "SW6.h"
#include "SW7.h"
#include "UTIL1.h"

int32_t mapToRange(int32_t val, int32_t offset, uint8_t nofBits) {
  if (val>offset) {
    val -= offset;
  } else {
    val = 0;
  }
  val = UTIL1_constrain(val, 0, 0xffff);
  if (nofBits==8) {
    val = UTIL1_map(val, 0, 0xffff, -127, 127);
    val = UTIL1_constrain(val, -127, 127);
  } else { /* 16bit */
    val = UTIL1_map64(val, 0, 0xffff, -32767, 32767);
    val = UTIL1_constrain(val, -32767, 32767);
  }
}

static uint8_t GetXY(int32_t *x, int32_t *y) {
  uint8_t res;
  uint16_t values[2];
  int32_t val;

  res = AD1_Measure(TRUE);
  if (res!=ERR_OK) {
    return res;
  }
  res = AD1_GetValue16(&values[0]);
  if (res!=ERR_OK) {
    return res;
  }
  *x = values[0];
  *y = values[1];
  return ERR_OK;
}

static uint8_t CalculateOffset(int32_t *offsetX, int32_t *offsetY) {
  uint8_t res;
  int32_t x, y;

  *offsetX = 0;
  *offsetY = 0;
  res = GetXY(&x, &y);
  if (res!=ERR_OK) {
    return res;
  }
  /* the potentiometer is assumed to be in the middle position */
  *offsetX = x-0x7fff;
  *offsetY = y-0x7fff;
  return ERR_OK;
}

static void CheckButtons(void) {
  uint8_t hatPos;

  /* push buttons */
  //HIDJ1_SetButton(0, SW1_GetVal()==0);
  //HIDJ1_SetButton(1, SW2_GetVal()==0);
  //HIDJ1_SetButton(2, SW3_GetVal()==0);
  //HIDJ1_SetButton(3, SW4_GetVal()==0);
  HIDJ1_SetButton(0, SW5_GetVal()==0); /* E */
  HIDJ1_SetButton(1, SW6_GetVal()==0); /* F */
  HIDJ1_SetButton(2, SW7_GetVal()==0); /* center */
  /* hat switch with 4 */
  if (SW1_GetVal()==0) { /* A */
    hatPos = 0; /* top */
  } else if (SW2_GetVal()==0) { /* B */
    hatPos = 1; /* right */
  } else if (SW3_GetVal()==0) { /* C */
    hatPos = 2; /* bottom */
  } else if (SW4_GetVal()==0) { /* D */
    hatPos = 3; /* left */
  } else {
    hatPos = -1; /* center */
  }
  HIDJ1_SetHatPos(0, hatPos);
}

void APP_Run(void) {
  int cnt=0; /* counter to slow down LED blinking */
  uint8_t res;
  int32_t adcx, adcy;
  int32_t x, y;
  int32_t offsetX, offsetY;

  (void)CalculateOffset(&offsetX, &offsetY); /* assuming joystick in middle position */
  for(;;) {
    (void)GetXY(&adcx, &adcy);
    x = mapToRange(adcx, offsetX, JOYSTICK_NOF_ANALOG_RES_BITS);
    y = mapToRange(adcy, offsetY, JOYSTICK_NOF_ANALOG_RES_BITS);
    HIDJ1_SetXY(0, x, y); /* set X and Y position */
    x = mapToRange(adcx, offsetX, JOYSTICK_NOF_THROTTLE_RES_BITS);
    HIDJ1_SetThrottle(0, x); /* Set throttle */
    CheckButtons(); /* check push buttons */
    WAIT1_Waitms(10); /* wait some time */
    cnt++;
    if (HIDJ1_App_Task()==ERR_OK) { /* run the USB application task: this will send the buffer */
      if ((cnt%100)==0) { /* slow down blinking */
        LEDR_Off();
        LEDG_Neg(); /* blink green LED if connected */
      }
    } else {
      if ((cnt%200)==0) {
        LEDG_Off();
        LEDR_Neg(); /* blink red LED if not connected */
      }
    }
  }
}
