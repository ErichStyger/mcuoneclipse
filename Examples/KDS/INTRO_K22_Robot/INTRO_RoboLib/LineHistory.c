/*
 * LineHistory.c
 *
 *  Created on: 30.08.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#if PL_HAS_LINE_SENSOR
#include "LineHistory.h"
#include "Reflectance.h"

#define HISTORY_MIN_SENSOR_VAL      0x60   /* minimum threshold value which is recorded in history */

static uint16_t SensorHistory[REF_NOF_SENSORS]; /* value of history while moving forward */

void HISTORY_SampleSensors(void) {
  uint8_t i;
  uint16_t val[REF_NOF_SENSORS];

  REF_GetSensorValues(&val[0], REF_NOF_SENSORS);
  for(i=0; i<REF_NOF_SENSORS; i++) {
    if (val[i]>=HISTORY_MIN_SENSOR_VAL) { /* only count line values */
      if (val[i]>SensorHistory[i]) {
        SensorHistory[i] = val[i];
      }
    }
  }
}

/*!
 * \brief Can be called during turning, will use it to sample sensor values.
 */
bool HISTORY_SampleTurnStopFunction(void) {
  HISTORY_SampleSensors();
  return FALSE; /* do not stop turning */
}

REF_LineKind HISTORY_LineKind(void) {
  int i, cnt, cntLeft, cntRight;

  cnt = cntLeft = cntRight = 0;
  for(i=0;i<REF_NOF_SENSORS;i++) {
    if (SensorHistory[i]>HISTORY_MIN_SENSOR_VAL) { /* count above threshold values */
      cnt++;
#if REF_SENSOR1_IS_LEFT
      if (i<REF_NOF_SENSORS/2) {
        cntLeft++;
      } else {
        cntRight++;
      }
#else
      if (i<REF_NOF_SENSORS/2) {
        cntRight++;
      } else {
        cntLeft++;
      }
#endif
    }
  }
  if (cnt==0) {
    return REF_LINE_NONE;
  } else if (cnt==REF_NOF_SENSORS) {
    return REF_LINE_FULL;
  } else if (cntLeft>cntRight) {
    return REF_LINE_LEFT;
  } else { /* must be cntRight>cntLeft */
    return REF_LINE_RIGHT;
  }
}

void HISTORY_Clear(void) {
  int i;

  for(i=0;i<REF_NOF_SENSORS;i++) {
    SensorHistory[i] = 0;
  }
}
#endif /* PL_HAS_LINE_SENSOR */

