// Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#ifndef TYPES_H
#define TYPES_H

//#include "MQX1.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "build.h"

// these definition re-define (but with no changes) those in MQX-Lite PE-Types.h for Kinetis
typedef signed char				int8;
typedef unsigned char			uint8;
typedef signed short int		int16;
typedef unsigned short int		uint16;
typedef signed long int			int32;
typedef unsigned long int		uint32;

// the quaternion type to be transmitted
typedef enum quaternion {Q3, Q3M, Q3G, Q6MA, Q6AG, Q9} quaternion_type;

// vector components
#define CHX 0
#define CHY 1
#define CHZ 2

// booleans
#define true 1
#define false 0

// useful multiplicative conversion constants
#define PI 3.141592654F					// Pi
#define FPIOVER180 0.01745329251994F	// degrees to radians conversion = pi / 180
#define F180OVERPI 57.2957795130823F	// radians to degrees conversion = 180 / pi
#define F180OVERPISQ 3282.8063500117F	// square of F180OVERPI
#define ONETHIRD 0.33333333F			// one third
#define ONESIXTH 0.166666667F			// one sixth
#define ONEOVER48 0.02083333333F		// 1 / 48
#define ONEOVER120 0.0083333333F		// 1 / 120
#define ONEOVER3840 0.0002604166667F	// 1 / 3840
#define ONEOVERSQRT2 0.707106781F		// 1/sqrt(2)
#define GTOMSEC2 9.80665				// standard gravity in m/s2

// project globals structure
struct ProjectGlobals
{
	volatile quaternion_type QuaternionPacketType;	// quaternion transmitted over UART
	quaternion_type DefaultQuaternionPacketType;	// default quaternion transmitted at power on
#if 0
	LWEVENT_STRUCT SamplingEventStruct;				// MQX-Lite hardware timer event
	LWEVENT_STRUCT RunKFEventStruct;				// MQX-Lite kalman filter sensor fusion event
	LWEVENT_STRUCT MagCalEventStruct;				// MQX-Lite magnetic calibration event
#else
	SemaphoreHandle_t SamplingEventSem;
	SemaphoreHandle_t RunKFEventSem;
	SemaphoreHandle_t MagCalEventSem;
#endif
	int32 loopcounter;								// counter incrementing each iteration of sensor fusion (typically 25Hz)
	volatile uint8 AngularVelocityPacketOn;			// flag to transmit angular velocity packet
	volatile uint8 DebugPacketOn;					// flag to transmit debug packet
	volatile uint8 RPCPacketOn;						// flag to transmit roll, pitch, compass packet
	volatile uint8 AltPacketOn;						// flag to transmit altitude packet
};

// quaternion structure definition
struct fquaternion
{
	float q0;	// scalar component
	float q1;	// x vector component
	float q2;	// y vector component
	float q3;	// z vector component
};

// gyro sensor structure definition
struct PressureSensor
{
	int32 iH;				// most recent unaveraged height (counts)
	int32 iP;				// most recent unaveraged pressure (counts)
	float fH;				// most recent unaveraged height (m)
	float fT;				// most recent unaveraged temperature (C)
	float fmPerCount;		// meters per count
	float fCPerCount;		// degrees Celsius per count
	int16 iT;				// most recent unaveraged temperature (counts)
	uint8 iWhoAmI;			// sensor whoami
};
	
// accelerometer sensor structure definition
struct AccelSensor
{
	float fGsAvg[3];						// averaged measurement (g)
	float fgPerCount;						// g per count
	int16 iGsBuffer[OVERSAMPLE_RATIO][3];	// buffered measurements (counts)
	int16 iGs[3];							// most recent unaveraged measurement (counts)
	int16 iGsAvg[3];						// averaged measurement (counts)
	int16 iCountsPerg;						// counts per g
	uint8 iWhoAmI;							// sensor whoami
};

// magnetometer sensor structure definition
struct MagSensor
{
	float fBsAvg[3];						// averaged un-calibrated measurement (uT)
	float fBcAvg[3];						// averaged calibrated measurement (uT)
	float fuTPerCount;						// uT per count
	float fCountsPeruT;						// counts per uT
	int16 iBsBuffer[OVERSAMPLE_RATIO][3];	// buffered uncalibrated measurement (counts)
	int16 iBs[3];							// most recent unaveraged uncalibrated measurement (counts)
	int16 iBsAvg[3];						// averaged uncalibrated measurement (counts)
	int16 iBcAvg[3];						// averaged calibrated measurement (counts)
	int16 iCountsPeruT;						// counts per uT
	uint8 iWhoAmI;							// sensor whoami
};

// gyro sensor structure definition
struct GyroSensor
{
	float fDegPerSecPerCount;				// deg/s per count
	int16 iYsBuffer[OVERSAMPLE_RATIO][3];	// buffered sensor frame measurements (counts)
	int16 iCountsPerDegPerSec;				// counts per deg/s
	int16 iYs[3];							// most recent sensor frame measurement (counts)
	uint8 iWhoAmI;							// sensor whoami
};

// 1DOF pressure state vector structure
struct SV_1DOF_P_BASIC
{
	float fLPH;					// low pass filtered height (m)
	float fLPT;					// low pass filtered temperature (C)
	float fdeltat;				// time interval (s)	
	float flpf;					// low pass filter coefficient
	int32 systick;				// systick timer
	int8 resetflag;				// flag to request re-initialization on next pass
};

// 3DOF basic accelerometer state vector structure
struct SV_3DOF_G_BASIC
{
	// start: elements common to all motion state vectors
	float fLPPhi;					// low pass roll (deg)
	float fLPThe;					// low pass pitch (deg)
	float fLPPsi;					// low pass yaw (deg)
	float fLPRho;					// low pass compass (deg)
	float fLPChi;					// low pass tilt from vertical (deg)
	float fLPR[3][3];				// low pass filtered orientation matrix
	struct fquaternion fLPq;		// low pass filtered orientation quaternion
	float fLPRVec[3];				// rotation vector
	float fOmega[3];				// angular velocity (deg/s)
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];					// unfiltered orientation matrix
	struct fquaternion fq;			// unfiltered orientation quaternion
	float fdeltat;					// time interval (s)
	float flpf;						// low pass filter coefficient
	int8 resetflag;					// flag to request re-initialization on next pass
};

// 3DOF basic magnetometer state vector structure
struct SV_3DOF_B_BASIC
{
	// start: elements common to all motion state vectors
	float fLPPhi;						// low pass roll (deg)
	float fLPThe;						// low pass pitch (deg)
	float fLPPsi;						// low pass yaw (deg)
	float fLPRho;						// low pass compass (deg)
	float fLPChi;						// low pass tilt from vertical (deg)
	float fLPR[3][3];					// low pass filtered orientation matrix
	struct fquaternion fLPq;			// low pass filtered orientation quaternion
	float fLPRVec[3];					// rotation vector
	float fOmega[3];					// angular velocity (deg/s)
	int32 systick;						// systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];						// unfiltered orientation matrix
	struct fquaternion fq;				// unfiltered orientation quaternion
	float fdeltat;						// time interval (s)
	float flpf;							// low pass filter coefficient
	int8 resetflag;						// flag to request re-initialization on next pass
};

// 3DOF basic gyroscope state vector structure
struct SV_3DOF_Y_BASIC
{
	// start: elements common to all motion state vectors
	float fPhi;						// roll (deg)
	float fThe;						// pitch (deg)
	float fPsi;						// yaw (deg)
	float fRho;						// compass (deg)
	float fChi;						// tilt from vertical (deg)
	float fR[3][3];					// unfiltered orientation matrix
	struct fquaternion fq;			// unfiltered orientation quaternion
	float fRVec[3];					// rotation vector
	float fOmega[3];				// angular velocity (deg/s)
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	float fGyrodeltat;				// gyro sensor sampling interval (s) = 1 / SENSORFS
	float fdeltat;					// kalman filter sampling interval (s) = OVERSAMPLE_RATIO / SENSORFS
	int8 resetflag;					// flag to request re-initialization on next pass
};

// 6DOF basic accelerometer and magnetometer state vector structure
struct SV_6DOF_GB_BASIC
{
	// start: elements common to all motion state vectors
	float fLPPhi;					// low pass roll (deg)
	float fLPThe;					// low pass pitch (deg)
	float fLPPsi;					// low pass yaw (deg)
	float fLPRho;					// low pass compass (deg)
	float fLPChi;					// low pass tilt from vertical (deg)
	float fLPR[3][3];				// low pass filtered orientation matrix
	struct fquaternion fLPq;		// low pass filtered orientation quaternion
	float fLPRVec[3];				// rotation vector
	float fOmega[3];				// virtual gyro angular velocity (deg/s)
	int32 systick;					// systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];					// unfiltered orientation matrix
	struct fquaternion fq;			// unfiltered orientation quaternion
	float fDelta;					// unfiltered inclination angle (deg)
	float fLPDelta;					// low pass filtered inclination angle (deg)
	float fdeltat;					// time interval (s)
	float flpf;						// low pass filter coefficient
	int8 resetflag;					// flag to request re-initialization on next pass
};

// 6DOF Kalman filter accelerometer and gyroscope state vector structure
struct SV_6DOF_GY_KALMAN
{
	// start: elements common to all motion state vectors
	float fPhiPl;						// roll (deg)
	float fThePl;						// pitch (deg)
	float fPsiPl;						// yaw (deg)
	float fRhoPl;						// compass (deg)
	float fChiPl;						// tilt from vertical (deg)
	float fRPl[3][3];					// a posteriori orientation matrix
	struct fquaternion fqPl;			// a posteriori orientation quaternion
	float fRVecPl[3];					// rotation vector
	float fOmega[3];					// average angular velocity (deg/s)
	int32 systick;						// systick timer;
	// end: elements common to all motion state vectors
	float fQw6x6[6][6];					// covariance matrix Qw
	float fK6x3[6][3];					// kalman filter gain matrix K
	float fQwCT6x3[6][3];				// Qw.C^T matrix
	float fQv;							// measurement noise covariance matrix leading diagonal
	float fZErr[3];						// measurement error vector
	float fqgErrPl[3];					// gravity vector tilt orientation quaternion error (dimensionless)
	float fbPl[3];						// gyro offset (deg/s)
	float fbErrPl[3];					// gyro offset error (deg/s)
	float fAccGl[3];					// linear acceleration (g) in global frame
	float fGyrodeltat;					// gyro sampling interval (s) = 1 / SENSORFS
	float fAlphaOver2;					// PI/360 * fKalmandeltat
	float fAlphaOver2Sq;				// (PI/360 * fKalmandeltat)^2
	float fAlphaOver2SqQvYQwb;			// (PI/360 * fKalmandeltat)^2 * (QvY + Qwb)
	float fAlphaOver2Qwb;				// PI/360 * fKalmandeltat * FQWB_9DOF_GBY_KALMAN;
	int8 resetflag;						// flag to request re-initialization on next pass
}; 

// 9DOF Kalman filter accelerometer, magnetometer and gyroscope state vector structure
struct SV_9DOF_GBY_KALMAN
{
	// start: elements common to all motion state vectors
	float fPhiPl;						// roll (deg)
	float fThePl;						// pitch (deg)
	float fPsiPl;						// yaw (deg)
	float fRhoPl;						// compass (deg)
	float fChiPl;						// tilt from vertical (deg)
	float fRPl[3][3];					// a posteriori orientation matrix
	struct fquaternion fqPl;			// a posteriori orientation quaternion
	float fRVecPl[3];					// rotation vector
	float fOmega[3];					// average angular velocity (deg/s)
	int32 systick;						// systick timer;
	// end: elements common to all motion state vectors
	float fQw10x10[10][10];				// covariance matrix Qw
	float fK10x7[10][7];				// kalman filter gain matrix K
	float fQwCT10x7[10][7];				// Qw.C^T matrix
	float fZErr[7];						// measurement error vector
	float fQv7x1[7];					// measurement noise covariance matrix leading diagonal
	float fDeltaPl;						// a posteriori inclination angle from Kalman filter (deg)
	float fsinDeltaPl;					// sin(fDeltaPl)
	float fcosDeltaPl;					// cos(fDeltaPl)
	float fqgErrPl[3];					// gravity vector tilt orientation quaternion error (dimensionless)
	float fqmErrPl[3];					// geomagnetic vector tilt orientation quaternion error (dimensionless)
	float fbPl[3];						// gyro offset (deg/s)
	float fbErrPl[3];					// gyro offset error (deg/s)
	float fDeltaErrPl;					// a priori inclination angle error correction
	float fAccGl[3];					// linear acceleration (g) in global frame
	float fVelGl[3];					// velocity (m/s) in global frame
	float fDisGl[3];					// displacement (m) in global frame	
	float fGyrodeltat;					// gyro sampling interval (s) = 1 / SENSORFS
	float fKalmandeltat;				// Kalman filter interval (s) = OVERSAMPLE_RATIO / SENSORFS	
	float fgKalmandeltat;				// g (m/s2) * Kalman filter interval (s) = 9.80665 * OVERSAMPLE_RATIO / SENSORFS	
	float fAlphaOver2;					// PI/360 * fKalmandeltat
	float fAlphaOver2Sq;				// (PI/360 * fKalmandeltat)^2
	float fAlphaOver2SqQvYQwb;			// (PI/360 * fKalmandeltat)^2 * (QvY + Qwb)
	float fAlphaOver2Qwb;				// PI/360 * fKalmandeltat * FQWB_9DOF_GBY_KALMAN;
	int8 iFirstAccelMagLock;			// denotes that 9DOF orientation has locked to 6DOF eCompass
	int8 resetflag;						// flag to request re-initialization on next pass
}; 

#endif // TYPES_H
