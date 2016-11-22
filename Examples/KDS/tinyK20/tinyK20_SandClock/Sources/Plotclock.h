/*
 * Plotclock.h
 *
 *  Created on: 15.10.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_PLOTCLOCK_H_
#define SOURCES_PLOTCLOCK_H_

/*!
 * \brief Main clock routine. Has to be called multiple times every minute. If the minute counter changes, writes the new time.
 */
void PlotClock_Loop(void);

/*!
 * \brief Setup the clock and initializes the servos. As using interrupts, this has to be called when interrupts are enabled (e.g. from a task context).
 */
void PlotClock_Setup(void);

#include "CLS1.h"
uint8_t PlotClock_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);


/*!
 * \brief Initialization routine
 */
void PLOTCLOCK_Init(void);

#endif /* SOURCES_PLOTCLOCK_H_ */
