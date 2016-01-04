/*
 * bleuart_cmdmode.c
 *
 *  Created on: 03.01.2016
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_BLEUART_CMDMODE_ENABLED
#include "bleuart_cmdmode.h"
#include "UTIL1.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "BLEAdafruit.h"

static void BleUartTask(void *pvParameters) {
  uint8_t buf[32];
  uint8_t res;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();
  int i;
  bool doit = FALSE;

  FRTOS1_vTaskDelay(pdMS_TO_TICKS(2000)); /* wait so other tasks have time to write to the Shell */
  BLE_Init(); /* initialize BLE module */
  BLE_Echo(FALSE); /* Disable command echo from Bluefruit */
  CLS1_SendStr("Changing LED activity to MODE\r\n", io->stdOut);
  res = BLE_SendATCommandExpectedResponse("AT+HWMODELED=1\n", buf, sizeof(buf), "OK\r\n"); /* NOTE: "=MODE" failed! */
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed changing LED activity\r\n", io->stdErr);
  }
  CLS1_SendStr("Adafruit BLE UART CMD Mode\r\n", io->stdOut);
  for(;;) {
    while(!BLE_IsConnected()) { /* wait until connected */
      CLS1_SendStr("Waiting for BLE UART connection...\r\n", io->stdOut);
      for(i=0;i<5;i++) {
        FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
        LED1_Neg();
      }
    }
    CLS1_SendStr("Connected!\r\n", io->stdOut);
    while(BLE_IsConnected()) { /* while connected */
      if (doit) {
        /* send string */
        res = BLE_SendATCommandExpectedResponse("AT+BLEUARTTX=a\n", buf, sizeof(buf), "OK\r\n");
        res = BLE_SendATCommandExpectedResponse("AT+BLEUARTTX=hello world\\n\n", buf, sizeof(buf), "OK\r\n");
      }
      res = BLE_SendATCommandExpectedResponse("AT+BLEUARTRX\n", buf, sizeof(buf), "OK\r\n");
      if (res==ERR_OK) {
        if (UTIL1_strncmp(buf, "OK\r\n", sizeof("OK\r\n")-1)==0) {
          /* only OK as response: no data */
        } else {
          /* print response */
          UTIL1_strCutTail(buf, "OK\r\n"); /* cut off the OK part */
          CLS1_SendStr("[Recv] ", io->stdOut);
          CLS1_SendStr(buf, io->stdOut);
        }
      }
      FRTOS1_vTaskDelay(pdMS_TO_TICKS(50));
      LED1_Neg();
    }
    CLS1_SendStr("Disconnected!\r\n", io->stdOut);
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void BLEUART_CMDMODE_Init(void) {
  if (FRTOS1_xTaskCreate(BleUartTask, "BleUart", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

#endif /* PL_BLEUART_CMDMODE_ENABLED */
