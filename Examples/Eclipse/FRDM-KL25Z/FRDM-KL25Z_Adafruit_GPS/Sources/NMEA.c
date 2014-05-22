/*
 * NMEA.c
 *
 *  Created on: 20.05.2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "NMEA.h"
#include "FRTOS1.h"
#include "GPS.h"
#include "CLS1.h"

#if PL_HAS_GPS
static portTASK_FUNCTION(NmeaTask, pvParameters) {
  GPS_TComData ch;

  (void)pvParameters; /* parameter not used */
  GPS_ClearRxBuf();
  for(;;) {
    while(GPS_GetCharsInRxBuf()!=0) {
      if (GPS_RecvChar(&ch)==ERR_OK) {
        CLS1_SendChar(ch);
      }
    }
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}
#endif /* PL_HAS_GPS */

void NMEA_Init(void) {
#if PL_HAS_GPS
  if (FRTOS1_xTaskCreate(
        NmeaTask,  /* pointer to the task */
        "NMEA", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
}


