/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
  #include "TouchCalibrate.h"
#endif

#if PL_CONFIG_USE_FT6206
static void TOUCH_OrientationRotate(McuFT6206_TouchPoint *point) {
  /* Portrait180 */
  point->y = MCUILI9341_TFTHEIGHT-point->y;
  point->x = MCUILI9341_TFTWIDTH-point->x;
}
#endif

uint8_t TOUCH_Poll(bool *pressed, uint16_t *x, uint16_t *y) {
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
      if (point.z>0) { /* z indicates how strong it was pressed */
        val = 0;
      }
      if (res==ERR_OK && point.z>0) {
        TOUCH_OrientationRotate(&point);
        *pressed = true;
        *x = point.x;
        *y = point.y;
        return ERR_OK; /* touched */
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
    if (TouchCalib_IsCalibrated()) {
      res = McuSTMPE610_GetCalibratedCoordinates(&xd, &yd, &zd);
    } else {
      res = McuSTMPE610_GetRawCoordinates(&xd, &yd, &zd);
    }
    if (res==ERR_OK) {
      *x = xd;
      *y = yd;
      *pressed = true;
      return ERR_OK; /* touched */
    }
  }
#endif
  return ERR_IDLE; /* not touched */
}

bool TOUCH_IsPressed(void) {
  uint8_t res;
#if PL_CONFIG_USE_STMPE610
  bool touched;

  res = McuSTMPE610_IsTouched(&touched);
  return res==ERR_OK && touched;
#elif PL_CONFIG_USE_FT6206
  uint8_t val;

  res = McuFT6206_ReadNofTouches(&val);
  return res==ERR_OK && val>0;
#endif
}

bool TOUCH_HasMoreData(void) {
#if PL_CONFIG_USE_STMPE610
  uint8_t res;
  bool empty;

  res = McuSTMPE610_FIFOisEmpty(&empty);
  return res==ERR_OK && !empty;
#elif PL_CONFIG_USE_FT6206
  return false; /* we are not buffering data */
#endif
}

void TOUCH_Init(void) {
}

void TOUCH_Deinit(void) {
}

#endif /* PL_CONFIG_USE_TOUCH */
