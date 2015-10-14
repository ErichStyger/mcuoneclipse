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
// This file defines real-time tasks required by the sensor fusion application.
// These are:
// * main task (one time startup)
// * sampling task (200 Hz nominal)
// * sensor fusion task (25Hz nominal)
// * magnetic calibration (background)
// These functions are intertwined with MQXLITE.  If you change RTOSs, you will have
// to rework this file.
//
#include <stdio.h>
#include <stdlib.h>

#include "Cpu.h"
#include "Events.h"
#include "SensorTasks.h"
#include "Init_Config.h"
#include "PDD_Includes.h"
#include "LED1.h" //"LED_RED.h"
#include "LED2.h" //"LED_GREEN.h"
#include "I2C.h"
#include "FTM.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "types.h"
#include "fusion.h"
#include "magnetic.h"
#include "drivers.h"
#include "user_tasks.h"
#include "FreeRTOS.h"

#define ENABLED_MQX  0

// global structures
struct ProjectGlobals globals;

// sensor data structures
#if defined USE_MPL3115
struct PressureSensor thisPressure;		// this pressure sensor
#endif
#if defined USE_FXOS8700 || defined USE_MMA8652 || defined USE_FXLS8952
struct AccelSensor thisAccel;			// this accelerometer
#endif
#if defined USE_FXOS8700 || defined USE_MAG3110
struct MagSensor thisMag;				// this magnetometer
struct MagCalibration thisMagCal;		// hard and soft iron magnetic calibration
struct MagneticBuffer thisMagBuffer;	// magnetometer measurement buffer
#endif
#if defined USE_FXAS2100X
struct GyroSensor thisGyro;				// this gyro
#endif
// 1DOF pressure structure
#if defined COMPUTE_1DOF_P_BASIC
struct SV_1DOF_P_BASIC thisSV_1DOF_P_BASIC;
#endif
// 3DOF accelerometer (Basic) structure
#if defined COMPUTE_3DOF_G_BASIC
struct SV_3DOF_G_BASIC thisSV_3DOF_G_BASIC;
#endif
// 3DOF magnetometer (Basic) structure
#if defined COMPUTE_3DOF_B_BASIC
struct SV_3DOF_B_BASIC thisSV_3DOF_B_BASIC;
#endif
// 3DOF gyro (Basic) structure
#if defined COMPUTE_3DOF_Y_BASIC
struct SV_3DOF_Y_BASIC thisSV_3DOF_Y_BASIC;
#endif
// 6DOF accelerometer and magnetometer (Basic) structure
#if defined COMPUTE_6DOF_GB_BASIC
struct SV_6DOF_GB_BASIC thisSV_6DOF_GB_BASIC;
#endif
// 6DOF accelerometer and gyro (Kalman) structure
#if defined COMPUTE_6DOF_GY_KALMAN
struct SV_6DOF_GY_KALMAN thisSV_6DOF_GY_KALMAN;
#endif
// 9DOF accelerometer, magnetometer and gyro (Kalman) structure
#if defined COMPUTE_9DOF_GBY_KALMAN
struct SV_9DOF_GBY_KALMAN thisSV_9DOF_GBY_KALMAN;
#endif

// sensor read task: this is interrupted by hardware callbacks (UART etc) but never by fusion or magnetic calibration
void RdSensData_task(uint32_t task_init_data)
{
	int32 iSum[3];					// array of sums
	int32 itmp;						// scratch
	static int8 iCounter = 0;		// decimation counter range 0 to OVERSAMPLE_RATIO-1
	int8 i, j, k, l;				// counters

#if ENABLED_MQX
	// create the sensor fusion task (controlled by sensor fusion event RunKFEventStruct)
	_task_create_at(0, FUSION_TASK, 0, Fusion_task_stack, FUSION_TASK_STACK_SIZE);
	// create the magnetic calibration task (controlled by MagCalEventStruct)
	_task_create_at(0, MAGCAL_TASK, 0, MagCal_task_stack, MAGCAL_TASK_STACK_SIZE);

	// create the sensor sampling event (typically 200Hz)
	_lwevent_create(&(globals.SamplingEventStruct), LWEVENT_AUTO_CLEAR);
	// create the Kalman filter sensor fusion event (typically 25Hz)
	_lwevent_create(&(globals.RunKFEventStruct), LWEVENT_AUTO_CLEAR);
	// create the magnetic calibration event (typically once per minute)
	_lwevent_create(&(globals.MagCalEventStruct), LWEVENT_AUTO_CLEAR);
#endif
	// reset the sensor sampling interrupt timer and set period (typically to 200Hz) over-writing Processor Expert value
	FTM_SetPeriodTicks(FTM_DeviceData, (uint16) (FTM_INCLK_HZ / SENSORFS));

	// initialize globals
	globals.AngularVelocityPacketOn = true;
	globals.DebugPacketOn = true;
	globals.RPCPacketOn = true;
	globals.AltPacketOn = true;

	// application-specific startup
	UserStartup();

	// initialize the physical sensors over I2C and hang on error to keep the red LED illuminated
	// with exception of MPL3115 (so as to support 9AXIS board option which doesn't populate MPL3115)
	LED1_On();		// red on
	LED2_Off();		// green off

#if defined USE_MPL3115
	MPL3115_Init(I2C_DeviceData, &thisPressure);
#endif
#if defined USE_FXOS8700
	while (!FXOS8700_Init(I2C_DeviceData, &thisAccel, &thisMag));
#endif
#if defined USE_FXAS2100X
	while (!FXAS2100X_Init(I2C_DeviceData, &thisGyro));
#endif
#if defined USE_MMA8652
	while (!MMA8652_Init(I2C_DeviceData, &thisAccel));
#endif
#if defined USE_FXLS8952
	while (!FXLS8952_Init(I2C_DeviceData, &thisAccel));
#endif
#if defined USE_MAG3110
	while (!MAG3110_Init(I2C_DeviceData, &thisMag));
#endif

	// initialize magnetometer data structure
#if defined COMPUTE_3DOF_B_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_9DOF_GBY_KALMAN
	// zero the calibrated measurement since this is used for indexing the magnetic buffer even before first calibration
	for (i = CHX; i <= CHZ; i++)
		thisMag.iBcAvg[i]= 0;
#endif

	// set red LED off now all required sensors are detected
	LED1_Off();

#if ENABLED_MQX
	// initialize user high frequency (typically 200Hz) task
	UserHighFrequencyTaskInit();
#endif

	// infinite loop controlled by hardware timer (typically 200Hz) with iCounter in range 0 to OVERSAMPLE_RATIO-1
	while(1)
	{
		// wait here for the sensor sampling event from the hardware timer
		// the sensor fusion and magnetic calibration tasks execute while this task is blocked here
		// FALSE means any bit (of the 1 bit enabled by the mask) unblocks and NULL means infinite timeout
#if ENABLED_MQX
		_lwevent_wait_for(&(globals.SamplingEventStruct), 1, FALSE, NULL);
#else
    FRTOS1_xSemaphoreTake(globals.SamplingEventSem, portMAX_DELAY);
#endif
		// read and process accelerometer sensor in every slot if present if accelerometer algorithm is in use.
#if defined COMPUTE_3DOF_G_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_6DOF_GY_KALMAN || defined COMPUTE_9DOF_GBY_KALMAN
#if defined USE_FXOS8700
		FXOS8700_ReadAccData(I2C_DeviceData, &thisAccel);
#endif
#if defined USE_MMA8652
		MMA8652_ReadData(I2C_DeviceData, &thisAccel);
#endif
#if defined USE_FXLS8952
		FXLS8952_ReadData(I2C_DeviceData, &thisAccel);
#endif
		// store measurement in a buffer for later end of block processing
		for (i = CHX; i <= CHZ; i++)
			thisAccel.iGsBuffer[iCounter][i] = thisAccel.iGs[i];

		// every OVERSAMPLE_RATIO passes calculate the block averaged measurement
		if (iCounter == (OVERSAMPLE_RATIO - 1))
		{
			// calculate the block averaged measurement in counts and g
			for (i = CHX; i <= CHZ; i++)
			{
				iSum[i] = 0;
				for (j = 0; j < OVERSAMPLE_RATIO; j++)
					iSum[i] += (int32)thisAccel.iGsBuffer[j][i];
				// compute the average with nearest integer rounding
				if (iSum[i] >= 0)
					thisAccel.iGsAvg[i] = (int16)((iSum[i] + (OVERSAMPLE_RATIO >> 1)) / OVERSAMPLE_RATIO);
				else
					thisAccel.iGsAvg[i] = (int16)((iSum[i] - (OVERSAMPLE_RATIO >> 1)) / OVERSAMPLE_RATIO);
				// convert from integer counts to float g
				thisAccel.fGsAvg[i] = (float)thisAccel.iGsAvg[i] * thisAccel.fgPerCount;
			}
		} // end of test for end of OVERSAMPLE_RATIO block
#endif // end of check for accelerometer algorithm and sensor

		// read and process the magnetometer sensor in every slot if magnetic algorithm is in use.
#if defined COMPUTE_3DOF_B_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_9DOF_GBY_KALMAN
#if defined USE_FXOS8700
		FXOS8700_ReadMagData(I2C_DeviceData, &thisMag);
#endif
#if defined USE_MAG3110
		MAG3110_ReadData(I2C_DeviceData, &thisMag);
#endif
		// store in a buffer for later end of block processing
		for (i = CHX; i <= CHZ; i++)
			thisMag.iBsBuffer[iCounter][i] = thisMag.iBs[i];

		// update magnetic buffer with iBs avoiding a write to the shared structure while a calibration is in progress.
		if (!thisMagCal.iCalInProgress)
			iUpdateMagnetometerBuffer(&thisMagBuffer, &thisMag, globals.loopcounter);

		// every OVERSAMPLE_RATIO passes calculate the block averaged and calibrated measurement using an anti-glitch filter
		// that rejects the measurement furthest from the mean. magnetometer sensors are sensitive
		// to occasional current pulses from power supply traces and so on and this is a simple method to remove these.
		if (iCounter == (OVERSAMPLE_RATIO - 1))
		{
			// calculate the channel means using all measurements
			for (i = CHX; i <= CHZ; i++)
			{
				// accumulate channel sums
				iSum[i] = 0;
				for (j = 0; j < OVERSAMPLE_RATIO; j++)
					iSum[i] += (int32)thisMag.iBsBuffer[j][i];
			}
			// store axis k in buffer measurement l furthest from its mean
			itmp = 0;
			for (i = CHX; i <= CHZ; i++)
			{
				for (j = 0; j < OVERSAMPLE_RATIO; j++)
				{
					if (abs((int32)thisMag.iBsBuffer[j][i] * OVERSAMPLE_RATIO - iSum[i]) >= itmp)
					{
						k = i;
						l = j;
						itmp = abs((int32)thisMag.iBsBuffer[j][i] * OVERSAMPLE_RATIO - iSum[i]);
					}
				}
			}

			// re-calculate the block averaged measurement ignoring channel k in measurement l
			if (OVERSAMPLE_RATIO == 1)
			{
				// use the one available measurement for averaging in this case
				for (i = CHX; i <= CHZ; i++)
				{
					thisMag.iBsAvg[i] = thisMag.iBsBuffer[0][i];
				}
			} // end of compute averages for OVERSAMPLE_RATIO = 1
			else
			{
				// sum all measurements ignoring channel k in measurement l
				for (i = CHX; i <= CHZ; i++)
				{
					iSum[i] = 0;
					for (j = 0; j < OVERSAMPLE_RATIO; j++)
					{
						if (!((i == k) && (j == l)))
							iSum[i] += (int32)thisMag.iBsBuffer[j][i];
					}
				}
				// compute the average with nearest integer rounding
				for (i = CHX; i <= CHZ; i++)
				{
					if (i != k)
					{
						// OVERSAMPLE_RATIO measurements were used
						if (iSum[i] >= 0)
							thisMag.iBsAvg[i] = (int16)((iSum[i] + (OVERSAMPLE_RATIO >> 1)) / OVERSAMPLE_RATIO);
						else
							thisMag.iBsAvg[i] = (int16)((iSum[i] - (OVERSAMPLE_RATIO >> 1)) / OVERSAMPLE_RATIO);
					}
					else
					{
						// OVERSAMPLE_RATIO - 1 measurements were used
						if (iSum[i] >= 0)
							thisMag.iBsAvg[i] = (int16)((iSum[i] + ((OVERSAMPLE_RATIO - 1) >> 1)) / (OVERSAMPLE_RATIO - 1));
						else
							thisMag.iBsAvg[i] = (int16)((iSum[i] - ((OVERSAMPLE_RATIO - 1) >> 1)) / (OVERSAMPLE_RATIO - 1));
					}
				}
			} // end of compute averages for OVERSAMPLE_RATIO = 1

			// convert the averages to float
			for (i = CHX; i <= CHZ; i++)
				thisMag.fBsAvg[i] = (float)thisMag.iBsAvg[i] * thisMag.fuTPerCount;

			// remove hard and soft iron terms from fBsAvg (uT) to get calibrated data fBcAvg (uT), iBc (counts)
			fInvertMagCal(&thisMag, &thisMagCal);

		} // end of test for end of OVERSAMPLE_RATIO block
#endif // end of check for magnetic algorithms and sensor

		// read the gyro sensor every time slot
#if defined COMPUTE_3DOF_Y_BASIC || defined COMPUTE_6DOF_GY_KALMAN || defined COMPUTE_9DOF_GBY_KALMAN
#if defined USE_FXAS2100X
		FXAS2100X_ReadData(I2C_DeviceData, &thisGyro);
#endif
		// store in a buffer for later gyro integration by sensor fusion algorithms
		for (i = CHX; i <= CHZ; i++)
			thisGyro.iYsBuffer[iCounter][i] = thisGyro.iYs[i];
#endif // end of check for gyro algorithm and sensor

		// read pressure only in first iCounter slot giving read at SENSORFS/OVERSAMPLE_RATIO Hz = 25Hz nominal
		// the MPL3115 is set to average 512 internal samples with 512ms ODR but it is read here at (typically) 25Hz
		// to over-sample and allow the low pass filter in the fusion task to smoothly interpolate the measurement.
#if defined USE_MPL3115
		if ((iCounter == 0) && thisPressure.iWhoAmI)
			MPL3115_ReadData(I2C_DeviceData, &thisPressure);
#endif // end of check for pressure sensor

#if ENABLED_MQX
		// run the user high frequency task
		UserHighFrequencyTaskRun();
#endif

		// every OVERSAMPLE_RATIO passes zero the decimation counter and enable the sensor fusion task
		if (iCounter++ == (OVERSAMPLE_RATIO - 1))
		{
			iCounter = 0;
#if ENABLED_MQX
			_lwevent_set(&(globals.RunKFEventStruct), 1);
#else
			FRTOS1_xSemaphoreGive(globals.RunKFEventSem);
#endif
		}
	} // end of infinite loop
}

// sensor fusion task: this is continually interrupted by the high priority sensor read task
static void Fusion_task(void *task_init_data)
{
	uint16 LEDGreenCounter = 0;			// green LED flash counter
	int8 initiatemagcal;				// flag to initiate a new magnetic calibration

	// initialize the sensor fusion algorithms
	fInitFusion();

#if ENABLED_MQX
	// initialize the user medium frequency (typically 25Hz) task
	UserMediumFrequencyTaskInit();
#endif
	// infinite loop controlled by MQX-Lite events
	while(1)
	{
		// wait for the sensor fusion task to be enabled
		// the magnetic calibration task executes while the fusion task is blocked here
#if ENABLED_MQX
		_lwevent_wait_for(&(globals.RunKFEventStruct), 1, FALSE, NULL);
#else
    FRTOS1_xSemaphoreTake(globals.RunKFEventSem, portMAX_DELAY);
#endif
		// flash the green LED to denote the sensor fusion is running
		if (++LEDGreenCounter >= SENSORFS / (4 * OVERSAMPLE_RATIO))
		{
			LED2_Neg();
			LEDGreenCounter = 0;
		}

		// 1DOF Pressure: call the low pass filter algorithm
#if defined COMPUTE_1DOF_P_BASIC
		thisSV_1DOF_P_BASIC.systick = SYST_CVR & 0x00FFFFFF;
		fRun_1DOF_P_BASIC(&thisSV_1DOF_P_BASIC, &thisPressure);
		thisSV_1DOF_P_BASIC.systick -= SYST_CVR & 0x00FFFFFF;
		if (thisSV_1DOF_P_BASIC.systick < 0) thisSV_1DOF_P_BASIC.systick += SYST_RVR;
#endif

		// 3DOF Accel Basic: call the tilt algorithm
#if defined COMPUTE_3DOF_G_BASIC
		thisSV_3DOF_G_BASIC.systick = SYST_CVR & 0x00FFFFFF;
		fRun_3DOF_G_BASIC(&thisSV_3DOF_G_BASIC, &thisAccel);
		thisSV_3DOF_G_BASIC.systick -= SYST_CVR & 0x00FFFFFF;
		if (thisSV_3DOF_G_BASIC.systick < 0) thisSV_3DOF_G_BASIC.systick += SYST_RVR;
#endif

		// 3DOF Magnetometer Basic: call the 2D vehicle compass algorithm
#if defined COMPUTE_3DOF_B_BASIC
		thisSV_3DOF_B_BASIC.systick = SYST_CVR & 0x00FFFFFF;
		fRun_3DOF_B_BASIC(&thisSV_3DOF_B_BASIC, &thisMag);
		thisSV_3DOF_B_BASIC.systick -= SYST_CVR & 0x00FFFFFF;
		if (thisSV_3DOF_B_BASIC.systick < 0) thisSV_3DOF_B_BASIC.systick += SYST_RVR;
#endif

		// 3DOF Gyro Basic: call the gyro integration algorithm
#if defined COMPUTE_3DOF_Y_BASIC
		thisSV_3DOF_Y_BASIC.systick = SYST_CVR & 0x00FFFFFF;
		fRun_3DOF_Y_BASIC(&thisSV_3DOF_Y_BASIC, &thisGyro);
		thisSV_3DOF_Y_BASIC.systick -= SYST_CVR & 0x00FFFFFF;
		if (thisSV_3DOF_Y_BASIC.systick < 0) thisSV_3DOF_Y_BASIC.systick += SYST_RVR;
#endif

		// 6DOF Accel / Mag: Basic: call the eCompass orientation algorithm
#if defined COMPUTE_6DOF_GB_BASIC
		thisSV_6DOF_GB_BASIC.systick = SYST_CVR & 0x00FFFFFF;
		fRun_6DOF_GB_BASIC(&thisSV_6DOF_GB_BASIC, &thisMag, &thisAccel);
		thisSV_6DOF_GB_BASIC.systick -= SYST_CVR & 0x00FFFFFF;
		if (thisSV_6DOF_GB_BASIC.systick < 0) thisSV_6DOF_GB_BASIC.systick += SYST_RVR;
#endif

		// 6DOF Accel / Gyro: call the Kalman filter orientation algorithm
#if defined COMPUTE_6DOF_GY_KALMAN
		thisSV_6DOF_GY_KALMAN.systick = SYST_CVR & 0x00FFFFFF;
		fRun_6DOF_GY_KALMAN(&thisSV_6DOF_GY_KALMAN, &thisAccel, &thisGyro);
		thisSV_6DOF_GY_KALMAN.systick -= SYST_CVR & 0x00FFFFFF;
		if (thisSV_6DOF_GY_KALMAN.systick < 0) thisSV_6DOF_GY_KALMAN.systick += SYST_RVR;
#endif
		// 9DOF Accel / Mag / Gyro: call the Kalman filter orientation algorithm
#if defined COMPUTE_9DOF_GBY_KALMAN
		thisSV_9DOF_GBY_KALMAN.systick = SYST_CVR & 0x00FFFFFF;
		fRun_9DOF_GBY_KALMAN(&thisSV_9DOF_GBY_KALMAN, &thisAccel, &thisMag, &thisGyro, &thisMagCal);
		thisSV_9DOF_GBY_KALMAN.systick -= SYST_CVR & 0x00FFFFFF;
		if (thisSV_9DOF_GBY_KALMAN.systick < 0) thisSV_9DOF_GBY_KALMAN.systick += SYST_RVR;
#endif

		// decide whether or not to initiate a magnetic calibration
#if defined COMPUTE_3DOF_B_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_9DOF_GBY_KALMAN
		// check no magnetic calibration is in progress
		if (!thisMagCal.iCalInProgress)
		{
			// do the first 4 element calibration immediately there are a minimum of MINMEASUREMENTS4CAL
			initiatemagcal = (!thisMagCal.iMagCalHasRun && (thisMagBuffer.iMagBufferCount >= MINMEASUREMENTS4CAL));

			// otherwise initiate a calibration at intervals depending on the number of measurements available
			initiatemagcal |= ((thisMagBuffer.iMagBufferCount >= MINMEASUREMENTS4CAL) &&
					(thisMagBuffer.iMagBufferCount < MINMEASUREMENTS7CAL) &&
					!(globals.loopcounter % INTERVAL4CAL));
			initiatemagcal |= ((thisMagBuffer.iMagBufferCount >= MINMEASUREMENTS7CAL) &&
					(thisMagBuffer.iMagBufferCount < MINMEASUREMENTS10CAL) &&
					!(globals.loopcounter % INTERVAL7CAL));
			initiatemagcal |= ((thisMagBuffer.iMagBufferCount >= MINMEASUREMENTS10CAL) &&
					!(globals.loopcounter % INTERVAL10CAL));

			// initiate the magnetic calibration if any of the conditions are met
			if (initiatemagcal)
			{
#if ENABLED_MQX
				_lwevent_set(&(globals.MagCalEventStruct), 1);
#else
      FRTOS1_xSemaphoreGive(globals.MagCalEventSem);
#endif
			}

		} // end of test that no calibration is already in progress
#endif

		// increment the loopcounter (used for time stamping magnetic data)
		globals.loopcounter++;

		// run the user medium frequency (typically 25Hz) user task
		UserMediumFrequencyTaskRun();

	} // end of infinite loop
}

// magnetic calibration task: this has the lowest priority and is continually interrupted by sensor read and fusion tasks
static void MagCal_task(void *task_init_data)
{
	// initialize magnetic calibration and magnetometer data buffer
#if defined COMPUTE_3DOF_B_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_9DOF_GBY_KALMAN
	fInitMagCalibration(&thisMagCal, &thisMagBuffer);
#endif

	// infinite loop controlled by MQX-Lite events
	while(1)
	{
		// wait for the magnetic calibration event
		// FALSE means any bit (of the 1 bit enabled by the mask) unblocks and NULL means infinite timeout
		LED1_Off(); 				// red LED off
#if ENABLED_MQX
		_lwevent_wait_for(&(globals.MagCalEventStruct), 1, FALSE, NULL);
#else
		FRTOS1_xSemaphoreTake(globals.MagCalEventSem, portMAX_DELAY);
#endif
		LED1_On();   			// red LED on

		// run the magnetic calibration
#if defined COMPUTE_3DOF_B_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_9DOF_GBY_KALMAN
		thisMagCal.iCalInProgress = true;
		thisMagCal.iMagCalHasRun = true;
		fRunMagCalibration(&thisMagCal, &thisMagBuffer, &thisMag);
#endif
	} // end of infinite loop
}

void SensorTasks_Init(void) {
  globals.MagCalEventSem = FRTOS1_xSemaphoreCreateBinary();
  if (globals.MagCalEventSem==NULL) {
    for(;;);
  }
  globals.RunKFEventSem = FRTOS1_xSemaphoreCreateBinary();
  if (globals.RunKFEventSem==NULL) {
    for(;;);
  }
  globals.SamplingEventSem = FRTOS1_xSemaphoreCreateBinary();
  if (globals.SamplingEventSem==NULL) {
    for(;;);
  }
  if (FRTOS1_xTaskCreate(
      MagCal_task,  /* pointer to the task */
      "MagCal", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  if (FRTOS1_xTaskCreate(
      Fusion_task,  /* pointer to the task */
      "Fusion", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }

}
