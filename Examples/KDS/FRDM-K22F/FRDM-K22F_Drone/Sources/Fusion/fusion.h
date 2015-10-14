// Copyright (c) 2014, 2015, Freescale Semiconductor, Inc.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Freescale Semiconductor, Inc. nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL FREESCALE SEMICONDUCTOR, INC. BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#ifndef FUSION_H
#define FUSION_H

#include "SensorTasks.h"

// *********************************************************************************
// COMPUTE_6DOF_GY_KALMAN constants
// *********************************************************************************

// gyro sensor noise covariance units deg^2
#define FQVY_6DOF_GY_KALMAN			1E4F
// gyro offset random walk units (deg/s)^2
#define FQWB_6DOF_GY_KALMAN			5E-1F

// *********************************************************************************
// COMPUTE_9DOF_GBY_KALMAN constants
// *********************************************************************************

// gyro sensor noise covariance units deg^2
#define FQVY_9DOF_GBY_KALMAN		1E4F 
// gyro offset random walk units (deg/s)^2
#define FQWB_9DOF_GBY_KALMAN		5E-1F			
// geomagnetic inclination angle random walk units deg/s
#define FQWDLT_9DOF_GBY_KALMAN		2E1F
// minimum magnetometer and magnetic disturbance
#define FQVBQD_MIN_9DOF_GBY_KALMAN	7E0F
// minimum and maximum gyro offset in deg/s
#define FGYRO_OFFSET_MIN_9DOF_GBY_KALMAN	-5.0F
#define FGYRO_OFFSET_MAX_9DOF_GBY_KALMAN	5.0F

// *********************************************************************************
// function prototypes
// *********************************************************************************
void fInitFusion(void);
void fInit_1DOF_P_BASIC(struct SV_1DOF_P_BASIC *pthisSV, struct PressureSensor *pthisPressure,  float flpftimesecs);
void fInit_3DOF_G_BASIC(struct SV_3DOF_G_BASIC *pthisSV, struct AccelSensor *pthisAccel, float flpftimesecs);
void fInit_3DOF_B_BASIC(struct SV_3DOF_B_BASIC *pthisSV, struct MagSensor *pthisMag, float flpftimesecs);
void fInit_3DOF_Y_BASIC(struct SV_3DOF_Y_BASIC *pthisSV);
void fInit_6DOF_GB_BASIC(struct SV_6DOF_GB_BASIC *pthisSV, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag, float flpftimesecs);
void fInit_6DOF_GY_KALMAN(struct SV_6DOF_GY_KALMAN *pthisSV, struct AccelSensor *pthisAccel);
void fInit_9DOF_GBY_KALMAN(struct SV_9DOF_GBY_KALMAN *pthisSV, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag,
		struct MagCalibration *pthisMagCal);
void fRun_1DOF_P_BASIC(struct SV_1DOF_P_BASIC *pthisSV, struct PressureSensor *pthisPressure);
void fRun_3DOF_G_BASIC(struct SV_3DOF_G_BASIC *pthisSV, struct AccelSensor *pthisAccel);
void fRun_3DOF_B_BASIC(struct SV_3DOF_B_BASIC *pthisSV, struct MagSensor *pthisMag);
void fRun_3DOF_Y_BASIC(struct SV_3DOF_Y_BASIC *pthisSV, struct GyroSensor *pthisGyro);
void fRun_6DOF_GB_BASIC(struct SV_6DOF_GB_BASIC *pthisSV, struct MagSensor *pthisMag, struct AccelSensor *pthisAccel);
void fRun_6DOF_GY_KALMAN(struct SV_6DOF_GY_KALMAN *pthisSV, struct AccelSensor *pthisAccel, struct GyroSensor *pthisGyro);
void fRun_9DOF_GBY_KALMAN(struct SV_9DOF_GBY_KALMAN *pthisSV, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag, struct GyroSensor *pthisGyro, struct MagCalibration *pthisMagCal);

#endif   // #ifndef FUSION_H
