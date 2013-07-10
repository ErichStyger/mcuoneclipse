/*
 * host.c
 *      Author: Erich Styger
 */

#include "host.h"
#include "msd_commands.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "FsMSD1.h"
#include "LEDR.h"
#include "LEDG.h"
#include "LEDB.h"

#define ONLY_HOST 0

static void print(unsigned char *str) {
#if !ONLY_HOST
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
#endif
}

static void CheckStatus(void) {
  switch (FsMSD1_GetDeviceStatus()) {
     case USB_DEVICE_IDLE:
       break;
     case USB_DEVICE_ATTACHED:
       LEDR_Off();
       LEDG_On();
       print((unsigned char*)"Mass Storage Device Attached\n" );
       break;
     case USB_DEVICE_SET_INTERFACE_STARTED:
       break;
     case USB_DEVICE_INTERFACED:
       break;
     case USB_DEVICE_DETACHED:
       LEDR_On();
       LEDG_Off();
       print((unsigned char*)"\nMass Storage Device Detached\n" );
       break;
     case USB_DEVICE_OTHER:
       break;
     default:
       print((unsigned char*)"Unknown Mass Storage Device State\n");
       break;
  } /* switch */
}

#if ONLY_HOST
static void HOST_Run(void) {
  LEDB_On();
  for(;;) {
    FsMSD1_AppTask();
    CheckStatus();
  }
}
#endif

static portTASK_FUNCTION(HostTask, pvParameters) {
  (void)pvParameters; /* not used */
  //FsMSD1_HostInit();
  for(;;) {
    FsMSD1_AppTask();
    CheckStatus();
    FRTOS1_taskYIELD();
    //FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void HOST_Init(void) {
#if ONLY_HOST
  FsMSD1_HostInit();
  HOST_Run();
#else
  FsMSD1_HostInit();
  if (FRTOS1_xTaskCreate(HostTask, (signed portCHAR *)"Host", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

