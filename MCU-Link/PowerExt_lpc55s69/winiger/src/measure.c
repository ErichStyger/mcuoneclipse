/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "measure.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuMCP3561.h"
#include "McuGPIO.h"
#include "SpiBus.h"
#include "calibration.h"

int32_t Measure_Offset(int index, int32_t *setVal) {
  static int32_t offset[3] = {0x5C28F, 0x5C28F, 0x5C28F};  // Initialwerte

  if (setVal != NULL) {
    // Setter: kopiere alle Werte ins statische Array
    memcpy(offset, setVal, sizeof(offset));
    return 0;  // optional: Status oder Dummy-Wert zurückgeben
  }

  // Getter: gib Wert an Index zurück 
  if (index >= 0 && index < 3) {
    return offset[index];
  } else {
    return 0;  // oder ein Fehlercode
  }
}

typedef enum MEASURE_CURR_MUX_e {
  MEASURE_CURR_MUX_VREF,      /* REFIN+ */
  MEASURE_CURR_MUX_VOLTAGE,   /* CH0 */
  MEASURE_CURR_MUX_CURRENT,   /* CH1 */
} MEASURE_CURR_MUX_e;

static MEASURE_CURR_MUX_e measure_curr_mux = MEASURE_CURR_MUX_VREF; /* default: REFIN+ */
McuGPIO_Handle_t ctrl_high_current; /* N-FET, HIGH active, I2C_SCL (pin 7, blue), FC3_RTS_SCL_SSEL1, PIO0_21, pin 76 on LPC55S69JBD100 */
static bool do_measure = false; /* set to true to start measuring */

static void WaitForDataReady(void) {
  uint8_t status;
  for(;;) {
    status = MCP3561_PollStatusByte();
    if ((status&MCP3561_STATUS_BYTE_DR_STATUS)==0){ /* bit is low active: bit is zero if data is ready */
      break;
    }
    //vTaskDelay(pdMS_TO_TICKS(1)); /* wait for data ready */
  } /* for */
}

static int32_t measureVoltageRaw(void) {
  /* uses the current muxing */
  return MCP3561_ReadADCData_24Bit();
}

static int32_t muxAndMeasureDUT_VoltageRaw(void) {
  int32_t raw;
  #if SpiBus_CONFIG_USE_MUTEX
  SpiBus_Lock();
  #endif
  if (measure_curr_mux != MEASURE_CURR_MUX_VOLTAGE) {
    McuMCP3561_MuxSingleEnded_Ch0();
    vTaskDelay(pdMS_TO_TICKS(1)); /* not sure if needed, but getting wrong data otherwise */
    measure_curr_mux = MEASURE_CURR_MUX_VOLTAGE;
  }
  WaitForDataReady();
  raw = measureVoltageRaw();
  #if SpiBus_CONFIG_USE_MUTEX
  SpiBus_Unlock();
  #endif
  return raw;
}

int32_t muxAndMeasureDUT_CurrentRaw(void) {
  int32_t raw;
  #if SpiBus_CONFIG_USE_MUTEX
  SpiBus_Lock();
  #endif
  if (measure_curr_mux != MEASURE_CURR_MUX_CURRENT) {
    McuMCP3561_MuxSingleEnded_Ch1();
    vTaskDelay(pdMS_TO_TICKS(1)); /* not sure if needed, but getting wrong data otherwise */
    measure_curr_mux = MEASURE_CURR_MUX_CURRENT;
  }
  WaitForDataReady();
  raw = measureVoltageRaw();
  #if SpiBus_CONFIG_USE_MUTEX
  SpiBus_Unlock();
  #endif
  return raw;
}

static int32_t muxAndMeasureDUT_VrefRaw(void) {
  int32_t raw;
  #if SpiBus_CONFIG_USE_MUTEX
  SpiBus_Lock();
  #endif
  if (measure_curr_mux != MEASURE_CURR_MUX_VREF) {
    McuMCP3561_MuxSingleEnded_RefInPlus();
    vTaskDelay(pdMS_TO_TICKS(1)); /* not sure if needed, but getting wrong data otherwise */
    measure_curr_mux = MEASURE_CURR_MUX_VREF;
  }
  WaitForDataReady();
  raw = measureVoltageRaw();
  #if SpiBus_CONFIG_USE_MUTEX
  SpiBus_Unlock();
  #endif
  return raw;
}

int32_t convertRawVoltageToMilliVolt(int32_t adcValue) {
  int32_t mV;
  /* need to be careful not to overflow 32bits, therefore only multiply by 3 and divide by 1000 later */
  mV = (adcValue * 3 /*VREF 3V*/) / (0x7FFFFF/1000); /* 0x7FFFFF: max ADC value. */
  //mV = mV - (3000/1047*47); /*subtrahiere Referenzspannung des Instrumentenverstärkers*/
  return mV;
}

float convertRawVoltageToMicroVolt(int32_t adcValue) {
  float uV;
  /* need to be careful not to overflow 32bits, therefore only multiply by 3 and divide by 1000 later */
  uV = 3000000.0f/(0x7FFFFF) * adcValue; /* 0x7FFFFF: max ADC value. */
  //mV = mV - (3000/1047*47); /*subtrahiere Referenzspannung des Instrumentenverstärkers*/
  return uV;
}

int32_t measure(int nof) {
  /* used to benchmark multiple measurements */
  int32_t adcValue;
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SEGGER_SYSVIEW_OnUserStart(0);
#endif
if (measure_curr_mux != MEASURE_CURR_MUX_CURRENT) {
    McuMCP3561_MuxSingleEnded_Ch1();
    vTaskDelay(pdMS_TO_TICKS(1)); /* not sure if needed, but getting wrong data otherwise */
    measure_curr_mux = MEASURE_CURR_MUX_CURRENT;
  }
  do {
    WaitForDataReady();
    adcValue = measureVoltageRaw();
    nof--;
  } while(nof>0);
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SEGGER_SYSVIEW_OnUserStop(0);
#endif
  return adcValue; /* only return last value */
}

static void measureTask(void *pvParameters) {
  float adcCurrent;
  MCP3561_Configure();
  //McuMCP3561_MuxSingleEnded_Ch1(); /* set to CH1 for current measurement */
  vTaskDelay(pdMS_TO_TICKS(100)); /* wait for ADC to be ready */
  for(;;) {
    if (do_measure) {
      int32_t adcValue = measure(10);
      adcCurrent = convertRawVoltageToMicroVolt(adcValue - (Calib_Offset_Result(adcValue)));
      if(McuGPIO_IsLow(ctrl_high_current)){
        adcCurrent = adcCurrent/9.2/3;
      }else{
        adcCurrent = adcCurrent/9.2/1500;
      }
      McuLog_info("DUT Current value: %.2f uA", adcCurrent);
/*
      vTaskDelay(pdMS_TO_TICKS(200)); 
      int32_t raw, mV;
      raw = 2 * muxAndMeasureDUT_VoltageRaw();
      mV = convertRawVoltageToMilliVolt(raw);
      McuLog_info("DUT Voltage value: %d mV\n", mV);
      */
      vTaskDelay(pdMS_TO_TICKS(1000)); 
    } else {
      vTaskDelay(pdMS_TO_TICKS(50)); 
    }
  }
}

void Measurement_Noise(void){
  float adcvoltage;
  int32_t adcValue;
  float min = 3.4028235e+38f;
  float max = 0;
  MCP3561_Configure(); //McuMCP3561_MuxSingleEnded_Ch1(); /* set to CH1 for current measurement */
  McuMCP3561_MuxSingleEnded_Ch1();
  vTaskDelay(pdMS_TO_TICKS(100)); /* wait for ADC to be ready */
  for(int8_t x= 0; x < 100; x++) {
      adcValue = measure(10);
      adcvoltage = convertRawVoltageToMicroVolt(adcValue - Calib_Offset_Result(adcValue));
      if (adcvoltage < min){
        min = adcvoltage;
      }
      if (adcvoltage > max){
        max = adcvoltage;
      }
      vTaskDelay(pdMS_TO_TICKS(10)); 
    }
    if(McuGPIO_IsLow(ctrl_high_current)){
        min = min/9.2/3;
        max = max/9.2/3;
      }else{
        min = min/9.2/1500;
        max = max/9.2/1500;
      }
    McuLog_info("Min Value: %.2f uA, Max Value: %.2f uA\n", min, max);
}

  uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[64];

  McuShell_SendStatusStr((const uint8_t*)"measure", (const uint8_t*)"Measurement status\r\n", io->stdOut);

  McuGPIO_GetPinStatusString(ctrl_high_current, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  measure", do_measure?(const unsigned char*)"on\r\n":(const unsigned char*)"off\r\n", io->stdOut);
  
  McuGPIO_GetPinStatusString(ctrl_high_current, buf, sizeof(buf));
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)"\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  high_curr", (const unsigned char*)buf, io->stdOut);

  int32_t raw, mV;
  raw = muxAndMeasureDUT_VrefRaw();
  mV = convertRawVoltageToMilliVolt(raw);
  McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"0x");
	McuUtility_strcatNum24Hex(buf, sizeof(buf), raw);
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)", ");
  McuUtility_strcatNum32s(buf, sizeof(buf), mV);
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" mV\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  ADC VREF", (const unsigned char*)buf, io->stdOut);

  raw = muxAndMeasureDUT_VoltageRaw();
  mV = 2 * convertRawVoltageToMilliVolt(raw);
  McuUtility_strcpy(buf, sizeof(buf), (const unsigned char*)"0x");
	McuUtility_strcatNum24Hex(buf, sizeof(buf), raw);
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)", ");
  McuUtility_strcatNum32s(buf, sizeof(buf), mV);
  McuUtility_strcat(buf, sizeof(buf), (const unsigned char*)" mV\r\n");
  McuShell_SendStatusStr((const unsigned char*)"  ADC Voltage", (const unsigned char*)buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((const unsigned char*)"measure", (const unsigned char*)"Group of measurement commands\r\n", io->stdOut);
  McuShell_SendHelpStr((const unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((const unsigned char*)"  on|off", (const unsigned char*)"Start or stop ADC measuring\r\n", io->stdOut);
  McuShell_SendHelpStr((const unsigned char*)"  high_curr on|off", (const unsigned char*)"Set high current mode on (HIGH) or off (LOW)\r\n", io->stdOut);
  McuShell_SendHelpStr((const unsigned char*)"  noise", (const unsigned char*)"Measure Noise\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t Measure_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
	if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0 || McuUtility_strcmp((char*)cmd, "measure help")==0) {
    *handled = true;
    return PrintHelp(io);
	} else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "measure status")==0)) {
	  *handled = true;
	  return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "measure high_curr off")==0) {
    *handled = true;
    McuGPIO_SetHigh(ctrl_high_current);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "measure high_curr on")==0) {
    *handled = true;
    McuGPIO_SetLow(ctrl_high_current);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "measure on")==0) {
    *handled = true;
    do_measure = true;
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "measure off")==0) {
    *handled = true;
    do_measure = false;
    return ERR_OK;
    } else if (McuUtility_strcmp((char*)cmd, "measure noise")==0) {
    *handled = true;
    Measurement_Noise();
    return ERR_OK;
  }
	return ERR_OK;
}

void Meaure_Deinit(void) {
}
 
void Measure_Init(void) {
  if (xTaskCreate(measureTask, "measure", 2048/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }

  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);  /* get default config */
  /* crtl_high_curr: PIO0_21 */
  config.hw.gpio = GPIO;
  config.hw.port = 0;
  config.hw.pin = 21;
  config.isInput = false; /* output */
  config.isHighOnInit = false;
  ctrl_high_current = McuGPIO_InitGPIO(&config);
}
