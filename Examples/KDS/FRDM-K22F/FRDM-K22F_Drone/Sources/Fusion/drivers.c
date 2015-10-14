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
// This file contains sensor drivers as well as the function which create the fusion output
// packets via UART.
//
// Sensor drivers require logical device drivers (for I2C) created via Processor Expert.
// If you change sensors and/or MCU architecture, these will need to be replaced as appropriate.
//
#include "I2C.h"
#include "UART_A.h"
#include "UART_B.h"
#include "FTM.h"
#include "string.h"

#include "build.h"
#include "types.h"
#include "drivers.h"
#include "magnetic.h"
#include "SensorTasks.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// low level I2C drivers
///////////////////////////////////////////////////////////////////////////////////////////////////////

// write a byte to specified I2C sensor and register
int8 WriteI2CByte(LDD_TDeviceData *DeviceDataPtr, uint8 I2CAddress, uint8 I2CRegister, uint8 I2CData)
{
	LDD_I2C_TErrorMask I2C_Error;
	LDD_I2C_TBusState I2C_BusState;		
	uint8 I2C_Buffer[2];

	// configure the I2C master logic to use selected slave address
	while (I2C_SelectSlaveDevice(DeviceDataPtr, LDD_I2C_ADDRTYPE_7BITS, I2CAddress) != ERR_OK)
		;

	// set up the buffer and send (with stop sequence)
	I2C_Buffer[0] = I2CRegister;
	I2C_Buffer[1] = I2CData;
	if (I2C_MasterSendBlock(DeviceDataPtr, I2C_Buffer, 2, LDD_I2C_SEND_STOP) != ERR_OK)
		return false;		

	// idle until error or transmission complete 
	do
	{
		I2C_GetError(DeviceDataPtr, &I2C_Error);
	} while (!(I2C_Error || I2C_MasterGetBlockSentStatus(DeviceDataPtr)));

	// make sure the stop sequence has been transmitted and the bus is idle
	do
	{
		I2C_CheckBus(DeviceDataPtr, &I2C_BusState);
	} while (I2C_BusState != LDD_I2C_IDLE);

	return (I2C_Error == ERR_OK);
}

// read an array of bytes from a specified I2C sensor and start register
int8 ReadI2CBytes(LDD_TDeviceData *DeviceDataPtr, uint8 I2CAddress, uint8 I2CRegister, uint8 *I2C_Buffer, uint8 nbytes)
{
	LDD_I2C_TErrorMask I2C_Error;
	LDD_I2C_TBusState I2C_BusState;		

	// configure the I2C master logic to use selected slave address
	while (I2C_SelectSlaveDevice(DeviceDataPtr, LDD_I2C_ADDRTYPE_7BITS, I2CAddress) != ERR_OK)
		;

	// write the start register address (no stop sequence)
	I2C_Buffer[0] = I2CRegister;
	if (I2C_MasterSendBlock(DeviceDataPtr, I2C_Buffer, 1, LDD_I2C_NO_SEND_STOP) != ERR_OK)
		return false;

	// loop until error or transmission complete
	do
	{
		I2C_GetError(DeviceDataPtr, &I2C_Error);
	} while (!(I2C_Error || I2C_MasterGetBlockSentStatus(DeviceDataPtr)));

	// send restart and requested number of data bytes (with stop sequence)
	if (I2C_MasterReceiveBlock(DeviceDataPtr, I2C_Buffer, nbytes, LDD_I2C_SEND_STOP) != ERR_OK)
		return false;

	// loop until error or transmission complete
	do
	{
		I2C_GetError(DeviceDataPtr, &I2C_Error);
	} while (!(I2C_Error || I2C_MasterGetBlockReceivedStatus(DeviceDataPtr)));

	// make sure the stop sequence has been transmitted and the bus is idle
	do
	{
		I2C_CheckBus(DeviceDataPtr, &I2C_BusState);
	} while (I2C_BusState != LDD_I2C_IDLE);

	return (I2C_Error == ERR_OK);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// sensor initialization over I2C
///////////////////////////////////////////////////////////////////////////////////////////////////////

// initialize MPL3115 pressure and temperature sensor (512ms or approx 2Hz ODR)
int8 MPL3115_Init(LDD_TDeviceData *DeviceDataPtr, struct PressureSensor *pthisPressure)
{
	int8 status;		// I2C transaction status

	// check the WHOAMI register for the correct value and return immediately if invalid
	status = ReadI2CBytes(DeviceDataPtr, MPL3115_I2C_ADDR, MPL3115_WHO_AM_I, &(pthisPressure->iWhoAmI), 1);
	status &= (pthisPressure->iWhoAmI == MPL3115_WHO_AM_I_VALUE);
	if (!status)
	{
		pthisPressure->iWhoAmI = 0;
		return status;
	}

	// write 0000 0000 = 0x00 to MPL3115_CTRL_REG1 to place the MPL3115 in Standby
	// [7]: ALT=0
	// [6]: RAW=0 
	// [5-3]: OS=000 
	// [2]: RST=0
	// [1]: OST=0
	// [0]: SBYB=0 to enter standby
	status &= WriteI2CByte(DeviceDataPtr, MPL3115_I2C_ADDR, MPL3115_CTRL_REG1, 0x00);

	// alternative for barometer mode
	// write 0011 1001 = 0x39 to configure MPL3115 and enter Active mode
	// [7]: ALT=0 for pressure measurements

	// write 1011 1001 = 0xB9 to configure MPL3115 and enter Active mode
	// [7]: ALT=1 for altitude measurements
	// [6]: RAW=0 to disable raw measurements
	// [5-3]: OS=111 for OS ratio=128 and 512ms output interval
	// [2]: RST=0 do not enter reset
	// [1]: OST=0 do not initiate a reading
	// [0]: SBYB=1 to enter active mode
	status &= WriteI2CByte(DeviceDataPtr, MPL3115_I2C_ADDR, MPL3115_CTRL_REG1, 0xB9);

	// store the gain terms in the pressure structure
#define MPL3115_MPERCOUNT 0.0000152587890625F		// 1/65536 fixed range for MPL3115	
#define MPL3115_CPERCPOUNT 0.00390625F				// 1/256 fixed range for MPL3115
	pthisPressure->fmPerCount = MPL3115_MPERCOUNT;
	pthisPressure->fCPerCount = MPL3115_CPERCPOUNT;

	return status;
}

// initialize FXOS8700 accelerometer plus magnetometer sensor (hybrid mode 200Hz ODR for both sensors)
int8 FXOS8700_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag)
{
	int8 status;		// I2C transaction status
	uint8 iWhoAmI;		// sensor WhoAmI

	// check the WHOAMI register for the correct value and return immediately if invalid
	status = ReadI2CBytes(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_WHO_AM_I, &iWhoAmI, 1);
	status &= (iWhoAmI == FXOS8700_WHO_AM_I_VALUE) || (iWhoAmI == FXOS8700_WHO_AM_I_VALUE_ENG) || (iWhoAmI == FXOS8701_WHO_AM_I_VALUE);
	if (!status)
	{
		pthisAccel->iWhoAmI = pthisMag->iWhoAmI = 0;
		return status;
	}
	else
	{
		pthisAccel->iWhoAmI = pthisMag->iWhoAmI = iWhoAmI;
	}

	// write 0000 0000 = 0x00 to CTRL_REG1 to place FXOS8700 into standby
	// [7-1] = 0000 000
	// [0]: active=0
	status &= WriteI2CByte(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_CTRL_REG1, 0x00);

	// write 0001 1111 = 0x1F to M_CTRL_REG1
	// [7]: m_acal=0: auto calibration disabled
	// [6]: m_rst=0: one-shot magnetic reset disabled
	// [5]: m_ost=0: one-shot magnetic measurement disabled
	// [4-2]: m_os=111=7: 8x oversampling (for 200Hz) to reduce magnetometer noise
	// [1-0]: m_hms=11=3: select hybrid mode with accel and magnetometer active
	status &= WriteI2CByte(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_M_CTRL_REG1, 0x1F);

	// write 0010 0000 = 0x20 to M_CTRL_REG2
	// [7]: reserved
	// [6]: reserved
	// [5]: hyb_autoinc_mode=1 to map the magnetometer registers to follow the accelerometer registers
	// [4]: m_maxmin_dis=0 to retain default min/max latching even though not used
	// [3]: m_maxmin_dis_ths=0
	// [2]: m_maxmin_rst=0
	// [1-0]: m_rst_cnt=00 to enable magnetic reset each cycle
	status &= WriteI2CByte(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_M_CTRL_REG2, 0x20);

	// write 0000 0001= 0x01 to XYZ_DATA_CFG register
	// [7]: reserved
	// [6]: reserved
	// [5]: reserved
	// [4]: hpf_out=0
	// [3]: reserved
	// [2]: reserved
	// [1-0]: fs=01 for 4g mode: 2048 counts / g = 8192 counts / g after 2 bit left shift
	status &= WriteI2CByte(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_XYZ_DATA_CFG, 0x01);

	// place the gain for this full scale range into the accelerometer structure
#define FXOS8700_COUNTSPERG 8192			
	pthisAccel->iCountsPerg = FXOS8700_COUNTSPERG;
	pthisAccel->fgPerCount = 1.0F / FXOS8700_COUNTSPERG;

	// write 0000 0010 = 0x02 to CTRL_REG2 to set MODS bits
	// [7]: st=0: self test disabled
	// [6]: rst=0: reset disabled
	// [5]: unused
	// [4-3]: smods=00
	// [2]: slpe=0: auto sleep disabled
	// [1-0]: mods=10 for high resolution (maximum over sampling)
	status &= WriteI2CByte(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_CTRL_REG2, 0x02);

	// write 0000 1101 = 0x0D to accelerometer control register 1
	// [7-6]: aslp_rate=00
	// [5-3]: dr=001=1 for 200Hz data rate (when in hybrid mode)
	// [2]: lnoise=1 for low noise mode (since we're in 4g mode)
	// [1]: f_read=0 for normal 16 bit reads
	// [0]: active=1 to take the part out of standby and enable sampling
	status &= WriteI2CByte(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_CTRL_REG1, 0x0D);

	// store the magnetometer gain into the structure
#define FXOS8700_COUNTSPERUT 10		
	pthisMag->iCountsPeruT = FXOS8700_COUNTSPERUT;
	pthisMag->fCountsPeruT = (float)FXOS8700_COUNTSPERUT;
	pthisMag->fuTPerCount = 1.0F / FXOS8700_COUNTSPERUT;

	return status;
}

// initialize FXLS8952 accelerometer sensor for 200Hz ODR
int8 FXLS8952_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel)
{
	int8 status;		// I2C transaction status

	// check the WHOAMI register for the correct value and return immediately if invalid
	status = ReadI2CBytes(DeviceDataPtr, FXLS8952_I2C_ADDR, FXLS8952_WHO_AM_I, &(pthisAccel->iWhoAmI), 1);
	status &= (pthisAccel->iWhoAmI == FXLS8952_WHO_AM_I_VALUE);
	if (!status)
	{
		pthisAccel->iWhoAmI = 0;
		return status;
	}

	// write 0000 0000 = 0x00 to SENS_CONFIG1 to place FXLS8952 into standby
	// [7-1]: Set when taking the part out of standby
	// [0]: ACTIVE=0 for standby
	status &= WriteI2CByte(DeviceDataPtr, FXLS8952_I2C_ADDR, FXLS8952_SENS_CONFIG1, 0x00);

	// write 0101 0000 = 0x50 to SENS_CONFIG2 register to set High Performance Mode
	// [7-6]: WAKE_PM=01 for High Performance Mode
	// [5-4]: SLEEP_PM=01 for High Performance Mode
	// [3]: LE_BE=0 for Little Endian
	// [2]: BLOCK=0 for normal latching
	// [1]: AINC_TEMP=0 to not include temperature in auto increment
	// [0]: F_READ=0 for normal 12 bit reads
	status &= WriteI2CByte(DeviceDataPtr, FXLS8952_I2C_ADDR, FXLS8952_SENS_CONFIG2, 0x50);

	// write 0100 0000 = 0x40 to SENS_CONFIG3 register to set 200Hz ODR
	// [7-4]: WAKE_ODR=0100 for 200Hz ODR and 16x decimation from maximum 3200Hz
	// [3-0]: SLEEP_ODR=0000:
	status &= WriteI2CByte(DeviceDataPtr, FXLS8952_I2C_ADDR, FXLS8952_SENS_CONFIG3, 0x40);

	// write 0000 0011 = 0x03 to SENS_CONFIG1 to configure 4g mode and Active mode
	// [7]: RST=0 for no software reset
	// [6-5]: ST_AXIS_SEL=00 to disable self test
	// [4]: ST_POL=0 (default)
	// [3]: AWS_EN=0 (default)
	// [2-1]: FSR=01 for 4g mode
	// [1]: ACTIVE=1 for standby
	status &= WriteI2CByte(DeviceDataPtr, FXLS8952_I2C_ADDR, FXLS8952_SENS_CONFIG1, 0x03);

	// store the gain terms in the accelerometer sensor structure
#define FXLS8952_COUNTSPERG 512
	pthisAccel->iCountsPerg = FXLS8952_COUNTSPERG;
	pthisAccel->fgPerCount = 1.0F / FXLS8952_COUNTSPERG;

	return status;
}

// initialize MMA8652 accelerometer sensor (200Hz ODR)
int8 MMA8652_Init(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel)
{
	int8 status;		// I2C transaction status

	// check the WHOAMI register for the correct value and return immediately if invalid
	status = ReadI2CBytes(DeviceDataPtr, MMA8652_I2C_ADDR, MMA8652_WHO_AM_I, &(pthisAccel->iWhoAmI), 1);
	status &= (pthisAccel->iWhoAmI == MMA8652_WHO_AM_I_VALUE);
	if (!status)
	{
		pthisAccel->iWhoAmI = 0;
		return status;
	}

	// write 0000 0000 = 0x00 to CTRL_REG1 to place MMA8652 into standby
	// [7-1] = 0000 000
	// [0]: active=0
	status &= WriteI2CByte(DeviceDataPtr, MMA8652_I2C_ADDR, MMA8652_CTRL_REG1, 0x00);

	// write 0000 0001 = 0x01 to XYZ_DATA_CFG register to set g range
	// [7-5]: reserved=000
	// [4]: HPF_OUT=0
	// [3-2]: reserved=00
	// [1-0]: FS=01 for +/-4g: 512 counts / g = 8192 counts / g after 4 bit left shift
	status &= WriteI2CByte(DeviceDataPtr, MMA8652_I2C_ADDR, MMA8652_XYZ_DATA_CFG, 0x01);

	// store the gain term in the accelerometer sensor structure
#define MMA8652_COUNTSPERG 8192			
	pthisAccel->iCountsPerg = MMA8652_COUNTSPERG;
	pthisAccel->fgPerCount = 1.0F / MMA8652_COUNTSPERG;

	// write 0000 0010 = 0x02 to CTRL_REG2 to set MODS bits
	// [7]: ST=0: self test disabled
	// [6]: RST=0: reset disabled
	// [5]: unused
	// [4-3]: SMODS=00
	// [2]: SLPE=0: auto sleep disabled
	// [1-0]: mods=10 for high resolution (maximum over sampling)
	status &= WriteI2CByte(DeviceDataPtr, MMA8652_I2C_ADDR, MMA8652_CTRL_REG2, 0x02);

	// write 0001 0001 = 0x11 to CTRL_REG1
	// [7-6]: aslp_rate=00
	// [5-3]: dr=010 for 200Hz data rate
	// [2]: unused=0
	// [1]: f_read=0 for normal 16 bit reads
	// [0]: active=1 to take the part out of standby and enable sampling
	status &= WriteI2CByte(DeviceDataPtr, MMA8652_I2C_ADDR, MMA8652_CTRL_REG1, 0x11);

	return status;
}

// initialize MAG3110 magnetometer sensor (80Hz ODR)
int8 MAG3110_Init(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag)
{
	int8 status;		// I2C transaction status

	// check the WHOAMI register for the correct value and return immediately if invalid
	status = ReadI2CBytes(DeviceDataPtr, MAG3110_I2C_ADDR, MAG3110_WHO_AM_I, &(pthisMag->iWhoAmI), 1);
	status &= (pthisMag->iWhoAmI == MAG3110_WHO_AM_I_VALUE);
	if (!status)
	{
		pthisMag->iWhoAmI = 0;
		return status;
	}

	// write 0000 0000 = 0x00 to CTRL_REG1 to place MAG3110 into standby
	// [7-1] = 0000 000
	// [0]: AC=0 for standby
	status &= WriteI2CByte(DeviceDataPtr, MAG3110_I2C_ADDR, MAG3110_CTRL_REG1, 0x00);

	// write 1001 0000 = 0x90 to CTRL_REG2
	// [7]: AUTO_MRST_EN=1: enable degaussing
	// [6]: unused=0
	// [5]: RAW=0: normal mode
	// [4]: Mag_RST=1: enable a single degauss
	// [3-0]: unused=0
	status &= WriteI2CByte(DeviceDataPtr, MAG3110_I2C_ADDR, MAG3110_CTRL_REG2, 0x90);

	// write 0000 0001 = 0x01 to CTRL_REG1 to take MAG3110 out of standby
	// [7-5]: DR=000 for 80Hz ODR (16x OS on 1280Hz ADC measurements)
	// [4-3]: OS=00 for no oversampling
	// [2]: FT=0 for normal reads
	// [1]: TM=0 to not trigger immediate measurement
	// [0]: AC=1 for active mode
	status &= WriteI2CByte(DeviceDataPtr, MAG3110_I2C_ADDR, MAG3110_CTRL_REG1, 0x01);

	// store the gain term in the magnetometer sensor structure
#define MAG3110_COUNTSPERUT 10						// fixed range for MAG3110 magnetometer
	pthisMag->iCountsPeruT = MAG3110_COUNTSPERUT;
	pthisMag->fCountsPeruT = (float)MAG3110_COUNTSPERUT;
	pthisMag->fuTPerCount = 1.0F / MAG3110_COUNTSPERUT;

	return status;
}

// initialize FXAS2100X gyroscope sensor (ODR is variable and matched to gyro sampling rate)
int8 FXAS2100X_Init(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro)
{
	int8 status;		// I2C transaction status

	// check the WHOAMI register for the correct value and return immediately if invalid
	status = ReadI2CBytes(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_WHO_AM_I, &(pthisGyro->iWhoAmI), 1);
	status &= (pthisGyro->iWhoAmI == FXAS21000_WHO_AM_I_VALUE) || (pthisGyro->iWhoAmI == FXAS21002_WHO_AM_I_VALUE) || (pthisGyro->iWhoAmI == FXAS21002_WHO_AM_I_VALUE_ENG);
	if (!status)
	{
		pthisGyro->iWhoAmI = 0;
		return status;
	}

	switch (pthisGyro->iWhoAmI)
	{
	case FXAS21000_WHO_AM_I_VALUE:
		// write 0000 0000 = 0x00 to CTRL_REG1 to place FXOS21000 in Standby
		// [7]: ZR_cond=0
		// [6]: RST=0
		// [5]: ST=0 self test disabled
		// [4-2]: DR[2-0]=000 for 200Hz ODR
		// [1-0]: Active=0, Ready=0 for Standby mode
		status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x00);

		// write 0000 0000 = 0x00 to CTRL_REG0 to configure range and filters
		// [7-6]: unused=00
		// [5]: SPIW=0 4 wire SPI (irrelevant)
		// [4-3]: SEL[1-0]=00 for 10Hz HPF at 200Hz ODR
		// [2]: HPF_EN=0 disable HPF
		// [1-0]: FS[1-0]=00 for 1600dps
		status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG0, 0x00);

		// place the gain for this full scale range into the gyro structure
		// 14 bit scaling is 5, 10, 20, 40 counts/dps for 1600, 800, 400, 200dps ranges
		// 16 bit scaling is 20, 40, 80, 160 counts/dps for 1600, 800, 400, 200dps ranges
#define FXAS21000_COUNTSPERDEGPERSEC 20     		// 1600dps range
		pthisGyro->iCountsPerDegPerSec = FXAS21000_COUNTSPERDEGPERSEC;
		pthisGyro->fDegPerSecPerCount = 1.0F / FXAS21000_COUNTSPERDEGPERSEC;

		// write 000X XX10 to CTRL_REG1 to configure ODR and enter Active mode
		// [7]: ZR_cond=0
		// [6]: RST=0
		// [5]: ST=0 self test disabled
		// [4-2]: DR[2-0]=000 for 200Hz ODR giving 0x02
		// [4-2]: DR[2-0]=001 for 100Hz ODR giving 0x06
		// [4-2]: DR[2-0]=010 for 50Hz ODR giving 0x0A
		// [4-2]: DR[2-0]=011 for 25Hz ODR giving 0x0E
		// [4-2]: DR[2-0]=100 for 12.5Hz ODR giving 0x12
		// [4-2]: DR[2-0]=101 for 6.25Hz ODR giving 0x16
		// [4-2]: DR[2-0]=110 for 3.125Hz ODR giving 0x1A
		// [4-2]: DR[2-0]=111 for 1.5625Hz ODR giving 0x1E
		// [1-0]: Active=1, Ready=0 for Active mode
		if (SENSORFS >= 200)	// select 200Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x02);
		else if (SENSORFS >= 100) // select 100Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x06);
		else if (SENSORFS >= 50) // select 50Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x0A);
		else if (SENSORFS >= 25) // select 25Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x0E);
		else if (SENSORFS >= 12) // select 12.5Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x12);
		else if (SENSORFS >= 6)  // select 6.25Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x16);
		else if (SENSORFS >= 3)  // select 3.125Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x1A);
		else // select 1.5625Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x1E);
		break;
	case FXAS21002_WHO_AM_I_VALUE:
	case FXAS21002_WHO_AM_I_VALUE_ENG:
		// write 0000 0000 = 0x00 to CTRL_REG1 to place FXOS21002 in Standby
		// [7]: ZR_cond=0
		// [6]: RST=0
		// [5]: ST=0 self test disabled
		// [4-2]: DR[2-0]=000 for 800Hz
		// [1-0]: Active=0, Ready=0 for Standby mode
		status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x00);

		// write 0000 0000 = 0x00 to CTRL_REG0 to configure range and filters
		// [7-6]: BW[1-0]=00, LPF disabled
		// [5]: SPIW=0 4 wire SPI (irrelevant)
		// [4-3]: SEL[1-0]=00 for 10Hz HPF at 200Hz ODR
		// [2]: HPF_EN=0 disable HPF
		// [1-0]: FS[1-0]=00 for 2000dps
		status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG0, 0x00);

		// place the gain for this full scale range into the gyro structure
#define FXAS21002_COUNTSPERDEGPERSEC 16    			// for 2000dps=32000 counts
		pthisGyro->iCountsPerDegPerSec = FXAS21002_COUNTSPERDEGPERSEC;
		pthisGyro->fDegPerSecPerCount = 1.0F / FXAS21002_COUNTSPERDEGPERSEC;

		// write 000X XX10 to CTRL_REG1 to configure ODR and enter Active mode
		// [7]: ZR_cond=0
		// [6]: RST=0
		// [5]: ST=0 self test disabled
		// [4-2]: DR[2-0]=000 for 800Hz ODR giving 0x02
		// [4-2]: DR[2-0]=001 for 400Hz ODR giving 0x06
		// [4-2]: DR[2-0]=010 for 200Hz ODR giving 0x0A
		// [4-2]: DR[2-0]=011 for 100Hz ODR giving 0x0E
		// [4-2]: DR[2-0]=100 for 50Hz ODR giving 0x12
		// [4-2]: DR[2-0]=101 for 25Hz ODR giving 0x16
		// [4-2]: DR[2-0]=110 for 12.5Hz ODR giving 0x1A
		// [4-2]: DR[2-0]=111 for 12.5Hz ODR giving 0x1E
		// [1-0]: Active=1, Ready=0 for Active mode
		if (SENSORFS >= 800)	// select 800Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x02);
		else if (SENSORFS >= 400) // select 400Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x06);
		else if (SENSORFS >= 200) // select 200Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x0A);
		else if (SENSORFS >= 100) // select 100Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x0E);
		else if (SENSORFS >= 50) // select 50Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x12);
		else if (SENSORFS >= 25)  // select 25Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x16);
		else // select 12.5Hz ODR
			status &= WriteI2CByte(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_CTRL_REG1, 0x1A);	
		break;
	default:
		// will never happen
		break;
	}

	return status;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// sensor read over I2C
///////////////////////////////////////////////////////////////////////////////////////////////////////

// read MPL3115 pressure sensor over I2C
int8 MPL3115_ReadData(LDD_TDeviceData *DeviceDataPtr, struct PressureSensor *pthisPressure)
{
	uint8 I2C_Buffer[5];	// I2C read buffer
	int8 status;			// I2C transaction status

	// read the five sequential sensor output bytes
	status = ReadI2CBytes(DeviceDataPtr, MPL3115_I2C_ADDR, MPL3115_OUT_P_MSB, I2C_Buffer, 5);

	// place the read buffer into the 32 bit altitude and 16 bit temperature
	pthisPressure->iH = (I2C_Buffer[0] << 24) | (I2C_Buffer[1] << 16) | (I2C_Buffer[2] << 8);
	pthisPressure->iT = (I2C_Buffer[3] << 8) | I2C_Buffer[4];

	// this line only valid if the MPL3115 is initialized to pressure mode
	pthisPressure->iP = (I2C_Buffer[0] << 16) | (I2C_Buffer[1] << 8) | (I2C_Buffer[2] << 0);

	// convert from counts to metres altitude and C
	pthisPressure->fH = (float) pthisPressure->iH * pthisPressure->fmPerCount;
	pthisPressure->fT = (float) pthisPressure->iT * pthisPressure->fCPerCount;

	return status;
}

// read FXOS8700 accelerometer over I2C
int8 FXOS8700_ReadAccData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel)
{
	uint8 I2C_Buffer[6];	// I2C read buffer
	int8 status;			// I2C transaction status
	int8 i;					// scratch

	// read the six sequential sensor accelerometer output bytes
	status = ReadI2CBytes(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_OUT_X_MSB, I2C_Buffer, 6);

	// process the three channels
	for (i = CHX; i <= CHZ; i++)
	{
		// place the 6 bytes read into the accelerometer structure
		pthisAccel->iGs[i] = (I2C_Buffer[2 * i] << 8) | I2C_Buffer[2 * i + 1];

		// check for -32768 since this value cannot be negated in a later HAL operation
		if (pthisAccel->iGs[i] == -32768) pthisAccel->iGs[i]++;
	}

	// apply the HAL
	ApplyAccelHAL(pthisAccel);


	return status;
}

// read FXLS8952 accelerometer data over I2C
int8 FXLS8952_ReadData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel)
{
	uint8 I2C_Buffer[6];	// I2C read buffer
	int8 status;			// I2C transaction status
	int8 i;					// scratch

	// read the six sequential sensor output bytes
	status = ReadI2CBytes(DeviceDataPtr, FXLS8952_I2C_ADDR, FXLS8952_OUT_X_LSB, I2C_Buffer, 6);

	// process the three channels
	for (i = CHX; i <= CHZ; i++)
	{
		// place the 6 bytes read into the 16 bit accelerometer structure
		pthisAccel->iGs[i] = (I2C_Buffer[2 * i + 1] << 8) | I2C_Buffer[2 * i];

		// check for -32768 since this value cannot be negated in a later HAL operation
		if (pthisAccel->iGs[i] == -32768) pthisAccel->iGs[i]++;
	}

	// apply the HAL
	ApplyAccelHAL(pthisAccel);

	return status;
}

// read MMA8652 accelerometer data over I2C
int8 MMA8652_ReadData(LDD_TDeviceData *DeviceDataPtr, struct AccelSensor *pthisAccel)
{
	uint8 I2C_Buffer[6];	// I2C read buffer
	int8 status;			// I2C transaction status
	int8 i;					// scratch

	// read the six sequential sensor output bytes
	status = ReadI2CBytes(DeviceDataPtr, MMA8652_I2C_ADDR, MMA8652_OUT_X_MSB, I2C_Buffer, 6);

	// process the three channels
	for (i = CHX; i <= CHZ; i++)
	{
		// place the 6 bytes read into the 16 bit accelerometer structure
		pthisAccel->iGs[i] = (I2C_Buffer[2 * i] << 8) | I2C_Buffer[2 * i + 1];

		// check for -32768 since this value cannot be negated in a later HAL operation
		if (pthisAccel->iGs[i] == -32768) pthisAccel->iGs[i]++;
	}

	// apply the HAL
	ApplyAccelHAL(pthisAccel);

	return status;
}

// read FXOS8700 magnetometer over I2C
int8 FXOS8700_ReadMagData(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag)
{
	uint8 I2C_Buffer[6];	// I2C read buffer
	int8 status;			// I2C transaction status
	int8 i;					// scratch

	// read the six sequential magnetometer output bytes
	status = ReadI2CBytes(DeviceDataPtr, FXOS8700_I2C_ADDR, FXOS8700_M_OUT_X_MSB, I2C_Buffer, 6);

	// process the three channels
	for (i = CHX; i <= CHZ; i++)
	{
		// place the 6 bytes read into the magnetometer structure
		pthisMag->iBs[i] = (I2C_Buffer[2 * i] << 8) | I2C_Buffer[2 * i + 1];

		// check for -32768 since this value cannot be negated in a later HAL operation
		if (pthisMag->iBs[i] == -32768) pthisMag->iBs[i]++;
	}

	// apply the HAL
	ApplyMagHAL(pthisMag);

	return status;
}

// read MAG3110 magnetometer data over I2C
int8 MAG3110_ReadData(LDD_TDeviceData *DeviceDataPtr, struct MagSensor *pthisMag)
{
	uint8 I2C_Buffer[6];	// I2C read buffer
	int8 status;			// I2C transaction status
	int8 i;					// scratch

	// read the six sequential sensor output bytes
	status = ReadI2CBytes(DeviceDataPtr, MAG3110_I2C_ADDR, MAG3110_OUT_X_MSB, I2C_Buffer, 6);

	// process the three channels
	for (i = CHX; i <= CHZ; i++)
	{
		// place the 6 bytes read into the 16 bit accelerometer structure
		pthisMag->iBs[i] = (I2C_Buffer[2 * i] << 8) | I2C_Buffer[2 * i + 1];

		// check for -32768 since this value cannot be negated in a later HAL operation
		if (pthisMag->iBs[i] == -32768) pthisMag->iBs[i]++;
	}

	// apply the magnetometer HAL
	ApplyMagHAL(pthisMag);

	return status;
}

// read FXAS2100X gyro data over I2C
int8 FXAS2100X_ReadData(LDD_TDeviceData *DeviceDataPtr, struct GyroSensor *pthisGyro)
{
	uint8 I2C_Buffer[6];	// I2C read buffer
	int8 status;			// I2C transaction status
	int8 i;					// scratch

	// read the six sequential sensor output bytes
	status = ReadI2CBytes(DeviceDataPtr, FXAS2100X_I2C_ADDR, FXAS2100X_DATA_REG, I2C_Buffer, 6);

	// process the three channels
	for (i = CHX; i <= CHZ; i++)
	{
		// place the 6 bytes read into the gyroscope structures
		pthisGyro->iYs[i] = (I2C_Buffer[2 * i] << 8) | I2C_Buffer[2 * i + 1];

		// check for -32768 since this value cannot be negated in a later HAL operation
		if (pthisGyro->iYs[i] == -32768) pthisGyro->iYs[i]++;
	}

	// apply the HAL
	ApplyGyroHAL(pthisGyro);

	return status;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Abstraction Layers (HAL) functions
///////////////////////////////////////////////////////////////////////////////////////////////////////

// function applies the hardware abstraction layer to the accelerometer readings
void ApplyAccelHAL(struct AccelSensor *pthisAccel)
{
#if THISCOORDSYSTEM == NED
	int16 itmp16;
	itmp16 = pthisAccel->iGs[CHX];
	pthisAccel->iGs[CHX] = pthisAccel->iGs[CHY];
	pthisAccel->iGs[CHY] = itmp16;
#endif // NED
#if THISCOORDSYSTEM == ANDROID
	pthisAccel->iGs[CHX] = -pthisAccel->iGs[CHX];
	pthisAccel->iGs[CHY] = -pthisAccel->iGs[CHY];
#endif // Android
#if (THISCOORDSYSTEM == WIN8)
	pthisAccel->iGs[CHZ] = -pthisAccel->iGs[CHZ];
#endif // Win8

	return;
}

// function applies the hardware abstraction layer to the magnetometer readings
void ApplyMagHAL(struct MagSensor *pthisMag)
{
#if THISCOORDSYSTEM == NED
	int16 itmp16;
	itmp16 = pthisMag->iBs[CHX];
	pthisMag->iBs[CHX] = -pthisMag->iBs[CHY];
	pthisMag->iBs[CHY] = -itmp16;
	pthisMag->iBs[CHZ] = -pthisMag->iBs[CHZ];
#endif // NED
#if THISCOORDSYSTEM == ANDROID
	pthisMag->iBs[CHX] = -pthisMag->iBs[CHX];
	pthisMag->iBs[CHY] = -pthisMag->iBs[CHY];		
#endif // Android
#if THISCOORDSYSTEM == WIN8
	pthisMag->iBs[CHX] = -pthisMag->iBs[CHX];
	pthisMag->iBs[CHY] = -pthisMag->iBs[CHY];
#endif

	// finally correct for the left handed magnetic coordinate system in MAG3110
#if defined USE_MAG3110
	pthisMag->iBs[CHZ] = -pthisMag->iBs[CHZ];
#endif

	return;
}

// function applies the hardware abstraction layer to the gyro readings
void ApplyGyroHAL(struct GyroSensor *pthisGyro)
{
#if THISCOORDSYSTEM == NED
	int16 itmp16;
	itmp16 = pthisGyro->iYs[CHX];
	pthisGyro->iYs[CHX] = -pthisGyro->iYs[CHY];
	pthisGyro->iYs[CHY] = -itmp16;
	pthisGyro->iYs[CHZ] = -pthisGyro->iYs[CHZ];
#endif // NED
#if THISCOORDSYSTEM == ANDROID
	pthisGyro->iYs[CHX] = -pthisGyro->iYs[CHX];
	pthisGyro->iYs[CHY] = -pthisGyro->iYs[CHY];
#endif // Android
#if THISCOORDSYSTEM == WIN8
	pthisGyro->iYs[CHX] = -pthisGyro->iYs[CHX];
	pthisGyro->iYs[CHY] = -pthisGyro->iYs[CHY];
#endif // Win8

	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Blueradios Bluetooth module initialization
///////////////////////////////////////////////////////////////////////////////////////////////////////

// initialize BlueRadios BR-LE4.0-D2A Bluetooth module
void BlueRadios_Init(LDD_TDeviceData *DeviceDataPtr)
{
	uint16 ilen;		// command string length

	// transmit "ATSRM,2,0\r" to minimize traffic from the module
	// command "ATSRM": sets the module response mode which configures how verbose the module will be
	// 2: response mode at to minimal
	// 0: disconnected mode is command mode
	// \r: carriage return escape sequence
	// note: UART_A is the UART connected to the Bluetooth module
	strcpy((char *)sUARTOutputBuffer, "ATSRM,2,0\r");
	ilen = strlen((char *)sUARTOutputBuffer);
	UART_A_SendBlock(DeviceDataPtr, sUARTOutputBuffer, ilen);

	// wait until all characters are transmitted over UART_A
	while (UART_A_GetSentDataNum(DeviceDataPtr) != ilen);

	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// UART packet drivers
///////////////////////////////////////////////////////////////////////////////////////////////////////

// function appends a variable number of source bytes to a destimation buffer
// for transmission as the bluetooth packet
// bluetooth packets are delimited by inserting the special byte 0x7E at the start
// and end of packets. this function must therefore handle the case of 0x7E appearing
// as general data. this is done here with the substitutions:
// a) replace 0x7E by 0x7D and 0x5E (one byte becomes two) 
// b) replace 0x7D by 0x7D and 0x5D (one byte becomes two)
// the inverse mapping must be performed at the application receiving the bluetooth stream: ie:
// replace 0x7D and 0x5E with 0x7E
// replace 0x7D and 0x5D with 0x7D
// NOTE: do not use this function to append the start and end bytes 0x7E to the bluetooth
// buffer. instead add the start and end bytes 0x7E explicitly as in:
// sUARTOutputBuffer[iByteCount++] = 0x7E;
void sBufAppendItem(uint8* pDest, uint32* pIndex, uint8* pSource, uint16 iBytesToCopy)
{
	uint16 i;			// loop counter

	// loop over number of bytes to add to the destination buffer
	for (i = 0; i < iBytesToCopy; i++)
	{
		switch (pSource[i])
		{
		case 0x7E:
			// special case 1: replace 0x7E (start and end byte) with 0x7D and 0x5E
			pDest[(*pIndex)++] = 0x7D;
			pDest[(*pIndex)++] = 0x5E;
			break;
		case 0x7D:
			// special case 2: replace 0x7D with 0x7D and 0x5D
			pDest[(*pIndex)++] = 0x7D;
			pDest[(*pIndex)++] = 0x5D;
			break;
		default:
			// general case, simply add this byte without change
			pDest[(*pIndex)++] = pSource[i];
			break;
		}
	}

	return;
}

// set packets out over UART_A to shield / Bluetooth module and over UART_B to OpenSDA / USB
void CreateAndSendPacketsViaUART(LDD_TDeviceData *DeviceDataPtr_A, LDD_TDeviceData *DeviceDataPtr_B)
{
	struct fquaternion fq;					// quaternion to be transmitted
	float ftmp;								// scratch
	static uint32 iTimeStamp = 0;			// 1MHz time stamp
	uint32 iIndex;							// output buffer counter
	int32 tmpint32;							// scratch int32
	int16 tmpint16;							// scratch int16
	int16 iPhi, iThe, iRho;					// integer angles to be transmitted
	int16 iDelta;							// magnetic inclination angle if available
	int16 iOmega[3];						// scaled angular velocity vector
	uint16 isystick;						// algorithm systick time
	uint8 tmpuint8;							// scratch uint8
	uint8 flags;							// byte of flags
	int16 i, j, k;							// general purpose
	static int16 MagneticPacketID = 0;	 	// magnetic packet number
	static uint8 iPacketNumber = 0; 		// packet number

#ifdef UART_OFF
	// enable full STOP mode
	SCB_SCR |= SCB_SCR_SLEEPDEEP_MASK; 
	return;
#else
	// disable full STOP mode
	SCB_SCR &= (~SCB_SCR_SLEEPDEEP_MASK); 
#endif

	// update the assumed 1MHz time stamp counter 
	iTimeStamp += (1000000 * OVERSAMPLE_RATIO) / SENSORFS;

	// zero the counter for bytes accumulated into the transmit buffer
	iIndex = 0;

	// ***************************************************************
	// Main type 1: range 0 to 35 = 36 bytes
	// Debug type 2: range 0 to 7 = 8 bytes
	// Angular velocity type 3: range 0 to 13 = 14 bytes
	// Euler angles type 4: range 0 to 13 = 14 bytes
	// Altitude/Temp type 5: range 0 to 13 = 14 bytes
	// Magnetic type 6: range 0 to 15 = 16 bytes
	// Kalman packet 7: range 0 to 47 = 48 bytes
	// Total is 150 bytes vs 256 bytes size of sUARTOutputBuffer
	// at 25Hz, data rate is 25*150 = 3750 bytes/sec = 37.5kbaud
	// the UART is set to 115kbaud so about 33% is being used
	// ***************************************************************

	// ************************************************************************
	// fixed length packet type 1
	// this packet type is always transmitted
	// total size is 0 to 35 equals 36 bytes 
	// ************************************************************************

	// [0]: packet start byte (need a iIndex++ here since not using sBufAppendItem)
	sUARTOutputBuffer[iIndex++] = 0x7E;

	// [1]: packet type 1 byte (iIndex is automatically updated in sBufAppendItem)
	tmpuint8 = 0x01;
	sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

	// [2]: packet number byte
	sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
	iPacketNumber++;

	// [6-3]: 1MHz time stamp (4 bytes)
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iTimeStamp, 4);

	// [12-7]: integer accelerometer data words (scaled to 8192 counts per g for PC GUI)
	// send non-zero data only if the accelerometer sensor is enabled and used by the selected quaternion
#if defined USE_FXOS8700 || defined USE_MMA8652 || defined USE_FXLS8952
	switch (globals.QuaternionPacketType)
	{
	case Q3:
	case Q6MA:
	case Q6AG:
	case Q9:
		// accelerometer data is used for the selected quaternion so transmit but clip at 4g
		tmpint32 = (thisAccel.iGs[CHX] * 8192) / thisAccel.iCountsPerg;
		if (tmpint32 > 32767) tmpint32 = 32767;
		if (tmpint32 < -32768) tmpint32 = -32768;
		tmpint16 = (int16) (tmpint32);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);

		tmpint32 = (thisAccel.iGs[CHY] * 8192) / thisAccel.iCountsPerg;
		if (tmpint32 > 32767) tmpint32 = 32767;
		if (tmpint32 < -32768) tmpint32 = -32768;
		tmpint16 = (int16) (tmpint32);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);

		tmpint32 = (thisAccel.iGs[CHZ] * 8192) / thisAccel.iCountsPerg;
		if (tmpint32 > 32767) tmpint32 = 32767;
		if (tmpint32 < -32768) tmpint32 = -32768;
		tmpint16 = (int16) (tmpint32);		
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		break;
	case Q3M:
	case Q3G:
	default:
		// accelerometer data is not used so transmit zero
		tmpint16 = 0;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
		break;
	}
#else
	// accelerometer data is not used so transmit zero
	tmpint16 = 0;
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
#endif

	// [18-13]: integer calibrated magnetometer data words (already scaled to 10 count per uT for PC GUI)
	// send non-zero data only if the magnetometer sensor is enabled and used by the selected quaternion
#if defined USE_FXOS8700 || defined USE_MAG3110
	switch (globals.QuaternionPacketType)
	{
	case Q3M:
	case Q6MA:
	case Q9:
		// magnetometer data is used for the selected quaternion so transmit
		tmpint16 = (int16) ((thisMag.iBcAvg[CHX] * 10) / thisMag.iCountsPeruT);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16) ((thisMag.iBcAvg[CHY] * 10) / thisMag.iCountsPeruT);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16) ((thisMag.iBcAvg[CHZ] * 10) / thisMag.iCountsPeruT);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		break;
	case Q3:
	case Q3G:
	case Q6AG:
	default:
		tmpint16 = 0;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
		break;
	}
#else
	// magnetometer data is not used so transmit zero
	tmpint16 = 0;
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
#endif

	// [24-19]: uncalibrated gyro data words (scaled to 20 counts per deg/s for PC GUI)
	// send non-zero data only if the gyro sensor is enabled and used by the selected quaternion
#if defined USE_FXAS2100X
	switch (globals.QuaternionPacketType)
	{
	case Q3G:
	case Q6AG:
	case Q9:
		// gyro data is used for the selected quaternion so transmit
		tmpint16 = (int16) ((thisGyro.iYs[CHX] * 20) / thisGyro.iCountsPerDegPerSec);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16) ((thisGyro.iYs[CHY] * 20) / thisGyro.iCountsPerDegPerSec);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16) ((thisGyro.iYs[CHZ] * 20) / thisGyro.iCountsPerDegPerSec);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		break;
	case Q3:
	case Q3M:
	case Q6MA:
	default:
		// gyro data is not used so transmit zero
		tmpint16 = 0;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
		break;
	}
#else
	// gyro data is not used so transmit zero
	tmpint16 = 0;
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
#endif

	// initialize default quaternion, flags byte, angular velocity and orientation
	fq.q0 = 1.0F;
	fq.q1 = fq.q2 = fq.q3 = 0.0F;
	flags = 0x00;
	iOmega[CHX] = iOmega[CHY] = iOmega[CHZ] = 0;
	iPhi = iThe = iRho = iDelta = 0;
	isystick = 0;

	// flags byte 33: quaternion type in least significant nibble
	// Q3:   coordinate nibble, 1
	// Q3M:	 coordinate nibble, 6
	// Q3G:	 coordinate nibble, 3
	// Q6MA: coordinate nibble, 2
	// Q6AG: coordinate nibble, 4
	// Q9:   coordinate nibble, 8

	// flags byte 33: coordinate in most significant nibble
	// Aerospace/NED:	0, quaternion nibble
	// Android:	  		1, quaternion nibble
	// Windows 8: 		2, quaternion nibble

	// set the quaternion, flags, angular velocity and Euler angles
	switch (globals.QuaternionPacketType)
	{
	case Q3:
#ifdef COMPUTE_3DOF_G_BASIC
		fq = thisSV_3DOF_G_BASIC.fLPq;
		flags |= 0x01;
		iOmega[CHX] = (int16)(thisSV_3DOF_G_BASIC.fOmega[CHX] * 20.0F);
		iOmega[CHY] = (int16)(thisSV_3DOF_G_BASIC.fOmega[CHY] * 20.0F);
		iOmega[CHZ] = (int16)(thisSV_3DOF_G_BASIC.fOmega[CHZ] * 20.0F);
		iPhi = (int16) (10.0F * thisSV_3DOF_G_BASIC.fLPPhi);
		iThe = (int16) (10.0F * thisSV_3DOF_G_BASIC.fLPThe);
		iRho = (int16) (10.0F * thisSV_3DOF_G_BASIC.fLPRho);
		iDelta = 0;
		isystick = (uint16)(thisSV_3DOF_G_BASIC.systick / 20);
#endif
		break;
	case Q3M:
#ifdef COMPUTE_3DOF_B_BASIC
		fq = thisSV_3DOF_B_BASIC.fLPq;
		//	flags |= 0x02;
		flags |= 0x06;
		iOmega[CHX] = (int16)(thisSV_3DOF_B_BASIC.fOmega[CHX] * 20.0F);
		iOmega[CHY] = (int16)(thisSV_3DOF_B_BASIC.fOmega[CHY] * 20.0F);
		iOmega[CHZ] = (int16)(thisSV_3DOF_B_BASIC.fOmega[CHZ] * 20.0F);
		iPhi = (int16) (10.0F * thisSV_3DOF_B_BASIC.fLPPhi);
		iThe = (int16) (10.0F * thisSV_3DOF_B_BASIC.fLPThe);
		iRho = (int16) (10.0F * thisSV_3DOF_B_BASIC.fLPRho);
		iDelta = 0;
		isystick = (uint16)(thisSV_3DOF_B_BASIC.systick / 20);
#endif
		break;
	case Q3G:
#ifdef COMPUTE_3DOF_Y_BASIC
		fq = thisSV_3DOF_Y_BASIC.fq;
		//flags |= 0x01;
		flags |= 0x03;
		iOmega[CHX] = (int16)(thisSV_3DOF_Y_BASIC.fOmega[CHX] * 20.0F);
		iOmega[CHY] = (int16)(thisSV_3DOF_Y_BASIC.fOmega[CHY] * 20.0F);
		iOmega[CHZ] = (int16)(thisSV_3DOF_Y_BASIC.fOmega[CHZ] * 20.0F);
		iPhi = (int16) (10.0F * thisSV_3DOF_Y_BASIC.fPhi);
		iThe = (int16) (10.0F * thisSV_3DOF_Y_BASIC.fThe);
		iRho = (int16) (10.0F * thisSV_3DOF_Y_BASIC.fRho);
		iDelta = 0;
		isystick = (uint16)(thisSV_3DOF_Y_BASIC.systick / 20);
#endif
		break;
	case Q6MA:
#ifdef COMPUTE_6DOF_GB_BASIC
		fq = thisSV_6DOF_GB_BASIC.fLPq;
		flags |= 0x02;
		iOmega[CHX] = (int16)(thisSV_6DOF_GB_BASIC.fOmega[CHX] * 20.0F);
		iOmega[CHY] = (int16)(thisSV_6DOF_GB_BASIC.fOmega[CHY] * 20.0F);
		iOmega[CHZ] = (int16)(thisSV_6DOF_GB_BASIC.fOmega[CHZ] * 20.0F);
		iPhi = (int16) (10.0F * thisSV_6DOF_GB_BASIC.fLPPhi);
		iThe = (int16) (10.0F * thisSV_6DOF_GB_BASIC.fLPThe);
		iRho = (int16) (10.0F * thisSV_6DOF_GB_BASIC.fLPRho);
		iDelta = (int16) (10.0F * thisSV_6DOF_GB_BASIC.fLPDelta);
		isystick = (uint16)(thisSV_6DOF_GB_BASIC.systick / 20);
#endif
		break;
	case Q6AG:	
#ifdef COMPUTE_6DOF_GY_KALMAN
		fq = thisSV_6DOF_GY_KALMAN.fqPl;
		flags |= 0x04;
		iOmega[CHX] = (int16)(thisSV_6DOF_GY_KALMAN.fOmega[CHX] * 20.0F);
		iOmega[CHY] = (int16)(thisSV_6DOF_GY_KALMAN.fOmega[CHY] * 20.0F);
		iOmega[CHZ] = (int16)(thisSV_6DOF_GY_KALMAN.fOmega[CHZ] * 20.0F);
		iPhi = (int16) (10.0F * thisSV_6DOF_GY_KALMAN.fPhiPl);
		iThe = (int16) (10.0F * thisSV_6DOF_GY_KALMAN.fThePl);
		iRho = (int16) (10.0F * thisSV_6DOF_GY_KALMAN.fRhoPl);
		iDelta = 0;
		isystick = (uint16)(thisSV_6DOF_GY_KALMAN.systick / 20);
#endif
		break;
	case Q9:
#ifdef COMPUTE_9DOF_GBY_KALMAN
		fq = thisSV_9DOF_GBY_KALMAN.fqPl;
		flags |= 0x08;
		iOmega[CHX] = (int16)(thisSV_9DOF_GBY_KALMAN.fOmega[CHX] * 20.0F);
		iOmega[CHY] = (int16)(thisSV_9DOF_GBY_KALMAN.fOmega[CHY] * 20.0F);
		iOmega[CHZ] = (int16)(thisSV_9DOF_GBY_KALMAN.fOmega[CHZ] * 20.0F);
		iPhi = (int16) (10.0F * thisSV_9DOF_GBY_KALMAN.fPhiPl);
		iThe = (int16) (10.0F * thisSV_9DOF_GBY_KALMAN.fThePl);
		iRho = (int16) (10.0F * thisSV_9DOF_GBY_KALMAN.fRhoPl);
		iDelta = (int16) (10.0F * thisSV_9DOF_GBY_KALMAN.fDeltaPl);
		isystick = (uint16)(thisSV_9DOF_GBY_KALMAN.systick / 20);
#endif
		break;
	default:
		// use the default data already initialized
		break;
	}

	// [32-25]: scale the quaternion (30K = 1.0F) and add to the buffer
	tmpint16 = (int16)(fq.q0 * 30000.0F);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	tmpint16 = (int16)(fq.q1 * 30000.0F);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	tmpint16 = (int16)(fq.q2 * 30000.0F);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	tmpint16 = (int16)(fq.q3 * 30000.0F);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);

	// set the coordinate system bits in flags from default NED (00)
#if (THISCOORDSYSTEM == ANDROID)
	// set the Android flag bits
	flags |= 0x10;
#elif (THISCOORDSYSTEM == WIN8)
	// set the Win8 flag bits
	flags |= 0x20;
#endif // THISCOORDSYSTEM

	// [33]: add the flags byte to the buffer
	sBufAppendItem(sUARTOutputBuffer, &iIndex, &flags, 1);

	// [34]: add the shield (bits 7-5) and Kinetis (bits 4-0) byte
	tmpuint8 = ((THIS_SHIELD & 0x07) << 5) | (THIS_KINETIS & 0x1F);
	sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

	// [35]: add the tail byte for the standard packet type 1
	sUARTOutputBuffer[iIndex++] = 0x7E;

	// ************************************************************************
	// Variable length debug packet type 2
	// currently total size is 0 to 7 equals 8 bytes 
	// ************************************************************************

	if (globals.DebugPacketOn)
	{
		// [0]: packet start byte
		sUARTOutputBuffer[iIndex++] = 0x7E;

		// [1]: packet type 2 byte
		tmpuint8 = 0x02;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

		// [2]: packet number byte
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
		iPacketNumber++;

		// [4-3] software version number
		tmpint16 = THISBUILD;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);

		// [6-5] systick count / 20
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&isystick, 2);

		// [7 in practice but can be variable]: add the tail byte for the debug packet type 2
		sUARTOutputBuffer[iIndex++] = 0x7E;
	}

	// ************************************************************************
	// Angular Velocity Bluetooth transmit packet type 3
	// total bytes for packet type 2 is range 0 to 13 = 14 bytes
	// ************************************************************************

	if (globals.AngularVelocityPacketOn)
	{
		// [0]: packet start byte
		sUARTOutputBuffer[iIndex++] = 0x7E;

		// [1]: packet type 3 byte (angular velocity)
		tmpuint8 = 0x03;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

		// [2]: packet number byte
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
		iPacketNumber++;

		// [6-3]: time stamp (4 bytes)
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iTimeStamp, 4);

		// [12-7]: add the scaled angular velocity vector to the output buffer
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iOmega[CHX], 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iOmega[CHY], 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iOmega[CHZ], 2);

		// [13]: add the tail byte for the angular velocity packet type 3
		sUARTOutputBuffer[iIndex++] = 0x7E;
	}

	// ************************************************************************
	// Roll, Pitch, Compass Euler angles packet type 4
	// total bytes for packet type 4 is range 0 to 13 = 14 bytes
	// ************************************************************************

	if 	(globals.RPCPacketOn)
	{
		// [0]: packet start byte
		sUARTOutputBuffer[iIndex++] = 0x7E;

		// [1]: packet type 4 byte (Euler angles)
		tmpuint8 = 0x04;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

		// [2]: packet number byte
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
		iPacketNumber++;

		// [6-3]: time stamp (4 bytes)
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iTimeStamp, 4);

		// [12-7]: add the angles (resolution 0.1 deg per count) to the transmit buffer
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iPhi, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iThe, 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iRho, 2);

		// [13]: add the tail byte for the roll, pitch, compass angle packet type 4
		sUARTOutputBuffer[iIndex++] = 0x7E;
	}

	// ************************************************************************
	// Altitude / Temperature packet type 5
	// total bytes for packet type 5 is range 0 to 13 = 14 bytes
	// ************************************************************************

#ifdef COMPUTE_1DOF_P_BASIC
	if (globals.AltPacketOn && thisPressure.iWhoAmI)
	{
		// [0]: packet start byte
		sUARTOutputBuffer[iIndex++] = 0x7E;

		// [1]: packet type 5 byte
		tmpuint8 = 0x05;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

		// [2]: packet number byte
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
		iPacketNumber++;

		// [6-3]: time stamp (4 bytes)
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&iTimeStamp, 4);

		// [10-7]: altitude (4 bytes, metres times 1000)
		tmpint32 = (int32)(thisSV_1DOF_P_BASIC.fLPH * 1000.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint32, 4);

		// [12-11]: temperature (2 bytes, deg C times 100)
		tmpint16 = (int16)(thisSV_1DOF_P_BASIC.fLPT * 100.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);

		// [13]: add the tail byte for the altitude / temperature packet type 5
		sUARTOutputBuffer[iIndex++] = 0x7E;
	}
#endif

	// ************************************************************************
	// magnetic buffer packet type 6
	// currently total size is 0 to 15 equals 16 bytes
	// this packet is only transmitted if a magnetic algorithm is computed
	// ************************************************************************

#if defined COMPUTE_3DOF_B_BASIC || defined COMPUTE_6DOF_GB_BASIC || defined COMPUTE_9DOF_GBY_KALMAN
	// [0]: packet start byte
	sUARTOutputBuffer[iIndex++] = 0x7E;

	// [1]: packet type 6 byte
	tmpuint8 = 0x06;
	sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

	// [2]: packet number byte
	sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
	iPacketNumber++;

	// [4-3]: number of active measurements in the magnetic buffer
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&(thisMagBuffer.iMagBufferCount), 2);	

	// [6-5]: fit error (%) with resolution 0.1% 
	if (thisMagCal.fFitErrorpc > 3276.7F)
		tmpint16 = 32767;
	else
		tmpint16 = (int16) (thisMagCal.fFitErrorpc * 10.0F);		
	sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);		

	// always calculate magnetic buffer row and column (low overhead and saves warnings)
	k = MagneticPacketID - 10;
	j = k / MAGBUFFSIZEX;
	i = k - j * MAGBUFFSIZEX;

	// [8-7]: int16: ID of magnetic variable to be transmitted
	// ID 0 to 4 inclusive are magnetic calibration coefficients
	// ID 5 to 9 inclusive are for future expansion
	// ID 10 to (MAGBUFFSIZEX=12) * (MAGBUFFSIZEY=24)-1 or 10 to 10+288-1 are magnetic buffer elements
	// where the convention is used that a negative value indicates empty buffer element (index=-1)
	if ((MagneticPacketID >= 10) && (thisMagBuffer.index[i][j] == -1))
	{
		// use negative ID to indicate inactive magnetic buffer element
		tmpint16 = -MagneticPacketID;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	}
	else
	{
		// use positive ID unchanged for variable or active magnetic buffer entry
		tmpint16 = MagneticPacketID;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
	}

	// [10-9]: int16: variable 1 to be transmitted this iteration
	// [12-11]: int16: variable 2 to be transmitted this iteration
	// [14-13]: int16: variable 3 to be transmitted this iteration
	switch (MagneticPacketID)
	{
	case 0:	
		// item 1: currently unused
		tmpint16 = 0;			
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);		
		// item 2: geomagnetic field strength with resolution 0.1uT
		tmpint16 = (int16)(thisMagCal.fB * 10.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		// item 3: magnetic inclination angle with resolution 0.1 deg	
		tmpint16 = iDelta;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		break;
	case 1:
		// items 1 to 3: hard iron components range -3276uT to +3276uT encoded with 0.1uT resolution
		tmpint16 = (int16)(thisMagCal.fV[CHX] * 10.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16)(thisMagCal.fV[CHY] * 10.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);		
		tmpint16 = (int16)(thisMagCal.fV[CHZ] * 10.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		break;			
	case 2:
		// items 1 to 3: diagonal soft iron range -32. to +32. encoded with 0.001 resolution
		tmpint16 = (int16)(thisMagCal.finvW[CHX][CHX] * 1000.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16)(thisMagCal.finvW[CHY][CHY] * 1000.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16)(thisMagCal.finvW[CHZ][CHZ] * 1000.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		break;
	case 3: 
		// items 1 to 3: off-diagonal soft iron range -32. to +32. encoded with 0.001 resolution
		tmpint16 = (int16)(thisMagCal.finvW[CHX][CHY] * 1000.0F);	
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16)(thisMagCal.finvW[CHX][CHZ] * 1000.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		tmpint16 = (int16)(thisMagCal.finvW[CHY][CHZ] * 1000.0F);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		break;
	case 4:				
	case 5:		
	case 6:		
	case 7:		
	case 8:		
	case 9:		
		// cases 4 to 9 inclusive are for future expansion so transmit zeroes for now
		tmpint16 = 0;		
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);		
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);	
		break;
	default:
		// 10 and upwards: this handles the magnetic buffer elements
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&(thisMagBuffer.iBs[CHX][i][j]), 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&(thisMagBuffer.iBs[CHY][i][j]), 2);
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&(thisMagBuffer.iBs[CHZ][i][j]), 2);
		break;
	}

	// wrap the variable ID back to zero if necessary
	MagneticPacketID++;
	if (MagneticPacketID >= (10 + MAGBUFFSIZEX * MAGBUFFSIZEY))
		MagneticPacketID = 0;

	// [15]: add the tail byte for the magnetic packet type 6
	sUARTOutputBuffer[iIndex++] = 0x7E;
#endif

	// *******************************************************************************
	// Kalman filter packet type 7
	// total bytes for packet type 7 is range 0 to 41 inclusive = 42 bytes
	// this packet is only transmitted when a Kalman algorithm is computed
	// and then non-zero data is transmitted only when a Kalman quaternion is selected
	// *******************************************************************************

#if defined COMPUTE_6DOF_GY_KALMAN || defined COMPUTE_9DOF_GBY_KALMAN
	if ((globals.QuaternionPacketType == Q6AG) || (globals.QuaternionPacketType == Q9))
	{
		// [0]: packet start byte
		sUARTOutputBuffer[iIndex++] = 0x7E;

		// [1]: packet type 7 byte
		tmpuint8 = 0x07;
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8, 1);

		// [2]: packet number byte
		sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
		iPacketNumber++;

		// [4-3]: fzgErr[CHX] resolution scaled by 30000 
		// [6-5]: fzgErr[CHY] resolution scaled by 30000 
		// [8-7]: fzgErr[CHZ] resolution scaled by 30000 
		for (i = CHX; i <= CHZ; i++)
		{
#if defined COMPUTE_6DOF_GY_KALMAN
			if (globals.QuaternionPacketType == Q6AG)
				tmpint16 = (int16)(thisSV_6DOF_GY_KALMAN.fZErr[i] * 3E4F);
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
			if (globals.QuaternionPacketType == Q9)
				tmpint16 = (int16)(thisSV_9DOF_GBY_KALMAN.fZErr[i] * 3E4F);
#endif
			// add the data to the packet
			sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		}

		// [10-9]: fgErrPl[CHX] resolution scaled by 30000 
		// [12-11]: fgErrPl[CHY] resolution scaled by 30000 
		// [14-13]: fgErrPl[CHZ] resolution scaled by 30000 
		for (i = CHX; i <= CHZ; i++)
		{
#if defined COMPUTE_6DOF_GY_KALMAN
			if (globals.QuaternionPacketType == Q6AG)
				tmpint16 = (int16)(thisSV_6DOF_GY_KALMAN.fqgErrPl[i] * 3E4F);
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
			if (globals.QuaternionPacketType == Q9)
				tmpint16 = (int16)(thisSV_9DOF_GBY_KALMAN.fqgErrPl[i] * 3E4F);
#endif
			// add the data to the packet
			sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		}

		// [16-15]: fzmErr[CHX] resolution scaled by 30000 
		// [18-17]: fzmErr[CHY] resolution scaled by 30000 
		// [20-19]: fzmErr[CHZ] resolution scaled by 30000 
		for (i = CHX; i <= CHZ; i++)
		{
#if defined COMPUTE_6DOF_GY_KALMAN
			if (globals.QuaternionPacketType == Q6AG)
				tmpint16 = 0;
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
			if (globals.QuaternionPacketType == Q9)
				tmpint16 = (int16)(thisSV_9DOF_GBY_KALMAN.fZErr[i + 3] * 3E4F);
#endif
			// add the data to the packet
			sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		}

		// [22-21]: fmErrPl[CHX] resolution scaled by 30000 
		// [24-23]: fmErrPl[CHY] resolution scaled by 30000 
		// [26-25]: fmErrPl[CHZ] resolution scaled by 30000 
		for (i = CHX; i <= CHZ; i++)
		{
#if defined COMPUTE_6DOF_GY_KALMAN
			if (globals.QuaternionPacketType == Q6AG)
				tmpint16 = 0;
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
			if (globals.QuaternionPacketType == Q9)
				tmpint16 = (int16)(thisSV_9DOF_GBY_KALMAN.fqmErrPl[i] * 3E4F);
#endif
			// add the data to the packet
			sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		}

		// [28-27]: fbPl[CHX] resolution 0.001 deg/sec
		// [30-29]: fbPl[CHY] resolution 0.001 deg/sec
		// [32-31]: fbPl[CHZ] resolution 0.001 deg/sec
		for (i = CHX; i <= CHZ; i++)
		{
#if defined COMPUTE_6DOF_GY_KALMAN
			if (globals.QuaternionPacketType == Q6AG)
				tmpint16 = (int16)(thisSV_6DOF_GY_KALMAN.fbPl[i] * 1000.0F);
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
			if (globals.QuaternionPacketType == Q9)
				tmpint16 = (int16)(thisSV_9DOF_GBY_KALMAN.fbPl[i] * 1000.0F);
#endif
			// add the data to the packet
			sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		}

		// [34-33]: fDeltaPl resolution 0.01deg
#if defined COMPUTE_6DOF_GY_KALMAN
		if (globals.QuaternionPacketType == Q6AG)
			tmpint16 = 0;
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
		if (globals.QuaternionPacketType == Q9)
			tmpint16 = (int16)(thisSV_9DOF_GBY_KALMAN.fDeltaPl * 100.0F);
#endif
		// add the data to the packet
		sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);

		// [36-35]: fAccGl[CHX] resolution 1/8192 g
		// [38-37]: fAccGl[CHY] resolution 1/8192 g
		// [40-39]: fAccGl[CHZ] resolution 1/8192 g
		for (i = CHX; i <= CHZ; i++)
		{
			// default to zero data
			ftmp = 0.0F;
#if defined COMPUTE_6DOF_GY_KALMAN
			if (globals.QuaternionPacketType == Q6AG)
				ftmp = thisSV_6DOF_GY_KALMAN.fAccGl[i] * 8192.0F;
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
			if (globals.QuaternionPacketType == Q9)
				ftmp = thisSV_9DOF_GBY_KALMAN.fAccGl[i] * 8192.0F;
#endif
			// check for clipping
			if (ftmp > 32767.0F)
				tmpint16 = 32767;
			else if (ftmp < -32768.0F)
				tmpint16 = -32768;
			else
				tmpint16 = (int16) ftmp;
			// add the data to the packet
			sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		}

		// [42-41]: fDisGl[CHX] resolution 0.01m
		// [44-43]: fDisGl[CHY] resolution 0.01m
		// [46-45]: fDisGl[CHZ] resolution 0.01m
		for (i = CHX; i <= CHZ; i++)
		{
			// default to zero data
			ftmp = 0.0F;
#if defined COMPUTE_6DOF_GY_KALMAN
			if (globals.QuaternionPacketType == Q6AG)
				ftmp = 0.0F;
#endif
#if defined COMPUTE_9DOF_GBY_KALMAN
			if (globals.QuaternionPacketType == Q9)
				ftmp = thisSV_9DOF_GBY_KALMAN.fDisGl[i] * 100.0F;
#endif
			// check for clipping
			if (ftmp > 32767.0F)
				tmpint16 = 32767;
			else if (ftmp < -32768.0F)
				tmpint16 = -32768;
			else
				tmpint16 = (int16) ftmp;
			// add the data to the packet
			sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8*)&tmpint16, 2);
		}

		// [47]: add the tail byte for the Kalman packet type 7
		sUARTOutputBuffer[iIndex++] = 0x7E;
	}

#endif // end of check for Kalman packet

	// ********************************************************************************
	// all packets have now been constructed in the output buffer so transmit over UART
	// to the Bluetooth module and over USB via the OpenSDA link.
	// this allows the same software build to support wired and wireless operation.
	// the final iIndex++ gives the number of bytes to transmit which is one more than
	// the last index in the buffer. this function is non-blocking
	// ********************************************************************************

	UART_A_SendBlock(DeviceDataPtr_A, sUARTOutputBuffer, iIndex);
	UART_B_SendBlock(DeviceDataPtr_B, sUARTOutputBuffer, iIndex);

	return;
}
