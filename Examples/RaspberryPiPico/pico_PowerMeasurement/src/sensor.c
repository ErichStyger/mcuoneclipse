/*
 * Copyright (c) 2023-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "sensor.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuINA260.h"
#include "McuSystemView.h"
#include "McuLog.h"

static uint32_t Sensor_energy_mWs;

uint32_t Sensor_GetEnergy_mWs(void) {
  return Sensor_energy_mWs;
}

static void Sensor_SetEnergy_mWs(uint32_t energy_mWs) {
  Sensor_energy_mWs = energy_mWs;
}

static void Sensor_AddEnergy_mWs(uint32_t energy_mWs) {
  Sensor_energy_mWs += energy_mWs;
}

#if PL_CONFIG_USE_SENSOR_TASK
static void sensorTask(void *pv) {
  uint32_t mW;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  Sensor_SetEnergy_mWs(0);
  for(;;) {
    mW = McuINA260_ReadPower();
    Sensor_AddEnergy_mWs(mW);
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
  }
}
#endif

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];
  uint16_t value;
  int16_t i16;

  McuShell_SendStatusStr((unsigned char*)"sensor", (unsigned char*)"sensor status\r\n", io->stdOut);
  McuUtility_Num32uToStr(buf, sizeof(buf), Sensor_GetEnergy_mWs());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" mWs\r\n");
  McuShell_SendStatusStr((unsigned char*)"  energy", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"sensor", (unsigned char*)"Group of sensor commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  reset energy", (unsigned char*)"Reset energy counter\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t Sensor_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "sensor help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "sensor status")==0)
            )
  {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "sensor reset energy")==0) {
    *handled = true;
    Sensor_SetEnergy_mWs(0);
    return ERR_OK;
  }
  return ERR_OK;
}

void Sensor_Deinit(void) {
}

void Sensor_Init(void) {
#if PL_CONFIG_USE_SENSOR_TASK
  BaseType_t res;

  res = xTaskCreate(sensorTask, "sensor", 800/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL);
  if (res!=pdPASS) {
    /* error! */
    for(;;) {}
  }
#endif
}

