/*
 * bleuart_cmdmode.c
 *
 *  Created on: 03.01.2016
 *      Author: Erich Styger
 */

#include "Platform.h"
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
#include "bleuart_cmdmode.h"
#include "UTIL1.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "BLEAdafruit.h"
#include "CLS1.h"
#include "UTIL1.h"

#define MAX_TX_MSG_SIZE     48 /* maximum UART message length to handle */
static uint8_t txBuffer[MAX_TX_MSG_SIZE] = "";
static bool isConnected = FALSE;
static bool isEnabled = FALSE;

static void BleUartTask(void *pvParameters) {
  uint8_t buf[MAX_TX_MSG_SIZE];
  uint8_t txBuf[MAX_TX_MSG_SIZE+sizeof("[Tx] ")+sizeof("AT+BLEUARTTX=\n")];
  uint8_t res;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();
  int i;
  bool prevIsEnabled = FALSE;

  BLE_Init(); /* initialize BLE module, has to be done when interrupts are enabled */
  CLS1_SendStr("******************************************\r\n", io->stdOut);
  CLS1_SendStr("* Adafruit BLE UART CMD Mode Application *\r\n", io->stdOut);
  CLS1_SendStr("******************************************\r\n", io->stdOut);
  for(;;) {
    if (!prevIsEnabled && isEnabled) { /* enabled now */
      prevIsEnabled = TRUE;
      BLE_Echo(FALSE); /* Disable command echo from Bluefruit */
      CLS1_SendStr("Changing LED activity to MODE.\r\n", io->stdOut);
      res = BLE_SendATCommandExpectedResponse("AT+HWMODELED=1\n", buf, sizeof(buf), "OK\r\n"); /* NOTE: "=MODE" failed! */
      if (res!=ERR_OK) {
        CLS1_SendStr("Failed setting LED mode.\r\n", io->stdErr);
      }
      CLS1_SendStr("BLE UART enabled.\r\n", io->stdOut);
    } else if (prevIsEnabled && !isEnabled) { /* disabled now */
      prevIsEnabled = FALSE;
      CLS1_SendStr("BLE UART disabled.\r\n", io->stdOut);
    }
    if (isEnabled) {
      while(isEnabled && !(isConnected=BLE_IsConnected())) { /* wait until connected */
        CLS1_SendStr("Waiting for BLE UART connection...\r\n", io->stdOut);
        for(i=0;i<5 && isEnabled;i++) {
          FRTOS1_vTaskDelay(pdMS_TO_TICKS(1000));
          LED1_Neg();
        }
      }
      if (isConnected) {
        CLS1_SendStr("Connected!\r\n", io->stdOut);
      }
      while(isEnabled) { /* will break */
        isConnected=BLE_IsConnected();
        if (!isConnected) {
          CLS1_SendStr("Disconnected!\r\n", io->stdOut);
          break; /* get out of loop */
        }
        if (txBuffer[0]!='\0') { /* have something to tx */
          /* copy buffer */
          taskENTER_CRITICAL();
          UTIL1_strcpy(txBuf, sizeof(txBuf), "AT+BLEUARTTX=");
          UTIL1_strcat(txBuf, sizeof(txBuf), "[Tx] ");
          UTIL1_strcat(txBuf, sizeof(txBuf), txBuffer);
          txBuffer[0] = '\0';
          taskEXIT_CRITICAL();
          /* send tx string */
          res = BLE_SendATCommandExpectedResponse(txBuf, buf, sizeof(buf), "OK\r\n");
          if (res!=ERR_OK) {
            CLS1_SendStr("Failed to Tx string\r\n", io->stdErr);
          }
        }
        /* check Rx */
        res = BLE_SendATCommandExpectedResponse("AT+BLEUARTRX\n", buf, sizeof(buf), "OK\r\n");
        if (res==ERR_OK) {
          if (UTIL1_strncmp(buf, "OK\r\n", sizeof("OK\r\n")-1)==0) {
            /* only OK as response: no data */
          } else {
            /* print response */
            UTIL1_strCutTail(buf, "OK\r\n"); /* cut off the OK part */
            CLS1_SendStr("[Rx] ", io->stdOut);
            CLS1_SendStr(buf, io->stdOut);
          }
        }
        FRTOS1_vTaskDelay(pdMS_TO_TICKS(50));
        LED1_Neg();
      } /* while */
    } else {
      FRTOS1_vTaskDelay(pdMS_TO_TICKS(500));
      LED1_Neg();
    }
  }
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  CLS1_SendStatusStr((const unsigned char*)"uart", (unsigned char*)"\r\n", io->stdOut);
  if (isEnabled) {
    CLS1_SendStatusStr((const unsigned char*)"  enabled", (unsigned char*)"yes\r\n", io->stdOut);
  } else {
    CLS1_SendStatusStr((const unsigned char*)"  enabled", (unsigned char*)"no\r\n", io->stdOut);
  }
  if (isConnected) {
    CLS1_SendStatusStr((const unsigned char*)"  status", (unsigned char*)"connected\r\n", io->stdOut);
  } else {
    CLS1_SendStatusStr((const unsigned char*)"  status", (unsigned char*)"disconnected\r\n", io->stdOut);
  }
  return ERR_OK;
}

uint8_t BLEUART_CMDMODE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "uart help")==0) {
    CLS1_SendHelpStr((unsigned char*)"uart", (const unsigned char*)"Group of Adafruit BLE commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  enable", (unsigned char*)"Enable BLE UART\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  disable", (unsigned char*)"Disable BLE UART\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  tx <string>", (unsigned char*)"Send string\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "uart status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "uart enable")==0) {
    isEnabled = TRUE;
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, "uart disable")==0) {
    isEnabled = FALSE;
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "uart tx ", sizeof("uart tx ") - 1) == 0) {
    *handled = TRUE;
    taskENTER_CRITICAL();
    UTIL1_strcpy(txBuffer, sizeof(txBuffer), cmd+sizeof("uart tx ")-1);
    UTIL1_strcat(txBuffer, sizeof(txBuffer), "\\n\n"); /* add newline */
    taskEXIT_CRITICAL();
  }
  return res; /* no error */
}
static TaskHandle_t handle;

void BLEUART_CMDMODE_Init(void) {
  txBuffer[0] = '\0';
  isConnected = FALSE;
  isEnabled = TRUE;
  if (FRTOS1_xTaskCreate(BleUartTask, "BleUart", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, &handle) != pdPASS) {
    for(;;){} /* error */
  }
}

#endif /* PL_CONFIG_BLEUART_CMDMODE_ENABLED */
