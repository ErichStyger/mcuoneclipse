/**
 * \file
 * \brief Application main loop.
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This implements the application main task.
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "RNET1.h"
#include "RNet_App.h"
#include "RAPP.h"
#include "SW1.h"

static void CheckKey(void) {
  uint16_t cnt;
  uint8_t data;
  
  if (SW1_GetVal()==0) { /* low active */
    WAIT1_WaitOSms(50); /* simple debounce */
    if (SW1_GetVal()==0) { /* still pressed? */
      cnt = 0;
      while(SW1_GetVal()==0) { /* wait until released */
        WAIT1_WaitOSms(10);
        cnt += 10;
      }
      if (cnt>1000) { /* long press*/
        data = 2; /* toggle LED2 */
      } else {
        data = 1; /* toggle LED1 */
      }
      (void)RAPP_SendPayloadDataBlock(&data, sizeof(data), RAPP_MSG_TYPE_DATA, RNWK_ADDR_BROADCAST, RPHY_PACKET_FLAGS_NONE);
    }
  }
}

static void AppTask(void *pvParameters) {
  uint16_t cntMs;
  
  cntMs = 0;
  for(;;) {
    if (cntMs>1000) {
      LED3_Neg();
      cntMs = 0;
    }
    CheckKey();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
    cntMs += 10;
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
