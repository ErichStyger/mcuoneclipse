/** ###################################################################
**     Filename  : LedFont.C
**     Project   : MPR08x
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 24.12.2008, 15:41
**     Contents  :
**         User source code
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE LedFont */

#include "LedFont.h"
#include "UTIL1.h"
#include "GDISP1.h"

static char LedFont_Text[48] =""; /* text to scroll across the display */
static bool LedFont_ScrollOnce = FALSE;

OS_FLAG_GRP *LedFont_Flags;

typedef struct {
  byte data[GDisp1_GetHeight()];
  GDisp1_PixelDim size; /* number of bytes to be used inside data */
} LedFont_FontDesc;

static const LedFont_FontDesc LedFont_FontTable [] = { 
 {{ 0b00000, 0b00000, 0b00000, 0b00000, 0b00000 }, 2}, // Space
 {{ 0b10111, 0b00000, 0b00000, 0b00000, 0b00000 }, 1}, // !
 {{ 0b00100, 0b00011, 0b00100, 0b00011, 0b00000 }, 4}, // "
 {{ 0b01010, 0b11111, 0b01010, 0b11111, 0b01010 }, 5}, // #
 {{ 0b10010, 0b10101, 0b11111, 0b10101, 0b01001 }, 5}, // $
 {{ 0b10011, 0b01011, 0b00100, 0b11010, 0b11001 }, 5}, // %
 {{ 0b01010, 0b10101, 0b10111, 0b01000, 0b11000 }, 5}, // &
 {{ 0b00100, 0b00011, 0b00000, 0b00000, 0b00000 }, 2}, // '
 {{ 0b01110, 0b10001, 0b00000, 0b00000, 0b00000 }, 2}, // (
 {{ 0b10001, 0b01110, 0b00000, 0b00000, 0b00000 }, 2}, // )
 {{ 0b01010, 0b00100, 0b11111, 0b00100, 0b01010 }, 5}, // *
 {{ 0b00100, 0b01110, 0b00100, 0b00000, 0b00000 }, 3}, // +
 {{ 0b10000, 0b01000, 0b00000, 0b00000, 0b00000 }, 2}, // ,
 {{ 0b00100, 0b00100, 0b00100, 0b00000, 0b00000 }, 3}, // -
 {{ 0b10000, 0b00000, 0b00000, 0b00000, 0b00000 }, 1}, // .
 {{ 0b10000, 0b01000, 0b00100, 0b00010, 0b00001 }, 5}, // /
 {{ 0b01110, 0b11001, 0b10101, 0b01110, 0b00000 }, 4}, // 0
 {{ 0b10010, 0b11111, 0b10000, 0b00000, 0b00000 }, 3}, // 1
 {{ 0b11001, 0b10101, 0b10101, 0b10010, 0b00000 }, 4}, // 2
 {{ 0b10001, 0b10101, 0b10101, 0b01010, 0b00000 }, 4}, // 3
 {{ 0b01100, 0b01010, 0b11111, 0b01000, 0b00000 }, 4}, // 4
 {{ 0b10011, 0b10101, 0b10101, 0b01001, 0b00000 }, 4}, // 5
 {{ 0b01110, 0b10101, 0b10101, 0b01000, 0b00000 }, 4}, // 6
 {{ 0b00001, 0b11001, 0b00101, 0b00011, 0b00000 }, 4}, // 7
 {{ 0b01010, 0b10101, 0b10101, 0b01010, 0b00000 }, 4}, // 8
 {{ 0b00010, 0b10101, 0b10101, 0b11110, 0b00000 }, 4}, // 9
 {{ 0b01010, 0b00000, 0b00000, 0b00000, 0b00000 }, 1}, // :
 {{ 0b10000, 0b01010, 0b00000, 0b00000, 0b00000 }, 2}, // ;
 {{ 0b00100, 0b01010, 0b10001, 0b00000, 0b00000 }, 3}, // <
 {{ 0b01010, 0b01010, 0b01010, 0b00000, 0b00000 }, 3}, // =
 {{ 0b10001, 0b01010, 0b00100, 0b00000, 0b00000 }, 3}, // >
 {{ 0b00010, 0b00001, 0b10101, 0b00101, 0b00010 }, 5}, // ?
 {{ 0b01110, 0b10001, 0b10101, 0b10101, 0b10110 }, 5}, // @
 {{ 0b11110, 0b00101, 0b00101, 0b11110, 0b00000 }, 4}, // A
 {{ 0b11111, 0b10101, 0b10101, 0b01010, 0b00000 }, 4}, // B
 {{ 0b01110, 0b10001, 0b10001, 0b10001, 0b00000 }, 4}, // C
 {{ 0b11111, 0b10001, 0b10001, 0b01110, 0b00000 }, 4}, // D
 {{ 0b11111, 0b10101, 0b10101, 0b10001, 0b00000 }, 4}, // E
 {{ 0b11111, 0b00101, 0b00101, 0b00001, 0b00000 }, 4}, // F
 {{ 0b01110, 0b10001, 0b10101, 0b11100, 0b00000 }, 4}, // G
 {{ 0b11111, 0b00100, 0b00100, 0b11111, 0b00000 }, 4}, // H
 {{ 0b10001, 0b11111, 0b10001, 0b00000, 0b00000 }, 3}, // I
 {{ 0b01000, 0b10001, 0b01111, 0b00001, 0b00000 }, 4}, // J
 {{ 0b11111, 0b00100, 0b01010, 0b10001, 0b00000 }, 4}, // K
 {{ 0b11111, 0b10000, 0b10000, 0b10000, 0b00000 }, 4}, // L
 {{ 0b11111, 0b00010, 0b00100, 0b00010, 0b11111 }, 5}, // M
 {{ 0b11111, 0b00010, 0b00100, 0b11111, 0b00000 }, 4}, // N
 {{ 0b01110, 0b10001, 0b10001, 0b01110, 0b00000 }, 4}, // O
 {{ 0b11111, 0b00101, 0b00101, 0b00010, 0b00000 }, 4}, // P
 {{ 0b01110, 0b10001, 0b01001, 0b10110, 0b00000 }, 4}, // Q
 {{ 0b11111, 0b00101, 0b01101, 0b10010, 0b00000 }, 4}, // R
 {{ 0b10010, 0b10101, 0b10101, 0b01001, 0b00000 }, 4}, // S
 {{ 0b00001, 0b00001, 0b11111, 0b00001, 0b00001 }, 5}, // T
 {{ 0b01111, 0b10000, 0b10000, 0b01111, 0b00000 }, 4}, // U
 {{ 0b00011, 0b01100, 0b10000, 0b01100, 0b00011 }, 5}, // V
 {{ 0b11111, 0b01000, 0b00100, 0b01000, 0b11111 }, 5}, // W
 {{ 0b10001, 0b01010, 0b00100, 0b01010, 0b10001 }, 5}, // X
 {{ 0b00001, 0b00010, 0b11100, 0b00010, 0b00001 }, 5}, // Y
 {{ 0b10001, 0b11001, 0b10101, 0b10011, 0b10001 }, 5}, // Z
 {{ 0b11111, 0b10001, 0b10001, 0b00000, 0b00000 }, 3}, // [
 {{ 0b00001, 0b00010, 0b00100, 0b01000, 0b10000 }, 5}, // (
 {{ 0b10001, 0b10001, 0b11111, 0b00000, 0b00000 }, 3}, // ]
 {{ 0b00010, 0b00001, 0b00010, 0b00000, 0b00000 }, 3}, // ^
 {{ 0b10000, 0b10000, 0b10000, 0b10000, 0b10000 }, 5}, // _
 {{ 0b00011, 0b00100, 0b00000, 0b00000, 0b00000 }, 2}, // '
 {{ 0b01000, 0b10101, 0b10101, 0b10101, 0b11110 }, 5}, // a
 {{ 0b11111, 0b10100, 0b10100, 0b11100, 0b00000 }, 4}, // b
 {{ 0b01100, 0b10010, 0b10010, 0b10010, 0b00000 }, 4}, // c
 {{ 0b01000, 0b10100, 0b10100, 0b10100, 0b11111 }, 5}, // d
 {{ 0b01110, 0b10101, 0b10101, 0b10101, 0b10110 }, 5}, // e
 {{ 0b00100, 0b11110, 0b00101, 0b00001, 0b00010 }, 5}, // f
 {{ 0b10010, 0b10101, 0b10101, 0b10101, 0b01110 }, 5}, // g
 {{ 0b11111, 0b00100, 0b00100, 0b11000, 0b00000 }, 4}, // h
 {{ 0b11101, 0b00000, 0b00000, 0b00000, 0b00000 }, 1}, // i
 {{ 0b10000, 0b01101, 0b00000, 0b00000, 0b00000 }, 2}, // j
 {{ 0b11111, 0b00100, 0b01010, 0b10001, 0b00000 }, 4}, // k
 {{ 0b10001, 0b11111, 0b10000, 0b00000, 0b00000 }, 3}, // l
 {{ 0b11110, 0b00001, 0b00110, 0b00001, 0b11110 }, 5}, // m
 {{ 0b11111, 0b00001, 0b00001, 0b00001, 0b11110 }, 5}, // n
 {{ 0b01110, 0b10001, 0b10001, 0b01110, 0b00000 }, 4}, // o
 {{ 0b11111, 0b00101, 0b00101, 0b00010, 0b00000 }, 4}, // p
 {{ 0b00010, 0b00101, 0b00101, 0b11111, 0b10000 }, 5}, // q
 {{ 0b11111, 0b00010, 0b00001, 0b00001, 0b00010 }, 5}, // r
 {{ 0b10010, 0b10101, 0b10101, 0b01001, 0b00000 }, 4}, // s
 {{ 0b00010, 0b01111, 0b10010, 0b10010, 0b00000 }, 4}, // t
 {{ 0b01111, 0b10000, 0b10000, 0b01111, 0b00000 }, 4}, // u
 {{ 0b00011, 0b01100, 0b10000, 0b01100, 0b00011 }, 5}, // v
 {{ 0b01111, 0b10000, 0b01100, 0b10000, 0b01111 }, 5}, // w
 {{ 0b10001, 0b01010, 0b00100, 0b01010, 0b10001 }, 5}, // x
 {{ 0b10011, 0b10100, 0b10100, 0b01111, 0b00000 }, 4}, // y
 {{ 0b10010, 0b11010, 0b10110, 0b10010, 0b00000 }, 4}, // z
 {{ 0b00110, 0b01111, 0b11110, 0b01111, 0b00110 }, 5}, // {
 {{ 0b10010, 0b01000, 0b00111, 0b01000, 0b10010 }, 5}, // |
 {{ 0b00100, 0b01110, 0b10101, 0b00100, 0b00100 }, 5}, // }
 {{ 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 }, 5}, // 
};

void LedFont_ScrollText(char *text, bool scrollOnce, bool waitForFinish) {
  INT8U err;
  
  UTIL1_strcpy((uint8_t*)LedFont_Text, sizeof(LedFont_Text), (const unsigned char*)text);
  LedFont_ScrollOnce = scrollOnce;
  while (!(OSFlagQuery(LedFont_Flags, &err)&LEDFONT_FLAG_READY)) {
    (void)OSTimeDlyHMSM(0,0,0,100); /* wait task to be ready */
  }
  OSTaskResume(TASK_PRIO_SCROLLER);
  if (scrollOnce && waitForFinish) {
    while (!(OSFlagQuery(LedFont_Flags, &err)&LEDFONT_FLAG_FINISHED_SCROLLING)) {
      (void)OSTimeDlyHMSM(0,0,0,100); /* wait for scrolling to be finished */
    }
    OSFlagPost(LedFont_Flags, LEDFONT_FLAG_FINISHED_SCROLLING, OS_FLAG_CLR, &err); /* clear flag */
  }
}

static GDisp1_PixelDim LedFont_PutChar(char ch, short x) {
  byte i, data;
  GDisp1_PixelDim y = 0;
  const LedFont_FontDesc *fontChar;
  
  if (ch < 0x20 || ch > 0x7E) { /* non-printable character */
    ch = ' '; /* convert to a blank */
  }
  fontChar = &LedFont_FontTable[ch-0x20];
  for(i=0;i<fontChar->size;i++) { /* process font elems */
    data = fontChar->data[i];
    y = 0;
    while(x>=0 && data!=0 && x<GDisp1_GetWidth()) {
      if (data&1) {
        GDisp1_SetPixel((GDisp1_PixelDim)x, y);
      } else {
        GDisp1_ClrPixel((GDisp1_PixelDim)x, y);
      }
      data >>= 1; /* next bit */
      y++;
    }
    x++;
  }
  return fontChar->size;
}

static void LedFont_Stop(void) {
  INT8U err;

  if (LedFont_ScrollOnce) {
    OSFlagPost(LedFont_Flags, LEDFONT_FLAG_FINISHED_SCROLLING, OS_FLAG_SET, &err); /* clear all button flags */
  }
  OSTaskSuspend(OS_PRIO_SELF); /* put task to sleep */
}

void LedFont_Scroller(void *pdata) {
  INT8U err;
  char *p;
  short x, xStart;

  (void)pdata; /* avoid compiler warning */
  OSFlagPost(LedFont_Flags, LEDFONT_FLAG_READY, OS_FLAG_SET, &err); /* announce that we are ready */
  for(;;) { /* forever */
    while (LedFont_Text[0] == '\0') { /* no text */
      LedFont_Stop();
    }
    for(xStart=GDisp1_GetWidth()-1;;xStart--) {
      GDisp1_Clear();
      p = &LedFont_Text[0]; /* get character */
      x = xStart;
      while(*p != '\0') { /* go through the text */
        x += LedFont_PutChar(*p, x);
        p++; /* next character */
        x++; /* add a space between characters */
      }
      GDisp1_UpdateFull();
      if (x <= 0) { /* reached end of text to scroll: start over again */
        LedFont_Stop();
        break; /* start again */
      }
      (void)OSTimeDlyHMSM(0,0,0,60); /* delay specifies the scrolling speed */
      if (OSFlagQuery(LedFont_Flags, &err)&LEDFONT_FLAG_QUIT) { /* E8 pressed: quit */
        OSFlagPost(LedFont_Flags, LEDFONT_FLAG_QUIT, OS_FLAG_CLR, &err); /* clear flag */
        LedFont_Stop();
        break; /* start again */
      }
    } /* for */
  }
}

/* END LedFont */
