/*
 * Application.c
 *
 *  Created on: Feb 22, 2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "RNET1.h"
#include "RNet_App.h"
#include "RAPP.h"

static void AppTask(void *pvParameters) {
  uint8_t data;
  
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    data = 0x1;
    (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_DATA, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
  }
}

void APP_Run(void) {
  RNETA_Init();
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        "App", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+2,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}
