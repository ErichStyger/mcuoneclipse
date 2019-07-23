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
  uint16_t version;
  uint8_t id;

//  McuSTMPE610_GetID(&id);
//  McuSTMPE610_GetVersion(&version);
#endif
  return 0; /* not touched */
}

void TOUCH_Init(void) {
}

void TOUCH_Deinit(void) {
}

#endif /* PL_CONFIG_USE_TOUCH */
