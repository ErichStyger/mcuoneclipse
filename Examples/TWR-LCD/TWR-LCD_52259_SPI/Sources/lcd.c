/*
 * lcd.c
 *
 *  Created on: Nov 2, 2012
 *      Author: Erich Styger
 */
#include "lcd.h"
#include "GDisp1.h"
#include "FDisp1.h"
#include "Helv08n.h"
//#include "LED1.h" /* LED1 is connected to the LCD Buzzer */
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"
#include "TCHS1.h"
#include "UTIL1.h"

static TCHS1_TouchScreenEvent evnt=(TCHS1_TouchScreenEvent)0xff; /* just some value other than existing events */
static TCHS1_PixelDim xPos, yPos;

void OnTouch(TCHS1_TouchScreenEvent event, TCHS1_PixelDim x, TCHS1_PixelDim y) {
  if (event==TCHS1_TOUCHSCREEN_EVENT_TOUCH) {
    xPos = x;
    yPos = y;
    evnt = event;
  } else if (event==TCHS1_TOUCHSCREEN_EVENT_MOVE) {
    xPos = x;
    yPos = y;
    evnt = event;
  } else if (event==TCHS1_TOUCHSCREEN_EVENT_RELEASE) {
    xPos = x;
    yPos = y;
    evnt = event;
  }
}

static void PrintLCDText(unsigned char line, const unsigned char *txt) {
  GDisp1_PixelDim x, y;
  FDisp1_Font *font;
  #define TEXT_LEFT_BORDER 10
  #define TEXT_TOP_BORDER 5
  
  font = Helv08n_GetFont();
  x = TEXT_LEFT_BORDER;
  y = (FDisp1_PixelDim)(line*Helv08n_GetBoxHeight()+TEXT_TOP_BORDER);
  FDisp1_WriteString((unsigned char*)txt, GDisp1_COLOR_WHITE, &x, &y, font);
}

static void PrintTouchText(unsigned char line) {
  unsigned char buf[32];

  if (evnt==TCHS1_TOUCHSCREEN_EVENT_TOUCH) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Touch: x:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), xPos, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" y:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), yPos, '0', 3);
  } else if (evnt==TCHS1_TOUCHSCREEN_EVENT_MOVE) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Move: x:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), xPos, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" y:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), yPos, '0', 3);
  } else if (evnt==TCHS1_TOUCHSCREEN_EVENT_RELEASE) {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Release: x:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), xPos, '0', 3);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" y:");
    UTIL1_strcatNum16uFormatted(buf, sizeof(buf), yPos, '0', 3);
  } else {
    UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"Touch me!");
  }
  PrintLCDText(line, buf);
}

#define BOX_WIDTH  20
#define BOX_HEIGHT 30
#define OFFSET     5

void LCD_Run(void) {
  GDisp1_PixelDim x, y;
  short xOffset, yOffset;
  GDisp1_PixelColor color;
  unsigned char line;

  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_WHITE);
  color = GDisp1_COLOR_BLUE;
  yOffset = xOffset = OFFSET;
  x = y = 0;
  line = 1;
  for(;;) {
    /* toggle the LED's */
    LED2_Neg();
    LED3_Neg();
    LED4_Neg();
    /* show graphic routines */
    GDisp1_DrawBox(x, y, BOX_WIDTH, BOX_HEIGHT, 2, color);
    if (x>GDisp1_GetWidth()-BOX_WIDTH) {
      xOffset = -xOffset;
    }
    if (y>GDisp1_GetHeight()-BOX_HEIGHT) {
      yOffset = -yOffset;
    }
    color++; /* iterate through color */
    x += xOffset;
    y += yOffset;
    /* draw some text */
    PrintTouchText(line);
    line++;
    if (line>10) {
      /* clear text area */
      line = 1;
      GDisp1_DrawFilledBox(0, 0, 150, 160, color);
    }
    /* handling touch screen */
    TCHS1_Scan(); /* this will call TCHS1_OnEvent() */
  } /* for */}
