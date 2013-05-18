/*
 * Reflectance.h
 *
 *  Created on: Feb 5, 2013
 *      Author: Erich Styger
 */

#ifndef REFLECTANCE_H_
#define REFLECTANCE_H_

#include "Platform.h"
#if PL_HAS_LINE_SENSOR
#include "CLS1.h"

#if PL_IS_ZUMO_ROBOT
  #define REF_NOF_SENSORS 6
#else
  #define REF_NOF_SENSORS 8
#endif

#define REF_MIDDLE_LINE_VALUE  ((REF_NOF_SENSORS+1)*1000/2)

typedef enum {
  REF_LINE_NONE=0,     /* no line, sensors do not see a line */
  REF_LINE_STRAIGHT=1, /* forward line |, sensors see a line underneath */
  REF_LINE_LEFT=2,     /* left half of sensors see line */
  REF_LINE_RIGHT=3,    /* right half of sensors see line */
  REF_LINE_FULL=4,     /* all sensors see a line */
  REF_LINE_AIR=5,      /* all sensors have a timeout value. Robot is not on ground at all? */
  REF_NOF_LINES        /* Sentinel */
} REF_LineKind;

REF_LineKind REF_GetLineKind(void);
REF_LineKind REF_HistoryLineKind(void);
void REF_ClearHistory(void);
void REF_SampleHistory(void);
void REF_DumpHistory(void);

unsigned char *REF_LineKindStr(REF_LineKind line);

byte REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void REF_InitSensorValues(void);

void REF_Measure(void);

#define REF_MAX_LINE_VALUE  ((REF_NOF_SENSORS-1)*1000) /* maximum value for REF_GetLine() */
uint16_t REF_GetLineValue(bool *onLine);

/*!
 * \brief starts or stops a reflectance sensor calibration.
 * \param start TRUE means starting the calibration, FALSE stops it.
 */
void REF_Calibrate(bool start);

/*!
 * \brief Function to find out if we can use the sensor (means: it is calibrated and not currently calibrating)
 * \return TRUE if the sensor is ready.
 */
bool REF_CanUseSensor(void);

bool REF_IsCalibrating(void);

void REF_Init(void);

#endif /* PL_HAS_LINE_SENSOR */

#endif /* REFLECTANCE_H_ */
