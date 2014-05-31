/**
 * \file
 * \brief GPS Data Logger Application
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the main module for the GPS data logger.
 */

#include "Platform.h"
#include "Application.h"
#include "LEDR.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"
#include "PORT_PDD.h"
#if PL_HAS_GPS
  #include "GPS.h"
  #include "NMEA.h"
  #include "TmDt1.h"
#endif

static portTASK_FUNCTION(AppTask, pvParameters) {
#if PL_HAS_GPS
  bool gotTime = FALSE;
  bool gotDate = FALSE;
  uint8_t hour, minute, second;
  uint16_t mSecond;
  uint8_t day, month;
  uint16_t year;
#endif

  (void)pvParameters; /* parameter not used */
  for(;;) {
#if PL_HAS_GPS
    if (!gotTime) {
      if (NMEA_GetTime(&hour, &minute, &second, &mSecond)==ERR_OK) {
        gotTime = TRUE;
        (void)TmDt1_SetTime(hour, minute, second, mSecond/10);
      }
    }
    if (!gotDate) {
      if (NMEA_GetDate(&day, &month, &year)==ERR_OK) {
        gotDate = TRUE;
        (void)TmDt1_SetDate(year, month, day);
      }
    }
#endif
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
#if PL_HAS_GPS
  /* GPS: pull-up on microcontroller Rx pin (PTE1) */
 // PORT_PDD_SetPinPullSelect(PORTE_BASE_PTR, 1, PORT_PDD_PULL_UP);
 // PORT_PDD_SetPinPullEnable(PORTE_BASE_PTR, 1, PORT_PDD_PULL_ENABLE);
#endif
#if PL_HAS_SD_CARD
  /* SD card: pull-up on Card Detect (PTE) is done in the GPIO_LDD component */
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_GPS
  NMEA_Init();
#endif
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

