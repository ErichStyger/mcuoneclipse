/*
 * ESP8266.c
 *
 *      Author: Erich Styger
 */

#include "ESP8266.h"
#include "Shell.h"
#include "UTIL1.h"
#include "CLS1.h"
#include "AS2.h"
#include "WAIT1.h"

static bool ESP_WebServerIsOn = FALSE;

uint8_t UTIL_ScanDoubleQuotedString(const uint8_t **cmd, uint8_t *buf, size_t bufSize)
{
  const uint8_t *p = *cmd;

  if (bufSize==1) {
    return ERR_FAILED; /* buffer too small */
  }
  buf[bufSize-1] = '\0'; /* terminate buffer */
  bufSize--;
  if (*p!='\"') {
    return ERR_FAILED; /* does not start with double quote */
  }
  p++; /* skip double quote */
  while(*p!='\"' && *p!='\0' && bufSize>0) {
    *buf++ = *p++;
    bufSize--;
  }
  if (*p!='\"') {
    return ERR_FAILED; /* no terminating double quote */
  } else {
    p++; /* skip double quote */
    *buf = '\0'; /* terminate buffer */
  }
  *cmd = p; /* advance pointer */
  return ERR_OK;
}


bool ESP_IsServerOn(void) {
  return ESP_WebServerIsOn;
}

static void Send(unsigned char *str) {
  while(*str!='\0') {
    AS2_SendChar(*str);
    str++;
  }
}

static void SkipNewLines(const unsigned char **p) {
  while(**p=='\n' || **p=='\r') {
    (*p)++; /* skip new lines */
  }
}

uint8_t ESP_ReadCharsUntil(uint8_t *buf, size_t bufSize, uint8_t sentinelChar, uint16_t timeoutMs) {
  uint8_t ch;
  uint8_t res = ERR_OK;

  if (bufSize<=1) {
    return ERR_OVERRUN; /* buffer to small */
  }
  buf[0] = '\0'; buf[bufSize-1] = '\0'; /* always terminate */
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
        WAIT1_WaitOSms(5);
        timeoutMs -= 5;
      } else {
        res = ERR_NOTAVAIL; /* timeout */
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

uint8_t ESP_SendATCommand(uint8_t *cmd, uint8_t *rxBuf, size_t rxBufSize, uint8_t *expectedTailStr, uint16_t msTimeout, const CLS1_StdIOType *io) {
  uint16_t snt;
  uint8_t res;

  if (rxBuf!=NULL) {
    rxBuf[0] = '\0';
  }
  if (io!=NULL) {
    CLS1_SendStr("sending>>:\r\n", io->stdOut);
    CLS1_SendStr(cmd, io->stdOut);
  }
  if (AS2_SendBlock(cmd, (uint16_t)UTIL1_strlen((char*)cmd), &snt) != ERR_OK) {
    return ERR_FAILED;
  }
  if (rxBuf!=NULL) {
    res = RxResponse(rxBuf, rxBufSize, expectedTailStr, msTimeout);
    if (io!=NULL) {
      CLS1_SendStr("received<<:\r\n", io->stdOut);
      CLS1_SendStr(rxBuf, io->stdOut);
    }
  }
  return res;
}

uint8_t ESP_TestAT(void) {
  /* AT */
  uint8_t rxBuf[sizeof("AT\r\r\n\r\nOK\r\n")];
  uint8_t res;

  res = ESP_SendATCommand("AT\r\n", rxBuf, sizeof(rxBuf), "AT\r\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS, NULL);
  return res;
}

uint8_t ESP_Restart(const CLS1_StdIOType *io, uint16_t timeoutMs) {
  /* AT+RST */
  uint8_t rxBuf[sizeof("AT+RST\r\r\n\r\nOK\r\n")];
  uint8_t res;
  uint8_t buf[64];

  AS2_ClearRxBuf(); /* clear buffer */
  res = ESP_SendATCommand("AT+RST\r\n", rxBuf, sizeof(rxBuf), "AT+RST\r\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS, io);
  if (res==ERR_OK) {
    for(;;) {
      ESP_ReadCharsUntil(buf, sizeof(buf), '\n', 1000);
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

uint8_t ESP_CloseConnection(uint8_t channel, const CLS1_StdIOType *io, uint16_t timeoutMs) {
  /* AT+CIPCLOSE=<channel> */
  uint8_t res;
  uint8_t cmd[64];

  UTIL1_strcpy(cmd, sizeof(cmd), "AT+CIPCLOSE=");
  UTIL1_strcatNum8u(cmd, sizeof(cmd), channel);
  UTIL1_strcat(cmd, sizeof(cmd), "\r\n");
  res = ESP_SendATCommand(cmd, NULL, 0, "Unlink\r\n", timeoutMs, io);
  return res;
}

uint8_t ESP_SetNumberOfConnections(uint8_t nof, const CLS1_StdIOType *io, uint16_t timeoutMs) {
  /* AT+CIPMUX=<nof>, 0: single connection, 1: multiple connections */
  uint8_t res;
  uint8_t cmd[sizeof("AT+CIPMUX=12\r\n")];
  uint8_t rxBuf[sizeof("AT+CIPMUX=12\r\n\r\nOK\r\n")+10];

  if (nof>1) { /* only 0 and 1 allowed */
    if (io!=NULL) {
      CLS1_SendStr("Wrong number of connection parameter!\r\n", io->stdErr);
    }
    return ERR_FAILED;
  }
  UTIL1_strcpy(cmd, sizeof(cmd), "AT+CIPMUX=");
  UTIL1_strcatNum8u(cmd, sizeof(cmd), nof);
  UTIL1_strcat(cmd, sizeof(cmd), "\r\n");
  res = ESP_SendATCommand(cmd, rxBuf, sizeof(rxBuf), "OK\r\n", timeoutMs, io);
  return res;
}

uint8_t ESP_SetServer(bool startIt, uint16_t port, const CLS1_StdIOType *io, uint16_t timeoutMs) {
  /* AT+CIPSERVER=<en>,<port>, where <en>: 0: stop, 1: start */
  uint8_t res;
  uint8_t cmd[sizeof("AT+CIPSERVER=1,80\r\n\r\nOK\r\n")+sizeof("no change")];
  uint8_t rxBuf[sizeof("AT+CIPSERVER=1,80\r\n\r\nOK\r\n")+sizeof("no change")];

  UTIL1_strcpy(cmd, sizeof(cmd), "AT+CIPSERVER=");
  if (startIt) {
    UTIL1_strcat(cmd, sizeof(cmd), "1,");
  } else {
    UTIL1_strcat(cmd, sizeof(cmd), "0,");
  }
  UTIL1_strcatNum16u(cmd, sizeof(cmd), port);
  UTIL1_strcat(cmd, sizeof(cmd), "\r\n");
  res = ESP_SendATCommand(cmd, rxBuf, sizeof(rxBuf), "OK\r\n", timeoutMs, io);
  if (res!=ERR_OK) { /* accept "no change" too */
    UTIL1_strcpy(cmd, sizeof(cmd), "AT+CIPSERVER=");
    if (startIt) {
      UTIL1_strcat(cmd, sizeof(cmd), "1,");
    } else {
      UTIL1_strcat(cmd, sizeof(cmd), "0,");
    }
    UTIL1_strcatNum16u(cmd, sizeof(cmd), port);
    UTIL1_strcat(cmd, sizeof(cmd), "\r\r\nno change\r\n");
    if (UTIL1_strcmp(rxBuf, cmd)==0) {
      res = ERR_OK;
    }
  }
  return res;
}

uint8_t ESP_SelectMode(uint8_t mode) {
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
  res = ESP_SendATCommand(txBuf, rxBuf, sizeof(rxBuf), expected, ESP_DEFAULT_TIMEOUT_MS, NULL);
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

uint8_t ESP_GetFirmwareVersionString(uint8_t *fwBuf, size_t fwBufSize) {
  /* AT+GMR */
  uint8_t rxBuf[32];
  uint8_t res;
  const unsigned char *p;

  res = ESP_SendATCommand("AT+GMR\r\n", rxBuf, sizeof(rxBuf), "\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS, NULL);
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

  res = ESP_SendATCommand("AT+CIFSR\r\n", rxBuf, sizeof(rxBuf), NULL, ESP_DEFAULT_TIMEOUT_MS, NULL);
  if (res!=ERR_OK) {
    if (UTIL1_strtailcmp(rxBuf, "\r\n")) {
      res = ERR_OK;
    }
  }
  if (res==ERR_OK) {
    if (UTIL1_strncmp(rxBuf, "AT+CIFSR\r\r\n", sizeof("AT+CIFSR\r\r\n")-1)==0) { /* check for beginning of response */
      UTIL1_strCutTail(rxBuf, "\r\n"); /* cut tailing response */
      p = rxBuf+sizeof("AT+CIFSR\r\r\n")-1; /* skip beginning */
      SkipNewLines(&p);
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

uint8_t ESP_GetModeString(uint8_t *buf, size_t bufSize) {
  /* AT+CWMODE? */
  uint8_t rxBuf[32];
  uint8_t res;
  const unsigned char *p;

  res = ESP_SendATCommand("AT+CWMODE?\r\n", rxBuf, sizeof(rxBuf), "\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS, NULL);
  if (res==ERR_OK) {
    if (UTIL1_strncmp(rxBuf, "AT+CWMODE?\r\r\n+CWMODE:", sizeof("AT+CWMODE?\r\r\n+CWMODE:")-1)==0) { /* check for beginning of response */
      UTIL1_strCutTail(rxBuf, "\r\n\r\nOK\r\n"); /* cut tailing response */
      p = rxBuf+sizeof("AT+CWMODE?\r\r\n+CWMODE:")-1; /* skip beginning */
      UTIL1_strcpy(buf, bufSize, p); /* copy information string */
    } else {
      res = ERR_FAILED;
    }
  }
  if (res!=ERR_OK) {
    UTIL1_strcpy(buf, bufSize, "ERROR");
  }
  return res;
}

uint8_t ESP_GetCIPMUXString(uint8_t *cipmuxBuf, size_t cipmuxBufSize) {
  /* AT+CIPMUX? */
  uint8_t rxBuf[32];
  uint8_t res;
  const unsigned char *p;

  res = ESP_SendATCommand("AT+CIPMUX?\r\n", rxBuf, sizeof(rxBuf), "\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS, NULL);
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

  res = ESP_SendATCommand("AT+CWJAP?\r\n", rxBuf, sizeof(rxBuf), "\r\n\r\nOK\r\n", ESP_DEFAULT_TIMEOUT_MS, NULL);
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

static uint8_t JoinAccessPoint(const uint8_t *ssid, const uint8_t *pwd, CLS1_ConstStdIOType *io) {
  /* AT+CWJAP="<ssid>","<pwd>" */
  uint8_t txBuf[48];
  uint8_t rxBuf[64];
  uint8_t expected[48];

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

  return ESP_SendATCommand(txBuf, rxBuf, sizeof(rxBuf), expected, ESP_DEFAULT_TIMEOUT_MS, io);
}

uint8_t ESP_JoinAP(const uint8_t *ssid, const uint8_t *pwd, int nofRetries, CLS1_ConstStdIOType *io) {
  uint8_t buf[32];
  uint8_t res;

  do {
    res = JoinAccessPoint(ssid, pwd, io);
    if (res==ERR_OK) {
      break;
    }
    WAIT1_WaitOSms(1000);
    nofRetries--;
  } while (nofRetries>0);
  return res;
}


static uint8_t ReadIntoIPDBuffer(uint8_t *buf, size_t bufSize, uint8_t *p, uint16_t msgSize, uint16_t msTimeout, const CLS1_StdIOType *io) {
  uint8_t ch;
  size_t nofInBuf;
  int timeout;

  nofInBuf = p-buf;
  bufSize -= nofInBuf; /* take into account what we already have in buffer */
  timeout = msTimeout;
  while (msgSize>0 && bufSize>0) {
    if (AS2_GetCharsInRxBuf()>0) {
      (void)AS2_RecvChar(&ch);
      *p = ch;
      if (io!=NULL) { /* copy on console */
        io->stdOut(ch);
      }
      p++;
      *p = '\0'; /* terminate */
      nofInBuf++; msgSize--; bufSize--;
    } else {
      /* check in case we recveive less characters than expected, happens for POST? */
      if (nofInBuf>6 && UTIL1_strncmp(&p[-6], "\r\nOK\r\n", sizeof("\r\nOK\r\n")-1)==0) {
        break;
      } else {
        timeout -= 10;
        WAIT1_WaitOSms(10);
        if (timeout<0) {
          return ERR_BUSY;
        }
      }
    }
  }
  return ERR_OK;
}

uint8_t ESP_GetIPD(uint8_t *msgBuf, size_t msgBufSize, uint8_t *ch_id, uint16_t *size, bool *isGet, uint16_t timeoutMs, const CLS1_StdIOType *io) {
  /* scan e.g. for
   * +IPD,0,404:POST / HTTP/1.1
   * and return ch_id (0), size (404)
   */
  uint8_t res = ERR_OK;
  const uint8_t *p;
  bool isIPD = FALSE;
  uint8_t cmd[24], rxBuf[48];
  uint16_t ipdSize;

  *ch_id = 0; *size = 0; *isGet = FALSE; /* init */
  for(;;) { /* breaks */
    res = ESP_ReadCharsUntil(msgBuf, msgBufSize, '\n', timeoutMs);
    if (res!=ERR_OK) {
      break; /* timeout */
    }
    if (res==ERR_OK) { /* line read */
      if (io!=NULL) {
        CLS1_SendStr(msgBuf, io->stdOut); /* copy on console */
      }
      isIPD = UTIL1_strncmp(msgBuf, "+IPD,", sizeof("+IPD,")-1)==0;
      if (isIPD) { /* start of IPD message */
        p = msgBuf+sizeof("+IPD,")-1;
        if (UTIL1_ScanDecimal8uNumber(&p, ch_id)!=ERR_OK) {
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
        if (UTIL1_ScanDecimal16uNumber(&p, size)!=ERR_OK) {
          if (io!=NULL) {
            CLS1_SendStr("ERR: wrong size?\r\n", io->stdErr); /* error on console */
          }
          res = ERR_FAILED;
          break;
        }
        if (*p!=':') {
          res = ERR_FAILED;
          break;
        }
        ipdSize = p-msgBuf; /* length of "+IPD,<channel>,<size>" string */
        p++; /* skip ':' */
        if (UTIL1_strncmp(p, "GET", sizeof("GET")-1)==0) {
          *isGet = TRUE;
        } else if (UTIL1_strncmp(p, "POST", sizeof("POST")-1)==0) {
          *isGet = FALSE;
        } else {
          res = ERR_FAILED;
        }
        while(*p!='\0') {
          p++; /* skip to the end */
        }
        /* read the rest of the message */
        res = ReadIntoIPDBuffer(msgBuf, msgBufSize, (uint8_t*)p, (*size)-ipdSize, ESP_DEFAULT_TIMEOUT_MS, io);
        break;
      }
    }
  }
  return res;
}

uint8_t ESP_StartWebServer(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  uint8_t res;

  res = ESP_SetNumberOfConnections(1, io, ESP_DEFAULT_TIMEOUT_MS);
  if (res!=ERR_OK) {
    CLS1_SendStr("ERR: failed to set multiple connections.\r\n", io->stdErr);
    return res;
  }
  res = ESP_SetServer(TRUE, 80, io, ESP_DEFAULT_TIMEOUT_MS);
  if (res!=ERR_OK) {
    CLS1_SendStr("ERR: failed to set server.\r\n", io->stdErr);
    return res;
  }
  CLS1_SendStr("INFO: Web Server started, waiting for connection on ", io->stdOut);
  if (ESP_GetIPAddrString(buf, sizeof(buf))==ERR_OK) {
    CLS1_SendStr(buf, io->stdOut);
    CLS1_SendStr(":80", io->stdOut);
  } else {
    CLS1_SendStr("(ERROR!)", io->stdOut);
  }
  CLS1_SendStr("\r\n", io->stdOut);

  return ERR_OK;
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
  res = ESP_SendATCommand(buf, rxBuf, sizeof(rxBuf), NULL, ESP_DEFAULT_TIMEOUT_MS, io);
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
  CLS1_SendHelpStr("  listAP", "List available Access Points\r\n", io->stdOut);
  CLS1_SendHelpStr("  connectAP \"ssid\",\"pwd\"", "Connect to an Access Point\r\n", io->stdOut);
  CLS1_SendHelpStr("  server (start|stop)", "Start or stop web server\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t ESP_PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[48];

  CLS1_SendStatusStr("ESP8266", "\r\n", io->stdOut);

  CLS1_SendStatusStr("  Webserver", ESP_WebServerIsOn?"ON\r\n":"OFF\r\n", io->stdOut);

  if (ESP_GetFirmwareVersionString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    /* 00160901: 0016 is SDK version, 0901 is the AT version */
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  AT+GMR", buf, io->stdOut);

  if (ESP_GetModeString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    if (UTIL1_strcmp(buf, "1")==0) {
      UTIL1_strcat(buf, sizeof(buf), " (device)");
    } else if (UTIL1_strcmp(buf, "2")==0) {
      UTIL1_strcat(buf, sizeof(buf), " (AP)");
    } else if (UTIL1_strcmp(buf, "3")==0) {
      UTIL1_strcat(buf, sizeof(buf), " (device+AP)");
    } else {
      UTIL1_strcat(buf, sizeof(buf), " (ERROR)");
    }
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  AT+CWMODE?", buf, io->stdOut);

  if (ESP_GetIPAddrString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  AT+CIFSR", buf, io->stdOut);

  if (ESP_GetConnectedAPString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  AT+CWJAP?", buf, io->stdOut);

  if (ESP_GetCIPMUXString(buf, sizeof(buf)) != ERR_OK) {
    UTIL1_strcpy(buf, sizeof(buf), "FAILED\r\n");
  } else {
    if (UTIL1_strcmp(buf, "0")==0) {
      UTIL1_strcat(buf, sizeof(buf), " (single connection)");
    } else if (UTIL1_strcmp(buf, "1")==0) {
      UTIL1_strcat(buf, sizeof(buf), " (multiple connections)");
    } else {
      UTIL1_strcat(buf, sizeof(buf), " (ERROR)");
    }
    UTIL1_strcat(buf, sizeof(buf), "\r\n");
  }
  CLS1_SendStatusStr("  CIPMUX", buf, io->stdOut);
  return ERR_OK;
}

uint8_t ESP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint32_t val;
  uint8_t res;
  const unsigned char *p;
  uint8_t pwd[24], ssid[24];

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "ESP help")==0) {
    *handled = TRUE;
    res = ESP_PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "ESP status")==0) {
    *handled = TRUE;
    res = ESP_PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "ESP send ", sizeof("ESP send ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("ESP send ")-1;

    (void)ESP_SendStr(p, io);
  } else if (UTIL1_strcmp((char*)cmd, "ESP test")==0) {
    *handled = TRUE;
    if (ESP_TestAT()!=ERR_OK) {
      CLS1_SendStr("TEST failed!\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      CLS1_SendStr("TEST ok!\r\n", io->stdOut);
    }
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
  } else if (UTIL1_strncmp((char*)cmd, "ESP connectAP ", sizeof("ESP connectAP ")-1)==0) {
    *handled = TRUE;
    p = cmd+sizeof("ESP connectAP ")-1;
    ssid[0] = '\0'; pwd[0] = '\0';
    res = UTIL_ScanDoubleQuotedString(&p, ssid, sizeof(ssid));
    if (res==ERR_OK && *p!='\0' && *p==',') {
      p++; /* skip comma */
      res = UTIL_ScanDoubleQuotedString(&p, pwd, sizeof(pwd));
    } else {
      CLS1_SendStr("Comma expected between strings!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
    if (res==ERR_OK) {
      res = ESP_JoinAP(ssid, pwd, 3, io);
    } else {
      CLS1_SendStr("Wrong command format!\r\n", io->stdErr);
      res = ERR_FAILED;
    }
  } else if (UTIL1_strcmp((char*)cmd, "ESP server start")==0) {
    *handled = TRUE;
    res = ESP_StartWebServer(io);
    ESP_WebServerIsOn = res==ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, "ESP server stop")==0) {
    *handled = TRUE;
    ESP_WebServerIsOn = FALSE;
  } else if (UTIL1_strcmp((char*)cmd, "ESP restart")==0) {
    *handled = TRUE;
    ESP_Restart(io, 2000);
  }
  return res;
}

void ESP_Deinit(void) {
  /* nothing to do */
}

void ESP_Init(void) {
  AS2_ClearRxBuf(); /* clear buffer */
}
