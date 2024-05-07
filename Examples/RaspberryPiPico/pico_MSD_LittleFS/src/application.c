/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#include "hardware/gpio.h"
#include "McuLED.h"
#include "McuLog.h"
#include "McuWait.h"
#include "McuUtility.h"
#include "McuArmTools.h"
#include "McuTimeDate.h"
#if PL_CONFIG_USE_USB_CDC
  /* needed for USB CDC: */
  #include <stdio.h>
  #include "pico/stdlib.h"
#endif
#if PL_CONFIG_USE_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
#endif
#if PL_CONFIG_USE_TINY_USB
  #include <tusb.h>
#endif
#if PL_CONFIG_USE_MININI
  #include "MinIniKeys.h"
  #include "McuMinINI.h"
#endif

static uint32_t led_delay_ms = NVMC_MININI_KEY_LED_DELAY_MS_DEFAULT;

#if PL_CONFIG_USE_LITTLE_FS

static TaskHandle_t usbTask; /* task handle to resume USB task */

static void mount_and_format_if_necessary(bool force_format) {
  #define README_TXT \
    "Raspberry Pi Pico littlefs USB Flash Memory Interface.\n"

  McuLog_info("Mounting litteFS volume.");
  if (force_format || McuLFS_Mount(McuShell_GetStdio())!=ERR_OK) {
    McuLog_info("Format the onboard flash memory with littlefs");

    if (McuLFS_Format(McuShell_GetStdio())!=ERR_OK) {
      McuLog_error("Format failed");
    }
    if (McuLFS_Mount(McuShell_GetStdio())!=ERR_OK) {
      McuLog_error("Mount failed");
    }
    /* create default file */
    lfs_file_t f;
    if (McuLFS_openFile(&f, "README.TXT")!=ERR_OK) {
      McuLog_error("Creating readme failed");
    }
    if (lfs_file_write(McuLFS_get_lfs(), &f, README_TXT, strlen(README_TXT))!=0) {
      McuLog_error("Writing text failed");
    }
    if (McuLFS_closeFile(&f)!=ERR_OK) {
      McuLog_error("Closing file failed");
    }
  }
}
#endif

static void AppTask(void *pv) {
  #define APP_HAS_ONBOARD_GREEN_LED   (1)

#if APP_HAS_ONBOARD_GREEN_LED
  /* only for pico boards which have an on-board green LED */
  McuLED_Config_t config;
  McuLED_Handle_t led;
  #define LED_PIN   (25) /* GPIO 25 */

  McuLED_GetDefaultConfig(&config);
  config.hw.pin = LED_PIN;
  config.isLowActive = false;
  led = McuLED_InitLed(&config);
  if (led==NULL) {
    McuLog_fatal("failed initializing LED");
    for(;;){}
  }
#endif

#if PL_CONFIG_USE_LITTLE_FS
  mount_and_format_if_necessary(false);
#endif
#if PL_CONFIG_USE_TINY_USB
  vTaskResume(usbTask); /* resume USB task */
#endif
#if PL_CONFIG_USE_MININI
  led_delay_ms = McuMinINI_ini_getl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_DELAY_MS, NVMC_MININI_KEY_LED_DELAY_MS_DEFAULT, NVMC_MININI_FILE_NAME);
#else
  led_delay_ms = NVMC_MININI_KEY_LED_DELAY_MS_DEFAULT;
#endif
  for(;;) {
  #if APP_HAS_ONBOARD_GREEN_LED
    McuLED_Toggle(led);
  #endif
    vTaskDelay(pdMS_TO_TICKS(led_delay_ms));
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[48];

  McuShell_SendStatusStr((unsigned char*)"app", (const unsigned char*)"Status of application\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)APP_VERSION_STR);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  version", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), led_delay_ms);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ms\r\n");
  McuShell_SendStatusStr((uint8_t*)"  led delay", buf, io->stdOut);
  return ERR_OK;
}

uint8_t App_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint32_t value;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "app help")==0) {
    McuShell_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  led delay <ms>", (const unsigned char*)"Set LED delay in ms\r\n", io->stdOut);
    *handled = true;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "app status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "app led delay ", sizeof("app led delay ")-1)==0) {
    *handled = true;
    p = cmd + sizeof("app led delay ")-1;
    if (McuUtility_ScanDecimal32uNumber(&p, &led_delay_ms)!=ERR_OK) {
      return ERR_FAILED;
    }
    #if PL_CONFIG_USE_MININI
    McuMinINI_ini_putl(NVMC_MININI_SECTION_LED, NVMC_MININI_KEY_LED_DELAY_MS, led_delay_ms, NVMC_MININI_FILE_NAME);
    #endif
    return ERR_OK;
  }
  return ERR_OK;
}

#if PL_CONFIG_USE_TINY_USB
static void tinyUSBTask(void*pv) {
  vTaskSuspend(NULL); /* gets resumed by application task */
  for(;;) {
    tud_task();
    vTaskDelay(pdMS_TO_TICKS(2));
  }
}
#endif

void APP_Run(void) {
  PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      4096/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }

  #if PL_CONFIG_USE_TINY_USB
  if (xTaskCreate(
        tinyUSBTask,  /* pointer to the task */
        "tinyUSB", /* task name for kernel awareness debugging */
        8192/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        &usbTask /* optional task handle to create */
      ) != pdPASS)
    {
      McuLog_fatal("failed creating task");
      for(;;){} /* error! probably out of memory */
    }
  #endif

  vTaskStartScheduler();
  for(;;) {
    /* shall not get here */
  }
}
