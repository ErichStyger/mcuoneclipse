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

static uint16_t midPointX, midPointY;

static int8_t ToSigned8Bit(uint16_t val, bool isX) {
  int32_t tmp;

  if (isX) {
    tmp = (int32_t)val-midPointX;
  } else {
    tmp = (int32_t)val-midPointY;
  }
  if (tmp>0) {
    tmp = (tmp*128)/0x7fff;
  } else {
    tmp = (-tmp*128)/0x7fff;
    tmp = -tmp;
  }
  if (tmp<-128) {
    tmp = -128;
  } else if (tmp>127) {
    tmp = 127;
  }
  return (int8_t)tmp;
}

static uint8_t GetXY(uint16_t *x, uint16_t *y, int8_t *x8, int8_t *y8) {
  uint8_t res;
  uint16_t values[2];

  res = AD1_Measure(TRUE);
  if (res!=ERR_OK) {
    return res;
  }
  res = AD1_GetValue16(&values[0]);
  if (res!=ERR_OK) {
    return res;
  }
  if (x!=NULL) {
    *x = values[0];
  }
  if (y!=NULL) {
    *y = values[1];
  }
  /* transform into -128...127 with zero as mid position */
  if (x8!=NULL) {
    *x8 = ToSigned8Bit(values[0], TRUE);
  }
  if (y8!=NULL) {
    *y8 = ToSigned8Bit(values[1], FALSE);
  }
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
  HIDJ1_SetHatPos(hatPos);
}

void APP_Run(void) {
  int cnt=0; /* counter to slow down LED blinking */
  uint8_t res;
  int8_t x, y;

  (void)GetXY(&midPointX, &midPointY, NULL, NULL); /* get initial mid point values */
  for(;;) {
    res = GetXY(NULL, NULL, &x, &y); /* get potentiometer values */
    HIDJ1_SetXY(x, y); /* set X and Y position */
    HIDJ1_SetThrottle(x); /* Set throttle */
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
