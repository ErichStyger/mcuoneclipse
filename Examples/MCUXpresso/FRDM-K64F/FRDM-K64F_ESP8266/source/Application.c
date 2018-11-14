/*
 * Application.c
 *
 *      Author: Erich Styger
 */
#include "PE_Types.h"
#include "CLS1.h"
#include "WAIT1.h"
#include "Shell.h"
#include "UTIL1.h"
#include "ESP8266.h"
#include "LEDR.h"
#include "LEDG.h"
#include "AS2.h"

static uint8_t APP_EspMsgBuf[512]; /* buffer for messages from ESP8266 */

static uint8_t SendWebPage(uint8_t ch_id, bool ledIsOn, uint8_t temperature, const CLS1_StdIOType *io) {
  static uint8_t http[1024];
  uint8_t cmd[24], rxBuf[48], expected[48];
  uint8_t buf[16];
  uint8_t res = ERR_OK;

  /* construct web page content */
  UTIL1_strcpy(http, sizeof(http), (uint8_t*)"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n");
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"<html>\r\n<body>\r\n");
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"<title>ESP8266 Web Server</title>\r\n");
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"<h2>Web Server using ESP8266</h2>\r\n");
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"<br /><hr>\r\n");
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"<p><form method=\"POST\"><strong>Temp: <input type=\"text\" size=2 value=\"");
  UTIL1_strcatNum8s(http, sizeof(http), temperature);
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"\"> <sup>O</sup>C");
  if (ledIsOn) {
    UTIL1_strcat(http, sizeof(http), (uint8_t*)"<p><input type=\"radio\" name=\"radio\" value=\"0\" >Red LED off");
    UTIL1_strcat(http, sizeof(http), (uint8_t*)"<br><input type=\"radio\" name=\"radio\" value=\"1\" checked>Red LED on");
  } else {
    UTIL1_strcat(http, sizeof(http), (uint8_t*)"<p><input type=\"radio\" name=\"radio\" value=\"0\" checked>Red LED off");
    UTIL1_strcat(http, sizeof(http), (uint8_t*)"<br><input type=\"radio\" name=\"radio\" value=\"1\" >Red LED on");
  }
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"</strong><p><input type=\"submit\"></form></span>");
  UTIL1_strcat(http, sizeof(http), (uint8_t*)"</body>\r\n</html>\r\n");

  UTIL1_strcpy(cmd, sizeof(cmd), "AT+CIPSEND="); /* parameters are <ch_id>,<size> */
  UTIL1_strcatNum8u(cmd, sizeof(cmd), ch_id);
  UTIL1_chcat(cmd, sizeof(cmd), ',');
  UTIL1_strcatNum16u(cmd, sizeof(cmd), UTIL1_strlen(http));
  UTIL1_strcpy(expected, sizeof(expected), cmd); /* we expect the echo of our command */
  UTIL1_strcat(expected, sizeof(expected), "\r\r\n> "); /* expect "> " */
  UTIL1_strcat(cmd, sizeof(cmd), "\r\n");
  res = ESP_SendATCommand(cmd, rxBuf, sizeof(rxBuf), expected, ESP_DEFAULT_TIMEOUT_MS, io);
  if (res!=ERR_OK) {
    if (io!=NULL) {
      CLS1_SendStr("INFO: TIMEOUT, closing connection!\r\n", io->stdOut);
    }
  } else {
    if (io!=NULL) {
      CLS1_SendStr("INFO: Sending http page...\r\n", io->stdOut);
    }
    UTIL1_strcat(http, sizeof(http), "\r\n\r\n"); /* need to add this to end the command! */
    res = ESP_SendATCommand(http, NULL, 0, NULL, ESP_DEFAULT_TIMEOUT_MS, io);
    if (res!=ERR_OK) {
      CLS1_SendStr("Sending page failed!\r\n", io->stdErr); /* copy on console */
    } else {
      for(;;) { /* breaks */
        res = ESP_ReadCharsUntil(buf, sizeof(buf), '\n', 1000);
        if (res==ERR_OK) { /* line read */
          if (io!=NULL) {
            CLS1_SendStr(buf, io->stdOut); /* copy on console */
          }
        }
        if (UTIL1_strncmp(buf, "SEND OK\r\n", sizeof("SEND OK\r\n")-1)==0) { /* ok from module */
          break;
        }
      }
    }
  }
  return res;
}

static void WebProcess(void) {
  uint8_t res=ERR_OK;
  bool isGet;
  uint8_t ch_id=0;
  uint16_t size=0;
  const uint8_t *p;
  const CLS1_StdIOType *io;

  if (ESP_IsServerOn()) {
    io = CLS1_GetStdio();
    res = ESP_GetIPD(APP_EspMsgBuf, sizeof(APP_EspMsgBuf), &ch_id, &size, &isGet, 1000, io);
    if (res==ERR_OK) {
      if (isGet) { /* GET: put web page */
        res = SendWebPage(ch_id, LEDR_Get()!=FALSE, 21 /*dummy temperature*/, io);
        if (res!=ERR_OK && io!=NULL) {
          CLS1_SendStr("Sending page failed!\r\n", io->stdErr); /* copy on console */
        }
      } else { /* POST: received info */
        int pos;

        pos = UTIL1_strFind(APP_EspMsgBuf, "radio=");
        if (pos!=-1) { /* found */
          if (UTIL1_strncmp(&APP_EspMsgBuf[pos], "radio=0", sizeof("radio=0")-1)) {
            LEDR_On();
          } else if (UTIL1_strncmp(&APP_EspMsgBuf[pos], "radio=1", sizeof("radio=1")-1)) {
            LEDR_Off();
          }
        }
        res = SendWebPage(ch_id, LEDR_Get()!=FALSE, 20 /*dummy temperature*/, io);
        if (res!=ERR_OK && io!=NULL) {
          CLS1_SendStr("Sending page failed!\r\n", io->stdErr); /* copy on console */
        }
      }
      CLS1_SendStr("INFO: Closing connection...\r\n", io->stdOut);
      res = ESP_CloseConnection(ch_id, io, ESP_DEFAULT_TIMEOUT_MS);
    }
  } else { /* copy messages we receive to console */
    while (AS2_GetCharsInRxBuf()>0) {
      uint8_t ch;

      (void)AS2_RecvChar(&ch);
      CLS1_SendChar(ch);
    }
  }
}


void APP_Run(void) {
  CLS1_ConstStdIOType *io;

  WAIT1_Waitms(1000); /* wait after power-on */
  ESP_Init();
  SHELL_Init();
  io = CLS1_GetStdio();
  CLS1_SendStr("\r\n------------------------------------------\r\n", io->stdOut);
  CLS1_SendStr("ESP8266 with FRDM-K64F\r\n", io->stdOut);
  CLS1_SendStr("------------------------------------------\r\n", io->stdOut);
  CLS1_PrintPrompt(io);
  for(;;) {
    WebProcess();
    SHELL_Parse();
    WAIT1_Waitms(10);
    LEDG_Neg();
  }
}
