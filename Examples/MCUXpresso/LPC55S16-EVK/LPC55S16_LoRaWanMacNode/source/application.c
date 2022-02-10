/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuShell.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "se-identity.h"
#include "secure-element-nvm.h"

#if McuLib_CONFIG_SDK_USE_FREERTOS
static void AppTask(void *pv) {
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
#endif

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[64];
  uint8_t devEUI[SE_EUI_SIZE] = LORAWAN_DEVICE_EUI;
//  uint8_t KeyValue[SE_KEY_SIZE];

  McuShell_SendStatusStr((unsigned char*)"app", (unsigned char*)"Application status\r\n", io->stdOut);

  buf[0] = '\0';
  for(int i=0; i<sizeof(devEUI); i++) {
    McuUtility_strcatNum8Hex(buf, sizeof(buf), devEUI[i]);
    McuUtility_chcat(buf, sizeof(buf), ' ');
  }
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  DevEUI", buf, io->stdOut);
#if 0
  buf[0] = '\0';
  for(int i=0; i<sizeof(devEUI); i++) {
    McuUtility_strcatNum8Hex(buf, sizeof(buf), devEUI[i]);
    McuUtility_chcat(buf, sizeof(buf), ' ');
  }
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  AppKey", buf, io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "app help") == 0)
  {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "app status")==0)
            )
  {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}

void APP_Init(void) {
#if McuLib_CONFIG_SDK_USE_FREERTOS
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      3000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
     for(;;){} /* error! probably out of memory */
  }
#endif
}


