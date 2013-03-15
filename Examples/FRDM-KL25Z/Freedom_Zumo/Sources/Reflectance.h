/*
 * Reflectance.h
 *
 *  Created on: Feb 5, 2013
 *      Author: Erich Styger
 */

#ifndef REFLECTANCE_H_
#define REFLECTANCE_H_

#include "CLS1.h"
#include "Platform.h"

#if PL_IS_ZUMO_ROBOT
  #define REF_NOF_SENSORS 6
#else
  #define REF_NOF_SENSORS 8
#endif

typedef enum {
  REF_LINE_NONE,     /* no line, sensors do not see a line */
  REF_LINE_FORWARD,  /* forward line |, sensors see a line underneath */
  REF_LINE_LEFT,     /* turn to left -|, left sensors line */
  REF_LINE_RIGHT,    /* turn to right |-, right sensors on a line */
  REF_LINE_FULL,     /* all sensors see a line -|- */
  REF_LINE_AIR       /* all sensors have a timout value. Robot is not on ground at all? */
} REF_LineKind;

REF_LineKind REF_GetLineKind(void);

unsigned char *LF_LineKindStr(REF_LineKind line);

byte REF_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void REF_Measure(void);

#define REF_MAX_LINE_VALUE  ((REF_NOF_SENSORS-1)*1000) /* maximum value for REF_GetLine() */
uint16_t REF_GetLineValue(bool *onLine);

void REF_Calibrate(bool on);

bool REF_CanUseSensor(void);

bool REF_IsCalibrating(void);

void REF_Init(void);

#endif /* REFLECTANCE_H_ */
