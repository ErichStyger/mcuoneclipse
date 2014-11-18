/*
 * ESP8266.c
 *
 *  Created on: 16.11.2014
 *      Author: tastyger
 */

#include "ESP8266.h"
#include "Shell.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "AS2.h"
#include "WAIT1.h"

#define ESP_DEFAULT_TIMEOUT_MS    (100)

static void Send(unsigned char *str) {
  while(*str!='\0') {
    AS2_SendChar(*str);
    str++;
  }
}

static uint8_t ReadCharsUntil(uint8_t *buf, size_t bufSize, uint8_t sentinelChar, uint16_t timeoutMs) {
  uint8_t ch;
  uint8_t res = ERR_OK;

  if (bufSize<=1) {
    return ERR_OVERRUN; /* buffer to small */
  }
  buf[bufSize-1] = '\0'; /* always terminate */
  bufSize--;
  for(;;) { /* breaks */
    if (bufSize==0) {
      res = ERR_OVERRUN;
      break;
    }
    if (AS2_GetCharsInRxBuf()>0) {
      (void)AS2_RecvChar(&ch);
      *buf = ch;
      buf++;
      bufSize--;
      if (ch==sentinelChar) {
        *buf = '\0'; /* terminate string */
        break; /* sentinel found */
      }
    } else {
      if (timeoutMs>10) {
        WAIT1_WaitOSms(10);
        timeoutMs -= 10;
      } else {
        res = ERR_IDLE; /* timeout */
        break;
      }
    }
  }
  return res;
}

static uint8_t RxResponse(unsigned char *rxBuf, size_t rxBufLength, unsigned char *expectedTail, uint16_t msTimeout) {
  unsigned char ch;
  uint8_t res = ERR_OK;
  unsigned char *p;

  if (rxBufLength < sizeof("x\r\n")) {
    return ERR_OVERFLOW; /* not enough space in buffer */
  }
  p = rxBuf;
  p[0] = '\0';
  for(;;) { /* breaks */
    if (msTimeout == 0) {
      break; /* will decide outside of loop if it is a timeout. */
    } else if (rxBufLength == 0) {
      res = ERR_OVERFLOW; /* not enough space in buffer */
      break;
    } else if (AS2_GetCharsInRxBuf() > 0) {
#if 0
      if (AS2_RecvChar(&ch) != ERR_OK) {
        res = ERR_RXEMPTY;
        break;
      }
#else
      /* might get an overrun OVERRUN_ERR error here? Ignoring error for now */
      (void)AS2_RecvChar(&ch);
#endif
      *p++ = ch;
      *p = '\0'; /* always terminate */
      rxBufLength--;
    } else if (expectedTail!=NULL && expectedTail[0]!='\0'
          && UTIL1_strtailcmp(rxBuf, expectedTail) == 0) {
      break; /* finished */
    } else {
      WAIT1_WaitOSms(1);
      msTimeout--;
    }
  } /* for */
  if (msTimeout==0) { /* timeout! */
    if (expectedTail[0] != '\0' /* timeout, and we expected something: an error for sure */
        || rxBuf[0] == '\0' /* timeout, did not know what to expect, but received nothing? There has to be a response. */
       )
    {
      res = ERR_FAULT;
    }
  }
  return res;
}

uint8_t ESP_SendATCommand(uint8_t *cmd, uint8_t *rxBuf, size_t rxBufSize, uint8_t *expectedTailStr, uint16_t msTimeout) {
  uint16_t snt;
  uint8_t res;

  rxBuf[0] = '\0';
  if (AS2_SendBlock(cmd, (uint16_t)UTIL1_strlen((char*)cmd), &snt) != ERR_OK) {
    return ERR_FAILED;
  }
  res = RxResponse(rxBuf, rxBufSize, expectedTailStr, msTimeout);
  return res;
}

uint8_t ESP_Test(void) {
  /* AT */
  uint8_t rxBuf[sizeof("AT\r\r\n\r\nOK\r\n")];
  uint8_t res;

  res = ESP_SendATCommand("AT\r\n", rxBuf, sizeof(rxBuf), "AT\r\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS);
  return res;
}

uint8_t ESP_Restart(const CLS1_StdIOType *io, uint16_t timeoutMs) {
  /* AT+RST */
  uint8_t rxBuf[sizeof("AT+RST\r\r\n\r\nOK\r\n")];
  uint8_t res;
  uint8_t buf[64];

  AS2_ClearRxBuf(); /* clear buffer */
  res = ESP_SendATCommand("AT+RST\r\n", rxBuf, sizeof(rxBuf), "AT+RST\r\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS);
  if (res==ERR_OK) {
    for(;;) {
      ReadCharsUntil(buf, sizeof(buf), '\n', 1000);
      if (io!=NULL) {
        CLS1_SendStr(buf, io->stdOut);
      }
      if (UTIL1_strncmp(buf, "ready", sizeof("ready")-1)==0) { /* wait until ready message from module */
        break; /* module has restarted */
      }
    }
  }
  AS2_ClearRxBuf(); /* clear buffer */
  return res;
}

uint8_t ESP_SelectWiFiMode(uint8_t mode) {
  /* AT+CWMODE=<mode>, where <mode> is 1=Sta, 2=AP or 3=both */
  uint8_t txBuf[sizeof("AT+CWMODE=x\r\n")];
  uint8_t rxBuf[sizeof("AT+CWMODE=x\r\r\nno change\r\n")];
  uint8_t expected[sizeof("AT+CWMODE=x\r\r\nno change\r\n")];
  uint8_t res;

  if (mode<1 || mode>3) {
    return ERR_RANGE; /* only 1, 2 or 3 */
  }
  UTIL1_strcpy(txBuf, sizeof(txBuf), "AT+CWMODE=");
  UTIL1_strcatNum16u(txBuf, sizeof(txBuf), mode);
  UTIL1_strcat(txBuf, sizeof(txBuf), "\r\n");
  UTIL1_strcpy(expected, sizeof(expected), "AT+CWMODE=");
  UTIL1_strcatNum16u(expected, sizeof(expected), mode);
  UTIL1_strcat(expected, sizeof(expected), "\r\r\n\n");
  res = ESP_SendATCommand(txBuf, rxBuf, sizeof(rxBuf), expected, ESP_DEFAULT_TIMEOUT_MS);
  if (res!=ERR_OK) {
    /* answer could be as well "AT+CWMODE=x\r\r\nno change\r\n"!! */
    UTIL1_strcpy(txBuf, sizeof(txBuf), "AT+CWMODE=");
    UTIL1_strcatNum16u(txBuf, sizeof(txBuf), mode);
    UTIL1_strcat(txBuf, sizeof(txBuf), "\r\n");
    UTIL1_strcpy(expected, sizeof(expected), "AT+CWMODE=");
    UTIL1_strcatNum16u(expected, sizeof(expected), mode);
    UTIL1_strcat(expected, sizeof(expected), "\r\r\nno change\r\n");
    if (UTIL1_strcmp(rxBuf, expected)==0) {
      res = ERR_OK;
    }
  }
  return res;
}

uint8_t ESP_GetFirmwareString(uint8_t *fwBuf, size_t fwBufSize) {
  /* AT+GMR */
  uint8_t rxBuf[32];
  uint8_t res;
  const unsigned char *p;

  res = ESP_SendATCommand("AT+GMR\r\n", rxBuf, sizeof(rxBuf), "\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS);
  if (res!=ERR_OK) {
    if (UTIL1_strtailcmp(rxBuf, "\r\n\r\nOK\r\n")) {
      res = ERR_OK;
    }
  }
  if (res==ERR_OK) {
    if (UTIL1_strncmp(rxBuf, "AT+GMR\r\r\n", sizeof("AT+GMR\r\r\n")-1)==0) { /* check for beginning of response */
      UTIL1_strCutTail(rxBuf, "\r\n\r\nOK\r\n"); /* cut tailing response */
      p = rxBuf+sizeof("AT+GMR\r\r\n")-1;  /* skip beginning */
      UTIL1_strcpy(fwBuf, fwBufSize, p); /* copy firmware information string */
    } else {
      res = ERR_FAILED;
    }
  }
  if (res!=ERR_OK) {
    UTIL1_strcpy(fwBuf, fwBufSize, "ERROR"); /* default error */
  }
  return res;
}

uint8_t ESP_GetIPAddrString(uint8_t *ipBuf, size_t ipBufSize) {
  /* AT+CIFSR */
  uint8_t rxBuf[32];
  uint8_t res;
  const unsigned char *p;

  res = ESP_SendATCommand("AT+CIFSR\r\n", rxBuf, sizeof(rxBuf), NULL, ESP_DEFAULT_TIMEOUT_MS);
  if (res!=ERR_OK) {
    if (UTIL1_strtailcmp(rxBuf, "\r\n")) {
      res = ERR_OK;
    }
  }
  if (res==ERR_OK) {
    if (UTIL1_strncmp(rxBuf, "AT+CIFSR\r\r\n", sizeof("AT+CIFSR\r\r\n")-1)==0) { /* check for beginning of response */
      UTIL1_strCutTail(rxBuf, "\r\n"); /* cut tailing response */
      p = rxBuf+sizeof("AT+CIFSR\r\r\n")-1; /* skip beginning */
      UTIL1_strcpy(ipBuf, ipBufSize, p); /* copy IP information string */
    } else {
      res = ERR_FAILED;
    }
  }
  if (res!=ERR_OK) {
    UTIL1_strcpy(ipBuf, ipBufSize, "ERROR");
  }
  return res;
}

uint8_t ESP_GetCIPMUXString(uint8_t *cipmuxBuf, size_t cipmuxBufSize) {
  /* AT+CIPMUX? */
  uint8_t rxBuf[32];
  uint8_t res;
  const unsigned char *p;

  res = ESP_SendATCommand("AT+CIPMUX?\r\n", rxBuf, sizeof(rxBuf), "\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS);
  if (res==ERR_OK) {
    if (UTIL1_strncmp(rxBuf, "AT+CIPMUX?\r\r\n+CIPMUX:", sizeof("AT+CIPMUX?\r\r\n+CIPMUX:")-1)==0) { /* check for beginning of response */
      UTIL1_strCutTail(rxBuf, "\r\n\r\nOK\r\n"); /* cut tailing response */
      p = rxBuf+sizeof("AT+CIPMUX?\r\r\n+CIPMUX:")-1; /* skip beginning */
      UTIL1_strcpy(cipmuxBuf, cipmuxBufSize, p); /* copy IP information string */
    } else {
      res = ERR_FAILED;
    }
  }
  if (res!=ERR_OK) {
    UTIL1_strcpy(cipmuxBuf, cipmuxBufSize, "ERROR");
  }
  return res;
}


uint8_t ESP_GetConnectedAPString(uint8_t *apBuf, size_t apBufSize) {
  /* AT+CWJAP? */
  uint8_t rxBuf[48];
  uint8_t res;
  const unsigned char *p;

  res = ESP_SendATCommand("AT+CWJAP?\r\n", rxBuf, sizeof(rxBuf), "\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS);
  if (res==ERR_OK) {
    if (UTIL1_strncmp(rxBuf, "AT+CWJAP?\r\r\n+CWJAP:\"", sizeof("AT+CWJAP?\r\r\n+CWJAP:\"")-1)==0) { /* check for beginning of response */
      UTIL1_strCutTail(rxBuf, "\"\r\n\r\nOK\r\n"); /* cut tailing response */
      p = rxBuf+sizeof("AT+CWJAP?\r\r\n+CWJAP:\"")-1; /* skip beginning */
      UTIL1_strcpy(apBuf, apBufSize, p); /* copy IP information string */
    } else {
      res = ERR_FAILED;
    }
  }
  if (res!=ERR_OK) {
    UTIL1_strcpy(apBuf, apBufSize, "ERROR");
  }
  return res;

}


uint8_t ESP_JoinAccessPoint(uint8_t *ssid, uint8_t *pwd, CLS1_ConstStdIOType *io) {
  /* AT+CWJAP="<ssid>","<pwd>" */
  uint8_t txBuf[48];
  uint8_t rxBuf[64];
  uint8_t expected[48];
  uint8_t res;

  UTIL1_strcpy(txBuf, sizeof(txBuf), "AT+CWJAP=\"");
  UTIL1_strcat(txBuf, sizeof(txBuf), ssid);
  UTIL1_strcat(txBuf, sizeof(txBuf), "\",\"");
  UTIL1_strcat(txBuf, sizeof(txBuf), pwd);
  UTIL1_strcat(txBuf, sizeof(txBuf), "\"\r\n");

  UTIL1_strcpy(expected, sizeof(expected), "AT+CWJAP=\"");
  UTIL1_strcat(expected, sizeof(expected), ssid);
  UTIL1_strcat(expected, sizeof(expected), "\",\"");
  UTIL1_strcat(expected, sizeof(expected), pwd);
  UTIL1_strcat(expected, sizeof(expected), "\"\r\r\n\r\nOK\r\n");

  res = ESP_SendATCommand(txBuf, rxBuf, sizeof(rxBuf), expected, ESP_DEFAULT_TIMEOUT_MS);
  if (io!=NULL) {
    CLS1_SendStr(rxBuf, res==ERR_OK?io->stdOut:io->stdErr);
  }
  return res;
}

uint8_t ESP_ConnectWiFi(uint8_t *ssid, uint8_t *pwd, int nofRetries, CLS1_ConstStdIOType *io) {
  uint8_t buf[32];
  uint8_t res;

  res = ESP_SelectWiFiMode(1);
  if (res==ERR_OK) {
    while(nofRetries>0) {
      res = ESP_JoinAccessPoint(ssid, pwd, io);
      if (res==ERR_OK) {
        break;
      }
      WAIT1_WaitOSms(2000);
      nofRetries--;
    }
  }
  return res;
}

static uint8_t ESP_SendWebPage(uint8_t ch_id, const CLS1_StdIOType *io) {
  static uint8_t httpHdr[64];
  uint8_t cmd[24], rxBuf[24], expected[24];
  uint8_t buf[16];
  uint8_t res;

  UTIL1_strcpy(httpHdr, sizeof(httpHdr), "HTTP/1.1 200 OK\r\n");
  UTIL1_strcat(httpHdr, sizeof(httpHdr), "Content-Type: text/html\r\n");
  UTIL1_strcat(httpHdr, sizeof(httpHdr), "Connection: close\r\n");

  UTIL1_strcpy(cmd, sizeof(cmd), "AT+CIPSEND="); /* parameters are <ch_id>,<size> */
  UTIL1_strcatNum8u(cmd, sizeof(cmd), ch_id);
  UTIL1_chcat(cmd, sizeof(cmd), ',');
  UTIL1_strcatNum16u(cmd, sizeof(cmd), UTIL1_strlen(httpHdr));
  UTIL1_strcat(cmd, sizeof(cmd), "\r\n");
  UTIL1_strcpy(expected, sizeof(expected), cmd); /* we expect the echo of our command */
  res = ESP_SendATCommand(cmd, rxBuf, sizeof(rxBuf), expected, ESP_DEFAULT_TIMEOUT_MS);
  for(;;) { /* breaks */
    res = ReadCharsUntil(buf, sizeof(buf), '\n', 1000);
    if (res==ERR_OK) { /* line read */
      if (io!=NULL) {
        CLS1_SendStr(buf, io->stdOut); /* copy on console */
      }
      if (UTIL1_strncmp(buf, ">", sizeof(">")-1)==0) { /* have ready signal to send data */
        Send(httpHdr);
      }
    }
  }
  return ERR_OK;
}

uint8_t ESP_StartWebServer(const CLS1_StdIOType *io) {
  uint8_t buf[64];
  uint8_t res=ERR_OK;
  uint8_t ch_id=0;
  uint16_t size=0;
  const uint8_t *p;

  ESP_SendStr("AT+CIPMUX=1", io); /* multiple connections, seems to be needed for server */
  ESP_SendStr("AT+CIPSERVER=1,80", io); /* single connection mode */
  CLS1_SendStr("INFO: Web Server started, waiting for connection.\r\n", io->stdOut);

  for(;;) { /* breaks */
    res = ReadCharsUntil(buf, sizeof(buf), '\n', 1000);
    if (res==ERR_OK) { /* line read */
      if (io!=NULL) {
        CLS1_SendStr(buf, io->stdOut); /* copy on console */
      }
      if (UTIL1_strncmp(buf, "+IPD,", sizeof("+IPD,")-1)==0) { /* start of IPD message */
        p = buf+sizeof("+IPD,")-1;
        if (UTIL1_ScanDecimal8uNumber(&p, &ch_id)!=ERR_OK) {
          if (io!=NULL) {
            CLS1_SendStr("ERR: wrong channel?\r\n", io->stdErr); /* error on console */
          }
          res = ERR_FAILED;
          break;
        }
        if (*p!=',') {
          res = ERR_FAILED;
          break;
        }
        p++; /* skip comma */
        if (UTIL1_ScanDecimal16uNumber(&p, &size)!=ERR_OK) {
          if (io!=NULL) {
            CLS1_SendStr("ERR: wrong size?\r\n", io->stdErr); /* error on console */
          }
          res = ERR_FAILED;
          break;
        } else {
          break; /* everything ok! */
        }
      }
    }
  }
  if (res==ERR_OK) {
    /* scan for OK at the end */
    for(;;) { /* breaks */
      res = ReadCharsUntil(buf, sizeof(buf), '\n', 1000);
      if (res==ERR_OK) {
        if (io!=NULL) {
          CLS1_SendStr(buf, io->stdOut); /* copy on console */
        }
        if (UTIL1_strncmp(buf, "OK", sizeof("OK")-1)==0) { /* finish of message */
          break;
        }
      }
    }
  }
  if (io!=NULL) {
    CLS1_SendStr("Connected!\r\n", io->stdOut); /* copy on console */
  }
  res = ESP_SendWebPage(ch_id, io);
  if (res!=ERR_OK) {
    CLS1_SendStr("Sending page failed!\r\n", io->stdErr); /* copy on console */
  }
  return res;
}

uint8_t ESP_SendStr(const uint8_t *str, CLS1_ConstStdIOType *io) {
  uint8_t buf[32];
  uint8_t rxBuf[48];
  uint8_t res;
  uint16_t timeoutMs;
  #define RX_TIMEOUT_MS 3000
  AS2_TComData ch;

  UTIL1_strcpy(buf, sizeof(buf), str);
  UTIL1_strcat(buf, sizeof(buf), "\r\n");
  res = ESP_SendATCommand(buf, rxBuf, sizeof(rxBuf), NULL, ESP_DEFAULT_TIMEOUT_MS);
  if (io!=NULL) {
    CLS1_SendStr(rxBuf, io->stdOut);
  }
  timeoutMs = 0;
  while(timeoutMs<RX_TIMEOUT_MS) {
    WAIT1_WaitOSms(100);
    timeoutMs += 100;
    while (AS2_GetCharsInRxBuf()>0) {
      (void)AS2_RecvChar(&ch);
      CLS1_SendChar(ch);
    }
  }
  return ERR_OK;
}

static uint8_t ESP_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr("ESP", "ESP8200 commands\r\n", io->stdOut);
  CLS1_SendHelpStr("  help|status", "Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr("  send <str>", "Sends a string to the module\r\n", io->stdOut);
  CLS1_SendHelpStr("  test", "Sends a test AT command\r\n", io->stdOut);
  CLS1_SendHelpStr("  restart", "Restart module\r\n", io->stdOut);
  CLS1_SendHelpStr("  listAP", "List Access Points\r\n", io->stdOut);
  CLS1_SendHelpStr("  connectedAP", "Show connected Access Points\r\n", io->stdOut);
  CLS1_SendHelpStr("  printIP", "Print own IP address\r\n", io->stdOut);
  CLS1_SendHelpStr("  startWeb", "Start web server\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t ESP_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];

  CLS1_SendStatusStr("ESP8266", "\r\n", io->stdOut);

  if (ESP_GetFirmwareString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  Firmware", buf, io->stdOut);

  if (ESP_GetIPAddrString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  IP", buf, io->stdOut);

  if (ESP_GetConnectedAPString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  AP", buf, io->stdOut);


  if (ESP_GetCIPMUXString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  CIPMUX", buf, io->stdOut);
  return ERR_OK;
}

uint8_t ESP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint32_t val;
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ESP help")==0) {
    *handled = TRUE;
    return ESP_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "ESP status")==0) {
    *handled = TRUE;
    return ESP_PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "ESP send ", sizeof("ESP send ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("ESP send ")-1;

    (void)ESP_SendStr(p, io);
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ESP test")==0) {
    *handled = TRUE;
    if (ESP_Test()!=ERR_OK) {
      CLS1_SendStr("TEST failed!\r\n", io->stdErr);
    } else {
      CLS1_SendStr("TEST ok!\r\n", io->stdOut);
    }
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ESP listAP")==0) {
    *handled = TRUE;
    (void)ESP_SendStr("AT+CWLAP", io);
    /* AT + CWLAP
    response
    + CWLAP: <ecn>, <ssid>, <rssi> [, <mode>]
    OK Or Fails, the return ERROR
    <Ecn> 0 OPEN
    1 WEP
    2 WPA_PSK
    3 WPA2_PSK
    4 WPA_WPA2_PSK
    <Ssid> string parameter, the access point name
    <Rssi> signal strength
    <Mode> 0: manually connect 1: An automatic connection
     */
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ESP connectedAP")==0) {
    *handled = TRUE;
    (void)ESP_SendStr("AT+CWJAP?", io);
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ESP printIP")==0) {
    *handled = TRUE;
    (void)ESP_SendStr("AT+CIFSR", io);
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ESP startWeb")==0) {
    *handled = TRUE;
    (void)ESP_StartWebServer(io);
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ESP restart")==0) {
    *handled = TRUE;
    ESP_Restart(io, 2000);
    return ERR_OK;
  }
  return ERR_OK;
}

void ESP_Init(void) {
  AS2_ClearRxBuf(); /* clear buffer */
}
