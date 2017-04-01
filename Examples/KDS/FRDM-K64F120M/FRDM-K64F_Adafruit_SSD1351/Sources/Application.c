/*
 * Application.c
 *
 *  Created on: 20.03.2017
 *      Author: Erich Styger Local
 */
#if 1
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "LCD1.h"
#include "GDisp1.h"
#include "Helv14.h"
#include "FDisp1.h"
#include "uncannyEyes.h"

static void SpeedTest(void) {
  int i;

  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_RED);
  GDisp1_UpdateFull();
  for(i=0;i<25;i++) {
//    GDisp1_DrawFilledBox(0, i*10, 10, 10, LCD1_COLOR_BLUE);
//    GDisp1_UpdateFull();
    GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_RED);
    GDisp1_UpdateFull();
    GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_GREEN);
    GDisp1_UpdateFull();
    GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_BLUE);
    GDisp1_UpdateFull();
  }
}

void APP_Run(void) {
  int i;
  FDisp1_PixelDim x, y;

  LCD1_Init();
  LCD1_Clear();
#if 1
  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_WHITE);
  GDisp1_UpdateFull();
  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_RED);
  GDisp1_UpdateFull();
  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_GREEN);
  GDisp1_UpdateFull();
  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, LCD1_COLOR_BLUE);
  GDisp1_UpdateFull();

  GDisp1_Clear();
  GDisp1_UpdateFull();

  GDisp1_DrawFilledBox(0, 0, 128, 128, LCD1_COLOR_RED);
  GDisp1_UpdateFull();
  GDisp1_DrawFilledBox(0, 0, 50, 10, LCD1_COLOR_YELLOW);
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_PORTRAIT);
  GDisp1_DrawFilledBox(0, 0, 100, 20, LCD1_COLOR_YELLOW);
  GDisp1_UpdateFull();

  x = 0; y = 0;
  FDisp1_WriteString("Portrait", LCD1_COLOR_RED, &x, &y, Helv14_GetFont());
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE);
  GDisp1_DrawFilledBox(0, 0, 100, 20, LCD1_COLOR_ORANGE);
  x = 0; y = 0;
  FDisp1_WriteString("Landscape", LCD1_COLOR_GREEN, &x, &y, Helv14_GetFont());
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_PORTRAIT180);
  GDisp1_DrawFilledBox(0, 0, 100, 20, LCD1_COLOR_RED);
  x = 0; y = 0;
  FDisp1_WriteString("Portrait180", LCD1_COLOR_BLUE, &x, &y, Helv14_GetFont());
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE180);
  GDisp1_DrawFilledBox(0, 0, 100, 20, LCD1_COLOR_BRIGHT_GREEN);
  x = 0; y = 0;
  FDisp1_WriteString("Landscape180", LCD1_COLOR_WHITE, &x, &y, Helv14_GetFont());
  GDisp1_UpdateFull();

#if 0
  LCD1_OpenWindow(0, 0, (LCD1_PixelDim)(LCD1_GetWidth()-1), (LCD1_PixelDim)(LCD1_GetHeight()-1)); /* window for whole display */
  for(i=0;i<500;i++) {
    LCD1_WriteDataWord(LCD1_COLOR_YELLOW);
  }
  LCD1_CloseWindow();
#endif
  LCD1_Clear();
  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_PORTRAIT);
  GDisp1_DrawLine(0, 0, 10, 50, LCD1_COLOR_RED);
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE);
  GDisp1_DrawLine(0, 0, 10, 50, LCD1_COLOR_GREEN);
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE180);
  GDisp1_DrawLine(0, 0, 10, 50, LCD1_COLOR_BLUE);
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_PORTRAIT180);
  GDisp1_DrawLine(0, 0, 10, 50, LCD1_COLOR_WHITE);
  LCD1_Clear();

  //GDisp1_DrawFilledBox(0, 0, 20, 40, LCD1_COLOR_WHITE);

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_PORTRAIT180);
  GDisp1_DrawFilledBox(0, 0, 20, 40, LCD1_COLOR_RED);
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE);
  GDisp1_DrawFilledBox(0, 0, 20, 40, LCD1_COLOR_GREEN);
  GDisp1_UpdateFull();

  LCD1_SetDisplayOrientation(LCD1_ORIENTATION_LANDSCAPE180);
  GDisp1_DrawFilledBox(0, 0, 20, 40, LCD1_COLOR_BLUE);
  GDisp1_UpdateFull();

  GDisp1_DrawFilledBox(50, 50, 20, 30, LCD1_COLOR_RED);
  GDisp1_DrawFilledBox(0, 0, 96, 96, LCD1_COLOR_BLUE);
  GDisp1_DrawBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), 1, LCD1_COLOR_GREEN);
  x = 0; y = 0;
  FDisp1_WriteString("Hello", LCD1_COLOR_GREEN, &x, &y, Helv14_GetFont());
  GDisp1_UpdateFull();

  EYES_Init();
  for(;;) {
    EYES_Run();
//    SpeedTest();
    LED1_Neg();
    WAIT1_Waitms(100);
    LED2_Neg();
    WAIT1_Waitms(100);
    LED3_Neg();
    WAIT1_Waitms(100);
  }
#endif
}

#endif
