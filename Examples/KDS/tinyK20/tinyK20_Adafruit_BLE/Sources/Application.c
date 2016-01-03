/*
 * Application.c
 *
 *  Created on: 27.12.2015
 *      Author: Erich Styger
 */

#include "Application.h"
#include "SM1.h"
#include "WAIT1.h"
#include "LED1.h"
#include "AdaBLE.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "CLS1.h"

static void ble_uart_cmdmode(void) {
  uint8_t buf[64];
  uint8_t res;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  CLS1_SendStr("Adafruit BLE UART CMD Mode\r\n", io->stdOut);
  BLE_Echo(FALSE); /* Disable command echo from Bluefruit */
  while(!BLE_IsConnected()) { /* wait until connected */
    CLS1_SendStr("Waiting for connection...\r\n", io->stdOut);
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
  }
  CLS1_SendStr("Connected\r\n", io->stdOut);
  //CLS1_SendStr("Changing LED activity\r\n", io->stdOut);
  while(BLE_IsConnected()) { /* while connected */
#if 0
    ble.println("AT+BLEUARTRX");
    ble.readline();
    if (strcmp(ble.buffer, "OK") == 0) {
      // no data
      return;
    }
    // Some data was found, its in the buffer
    Serial.print(F("[Recv] ")); Serial.println(ble.buffer);
    ble.waitForOK();
#endif
    res = BLE_SendATCommandExpectedResponse("AT+BLEUARTRX", buf, sizeof(buf), "OK\r\n");
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
  }
  CLS1_SendStr("Disconnected!\r\n", io->stdOut);
}

static void AppTask(void *pvParameters) {
  BLE_Init(); /* initialize BLE module */
#if 0
  SYS1_Print("Starting BLE application\r\n");
  SYS1_PrintfHost("status 1:%d\r\n", 35);
  SYS1_PrintfTarget("status 2:%d\r\n", 38);
  SYS1_Warn("Warning: BLE module not connected\r\n");
  SYS1_WarnfHost("BLE status 1:%d\r\n", 15);
  SYS1_WarnfTarget("BLE status 2:%d\r\n", 33);
  SYS1_Error("Error: BLE IRQ is high\r\n");
  SYS1_ErrorfHost("BLE IRQ:%d\r\n", 444);
  SYS1_ErrorfTarget("BLE IRQ:%d\r\n", 103);
#endif
  FRTOS1_vTaskDelay(pdMS_TO_TICKS(2000)); /* wait so other tasks have time to write to the Shell */
  ble_uart_cmdmode();
  for(;;) {
    LED1_Neg();
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  SHELL_Init();
  if (FRTOS1_xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  vTaskStartScheduler();
}
