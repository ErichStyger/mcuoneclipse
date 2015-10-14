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
#ifndef DRIVERS_H
#define DRIVERS_H

#include "SensorTasks.h"

// sensor physical I2C addresses
#define MPL3115_I2C_ADDR				0x60
#define FXOS8700_I2C_ADDR				0x1E
#define FXAS2100X_I2C_ADDR				0x20
#define MMA8652_I2C_ADDR				0x1D
#define MAG3110_I2C_ADDR				0x0E
#define FXLS8952_I2C_ADDR				0x18

// MPL3115 registers and constants
#define MPL3115_STATUS					0x00
#define MPL3115_OUT_P_MSB				0x01
#define MPL3115_WHO_AM_I				0x0C
#define MPL3115_CTRL_REG1       		0x26
#define MPL3115_WHO_AM_I_VALUE			0xC4

// FXOS8700 registers and constants
#define FXOS8700_OUT_X_MSB       	  	0x01
#define FXOS8700_WHO_AM_I      			0x0D
#define FXOS8700_XYZ_DATA_CFG       	0x0E
#define FXOS8700_CTRL_REG1        	 	0x2A
#define FXOS8700_CTRL_REG2        	 	0x2B
#define FXOS8700_M_OUT_X_MSB       		0x33
#define FXOS8700_M_CTRL_REG1         	0x5B
#define FXOS8700_M_CTRL_REG2        	0x5C
#define FXOS8700_WHO_AM_I_VALUE_ENG     0xC4	// engineering samples
#define FXOS8700_WHO_AM_I_VALUE     	0xC7	// production
#define FXOS8701_WHO_AM_I_VALUE     	0xC9

// FXAS2100X registers and constants
#define FXAS2100X_DATA_REG            	0x01
#define FXAS2100X_WHO_AM_I        		0x0C
#define FXAS2100X_CTRL_REG0           	0x0D
#define FXAS2100X_CTRL_REG1           	0x13
#define FXAS21000_WHO_AM_I_VALUE		0xD1	// engineering and production
#define FXAS21002_WHO_AM_I_VALUE_ENG	0xD6	// engineering samples
#define FXAS21002_WHO_AM_I_VALUE		0xD7	// production

// MMA8652 registers and constants
#define MMA8652_STATUS					0x00
#define MMA8652_OUT_X_MSB       	  	0x01
#define MMA8652_WHO_AM_I        		0x0D
#define MMA8652_XYZ_DATA_CFG     	  	0x0E
#define MMA8652_CTRL_REG1           	0x2A
#define MMA8652_CTRL_REG2           	0x2B
#define MMA8652_WHO_AM_I_VALUE			0x4A

// MAG3110 registers and constants
#define MAG3110_STATUS					0x00
#define MAG3110_OUT_X_MSB       	  	0x01
#define MAG3110_WHO_AM_I      			0x07
#define MAG3110_CTRL_REG1        	 	0x10
#define MAG3110_CTRL_REG2         		0x11
#define MAG3110_WHO_AM_I_VALUE     		0xC4

// FXLS8952 registers and constants
#define FXLS8952_STATUS					0x00	
#define FXLS8952_OUT_X_LSB       	  	0x02	
#define FXLS8952_OUT_X_MSB       	  	0x03	
#define FXLS8952_OUT_Y_LSB       	  	0x04	
#define FXLS8952_OUT_Y_MSB       	  	0x05	
#define FXLS8952_OUT_Z_LSB       	  	0x06	
#define FXLS8952_OUT_Z_MSB       	  	0x07	
#define FXLS8952_WHO_AM_I        		0x0F	
#define FXLS8952_SENS_CONFIG1    	  	0x11	
#define FXLS8952_SENS_CONFIG2    	  	0x12	
#define FXLS8952_SENS_CONFIG3    	  	0x13	
#define FXLS8952_WHO_AM_I_VALUE			0x72

// functions defined in drivers.c
int8 WriteI2CByte(LDD_TDeviceData *DeviceDataPtr, uint8 I2CAddress, uint8 I2CRegister, uint8 I2CData);
int8 ReadI2CBytes(LDD_TDeviceData *DeviceDataPtr, uint8 I2CAddress, uint8 I2CRegister, uint8 *I2C_Buffer, uint8 nbytes);
int8 MPL3115_Init(LDD_TDeviceData *DeviceDataPtr, struct PressureSensor *pthisPressure);
int8 FXOS8700_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag);
int8 FXAS2100X_Init(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro);
int8 MMA8652_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
int8 FXLS8952_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
int8 MAG3110_Init(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag);
int8 MPL3115_ReadData(LDD_TDeviceData *DeviceDataPtr, struct PressureSensor *pthisPressure);
int8 FXOS8700_ReadAccData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
int8 FXOS8700_ReadMagData(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag);
int8 FXAS2100X_ReadData(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro);
int8 MMA8652_ReadData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
int8 FXLS8952_ReadData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel);
int8 MAG3110_ReadData(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag);
void ApplyAccelHAL(struct AccelSensor *pthisAccel);
void ApplyMagHAL(struct MagSensor *pthisMag);
void ApplyGyroHAL(struct GyroSensor *pthisGyro);
void BlueRadios_Init(LDD_TDeviceData *DeviceDataPtr);
void sBufAppendItem(uint8* pDest, uint32* pIndex, uint8* pSource, uint16 iBytesToCopy);
void CreateAndSendPacketsViaUART(LDD_TDeviceData *DeviceDataPtr_A, LDD_TDeviceData *DeviceDataPtr_B);

#endif // DRIVERS_H
