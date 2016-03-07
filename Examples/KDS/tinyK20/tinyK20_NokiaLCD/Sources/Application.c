/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "PDC1.h"
#include "GDisp1.h"

static void DrawLines(void) {
  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_UpdateFull();
  for(i=0;i<10;i++) {
    w=30; h=40;
    for(x=0;x<GDisp1_GetWidth()/2;x+=2) {
      for(y=20;x<GDisp1_GetHeight()/4;y++) {
        GDisp1_DrawLine(x, y, x+w, y+h, GDisp1_COLOR_BLACK);
        GDisp1_UpdateFull();
      }
    }
  }
}

static void DrawText(void) {
  GDisp1_Clear();
  GDisp1_UpdateFull();
  PDC1_WriteLineStr(1, "hello");
  WAIT1_Waitms(1000);
  PDC1_WriteLineStr(2, "world");
  WAIT1_Waitms(1000);
  PDC1_WriteLineStr(3, "out");
  WAIT1_Waitms(1000);
  PDC1_WriteLineStr(4, "there");
  WAIT1_Waitms(1000);
  PDC1_WriteLineStr(5, "!!!!!");
  WAIT1_Waitms(1000);
}

void APP_Start(void) {
  for(;;) {
    DrawText();
    LED1_Neg();
    WAIT1_Waitms(1000);
    DrawLines();
  }
}
