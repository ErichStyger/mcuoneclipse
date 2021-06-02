/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_BLE
#include "bleuart_cmdmode.h"
#include "ble.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "McuShell.h"
#include "McuRB.h"
#include "McuLog.h"
#if PL_CONFIG_USE_BLE_MSG
  #include "bleMsg.h"
#endif

#define MAX_TX_MSG_SIZE     48 /* maximum UART message length to handle */
static McuRB_Handle_t BleRxBuffer, BleTxBuffer;
static bool isConnected = false;
static bool isEnabled = false;
uint8_t BLEUART_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

static void BLEUart_SendChar(unsigned char ch) {
  (void)McuRB_Put(BleTxBuffer, &ch);
}

static void BLEUart_ReadChar(uint8_t *cp) {
  if (McuRB_Get(BleRxBuffer, cp)==ERR_OK) {
    /* got it */
  } else {
    *cp = '\0'; /* nothing received */
  }
}

static bool BLEUart_CharPresent(void) {
  return McuRB_NofElements(BleRxBuffer)!=0;
}

McuShell_ConstStdIOType BLEUART_stdio = {
    (McuShell_StdIO_In_FctType)BLEUart_ReadChar, /* stdin */
    (McuShell_StdIO_OutErr_FctType)BLEUart_SendChar,  /* stdout */
    (McuShell_StdIO_OutErr_FctType)BLEUart_SendChar,  /* stderr */
    BLEUart_CharPresent /* if input is not empty */
  };

uint8_t BLEUart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

void BLEUart_SendString(const unsigned char *str) {
  McuLog_debug("BLE Tx: %s", str);
  while(*str!='\0') {
    BLEUart_SendChar(*str);
    str++;
  }
}

#if PL_CONFIG_USE_BLE_NEOPIXEL
static uint8_t NeoBrightness = 0;
#endif

#if PL_CONFIG_USE_BLE_NEOPIXEL
static void commandVersion(const unsigned char *buf) {
  #define NEOPIXEL_VERSION_STRING "Neopixel v2.0"
  (void)buf; /* not used */
  BLEUart_SendString((const unsigned char*)NEOPIXEL_VERSION_STRING);
}
#endif

#if PL_CONFIG_USE_BLE_NEOPIXEL
static void commandSetup(const unsigned char *buf) {
  //uint8_t width, height, stride, componentsValue, is400Hz;
  (void)buf; /* not used */
  BLEUart_SendString((const unsigned char*)"OK");
}
#endif

#if PL_CONFIG_USE_BLE_NEOPIXEL
static void commandClearColor(const unsigned char *buf) {
  (void)buf; /* not used */
  BLEUart_SendString((const unsigned char*)"OK");
}
#endif

#if PL_CONFIG_USE_BLE_NEOPIXEL
static void commandSetBrightness(const unsigned char *buf) {
  NeoBrightness = buf[1];
  BLEUart_SendString((const unsigned char*)"OK");
}
#endif

#if PL_CONFIG_USE_BLE_NEOPIXEL
static void commandSetPixel(const unsigned char *buf) {
  (void)buf; /* not used */
  BLEUart_SendString((const unsigned char*)"OK");
}
#endif

#if PL_CONFIG_USE_BLE_NEOPIXEL
static void commandImage(const unsigned char *buf) {
  (void)buf; /* not used */
  BLEUart_SendString((const unsigned char*)"OK");
}
#endif

static void BleUartTask(void *pvParameters) {
  uint8_t buf[MAX_TX_MSG_SIZE];
  uint8_t txBuf[MAX_TX_MSG_SIZE+sizeof("[Tx] ")+sizeof("AT+BLEUARTTX=\n")];
  uint8_t res;
  int i;
  bool prevIsEnabled = FALSE;

  McuLog_trace("Starting BleUart Task");
  vTaskDelay(pdMS_TO_TICKS(2000)); /* give module time to power up */
  BLE_Init(); /* initialize BLE module, has to be done when interrupts are enabled */
  for(;;) {
    if (!prevIsEnabled && isEnabled) { /* enabled now */
      prevIsEnabled = TRUE;
      BLE_Echo(FALSE); /* Disable command echo from Bluefruit */
      McuLog_info("BLE: Changing LED activity to MODE.");
      res = BLE_SendATCommandExpectedResponse((unsigned char*)"AT+HWMODELED=1\n", buf, sizeof(buf), (unsigned char*)"OK\r\n"); /* NOTE: "=MODE" failed! */
      if (res!=ERR_OK) {
        McuLog_error("BLE: Failed setting LED mode.");
      }
      McuLog_info("BLE UART enabled.");
    } else if (prevIsEnabled && !isEnabled) { /* disabled now */
      prevIsEnabled = FALSE;
      McuLog_info("BLE UART disabled.");
    }
    if (isEnabled) {
      while(isEnabled && !(isConnected=BLE_IsConnected())) { /* wait until connected */
        /* McuShell_SendStr((unsigned char*)"Waiting for BLE UART connection...\r\n", io->stdOut); */
        for(i=0;i<2 && isEnabled;i++) {
          vTaskDelay(pdMS_TO_TICKS(1000));
        }
      }
      if (isConnected) {
        McuLog_info("BLE Connected!");
      }
      while(isEnabled) { /* will break */
        if (McuRB_NofElements(BleTxBuffer)!=0) { /* have something to tx */
          int i;
          unsigned char ch;

          /* copy data from ring buffer to output buffer */
          McuUtility_strcpy(txBuf, sizeof(txBuf), (unsigned char*)"AT+BLEUARTTX=");
          i = 0;
          while(i<sizeof(txBuf) && i<MAX_TX_MSG_SIZE-3) { /* -1 because \n needs to be sent as '\' 'n' plus '\n' at the end needed */
            res = McuRB_Get(BleTxBuffer, &ch);
            if (res!=ERR_OK) {
              break;
            }
            if (ch=='\n') { /* do not send line end */
              McuUtility_chcat(txBuf, sizeof(txBuf), '\\');
              i++;
              McuUtility_chcat(txBuf, sizeof(txBuf), 'n');
              i++;
            } else if (ch=='\r') { /* skip */
              i++;
            } else {
              McuUtility_chcat(txBuf, sizeof(txBuf), ch);
              i++;
            }
          }
          if (i>0) {
            /* send tx string */
            McuUtility_chcat(txBuf, sizeof(txBuf), '\n');
            res = BLE_SendATCommandExpectedResponse(txBuf, buf, sizeof(buf), (unsigned char*)"OK\r\n");
            if (res!=ERR_OK) {
              McuLog_error("Failed to Tx string");
            }
          }
        } /* something to tx */
        /* check Rx */
        res = BLE_SendATCommandExpectedResponse((unsigned char*)"AT+BLEUARTRX\n", buf, sizeof(buf), (unsigned char*)"OK\r\n");
        if (res==ERR_OK) {
          if (McuUtility_strncmp((char*)buf, (char*)"OK\r\n", sizeof("OK\r\n")-1)==0) {
            /* only OK as response: no data */
            if (McuRB_NofElements(BleTxBuffer)==0) {
              vTaskDelay(pdMS_TO_TICKS(1000)); /* nothing to send and nothing received: give back more CPU time */
            }
          } else {
            /* print response */
            McuUtility_strCutTail(buf, (unsigned char*)"OK\r\n"); /* cut off the OK part */
        #if PL_CONFIG_USE_BLE_MSG
            McuLog_debug("BLE Rx: %s", buf);
            if (buf[0]=='!') { /* special callback */
              BLEMSG_RxCallback(buf);
#if PL_CONFIG_USE_BLE_NEOPIXEL
            /* see https://github.com/adafruit/Adafruit_BluefruitLE_nRF51/blob/master/examples/neopixel/neopixel.ino */
            } else if (buf[0]=='V') {
              commandVersion(buf);
            } else if (buf[0]=='S') {
              commandSetup(buf);
            } else if (buf[0]=='C') {
              commandClearColor(buf);
            } else if (buf[0]=='B') {
              commandSetBrightness(buf);
            } else if (buf[0]=='P') {
              commandSetPixel(buf);
            } else if (buf[0]=='I') {
              commandImage(buf);
#endif
            } else {
              McuRB_Putn(BleRxBuffer, buf, strlen((char*)buf)); /* pass to the shell parser */
            }
        #else
            McuRB_Putn(BleRxBuffer, buf, strlen((char*)buf)); /* pass to the shell parser */
        #endif
          }
        }
        isConnected=BLE_IsConnected();
        if (!isConnected) {
          McuLog_info("BLE disconnected.");
          break; /* get out of loop */
        }
        vTaskDelay(pdMS_TO_TICKS(50));
      } /* while */
    } else {
      vTaskDelay(pdMS_TO_TICKS(1000));
    } /* if isEnabled */
  } /* for */
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  McuShell_SendStatusStr((const unsigned char*)"bleuart", (unsigned char*)"BLE UART status\r\n", io->stdOut);
  if (isEnabled) {
    McuShell_SendStatusStr((const unsigned char*)"  enabled", (unsigned char*)"yes\r\n", io->stdOut);
  } else {
    McuShell_SendStatusStr((const unsigned char*)"  enabled", (unsigned char*)"no\r\n", io->stdOut);
  }
  if (isConnected) {
    McuShell_SendStatusStr((const unsigned char*)"  status", (unsigned char*)"connected\r\n", io->stdOut);
  } else {
    McuShell_SendStatusStr((const unsigned char*)"  status", (unsigned char*)"disconnected\r\n", io->stdOut);
  }
  return ERR_OK;
}

uint8_t BLEUART_CMDMODE_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "bleuart help")==0) {
    McuShell_SendHelpStr((unsigned char*)"bleuart", (const unsigned char*)"Group of Adafruit BLE UART commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  enable", (unsigned char*)"Enable BLE UART\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  disable", (unsigned char*)"Disable BLE UART\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  tx <string>", (unsigned char*)"Send string\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "bleuart status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "bleuart enable")==0) {
    isEnabled = TRUE;
    *handled = TRUE;
  } else if (McuUtility_strcmp((char*)cmd, "bleuart disable")==0) {
    isEnabled = FALSE;
    *handled = TRUE;
  } else if (McuUtility_strncmp((char*)cmd, "bleuart tx ", sizeof("bleuart tx ") - 1) == 0) {
    *handled = TRUE;
    McuRB_Putn(BleTxBuffer, (void*)(cmd+sizeof("bleuart tx ")-1), strlen((char*)(cmd+sizeof("bleuart tx ")-1)));
    McuRB_Putn(BleTxBuffer, (unsigned char*)"\\n\n", sizeof("\\n\n")-1);
  }
  return res; /* no error */
}

void BLEUART_CMDMODE_Init(void) {
  McuRB_Config_t rbConfig;

  McuRB_GetDefaultconfig(&rbConfig);
  rbConfig.nofElements = 64;
  BleRxBuffer = McuRB_InitRB(&rbConfig);
  rbConfig.nofElements = 1024;
  BleTxBuffer = McuRB_InitRB(&rbConfig);

  isConnected = FALSE;
  isEnabled = true;
  if (xTaskCreate(BleUartTask, "BleUart", 1000/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    McuLog_fatal("Failed creating BleUart task.");
    for(;;){} /* error */
  }
}

#endif /* PL_CONFIG_BLEUART_CMDMODE_ENABLED */
