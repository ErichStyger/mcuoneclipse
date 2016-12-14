/*
 * Application.c
 *
 *  Created on: 13.12.2016
 *      Author: Erich Styger Local
 */


#include "Application.h"
#include "WAIT1.h"
#include "LED1.h"

#if 0
#include "SPI1.h"
#include "CS.h" /* chip select is HIGH active */

/**************************************************************************
    Sharp Memory Display Connector
    -----------------------------------------------------------------------
    Pin   Function        Notes
    ===   ==============  ===============================
      1   VIN             3.3-5.0V (into LDO supply)
      2   3V3             3.3V out
      3   GND
      4   SCLK            Serial Clock
      5   MOSI            Serial Data Input, data is sent to the display in little-endian format (LSB first)
      6   CS              Serial Chip Select
      9   EXTMODE         COM Inversion Select (Low = SW clock/serial)
      7   EXTCOMIN        External COM Inversion Signal
      8   DISP            Display On(High)/Off(Low)
 **************************************************************************/
// LCD Dimensions
#define SHARPMEM_LCDWIDTH       (96)
#define SHARPMEM_LCDHEIGHT      (96)

#define SHARPMEM_BIT_WRITECMD   (0x80)
#define SHARPMEM_BIT_VCOM       (0x40)
#define SHARPMEM_BIT_CLEAR      (0x20)
#define TOGGLE_VCOM             do { _sharpmem_vcom = _sharpmem_vcom ? 0x00 : SHARPMEM_BIT_VCOM; } while(0);

static uint32_t _sharpmem_vcom;
static uint8_t sharpmem_buffer[(SHARPMEM_LCDWIDTH*SHARPMEM_LCDHEIGHT)/8];

static uint8_t SHM_RevertBits(uint8_t data) {
  uint8_t tmp, i;

  /* revert bits */
  tmp = 0;
  for(i=0;;i++) {
    if (data&1) {
      tmp |= 0x1;
    }
    if (i==7) {
      break;
    }
    tmp <<= 1;
    data >>= 1;
  }
  return tmp;
}

void SHM_SendByte(uint8_t data) {
  SPI1_SendChar(data); /* component is LSB first! */
}

//void SHM_SendByteLSB(uint8_t data) {
//  SPI1_SendChar(/*SHM_RevertBits(data)*/data); /* component is MSB first */
//}

void SHM_Refresh(void) {
  uint16_t i, totalbytes, currentline, oldline;
  totalbytes = sizeof(sharpmem_buffer);

  /* Send the write command */
  CS_SetVal();
  SHM_SendByte(SHARPMEM_BIT_WRITECMD | _sharpmem_vcom);
  TOGGLE_VCOM;

  /* Send the address for line 1 */
  oldline = currentline = 1;
  SHM_SendByte(SHM_RevertBits(currentline));

  /* Send image buffer */
  for (i=0; i<totalbytes; i++) {
    SHM_SendByte(sharpmem_buffer[i]);
    currentline = ((i+1)/(SHARPMEM_LCDWIDTH/8)) + 1;
    if(currentline != oldline) {
      /* Send end of line and address bytes */
      SHM_SendByte(0x00);
      if (currentline <= SHARPMEM_LCDHEIGHT) {
        SHM_SendByte(SHM_RevertBits(currentline));
      }
      oldline = currentline;
    }
  }
  /* Send another trailing 8 bits for the last line */
  SHM_SendByte(0x00);
  CS_ClrVal();
}

void SHM_Line(uint8_t line, uint8_t data) {
  uint16_t i, totalbytes, currentline, oldline;

  /* Send the write command */
  CS_SetVal();
  SHM_SendByte(SHARPMEM_BIT_WRITECMD | _sharpmem_vcom);
  TOGGLE_VCOM;

  /* Send the address for line */
  SHM_SendByte(SHM_RevertBits(line+1));

  /* Send image buffer */
  totalbytes = SHARPMEM_LCDWIDTH/8;
  for (i=0; i<totalbytes; i++) {
    SHM_SendByte(data);
  }
  /* Send another trailing 8 bits for the last line */
  SHM_SendByte(0x00);
  CS_ClrVal();
}

void SHM_ClearDisplay(void) {
  /* send clear command */
  CS_SetVal();
  SHM_SendByte(_sharpmem_vcom | SHARPMEM_BIT_CLEAR);
  SHM_SendByte(0x00);
  TOGGLE_VCOM;
  CS_ClrVal();
}

void SHM_Init(void) {
  /* Data order: LSB first
   * Data is shifted on clock rising edge
   * Clock Idle Polarity: Low
   */
  CS_ClrVal(); /* disable device */
  SPI1_SetShiftClockPolarity(0); /* 0: falling edge: data is sampled at rising edge and shifted at falling edge */
  SPI1_SetIdleClockPolarity(0); /* 0: low idle polarity */
  // Set the vcom bit to a defined state
  _sharpmem_vcom = SHARPMEM_BIT_VCOM;
}

static void Test(void) {
  uint8_t line;
  SHM_Init();

  sharpmem_buffer[0] = 0b11000111; /* bit 0: black, bit 1: white */
  SHM_ClearDisplay();
  for(line=0;line<SHARPMEM_LCDHEIGHT;line++) {
    SHM_Line(line, 0xF0);
  }
  SHM_ClearDisplay();
  SHM_Refresh();
}
#else
#include "GDisp1.h"
#include "FDisp1.h"

#include "Helv8.h"
#include "Helv8Bold.h"
#include "Helv10.h"
#include "Helv12.h"
#include "Cour8.h"
#include "Cour8Bold.h"
#include "Cour10.h"
#include "Cour12.h"

static void DrawLines(void) {
  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_UpdateFull();

  GDisp1_DrawBox(0, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();

  GDisp1_DrawBox(GDisp1_GetWidth()-10, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();

  GDisp1_DrawLine(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  GDisp1_DrawLine(0, GDisp1_GetHeight()-1, GDisp1_GetWidth()-1, 0, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  for(i=0;i<20;i++) {
    GDisp1_DrawCircle((GDisp1_GetWidth()-1)/2, (GDisp1_GetHeight()-1)/2, 5+i*2, GDisp1_COLOR_BLACK);
    GDisp1_UpdateFull();
  }
  WAIT1_Waitms(1000);
}

static void DrawRectangles(void) {
  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_UpdateFull();

  GDisp1_DrawLine(0, 0, GDisp1_GetWidth()-1, GDisp1_GetHeight()-1, GDisp1_COLOR_BLACK);
  GDisp1_DrawLine(0, GDisp1_GetHeight()-1, GDisp1_GetWidth()-1, 0, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  for(i=0;i<GDisp1_GetShorterSide(); i+=2) {
    GDisp1_DrawBox(((GDisp1_GetShorterSide()-1)/2)-i, ((GDisp1_GetShorterSide()-1)/2)-i, 2*(i+1), 2*(i+1), 1, GDisp1_COLOR_BLACK);
    GDisp1_UpdateFull();
  }
  WAIT1_Waitms(1000);
}

static void DrawBoxes(void) {
  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_DrawFilledBox(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_DrawFilledBox(0+20, 0+20, GDisp1_GetWidth()-40, GDisp1_GetHeight()-40, GDisp1_COLOR_WHITE);
  GDisp1_DrawFilledBox(0+40, 0+40, GDisp1_GetWidth()-80, GDisp1_GetHeight()-80, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  WAIT1_Waitms(1000);
}

static void DrawFont(void) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  GDisp1_UpdateFull();
  x = 0; y = 0;
  FDisp1_WriteString("Helv8", GDisp1_COLOR_BLACK, &x, &y, Helv8_GetFont());
  FDisp1_WriteString(" Helv8 BOLD", GDisp1_COLOR_BLACK, &x, &y, Helv8Bold_GetFont());

  x = 0;  y += Helv8_GetBoxHeight();
  FDisp1_WriteString("Helv10", GDisp1_COLOR_BLACK, &x, &y, Helv10_GetFont());

  x = 0;  y += Helv10_GetBoxHeight();
  FDisp1_WriteString("Helv12", GDisp1_COLOR_BLACK, &x, &y, Helv12_GetFont());

  x = 0;  y += Helv12_GetBoxHeight();
  FDisp1_WriteString("Cour8", GDisp1_COLOR_BLACK, &x, &y, Cour8_GetFont());
  FDisp1_WriteString(" Cour8 BOLD", GDisp1_COLOR_BLACK, &x, &y, Cour8Bold_GetFont());

  x = 0;  y += Cour8_GetBoxHeight();
  FDisp1_WriteString("Cour10", GDisp1_COLOR_BLACK, &x, &y, Cour10_GetFont());

  x = 0;  y += Cour10_GetBoxHeight();
  FDisp1_WriteString("Cour12", GDisp1_COLOR_BLACK, &x, &y, Cour12_GetFont());

  GDisp1_UpdateFull();
  WAIT1_Waitms(1000);
}

void Test(void) {
  DrawFont();
  DrawLines();
  DrawRectangles();
  DrawBoxes();
}
#endif

void APP_Run(void) {
  for(;;) {
    Test();
    LED1_Neg();
    WAIT1_Waitms(100);
  }
}
