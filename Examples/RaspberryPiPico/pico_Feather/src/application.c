/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
#endif
#include "hardware/gpio.h"
#include "McuLED.h"
#include "McuLog.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuArmTools.h"
#include "McuTimeDate.h"
#if McuRNET_CONFIG_IS_ENABLED
  #include "RNet/RApp.h"
#endif

#if !PL_CONFIG_USE_PICO_W
  #define LED_PIN   (13) /* GPIO 13, little red led on feather */
#endif

static TimerHandle_t timerHndl;

static void vTimerCallbackExpired(TimerHandle_t pxTimer) {
  McuTimeDate_AddTick();
}

static void AppTask(void *pv) {
  #define APP_HAS_ONBOARD_GREEN_LED   (0) /*(!PL_CONFIG_USE_PICO_W)*/

#if APP_HAS_ONBOARD_GREEN_LED
  /* only for pico boards which have an on-board green LED */
  McuLED_Config_t config;
  McuLED_Handle_t led;

  McuLED_GetDefaultConfig(&config);
  config.hw.pin = LED_PIN;
  config.isLowActive = false;
  led = McuLED_InitLed(&config);
  if (led==NULL) {
    McuLog_fatal("failed initializing LED");
    for(;;){}
  }
#else
  bool toggle = false;
#endif
  for(;;) {
  #if APP_HAS_ONBOARD_GREEN_LED
    McuLED_Toggle(led);
  #elif PL_CONFIG_USE_NEO_PIXEL_HW
    NEO_ClearAllPixel();
    if (toggle) {
      NEO_SetPixelColor(0, 0, 0x02);
    } else {
      NEO_SetPixelColor(0, 0, 0x0200);
    }
    toggle = !toggle;
    NEO_TransferPixels();
  #endif
    vTaskDelay(pdMS_TO_TICKS(10*100));
  }
}

#if McuRNET_CONFIG_IS_ENABLED
static void RNetTask(void *pv) {
  for(;;) {
    RAPP_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, RAPP_MSG_TYPE_DATA_ID_PRESENCE_DETECTION, 0, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}
#endif

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[48];

  McuShell_SendStatusStr((unsigned char*)"app", (const unsigned char*)"Status of application\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"1.0");
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  version", buf, io->stdOut);
  return ERR_OK;
}

uint8_t App_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "app help")==0) {
    McuShell_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = true;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "app status")==0)) {
    *handled = true;
    return PrintStatus(io);
  }
  return ERR_OK;
}

static McuGPIO_Handle_t v_aux_pin_handle;

static void v_aux_on(void) {
  McuGPIO_SetLow(v_aux_pin_handle); /* V_AUX is LOW active */
}

static void v_aux_off(void) {
  McuGPIO_SetHigh(v_aux_pin_handle); /* V_AUX is LOW active */
}

static void init_v_aux(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  config.hw.pin = 28; /* GPIO28, A2/pin 7 on feather*/
  config.isInput = false;
  config.isHighOnInit = true; /* v_aux enable is LOW active. Have it disabled at the beginning. */
  v_aux_pin_handle = McuGPIO_InitGPIO(&config);
  if (v_aux_pin_handle==NULL) {
    for(;;){}
  }
}

void App_Run(void) {
  PL_Init();
  init_v_aux(); /* default */
  v_aux_on(); /* turn power on */
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      1500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
#if McuRNET_CONFIG_IS_ENABLED
  if (xTaskCreate(
      RNetTask,  /* pointer to the task */
      "RNet", /* task name for kernel awareness debugging */
      1500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
#endif
  timerHndl = xTimerCreate(
        "timer", /* name */
        pdMS_TO_TICKS(McuTimeDate_CONFIG_TICK_TIME_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackExpired); /* callback */
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure!?! */
  }
  vTaskStartScheduler();
  for(;;) {
    /* shall not get here */
  }
  PL_Deinit();
}
