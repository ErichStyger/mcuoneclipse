/**
 * \file
 * \brief Application module
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This is the implementation of the application.
 */
#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "EVNT1.h"
#include "Shell.h"
#include "FX1.h"

void APP_HandleEvent(uint8_t event) {
  switch(event) {
    case EVNT1_KEY1_PRESSED:
      CLS1_SendStr((unsigned char*)"KEY1 pressed!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_RELEASED:
      CLS1_SendStr((unsigned char*)"KEY1 released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    case EVNT1_KEY1_LONG_RELEASED:
      CLS1_SendStr((unsigned char*)"KEY1 long released!\r\n", CLS1_GetStdio()->stdOut);
      break;
    default:
      break;
  }
}

static void AppTask(void *pvParameters) {
  FX1_Init();
  for(;;) {
    EVNT1_HandleEvent();
    LED1_Neg();
    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Run(void) {
  /* some hardware test... */
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  CLS1_SendStr((unsigned char*)"Hello\r\n", CLS1_GetStdio()->stdOut);
  LED1_Neg();
  LED2_Neg();
  LED3_Neg();
  
  /* now start the application */
  SHELL_Init();
  if (FRTOS1_xTaskCreate(
        AppTask,  /* pointer to the task */
        (signed char *)"App", /* task name for kernel awareness debugging */
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
