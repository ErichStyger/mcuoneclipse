/*
 * host.c
 *      Author: Erich Styger
 */

#include "host.h"
#include "msd_commands.h"
#include "CLS1.h"
#include "FRTOS1.h"
#include "FsMSD1.h"

static void print(unsigned char *str) {
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
}

static void CheckStatus(void) {
  switch (FsMSD1_GetDeviceStatus()) {
     case USB_DEVICE_IDLE:
       break;
     case USB_DEVICE_ATTACHED:
       print((unsigned char*)"Mass Storage Device Attached\n" );
       break;
     case USB_DEVICE_SET_INTERFACE_STARTED:
       break;
     case USB_DEVICE_INTERFACED:
       break;
     case USB_DEVICE_DETACHED:
       print((unsigned char*)"\nMass Storage Device Detached\n" );
       break;
     case USB_DEVICE_OTHER:
       break;
     default:
       print((unsigned char*)"Unknown Mass Storage Device State\n");
       break;
  } /* switch */
}

static portTASK_FUNCTION(HostTask, pvParameters) {
  (void)pvParameters; /* not used */
  FsMSD1_HostInit();
  for(;;) {
    FsMSD1_AppTask();
    CheckStatus();
    FRTOS1_vTaskDelay(30/portTICK_RATE_MS);
  }
}

void HOST_Init(void) {
  if (FRTOS1_xTaskCreate(HostTask, (signed portCHAR *)"Host", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

