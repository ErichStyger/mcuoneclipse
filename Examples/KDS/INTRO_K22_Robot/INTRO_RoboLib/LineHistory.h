/*
 * LineHistory.h
 *
 *  Created on: 30.08.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_INTRO_ROBOLIB_LINEHISTORY_H_
#define SOURCES_INTRO_ROBOLIB_LINEHISTORY_H_

#include "Reflectance.h"
#if PL_HAS_LINE_SENSOR
void HISTORY_SampleSensors(void);

/*!
 * \brief Can be called during turning, will use it to sample sensor values.
 */
bool HISTORY_SampleTurnStopFunction(void);

REF_LineKind HISTORY_LineKind(void);

void HISTORY_Clear(void);
#endif /* PL_HAS_LINE_SENSOR */

#endif /* SOURCES_INTRO_ROBOLIB_LINEHISTORY_H_ */
