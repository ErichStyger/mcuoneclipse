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
// This file contains build controls for a sensor fusion project.
// Board and MCU customization is done via Processor Expert.  The fusion
// code sits above that software layer, and can usually be ported from
// one board environment to another with no changes.

#ifndef BUILD_H
#define BUILD_H

// Kinetis processor base boards: 5 bit code 0 to 31 inclusive transmitted in bits 4-0
#define RESERVED0     		0
#define FRDM_KL25Z     		1
#define FRDM_K20D50M   		2
#define SPARE0		    	3
#define FRDM_KL26Z    		4
#define FRDM_K64F	   		5
#define SPARE1			  	6
#define FRDM_KL46Z  		7
#define SPARE2				8
#define FRDM_K22F			9
#define SPARE3				10
#define FRDM_KL05Z     		11
#define SPARE4				12
#define FRDM_KL02Z     		13
#define FRDM_KE02Z     		14
#define FRDM_KE06Z     		15
// spare 16 to 31 inclusive

// define PCBs: only used i) to detect invalid build and ii) specify rotating PCB graphic and iii) clock rates
#ifdef KL25Z
#define THIS_KINETIS       	FRDM_KL25Z
#define FTM_INCLK_HZ		1000000	
#endif
#ifdef K20D50M
#define THIS_KINETIS		FRDM_K20D50M
#define FTM_INCLK_HZ		1000000
#endif
#ifdef KL26Z
#define THIS_KINETIS		FRDM_KL26Z
#define FTM_INCLK_HZ		1000000
#endif
#ifdef K64F
#define THIS_KINETIS		FRDM_K64F
#define FTM_INCLK_HZ		1000000
#endif
#ifdef KL46Z
#define THIS_KINETIS		FRDM_KL46Z
#define FTM_INCLK_HZ		1000000
#endif
#ifdef K22F
#define THIS_KINETIS		FRDM_K22F
#define FTM_INCLK_HZ		1000000
#endif

// shield boards: 3 bit code 0 to 7 inclusive transmitted in bits 7-5
#define SHIELD_MULTIB		0
#define SHIELD_NONE			1
#define SHIELD_AGM01		2
#define SHIELD_AGM02		3
#define THIS_SHIELD			SHIELD_MULTIB
// spare 5 to 7 inclusive

// coordinate system for the build
#define NED 0                       // identifier for NED (Aerospace) axes and angles
#define ANDROID 1                   // identifier for Android axes and angles
#define WIN8 2						// identifier for Windows 8 axes and angles
#define THISCOORDSYSTEM NED			// the coordinate system to be used

// sensors to be enabled: compile errors will warn if the selected sensors are inadequate for the algorithms.
// avoid enabling duplicate sensor types (eg FXOS8700 plus MMA8652 or FXOS8700 plus MAG3110).
// this will still work but the accelerometer or magnetometer data will be read twice over from different sensors.
#define USE_MPL3115
#define USE_FXOS8700
#define USE_FXAS2100X
//#define USE_MMA8652
//#define USE_MAG3110
//#define USE_FXLS8952

// enforce a fatal compilation error for invalid builds
// FRDM_K20D50M has MMA8451 only at I2C address 0x1D and MULTI(-B) has MMA8652 at address 0x1D
#if (THIS_KINETIS == FRDM_K20D50M) && (THIS_SHIELD == SHIELD_MULTIB) && defined USE_MMA8652
#error The K20D50M Freedom board has one I2C bus creating address conflict between MMA8451 and MMA8652
#endif

// normally all enabled: degrees of freedom algorithms to be executed
#define COMPUTE_1DOF_P_BASIC		// 1DOF pressure (altitude) and temperature: (pressure)
#define COMPUTE_3DOF_G_BASIC		// 3DOF accel tilt: (accel)
#define COMPUTE_3DOF_B_BASIC		// 3DOF mag eCompass (vehicle): (mag)
#define COMPUTE_3DOF_Y_BASIC		// 3DOF gyro integration: (gyro)
#define COMPUTE_6DOF_GB_BASIC		// 6DOF accel and mag eCompass: (accel + mag)
#define COMPUTE_6DOF_GY_KALMAN		// 6DOF accel and gyro (Kalman): (accel + gyro)
#define COMPUTE_9DOF_GBY_KALMAN		// 9DOF accel, mag and gyro (Kalman): (accel + mag + gyro)

// int16 build number sent in debug packet
#define THISBUILD  500

// sampling rate and kalman filter timing eg (25, 1), (200, 8), (400, 16), (500, 20), (600, 24), (800, 32)
// the MULTI-(B) 9-AXIS and AGM01 boards are able to sample the gyro sensor at 800Hz with Kalman filter rates depending
// on the processor speed and number of algorithms executing in parallel.
#define SENSORFS 			200         // int32: frequency (Hz) of gyro sensor sampling process
#define OVERSAMPLE_RATIO 	8			// int32: accel and mag sampling and algorithms run at SENSORFS / OVERSAMPLE_RATIO Hz

#endif // BUILD_H
