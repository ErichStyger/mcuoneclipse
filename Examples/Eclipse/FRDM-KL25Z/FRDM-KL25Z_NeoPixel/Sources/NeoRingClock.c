/*
 * NeoRingClock.c
 *
 *  Created on: 07.07.2014
 *      Author: tastyger
 */

#include "NeoPixel.h"
#include "TmDt1.h"
#include "NeoLine.h"

#define CLOCK_NOF_PIXEL         60 /* number of pixels in ring */
#define CLOCK_IDX_START_PIXEL   0  /* start index of clock */
#define CLOCK_IDX_END_PIXEL     (CLOCK_IDX_START_PIXEL+CLOCK_NOF_PIXEL-1) /* index of last pixel */
#define CLOCK_NOF_HOUR_MARKS    12 /* number of markings for the hours */

#define CLOCK_DIMM_HOURLY_MARKS  16 /* dimming divisor for hour marks */
#define CLOCK_DIMM_HMS_MARKS     2  /* dimming factor for hour, minute and seconds dots */
#define CLOCK_MULTI_HOUR_MARKS   1  /* 1 or 0 */

#define CLOCK_RGB_HOURLY_MARKS (0xff/CLOCK_DIMM_HOURLY_MARKS), (0xff/CLOCK_DIMM_HOURLY_MARKS), (0xff/CLOCK_DIMM_HOURLY_MARKS)

#define CLOCK_RGB_HOUR_DOT_M1   0x00, (0xff/(CLOCK_DIMM_HMS_MARKS*8)), 0x00
#define CLOCK_RGB_HOUR_DOT      0x00, (0xff/CLOCK_DIMM_HMS_MARKS), 0x00
#define CLOCK_RGB_HOUR_DOT_P1   0x00, (0xff/(CLOCK_DIMM_HMS_MARKS*8)), 0x00

#define CLOCK_RGB_MINUTE_DOT    0x00, 0x00, (0xff/CLOCK_DIMM_HMS_MARKS)
#define CLOCK_RGB_SECOND_DOT    (0xff/CLOCK_DIMM_HMS_MARKS), 0x00, (0xff/CLOCK_DIMM_HMS_MARKS)

void CLOCK_Clear(void) {
  NEO_PixelIdxT i;

  for(i=CLOCK_IDX_START_PIXEL;i<=CLOCK_IDX_END_PIXEL;i++) {
    NEO_ClearPixel(i);
  }
}

void CLOCK_DrawClockGround(void) {
  int i;
  NEO_PixelIdxT pixel;

  pixel = CLOCK_IDX_START_PIXEL;
  for (i=0;i<CLOCK_NOF_HOUR_MARKS;i++) {
    NEO_SetPixelRGB(pixel, CLOCK_RGB_HOURLY_MARKS);
    pixel += CLOCK_NOF_PIXEL/CLOCK_NOF_HOUR_MARKS; /* one mark every hour */
  }
}

void CLOCK_AddHour(uint8_t hour, uint8_t minute) {
  NEO_PixelIdxT pixel;

  if (hour>24) {
    return; /* only 0..23 allowed */
  }
  if (minute>60) {
    return; /* only 0..59 allowed */
  }
  if (hour>12) {
    hour -= 12;
  }
  pixel = CLOCK_IDX_START_PIXEL+((CLOCK_NOF_PIXEL*hour)/12); /* hour base */
  pixel += ((CLOCK_NOF_PIXEL*minute)/60/12); /* add minute offset */
#if CLOCK_MULTI_HOUR_MARKS
  NEO_SetPixelRGB(pixel, CLOCK_RGB_HOUR_DOT);
  if (pixel==CLOCK_IDX_START_PIXEL) {
    NEO_SetPixelRGB(pixel+1, CLOCK_RGB_HOUR_DOT_P1);
    NEO_SetPixelRGB(CLOCK_IDX_END_PIXEL, CLOCK_RGB_HOUR_DOT_M1);
  } else if (pixel==CLOCK_IDX_END_PIXEL) {
    NEO_SetPixelRGB(CLOCK_IDX_START_PIXEL, CLOCK_RGB_HOUR_DOT_P1);
    NEO_SetPixelRGB(pixel-1, CLOCK_RGB_HOUR_DOT_M1);
  } else {
    NEO_SetPixelRGB(pixel+1, CLOCK_RGB_HOUR_DOT_P1);
    NEO_SetPixelRGB(pixel-1, CLOCK_RGB_HOUR_DOT_M1);
  }
#else
  NEO_SetPixelRGB(pixel, CLOCK_RGB_HOUR_DOT);
#endif
}

void CLOCK_AddMinute(uint8_t minute) {
  NEO_PixelIdxT pixel;

  if (minute>60) {
    return; /* only 0..59 allowed */
  }
  pixel = CLOCK_IDX_START_PIXEL+((CLOCK_NOF_PIXEL*minute)/60);
  NEO_SetPixelRGB(pixel, CLOCK_RGB_MINUTE_DOT);
}

void CLOCK_AddSecond(uint8_t sec) {
  NEO_PixelIdxT pixel;

  if (sec>60) {
    return; /* only 0..59 allowed */
  }
  pixel = CLOCK_IDX_START_PIXEL+((CLOCK_NOF_PIXEL*sec)/60);
  NEO_SetPixelRGB(pixel, CLOCK_RGB_SECOND_DOT);
}

void CLOCK_SetTime(uint8_t hour, uint8_t min, uint8_t second) {
  CLOCK_Clear();
  CLOCK_DrawClockGround();
  CLOCK_AddHour(hour, min);
  CLOCK_AddMinute(min);
  CLOCK_AddSecond(second);
}

#include "TI1.h"

void CLOCK_Update(void) {
  static int prevHour=-1, prevMinute=-1, prevSecond=1;
  TIMEREC time;
  uint8_t res;

  res = TmDt1_GetTime(&time);
  if (res==ERR_OK) {
    if (time.Hour!=prevHour || time.Min!=prevMinute || time.Sec!=prevSecond) {
      CLOCK_SetTime(time.Hour, time.Min, time.Sec);
      (void)NEO_TransferPixels();
      prevHour = time.Hour;
      prevMinute = time.Min;
      prevSecond = time.Sec;
    }
  }
}

void CLOCK_Init(void) {
  CLOCK_Clear();
  (void)NEOL_PixelTrail(0x00, 0x00, 0xFF, CLOCK_IDX_START_PIXEL, CLOCK_IDX_END_PIXEL,  8, 25, 25);
}

