/*
 * Plotclock.h
 *
 *  Created on: 15.10.2016
 *      Author: Erich Styger Local
 */

#ifndef SOURCES_PLOTCLOCK_H_
#define SOURCES_PLOTCLOCK_H_


void lift(char lift);
void drawTo(double pX, double pY);
void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee);
void set_XY(double Tx, double Ty);
void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee);

void PlotClock_Loop(void);

#include "CLS1.h"
uint8_t PlotClock_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);


#endif /* SOURCES_PLOTCLOCK_H_ */
