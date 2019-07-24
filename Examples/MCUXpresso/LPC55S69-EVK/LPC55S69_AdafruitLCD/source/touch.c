/*
 * touch.c
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_USE_GUI_TOUCH_NAV
#include "McuLib.h"
#include "touch.h"
#include "McuILI9341.h"
#if PL_CONFIG_USE_FT6206
  #include "McuFT6206.h"
#endif
#if PL_CONFIG_USE_STMPE610
  #include "McuSTMPE610.h"
#endif

#if PL_CONFIG_USE_FT6206
static void TOUCH_OrientationRotate(McuFT6206_TouchPoint *point) {
  /* Portrait180 */
  point->y = MCUILI9341_TFTHEIGHT-point->y;
  point->x = MCUILI9341_TFTWIDTH-point->x;
}
#endif

int TOUCH_Poll(bool *pressed, int *x, int *y) {
  /* defaults */
  *pressed = false;
  *x = 0;
  *y = 0;
#if PL_CONFIG_USE_FT6206
  uint8_t val, res;
  McuFT6206_TouchPoint point;

  if (McuFT6206_ReadNofTouches(&val)==ERR_OK) {
    if (val>0) { /* there are touches */
      res = McuFT6206_ReadPoint(0, &point);
      if (point.z>0) {
        val = 0;
      }
      if (res==ERR_OK && point.z>0) {
        TOUCH_OrientationRotate(&point);
        *pressed = true;
        *x = point.x;
        *y = point.y;
        return 1; /* touched */
      }
    }
  }
#endif
#if PL_CONFIG_USE_STMPE610
  /* test only */
  bool empty;
  uint8_t res, zd;
  uint16_t xd, yd;

  res = McuSTMPE610_FIFOisEmpty(&empty);
  if (res==ERR_OK && !empty) {
    res = McuSTMPE610_GetLastPoint(&xd, &yd, &zd);
    if (res==ERR_OK) {
      /* the STMPE610 delivers x and y in the range of 0...4096, and z is the pressure (the harder the press, the lower the number */
      #define TS_MINX 300
      #define TS_MAXX 3800
      #define TS_MINY 210
      #define TS_MAXY 3700
      #define LCD_HEIGHT 320
      #define LCD_WIDTH  240

      *x = McuUtility_map(xd, TS_MINX, TS_MAXX, 0, LCD_WIDTH);
      *y = McuUtility_map(yd, TS_MINY, TS_MAXY, 0, LCD_HEIGHT);
      if (*x < 0) {
        *x = 0;
      } else if (*x > LCD_WIDTH-1) {
        *x = LCD_WIDTH-1;
      }
      if (*y < 0) {
        *y = 0;
      } else if (*y > LCD_HEIGHT-1) {
        *y = LCD_HEIGHT-1;
      }
      *pressed = true;
      return 1; /* touched */
    }
  }
#endif
  return 0; /* not touched */
}

void TOUCH_Init(void) {
}

void TOUCH_Deinit(void) {
}

#endif /* PL_CONFIG_USE_TOUCH */
