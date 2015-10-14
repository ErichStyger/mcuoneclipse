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
// If you want to take a simplistic approach of using the existing templates
// as your starting point, simply adding your code for startup, sampling task (eg. 200Hz)
// and fusion tasks (eg. 25Hz), then this is the file for you.  Just put your code
// where ever you see "PUT YOUR CODE HERE"
//
#include "Cpu.h"
#include "UART_A.h"
#include "UART_B.h"

#include "SensorTasks.h"
#include "Events.h"
#include "drivers.h"
#include "UART_A.h"

// global structures
uint8 sUARTOutputBuffer[256];  // larger than the nominal 124 byte size for outgoing packets
uint8 sUART_A_InputBuffer[32]; // larger than nominal 1 byte command in case of buffering
uint8 sUART_B_InputBuffer[32]; // larger than nominal 1 byte command in case of buffering

void UserStartup(void)
{
	// initialize the BlueRadios Bluetooth module
	BlueRadios_Init(UART_A_DeviceData);

	// trigger a callback when any single character is received into 
	// the UART_A or UART_B buffers.
	UART_A_ReceiveBlock(UART_A_DeviceData, sUART_A_InputBuffer, 1);	// Bluetooth on shield
	UART_B_ReceiveBlock(UART_B_DeviceData, sUART_B_InputBuffer, 1);	// OpenSDA and USB
	
	// UART callbacks and command interpreter are located in Events.c

	// put code here to be executed at the end of the RTOS startup sequence.
	//
	// PUT YOUR CODE HERE
	//

	return;
}

void UserHighFrequencyTaskInit(void)
{
	// User code to be executed ONE TIME the first time the high 
	// frequency task is run.
	//
	// PUT YOUR CODE HERE
	//
	return;
}

void UserMediumFrequencyTaskInit(void)
{
	// User code to be executed ONE TIME the first time the medium 
	// frequency task is run
	//
	// PUT YOUR CODE HERE
	//
	return;
}


void UserHighFrequencyTaskRun(void)
{
	// The default frequency at which this code runs is 200Hz.
	// This code runs after sensors are sampled.
	// In general, try to keep "high intensity" code out of 
	// UserHighFrequencyTaskRun.
	// The high frequency task also has highest priority.
	//
	// PUT YOUR CODE HERE
	//
	return;
}

void UserMediumFrequencyTaskRun(void)
{
	static int32 iThrottle = 0;

	// This function is called after the Kalman filter loop at a rate of 
	// SENSORFS / OVERSAMPLE_RATIO Hz. With the default settings this is 
	// 200Hz/8=25Hz giving a smooth video quality display on the PC and 
	// Android user interfaces. The UART (serial over USB and over Bluetooth) 
	// is limited to 115kbps which is more than adequate for the 31kbps 
	// needed at the default 25Hz output rate but insufficient for 100Hz or 
	// 200Hz output rates.  There is little point is providing output data 
	// faster than 25Hz video rates but since the UARTs can
	// support a higher rate, the limit is set to MAXPACKETRATEHZ=40Hz.

	// check for any need to throttle the output rate
#define MAXPACKETRATEHZ 40
#define RATERESOLUTION 1000
	if (((int32)MAXPACKETRATEHZ * (int32)OVERSAMPLE_RATIO) >= (int32)SENSORFS)
	{
		// no UART bandwidth problem: transmit the packets over UART (USB and Bluetooth)
		CreateAndSendPacketsViaUART(UART_A_DeviceData, UART_B_DeviceData);
	}
	else
	{
		// throttle back by fractional multiplier 
		//    (OVERSAMPLE_RATIO * MAXPACKETRATEHZ) / SENSORFS
		// the increment applied to iThrottle is in the range 0 to (RATERESOLUTION - 1)
		iThrottle += ((int32)OVERSAMPLE_RATIO * (int32) MAXPACKETRATEHZ * 
				(int32)RATERESOLUTION) / SENSORFS;
		if (iThrottle >= RATERESOLUTION)
		{			
			// update the throttle counter and transmit the packets over 
			// UART (USB and Bluetooth)
			iThrottle -= RATERESOLUTION;
			CreateAndSendPacketsViaUART(UART_A_DeviceData, UART_B_DeviceData);
		}
	}

	//
	// PUT YOUR CODE HERE
	//
	
	return;
}
