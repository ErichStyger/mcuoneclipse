/*
 * SensorTasks.h
 *
 *  Created on: 12.10.2015
 *      Author: tastyger
 */

#ifndef SOURCES_FUSION_SENSORTASKS_H_
#define SOURCES_FUSION_SENSORTASKS_H_

#include "types.h"
#include "build.h"

extern struct ProjectGlobals globals;

extern uint8 sUARTOutputBuffer[];
extern uint8 sUART_A_InputBuffer[];
extern uint8 sUART_B_InputBuffer[];
extern struct PressureSensor thisPressure;
extern struct AccelSensor thisAccel;
extern struct MagSensor thisMag;
extern struct GyroSensor thisGyro;
extern struct MagCalibration thisMagCal;
extern struct MagneticBuffer thisMagBuffer;

extern struct SV_1DOF_P_BASIC thisSV_1DOF_P_BASIC;
extern struct SV_3DOF_G_BASIC thisSV_3DOF_G_BASIC;
extern struct SV_3DOF_B_BASIC thisSV_3DOF_B_BASIC;
extern struct SV_3DOF_Y_BASIC thisSV_3DOF_Y_BASIC;
extern struct SV_6DOF_GB_BASIC thisSV_6DOF_GB_BASIC;
extern struct SV_6DOF_GY_KALMAN thisSV_6DOF_GY_KALMAN;
extern struct SV_9DOF_GBY_KALMAN thisSV_9DOF_GBY_KALMAN;

#define _mem_alloc_zero                 _lwmem_alloc_zero


void SensorTasks_Init(void);


#endif /* SOURCES_FUSION_SENSORTASKS_H_ */
