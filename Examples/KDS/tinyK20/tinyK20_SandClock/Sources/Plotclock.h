/*
 * Plotclock.h
 *
 *  Created on: 15.10.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_PLOTCLOCK_H_
#define SOURCES_PLOTCLOCK_H_

void PlotClock_Loop(void);

void PlotClock_Setup(void);

#include "CLS1.h"
uint8_t PlotClock_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);


#endif /* SOURCES_PLOTCLOCK_H_ */
