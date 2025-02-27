/*
 * ctimer.h
 *
 * Created on: 24 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#ifndef __C_TIMERS___
#define __C_TIMERS___

void init_MeasurementTimer(void);
void init_TriggerCommandTimer(void);

void MeasurementTimer_start(void);
void MeasurementTimer_stop(void);

#endif /* __C_TIMERS___ */
