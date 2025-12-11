/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "calibration.h"
#include "measure.h"
#include "McuGPIO.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "McuMCP3561.h"

static McuGPIO_Handle_t cal_0;  /* N-FET, HIGH active, I2C_SDA (pin 6, green), FC3_CTS_SDA_SSEL0, PIO0_4, pin 86 on LPC55S69JBD100 */
static McuGPIO_Handle_t cal_1;  /* N-FET, HIGH active, SYNC_TRIG (pin 10, white), PIO0_6, pin 89 on LPC55S69JBD100 */
static McuGPIO_Handle_t cal_en; /* N-FET, HIGH active, UART_OUT (pin 9, gray), FC0-UART-TXD (VCOM, target RXD), PIO0_25, pin 89 on LPC55S69JBD100 */

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];

  McuShell_SendStatusStr((unsigned char*)"calib", (unsigned char*)"Calibration pin status\r\n", io->stdOut);
  McuGPIO_GetPinStatusString(cal_0, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  cal_0", (const unsigned char*)buf, io->stdOut);

  McuGPIO_GetPinStatusString(cal_1, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  cal_1", (const unsigned char*)buf, io->stdOut);

  McuGPIO_GetPinStatusString(cal_en, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  cal_en", (const unsigned char*)buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"calib", (unsigned char*)"Group of calibration commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  cal_0 on|off", (unsigned char*)"Turn calibration resistor 0 on (HIGH) or off (LOW)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  cal_1 on|off", (unsigned char*)"Turn calibration resistor 1 on (HIGH) or off (LOW)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  cal_en on|off", (unsigned char*)"Turn calibration on (HIGH) or off (LOW)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  start", (unsigned char*)"Start Calibration\r\n", io->stdOut);
  return ERR_OK;
}

void Calibration_Start(void) {
    int32_t calib_volt[3] = {0};

    McuGPIO_SetHigh(cal_en);
    McuGPIO_SetLow(cal_0);
    McuGPIO_SetLow(cal_1);
    McuGPIO_SetHigh(ctrl_high_current);
    vTaskDelay(pdMS_TO_TICKS(200)); 
    calib_volt[0] = muxAndMeasureDUT_CurrentRaw(); //Measured Value

    McuGPIO_SetHigh(cal_0);
    vTaskDelay(pdMS_TO_TICKS(200)); 
    calib_volt[1] = (muxAndMeasureDUT_CurrentRaw() - 0x25953E); //Measured Value - Calculated Value  (0x7FFFFF/47000*1500*9.2) = 0x25953E

    McuGPIO_SetLow(cal_0);
    McuGPIO_SetLow(ctrl_high_current);
    McuGPIO_SetHigh(cal_1);
    vTaskDelay(pdMS_TO_TICKS(200)); 
    calib_volt[2] = (muxAndMeasureDUT_CurrentRaw() - 0xD159E); //Measured Value - Calculated Value - (0x7FFFFF/270*3*9.2) = 0xD159E

    McuGPIO_SetLow(cal_en);
    McuGPIO_SetLow(cal_0);
    McuGPIO_SetLow(cal_1);
    McuGPIO_SetLow(ctrl_high_current);

    Measure_Offset(0, calib_volt);
}

int32_t Calib_Offset_Result(int32_t adc_value) {
  if (adc_value < 0x61A80)
    return Measure_Offset(0, NULL);
  else if(McuGPIO_IsLow(ctrl_high_current)){
    return Measure_Offset(2, NULL);
  }else{
    return Measure_Offset(1, NULL);
  }
}


uint8_t Calibration_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
	if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0 || McuUtility_strcmp((char*)cmd, "calib help")==0) {
    *handled = true;
    return PrintHelp(io);
	} else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "calib status")==0)) {
	  *handled = true;
	  return PrintStatus(io);
	} else if (McuUtility_strcmp((char*)cmd, "calib cal_0 on")==0) {
	  *handled = true;
	  McuGPIO_SetHigh(cal_0);
    return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "calib cal_0 off")==0) {
	  *handled = true;
	  McuGPIO_SetLow(cal_0);
    return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "calib cal_1 on")==0) {
	  *handled = true;
	  McuGPIO_SetHigh(cal_1);
    return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "calib cal_1 off")==0) {
	  *handled = true;
	  McuGPIO_SetLow(cal_1);
    return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "calib cal_en on")==0) {
	  *handled = true;
	  McuGPIO_SetHigh(cal_en);
    return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "calib cal_en off")==0) {
	  *handled = true;
	  McuGPIO_SetLow(cal_en);
    return ERR_OK;
	} else if (McuUtility_strcmp((char*)cmd, "calib start")==0) {
	  *handled = true;
    Calibration_Start();
    return ERR_OK;
	}
	return ERR_OK;
}

void Calibration_Deinit(void) {
  cal_0 = McuGPIO_DeinitGPIO(cal_0);
  cal_1 = McuGPIO_DeinitGPIO(cal_1);
  cal_en = McuGPIO_DeinitGPIO(cal_en);
}

void Calibration_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);  /* get default config */

  /* cal_0: PIO0_4 */
  config.hw.gpio = GPIO;
  config.hw.port = 0;
  config.hw.pin = 4;
  config.isInput = false; /* output */
  config.isHighOnInit = false;
  cal_0 = McuGPIO_InitGPIO(&config);

  /* cal_1: PIO0_6 */
  config.hw.gpio = GPIO;
  config.hw.port = 0;
  config.hw.pin = 6;
  config.isInput = false; /* output */
  config.isHighOnInit = false;
  cal_1 = McuGPIO_InitGPIO(&config);

  /* cal_en: PIO0_25 */
  config.hw.gpio = GPIO;
  config.hw.port = 0;
  config.hw.pin = 25;
  config.isInput = false; /* output */
  config.isHighOnInit = false;
  cal_en = McuGPIO_InitGPIO(&config);
}