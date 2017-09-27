/*
 * Sumo.h
 *
 *  Created on: Aug 30, 2013
 *      Author: Erich Styger
 */

#ifndef SUMO_H_
#define SUMO_H_

#include "Platform.h"

void SUMO_StartTurnLeft(void);
void SUMO_StartTurnRight(void);

void SUMO_RadarOn(void);

void SUMO_RadarOff(void);

bool SUMO_IsDoingSumo(void);

void SUMO_StartCountdown(void);

void SUMO_StartSumo(void);

void SUMO_StopSumo(void);

void SUMO_StartStopSumo(void);

#if PL_CONFIG_HAS_SHELL
#include "CLS1.h"
  uint8_t SUMO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

void SUMO_Init(void);

#endif /* SUMO_H_ */
