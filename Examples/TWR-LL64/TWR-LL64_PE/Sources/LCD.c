/*
 * LCD.c
 *
 *  Created on: 07.05.2010
 *      Author: Erich Styger
 */
#include "LCD.h"
#include "LCD1.h"
#include "WAIT1.h"
#include "TMDT1.h"
#include "UTIL1.h"

#define LCD_NOF_CHARS       5   /* number of alphanumeric chars on LCD */
#define LCD_NOF_PLANES      2   /* number of alphanumeric chars on LCD */
#define LCD_NOF_AN_SEGMENTS 7   /* we have 7 (A..G) segments alpha-numeric */

static const byte LCD_SymbolTable[LCD_SYMBOL_LAST][LCD_NOF_PLANES] = {
  /* LCD_SYMBOL_MONDAY,            */  {0,0},
  /* LCD_SYMBOL_TUESDAY,           */  {4,0},
  /* LCD_SYMBOL_WEDNESDAY,         */  {8,0},
  /* LCD_SYMBOL_THURSDAY,          */  {9,0},
  /* LCD_SYMBOL_FRIDAY,            */  {13,0},
  /* LCD_SYMBOL_SATURDAY,          */  {14,1},
  /* LCD_SYMBOL_SUNDAY             */  {15,1},
  /* LCD_SYMBOL_HEAT,              */  {14,0},
  /* LCD_SYMBOL_COOL,              */  {15,0},
  /* LCD_SYMBOL_BATTERY_OUTLINE,   */  {1,0},
  /* LCD_SYMBOL_BATTERY_P1,        */  {1,1},
  /* LCD_SYMBOL_BATTERY_P2,        */  {2,1},
  /* LCD_SYMBOL_BATTERY_P3,        */  {2,0},
  /* LCD_SYMBOL_BATTERY_P4,        */  {3,0},
  /* LCD_SYMBOL_AM,                */  {19,0},
  /* LCD_SYMBOL_PM,                */  {19,1},
  /* LCD_SYMBOL_FLTR,              */  {20,0},
  /* LCD_SYMBOL_HOLD,              */  {20,1},
  /* LCD_SYMBOL_T1,                */  {0,1},
  /* LCD_SYMBOL_COLON,             */  {8,1}
};

/*! \brief mapping of segments to number */
static const byte LCD_NumericTableAG[10] = {
  /*ABCDEFG segment mapping */
  0b1111110, /* 0 */
  0b0110000, /* 1 */
  0b1101101, /* 2 */
  0b1111001, /* 3 */
  0b0110011, /* 4 */
  0b1011011, /* 5 */
  0b1011111, /* 6 */
  0b1110000, /* 7 */
  0b1111111, /* 8 */
  0b1111011, /* 9 */
};

#define LCD_SpaceAG 0b0000000 /*   */
#define LCD_MinusAG 0b0000001 /* - */

/*! \brief mapping 7-segment numbers to pins and planes */
static const byte LCD_SegmentTable[LCD_NOF_CHARS][LCD_NOF_AN_SEGMENTS][LCD_NOF_PLANES] = {
    { /* position 0 */
      {6,1}, /* 1G */
      {5,1}, /* 1F */
      {7,1}, /* 1E */
      {7,0}, /* 1D */
      {6,0}, /* 1C */
      {5,0}, /* 1B */
      {4,1}, /* 1A */
    },
    { /* position 1 */
      {11,1}, /* 2G */
      {10,1}, /* 2F */
      {12,1}, /* 2E */
      {12,0}, /* 2D */
      {11,0}, /* 2C */
      {10,0}, /* 2B */
      {9,1},  /* 2A */
    },
    { /* position 2 */
      {17,1}, /* 3G */
      {16,1}, /* 3F */
      {18,1}, /* 3E */
      {18,0}, /* 3D */
      {17,0}, /* 3C */
      {16,0}, /* 3B */
      {13,1}, /* 3A */
    },
    { /* position 3 */
      {23,1}, /* 4G */
      {23,0}, /* 4F */
      {22,0}, /* 4E */
      {21,0}, /* 4D */
      {22,1}, /* 4C */
      {24,1}, /* 4B */
      {24,0}, /* 4A */
    },
    { /* position 4 */
      {26,1}, /* 5G */
      {26,0}, /* 5F */
      {25,0}, /* 5E */
      {21,1}, /* 5D */
      {25,1}, /* 5C */
      {27,1}, /* 5B */
      {27,0}, /* 5A */
    },
};

static void LCD_MapToPins(byte pos, byte segmentMappingAG) {
  byte *pinMappingAG;
  byte i;

  pinMappingAG = (byte*)LCD_SegmentTable[pos];
  for(i=0;i<LCD_NOF_AN_SEGMENTS;i++) {
    if (segmentMappingAG&1) { /* enable segment */
      (void)LCD1_SetSegmentState(pinMappingAG[0], pinMappingAG[1], TRUE);
    } else { /* turn off segment */
      (void)LCD1_SetSegmentState(pinMappingAG[0], pinMappingAG[1], FALSE);
    }
    segmentMappingAG >>= 1; /* next bit */
    pinMappingAG += LCD_NOF_PLANES; /* next pin descriptor */
  }
}

void LCD_PrintAlphaNum(byte pos, byte ch) {
  if (pos > LCD_NOF_CHARS) { /* invalid position */
    return;
  }
  if (ch>='0' && ch<='9') {
    LCD_MapToPins(pos, LCD_NumericTableAG[ch-'0']);
  } else if (ch=='-') {
    LCD_MapToPins(pos, LCD_MinusAG);
  } else if (ch==' ') {
    LCD_MapToPins(pos, LCD_SpaceAG);
  }
}

void LCD_SymbolOn(LCD_SymbolKind sy) {
  (void)LCD1_SetSegmentState(LCD_SymbolTable[sy][0], LCD_SymbolTable[sy][1], TRUE);
}

void LCD_SymbolOff(LCD_SymbolKind sy) {
  (void)LCD1_SetSegmentState(LCD_SymbolTable[sy][0], LCD_SymbolTable[sy][1], FALSE);
}

void LCD_WeekDay(void) {
  DATEREC date;
  byte weekday;
  
  LCD_SymbolOff(LCD_SYMBOL_MONDAY);
  LCD_SymbolOff(LCD_SYMBOL_TUESDAY);
  LCD_SymbolOff(LCD_SYMBOL_WEDNESDAY);
  LCD_SymbolOff(LCD_SYMBOL_THURSDAY);
  LCD_SymbolOff(LCD_SYMBOL_FRIDAY);
  LCD_SymbolOff(LCD_SYMBOL_SATURDAY);
  LCD_SymbolOff(LCD_SYMBOL_SUNDAY);
  (void)TmDt1_GetDate(&date);
  weekday = UTIL1_WeekDay(date.Year, date.Month, date.Day);
  switch(weekday) {
    case 0: LCD_SymbolOn(LCD_SYMBOL_SUNDAY); break;
    case 1: LCD_SymbolOn(LCD_SYMBOL_MONDAY); break;
    case 2: LCD_SymbolOn(LCD_SYMBOL_TUESDAY); break;
    case 3: LCD_SymbolOn(LCD_SYMBOL_WEDNESDAY); break;
    case 4: LCD_SymbolOn(LCD_SYMBOL_THURSDAY); break;
    case 5: LCD_SymbolOn(LCD_SYMBOL_FRIDAY); break;
    case 6: LCD_SymbolOn(LCD_SYMBOL_SATURDAY); break;
  }
}

void LCD_ShowTime(void) {
  TIMEREC time;
  
  (void)TmDt1_GetTime(&time);
  if (time.Hour>12) {
    LCD_SymbolOff(LCD_SYMBOL_AM);
    LCD_SymbolOn(LCD_SYMBOL_PM);
    time.Hour -= 12;
  } else {
    LCD_SymbolOff(LCD_SYMBOL_PM);
    LCD_SymbolOn(LCD_SYMBOL_AM);
  }
  if (time.Hour>=10) {
    LCD_SymbolOn(LCD_SYMBOL_T1);
    time.Hour -= 10;
  } else {
    LCD_SymbolOff(LCD_SYMBOL_T1);
  }
  LCD_PrintAlphaNum(0, '0'+(time.Hour%10));
  LCD_SymbolOn(LCD_SYMBOL_COLON);
  LCD_PrintAlphaNum(1, '0'+(time.Min/10));
  LCD_PrintAlphaNum(2, '0'+(time.Min%10));
  LCD_PrintAlphaNum(3, '0'+(time.Sec/10));
  LCD_PrintAlphaNum(4, '0'+(time.Sec%10));
  LCD_WeekDay();
}

void LCD_Test(void) {
  byte i, j;
  
  LCD_ShowTime();
  for(j=0;j<LCD_NOF_CHARS;j++) {
    for(i='0';i<='9';i++) {
      LCD_PrintAlphaNum(j, i);
      WAIT1_Waitms(50);
    }
  }
  for(j=0;j<LCD_NOF_CHARS;j++) {
    LCD_PrintAlphaNum(j, ' ');
  }
  for(i=0; i<LCD_SYMBOL_LAST; i++) {
    LCD_SymbolOn(i);
    WAIT1_Waitms(50);
  }
  WAIT1_Waitms(500);
  for(i=0; i<LCD_SYMBOL_LAST; i++) {
    LCD_SymbolOff(i);
    WAIT1_Waitms(50);
  }
}
