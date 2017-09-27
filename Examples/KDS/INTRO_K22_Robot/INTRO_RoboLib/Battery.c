/**
 * \file
 * \brief Module for the battery management.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Deals with the robot battery.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_BATTERY_ADC
#include "Battery.h"
#include "ADC_Bat.h"
#include "CLS1.h"
#include "FRTOS1.h"

uint8_t BATT_MeasureBatteryVoltage(uint16_t *cvP) {
  #define SAMPLE_GROUP_SIZE 1U
  ADC_Bat_TResultData results[SAMPLE_GROUP_SIZE]={0};
  LDD_ADC_TSample SampleGroup[SAMPLE_GROUP_SIZE];
  uint32_t milliVolts;
#define BAT_V_DIVIDER_UP   62 /* voltage divider pull-up */
#define BAT_V_DIVIDER_DOWN 30 /* voltage divider pull-down */

  *cvP = 0; /* init */
  SampleGroup[0].ChannelIdx = 0U;  /* Create one-sample group */
  if (ADC_Bat_CreateSampleGroup(ADC_Bat_DeviceData, (LDD_ADC_TSample *)SampleGroup, SAMPLE_GROUP_SIZE)!=ERR_OK) {  /* Set created sample group */
    return ERR_FAILED;
  }
  if (ADC_Bat_StartSingleMeasurement(ADC_Bat_DeviceData)!=ERR_OK) {
    return ERR_FAILED;
  }
  while(!ADC_Bat_GetMeasurementCompleteStatus(ADC_Bat_DeviceData)) {
    vTaskDelay(pdMS_TO_TICKS(1)); /* wait */
  }
  if (ADC_Bat_GetMeasuredValues(ADC_Bat_DeviceData, &results[0])!=ERR_OK) {
    return ERR_FAILED;
  }
  /* reference voltage is 3.3V. Battry Voltage is using a voltage divider (R29, 62KOhm pullup to VBat, R30 30kOhm pull down to GND) */
  milliVolts = results[0]*330*(BAT_V_DIVIDER_UP+BAT_V_DIVIDER_DOWN)/BAT_V_DIVIDER_DOWN/0xffff; /* scale it to centi-volt. Do multiplication first to avoid numerical issues */
  *cvP = milliVolts;
  return ERR_OK;
}

static uint8_t BATT_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  uint16_t cv;

  CLS1_SendStatusStr((unsigned char*)"battery", (unsigned char*)"\r\n", io->stdOut);
  buf[0] = '\0';
  if (BATT_MeasureBatteryVoltage(&cv)==ERR_OK) {
    UTIL1_strcatNum32sDotValue100(buf, sizeof(buf), cv);
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)" V\r\n");
  } else {
    UTIL1_strcat(buf, sizeof(buf), (uint8_t*)"ERROR\r\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  Battery", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"battery", (unsigned char*)"Group of battery commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t BATT_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"battery help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"battery status")==0) {
    *handled = TRUE;
    return BATT_PrintStatus(io);
  }
  return res;
}


void BATT_Init(void){
}

void BATT_Deinit(void) {
}

#endif /* PL_CONFIG_HAS_BATTERY_ADC */
