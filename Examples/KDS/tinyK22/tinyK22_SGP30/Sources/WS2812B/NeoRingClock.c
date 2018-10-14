/*
 * NeoRingClock.c
 *
 *  Created on: 07.07.2014
 *      Author: tastyger
 */

#include "NeoPixel.h"
#include "TmDt1.h"
#include "NeoLine.h"
#include "NeoRingClock.h"

#define CLOCK_HAS_RING_60         1
#define CLOCK_RING_60_NOF_PIXEL   60
#define CLOCK_RING_60_PIXEL_FIRST 0 /* start pixel index of 60 ring */
#define CLOCK_RING_60_PIXEL_LAST  (CLOCK_RING_60_PIXEL_FIRST+CLOCK_RING_60_NOF_PIXEL-1) /* end pixel index of 60 ring */

#define CLOCK_HAS_RING_24         1
#define CLOCK_RING_24_NOF_PIXEL   24
#define CLOCK_RING_24_PIXEL_FIRST (CLOCK_RING_60_PIXEL_LAST+1) /* start pixel index of 24 ring */
#define CLOCK_RING_24_PIXEL_LAST  (CLOCK_RING_24_PIXEL_FIRST+CLOCK_RING_24_NOF_PIXEL-1) /* end pixel index of 24 ring */

#define CLOCK_HAS_RING_12         1
#define CLOCK_RING_12_NOF_PIXEL   12
#define CLOCK_RING_12_PIXEL_FIRST (CLOCK_RING_24_PIXEL_LAST+1) /* start pixel index of 12 ring */
#define CLOCK_RING_12_PIXEL_LAST  (CLOCK_RING_12_PIXEL_FIRST+CLOCK_RING_12_NOF_PIXEL-1) /* end pixel index of 12 ring */

#define CLOCK_NOF_PIXEL         (CLOCK_RING_60_NOF_PIXEL+CLOCK_RING_24_NOF_PIXEL+CLOCK_RING_12_NOF_PIXEL) /* number of pixels in ring */
#define CLOCK_IDX_START_PIXEL   0  /* start index of clock */
#define CLOCK_IDX_END_PIXEL     (CLOCK_IDX_START_PIXEL+CLOCK_NOF_PIXEL-1) /* index of last pixel */
#define CLOCK_NOF_HOUR_MARKS    12 /* number of markings for the hours */

#define CLOCK_DIMM_HOURLY_MARKS  16 /* >=1, dimming divisor for hour marks */
#define CLOCK_DIMM_HMS_MARKS     1  /* >=1, dimming divisor for hour, minute and seconds dots */
#define CLOCK_MULTI_HOUR_MARKS   1  /* 1 or 0 */

#define CLOCK_RGB_HOURLY_MARKS  NEO_MAKE_COLOR_RGB((0xff/CLOCK_DIMM_HOURLY_MARKS), (0xff/CLOCK_DIMM_HOURLY_MARKS), (0xff/CLOCK_DIMM_HOURLY_MARKS))

#define CLOCK_RGB_HOUR_DOT_M1   NEO_MAKE_COLOR_RGB(0x00, (0xff/(CLOCK_DIMM_HMS_MARKS*8)), 0x00)
#define CLOCK_RGB_HOUR_DOT      0x00, (0xff/CLOCK_DIMM_HMS_MARKS), 0x00
#define CLOCK_RGB_HOUR_DOT_P1   NEO_MAKE_COLOR_RGB(0x00, (0xff/(CLOCK_DIMM_HMS_MARKS*8)), 0x00)

#define CLOCK_RGB_MINUTE_DOT    0x00, 0x00, (0xff/CLOCK_DIMM_HMS_MARKS)
#define CLOCK_RGB_SECOND_DOT    NEO_MAKE_COLOR_RGB((0xff/CLOCK_DIMM_HMS_MARKS), 0x00, (0xff/CLOCK_DIMM_HMS_MARKS))

static void CLOCK_Clear(void) {
  NEO_PixelIdxT i;

  for(i=CLOCK_IDX_START_PIXEL;i<=CLOCK_IDX_END_PIXEL;i++) {
    NEO_ClearPixel(0, i);
  }
}

/*!
 * \brief Draws the 'background' of the clock with the clock hour marks
 */
static void CLOCK_DrawClockGround(void) {
  int i;
  NEO_PixelIdxT pixel;

#if CLOCK_HAS_RING_60
  pixel = CLOCK_RING_60_PIXEL_FIRST;
#elif CLOCK_HAS_RING_24
  pixel = CLOCK_RING_24_PIXEL_FIRST;
#elif CLOCK_HAS_RING_12
  pixel = CLOCK_RING_12_PIXEL_FIRST;
#endif
  for (i=0;i<CLOCK_NOF_HOUR_MARKS;i++) {
    NEO_SetPixelColor(0, pixel, CLOCK_RGB_HOURLY_MARKS);
#if CLOCK_HAS_RING_60 /* marks only on outer ring */
    pixel += CLOCK_RING_60_NOF_PIXEL/CLOCK_NOF_HOUR_MARKS; /* one mark every hour */
#elif CLOCK_HAS_RING_24
    pixel += CLOCK_RING_24_NOF_PIXEL/CLOCK_NOF_HOUR_MARKS; /* one mark every hour */
#elif CLOCK_HAS_RING_12
    pixel += CLOCK_RING_12_NOF_PIXEL/CLOCK_NOF_HOUR_MARKS; /* one mark every hour */
#endif
  }
}

static void AddHour(uint8_t hour, uint8_t minute, NEO_PixelIdxT ringFirstPixel, NEO_PixelIdxT ringLastPixel, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT pixel;
  NEO_PixelIdxT ringNofPixel;

  if (hour>24) {
    return; /* only 0..23 allowed */
  }
  if (minute>60) {
    return; /* only 0..59 allowed */
  }
  if (hour>=12) {
    hour -= 12;
  }
  ringNofPixel = ringLastPixel-ringFirstPixel+1;
  pixel = ringFirstPixel+((ringNofPixel*hour)/12); /* hour base */
  pixel += ((ringNofPixel*minute)/60/12); /* add minute offset */
#if CLOCK_MULTI_HOUR_MARKS
  NEO_SetPixelColor(0, pixel, NEO_MAKE_COLOR_RGB(red, green, blue));
  if (pixel==ringFirstPixel) {
    NEO_SetPixelColor(0, pixel+1, CLOCK_RGB_HOUR_DOT_P1);
    NEO_SetPixelColor(0, ringLastPixel, CLOCK_RGB_HOUR_DOT_M1);
  } else if (pixel==ringLastPixel) {
    NEO_SetPixelColor(0, ringFirstPixel, CLOCK_RGB_HOUR_DOT_P1);
    NEO_SetPixelColor(0, pixel-1, CLOCK_RGB_HOUR_DOT_M1);
  } else {
    NEO_SetPixelColor(0, pixel+1, CLOCK_RGB_HOUR_DOT_P1);
    NEO_SetPixelColor(0, pixel-1, CLOCK_RGB_HOUR_DOT_M1);
  }
#else
  NEO_SetPixelRGB(pixel, red, green, blue);
#endif
}

/*!
 * \brief Draws the current hour mark
 * \param hour Current hour value
 * \param minute Current minute value
 */
static void CLOCK_AddHour(uint8_t hour, uint8_t minute) {
  if (hour>24) {
    return; /* only 0..23 allowed */
  }
  if (minute>60) {
    return; /* only 0..59 allowed */
  }
  if (hour>12) {
    hour -= 12;
  }
#if CLOCK_HAS_RING_60
  AddHour(hour, minute, CLOCK_RING_60_PIXEL_FIRST, CLOCK_RING_60_PIXEL_LAST, CLOCK_RGB_HOUR_DOT);
#endif
#if CLOCK_HAS_RING_24
  AddHour(hour, minute, CLOCK_RING_24_PIXEL_FIRST, CLOCK_RING_24_PIXEL_LAST, CLOCK_RGB_HOUR_DOT);
#endif
#if CLOCK_HAS_RING_12 && !CLOCK_HAS_RING_60
  AddHour(hour, minute, CLOCK_RING_12_PIXEL_FIRST, CLOCK_RING_12_PIXEL_LAST, CLOCK_RGB_HOUR_DOT);
#endif
}

static void AddMinute(uint8_t minute, NEO_PixelIdxT ringFirstPixel, NEO_PixelIdxT ringNofPixel, uint8_t red, uint8_t green, uint8_t blue) {
  NEO_PixelIdxT pixel;

  if (minute>60) {
    return; /* only 0..59 allowed */
  }

  pixel = ringFirstPixel+((ringNofPixel*minute)/60);
  NEO_SetPixelColor(0, pixel, NEO_MAKE_COLOR_RGB(red, green, blue));
}

static void CLOCK_AddMinute(uint8_t minute) {
  if (minute>60) {
    return; /* only 0..59 allowed */
  }
#if CLOCK_HAS_RING_60
  AddMinute(minute, CLOCK_RING_60_PIXEL_FIRST, CLOCK_RING_60_NOF_PIXEL, CLOCK_RGB_MINUTE_DOT);
#endif
#if CLOCK_HAS_RING_24
  AddMinute(minute, CLOCK_RING_24_PIXEL_FIRST, CLOCK_RING_24_NOF_PIXEL, CLOCK_RGB_MINUTE_DOT);
#endif
#if CLOCK_HAS_RING_12
  AddMinute(minute, CLOCK_RING_12_PIXEL_FIRST, CLOCK_RING_12_NOF_PIXEL, CLOCK_RGB_MINUTE_DOT);
#endif
}

static void CLOCK_AddSecond(uint8_t sec) {
  NEO_PixelIdxT pixel;
  NEO_PixelIdxT ringFirstPixel; /* first pixel of ring */
  NEO_PixelIdxT ringNofPixel; /* number of pixels in ring */

  if (sec>60) {
    return; /* only 0..59 allowed */
  }
#if CLOCK_HAS_RING_60
  ringFirstPixel = CLOCK_RING_60_PIXEL_FIRST;
  ringNofPixel = CLOCK_RING_60_NOF_PIXEL;
#elif CLOCK_HAS_RING_24
  ringFirstPixel = CLOCK_RING_24_PIXEL_FIRST;
  ringNofPixel = CLOCK_RING_24_NOF_PIXEL;
#elif CLOCK_HAS_RING_12
  ringFirstPixel = CLOCK_RING_12_PIXEL_FIRST;
  ringNofPixel = CLOCK_RING_12_NOF_PIXEL;
#endif
  pixel = ringFirstPixel+((ringNofPixel*sec)/60);
  NEO_SetPixelColor(0, pixel, CLOCK_RGB_SECOND_DOT);
}

void CLOCK_SetTime(uint8_t hour, uint8_t min, uint8_t second) {
  CLOCK_Clear();
  CLOCK_DrawClockGround();
  CLOCK_AddHour(hour, min);
  CLOCK_AddMinute(min);
  CLOCK_AddSecond(second);
}

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
  (void)NEOL_PixelTrail(NEO_MAKE_COLOR_RGB(0x00, 0x00, 0xFF), CLOCK_IDX_START_PIXEL, CLOCK_IDX_END_PIXEL, 8, 25, 25);
}

