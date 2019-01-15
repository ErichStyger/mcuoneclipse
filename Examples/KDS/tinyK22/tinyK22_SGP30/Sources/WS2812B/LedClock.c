/*
 * LedClock.c
 *
 *  Created on: 14.01.2019
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_HAS_NEO_CLOCK
#include "LedClock.h"
#include "TmDt1.h"
#include "FRTOS1.h"
#include "LEDFrame.h"
#include "LedDisp.h"
#include "NeoApp.h"
#include "Orientation.h"

static xTaskHandle ClockTaskHandle; /* task handle */

#if 0
static void ClockUpdate(void) {
  static int prevHour=-1, prevMinute=-1, prevSecond=1;
  TIMEREC time;
  uint8_t res;

  res = TmDt1_GetTime(&time);
  if (res==ERR_OK) {
    if (time.Hour!=prevHour || time.Min!=prevMinute || time.Sec!=prevSecond) {
#if PL_HAS_LED_FRAME_CLOCK
      NEOA_RequestNeoMutex();
      LEDFRAME_ShowClockTime(&time);
      NEOA_ReleaseNeoMutex();
#endif
      prevHour = time.Hour;
      prevMinute = time.Min;
      prevSecond = time.Sec;
    }
  }
}
#endif

static void SetDisplayOrientation(ORI_Orientation_e orientation) {
  switch(orientation) {
    case ORI_ORIENTATION_X_UP:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_PORTRAIT);
      break;
    case ORI_ORIENTATION_X_DOWN:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_PORTRAIT180);
      break;
    case ORI_ORIENTATION_Y_UP:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE180);
      break;
    case ORI_ORIENTATION_Y_DOWN:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
      break;
    case ORI_ORIENTATION_Z_UP:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
      break;
    case ORI_ORIENTATION_Z_DOWN:
      LedDisp_SetDisplayOrientation(LedDisp_ORIENTATION_LANDSCAPE);
      break;
    default:
      break;
  } /* switch */
}

static void ClockTask(void* pvParameters) {
  ORI_Orientation_e oldOrientation, newOrientation;

  (void)pvParameters; /* parameter not used */
  oldOrientation = ORI_GetCurrentOrientation();
  SetDisplayOrientation(oldOrientation);
  for(;;) {
    /* check orientation */
    newOrientation = ORI_GetCurrentOrientation();
    if (newOrientation!=oldOrientation) {
      oldOrientation = newOrientation;
      SetDisplayOrientation(newOrientation);
    }
    /* update clock */
    NEOA_RequestNeoMutex();
    if (LEDFRAME_CheckAndUpdateClock()==ERR_OK) {
      NEOA_RequestDisplayUpdate();
    }
    NEOA_ReleaseNeoMutex();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void LedClock_StartTask(void) {
  if (xTaskCreate(
        ClockTask,  /* pointer to the task */
        "Clock", /* task name for kernel awareness debugging */
        800/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        &ClockTaskHandle /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

void LedClock_StopTask(void) {
  if (ClockTaskHandle!=NULL) {
    vTaskDelete(ClockTaskHandle);
  }
  ClockTaskHandle = NULL;
}

#endif /* PL_CONFIG_HAS_NEO_CLOCK */
